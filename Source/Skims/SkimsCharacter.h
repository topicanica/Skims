// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StatsInterface.h"
#include "InputActionValue.h"
#include "WorldClock.h"
#include "SkimsCharacter.generated.h"

UCLASS(Blueprintable)
class ASkimsCharacter : public ACharacter, public IStatsInterface
{
	GENERATED_BODY()

public:
	ASkimsCharacter();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ModifyBladder(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ModifyHunger(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ModifyEnergy(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ModifyFun(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ModifySocial(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ModifyHygene(float Amount);

	UFUNCTION()
	void UpdateStatsHourly();

	virtual void OnStatDepleted_Implementation() override;

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// Stats component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	class UStatsComponent* StatsComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	float Sensitivity = 0.5f;

	AWorldClock* WorldClock;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditANywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void EnableCharacterMovement(bool bShouldMove);

};

