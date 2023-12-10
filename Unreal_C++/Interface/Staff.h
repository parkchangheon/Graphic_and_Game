// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectReflection/Person.h"
#include "ObjectReflection/LessonInterface.h"
#include "Staff.generated.h"

/**
 * 
 */
UCLASS()
class TOUCHTEST_API UStaff : public UPerson, public ILessonInterface
{
	GENERATED_BODY()
	
public:
	UStaff();

	virtual void DoLesson()override;

};
