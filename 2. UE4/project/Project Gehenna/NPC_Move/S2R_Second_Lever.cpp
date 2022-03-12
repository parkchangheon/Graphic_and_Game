// Fill out your copyright notice in the Description page of Project Settings.


#include "S2R_Second_Lever.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"


AS2R_Second_Lever::AS2R_Second_Lever()
{
	PrimaryActorTick.bCanEverTick = false;
	CountdownTime = 4;
	isholding = false;

	BoxMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxMesh"));
	NPC_Lever = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>Lever(TEXT("StaticMesh'/Game/MAP_CONTENTS/PCH_Direct12/Lever/SM_Lever.SM_Lever'"));

	if (Lever.Succeeded())
	{
		NPC_Lever->SetStaticMesh(Lever.Object);
	}
}


void AS2R_Second_Lever::BeginPlay()
{
	Super::BeginPlay();

}



void AS2R_Second_Lever::StartTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer Start"));
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AS2R_Second_Lever::AdvanceTimer, 1.0f, true);
}


void AS2R_Second_Lever::AdvanceTimer()
{
	--CountdownTime;
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


void AS2R_Second_Lever::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("NotifyHit"));
}

