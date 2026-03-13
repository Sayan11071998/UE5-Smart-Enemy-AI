#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/SEAI_EnemyAI_Interface.h"
#include "SEAI_EnemyCharacter_Base.generated.h"

class ASEAI_SwordBase;
class ASEAI_PatrolRoute;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponEquipped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponUnequipped);

UCLASS()
class UE5_SMART_ENEMY_AI_API ASEAI_EnemyCharacter_Base : public ACharacter, public ISEAI_EnemyAI_Interface
{
	GENERATED_BODY()

public:
	ASEAI_EnemyCharacter_Base();

	void Attack();
	
	// USEAI_EnemyAI_Interface interface
	virtual ASEAI_PatrolRoute* GetPatrolRoute_Implementation() const override;
	virtual float SetMovementSpeed_Implementation(ESEAI_MovementSpeed Speed) override;
	virtual void GetIdealRange_Implementation(float& OutAttackRadius, float& OutDefendRadius) const override;
	virtual void EquipWeapon_Implementation() override;
	virtual void UnequipWeapon_Implementation() override;
	
	// Notify Calls
	void HandleEquipNotify();
	void HandleUnequipNotify();
	
	// Delegate Calls
	FOnWeaponEquipped OnWeaponEquipped;
	FOnWeaponUnequipped OnWeaponUnequipped;
	FOnAttackEnd OnAttackEnd;
	
	UPROPERTY(EditInstanceOnly, Category = "AI")
	TObjectPtr<ASEAI_PatrolRoute> PatrolRoute;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<ASEAI_SwordBase> SwordClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName SwordSocket = FName(TEXT("hand_r_sword_socket"));
	
	UPROPERTY(EditDefaultsOnly, Category = "AI|Combat")
	TObjectPtr<UAnimMontage> EquipMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI|Combat")
	TObjectPtr<UAnimMontage> UnequipMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TObjectPtr<UAnimMontage> AttackMontage;

	void OnEquipMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnUnequipMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void HandleAttackMontageFinished(UAnimMontage* Montage, bool bInterrupted);
	
private:
	UPROPERTY()
	TObjectPtr<ASEAI_SwordBase> SpawnedSword;
	
	bool bIsWeaponEquipped = false;
	
public:
	FORCEINLINE bool IsWeaponEquipped() const { return bIsWeaponEquipped; }
};