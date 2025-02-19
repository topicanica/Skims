// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldClock.h"
#include "StatsComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKIMS_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UStatsComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Bladder;
	float MaxBladder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Hunger;
	float MaxHunger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Energy;
	float MaxEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Fun;
	float MaxFun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Social;
	float MaxSocial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Hygene;
	float MaxHygene;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DepleteStats();
	
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetStats(float NewBladder, float NewHunger, float NewEnergy, float NewFun, float NewSocial, float NewHygene);

	// Take points of each stat
	void ModifyBladder(float Amount);
	FORCEINLINE float GetBladderPercent() const { return Bladder / 100.0f; }

	void ModifyHunger(float Amount);
	FORCEINLINE float GetHungerPercent() const { return Hunger / 100.0f; }

	void ModifyEnergy(float Amount);
	FORCEINLINE float GetEnergyPercent() const { return Energy / 100.0f; }

	void ModifyFun(float Amount);
	FORCEINLINE float GetFunPercent() const { return Fun / 100.0f; }
	
	void ModifySocial(float Amount);
	FORCEINLINE float GetSocialPercent() const { return Social / 100.0f; }

	void ModifyHygene(float Amount);
	FORCEINLINE float GetHygenePercent() const { return Hygene / 100.0f; }
};
