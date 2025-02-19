// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkimsCharacter.h"
#include "SkimsPlayerController.h"
#include "StatsComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ASkimsCharacter::ASkimsCharacter()
{
	// Set size for collision capsule
	float HalfHeight = 178.73f / 2.0f; // Desired height in centimeters
	float Radius = HalfHeight / 2.0f;
	GetCapsuleComponent()->InitCapsuleSize(Radius, HalfHeight);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// Create a stats component
	StatsComponent = CreateOptionalDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
}
void ASkimsCharacter::UpdateStatsHourly()
{
	if (StatsComponent)
	{
		StatsComponent->DepleteStats();
		ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
		if (PlayerController != nullptr)
		{
			PlayerController->UpdateBladderPercent(StatsComponent->GetBladderPercent());
			PlayerController->UpdateHungerPercent(StatsComponent->GetHungerPercent());
			PlayerController->UpdateEnergyPercent(StatsComponent->GetEnergyPercent());
			PlayerController->UpdateFunPercent(StatsComponent->GetFunPercent());
			PlayerController->UpdateSocialPercent(StatsComponent->GetSocialPercent());
			PlayerController->UpdateHygenePercent(StatsComponent->GetHygenePercent());
		}
	}
}

void ASkimsCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (this && !this->IsPendingKill())
	{
		// Get reference to the world clock (assuming it's spawned in the level)
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldClock::StaticClass(), FoundActors);
		if (FoundActors.Num() > 0)
		{
			WorldClock = Cast<AWorldClock>(FoundActors[0]);
			if (WorldClock)
			{
				// Listen for the hourly timer trigger event from the world clock

				WorldClock->OnHourChanged.AddDynamic(this, &ASkimsCharacter::UpdateStatsHourly);
			}
		}
	}
}

void ASkimsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASkimsCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASkimsCharacter::Look);
	}
}

void ASkimsCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (!Controller->IsMoveInputIgnored())
    {
        if (Controller != nullptr)
        {
            // find out which way is forward
            const FRotator Rotation = Controller->GetControlRotation();
            const FRotator YawRotation(0, Rotation.Yaw, 0);

            // get forward vector
            const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

            // get right vector 
            const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

            // add movement 
            AddMovementInput(ForwardDirection, MovementVector.Y);
            AddMovementInput(RightDirection, MovementVector.X);
        }
    }
}

void ASkimsCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X * Sensitivity);
		AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
	}
}

void ASkimsCharacter::EnableCharacterMovement(bool bShouldMove)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		// Toggle input for the player controller
		if (bShouldMove)
		{
			PlayerController->ResetIgnoreMoveInput();
		}
		else
		{
			PlayerController->SetIgnoreMoveInput(true);
		}
	}
}

void ASkimsCharacter::OnStatDepleted_Implementation()
{
	if (DeathMontage && GetMesh() && GetMesh()->GetAnimInstance())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage);
		UE_LOG(LogTemp, Warning, TEXT("Failed to load animation montage!"));
	}
}

void ASkimsCharacter::ModifyBladder(float Amount)
{
	if (StatsComponent)
	{
		StatsComponent->ModifyBladder(Amount);
		ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
		if (PlayerController != nullptr)
		{
			PlayerController->UpdateBladderPercent(StatsComponent->GetBladderPercent());
		}
	}
}

void ASkimsCharacter::ModifyHunger(float Amount)
{
	if (StatsComponent)
	{
		StatsComponent->ModifyHunger(Amount);
		ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
		if (PlayerController != nullptr)
		{
			PlayerController->UpdateHungerPercent(StatsComponent->GetHungerPercent());
		}
	}
}

void ASkimsCharacter::ModifyEnergy(float Amount)
{
	if (StatsComponent)
	{
		StatsComponent->ModifyEnergy(Amount);
		ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
		if (PlayerController != nullptr)
		{
			PlayerController->UpdateEnergyPercent(StatsComponent->GetEnergyPercent());
		}
	}
}

void ASkimsCharacter::ModifyFun(float Amount)
{
	if (StatsComponent)
	{
		StatsComponent->ModifyFun(Amount);
		ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
		if (PlayerController != nullptr)
		{
			PlayerController->UpdateFunPercent(StatsComponent->GetFunPercent());
		}
	}
}

void ASkimsCharacter::ModifySocial(float Amount)
{
	if (StatsComponent)
	{
		StatsComponent->ModifySocial(Amount);
		ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
		if (PlayerController != nullptr)
		{
			PlayerController->UpdateSocialPercent(StatsComponent->GetSocialPercent());
		}
	}
}

void ASkimsCharacter::ModifyHygene(float Amount)
{
	if (StatsComponent)
	{
		StatsComponent->ModifyHygene(Amount);
		ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
		if (PlayerController != nullptr)
		{
			PlayerController->UpdateHygenePercent(StatsComponent->GetHygenePercent());
		}
	}
}
