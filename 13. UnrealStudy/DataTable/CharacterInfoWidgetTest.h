// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterInfoWidgetTest.generated.h"

/**
 * 
 */
class UTextBlock;
struct FABCharacterData;
UCLASS()
class STUDYPROJECT_API UCharacterInfoWidgetTest : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterLevel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterHp;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterAttack;


};
