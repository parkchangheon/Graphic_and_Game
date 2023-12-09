// Fill out your copyright notice in the Description page of Project Settings.


#include "TTGameInstance.h"
#include "ObjectReflection/Student.h"
#include "ObjectReflection/Teacher.h"
#include "UObject/UnrealType.h"

UTTGameInstance::UTTGameInstance()
{
	SchoolName = TEXT("기본 학교"); //CDO 템플릿 객체에 저장됨.
}


void UTTGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("==========================="));
	UClass* ClassRuntime = GetClass();								// 런타임에서 얻어올 수 있다.
	UClass* ClassCompileTime = UTTGameInstance::StaticClass();		// 컴파일 타임에서 얻어올 수 있다.

	//check(ClassRuntime == ClassCompileTime);	//에디터가 종료가 된다.
	//ensure(ClassRuntime == ClassCompileTime);	//에디터가 종료되진 않는다.
	//ensureMsgf(ClassRuntime == ClassCompileTime, TEXT("It Is ensureMSgf Stop Lock")); //메세지를 출력함.

	SchoolName = TEXT("인천대학교");	//해당 이름이 저장되어있다.
	UE_LOG(LogTemp, Warning, TEXT("학교 이름 : %s"), *SchoolName);
	UE_LOG(LogTemp, Warning, TEXT("학교 이름 CDO 버전 : %s"), *GetClass()->GetDefaultObject<UTTGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Warning, TEXT("==========================="));

	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	Student->SetName(TEXT("새로운 학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름은 : %s 입니다."), *Student->GetName());


	/*FString CurrentTeacherName;
	FString NewTeacherName(TEXT("새로운 선생님 3"));
	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));

	
	if (NameProp)
	{
		NameProp->GetPropertyValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Warning, TEXT("현재 선생님 이름 : %s "), *CurrentTeacherName);

		NameProp->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(LogTemp, Warning, TEXT("새로운 선생님 이름 : %s "), *Teacher->GetName());

	}*/

	UE_LOG(LogTemp, Warning, TEXT("==========================="));

	Student->DoLesson();
	UFunction* DoLessonLec = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonLec)
	{
		Teacher->ProcessEvent(DoLessonLec, nullptr);
	}



}