// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UINewPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UI_PRACTICE_API AUINewPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AUINewPlayerController();
	virtual void BeginPlay()override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUIMainMenu> MMUIClass;

	class UUIMainMenu* MMUIWidget;
};
