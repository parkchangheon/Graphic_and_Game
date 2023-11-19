// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SBInventory.h"
#include "Components/GridPanel.h"
#include "UI/SBInventorySlot.h"



void USBInventory::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ItemWidgetClass)
	{
		ItemWidget = Cast<USBInventorySlot>(CreateWidget(GetWorld(), ItemWidgetClass));
	}

	for (int i = 0; i < 30; i++)
	{
		InvenGridPanel->AddChild(ItemWidget);
	}
}
