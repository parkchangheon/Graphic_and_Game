// Fill out your copyright notice in the Description page of Project Settings.


#include "S2R_Final_PannelLever.h"
#include "S2R_Second_Lever.h"



AS2R_Final_PannelLever::AS2R_Final_PannelLever()
{

	Pannel_Status = false;



	Main_Body = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("MainBody"));
	Lever = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever1"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));


	RootComponent = Main_Body;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>LeverAsset(TEXT("StaticMesh'/Game/MAP_CONTENTS/PCH_Direct12/Lever/SM_Lever.SM_Lever'"));

	if (LeverAsset.Succeeded())
	{
		Lever->SetStaticMesh(LeverAsset.Object);
	}


}



void AS2R_Final_PannelLever::Interact()
{
	Pannel_Status = true;

}
