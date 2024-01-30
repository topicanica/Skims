// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StatsInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStatsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SKIMS_API IStatsInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	// Interface made for blueprint events connected to HUDStats and StatsCompoenent
public:
	UFUNCTION(BlueprintNativeEvent, Category = Bladder)
	void OnBladderDeterioration();
	virtual void OnBladderDeterioration_Implementation() = 0;

	UFUNCTION(BlueprintNativeEvent, Category = Bladder)
	void OnBladderImprovement();
	virtual void OnBladderImprovement_Implementation() = 0;



	UFUNCTION(BlueprintNativeEvent, Category = Hunger)
	void OnHungerDeterioration();
	virtual void OnHungerDeterioration_Implementation() = 0;

	UFUNCTION(BlueprintNativeEvent, Category = Hunger)
	void OnHungerImprovement();
	virtual void OnHungerImprovement_Implementation() = 0;



	UFUNCTION(BlueprintNativeEvent, Category = Energy)
	void OnEnergyDeterioration();
	virtual void OnEnergyDeterioration_Implementation() = 0;

	UFUNCTION(BlueprintNativeEvent, Category = Energy)
	void OnEnergyImprovement();
	virtual void OnEnergyImprovement_Implementation() = 0;



	UFUNCTION(BlueprintNativeEvent, Category = Fun)
	void OnFunDeterioration();
	virtual void OnFunDeterioration_Implementation() = 0;

	UFUNCTION(BlueprintNativeEvent, Category = Fun)
	void OnFunImprovement();
	virtual void OnFunImprovement_Implementation() = 0;



	UFUNCTION(BlueprintNativeEvent, Category = Social)
	void OnSocialDeterioration();
	virtual void OnSocialDeterioration_Implementation() = 0;

	UFUNCTION(BlueprintNativeEvent, Category = Social)
	void OnSocialImprovement();
	virtual void OnSocialImprovement_Implementation() = 0;



	UFUNCTION(BlueprintNativeEvent, Category = Hygene)
	void OnHygeneDeterioration();
	virtual void OnHygeneDeterioration_Implementation() = 0;

	UFUNCTION(BlueprintNativeEvent, Category = Hygene)
	void OnHygeneImprovement();
	virtual void OnHygeneImprovement_Implementation() = 0;
};
