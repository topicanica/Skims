// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SkimsGameMode.generated.h"

UCLASS(minimalapi)
class ASkimsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASkimsGameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* BackgroundMusicCue;
};



