// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraUtility.generated.h"

UCLASS()
class TUTORIAL_OF_C_API ACameraUtility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraUtility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		AActor* CameraOne;

	UPROPERTY(EditAnywhere)
		AActor* CameraTwo;

	// 카메라 객체 2개에 대한 선언을 한다.


	float TimeToNextCameraChange;  // 카메라 전환 사이에 초가 있다. 그것을 위한 변수 선언.

};
