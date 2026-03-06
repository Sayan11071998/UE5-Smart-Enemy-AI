#include "Enemy/AI/Tasks/SEAI_BTTFocusTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

USEAI_BTTFocusTarget::USEAI_BTTFocusTarget()
{
	NodeName = TEXT("Focus Target");
}

EBTNodeResult::Type USEAI_BTTFocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		AActor* FocusTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AttackTargetKey.SelectedKeyName));
		if (FocusTarget)
		{
			AIController->SetFocus(FocusTarget);
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}