// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Cplus_Inter.h"

// Sets default values
ABP_Cplus_Inter::ABP_Cplus_Inter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<APawn> BpClass(TEXT("Blueprint'/Game/Map/Interaction/BP_C++_Interact/Bp_TestClass.Bp_TestClass'")); //<> 꺽쇠는 블루프린트 타입을 넣어주는것
	
	if (BpClass.Succeeded() && BpClass.Class != NULL)
	{
		// BpClass.Class->필요한 함수를 가져온다.
	}

	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT(""));
	if (MeshAsset.Succeeded() && MeshAsset.Object != NULL)
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void ABP_Cplus_Inter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABP_Cplus_Inter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

