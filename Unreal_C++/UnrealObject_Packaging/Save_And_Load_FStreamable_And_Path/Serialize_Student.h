// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Serialize_Student.generated.h"

/**
 * 
 */
UCLASS()
class TOUCHTEST_API USerialize_Student : public UObject
{
	GENERATED_BODY()
	
public:
	USerialize_Student();
	int32 GetOrder() const { return Order; }
	void SetOrder(int32 InOrder) { Order = InOrder; }

	const FString& GetName() const { return Name; }
	void SetName(const FString& InName) { Name = InName; }

	virtual void Serialize(FArchive& Ar) override;


private:
	UPROPERTY()
	int32 Order;

	UPROPERTY()
	FString Name;

};
