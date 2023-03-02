// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Particles/ParticleSystemComponent.h>
#include "FireEvent.generated.h"

UCLASS()
class UDEMY1_API AFireEvent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void AddFuel();

public:


	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* particleSystem;

	FTimerHandle fireTimer;
	bool bfire;

	int8 fireDeltaTime;

	UFUNCTION(BlueprintCallable)
	void OffFire();

};
