// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPS_C_ProjectGameMode.generated.h"

UCLASS(minimalapi)
class ATPS_C_ProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	//UFUNCTION()
	//void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	ATPS_C_ProjectGameMode();
protected:
	//virtual void BeginPlay() override;

	//UPROPERTY(EditAnyWhere)
	//	TSubclassOf<UUserWidget> StartingWidgetClass;

	//UPROPERTY()
	//	UUserWidget* CurrentWidget;
};



