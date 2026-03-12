#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SEAI_PatrolRoute.generated.h"

class USplineComponent;

UCLASS()
class UE5_SMART_ENEMY_AI_API ASEAI_PatrolRoute : public AActor
{
	GENERATED_BODY()
	
public:	
	ASEAI_PatrolRoute();
	
	FVector GetSplinePointAsWorldPosition(int32 PointIndex) const;
	void IncrementPatrolRoute();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USplineComponent> PatrolRoute;
	
	int32 PatrolIndex;
	int32 Direction;
	
public:
	FORCEINLINE int32 GetPatrolIndex() const { return PatrolIndex; }
};