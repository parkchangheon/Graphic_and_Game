// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "NewUIMenu.h"
#include "UIMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class UI_PRACTICE_API UUIMainMenu : public UUserWidget
{
	GENERATED_BODY()



protected:
	UNewUIMenu* NewWidget;

	UPROPERTY()
	UButton* Menu_Btn;

	UPROPERTY()
	UButton* QuitButton;

public:
	void OnclickedNewGameBtn();
	void OnClickedQuitBtn();
};
