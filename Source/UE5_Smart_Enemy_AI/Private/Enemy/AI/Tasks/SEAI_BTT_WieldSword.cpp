#include "Enemy/AI/Tasks/SEAI_BTT_WieldSword.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "AIController.h"

USEAI_BTT_WieldSword::USEAI_BTT_WieldSword()
{
	NodeName = TEXT("Wield Sword");
}

EBTNodeResult::Type USEAI_BTT_WieldSword::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		ASEAI_EnemyCharacter_Base* Enemy = Cast<ASEAI_EnemyCharacter_Base>(AIController->GetPawn());
		if (Enemy)
		{
			Enemy->WieldSword();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}