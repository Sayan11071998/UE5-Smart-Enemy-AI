#include "Items/SEAI_SwordBase.h"

ASEAI_SwordBase::ASEAI_SwordBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordMesh"));
	RootComponent = SwordMesh;
}