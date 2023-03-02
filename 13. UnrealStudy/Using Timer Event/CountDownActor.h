// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Components/TextRenderComponent.h>
#include "CountDownActor.generated.h"

UCLASS()
class UDEMY1_API ACountDownActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountDownActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
	int32 CountdownTime;
	UTextRenderComponent* CountdownText;

	void UpdateTimerDisplay();
	void AdvanceTimer();

	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();
	virtual void CountdownHasFinished_Implementation();
	FTimerHandle CountdownTimerHandle;
	
};
