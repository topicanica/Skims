// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBaseActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
AInteractableBaseActor::AInteractableBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	// Need to edit the size of the box component
	CollisionComp->BodyInstance.SetCollisionProfileName("OverlappAll");
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

