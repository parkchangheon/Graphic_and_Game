// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

int UMyBlueprintFunctionLibrary::EasyPlus(int a, int b)
{
	int c = a + b;

	UE_LOG(LogTemp, Log, TEXT("result = %d"), c);

	return c;
}


// constructorHelpers 클래스는 생성자에서 클래스를 초기화하는데 도움을 주는 클래스이다.
// 콘텐츠 브라우저의 리소스나 블루 프린트 클래스를 불러오는 작업을 도와주는 기능을 가지고 있다.
// 생성자 이외의 함수에서는 에러가 발생한다.


