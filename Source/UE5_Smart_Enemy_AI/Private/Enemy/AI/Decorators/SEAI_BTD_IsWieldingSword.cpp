#include "Enemy/AI/Decorators/SEAI_BTD_IsWieldingSword.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "AIController.h"

USEAI_BTD_IsWieldingSword::USEAI_BTD_IsWieldingSword()
{
	NodeName = TEXT("Is Wielding Sword");
}

bool USEAI_BTD_IsWieldingSword::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		ASEAI_EnemyCharacter_Base* Enemy = Cast<ASEAI_EnemyCharacter_Base>(AIController->GetPawn());
		if (Enemy)
		{
			return Enemy->IsWieldingSword();
		}
	}

	return false;
}