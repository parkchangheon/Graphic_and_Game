// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectReflection/LessonInterface.h"

// Add default functionality here for any ILessonInterface functions that are not pure virtual.

void ILessonInterface::DoLesson()
{
	UE_LOG(LogTemp, Warning, TEXT("Interface Class Initialize"));
}
