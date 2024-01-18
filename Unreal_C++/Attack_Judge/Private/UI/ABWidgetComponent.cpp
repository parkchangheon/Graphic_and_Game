// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABWidgetComponent.h"
#include "UI/ABUserWidget.h"

void UABWidgetComponent::InitWidget()
{
	Super::InitWidget();
	// 해당 위젯에 대한 인스턴스가 생긴 직후.
	// 위젯에 관련된 UI 요소들이 모두 준비가 되면 NativeConstruct가 

	UABUserWidget* ABUserWidget = Cast<UABUserWidget>(GetWidget());	//현재 컴포넌트가 소유한 위젯을 가져옴
	if (ABUserWidget)
	{
		ABUserWidget->SetOwningActor(GetOwner());
	}

}