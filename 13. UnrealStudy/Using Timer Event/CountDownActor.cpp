// Fill out your copyright notice in the Description page of Project Settings.


#include "CountDownActor.h"

// Sets default values
ACountDownActor::ACountDownActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("countdown Text"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;

	CountdownTime = 3;
}

// Called when the game starts or when spawned
void ACountDownActor::BeginPlay()
{
	Super::BeginPlay();
	UpdateTimerDisplay();

	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountDownActor::AdvanceTimer, 1.0f, true);
}


void ACountDownActor::UpdateTimerDisplay()
{
	FString fString = FString::FromInt(FMath::Max(CountdownTime, 0));
	CountdownText->SetText(FText::FromString(fString));
}

void ACountDownActor::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay();
	if (CountdownTime < 1)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();
	}
}

void ACountDownActor::CountdownHasFinished_Implementation()
{
	CountdownText->SetText(FText::FromString("Go!!!!"));
	
}
 
