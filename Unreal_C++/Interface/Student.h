// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectReflection/Person.h"
#include "ObjectReflection/LessonInterface.h"
#include "Student.generated.h"

/**
 *  
 */
UCLASS()
class TOUCHTEST_API UStudent : public UPerson, public ILessonInterface
{
	GENERATED_BODY()

public:
	UStudent();

	virtual void DoLesson()override;

private:
	UPROPERTY()
	int32 ID;


	
};
 