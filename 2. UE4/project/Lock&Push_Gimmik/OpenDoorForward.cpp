// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoorForward.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AOpenDoorForward::AOpenDoorForward()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Open = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MY BOX COMPONENT"));
	BoxComponent->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	RootComponent = BoxComponent;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MY Door"));
	Door->SetRelativeLocation(FVector(0.0f, 50.0f, -50.0f)); // 피벗 위치 변경?
	Door->SetupAttachment(RootComponent);


	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AOpenDoorForward::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AOpenDoorForward::OnOverlapEnd);

}


// Called when the game starts or when spawned
void AOpenDoorForward::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOpenDoorForward::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DoorRotation = Door->RelativeRotation;
	if (Open)
	{
		Door->SetRelativeRotation(FMath::Lerp(FQuat(DoorRotation), FQuat(FRotator(0.0f, RotateValue, 0.0f)), 0.01));
	}
	else
	{
		Door->SetRelativeRotation(FMath::Lerp(FQuat(DoorRotation), FQuat(FRotator(0.0f, 0.0f, 0.0f)), 0.01));
	}
}

void AOpenDoorForward::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		FVector PawnLocation = OtherActor->GetActorLocation();
		FVector Direction = GetActorLocation()-PawnLocation;
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

void AOpenDoorForward::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Open=false;
	}
}