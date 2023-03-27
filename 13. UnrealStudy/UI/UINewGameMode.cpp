// Fill out your copyright notice in the Description page of Project Settings.

#include <Blueprint/UserWidget.h>
#include "GameMode/UINewGameMode.h"
#include "UINewPlayerController.h"



AUINewGameMode::AUINewGameMode()
{
	UE_LOG(LogTemp, Warning, TEXT("AUINewGameMode Constructor"));

	PlayerControllerClass = AUINewPlayerController::StaticClass();
}

void AUINewGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AUINewGameMode is Begin Play"));
}




