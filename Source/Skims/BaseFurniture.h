// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBaseActor.h"
#include "BaseFurniture.generated.h"

/**
 * 
 */
UCLASS()
class SKIMS_API ABaseFurniture : public AInteractableBaseActor
{
	GENERATED_BODY()

public:
	ABaseFurniture() : AInteractableBaseActor() {};
};
