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

	tBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root")); //하위 개체를 만든다. 구성요소는 상자다
	tBox->SetGenerateOverlapEvents(true); // Box->bGenerateOverlapEvents=true;
	tBox->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::TriggerEnter);

	tBox->SetRelativeScale3D(BoxSize);
	RootComponent = tBox;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->AttachTo(RootComponent);//MyMesh를 RootComponent와 연결시킨다.

	//정적메쉬를 박스개체에 연결. staticMesh가 게임에서 눈에 보이는것
	//정적 메쉬는 액터를 위한 모델일뿐.

	SpeedScale = 0.0f;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);  //DeltaTime은 마지막 프레임에서 게임에서 흐른시간

	FVector NewLocation = GetActorLocation(); // 액터의 위치를 얻는다.
	float DeltaHeight = (FMath::Sin(RunningTime+DeltaTime)-FMath::Sin(RunningTime));
	//sin을 사용하는 이유는 -1~ 1사이에 변동하는 값으로 구를 이동시킬 수 있기 때문에?
	//1을 치고 다시 -1을 치고, 1을 치고...액터를 위아래로 움직이게 할 수 있으므로...

	//이건 어느 방향으로 보낼지?
	//NewLocation.Z += DeltaHeight * 20.0f; #2강에서 쓰임
	NewLocation.Y += DeltaHeight * SpeedScale;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}


void AMyActor::TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector PlayerStartingLocation = FVector(-350.0f, -100.0f, 235.0f);   //플레이어의 시작 위치를 지정하는데, 후에 메쉬들과 충돌 후에 돌아오기 편하기 위해 설정.
	//플레이어가 돌과 부딫혔을때 다시 스타팅 포인트로 돌아가도록한다.
	OtherActor->SetActorLocation(PlayerStartingLocation);
}
