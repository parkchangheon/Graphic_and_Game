// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TOUCHTEST_API FStudentManager : public FGCObject
{
public:
	FStudentManager(class UGCStudent* InStudent) : SafeStudent(InStudent) {};
	const class UGCStudent* GetStudent() const { return SafeStudent; }

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override
	{
		return TEXT("FStudentManager");
	}


private:
	class UGCStudent* SafeStudent = nullptr;


};
