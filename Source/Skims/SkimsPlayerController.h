// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "SkimsPlayerController.generated.h"

UCLASS()
class ASkimsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASkimsPlayerController();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDStats> BP_HUDStats;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> BP_HUDClock;

	void UpdateBladderPercent(float BladderPercent);
	void UpdateHungerPercent(float HungerPercent);
	void UpdateEnergyPercent(float EnergyPercent);
	void UpdateFunPercent(float FunPercent);
	void UpdateSocialPercent(float SocialPercent);
	void UpdateHygenePercent(float HygenePercent);
	
protected:
	virtual void BeginPlay();

	virtual void SetupInputComponent() override;

private:
	class UHUDStats* HUDStats;
	class UUserWidget* HUDClock;
};


