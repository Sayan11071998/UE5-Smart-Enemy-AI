#include "Enemy/AI/Tasks/SEAI_BTTDefaultAttack.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "AIController.h"

USEAI_BTTDefaultAttack::USEAI_BTTDefaultAttack()
{
	NodeName = TEXT("Default Attack");
	bNotifyTick = false;
}

EBTNodeResult::Type USEAI_BTTDefaultAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		ASEAI_EnemyCharacter_Base* Enemy = Cast<ASEAI_EnemyCharacter_Base>(AIController->GetPawn());
		if (Enemy)
		{
			CachedBTComp = &OwnerComp;
			
			// Bind to the attack end delegate
			Enemy->OnAttackEnd.AddDynamic(this, &USEAI_BTTDefaultAttack::HandleAttackFinished);
			
			// Start the attack
			Enemy->Attack();
			
			return EBTNodeResult::InProgress;
		}
	}
	
	return EBTNodeResult::Failed;
}

void USEAI_BTTDefaultAttack::HandleAttackFinished()
{
	if (CachedBTComp)
	{
		FinishLatentTask(*CachedBTComp, EBTNodeResult::Succeeded);
	}
}