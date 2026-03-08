#include "Enemy/AI/Tasks/SEAI_BTT_MoveAlongPatrolRoute.h"
#include "AIController.h"
#include "Components/SEAI_PatrolRoute.h"
#include "Interfaces/SEAI_EnemyAI_Interface.h"
#include "Navigation/PathFollowingComponent.h"

USEAI_BTT_MoveAlongPatrolRoute::USEAI_BTT_MoveAlongPatrolRoute()
{
	NodeName = TEXT("Move Along Patrol Route");
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type USEAI_BTT_MoveAlongPatrolRoute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	ASEAI_PatrolRoute* PatrolRoute = nullptr;
	if (ControlledPawn->Implements<USEAI_EnemyAI_Interface>())
	{
		PatrolRoute = ISEAI_EnemyAI_Interface::Execute_GetPatrolRoute(ControlledPawn);
	}

	if (!IsValid(PatrolRoute))
	{
		return EBTNodeResult::Failed;
	}

	const FVector Destination = PatrolRoute->GetSplinePointAsWorldPosition(PatrolRoute->GetPatrolIndex());

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(Destination);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);

	const FPathFollowingRequestResult MoveResult = AIController->MoveTo(MoveRequest);

	if (MoveResult.Code == EPathFollowingRequestResult::RequestSuccessful)
	{
		AIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(
			this, &USEAI_BTT_MoveAlongPatrolRoute::OnMoveCompleted, &OwnerComp, PatrolRoute
		);

		return EBTNodeResult::InProgress;
	}
	else if (MoveResult.Code == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		PatrolRoute->IncrementPatrolRoute();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type USEAI_BTT_MoveAlongPatrolRoute::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		AIController->StopMovement();
	}

	return EBTNodeResult::Aborted;
}

void USEAI_BTT_MoveAlongPatrolRoute::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result,
	UBehaviorTreeComponent* OwnerComp, ASEAI_PatrolRoute* PatrolRoute)
{
	if (!OwnerComp) return;

	AAIController* AIController = OwnerComp->GetAIOwner();
	if (AIController && AIController->GetPathFollowingComponent())
	{
		AIController->GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);
	}

	if (Result.IsSuccess())
	{
		if (IsValid(PatrolRoute))
		{
			PatrolRoute->IncrementPatrolRoute();
		}
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		FinishLatentTask(*OwnerComp, EBTNodeResult::Failed);
	}
}