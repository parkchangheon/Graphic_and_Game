// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TTMoveWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOUCHTEST_API UTTMoveWidget : public UUserWidget
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* MovePanel;
};
