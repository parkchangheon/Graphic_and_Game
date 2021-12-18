// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Interact.h"
#include "Interact_testDoor.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API AInteract_testDoor : public AMaster_Interact
{
	GENERATED_BODY()
	

public:
	AInteract_testDoor();
	virtual void BeginPlay() override;

	virtual void Interact() override;

	

	
public:
	UPROPERTY()
	bool IsDoorclosed;

	float DoorCurrentRotation;
	float AddRotation;

	class UStaticMeshComponent* Door;
};
