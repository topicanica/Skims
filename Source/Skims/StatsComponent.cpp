// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "StatsInterface.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Default Values
	Bladder = Hunger = Energy = Fun = Social = Hygene = 50.0f;
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UStatsComponent::LoseBladder(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnBladderDeterioration(GetOwner());
	}
	Bladder -= Amount;
}
void UStatsComponent::AddBladder(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnBladderImprovement(GetOwner());
	}
	Bladder += Amount;
}

void UStatsComponent::LoseHunger(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnHungerDeterioration(GetOwner());
	}
	Hunger -= Amount;
}
void UStatsComponent::AddHunger(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnHungerImprovement(GetOwner());
	}
	Hunger += Amount;
}

void UStatsComponent::LoseEnergy(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnEnergyDeterioration(GetOwner());
	}
	Energy -= Amount;
}
void UStatsComponent::AddEnergy(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnEnergyImprovement(GetOwner());
	}
	Energy += Amount;
}

void UStatsComponent::LoseFun(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnFunDeterioration(GetOwner());
	}
	Fun -= Amount;
}
void UStatsComponent::AddFun(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnFunImprovement(GetOwner());
	}
	Fun += Amount;
}

void UStatsComponent::LoseSocial(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnSocialDeterioration(GetOwner());
	}
	Social -= Amount;
}
void UStatsComponent::AddSocial(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnSocialImprovement(GetOwner());
	}
	Social += Amount;
}

void UStatsComponent::LoseHygene(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnHygeneDeterioration(GetOwner());
	}
	Hygene -= Amount;
}
void UStatsComponent::AddHygene(float Amount)
{
	if (GetOwner()->Implements<UStatsInterface>())
	{
		IStatsInterface::Execute_OnHygeneImprovement(GetOwner());
	}
	Hygene += Amount;
}

