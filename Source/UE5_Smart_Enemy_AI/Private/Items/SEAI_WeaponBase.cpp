#include "Items/SEAI_WeaponBase.h"

ASEAI_WeaponBase::ASEAI_WeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}