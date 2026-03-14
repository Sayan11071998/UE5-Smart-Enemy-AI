#include "Enemy/SEAI_EnemyCharacter_Ranged.h"
#include "Items/SEAI_WeaponBase.h"

void ASEAI_EnemyCharacter_Ranged::BeginPlay()
{
	Super::BeginPlay();
	ISEAI_EnemyAI_Interface::Execute_EquipWeapon(this);
}

void ASEAI_EnemyCharacter_Ranged::EquipWeapon_Implementation()
{
	if (WeaponClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		
		SpawnedWeapon = GetWorld()->SpawnActor<ASEAI_WeaponBase>(WeaponClass, GetActorTransform(), SpawnParams);
		if (SpawnedWeapon)
		{
			FAttachmentTransformRules AttachRules(
				EAttachmentRule::SnapToTarget,
				EAttachmentRule::SnapToTarget,
				EAttachmentRule::SnapToTarget,
				true
			);
			
			SpawnedWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("Hand_r_rifle_socket"));
			bIsWeaponEquipped = true;
			OnWeaponEquipped.Broadcast();
		}
	}
}