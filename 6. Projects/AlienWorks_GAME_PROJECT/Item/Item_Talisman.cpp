// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Talisman.h"

AItem_Talisman::AItem_Talisman()
{
	PrimaryActorTick.bCanEverTick = false;

	ConstructorHelpers::FObjectFinder<UStaticMesh> Item_TM(TEXT("StaticMesh'/Game/ProjectAsset/Props/SM_Talisman.SM_Talisman'"));
	if (Item_TM.Succeeded())
	{
		Item->SetStaticMesh(Item_TM.Object);
	}
}
