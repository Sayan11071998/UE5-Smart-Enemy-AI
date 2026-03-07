#include "Components/SEAI_PatrolRoute.h"
#include "Components/SplineComponent.h"

ASEAI_PatrolRoute::ASEAI_PatrolRoute()
{
	PrimaryActorTick.bCanEverTick = false;
	
	PatrolRoute = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolRoute"));
	RootComponent = PatrolRoute;
	
	PatrolIndex = 0;
	Direction = 1;
}

FVector ASEAI_PatrolRoute::GetSplinePointAsWorldPosition(int32 PointIndex) const
{
	if (!PatrolRoute)
	{
		return FVector::ZeroVector;
	}
	
	return PatrolRoute->GetLocationAtSplinePoint(PointIndex, ESplineCoordinateSpace::World);
}

void ASEAI_PatrolRoute::IncrementPatrolRoute()
{
	if (!PatrolRoute) return;
	
	PatrolIndex = PatrolIndex + Direction;
	const int32 NumPoints = PatrolRoute->GetNumberOfSplinePoints();
	
	if (PatrolIndex == NumPoints - 1)
	{
		Direction = -1;
	}
	else if (PatrolIndex == 0)
	{
		Direction = 1;
	}
}