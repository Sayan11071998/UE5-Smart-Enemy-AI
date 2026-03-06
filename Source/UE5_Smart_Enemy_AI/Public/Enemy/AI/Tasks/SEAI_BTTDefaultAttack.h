#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SEAI_BTTDefaultAttack.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_BTTDefaultAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USEAI_BTTDefaultAttack();
	
protected:
	// ~ Begin UBTTaskNode interface
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// ~ End UBTTaskNode interface
	
	UFUNCTION()
	void HandleAttackFinished();
	
private:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> CachedBTComp;
};