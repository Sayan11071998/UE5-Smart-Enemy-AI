#include "Enemy/AI/Decorators/SEAI_BTD_IsWithinIdealRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

USEAI_BTD_IsWithinIdealRange::USEAI_BTD_IsWithinIdealRange()
{
	NodeName = TEXT("Is Within Ideal Range");
	
	AttackTargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(USEAI_BTD_IsWithinIdealRange, AttackTargetKey), AActor::StaticClass());
	IdealRangeKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(USEAI_BTD_IsWithinIdealRange, IdealRangeKey));
}

bool USEAI_BTD_IsWithinIdealRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const AAIController* AIC = OwnerComp.GetAIOwner();
	const APawn* ControlledPawn = AIC ? AIC->GetPawn() : nullptr;
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	
	if (!ControlledPawn || !BlackboardComp) return false;

	AActor* AttackTarget = Cast<AActor>(BlackboardComp->GetValueAsObject(AttackTargetKey.SelectedKeyName));
	if (!AttackTarget) return false;

	const float DistanceToTarget = ControlledPawn->GetDistanceTo(AttackTarget);
	const float IdealRangeValue = BlackboardComp->GetValueAsFloat(IdealRangeKey.SelectedKeyName);

	return (DistanceToTarget - ErrorMargin) <= IdealRangeValue;
}