#include "PlayerCharacter/SEAI_PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "KismetAnimationLibrary.h"

void USEAI_PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void USEAI_PlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character || !MovementComponent)
	{
		Character = Cast<ACharacter>(TryGetPawnOwner());
		if (Character)
		{
			MovementComponent = Character->GetCharacterMovement();
		}
	}

	if (Character && MovementComponent)
	{
		Velocity = MovementComponent->Velocity;
		bIsFalling = MovementComponent->IsFalling();
		GroundSpeed = Velocity.Size2D();

		const FVector Acceleration = MovementComponent->GetCurrentAcceleration();
		bShouldMove = (GroundSpeed > 3.f) && (!Acceleration.IsNearlyZero());

		Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Character->GetActorRotation());
		
		if (AAIController* AIController = Character->GetController<AAIController>())
		{
			bIsFocusingTarget = IsValid(AIController->GetFocusActor());
		}
		else
		{
			bIsFocusingTarget = false;
		}
	}
}