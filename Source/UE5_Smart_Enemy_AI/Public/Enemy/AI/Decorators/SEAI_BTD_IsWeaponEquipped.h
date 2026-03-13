#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SEAI_BTD_IsWeaponEquipped.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_BTD_IsWeaponEquipped : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	USEAI_BTD_IsWeaponEquipped();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
