// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StatsInterface.h"
#include "SkimsCharacter.generated.h"

UCLASS(Blueprintable)
class ASkimsCharacter : public ACharacter, public IStatsInterface
{
	GENERATED_BODY()

public:
	ASkimsCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual void OnBladderDeterioration_Implementation() override;
	virtual void OnBladderImprovement_Implementation() override;

	virtual void OnHungerDeterioration_Implementation() override;
	virtual void OnHungerImprovement_Implementation() override;

	virtual void OnEnergyDeterioration_Implementation() override;
	virtual void OnEnergyImprovement_Implementation() override;

	virtual void OnFunDeterioration_Implementation() override;
	virtual void OnFunImprovement_Implementation() override;

	virtual void OnSocialDeterioration_Implementation() override;
	virtual void OnSocialImprovement_Implementation() override;

	virtual void OnHygeneDeterioration_Implementation() override;
	virtual void OnHygeneImprovement_Implementation() override;


private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Stats component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
	class UStatsComponent* StatsComponent;
};

