#include "Enemy/AI/Tasks/SEAI_BTT_UnequipWeapon.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "Interfaces/SEAI_EnemyAI_Interface.h"
#include "AIController.h"

USEAI_BTT_UnequipWeapon::USEAI_BTT_UnequipWeapon()
{
	NodeName = TEXT("Unequip Weapon");
}

EBTNodeResult::Type USEAI_BTT_UnequipWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		APawn* ControlledPawn = AIController->GetPawn();
		if (ISEAI_EnemyAI_Interface* EnemyInterface = Cast<ISEAI_EnemyAI_Interface>(ControlledPawn))
		{
			if (ASEAI_EnemyCharacter_Base* Enemy = Cast<ASEAI_EnemyCharacter_Base>(ControlledPawn))
			{
				CachedBTComp = &OwnerComp;
				Enemy->OnWeaponUnequipped.AddUniqueDynamic(this, &USEAI_BTT_UnequipWeapon::OnUnequipFinished);
				
				ISEAI_EnemyAI_Interface::Execute_UnequipWeapon(ControlledPawn);
				return EBTNodeResult::InProgress;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}

void USEAI_BTT_UnequipWeapon::OnUnequipFinished()
{
	if (CachedBTComp)
	{
		FinishLatentTask(*CachedBTComp, EBTNodeResult::Succeeded);
	}
}
