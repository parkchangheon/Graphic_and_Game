// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

// 리플렉션 기능... 언리얼에는 리플렉션이 없어서 야매로 만들어준것 
//언리얼 매크로다라는 것을 알려줌
UCLASS() 

class INFLEARN_UNREAL_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category=BattleStat)
	int32 Hp;
	UPROPERTY(EditAnywhere, Category = BattleStat)
	int32 Mp;

};
