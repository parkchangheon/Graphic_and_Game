// Fill out your copyright notice in the Description page of Project Settings.


#include "TTGameInstance.h"
#include "ObjectReflection/Student.h"
#include "ObjectReflection/Teacher.h"
#include "ObjectReflection/Staff.h"

#include "ObjectReflection/CourseInfo.h"
#include "ObjectReflection/GCStudent.h"
#include "ObjectReflection/StudentManager.h"
#include "ObjectReflection/Serialize_Student.h"

#include "JsonObjectConverter.h"
#include "Algo/Accumulate.h"

#include "UObject/SavePackage.h"
#include "UObject/UnrealType.h"


const FString UTTGameInstance::PackageName = TEXT("/Game/Student");
const FString UTTGameInstance::AssetName = TEXT("TopStudent");


UTTGameInstance::UTTGameInstance()
{
	// 생성자에서 애셋을 로딩하는 것은 애셋이 게임이 시작하기 전에 메모리에 다 올라와있어야함을 뜻함.

	//const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	//static ConstructorHelpers::FObjectFinder<USerialize_Student> UASSET_TopStudent(*TopSoftObjectPath);	

	////ConstructorHelpers를 통해 애셋을 로딩했으면, .Succeeded를 통해 로딩이 잘 되었는지 확인 가능.
	//if (UASSET_TopStudent.Succeeded())
	//{
	//	PrintStudentInfo(UASSET_TopStudent.Object, TEXT("Constructor"));
	//}

}

void PrintStudentInfo(const USerialize_Student* InStudent, const FString& InTag)
{
	UE_LOG(LogTemp, Warning, TEXT("{%s} 이름 : %s, 순번 %d"), *InTag, *InStudent->GetName(), InStudent->GetOrder());
}

void UTTGameInstance::Init()
{
	Super::Init();

	// =============== 패키징 활용하는 방법 ===============
	SaveStudentPackage();
	//LoadStudentPackage();

	// =============== 경로를 이용하여 로딩하는 방법 ===============
	// Streamable Manager (애셋 스트리밍 관리자) 
	// 애셋의 비동기 로딩을 지원하는 관리자객체
	// 콘텐츠 제작과 무고나한 싱글턴 클래스에 FStreamableManager를 선언하는 것이 좋음. (Ex - GameInstance가 좋긴함)
	// FStreamableManager를 활용해 애셋의 동기/비동기 로딩을 관리할 수 있음.
	// 다수의 오브젝트 경로를 입력해 다수의 애셋을 로딩하는 것도 가능함.
	//LoadStudentObject();

	// =============== 비동기 애셋 로딩을 이용하는 방법 ===============
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	Handle = StreamableManager.RequestAsyncLoad(TopSoftObjectPath,
		[&]() {
			if (Handle.IsValid() && Handle->HasLoadCompleted())
			{
				USerialize_Student* TopStudent = Cast<USerialize_Student>(Handle->GetLoadedAsset());
				if (TopStudent)
				{
					PrintStudentInfo(TopStudent, TEXT("AsyncLoad"));

					Handle->ReleaseHandle();
					Handle.Reset();
				}
			}
		});

}

void UTTGameInstance::SaveStudentPackage() const
{
	//저장하기전에 로드할 것이 있다ㅕㄴ 로드한다.
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if (StudentPackage)
	{
		StudentPackage->FullyLoad();
	}

	//패키지 생성.
	StudentPackage = CreatePackage(*PackageName);	

	//패키지 저장옵션
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	//무엇을 담을것인가?
	//UStudent* TopStudent = NewObject<UStudent>();	//이렇게 하면 TransientPackage안에 들어가겠지만, 
	USerialize_Student* TopStudent = NewObject<USerialize_Student>(StudentPackage, USerialize_Student::StaticClass(), *AssetName, ObjectFlag);	//이런 방식이라면 StudentPackage에 넣기 가능
	//==> 언리얼 오브젝트를 생성했다.

	TopStudent->SetName(TEXT("NewPackage_Parker"));
	TopStudent->SetOrder(99);

	const int32 NumoSubs = 10;
	for (int ix = 1; ix <= NumoSubs; ++ix)
	{
		FString SubObjectName = FString::Printf(TEXT("Student%d"), ix);
		USerialize_Student* SubStudent = NewObject<USerialize_Student>(TopStudent, USerialize_Student::StaticClass(), *SubObjectName, ObjectFlag);
		SubStudent->SetName(FString::Printf(TEXT("학생 %d"), ix));
		SubStudent->SetOrder(ix);
	}

	//UAsset에 대한 
	const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	
	//저장옵션
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;

	if (UPackage::SavePackage(StudentPackage, nullptr, *PackageFileName, SaveArgs))
	{
		UE_LOG(LogTemp, Log, TEXT("패키지가 성공적으로 저장됨"));
	}

}

void UTTGameInstance::LoadStudentPackage() const
{
	// 패키지를 로딩하고,
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if(StudentPackage==nullptr)
	{ 
		UE_LOG(LogTemp, Log, TEXT("패키지를 찾을 수 없습니다."));
		return;
	}

	StudentPackage->FullyLoad();

	//로딩된 패키지에서 Asset이름으로 USerialize_Student를 찾아서 출력함.
	USerialize_Student* TopStudent = FindObject<USerialize_Student>(StudentPackage, *AssetName);
	PrintStudentInfo(TopStudent, TEXT("Find Object Asset "));
}

void UTTGameInstance::LoadStudentObject() const
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	USerialize_Student* TopStudent = LoadObject<USerialize_Student>(nullptr, *TopSoftObjectPath);
	PrintStudentInfo(TopStudent, TEXT("Load Object Asset "));

}
