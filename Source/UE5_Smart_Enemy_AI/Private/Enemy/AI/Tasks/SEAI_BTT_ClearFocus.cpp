#include "Enemy/AI/Tasks/SEAI_BTT_ClearFocus.h"

#include "AIController.h"

USEAI_BTT_ClearFocus::USEAI_BTT_ClearFocus()
{
	NodeName = "Clear Focus";
}

EBTNodeResult::Type USEAI_BTT_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		AIController->ClearFocus(EAIFocusPriority::Gameplay);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}