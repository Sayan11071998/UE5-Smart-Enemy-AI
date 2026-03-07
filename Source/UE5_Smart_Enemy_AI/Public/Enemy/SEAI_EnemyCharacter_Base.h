#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/SEAI_EnemyAI_Interface.h"
#include "SEAI_EnemyCharacter_Base.generated.h"

class ASEAI_SwordBase;
class ASEAI_PatrolRoute;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class UE5_SMART_ENEMY_AI_API ASEAI_EnemyCharacter_Base : public ACharacter, public ISEAI_EnemyAI_Interface
{
	GENERATED_BODY()

public:
	ASEAI_EnemyCharacter_Base();
	
	void WieldSword();
	void Attack();
	
	// USEAI_EnemyAI_Interface interface
	virtual ASEAI_PatrolRoute* GetPatrolRoute_Implementation() const override;
	
	FOnAttackEnd OnAttackEnd;
	
	UPROPERTY(EditInstanceOnly, Category = "AI")
	TObjectPtr<ASEAI_PatrolRoute> PatrolRoute;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<ASEAI_SwordBase> SwordClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName SwordSocket = FName(TEXT("hand_r_sword_socket"));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TObjectPtr<UAnimMontage> AttackMontage;

	void HandleAttackMontageFinished(UAnimMontage* Montage, bool bInterrupted);
	
private:
	UPROPERTY()
	TObjectPtr<ASEAI_SwordBase> SpawnedSword;
	
	bool bIsWieldingSword = false;
	
public:
	FORCEINLINE bool IsWieldingSword() const { return bIsWieldingSword; }
};