// Copyright Epic Games, Inc. All Rights Reserved.

#include "tutorial_of_c.h"
#include "tutorial_of_cGameMode.h"
#include "tutorial_of_cHUD.h"
#include "tutorial_of_cCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

void Atutorial_of_cGameMode::BeginPlay()
{
	Super::BeginPlay();
	Atutorial_of_cCharacter* MyCharacter = Cast<Atutorial_of_cCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (PlayerHUDClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}

Atutorial_of_cGameMode::Atutorial_of_cGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = Atutorial_of_cHUD::StaticClass();
}
