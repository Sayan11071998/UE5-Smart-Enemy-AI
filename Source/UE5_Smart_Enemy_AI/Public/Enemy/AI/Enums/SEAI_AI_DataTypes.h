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