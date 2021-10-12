// Fill out your copyright notice in the Description page of Project Settings.


#include "Door_tutorial.h"

// Sets default values
ADoor_tutorial::ADoor_tutorial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor_tutorial::BeginPlay()
{
	Super::BeginPlay();
	
	
	ScaleDoor();
}

// Called every frame
void ADoor_tutorial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OpenDoor(DeltaTime);
}

void ADoor_tutorial::OpenDoor(float DeltaTime)
{
	FRotator NewRotation = GetActorRotation();
	if (NewRotation.Yaw <= 90) {
		NewRotation.Yaw += OpenDoorFull * DeltaTime;
		SetActorRotation(NewRotation);
	}
}

void ADoor_tutorial::ScaleDoor()
{
	//scale 하는법
	//1번째
	//GetTransform().GetScale3D();
	
	//2번째
	/*FVector NewScale = GetActorScale3D();
	NewScale.X += 10.f;
	SetActorScale3D();*/
	
	//3번째
	//SetActorScale3D(FVector(5.f, 2.f, 5.f));
}

