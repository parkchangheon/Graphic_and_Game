// Fill out your copyright notice in the Description page of Project Settings.


#include "Furniture_RL.h"

// Sets default values
AFurniture_RL::AFurniture_RL()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFurniture_RL::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFurniture_RL::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location_RL = GetActorLocation();

	Location_RL.X += 20 * DeltaTime;
	SetActorLocation(Location_RL);
}



//UPROPERTY는 매크로이다
//언리얼 에디터에서 변수값을 바꿀 수 있게 해준다
// 게임 프로그래밍 지식이 없는 디자이너가 사용하기 편하게 한다.
