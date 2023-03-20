// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UIMainMenu.h"
#include "UINewGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UI_PRACTICE_API AUINewGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget>NewWidgetClass);
	//TSubClassOf => 언리얼 엔진에서 UCLASS타입의 안정성을 보장하는 템플릿 클래스
	// TSubclassOf에 전달된 대상이 <> 안에 넣어준 인자 타입과 일치하거나, 템플릿 인자로 받은 타입을 상속받은 타입인지 검사한다. (런타임에)  

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;


};
