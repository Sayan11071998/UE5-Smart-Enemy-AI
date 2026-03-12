#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SEAI_BTT_UnequipSword.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_BTT_UnequipSword : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USEAI_BTT_UnequipSword();
	
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