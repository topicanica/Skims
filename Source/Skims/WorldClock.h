#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetStringLibrary.h"
#include "WorldClock.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHourChangedDelegate);

UCLASS(Blueprintable)
class SKIMS_API AWorldClock : public AActor
{
	GENERATED_BODY()

public:
	AWorldClock();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Clock")
	FString GetCurrentTime() const;

	UFUNCTION(BlueprintCallable, Category = "Clock")
	FDateTime GetCurrentDateTime() const;

	UFUNCTION(BlueprintCallable, Category = "Clock")
	void SetCurrentTime(FDateTime NewCurrentTime);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Clock")
	float TimeMultiplier;

	UPROPERTY(BlueprintAssignable, Category = "Clock")
	FHourChangedDelegate OnHourChanged;

private:

	FDateTime InitialTime;
	FDateTime CurrentTime;

	void UpdateCurrentTime(float DeltaTime);

	void UpdateSkybox();

	float CalculateDayNightTransitionValue(int32 CurrentHour, int32 CurrentMinute);

	void CheckHourReached();

	float LastTransitionValue;
	int32 LastHour;
	int32 LastMinute;
	int32 OnHourCounter = 0;
};
