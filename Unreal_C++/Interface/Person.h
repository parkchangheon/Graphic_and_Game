// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class TOUCHTEST_API UPerson : public UObject
{
	GENERATED_BODY()


public:

	UPerson();

	UFUNCTION()
	virtual void DoLesson();
	FORCEINLINE	const FString& GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& InName) { Name = InName; }


protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;


private:


};
