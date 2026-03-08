#include "Enemy/AI/Tasks/SEAI_BTT_WieldSword.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "AIController.h"

USEAI_BTT_WieldSword::USEAI_BTT_WieldSword()
{
	NodeName = TEXT("Wield Sword");
}

EBTNodeResult::Type USEAI_BTT_WieldSword::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ASEAI_EnemyCharacter_Base* Enemy = Cast<ASEAI_EnemyCharacter_Base>(AIController->GetPawn()))
		{
			CachedBTComp = &OwnerComp;
			Enemy->OnEquipSwordEnd.AddUniqueDynamic(this, &USEAI_BTT_WieldSword::OnWieldFinished);
			
			Enemy->WieldSword();
			return EBTNodeResult::InProgress;
		}
	}
	
	return EBTNodeResult::Failed;
}

void USEAI_BTT_WieldSword::OnWieldFinished()
{
	if (CachedBTComp)
	{
		FinishLatentTask(*CachedBTComp, EBTNodeResult::Succeeded);
	}
}