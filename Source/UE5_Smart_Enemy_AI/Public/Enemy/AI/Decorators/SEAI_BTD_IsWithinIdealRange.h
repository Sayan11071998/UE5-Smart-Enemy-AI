#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SEAI_BTD_IsWithinIdealRange.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_BTD_IsWithinIdealRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	USEAI_BTD_IsWithinIdealRange();
	
protected:
	// ~ Begin UBTDecorator interface
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	// ~ End UBTDecorator interface
	
private:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackTargetKey;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector IdealRangeKey;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float ErrorMargin = 0.f;
};