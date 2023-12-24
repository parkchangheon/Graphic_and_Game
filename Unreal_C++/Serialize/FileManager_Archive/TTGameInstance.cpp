// Fill out your copyright notice in the Description page of Project Settings.


#include "TTGameInstance.h"
#include "ObjectReflection/Student.h"
#include "ObjectReflection/Teacher.h"
#include "ObjectReflection/Staff.h"

#include "ObjectReflection/CourseInfo.h"
#include "ObjectReflection/GCStudent.h"
#include "ObjectReflection/StudentManager.h"
#include "ObjectReflection/Serialize_Student.h"

#include "Algo/Accumulate.h"


#include "UObject/UnrealType.h"

void PrintStudentInfo(const USerialize_Student* InStudent, const FString& InTag)
{
	UE_LOG(LogTemp, Warning, TEXT("{%s} 이름 : %s, 순번 %d"), *InTag, *InStudent->GetName(), InStudent->GetOrder());
}


UTTGameInstance::UTTGameInstance()
{


}

void UTTGameInstance::Init()
{
	Super::Init();
	
	FStudentData RawDataSrc(34, "박창헌");
	const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	UE_LOG(LogTemp, Warning, TEXT(" 저장할 파일 폴더 : %s"), *SavedDir); //C:\TOUCH\touchtest\Saved

	{
		//이렇게만 하면 제대로 나오진 않음.
		const FString RawDataFileName(TEXT("RawData.bin"));
		FString RawDataAbsolutePath = FPaths::Combine(SavedDir, *RawDataFileName);
		UE_LOG(LogTemp, Warning, TEXT(" 저장할 파일 폴더 전체 경로 : %s"), *RawDataAbsolutePath);
		
		//MakeStandardFileName을 거쳐서 제대로된 절대경로로 바꿔줌
		FPaths::MakeStandardFilename(RawDataAbsolutePath);
		UE_LOG(LogTemp, Warning, TEXT(" 변경할 파일 폴더 전체 경로 : %s"), *RawDataAbsolutePath);

		//RawData.bin 를 쓸 수 있는 Achive파일
		FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);
		if (RawFileWriterAr)
		{
			*RawFileWriterAr << RawDataSrc;	//파일전송.
			RawFileWriterAr->Close();
			delete RawFileWriterAr;
			RawFileWriterAr = nullptr;
		}

		FStudentData RawDataDest;
		FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);
		if (RawFileReaderAr)
		{
			*RawFileReaderAr << RawDataDest;
			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("[RawData] 이름 %s 순번 %d"), *RawDataDest.Name, RawDataDest.Order);
		}
	}

	StudentSrc = NewObject<USerialize_Student>();
	StudentSrc->SetName(TEXT("Park Chang Heon"));
	StudentSrc->SetOrder(60);


	{
		const FString ObjectDataFileName(TEXT("ObjectData.bin"));
		FString ObjectDataAbsolutePath = FPaths::Combine(*SavedDir, *ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

		// 메모리에 언리얼 오브젝트를 저장.
		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriterAr(BufferArray);
		StudentSrc->Serialize(MemoryWriterAr);

		if (TUniquePtr<FArchive> FileWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath)))
		{
			*FileWriterAr << BufferArray;
			FileWriterAr->Close();
		}


		TArray<uint8> BufferArrayFromFile;
		if (TUniquePtr<FArchive> FileReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath)))
		{
			*FileReaderAr << BufferArrayFromFile;	//버퍼의 파일 내용이 Reader에 담기게 됨
			FileReaderAr->Close();
		}

		FMemoryReader MemoryReaderAr(BufferArrayFromFile);
		USerialize_Student* StudentDst = NewObject<USerialize_Student>();
		StudentDst->Serialize(MemoryReaderAr);
		PrintStudentInfo(StudentDst, TEXT("ObjectData"));
	}



}

void UTTGameInstance::Shutdown()
{
	Super::Shutdown();
	

}
