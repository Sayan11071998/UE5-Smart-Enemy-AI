#include "Enemy/AI/SEAI_EnemyAIController_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/AI/Enums/SEAI_AI_DataTypes.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "PlayerCharacter/SEAI_PlayerCharacter.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AIPerceptionSystem.h"
#include "Interfaces/SEAI_EnemyAI_Interface.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"

ASEAI_EnemyAIController_Base::ASEAI_EnemyAIController_Base()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	
	SightConfig->SightRadius = 800.f;
	SightConfig->LoseSightRadius = 1200.f;
	SightConfig->PeripheralVisionAngleDegrees = 60.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	
	HearingConfig->HearingRange = 500.f;
	HearingConfig->SetMaxAge(3.f);
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	
	DamageConfig->SetMaxAge(5.0f);

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->ConfigureSense(*HearingConfig);
	PerceptionComp->ConfigureSense(*DamageConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ASEAI_EnemyAIController_Base::HandleTargetPerceptionUpdated);
}

void ASEAI_EnemyAIController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (ASEAI_EnemyCharacter_Base* EnemyCharacter = Cast<ASEAI_EnemyCharacter_Base>(InPawn))
	{
		if (UBehaviorTree* BT = EnemyCharacter->BehaviorTree)
		{
			RunBehaviorTree(BT);
			SetStateAsPassive();
			
			float AttackRadius = 0.f;
			float DefendRadius = 0.f;
			
			ISEAI_EnemyAI_Interface::Execute_GetIdealRange(InPawn, AttackRadius, DefendRadius);
			
			if (UBlackboardComponent* BlackboardComp = GetBlackboardComponent())
			{
				BlackboardComp->SetValueAsFloat(AttackRadiusKeyName, AttackRadius);
				BlackboardComp->SetValueAsFloat(DefendRadiusKeyName, DefendRadius);
			}
		}
	}
}

bool ASEAI_EnemyAIController_Base::CanSenseActor(TObjectPtr<AActor> Actor, ESEAI_AISense Sense,
	FAIStimulus& OutStimulus) const
{
	if (!Actor || !PerceptionComp) return false;
	
	FActorPerceptionBlueprintInfo PerceptionInfo;
	PerceptionComp->GetActorsPerception(Actor, PerceptionInfo);

	TSubclassOf<UAISense> SenseClass;
	switch (Sense)
	{
	case ESEAI_AISense::Sight:
		SenseClass = UAISense_Sight::StaticClass();
		break;
	case ESEAI_AISense::Hearing:
		SenseClass = UAISense_Hearing::StaticClass();
		break;
	case ESEAI_AISense::Damage:
		SenseClass = UAISense_Damage::StaticClass();
		break;
	default:
		return false;
	}
	
	// Loop through "Last Sensed Stimuli" to find a match
	for (const FAIStimulus& Stimulus : PerceptionInfo.LastSensedStimuli)
	{
		if (UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus) == SenseClass)
		{
			if (Stimulus.WasSuccessfullySensed())
			{
				OutStimulus = Stimulus;
				return true;
			}
		}
	}
	return false;
}

ESEAI_AIState ASEAI_EnemyAIController_Base::GetCurrentState() const
{
	if (const UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		return static_cast<ESEAI_AIState>(BlackboardComponent->GetValueAsEnum(StateKeyName));
	}
	return ESEAI_AIState::Passive;
}

void ASEAI_EnemyAIController_Base::HandleSensedSight(TObjectPtr<AActor> Actor)
{
	ESEAI_AIState CurrentState = GetCurrentState();
	
	// Switch on State: only proceed if Passive, Frozen, or Investigating
	if (CurrentState == ESEAI_AIState::Passive ||
		CurrentState == ESEAI_AIState::Investigating)
	{
		// Is the actor the Player Character?
		if (Actor && Actor->IsA<ASEAI_PlayerCharacter>())
		{
			SetStateAsAttacking(Actor);
		}
	}
}

void ASEAI_EnemyAIController_Base::HandleSensedSound(FVector Location)
{
	ESEAI_AIState CurrentState = GetCurrentState();
	if (CurrentState == ESEAI_AIState::Passive || CurrentState == ESEAI_AIState::Investigating)
	{
		SetStateAsInvestigating(Location);
	}
}

void ASEAI_EnemyAIController_Base::HandleSensedDamage(TObjectPtr<AActor> Actor)
{
	ESEAI_AIState CurrentState = GetCurrentState();
	if (CurrentState == ESEAI_AIState::Passive ||
		CurrentState == ESEAI_AIState::Investigating)
	{
		SetStateAsAttacking(Actor);
	}
}

void ASEAI_EnemyAIController_Base::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor) return;
	
	FAIStimulus CurrentStimulus;
	
	// Check Sight
	if (CanSenseActor(Actor, ESEAI_AISense::Sight, CurrentStimulus))
	{
		HandleSensedSight(Actor);
	}
	
	// Check Hearing
	if (CanSenseActor(Actor, ESEAI_AISense::Hearing, CurrentStimulus))
	{
		HandleSensedSound(CurrentStimulus.StimulusLocation);
	}
	
	// Check Damage
	if (CanSenseActor(Actor, ESEAI_AISense::Damage, CurrentStimulus))
	{
		HandleSensedDamage(Actor);
	}
}

void ASEAI_EnemyAIController_Base::SetStateAsPassive()
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		AttackTarget = nullptr;
		
		BlackboardComponent->SetValueAsEnum(StateKeyName, static_cast<uint8>(ESEAI_AIState::Passive));
	}
}

void ASEAI_EnemyAIController_Base::SetStateAsAttacking(TObjectPtr<AActor> Target)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		AttackTarget = Target.Get();
		
		BlackboardComponent->SetValueAsObject(AttackTargetKeyName, Target);
		BlackboardComponent->SetValueAsEnum(StateKeyName, static_cast<uint8>(ESEAI_AIState::Attacking));
		
		SetFocus(AttackTarget);
	}
}

void ASEAI_EnemyAIController_Base::SetStateAsInvestigating(FVector Location)
{
	if (UBlackboardComponent* BlackboardComp = GetBlackboardComponent())
	{
		BlackboardComp->SetValueAsEnum(StateKeyName, static_cast<uint8>(ESEAI_AIState::Investigating));
		BlackboardComp->SetValueAsVector(PointOfInterestKeyName, Location);
	}
}