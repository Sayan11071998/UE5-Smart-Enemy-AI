#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SEAI_PlayerCharacter.generated.h"

struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class UE5_SMART_ENEMY_AI_API ASEAI_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASEAI_PlayerCharacter();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Input Callbacks
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void HandleToggleAIState();
	void HandleMakeNoise();
	void HandleDamageAction();
	
private:
	// Private Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	
	// Input Assets
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ToggleAIStateAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MakeNoiseAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DamageAction;
	
	// Effects
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UParticleSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<USoundBase> ExplosionSound;
	
	bool bIsAIStateAttacking = false;

public:
	FORCEINLINE TObjectPtr<USpringArmComponent> GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE TObjectPtr<UCameraComponent> GetFollowCamera() const { return FollowCamera; }
};