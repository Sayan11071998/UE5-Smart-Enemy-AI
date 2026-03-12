#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SEAI_BTT_MoveAlongPatrolRoute.generated.h"

struct FPathFollowingResult;

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_BTT_MoveAlongPatrolRoute : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USEAI_BTT_MoveAlongPatrolRoute();
	
protected:
	// ~ Begin UBTTaskNode interface
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// ~ End UBTTaskNode interface
	
private:
	// Acceptance radius matching Blueprint value of 10.0
	float AcceptanceRadius = 10.0f;

	// Callback for when AI MoveTo completes
	void OnMoveCompleted(
		FAIRequestID RequestID,
		const FPathFollowingResult& Result,
		UBehaviorTreeComponent* OwnerComp,
		class ASEAI_PatrolRoute* PatrolRoute
	);
};