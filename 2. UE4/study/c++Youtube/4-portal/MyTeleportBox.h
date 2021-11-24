// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "TPS_C_ProjectCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyTeleportBox.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API AMyTeleportBox : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	AMyTeleportBox();
	
	UFUNCTION()
	void EnterTeleporter(class AActor* overlappedActor, class AActor* otherActor);

	UFUNCTION()
	void ExitTeleporter(class AActor* overlappedActor, class AActor* otherActor);

	UPROPERTY(EditAnywhere, Category = "Teleporter")
	AMyTeleportBox* otherTele;
	UPROPERTY()
	bool teleporting;
};
