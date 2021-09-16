// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_Plus_projectGameMode.generated.h"

UCLASS(minimalapi)
class AC_Plus_projectGameMode : public 
	AGameModeBase
{
	GENERATED_BODY()

public:
	AC_Plus_projectGameMode();

public:
	void BeginPlay();
};



