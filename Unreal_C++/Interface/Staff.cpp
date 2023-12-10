// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectReflection/Staff.h"

UStaff::UStaff()
{
	Name = TEXT("직원1");

}

void UStaff::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Warning, TEXT("교직원 %s는 일을 해야합니다.ㅠ"), *Name);
}
