// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveSomewhere.h"

// Sets default values for this component's properties
UMoveSomewhere::UMoveSomewhere()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveSomewhere::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->GetWorldTimerManager().SetTimer(MoveSomewhereHandle, this, &UMoveSomewhere::MoveSomewhere, 2.f,true);
	// ...
	
}


// Called every frame
void UMoveSomewhere::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMoveSomewhere::MoveSomewhere()
{
	FVector newLocation = GetOwner()->GetActorLocation();
	newLocation.X += 100.f;
	GetOwner()->SetActorLocation(newLocation);
}

