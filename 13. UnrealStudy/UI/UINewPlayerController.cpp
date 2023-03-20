// Fill out your copyright notice in the Description page of Project Settings.


#include "UINewPlayerController.h"


void AUINewPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}


