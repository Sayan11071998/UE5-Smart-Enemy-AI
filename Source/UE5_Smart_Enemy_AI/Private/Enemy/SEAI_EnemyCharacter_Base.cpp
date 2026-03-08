#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/SEAI_SwordBase.h"

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

void ASEAI_EnemyCharacter_Base::EquipSword()
{
	if (EquipMontage && !bIsSwordEquipped)
	{
		float Duration = PlayAnimMontage(EquipMontage);
		if (Duration > 0.0f)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				FOnMontageEnded MontageEndedDelegate;
				MontageEndedDelegate.BindUObject(this, &ASEAI_EnemyCharacter_Base::OnEquipMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, EquipMontage);
			}
		}
	}
}

void ASEAI_EnemyCharacter_Base::UnequipSword()
{
	if (UnequipMontage && bIsSwordEquipped)
	{
		float Duration = PlayAnimMontage(UnequipMontage);
		if (Duration > 0.0f)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				FOnMontageEnded MontageEndedDelegate;
				MontageEndedDelegate.BindUObject(this, &ASEAI_EnemyCharacter_Base::OnUnequipMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, UnequipMontage);
			}
		}
	}
}

void ASEAI_EnemyCharacter_Base::Attack()
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
				MontageEndedDelegate.BindUObject(this, &ASEAI_EnemyCharacter_Base::HandleAttackMontageFinished);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, AttackMontage);
			}
		}
		else
		{
			OnAttackEnd.Broadcast();
		}
	}
}

void ASEAI_EnemyCharacter_Base::OnEquipMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnEquipSwordEnd.Broadcast();
}

void ASEAI_EnemyCharacter_Base::OnUnequipMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnUnequipSwordEnd.Broadcast();
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

void ASEAI_EnemyCharacter_Base::HandleEquipNotify()
{
	if (SwordClass && !SpawnedSword)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		
		SpawnedSword = GetWorld()->SpawnActor<ASEAI_SwordBase>(SwordClass, GetActorTransform(), SpawnParams);
		if (SpawnedSword)
		{
			FAttachmentTransformRules AttachRules(
				EAttachmentRule::SnapToTarget,	
				EAttachmentRule::SnapToTarget,	
				EAttachmentRule::SnapToTarget,
				true
			);
			
			SpawnedSword->AttachToComponent(GetMesh(), AttachRules, SwordSocket);
			bIsSwordEquipped = true;
		}
	}
}

void ASEAI_EnemyCharacter_Base::HandleUnequipNotify()
{
	if (SpawnedSword)
	{
		SpawnedSword->Destroy();
		SpawnedSword = nullptr;
		bIsSwordEquipped = false;
	}
}