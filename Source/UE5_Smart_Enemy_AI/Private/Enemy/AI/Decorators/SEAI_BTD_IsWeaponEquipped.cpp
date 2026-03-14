#include "Enemy/AI/Decorators/SEAI_BTD_IsWeaponEquipped.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "AIController.h"

USEAI_BTD_IsWeaponEquipped::USEAI_BTD_IsWeaponEquipped()
{
	NodeName = TEXT("Is Weapon Equipped");
}

bool USEAI_BTD_IsWeaponEquipped::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ASEAI_EnemyCharacter_Base* Enemy = Cast<ASEAI_EnemyCharacter_Base>(AIController->GetPawn()))
		{
			return Enemy->IsWeaponEquipped();
		}
	}
	
	return false;
}
