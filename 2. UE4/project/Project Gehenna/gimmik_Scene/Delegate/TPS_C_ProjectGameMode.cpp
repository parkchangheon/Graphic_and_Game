// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPS_C_ProjectGameMode.h"
#include "TPS_C_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

ATPS_C_ProjectGameMode::ATPS_C_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;

	}
}

//void ATPS_C_ProjectGameMode::BeginPlay()
//{
//	Super::BeginPlay();
//	ChangeMenuWidget(StartingWidgetClass);
//}
//
//void ATPS_C_ProjectGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
//{
//	if (CurrentWidget != nullptr)
//	{
//		CurrentWidget->RemoveFromViewport();
//		CurrentWidget = nullptr;
//	}
//
//	if (NewWidgetClass != nullptr)
//	{
//		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
//		if (CurrentWidget != nullptr)
//		{
//			CurrentWidget->AddToViewport();
//		}
//	}
//}