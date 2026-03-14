#pragma once

#include "CoreMinimal.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "SEAI_EnemyCharacter_Melee.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API ASEAI_EnemyCharacter_Melee : public ASEAI_EnemyCharacter_Base
{
	GENERATED_BODY()

public:
	virtual void Attack() override;

protected:
	virtual void BeginPlay() override;

public:
	// ~ Begin USEAI_EnemyAI_Interface interface
	virtual void EquipWeapon_Implementation() override;
	virtual void UnequipWeapon_Implementation() override;
	// ~ End USEAI_EnemyAI_Interface interface

	virtual void HandleEquipNotify() override;
	virtual void HandleUnequipNotify() override;
};