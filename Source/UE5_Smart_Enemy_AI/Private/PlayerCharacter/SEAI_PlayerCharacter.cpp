#include "PlayerCharacter/SEAI_PlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/SEAI_EnemyCharacter_Base.h"
#include "Enemy/AI/SEAI_EnemyAIController_Base.h"

ASEAI_PlayerCharacter::ASEAI_PlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;	
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ASEAI_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASEAI_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASEAI_PlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASEAI_PlayerCharacter::Look);
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	
		EnhancedInputComponent->BindAction(ToggleAIStateAction, ETriggerEvent::Started, this, &ASEAI_PlayerCharacter::HandleToggleAIState);
	}
}

void ASEAI_PlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Moved = Value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator YawRot(0, Controller->GetControlRotation().Yaw, 0);
		AddMovementInput(FRotationMatrix(YawRot).GetUnitAxis(EAxis::X), Moved.Y);
		AddMovementInput(FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y), Moved.X);
	}
}

void ASEAI_PlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Looked = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(Looked.X);
		AddControllerPitchInput(Looked.Y);
	}
}

void ASEAI_PlayerCharacter::HandleToggleAIState()
{
	AActor* EnemyActor = UGameplayStatics::GetActorOfClass(this, ASEAI_EnemyCharacter_Base::StaticClass());
    
	if (EnemyActor)
	{
		APawn* EnemyPawn = Cast<APawn>(EnemyActor);
		if (EnemyPawn)
		{
			ASEAI_EnemyAIController_Base* AIC = Cast<ASEAI_EnemyAIController_Base>(EnemyPawn->GetController());
			if (AIC)
			{
				bIsAIStateAttacking = !bIsAIStateAttacking;
				if (bIsAIStateAttacking)
				{
					AIC->SetStateAsAttacking(this);
				}
				else
				{
					AIC->SetStateAsPassive();
				}
			}
		}
	}
}