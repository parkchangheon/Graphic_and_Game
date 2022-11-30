// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_FasterPill.h"

AItem_FasterPill::AItem_FasterPill()
{
	PrimaryActorTick.bCanEverTick = false;

	ConstructorHelpers::FObjectFinder<UStaticMesh> Item_FP(TEXT("StaticMesh'/Game/PCH_PRIVATE/SM_ReinforcementPill.SM_ReinforcementPill'"));
	if (Item_FP.Succeeded())
	{
		Item->SetStaticMesh(Item_FP.Object);
	}

}