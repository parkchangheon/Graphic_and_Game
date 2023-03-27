// Fill out your copyright notice in the Description page of Project Settings.


#include "UINewPlayerController.h"
#include "UIMainMenu.h"


AUINewPlayerController::AUINewPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUIMainMenu> WB_MainMenu (TEXT("WidgetBlueprint'/Game/UI/BP_MainUI.BP_MainUI_C'"));

	if (WB_MainMenu.Succeeded())
	{
		MMUIClass = WB_MainMenu.Class;
		UE_LOG(LogTemp, Warning, TEXT("WB_MainMenu.Succeeded()"));

	}
}

void AUINewPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MMUIWidget = CreateWidget<UUIMainMenu>(this, MMUIClass);
	MMUIWidget->AddToViewport();

	SetInputMode(FInputModeGameAndUI());
}


