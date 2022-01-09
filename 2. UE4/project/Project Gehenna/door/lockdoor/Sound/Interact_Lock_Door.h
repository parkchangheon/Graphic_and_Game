// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Interact.h"
#include "Interact_Lock_Door.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API AInteract_Lock_Door : public AMaster_Interact
{
	GENERATED_BODY()


public:
	AInteract_Lock_Door();
	virtual void BeginPlay() override;

	virtual void Interact() override;


public:
	UPROPERTY(BlueprintReadWrite)
	bool IsDoorclosed;

	UPROPERTY(BlueprintReadWrite)
	bool IsDoorLocked;

	UPROPERTY()
	bool DoorLockSound;

	float DoorCurrentRotation;
	float AddRotation;

	class UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere,Category="Sound")
	class USoundBase* LockDoor;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* OpenDoor;

};
