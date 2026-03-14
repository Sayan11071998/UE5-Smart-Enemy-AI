#pragma once

#include "CoreMinimal.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "SEAI_EnemyCharacter_Ranged.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API ASEAI_EnemyCharacter_Ranged : public ASEAI_EnemyCharacter_Base
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// ~ Begin USEAI_EnemyAI_Interface interface
	virtual void EquipWeapon_Implementation() override;
	// ~ End USEAI_EnemyAI_Interface interface
};