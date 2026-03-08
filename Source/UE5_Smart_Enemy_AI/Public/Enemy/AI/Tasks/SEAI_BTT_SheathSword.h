#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SEAI_BTT_SheathSword.generated.h"

/**
 * Latent BT Task to trigger sword sheathing and wait for animation to finish.
 */
UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_BTT_SheathSword : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USEAI_BTT_SheathSword();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UFUNCTION()
	void OnSheathFinished();

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> CachedBTComp;
};
