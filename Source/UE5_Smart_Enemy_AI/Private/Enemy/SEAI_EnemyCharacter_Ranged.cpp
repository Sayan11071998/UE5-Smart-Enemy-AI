#include "Enemy/SEAI_EnemyCharacter_Ranged.h"
#include "Items/SEAI_WeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"

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

float ASEAI_EnemyCharacter_Ranged::SetMovementSpeed_Implementation(ESEAI_MovementSpeed Speed)
{
	float SpeedValue = 0.f;

	switch (Speed)
	{
	case ESEAI_MovementSpeed::Idle:
		SpeedValue = 0.f;
		break;
	case ESEAI_MovementSpeed::Walking:
		SpeedValue = 200.f;
		break;
	case ESEAI_MovementSpeed::Jogging:
		SpeedValue = 300.f;
		break;
	case ESEAI_MovementSpeed::Sprinting:
		SpeedValue = 500.f;
		break;
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SpeedValue;
	}

	return SpeedValue;
}

void ASEAI_EnemyCharacter_Ranged::GetIdealRange_Implementation(float& OutAttackRadius, float& OutDefendRadius) const
{
	OutAttackRadius = 600.f;
	OutDefendRadius = 600.f;
}