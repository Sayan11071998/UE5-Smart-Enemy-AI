#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SEAI_AN_SheathSword.generated.h"

/**
 * Custom AnimNotify to trigger SheathSword logic in C++
 */
UCLASS()
class UE5_SMART_ENEMY_AI_API USEAI_AN_SheathSword : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
