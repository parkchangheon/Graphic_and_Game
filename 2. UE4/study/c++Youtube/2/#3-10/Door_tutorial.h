// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door_tutorial.generated.h"

UCLASS()
class BASIC_C_TUTORIAL_API ADoor_tutorial : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor_tutorial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Open the door 
	const float OpenDoorFull = -90.f;
	void OpenDoor(float DeltaTime);
	void ScaleDoor();
};
