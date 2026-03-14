#include "Enemy/SEAI_EnemyCharacter_Melee.h"
#include "Animation/AnimInstance.h"
#include "Items/SEAI_WeaponBase.h"

void ASEAI_EnemyCharacter_Melee::BeginPlay()
{
	Super::BeginPlay();
}

void ASEAI_EnemyCharacter_Melee::Attack()
{
	if (AttackMontage)
	{
		float Duration = PlayAnimMontage(AttackMontage);
		
		if (Duration > 0.0f)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				FOnMontageEnded MontageEndedDelegate;
				MontageEndedDelegate.BindUObject(this, &ASEAI_EnemyCharacter_Melee::HandleAttackMontageFinished);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, AttackMontage);
			}
		}
		else
		{
			OnAttackEnd.Broadcast();
		}
	}
}

void ASEAI_EnemyCharacter_Melee::EquipWeapon_Implementation()
{
	if (EquipMontage && !bIsWeaponEquipped)
	{
		float Duration = PlayAnimMontage(EquipMontage);
		if (Duration > 0.0f)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				FOnMontageEnded MontageEndedDelegate;
				MontageEndedDelegate.BindUObject(this, &ASEAI_EnemyCharacter_Melee::OnEquipMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, EquipMontage);
				return;
			}
		}
	}
	
	OnWeaponEquipped.Broadcast();
}

void ASEAI_EnemyCharacter_Melee::UnequipWeapon_Implementation()
{
	if (UnequipMontage && bIsWeaponEquipped)
	{
		float Duration = PlayAnimMontage(UnequipMontage);
		if (Duration > 0.0f)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				FOnMontageEnded MontageEndedDelegate;
				MontageEndedDelegate.BindUObject(this, &ASEAI_EnemyCharacter_Melee::OnUnequipMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, UnequipMontage);
				return;
			}
		}
	}
	
	OnWeaponUnequipped.Broadcast();
}

void ASEAI_EnemyCharacter_Melee::HandleEquipNotify()
{
	if (WeaponClass && !SpawnedWeapon)
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
			
			SpawnedWeapon->AttachToComponent(GetMesh(), AttachRules, TEXT("Hand_r_sword_socket"));
			bIsWeaponEquipped = true;
		}
	}
}

void ASEAI_EnemyCharacter_Melee::HandleUnequipNotify()
{
	if (SpawnedWeapon)
	{
		SpawnedWeapon->Destroy();
		SpawnedWeapon = nullptr;
		bIsWeaponEquipped = false;
	}
}