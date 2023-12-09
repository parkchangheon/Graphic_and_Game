// Fill out your copyright notice in the Description page of Project Settings.


#include "TTBackWidget.h"
#include "TTMoveWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UTTBackWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsTouching = false;
}

FReply UTTBackWidget::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchStarted(InGeometry, InGestureEvent);

	UCanvasPanel* MovePanelCanvas = MoveWidgetRef->MovePanel;
	UCanvasPanelSlot* MovePanelCanvasSlot = Cast<UCanvasPanelSlot>(MovePanelCanvas->Slot);

	ClickLocDiff = InGestureEvent.GetScreenSpacePosition() - MovePanelCanvasSlot->GetPosition();

	bIsTouching = true;
	
	return FReply::Handled();
}

FReply UTTBackWidget::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchEnded(InGeometry, InGestureEvent);
	bIsTouching = false;
	return FReply::Handled();
}

FReply UTTBackWidget::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	Super::NativeOnTouchMoved(InGeometry, InGestureEvent);
	if (bIsTouching)
	{
		SetWidgetPosition(MoveWidgetRef, InGestureEvent.GetScreenSpacePosition());
	}
	return FReply::Handled();
}

void UTTBackWidget::SetWidgetPosition(UUserWidget* InUserWidget, FVector2D InTouchPos)
{
	UCanvasPanel* MovePanelCanvas = MoveWidgetRef->MovePanel;
	UCanvasPanelSlot* MovePanelCanvasSlot = Cast<UCanvasPanelSlot>(MovePanelCanvas->Slot);

	if (MovePanelCanvasSlot)
	{
		MovePanelCanvasSlot->SetPosition(InTouchPos - ClickLocDiff);
	}

}
