// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyingFurniture.generated.h" //항상 마지막 줄에 선언

UCLASS()  // 매크로이고, 언리얼 오브젝트임을 선언하기 위함
class BASIC_C_TUTORIAL_API AFlyingFurniture : public AActor
{
	// A~ 플라잉 퍼니쳐 같이 접두사를 써주어, 표기 (Actor - A)
	// 접두사는 크게 A랑 U가 사용되며, A는 액터, U는 클래스.
	GENERATED_BODY() // 해당 클래스가 언리얼 오브젝트임을 선언하기 위함.
	
public:	
	// Sets default values for this actor's properties
	AFlyingFurniture();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; //오버라이딩한다.

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; // 틱은 매 게임 프레임마다 선언 30FPS는 1초마다 30번 호출

};
