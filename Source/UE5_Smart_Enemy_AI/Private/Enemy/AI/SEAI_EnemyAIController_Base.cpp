#include "Enemy/AI/SEAI_EnemyAIController_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/AI/Enums/SEAI_AI_DataTypes.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "PlayerCharacter/SEAI_PlayerCharacter.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"

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
	
	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
		SetStateAsPassive();
	}
}

void ASEAI_EnemyAIController_Base::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	// Check if the perceived actor is the Player
	if (Actor && Actor->IsA<ASEAI_PlayerCharacter>())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			// Spotted the player -> Start Attacking
			SetStateAsAttacking(Actor);
		}
		else
		{
			// Lost sight of the player -> Go back to Passive
			SetStateAsPassive();
		}
	}
}

void ASEAI_EnemyAIController_Base::SetStateAsPassive()
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		BlackboardComponent->SetValueAsEnum(StateKeyName, static_cast<uint8>(ESEAI_AIState::Passive));
	}
}

void ASEAI_EnemyAIController_Base::SetStateAsAttacking(TObjectPtr<AActor> Target)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		BlackboardComponent->SetValueAsObject(AttackTargetKeyName, Target);
		BlackboardComponent->SetValueAsEnum(StateKeyName, static_cast<uint8>(ESEAI_AIState::Attacking));
	}
}