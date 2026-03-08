#include "Enemy/AI/Tasks/SEAI_BTT_UnequipSword.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "AIController.h"

USEAI_BTT_UnequipSword::USEAI_BTT_UnequipSword()
{
	NodeName = TEXT("Unequip Sword");
}

EBTNodeResult::Type USEAI_BTT_UnequipSword::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ASEAI_EnemyCharacter_Base* Enemy = Cast<ASEAI_EnemyCharacter_Base>(AIController->GetPawn()))
		{
			CachedBTComp = &OwnerComp;
			Enemy->OnUnequipSwordEnd.AddUniqueDynamic(this, &USEAI_BTT_UnequipSword::OnUnequipFinished);
			
			Enemy->UnequipSword();
			return EBTNodeResult::InProgress;
		}
	}
	
	return EBTNodeResult::Failed;
}

void USEAI_BTT_UnequipSword::OnUnequipFinished()
{
	if (CachedBTComp)
	{
		FinishLatentTask(*CachedBTComp, EBTNodeResult::Succeeded);
	}
}