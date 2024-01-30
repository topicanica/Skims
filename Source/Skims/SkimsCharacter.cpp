// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkimsCharacter.h"
#include "StatsComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "SkimsPlayerController.h"

ASkimsCharacter::ASkimsCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	StatsComponent = CreateOptionalDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
}

void ASkimsCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ASkimsCharacter::OnBladderDeterioration_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateBladderPercent(StatsComponent->GetBladderPercent());
	}
}

void ASkimsCharacter::OnBladderImprovement_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateBladderPercent(StatsComponent->GetBladderPercent());
	}
}

void ASkimsCharacter::OnHungerDeterioration_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateHungerPercent(StatsComponent->GetHungerPercent());
	}
}

void ASkimsCharacter::OnHungerImprovement_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateHungerPercent(StatsComponent->GetHungerPercent());
	}
}

void ASkimsCharacter::OnEnergyDeterioration_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateEnergyPercent(StatsComponent->GetEnergyPercent());
	}
}

void ASkimsCharacter::OnEnergyImprovement_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateEnergyPercent(StatsComponent->GetEnergyPercent());
	}
}

void ASkimsCharacter::OnFunDeterioration_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateFunPercent(StatsComponent->GetFunPercent());
	}
}

void ASkimsCharacter::OnFunImprovement_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateFunPercent(StatsComponent->GetFunPercent());
	}
}

void ASkimsCharacter::OnSocialDeterioration_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateSocialPercent(StatsComponent->GetSocialPercent());
	}
}

void ASkimsCharacter::OnSocialImprovement_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateSocialPercent(StatsComponent->GetSocialPercent());
	}
}

void ASkimsCharacter::OnHygeneDeterioration_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateHygenePercent(StatsComponent->GetHygenePercent());
	}
}

void ASkimsCharacter::OnHygeneImprovement_Implementation()
{
	ASkimsPlayerController* PlayerController = Cast<ASkimsPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateHygenePercent(StatsComponent->GetHygenePercent());
	}
}


