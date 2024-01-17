// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABHPBar.h"
#include "Components/ProgressBar.h"

UABHPBar::UABHPBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;


}

void UABHPBar::NativeConstruct()
{
	Super::NativeConstruct();
	/*HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHpBar")));*/
	ensure(HpProgressBar);
}


void UABHPBar::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp);
	}
}

