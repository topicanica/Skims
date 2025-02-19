// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBaseActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/CollisionProfile.h"
#include "SkimsCharacter.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"


// Sets default values
AInteractableBaseActor::AInteractableBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(SceneComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SceneComp);

	// Bind the overlap event
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AInteractableBaseActor::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AInteractableBaseActor::OnOverlapEnd);

	// Set collision object type to your custom channel
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void AInteractableBaseActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractableBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableBaseActor::StartInteraction_Implementation()
{
	bIsInteractedWith = true;
	if (bIsInteractedWith)
	{
		TogglePlayerInput(false);
		ToggleWidgetVisibility(false);
		InteractingCharacter->EnableCharacterMovement(false);
		StartDelay();
	}
}

void AInteractableBaseActor::EndInteraction_Implementation()
{
	bIsInteractedWith = false;
	TogglePlayerInput(true);
	ToggleWidgetVisibility(true);
	InteractingCharacter->EnableCharacterMovement(true);

}


void AInteractableBaseActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromLine, const FHitResult& LineResult)
{
	if (OtherActor && OtherActor->IsA<ASkimsCharacter>())
	{
		InteractingCharacter = Cast<ASkimsCharacter>(OtherActor);

		// Perform line trace from player's location in the direction they're looking
		FVector StartLocation = InteractingCharacter->GetActorLocation();
		FVector ForwardVector = InteractingCharacter->GetActorForwardVector();
		FVector EndLocation = StartLocation + (ForwardVector * 400);

		FHitResult HitResult;
		FCollisionQueryParams TraceParams;

		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_GameTraceChannel1, TraceParams))
		{
			// Check if the hit actor is this player character
			if (HitResult.GetActor() == InteractingCharacter)
			{
				TogglePlayerInput(true);
				ToggleWidgetVisibility(true);
			}
		}
	}
}

void AInteractableBaseActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the overlapping actor is the main character
	if (OtherActor && OtherActor != this && OtherActor->IsA<ASkimsCharacter>())
	{
		ToggleWidgetVisibility(false);
		TogglePlayerInput(false);
	}
}

void AInteractableBaseActor::TogglePlayerInput(bool bShow)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		if (bShow)
		{			
			PlayerController->EnableInput(PlayerController);
			if (!bIsInteractedWith)
			{
				PlayerController->InputComponent->BindAction("Interact", IE_Pressed, this, &AInteractableBaseActor::StartInteraction);
			}
		}
		else
		{
			PlayerController->DisableInput(PlayerController);
			PlayerController->InputComponent->ClearActionBindings();
		}
	}
}

void AInteractableBaseActor::ToggleWidgetVisibility(bool bShow)
{
	if (bShow)
	{
		if (WidgetInstance == nullptr && WidgetInteractable != nullptr)
		{
			WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetInteractable);
			if (WidgetInstance != nullptr)
			{
				WidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if (WidgetInstance != nullptr)
		{
			WidgetInstance->RemoveFromParent();
			WidgetInstance = nullptr;
		}
	}
}

void AInteractableBaseActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (MeshComp && CollisionComp)
	{
		FBox Bounds = MeshComp->Bounds.GetBox();
		FVector Center = Bounds.GetCenter();
		FVector Extents = Bounds.GetExtent();
		FVector IncreasedExtents = Extents + FVector(10.0f, 10.0f, 10.0f);
		Center.Z = Bounds.Min.Z + Extents.Z;
		CollisionComp->SetWorldLocation(Center);
		CollisionComp->SetBoxExtent(IncreasedExtents);
	}
}

void AInteractableBaseActor::RemoveOverlappingInteractables()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		AInteractableBaseActor* InteractableActor = Cast<AInteractableBaseActor>(OverlappingActor);
		if (InteractableActor)
		{
			InteractableActor->Destroy();
		}
	}
}
void AInteractableBaseActor::StartDelay()
{
	// Get a reference to the world
	UWorld* World = GetWorld();
	if (!World)
	{
		// Handle error, world not found
		return;
	}

	// Call DelayedFunctionCall after 4 seconds
	FTimerHandle TimerHandle;
	World->GetTimerManager().SetTimer(TimerHandle, this, &AInteractableBaseActor::EndInteraction_Implementation, 4.0f, false);
}

// Function to round a value to the nearest grid spacing 
float AInteractableBaseActor::RoundToGridSpacing(float Value)
{
	return FMath::RoundToFloat(Value / GridSpacing) * GridSpacing;
}