// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Delegates/Delegate.h"
#include "InteractableBaseActor.generated.h"


UCLASS(Blueprintable)
class SKIMS_API AInteractableBaseActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AInteractableBaseActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the actor is interacted with 
	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void StartInteraction();

	virtual void StartInteraction_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void EndInteraction();

	virtual void EndInteraction_Implementation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactable")
	class ASkimsCharacter* InteractingCharacter;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class ASkimsCharacter* GetInteractingCharacter() const { return InteractingCharacter; }

	// Function to remove overlapping actors of the interactable type
	UFUNCTION(BlueprintCallable, Category = "Interactible")
	void RemoveOverlappingInteractables();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Functions to handle the begin and end overlap event
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromLine, const FHitResult& LineResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called when the actor is constructed
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InteractableActor, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComp;

	// Static mesh component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InteractableActor, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComp;

	// Static mesh component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InteractableActor, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* ChildMeshComp;

	// Collision box Component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = InteractableActor, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionComp;

	// Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = InteractableWidget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WidgetInteractable;

	UUserWidget* WidgetInstance;

protected:
	void ToggleWidgetVisibility(bool bShow);

	void TogglePlayerInput(bool bInput);

	void StartDelay();

	bool bIsInteractedWith;

	float RoundToGridSpacing(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InteractableActor)
	float GridSpacing = 100.0f;
};

