// Fill out your copyright notice in the Description page of Project Settings.


#include "TTGameInstance.h"
#include "ObjectReflection/Student.h"
#include "ObjectReflection/Teacher.h"
#include "ObjectReflection//Staff.h"

#include "UObject/UnrealType.h"

UTTGameInstance::UTTGameInstance()
{
	SchoolName = TEXT("기본 학교"); //CDO 템플릿 객체에 저장됨.
}


void UTTGameInstance::Init()
{
	Super::Init();

	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>() };

	for (const auto Person : Persons)
	{
		UE_LOG(LogTemp,Warning,TEXT("구성원 이름 : %s"), *Person->GetName())
	}

	for (const auto Person : Persons)
	{
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);
		if (LessonInterface)
		{
			LessonInterface->DoLesson(); 
		}
		
	}

}