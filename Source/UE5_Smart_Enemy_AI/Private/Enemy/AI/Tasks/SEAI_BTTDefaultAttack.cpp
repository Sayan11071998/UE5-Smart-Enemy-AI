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
			
			Enemy->OnAttackEnd.RemoveDynamic(this, &USEAI_BTTDefaultAttack::HandleAttackFinished);
			Enemy->OnAttackEnd.AddDynamic(this, &USEAI_BTTDefaultAttack::HandleAttackFinished);

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
		AAIController* AIController = CachedBTComp->GetAIOwner();
		if (AIController)
		{
			ASEAI_EnemyCharacter_Base* Enemy = Cast<ASEAI_EnemyCharacter_Base>(AIController->GetPawn());
			if (Enemy)
			{
				Enemy->OnAttackEnd.RemoveDynamic(this, &USEAI_BTTDefaultAttack::HandleAttackFinished);
			}
		}

		FinishLatentTask(*CachedBTComp, EBTNodeResult::Succeeded);
		CachedBTComp = nullptr;
	}
}