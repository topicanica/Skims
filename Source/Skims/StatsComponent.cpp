// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "StatsInterface.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Default Values
	Bladder = Hunger = Energy = Fun = Social = Hygene = 50.0f;
	MaxBladder = MaxHunger = MaxEnergy = MaxFun = MaxSocial = MaxHygene = 100.0f;
}

// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatsComponent::DepleteStats()
{
	// Decrease health and stamina by some amount (e.g., 10 units every hour)
	Bladder -= 3.0f;
	Hunger -= 3.0f;
	Energy -= 3.0f;
	Fun -= 3.0f;
	Social -= 3.0f;
	Hygene -= 3.0f;

	// Clamp values to ensure they stay within valid range
	Bladder = FMath::Clamp(Bladder, 0.0f, MaxBladder);
	Hunger = FMath::Clamp(Hunger, 0.0f, MaxHunger);
	Energy = FMath::Clamp(Energy, 0.0f, MaxEnergy);
	Fun = FMath::Clamp(Fun, 0.0f, MaxFun);
	Social = FMath::Clamp(Social, 0.0f, MaxSocial);
	Hygene = FMath::Clamp(Hygene, 0.0f, MaxHygene);

	if (Bladder == 0.0f || Hunger == 0.0f || Energy == 0.0f)
	{
		IStatsInterface::Execute_OnStatDepleted(GetOwner());
	}
}

void UStatsComponent::SetStats(float NewBladder, float NewHunger, float NewEnergy, float NewFun, float NewSocial, float NewHygene)
{
	Bladder = NewBladder;
	Hunger = NewHunger;
	Energy = NewEnergy;
	Fun = NewHygene;
	Social = NewSocial;
	Hygene = NewHygene;
}
void UStatsComponent::ModifyBladder(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		if (Bladder == 0.0f)
		{
			IStatsInterface::Execute_OnStatDepleted(GetOwner());
		}
	}
	Bladder = FMath::Clamp(Bladder + Amount, 0.0f, MaxBladder);
}

void UStatsComponent::ModifyHunger(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		if (Hunger == 0.0f)
		{
			IStatsInterface::Execute_OnStatDepleted(GetOwner());
		}
	}
	Hunger = FMath::Clamp(Hunger + Amount, 0.0f, MaxHunger);

}

void UStatsComponent::ModifyEnergy(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		if (Energy == 0.0f)
		{
			IStatsInterface::Execute_OnStatDepleted(GetOwner());
		}
	} 
	Energy = FMath::Clamp(Energy + Amount, 0.0f, MaxEnergy);
}

void UStatsComponent::ModifyFun(float Amount)
{
	Fun = FMath::Clamp(Fun + Amount, 0.0f, MaxFun);
}

void UStatsComponent::ModifySocial(float Amount)
{

	Social = FMath::Clamp(Social + Amount, 0.0f, MaxSocial);
}

void UStatsComponent::ModifyHygene(float Amount)
{
	/*if (GetOwner()->Implements<UStatsInterface>())
	{
		if (Hygene == 0.0f)
		{
			IStatsInterface::Execute_OnStatDepleted(GetOwner());
		}
	}*/
	Hygene = FMath::Clamp(Hygene + Amount, 0.0f, MaxHygene);
}

