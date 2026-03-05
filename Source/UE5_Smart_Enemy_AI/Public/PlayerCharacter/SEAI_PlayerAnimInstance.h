#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SEAI_PlayerAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_PlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// ~ Begin UAnimInstance interface
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	// ~ End UAnimInstance interface

protected:
	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<ACharacter> Character;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Movement Data")
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category = "Movement Data")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement Data")
	bool bShouldMove;

	UPROPERTY(BlueprintReadOnly, Category = "Movement Data")
	bool bIsFalling;
};