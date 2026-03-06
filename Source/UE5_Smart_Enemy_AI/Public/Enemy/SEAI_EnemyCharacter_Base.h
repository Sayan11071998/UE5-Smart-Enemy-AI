#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SEAI_EnemyCharacter_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class UE5_SMART_ENEMY_AI_API ASEAI_EnemyCharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	ASEAI_EnemyCharacter_Base();
	
	void Attack();
	
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnAttackEnd OnAttackEnd;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TObjectPtr<UAnimMontage> AttackMontage;

	void HandleAttackMontageFinished(UAnimMontage* Montage, bool bInterrupted);
};