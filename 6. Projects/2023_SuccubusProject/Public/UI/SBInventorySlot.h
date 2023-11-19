// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBInventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class SUCCUBUSAD_API USBInventorySlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//USBInventorySlot(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMax=31, UIMin=-1))
	int SlotNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Count;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<ESlotType> Type;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UImage* ItemImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* ItemText;

};
