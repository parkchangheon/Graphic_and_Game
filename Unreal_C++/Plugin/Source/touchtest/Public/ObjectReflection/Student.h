// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectReflection/Person.h"
#include "ObjectReflection/LessonInterface.h"
#include "Plug_Person.h"

#include "Student.generated.h"


/**
 *  
 */
UCLASS()
class TOUCHTEST_API UStudent : public UPlug_Person
{
	GENERATED_BODY()

public:
	//UStudent();

	//virtual void DoLesson()override;

private:
	UPROPERTY()
	int32 ID;

public:
	//void GetNotification(const FString& InSchool, const FString& InNewNotify);

	
};
 