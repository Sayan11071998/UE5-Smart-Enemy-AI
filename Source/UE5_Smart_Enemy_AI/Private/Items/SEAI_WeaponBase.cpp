#include "Items/SEAI_WeaponBase.h"

ASEAI_WeaponBase::ASEAI_WeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
}
