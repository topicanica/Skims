// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDStats.h"
#include "Components/ProgressBar.h"

void UHUDStats::UpdateBladderPercent(float BladderPercent)
{
	BladderBar->SetPercent(BladderPercent);
}

void UHUDStats::UpdateHungerPercent(float HungerPercent)
{
	HungerBar->SetPercent(HungerPercent);
}

void UHUDStats::UpdateEnergyPercent(float EnergyPercent)
{
	EnergyBar->SetPercent(EnergyPercent);
}

void UHUDStats::UpdateFunPercent(float FunPercent)
{
	FunBar->SetPercent(FunPercent);
}

void UHUDStats::UpdateSocialPercent(float SocialPercent)
{
	SocialBar->SetPercent(SocialPercent);
}

void UHUDStats::UpdateHygenePercent(float HygenePercent)
{
	HygeneBar->SetPercent(HygenePercent);
}

