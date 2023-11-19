// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBInventory.generated.h"

/**
 * 
 */
UCLASS()
class SUCCUBUSAD_API USBInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UGridPanel* InvenGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widget)
	TSubclassOf<UUserWidget> ItemWidgetClass;

	UPROPERTY()
	class UUserWidget* ItemWidget;
};
