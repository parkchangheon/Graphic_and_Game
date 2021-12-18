// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact_testDoor.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetMathLibrary.h>
#include "TPS_C_ProjectCharacter.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"


AInteract_testDoor::AInteract_testDoor()
{
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	RootComponent = Door;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Door.SM_Door'"));
	
	if (DoorAsset.Succeeded())
	{
		Door->SetStaticMesh(DoorAsset.Object);
	}

	DoorCurrentRotation = 0.0f;
}


void AInteract_testDoor::BeginPlay()
{
	Super::BeginPlay();

	IsDoorclosed = true;
}



void AInteract_testDoor::Interact()
{
	if (IsDoorclosed) // 문이 닫힌 상태
	{
		//interact 하자마자 문이 열리게끔 코드를 짠다.
		//캐릭터 벡터 받아서 문이 열리는 방향을 조절하고 
		// 문이 열린다.
		float dot; // 내적 벡터 반환 float

		FVector vec;
		FTimerHandle WaitHandle;
		float WaitTime = 5.0f;

		AActor* character = GetWorld()->GetFirstPlayerController()->GetPawn();

		vec = character->GetActorLocation() - GetActorLocation();//GetActorLocation  //
		vec.Normalize(); // 정규화된 법선 벡터를 출력
		auto forwardvector = GetActorForwardVector();


		dot = FVector::DotProduct(forwardvector, vec);

		float delta = GetWorld()->DeltaTimeSeconds;
		float yawDelta = 0;
		FQuat QuatRotation;

		if (dot >= 0)
		{
			yawDelta = -90;
			QuatRotation = FQuat(FRotator(0, yawDelta, 0));
			AddActorWorldRotation(QuatRotation, false, 0, ETeleportType::None);
			UE_LOG(LogTemp, Warning, TEXT("right"));
		}


		else
		{
			yawDelta = 90;
			QuatRotation = FQuat(FRotator(0, yawDelta, 0));
			AddActorWorldRotation(QuatRotation, false, 0, ETeleportType::None);
			UE_LOG(LogTemp, Warning, TEXT("left"));

		}

		// IsDoorclosed = false;
		// yawDelta = -yawDelta;
		// 타이머로 interact 한뒤에 5초뒤에 문이 닫히게끔 코드 작성
		
		IsDoorclosed = false;

		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				QuatRotation = FQuat(FRotator(0, -yawDelta, 0));
				SetActorRotation(QuatRotation);

				UE_LOG(LogTemp, Warning, TEXT("Door close"));
				IsDoorclosed = true;

			}), WaitTime, false);

	}
	
}