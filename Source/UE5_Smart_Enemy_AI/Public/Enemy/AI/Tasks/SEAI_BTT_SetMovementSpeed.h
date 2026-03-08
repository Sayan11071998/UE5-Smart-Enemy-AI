#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy/AI/Enums/SEAI_AI_DataTypes.h"
#include "SEAI_BTT_SetMovementSpeed.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_BTT_SetMovementSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USEAI_BTT_SetMovementSpeed();
	
protected:
	// ~ Begin UBTTaskNode interface
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// ~ End UBTTaskNode interface
	
private:
	UPROPERTY(EditAnywhere, Category = "AI")
	ESEAI_MovementSpeed MovementSpeed;
};