// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Plug_PersonImpl.generated.h"

/**
 * 
 */
 //class COMMONUTILITY_API UPlug_PersonImpl : public UObject

UCLASS()
class UPlug_PersonImpl : public UObject		//API를 삭제해서 안전하게 외부 모듈이 참조할 수 없도록함.

{
	GENERATED_BODY()
	
};
