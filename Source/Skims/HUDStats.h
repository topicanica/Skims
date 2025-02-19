// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDStats.generated.h"

/**
 * 
 */
UCLASS()
class SKIMS_API UHUDStats : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* BladderBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HungerBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* EnergyBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* FunBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* SocialBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HygeneBar;

	void UpdateBladderPercent(float BladderPercent);
	void UpdateHungerPercent(float HungerPercent);
	void UpdateEnergyPercent(float EnergyPercent);
	void UpdateFunPercent(float FunPercent);
	void UpdateSocialPercent(float BladderPercent);
	void UpdateHygenePercent(float BladderPercent);
};
