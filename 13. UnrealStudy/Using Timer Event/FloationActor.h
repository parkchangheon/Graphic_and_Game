// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloationActor.generated.h"

UCLASS()
class UDEMY1_API AFloationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloationActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	FVector RunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = move, meta = (AllowPrivateAccess = "true"))
	FVector floatingSpeed;

};
