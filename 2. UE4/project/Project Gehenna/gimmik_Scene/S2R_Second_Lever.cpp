// Fill out your copyright notice in the Description page of Project Settings.


#include "S2R_Second_Lever.h"


AS2R_Second_Lever::AS2R_Second_Lever()
{
	PrimaryActorTick.bCanEverTick = false;
	CountdownTime = 4;
	isholding = false;
}


void AS2R_Second_Lever::BeginPlay()
{
	Super::BeginPlay();

}


void AS2R_Final_PannelLever::Interact()
{

}

void AS2R_Second_Lever::StartTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer Start"));
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AS2R_Second_Lever::AdvanceTimer, 1.0f, true);
}


void AS2R_Second_Lever::AdvanceTimer()
{
	--CountdownTime;
	UE_LOG(LogTemp, Warning, TEXT("%d", CountdownTime));
	if (CountdownTime < 2 && CountdownTime>=1) //3초 지난 후,
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();

	}
}





void AS2R_Second_Lever::CountdownHasFinished()
{
	UE_LOG(LogTemp,Warning, TEXT("Called!"));
}
