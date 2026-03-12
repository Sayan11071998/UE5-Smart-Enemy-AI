#include "Enemy/AI/Tasks/SEAI_BTT_MoveToIdealRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

USEAI_BTT_MoveToIdealRange::USEAI_BTT_MoveToIdealRange()
{
	NodeName = TEXT("Move To Ideal Range");
	bNotifyTaskFinished = true;
	
	AttackTargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(USEAI_BTT_MoveToIdealRange, AttackTargetKey), AActor::StaticClass());
	IdealRangeKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(USEAI_BTT_MoveToIdealRange, IdealRangeKey));
}

EBTNodeResult::Type USEAI_BTT_MoveToIdealRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	
	if (!AIC || !BBComp) return EBTNodeResult::Failed;
	
	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(AttackTargetKey.SelectedKeyName));
	const float AcceptanceRadius = BBComp->GetValueAsFloat(IdealRangeKey.SelectedKeyName);
	
	if (!TargetActor) return EBTNodeResult::Failed;
	
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(TargetActor);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
	MoveRequest.SetReachTestIncludesAgentRadius(true);
	
	const FPathFollowingRequestResult MoveResult = AIC->MoveTo(MoveRequest);
	if (MoveResult.Code == EPathFollowingRequestResult::RequestSuccessful)
	{
		AIC->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &USEAI_BTT_MoveToIdealRange::OnMoveCompleted, &OwnerComp);
		return EBTNodeResult::InProgress;
	}
	else if (MoveResult.Code == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type USEAI_BTT_MoveToIdealRange::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIC = OwnerComp.GetAIOwner())
	{
		AIC->StopMovement();
	}
	return EBTNodeResult::Aborted;
}

void USEAI_BTT_MoveToIdealRange::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result,
	UBehaviorTreeComponent* OwnerComp)
{
	if (OwnerComp)
	{
		if (AAIController* AIC = OwnerComp->GetAIOwner())
		{
			if (AIC->GetPathFollowingComponent())
			{
				AIC->GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);
			}
		}
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
}