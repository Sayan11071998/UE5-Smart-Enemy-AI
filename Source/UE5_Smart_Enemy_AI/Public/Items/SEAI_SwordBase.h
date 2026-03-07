#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEAI_SwordBase.generated.h"

UCLASS()
class UE5_SMART_ENEMY_AI_API ASEAI_SwordBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASEAI_SwordBase();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UStaticMeshComponent> SwordMesh;
};