// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Kismet/KismetMathLibrary.h"
#include <Runtime/Engine/Private/PlayerController.cpp>



// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Open = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MY BOX COMPONENT"));
	BoxComponent->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	RootComponent = BoxComponent;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MY DOOR"));
	Door->SetRelativeLocation(FVector(0.f, 50.f, -50.f));
	Door->SetupAttachment(RootComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);


}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorRotation = Door->GetRelativeRotation();
	if (Open)
	{
		Door->SetRelativeRotation(FMath::Lerp(FQuat(DoorRotation), FQuat(FRotator(0.0f, RotateValue, 0.0f)), 0.01));
	}
	else
	{
		Door->SetRelativeRotation(FMath::Lerp(FQuat(DoorRotation), FQuat(FRotator(0.0f, 0.0f, 0.0f)), 0.01));
	}
	
}



void ADoor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerController::IsInputKeyDown(FKey(FName("E") {

	}

	// 여기에 캐릭터가 E키를 눌렀을때를 조건으로 넣어준다. 

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		FVector PawnLocation = OtherActor->GetActorLocation();
		FVector Direction = GetActorLocation() - PawnLocation;
		Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());//a를 리턴하되 b의 역을

		if (Direction.X > 0.0f)
		{
			RotateValue = 90.0f;
		}
		else
		{
			RotateValue = -90.0f;
		}
		Open = true;
	}
}


void ADoor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Open = false;
	}
}