// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class TUTORIAL_OF_C_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(EditAnywhere)
		UShapeComponent* Root;
	// 변수? 언리얼 리플렉션 시스템에 해당 프로퍼티가 있음을 알림
	// 리플렉션은 프로그램이 실행시간에 자기자신을 조사하는 기능.

	UPROPERTY(EditAnywhere) // 선언된 u 자형 구성 요소 경로는 우리가 있는 속성의 어느 곳에서나 편집기로 사용된다.
		UStaticMeshComponent* MyMesh;

	float RunningTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
