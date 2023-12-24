// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TTGameInstance.generated.h"


struct FStudentData
{
	FStudentData() {}
	FStudentData(int32 InOrder, const FString& InName) :Order(InOrder), Name(InName) {}

	friend FArchive& operator<<(FArchive& Ar, FStudentData& InStudentData)
	{
		Ar << InStudentData.Order;
		Ar << InStudentData.Name;
		return Ar;
	}

	int32 Order = -1;
	FString Name = TEXT("PARKer");
};


UCLASS()
class TOUCHTEST_API UTTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UTTGameInstance();
	virtual void Init()override;
	virtual void Shutdown()override;

private:
	UPROPERTY()
	TObjectPtr<class USerialize_Student> StudentSrc;


};

