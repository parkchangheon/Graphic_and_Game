// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Interact.h"
#include "Components/SpotLightComponent.h"
#include "Interact_test_light.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API AInteract_test_light : public AMaster_Interact
{
	GENERATED_BODY()
	

public:
	virtual void Interact() override;

	UPROPERTY()
	bool State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Intensity;

	UPROPERTY(EditAnywhere)
	USpotLightComponent* Light;

	AInteract_test_light();
};
