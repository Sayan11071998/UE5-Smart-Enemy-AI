#pragma once

#include "CoreMinimal.h"
#include "SEAI_AI_DataTypes.generated.h"

UENUM(BlueprintType)
enum class ESEAI_MovementSpeed : uint8
{
	Idle      UMETA(DisplayName = "Idle"),
	Walking   UMETA(DisplayName = "Walking"),
	Jogging   UMETA(DisplayName = "Jogging"),
	Sprinting UMETA(DisplayName = "Sprinting")
};

UENUM(BlueprintType)
enum class ESEAI_AIState : uint8
{
	Passive        UMETA(DisplayName = "Passive"),
	Attacking      UMETA(DisplayName = "Attacking"),
	Frozen         UMETA(DisplayName = "Frozen"),
	Investigating  UMETA(DisplayName = "Investigating"),
	Dead           UMETA(DisplayName = "Dead")
};