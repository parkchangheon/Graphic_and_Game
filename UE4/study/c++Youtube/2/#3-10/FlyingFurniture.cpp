// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingFurniture.h"
FVector NewLocation;
int Start;
int End;
bool flag = true;


// Sets default values
AFlyingFurniture::AFlyingFurniture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;  // Tick 함수가 매 프레임마다 호출될거란거다.

}

// Called when the game starts or when spawned
void AFlyingFurniture::BeginPlay()
{
	Super::BeginPlay();  //BeginPlay는 가상함수이다.  이 함수를 재정의하는 기능을 가지고 있다.
	// 즉 상위 BeingPlay에서 모든 함수들을 호출해온다.
	int Number = 10;
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay() has called!!"));
	UE_LOG(LogTemp, Warning, TEXT("Number value is %d"),Number);
	/*UE_LOG는 c++ 매크로로,
		게임이 실행될때, 메시지를 logging 하고 sending 하는 역할을 한다.

		왜 쓸모가 있나 ?
		-checking if some method / finction is being called
		- looking at some data during gameplay*/



	
	/* // 튜토리얼1 과제 파트(하드)
	NewLocation = GetActorLocation();
	Start = NewLocation.Z;
	End = NewLocation.Z + 200;
	*/
}

// 기본
//// Called every frame
//void AFlyingFurniture::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	FVector NewLocation = GetActorLocation(); //FVector형태로 반환
//	// NewLocation.Z += 20; => 그냥 이대로만 선언하면 프레임 마다 20씩 증가하므로 30프레임에선 600, 60프레임에선 1200 증가한다
//	//해결책->
//	NewLocation.Z += 20 * DeltaTime; //Deltatime을 쓰면 해결..
//	//액터의 위치 설정 방법
//	SetActorLocation(NewLocation);
//
//	
//
//	// 해당 코드는 일정한 시간에 하늘로 올라가는 가구들을 볼 수 있다.
//}




void AFlyingFurniture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (flag==true) {
		NewLocation.Z += 20 * DeltaTime;
		if (NewLocation.Z >= End)
			flag = false;
	}

	if (flag == false) {
		NewLocation.Z -= 20 * DeltaTime;
		if (NewLocation.Z <= Start) {
			flag = true;
		}
	}

	
	SetActorLocation(NewLocation);

	//UE_LOG(LogTemp, Warning, TEXT("EverySingleTime!!"));



}

