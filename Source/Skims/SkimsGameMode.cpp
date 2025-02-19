// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkimsGameMode.h"
#include "SkimsPlayerController.h"
#include "SkimsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ASkimsGameMode::ASkimsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASkimsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Skims/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Skims/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	// Set default value for the Sound Cue variable
	static ConstructorHelpers::FObjectFinder<USoundBase> SoundCue(TEXT("/Game/Music/SC_ThemeSong"));
	BackgroundMusicCue = SoundCue.Object;
}

void ASkimsGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (BackgroundMusicCue)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BackgroundMusicCue);
	}
}
