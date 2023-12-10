// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectReflection/Teacher.h"

UTeacher::UTeacher()
{
	Name = TEXT("선생1");
	Year = 10;
	ID = 1001;
}

void UTeacher::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Warning, TEXT("선생 %s는 수업을 해야합니다."), *Name);

}
