#include "Enemy/AI/Decorators/SEAI_BTD_IsEquippedSword.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "AIController.h"

USEAI_BTD_IsEquippedSword::USEAI_BTD_IsEquippedSword()
{
	NodeName = TEXT("Is Equipped Sword");
}

bool USEAI_BTD_IsEquippedSword::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ASEAI_EnemyCharacter_Base* Enemy = Cast<ASEAI_EnemyCharacter_Base>(AIController->GetPawn()))
		{
			return Enemy->IsSwordEquipped();
		}
	}
	
	return false;
}