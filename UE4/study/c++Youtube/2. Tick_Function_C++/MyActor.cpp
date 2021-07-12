// Fill out your copyright notice in the Description page of Project Settings.

#include "tutorial_of_c.h"
#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "WorldCollision.h"
#include "PrimitiveViewRelevance.h"
#include "PrimitiveSceneProxy.h"
#include "SceneManagement.h"
#include "PhysicsEngine/BoxElem.h"
#include "PhysicsEngine/BodySetup.h"
#include "PrimitiveSceneProxy.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; //틱기능을 사용한다.

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root")); //하위 개체를 만든다. 구성요소는 상자다
	RootComponent = Root;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->AttachTo(RootComponent);//MyMesh를 RootComponent와 연결시킨다.

	//정적메쉬를 박스개체에 연결. staticMesh가 게임에서 눈에 보이는것
	//정적 메쉬는 액터를 위한 모델일뿐.


}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation(); // 액터의 위치를 얻는다.
	float DeltaHeight = (FMath::Sin(RunningTime+DeltaTime)-FMath::Sin(RunningTime));
	//sin을 사용하는 이유는 -1~ 1사이에 변동하는 값으로 구를 이동시킬 수 있기 때문에?
	//1을 치고 다시 -1을 치고, 1을 치고...액터를 위아래로 움직이게 할 수 있으므로...

	//이건 어느 방향으로 보낼지?
	NewLocation.Z += DeltaHeight * 20.0f; 
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);


}

