// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StatsInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
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
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Stats")
	//void OnBladderModified();

	/*UFUNCTION(BlueprintNativeEvent, Category = "Stats")
	void OnLowStat();
	virtual void OnLowStat_Implementation() = 0;*/

	UFUNCTION(BlueprintNativeEvent, Category = "Stats")
	void OnStatDepleted();
	virtual void OnStatDepleted_Implementation() = 0;

	// this should be only used for specific functions that are connected to stats, such as on depleted, on low stat etc etc
};
 
