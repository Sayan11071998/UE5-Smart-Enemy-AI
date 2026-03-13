#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEAI_WeaponBase.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API ASEAI_WeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASEAI_WeaponBase();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
};
