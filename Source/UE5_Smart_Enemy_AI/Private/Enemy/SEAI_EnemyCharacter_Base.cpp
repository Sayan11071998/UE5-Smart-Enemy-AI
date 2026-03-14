#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/SEAI_WeaponBase.h"

ASEAI_EnemyCharacter_Base::ASEAI_EnemyCharacter_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	
	if (GetMesh())
	{
		GetMesh()->SetCollisionObjectType(ECC_Pawn);
		GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		GetMesh()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
		GetMesh()->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);
		GetMesh()->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);
	}
	
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
}

void ASEAI_EnemyCharacter_Base::OnEquipMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnWeaponEquipped.Broadcast();
}

void ASEAI_EnemyCharacter_Base::OnUnequipMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnWeaponUnequipped.Broadcast();
}

void ASEAI_EnemyCharacter_Base::HandleAttackMontageFinished(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == AttackMontage)
	{
		OnAttackEnd.Broadcast();
	}
}

ASEAI_PatrolRoute* ASEAI_EnemyCharacter_Base::GetPatrolRoute_Implementation() const
{
	return PatrolRoute;
}

float ASEAI_EnemyCharacter_Base::SetMovementSpeed_Implementation(ESEAI_MovementSpeed Speed)
{
	float SpeedValue = 0.f;

	switch (Speed)
	{
	case ESEAI_MovementSpeed::Idle:
		SpeedValue = 0.f;
		break;
	case ESEAI_MovementSpeed::Walking:
		SpeedValue = 100.f;
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

void ASEAI_EnemyCharacter_Base::GetIdealRange_Implementation(float& OutAttackRadius, float& OutDefendRadius) const
{
	OutAttackRadius = 150.f;
	OutDefendRadius = 350.f;
}

void ASEAI_EnemyCharacter_Base::HandleEquipNotify()
{
	if (WeaponClass && !SpawnedWeapon)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		
		SpawnedWeapon = GetWorld()->SpawnActor<ASEAI_WeaponBase>(WeaponClass, GetActorTransform(), SpawnParams);
		if (SpawnedWeapon)
		{
			FAttachmentTransformRules AttachRules(
				EAttachmentRule::SnapToTarget,	
				EAttachmentRule::SnapToTarget,	
				EAttachmentRule::SnapToTarget,
				true
			);
			
			SpawnedWeapon->AttachToComponent(GetMesh(), AttachRules, WeaponSocket);
			bIsWeaponEquipped = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[%s] Failed to spawn weapon of class %s"), *GetName(), *WeaponClass->GetName());
		}
	}
	else
	{
		if (!WeaponClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("[%s] WeaponClass is null in HandleEquipNotify"), *GetName());
		}
	}
}

void ASEAI_EnemyCharacter_Base::HandleUnequipNotify()
{
	if (SpawnedWeapon)
	{
		SpawnedWeapon->Destroy();
		SpawnedWeapon = nullptr;
		bIsWeaponEquipped = false;
	}
}

void ASEAI_EnemyCharacter_Base::Attack()
{
}

void ASEAI_EnemyCharacter_Base::EquipWeapon_Implementation()
{
}

void ASEAI_EnemyCharacter_Base::UnequipWeapon_Implementation()
{
}