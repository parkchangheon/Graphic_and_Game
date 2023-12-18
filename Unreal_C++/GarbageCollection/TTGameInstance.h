// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TTGameInstance.generated.h"


UCLASS()
class TOUCHTEST_API UTTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	
	virtual void Init()override;
	virtual void Shutdown()override;
	void CheckUObjectIsValid(const UObject* InObject, const FString& InTag);
	void CheckUObjectIsNull(const UObject* InObject, const FString& InTag);

private:

	TObjectPtr<class UGCStudent> NonPropStudent;

	UPROPERTY()
	TObjectPtr<class UGCStudent> PropStudent;


	TArray<TObjectPtr<class UGCStudent>> NonPropStudents;

	UPROPERTY()
	TArray<TObjectPtr<class UGCStudent>> PropStudents;


	//일반 CPP는 어떻게..?
	class FStudentManager* StudentManager = nullptr;


};

