// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldClock.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
AWorldClock::AWorldClock()
    : LastHour(-1), LastMinute(-1), LastTransitionValue(0.0f)
{
    PrimaryActorTick.bCanEverTick = true;
    TimeMultiplier = 50;

    FDateTime Now = FDateTime::Now();
    InitialTime = FDateTime(Now.GetYear(), Now.GetMonth(), Now.GetDay(), 8, 0, 0);
    CurrentTime = InitialTime;
}

void AWorldClock::BeginPlay()
{
    Super::BeginPlay();
}

void AWorldClock::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateCurrentTime(DeltaTime);
    CheckHourReached();
}
void AWorldClock::SetCurrentTime(FDateTime NewCurrentTime)
{
    CurrentTime = NewCurrentTime;
}
FString AWorldClock::GetCurrentTime() const
{
    FString TimeString = FString::Printf(TEXT("%02d:%02d"), CurrentTime.GetHour(), CurrentTime.GetMinute());
    return TimeString;
}

FDateTime AWorldClock::GetCurrentDateTime() const
{
    return CurrentTime;
}

void AWorldClock::UpdateCurrentTime(float DeltaTime)
{
    CurrentTime += FTimespan::FromMinutes(TimeMultiplier) * DeltaTime;
}

void AWorldClock::UpdateSkybox()
{
    if (CurrentTime.GetHour() != LastHour || CurrentTime.GetMinute() != LastMinute)
    {
        LastHour = CurrentTime.GetHour();
        LastMinute = CurrentTime.GetMinute();

        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AStaticMeshActor::StaticClass(), FName(TEXT("Skybox")), FoundActors);
        if (!FoundActors.IsEmpty())
        {
            AActor* Skybox = FoundActors[0];
            AStaticMeshActor* StaticMeshActor = Cast<AStaticMeshActor>(Skybox);
            UStaticMeshComponent* StaticMeshComponent = StaticMeshActor->GetStaticMeshComponent();
            UMaterialInterface* Material = StaticMeshComponent->GetMaterial(0);
            UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);

            if (!DynamicMaterial)
            {
                DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
                StaticMeshComponent->SetMaterial(0, DynamicMaterial);
            }

            float TransitionValue = CalculateDayNightTransitionValue(LastHour, LastMinute);
            DynamicMaterial->SetScalarParameterValue("Switch Day Night", TransitionValue);

            LastTransitionValue = TransitionValue;
        }
    }
}

float SmoothStep(float t)
{
    return t * t * (3.0f - 2.0f * t);
}

float AWorldClock::CalculateDayNightTransitionValue(int32 CurrentHour, int32 CurrentMinute)
{
    float TransitionFactor = 0.0f;
    if (CurrentHour >= 20 || CurrentHour < 4)
    {
        TransitionFactor = 1.0f;
    }
    else if (CurrentHour >= 4 && CurrentHour < 7)
    {
        TransitionFactor = 1.0f - SmoothStep((float)(CurrentHour - 4 + CurrentMinute / 60.0f) / 3.0f);
    }
    else if (CurrentHour >= 7 && CurrentHour < 17)
    {
        TransitionFactor = 0.0f;
    }
    else if (CurrentHour >= 17 && CurrentHour < 20)
    {
        float TransitionDurationMinutes = 180; // 3 hours in minutes
        float TotalMinutes = (CurrentHour - 17) * 60 + CurrentMinute;
        TransitionFactor = SmoothStep(TotalMinutes / TransitionDurationMinutes);
    }

    return FMath::Clamp(TransitionFactor, 0.0f, 1.0f);
}

void AWorldClock::CheckHourReached()
{
    if (LastHour != CurrentTime.GetHour())
    {
        OnHourCounter = 0;
    }
    
    UpdateSkybox();
    if (CurrentTime.GetMinute() == 0 && OnHourCounter == 0)
    {
        OnHourCounter = 1;
        OnHourChanged.Broadcast();
    }
}


