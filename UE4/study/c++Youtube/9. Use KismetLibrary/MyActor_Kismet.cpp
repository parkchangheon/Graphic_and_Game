// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor_Kismet.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AMyActor_Kismet::AMyActor_Kismet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	RootComponent = MyMesh;
}

// Called when the game starts or when spawned
void AMyActor_Kismet::BeginPlay()
{
	Super::BeginPlay();
	MyMesh->SetRelativeRotation(/*GetRandomRotator()==>*/ UKismetMathLibrary::RandomRotator());
}

// Called every frame
void AMyActor_Kismet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//FRotator AMyActor_Kismet::GetRandomRotator()
//{
//	FRotator MyRandomRotator = FRotator(0.f, 0.f, 0.f);
//	MyRandomRotator.Pitch = FMath::FRandRange(0.f, 360.f); //y축 회전
//	MyRandomRotator.Yaw = FMath::FRandRange(0.f, 360.f);   // z축 회전
//	MyRandomRotator.Roll = FMath::FRandRange(0.f, 360.f);  // x 축 회전
//
//	return MyRandomRotator;
//}
//=> 이걸 kismet처리
