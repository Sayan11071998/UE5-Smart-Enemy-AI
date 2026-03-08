#include "Enemy/AI/Decorators/SEAI_BTD_HasPatrolRoute.h"
#include "Interfaces/SEAI_EnemyAI_Interface.h"
#include "AIController.h"

USEAI_BTD_HasPatrolRoute::USEAI_BTD_HasPatrolRoute()
{
	NodeName = TEXT("Has Patrol Route");
}

bool USEAI_BTD_HasPatrolRoute::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController && AIController->GetPawn())
	{
		APawn* ControlledPawn = AIController->GetPawn();
		if (ControlledPawn->Implements<USEAI_EnemyAI_Interface>())
		{
			return ISEAI_EnemyAI_Interface::Execute_GetPatrolRoute(ControlledPawn) != nullptr;
		}
	}
	
	return false;
}