// Fill out your copyright notice in the Description page of Project Settings.


#include "S2R_Final_Gate.h"

AS2R_Final_Gate::AS2R_Final_Gate()
{
	Master_Gate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gate"));
	Door_Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorR"));
	Door_Left  = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorL"));

	Pannel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pan1"));
	Pannel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pan2"));
	Pannel3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pan3"));


	RootComponent = Master_Gate;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorAsset(TEXT("StaticMesh'/Game/Hospital/Meshes/Architecture/Doors/SM_Door.SM_Door'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>PannelAsset(TEXT("StaticMesh'/Game/MAP_CONTENTS/PCH_Direct12/Pannel/SM_WoodPannel.SM_WoodPannel'"));

	if (DoorAsset.Succeeded())
	{
		Door_Right->SetStaticMesh(DoorAsset.Object);
		Door_Left->SetStaticMesh(DoorAsset.Object);

		Pannel1->SetStaticMesh(PannelAsset.Object);
		Pannel2->SetStaticMesh(PannelAsset.Object);
		Pannel3->SetStaticMesh(PannelAsset.Object);


		Door_Right->SetupAttachment(RootComponent);
		Door_Left->SetupAttachment(RootComponent);
		Pannel1->SetupAttachment(RootComponent);
		Pannel2->SetupAttachment(RootComponent);
		Pannel3->SetupAttachment(RootComponent);

	}
	Gate_Status = false;

}




void AS2R_Final_Gate::BeginPlay()
{
	Super::BeginPlay();

	

}




void AS2R_Final_Gate::Interact()
{
	


}




void AS2R_Final_Gate::OpenDoor()
{


}



