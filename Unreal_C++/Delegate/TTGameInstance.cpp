// Fill out your copyright notice in the Description page of Project Settings.


#include "TTGameInstance.h"
#include "ObjectReflection/Student.h"
#include "ObjectReflection/Teacher.h"
#include "ObjectReflection/Staff.h"

#include "ObjectReflection/CourseInfo.h"

#include "UObject/UnrealType.h"

UTTGameInstance::UTTGameInstance()
{
	SchoolName = TEXT("기본 학교"); //CDO 템플릿 객체에 저장됨.
}


void UTTGameInstance::Init()
{
	Super::Init();

	//생성한 객체는 멤버변수로 들어가서, 관리를 받는데, 특별한 일이 없는한 메모리를 들고 있는다.
	CourseInfo = NewObject<UCourseInfo>(this);
	//CourseInfo는 GameInstance의 서브 오브젝트가 된다.
	//GameInstance는 CourseInfo의 Outer가 된다.

	UStudent* Student1 = NewObject<UStudent>();	//자동으로 소멸되어, Outer 설정 x
	Student1->SetName(TEXT("학생1"));
	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("학생2"));
	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("학생3"));

	// 클래스 인스턴스를 지정하고 멤버 변수를 직접 묶을 수 가 있다.
	CourseInfo->CourseInfoOnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->CourseInfoOnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->CourseInfoOnChanged.AddUObject(Student3, &UStudent::GetNotification);

	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("수강신청 시간이 변경되었습니다."));
}