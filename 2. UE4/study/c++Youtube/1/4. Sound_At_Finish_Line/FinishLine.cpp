// Fill out your copyright notice in the Description page of Project Settings.

#include "tutorial_of_c.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "FinishLine.h"

// Sets default values
AFinishLine::AFinishLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FinishLineBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	RootComponent = FinishLineBox;

	FinishLineBox->SetGenerateOverlapEvents(true);
	FinishLineBox->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::TriggerEnter);
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFinishLine::TriggerEnter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		//OtherActor->PlaySoundOnActor(MySound);
		UGameplayStatics::PlaySoundAtLocation(this, MySound, OtherActor->GetActorLocation());
	}
}
