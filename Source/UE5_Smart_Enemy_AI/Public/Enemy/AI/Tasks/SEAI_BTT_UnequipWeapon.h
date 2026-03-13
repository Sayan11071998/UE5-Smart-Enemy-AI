#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SEAI_BTT_UnequipWeapon.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_BTT_UnequipWeapon : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USEAI_BTT_UnequipWeapon();
	
protected:
	// ~ Begin UBTTaskNode interface
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// ~ End UBTTaskNode interface

private:
	UFUNCTION()
	void OnUnequipFinished();

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> CachedBTComp;
};
