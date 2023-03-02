// Fill out your copyright notice in the Description page of Project Settings.


#include "FireEvent.h"

// Sets default values
AFireEvent::AFireEvent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire Particle"));
	RootComponent = particleSystem;

	fireDeltaTime = 5;


}

// Called when the game starts or when spawned
void AFireEvent::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(fireTimer, this, &AFireEvent::AddFuel, 1.0f, true);
}


void AFireEvent::AddFuel()
{
	--fireDeltaTime;
	if (fireDeltaTime <= 0)
	{
		OffFire();
	}
}

void AFireEvent::OffFire()
{
	GetWorldTimerManager().ClearTimer(fireTimer);
	particleSystem->DeactivateSystem();
}

