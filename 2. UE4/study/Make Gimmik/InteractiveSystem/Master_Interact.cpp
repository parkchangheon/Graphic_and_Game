// Fill out your copyright notice in the Description page of Project Settings.


#include "Master_Interact.h"

// Sets default values
AMaster_Interact::AMaster_Interact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT COMPONENT"));
	RootComponent = _RootComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Mesh->SetupAttachment(RootComponent);



}

// Called when the game starts or when spawned
void AMaster_Interact::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMaster_Interact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

