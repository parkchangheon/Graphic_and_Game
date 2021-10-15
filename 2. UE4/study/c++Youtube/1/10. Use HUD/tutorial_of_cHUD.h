// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "tutorial_of_cHUD.generated.h"

UCLASS()
class Atutorial_of_cHUD : public AHUD
{
	GENERATED_BODY()

public:
	Atutorial_of_cHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

