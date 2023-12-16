// Fill out your copyright notice in the Description page of Project Settings.


#include "TTGameInstance.h"
#include "ObjectReflection/Student.h"
#include "ObjectReflection/Teacher.h"
#include "ObjectReflection/Staff.h"

#include "ObjectReflection/CourseInfo.h"
#include "Algo/Accumulate.h"

#include "UObject/UnrealType.h"

UTTGameInstance::UTTGameInstance()
{
	SchoolName = TEXT("기본 학교"); //CDO 템플릿 객체에 저장됨.
}


FString UTTGameInstance::MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상해지성");
	TCHAR LastChar[] = TEXT("수은원연");

	TArray<TCHAR> RandomArray;
	RandomArray.SetNum(3);
	RandomArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandomArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandomArray[2] = LastChar[FMath::RandRange(0, 3)];


	return RandomArray.GetData();
}


void UTTGameInstance::Init()
{
	Super::Init();

	//생성한 객체는 멤버변수로 들어가서, 관리를 받는데, 특별한 일이 없는한 메모리를 들고 있는다.
	//CourseInfo = NewObject<UCourseInfo>(this);
	////CourseInfo는 GameInstance의 서브 오브젝트가 된다.
	////GameInstance는 CourseInfo의 Outer가 된다.

	//UStudent* Student1 = NewObject<UStudent>();	//자동으로 소멸되어, Outer 설정 x
	//Student1->SetName(TEXT("학생1"));
	//UStudent* Student2 = NewObject<UStudent>();
	//Student2->SetName(TEXT("학생2"));
	//UStudent* Student3 = NewObject<UStudent>();
	//Student3->SetName(TEXT("학생3"));

	//// 클래스 인스턴스를 지정하고 멤버 변수를 직접 묶을 수 가 있다.
	//CourseInfo->CourseInfoOnChanged.AddUObject(Student1, &UStudent::GetNotification);
	//CourseInfo->CourseInfoOnChanged.AddUObject(Student2, &UStudent::GetNotification);
	//CourseInfo->CourseInfoOnChanged.AddUObject(Student3, &UStudent::GetNotification);

	//CourseInfo->ChangeCourseInfo(SchoolName, TEXT("수강신청 시간이 변경되었습니다."));


	/*const int32 Arraynum = 10;
	TArray<int32> Int32Arr;

	for (int32 ix = 0; ix < Arraynum; ix++)
	{
		Int32Arr.Emplace(ix);
	}
	
	Int32Arr.RemoveAll([](int32 Val) {return Val % 2 == 0; });
	Int32Arr += {2, 4, 6, 8, 10};


	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1,3,5,7,9,2,4,6,8,10 };
	Int32ArrayCompare.AddUninitialized(Arraynum);
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * Arraynum);

	ensure(Int32Arr == Int32ArrayCompare);


	int32 Sum=55;
	int32 SumByAlgo = Algo::Accumulate(Int32Arr, 0);
	ensure(Sum == SumByAlgo);*/


	const int32 StudentNum = 300;

	for (int ix = 0; ix < StudentNum; ix++)
	{
		//구조체 배열이니까, 구조체 형식으로 만들어서 넣음.
		StudentData.Emplace(FStudentData(MakeRandomName(), ix));	
	}

	TArray<FString> AllStudentsNames;
	Algo::Transform(StudentData, AllStudentsNames, 
		[](const FStudentData& val) 
		{
			return val.Name;
		}
	);

	//  TArray<FStudentData>  ==>  TArray<FString> 로 넣는데 어떻게 넣느냐? 세번째 인자의 조건으로 넣는다?


	TSet<FString> AllUniqueNames; 
	Algo::Transform(StudentData, AllUniqueNames,
		[](const FStudentData& val)
		{
			return val.Name;
		}
	);



	//언리얼 TMap은 TSet의 구조로 구현되어있는데, 
	// key - value 구성의 튜플로 구성되어있다.	==> 
	// 해시테이블 형태로 구축되어 있어 빠른 검색이 가능함.
	// 동적 배열의 형태로 데이터가 모여있음.
	// 데이터를 빠르게 순회 가능.
	// 데이터 삭제해도 재구축이 일어나지 않음.
	// 비어 있는 데이터가 있을 수 있음.
	// TMultiMap을 사용하면 중복 데이터를 관리할 수 있음.


	Algo::Transform(StudentData, StudentsMap,
		[](const FStudentData& val)
		{
			return TPair<int32, FString>(val.Order, val.Name);
		}
	);


	TMap<FString, int32> StudnetsMapByUniqueName;
	Algo::Transform(StudentData, StudentsMap,
		[](const FStudentData& val)
		{
			return TPair<FString, int32>(val.Name, val.Order);
		}
	);

	TMultiMap<FString, int32> StudentsMapByName;
	Algo::Transform(StudentData, StudentsMap,
		[](const FStudentData& val)
		{
			return TPair<FString, int32>(val.Name, val.Order);
		}
	);

	const FString TargetName(TEXT("이혜은"));
	TArray<int32> AllOrders;
	StudentsMapByName.MultiFind(TargetName, AllOrders);

	UE_LOG(LogTemp, Warning, TEXT("이름이 %s인 학생의 수 : %d"), *TargetName, AllOrders.Num());

}