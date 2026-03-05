#include "Enemy/AI/SEAI_EnemyAIController_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ASEAI_EnemyAIController_Base::ASEAI_EnemyAIController_Base()
{
}

void ASEAI_EnemyAIController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	GetWorldTimerManager().SetTimer(
		PossessionTimerHandle, 
		this,
		&ASEAI_EnemyAIController_Base::OnPossessionDelayCompleted,
		0.2f,
		false	
	);
}

void ASEAI_EnemyAIController_Base::OnPossessionDelayCompleted()
{
	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
		
		if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			BlackboardComponent->SetValueAsObject(AttackTargetKeyName, PlayerCharacter);
		}
	}
}