#include "Enemy/AI/Tasks/SEAI_BTT_EquipSword.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "AIController.h"

USEAI_BTT_EquipSword::USEAI_BTT_EquipSword()
{
	NodeName = TEXT("Equip Sword");
}

EBTNodeResult::Type USEAI_BTT_EquipSword::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ASEAI_EnemyCharacter_Base* Enemy = Cast<ASEAI_EnemyCharacter_Base>(AIController->GetPawn()))
		{
			CachedBTComp = &OwnerComp;
			Enemy->OnEquipSwordEnd.AddUniqueDynamic(this, &USEAI_BTT_EquipSword::OnEquipFinished);
			
			Enemy->EquipSword();
			return EBTNodeResult::InProgress;
		}
	}
	
	return EBTNodeResult::Failed;
}

void USEAI_BTT_EquipSword::OnEquipFinished()
{
	if (CachedBTComp)
	{
		FinishLatentTask(*CachedBTComp, EBTNodeResult::Succeeded);
	}
}