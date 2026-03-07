#include "Components/SEAI_PatrolRoute.h"
#include "Components/SplineComponent.h"

ASEAI_PatrolRoute::ASEAI_PatrolRoute()
{
	PrimaryActorTick.bCanEverTick = false;
	
	PatrolRoute = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolRoute"));
	RootComponent = PatrolRoute;
}

FVector ASEAI_PatrolRoute::GetSplinePointAsWorldPosition(int32 PointIndex) const
{
	return PatrolRoute->GetLocationAtSplinePoint(PointIndex, ESplineCoordinateSpace::World);
}

void ASEAI_PatrolRoute::IncrementPatrolRoute()
{
	const int32 NumPoints = PatrolRoute->GetNumberOfSplinePoints();

	PatrolIndex += Direction;

	if (PatrolIndex >= NumPoints)
	{
		Direction = -1;
		PatrolIndex = NumPoints - 1;
	}
	else if (PatrolIndex <= 0)
	{
		Direction = 1;
		PatrolIndex = 0;
	}
}