// Fill out your copyright notice in the Description page of Project Settings.
//DeltaTime 이랑 Fstring으로 객체명 받아오는 것 까지 진행하였음.
// FTransform -> 구조체 관련 (F 키워드는 구조체이다) 

#include "DeltaTime_Tutorial.h"

// Sets default values
ADeltaTime_Tutorial::ADeltaTime_Tutorial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADeltaTime_Tutorial::BeginPlay()
{
	Super::BeginPlay();
	FString ActorName = GetName(); //FString 형식을 받는다 GetName이 아니라 GetActorLabel을 하면 띄워쓰기가 적용된다.
	UE_LOG(LogTemp, Warning, TEXT("MY Name is %s"), *ActorName);
	// -------------------------------------------------------------------------

	//FTransform 사용법
	FTransform ActorTransform = GetTransform(); // 
	ActorTransform.GetRotation();//GetScale3D , Location... 기타 등등을 얻을 수 있음. (Transform에 있는 것들)

	UE_LOG(LogTemp, Warning, TEXT("Location X=  %.3f"), ActorTransform.GetRotation().X);
}

// Called every frame
void ADeltaTime_Tutorial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //DeltaTime은 30FPS 이면 1/30 => 0.0333마다 ~ 
	FVector NewLocation = GetActorLocation();

	NewLocation.Z += SpeedDelta * DeltaTime;
	SetActorLocation(NewLocation);
}

