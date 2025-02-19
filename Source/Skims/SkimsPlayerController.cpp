// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkimsPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "SkimsCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "HUDStats.h"
#include "InteractableBaseActor.h"

ASkimsPlayerController::ASkimsPlayerController(){

}
void ASkimsPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (BP_HUDStats != nullptr)
	{
		HUDStats = CreateWidget<UHUDStats>(this, BP_HUDStats);
		HUDStats->AddToViewport();

		HUDClock = CreateWidget<UUserWidget>(this, BP_HUDClock);
		HUDClock->AddToViewport();
 	}
}

void ASkimsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ASkimsPlayerController::UpdateBladderPercent(float BladderPercent)
{
	if (HUDStats != nullptr)
	{
		HUDStats->UpdateBladderPercent(BladderPercent);
	}
}

void ASkimsPlayerController::UpdateHungerPercent(float HungerPercent)
{
	if (HUDStats != nullptr)
	{
		HUDStats->UpdateHungerPercent(HungerPercent);
	}
}

void ASkimsPlayerController::UpdateEnergyPercent(float EnergyPercent)
{
	if (HUDStats != nullptr)
	{
		HUDStats->UpdateEnergyPercent(EnergyPercent);
	}
}

void ASkimsPlayerController::UpdateFunPercent(float FunPercent)
{
	if (HUDStats != nullptr)
	{
		HUDStats->UpdateFunPercent(FunPercent);
	}
}

void ASkimsPlayerController::UpdateSocialPercent(float SocialPercent)
{
	if (HUDStats != nullptr)
	{
		HUDStats->UpdateSocialPercent(SocialPercent);
	}
}

void ASkimsPlayerController::UpdateHygenePercent(float HygenePercent)
{
	if (HUDStats != nullptr)
	{
		HUDStats->UpdateHygenePercent(HygenePercent);
	}
}
