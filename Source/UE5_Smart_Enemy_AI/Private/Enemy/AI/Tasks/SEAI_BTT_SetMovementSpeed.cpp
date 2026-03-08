#include "Enemy/AI/Tasks/SEAI_BTT_SetMovementSpeed.h"
#include "Interfaces/SEAI_EnemyAI_Interface.h"
#include "AIController.h"

USEAI_BTT_SetMovementSpeed::USEAI_BTT_SetMovementSpeed()
{
	NodeName = TEXT("Set Movement Speed");
}

EBTNodeResult::Type USEAI_BTT_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController && AIController->GetPawn())
	{
		APawn* ControlledPawn = AIController->GetPawn();
		if (ControlledPawn->Implements<USEAI_EnemyAI_Interface>())
		{
			ISEAI_EnemyAI_Interface::Execute_SetMovementSpeed(ControlledPawn, MovementSpeed);
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}