// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpen_Component.h"

// Sets default values for this component's properties
UDoorOpen_Component::UDoorOpen_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	DoorOpenComponent();
}


// Called every frame
void UDoorOpen_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}

void UDoorOpen_Component::DoorOpenComponent()
{
	FRotator newRotation = GetOwner()->GetActorRotation();
	newRotation.Yaw += 90.f;
	GetOwner()->SetActorRotation(newRotation);
}

