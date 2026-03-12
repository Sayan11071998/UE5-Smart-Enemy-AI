#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SEAI_BTT_ClearFocus.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_BTT_ClearFocus : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USEAI_BTT_ClearFocus();
	
protected:
	// ~ Begin UBTTaskNode interface
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// ~ End UBTTaskNode interface
};