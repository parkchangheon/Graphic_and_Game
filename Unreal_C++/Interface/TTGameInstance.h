// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TTGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOUCHTEST_API UTTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UTTGameInstance();
	virtual void Init()override;

private:

	UPROPERTY() 
	FString SchoolName;

};

