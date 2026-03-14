#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SEAI_AN_EquipWeapon.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_AN_EquipWeapon : public UAnimNotify
{
	GENERATED_BODY()

public:
	// ~ Begin UAnimNotify interface
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	// ~ End UAnimNotify interface
};
