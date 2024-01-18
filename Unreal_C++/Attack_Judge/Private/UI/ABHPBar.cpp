// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABHPBar.h"
#include "Components/ProgressBar.h"
#include "Interface/ABCharacterWidgetInterface.h"


UABHPBar::UABHPBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;


}

void UABHPBar::NativeConstruct()
{
	Super::NativeConstruct();
	/*HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHpBar")));*/
	ensure(HpProgressBar);

	IABCharacterWidgetInterface* CharacterWidget = Cast<IABCharacterWidgetInterface>(OwningActor);
	if(CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}


void UABHPBar::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp/ MaxHp);
	}
}

