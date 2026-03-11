#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SEAI_BTT_MoveToIdealRange.generated.h"

struct FPathFollowingResult;

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_BTT_MoveToIdealRange : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USEAI_BTT_MoveToIdealRange();
	
protected:
	// ~ Begin UBTTaskNode interface
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// ~ End UBTTaskNode interface
	
private:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackTargetKey;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector IdealRangeKey;
	
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result, UBehaviorTreeComponent* OwnerComp);
};