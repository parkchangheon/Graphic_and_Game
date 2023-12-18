// Fill out your copyright notice in the Description page of Project Settings.


#include "TTGameInstance.h"
#include "ObjectReflection/Student.h"
#include "ObjectReflection/Teacher.h"
#include "ObjectReflection/Staff.h"

#include "ObjectReflection/CourseInfo.h"
#include "ObjectReflection/GCStudent.h"
#include "ObjectReflection/StudentManager.h"

#include "Algo/Accumulate.h"


#include "UObject/UnrealType.h"


void UTTGameInstance::Init()
{
	Super::Init();

	NonPropStudent = NewObject<UGCStudent>();
	PropStudent = NewObject<UGCStudent>();

	NonPropStudents.Add(NewObject<UGCStudent>());
	PropStudents.Add(NewObject<UGCStudent>());

	StudentManager = new FStudentManager(NewObject<UGCStudent>());
}

void UTTGameInstance::Shutdown()
{
	Super::Shutdown();

	const UGCStudent* StudentInManager = StudentManager->GetStudent();

	delete StudentManager;
	StudentManager = nullptr;

	CheckUObjectIsNull(StudentInManager, TEXT("StudentInManager"));
	CheckUObjectIsValid(StudentInManager, TEXT("StudentInManager"));
	// StudentManager는 c++ 객체라, 안에있는 UObject를 관리할 수 없다.
	// UObejct를 지킬 수 있는 방법이 없다.

	//StudentManager
	//==> 방법은?		일반 C++객체가 나는 관리당할거라고 알려주는게 있다. (FGCObject를 상속받는다.)
	//그리고 두개의 함수를 Override받음 AddReferencedObjects, GetReferencerName 


	CheckUObjectIsNull(NonPropStudent, TEXT("NonPropStudent"));
	CheckUObjectIsValid(NonPropStudent, TEXT("NonPropStudent"));

	CheckUObjectIsNull(PropStudent, TEXT("PropStudent"));
	CheckUObjectIsValid(PropStudent, TEXT("PropStudent"));

	// Null이 아니다
	// Null이 아니다.

	// 유효하지 않다.
	// 유효하다.

	//고로, NonPropStudnet는 Null은 아니지만, 유효하지는 않아, 댕글링 문제가 발생가능하다.



	CheckUObjectIsNull(NonPropStudents[0], TEXT("NonPropStudents"));
	CheckUObjectIsValid(NonPropStudents[0], TEXT("NonPropStudents"));

	CheckUObjectIsNull(PropStudents[0], TEXT("PropStudents"));
	CheckUObjectIsValid(PropStudents[0], TEXT("PropStudents"));

}

void UTTGameInstance::CheckUObjectIsValid(const UObject* InObject, const FString& InTag)
{
	if (InObject->IsValidLowLevel())	//정교하게 체크 => 널포인터도 함께 체크.
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s]는 유효한 오브젝트"), *InTag);
	}
	
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s]는 유효하지 않은 오브젝트"), *InTag);
	}
}

void UTTGameInstance::CheckUObjectIsNull(const UObject* InObject, const FString& InTag)
{
	if (InObject == nullptr)	//정교하게 체크 => 널포인터도 함께 체크.
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s]는 Nullptr 오브젝트"), *InTag);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s]는 Nullptr가 아닌 오브젝트"), *InTag);
	}
}
