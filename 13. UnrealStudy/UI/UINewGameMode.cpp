// Fill out your copyright notice in the Description page of Project Settings.

#include <Blueprint/UserWidget.h>
#include "GameMode/UINewGameMode.h"


void AUINewGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}


void AUINewGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	// 1. 기존 위젯이 존재한다면 지운다
	// 2. 새로이 표시할 위젯이 존재시 => 해당 위젯을 CurrentWidget에 만들어준다.

	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}



}