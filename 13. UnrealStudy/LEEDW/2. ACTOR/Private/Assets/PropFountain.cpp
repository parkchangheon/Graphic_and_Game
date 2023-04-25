// Fill out your copyright notice in the Description page of Project Settings.


#include "Assets/PropFountain.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APropFountain::APropFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATER"));
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
	Splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPLASH"));

	RootComponent = Body;
	Water->SetupAttachment(Body);
	Light->SetupAttachment(Body);
	Splash->SetupAttachment(Body);


	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f));
	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));
	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));

	//게임에서 생성자 코드가 여러번 호출 될때마다, 지역변수를 초기화하는건 비효율적이기에 static 선언
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BODY(TEXT("StaticMesh'/Game/StarterContent/Props/SM_TableRound.SM_TableRound'"));
	if (SM_BODY.Succeeded())
	{
		Body->SetStaticMesh(SM_BODY.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_RING(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
	if (SM_RING.Succeeded())
	{
		Water->SetStaticMesh(SM_RING.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem>SM_PARTICLE(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	if (SM_PARTICLE.Succeeded())
	{
		Splash->SetTemplate(SM_PARTICLE.Object);
	}
}

// Called when the game starts or when spawned
void APropFountain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APropFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

