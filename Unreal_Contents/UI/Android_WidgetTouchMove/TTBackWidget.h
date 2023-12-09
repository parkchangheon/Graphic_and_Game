// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TTBackWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOUCHTEST_API UTTBackWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct()override;

	virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)override;
	virtual FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)override;
	virtual FReply NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)override;

	void SetWidgetPosition(UUserWidget* InUserWidget, FVector2D InTouchPos);
	bool bIsTouching;
	
	FVector2D ClickLocDiff;

	UPROPERTY(meta=(BindWidget))
	class UTTMoveWidget* MoveWidgetRef;
};
