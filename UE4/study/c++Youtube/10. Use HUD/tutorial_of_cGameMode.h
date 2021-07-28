// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "tutorial_of_cGameMode.generated.h"

UCLASS(minimalapi)
class Atutorial_of_cGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override; 

public:
	Atutorial_of_cGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;
};



