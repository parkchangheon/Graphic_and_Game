// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectReflection/Person.h"

UPerson::UPerson()
{
	Name = TEXT("홍길동");
	Year = 1;
}

void UPerson::DoLesson()
{
	UE_LOG(LogTemp, Log, TEXT("%s 님이 수업에 참여합니다."), *Name);
}

