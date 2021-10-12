// Fill out your copyright notice in the Description page of Project Settings.


#include "Uproperty_Tutorial.h"

// Sets default values
AUproperty_Tutorial::AUproperty_Tutorial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpeedOfMovingUp = 10.5f;
}

// Called when the game starts or when spawned
void AUproperty_Tutorial::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUproperty_Tutorial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();

	NewLocation.Z += SpeedOfMovingUp * DeltaTime;
	SetActorLocation(NewLocation);
}

