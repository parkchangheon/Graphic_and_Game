// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h" // 엔진미니멀 헤더로 바꾼다
#include "GameFramework/Character.h"
#include "ARPlayer.generated.h"

UCLASS()    
class TUTORIAL_CHARACTER_API AARPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARPlayer();


protected:
	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* Arm;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
