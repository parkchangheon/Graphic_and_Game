// Fill out your copyright notice in the Description page of Project Settings.


#include "FloationActor.h"

// Sets default values
AFloationActor::AFloationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	floatingSpeed = FVector(1.0f, 1.0f, 1.0f);
}

// Called when the game starts or when spawned
void AFloationActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaX = (FMath::Sin(RunningTime.X + DeltaTime * floatingSpeed.X) - FMath::Sin(RunningTime.X));
	float DeltaY = (FMath::Sin(RunningTime.Y + DeltaTime * floatingSpeed.Y) - FMath::Sin(RunningTime.Y));
	float DeltaZ = (FMath::Sin(RunningTime.Z + DeltaTime * floatingSpeed.Z) - FMath::Sin(RunningTime.Z));

	NewLocation += FVector(DeltaX, DeltaY, DeltaZ) * floatingSpeed;
	RunningTime += DeltaTime * floatingSpeed;


	SetActorLocation(NewLocation);
	
}

