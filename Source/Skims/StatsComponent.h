// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKIMS_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditDefaultsOnly, Category = Bladder)
	float Bladder;

	UPROPERTY(EditDefaultsOnly, Category = Hunger)
	float Hunger;

	UPROPERTY(EditDefaultsOnly, Category = Energy)
	float Energy;

	UPROPERTY(EditDefaultsOnly, Category = Fun)
	float Fun;

	UPROPERTY(EditDefaultsOnly, Category = Social)
	float Social;

	UPROPERTY(EditDefaultsOnly, Category = Hygene)
	float Hygene;

	// Sets default values for this component's properties
	UStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Take points of each stat
	void LoseBladder(float Amount);
	void AddBladder(float Amount);
	FORCEINLINE float GetBladderPercent() const { return Bladder / 100.0f; }

	void LoseHunger(float Amount);
	void AddHunger(float Amount);
	FORCEINLINE float GetHungerPercent() const { return Hunger / 100.0f; }

	void LoseEnergy(float Amount);
	void AddEnergy(float Amount);
	FORCEINLINE float GetEnergyPercent() const { return Energy / 100.0f; }

	void LoseFun(float Amount);
	void AddFun(float Amount);
	FORCEINLINE float GetFunPercent() const { return Fun / 100.0f; }

	void LoseSocial(float Amount);
	void AddSocial(float Amount);
	FORCEINLINE float GetSocialPercent() const { return Social / 100.0f; }

	void LoseHygene(float Amount);
	void AddHygene(float Amount);
	FORCEINLINE float GetHygenePercent() const { return Hygene / 100.0f; }

};
