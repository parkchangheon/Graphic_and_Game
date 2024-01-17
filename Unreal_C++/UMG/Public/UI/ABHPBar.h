// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABHPBar.generated.h"

/**
 * 
 */
UCLASS()
class TESTTT_API UABHPBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UABHPBar(const FObjectInitializer& ObjectInitializer);
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:
	virtual void NativeConstruct() override;



protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;
};
