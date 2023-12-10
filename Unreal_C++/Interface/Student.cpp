// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectReflection/Student.h"

UStudent::UStudent()
{
	Name = TEXT("학생1");
	Year = 1;
	ID = 1;
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Warning, TEXT("학생 %s는 공부를 해야합니다."), *Name);
}
