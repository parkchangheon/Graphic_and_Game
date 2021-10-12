// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Uproperty_Tutorial.generated.h"

UCLASS()
class BASIC_C_TUTORIAL_API AUproperty_Tutorial : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUproperty_Tutorial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere,Category="Velocity for Actor")
	float SpeedOfMovingUp;

};
