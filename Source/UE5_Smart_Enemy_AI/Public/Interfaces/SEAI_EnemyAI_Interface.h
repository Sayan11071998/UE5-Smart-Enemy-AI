#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enemy/AI/Enums/SEAI_AI_DataTypes.h"
#include "SEAI_EnemyAI_Interface.generated.h"

class ASEAI_PatrolRoute;

UINTERFACE(MinimalAPI)
class USEAI_EnemyAI_Interface : public UInterface
{
	GENERATED_BODY()
};

class UE5_SMART_ENEMY_AI_API ISEAI_EnemyAI_Interface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI")
	ASEAI_PatrolRoute* GetPatrolRoute() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AI")
	float SetMovementSpeed(ESEAI_MovementSpeed Speed);
};