// Fill out your copyright notice in the Description page of Project Settings.


#include "S2R_Second_Lever.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"


AS2R_Second_Lever::AS2R_Second_Lever()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxMesh"));
	NPC_Lever = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>LeverNPC(TEXT("StaticMesh'/Game/MAP_CONTENTS/PCH_Direct12/Lever/SM_Lever.SM_Lever'"));

	if (LeverNPC.Succeeded())
	{
		NPC_Lever->SetStaticMesh(LeverNPC.Object);
	}

	BoxMesh->OnComponentBeginOverlap.AddDynamic(this, &AS2R_Second_Lever::OnBeginOverlap);
}


void AS2R_Second_Lever::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AS2R_Second_Lever::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AS2R_Second_Lever::OnOverlapEnd);
}

void AS2R_Second_Lever::OnBeginOverlap(AActor* Overlapped, AActor* Other)
{
	ACharacter* NPC_Moon = Cast<ACharacter>(Other);
	if (Other) // 다른 겹쳐진 것이 == NPC 문창섭일때.
	{
		
	}

	UE_LOG(LogTemp, Warning, TEXT("OVERLAPPED"));
}



void AS2R_Second_Lever::OnOverlapEnd(AActor* Overlapped, AActor* Other)
{

}

