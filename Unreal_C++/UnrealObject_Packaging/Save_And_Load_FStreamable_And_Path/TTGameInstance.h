// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "TTGameInstance.generated.h"



UCLASS()
class TOUCHTEST_API UTTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init()override;
	UTTGameInstance();

	// 패키지를 이용하여 저장/로딩
	void SaveStudentPackage() const;
	void LoadStudentPackage() const;

	// 경로를 이용하여 저장/로딩
	void LoadStudentObject()const;

private:
	UPROPERTY()
	TObjectPtr<class USerialize_Student> StudentSrc;

	static const FString PackageName;
	static const FString AssetName;


	//비동기 로딩
	FStreamableManager StreamableManager;
	TSharedPtr<FStreamableHandle> Handle;		//스트리밍된 애셋을 관리할 수 있는 Handler

};

