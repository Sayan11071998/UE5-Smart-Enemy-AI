#include "Enemy/AI/SEAI_EnemyAIController_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/AI/Enums/SEAI_AI_DataTypes.h"

ASEAI_EnemyAIController_Base::ASEAI_EnemyAIController_Base()
{
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