// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Userprofile.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CPP_STUDY_API UUserprofile : public UObject
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float HpMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	FString Name;


	//블루프린트 드롭다운 메뉴에서 UObject로부터 파생된 모든 UClass를 출력
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Unit)
	TSubclassOf<UObject> UClassOfPlayer;

	//GameMode C++베이스 클래스로부터 파생된 UCLASS들의 문자열 이름을 출력
	UPROPERTY(EditAnywhere, meta = (MetaClass = "GameMode"),
		Category = Unit)
		FStringClassReference UClassGameMode;
};


