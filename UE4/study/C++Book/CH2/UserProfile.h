// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserProfile.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class C_PLUS_PROJECT_API UUserProfile : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)    //EditAnywhere 는 UPROPERTY를 코드 또는 편집기를 통해 변경가능하다는 의미,, BlueprintReadWrite는 블루프린트가 변수를 언제든 읽고 쓸수 있음을 의미
	float Armor;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float HpMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	FString Name;



	//블루프린트 드롭다운 메뉴에서 UObject로부터 파생된 모든 UClass 출력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	TSubclassOf<UObject>UClassOfPlayer;


	//GameMode C++베이스 클래스로부터 파생된 UCLASS들의 문자열 이름을 출력
	UPROPERTY(EditAnywhere, meta = (MetaClass = "GameMode"), Category = Unit)
	FStringClassReference UClassGameMode;


	//Custom struct example UPROPERTY(EditAnywhere, BlueprintReadWrite,Category=HUD)
};





