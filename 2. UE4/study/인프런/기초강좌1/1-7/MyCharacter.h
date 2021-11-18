// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class INFLEARN_UNREAL_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Attack();
	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool binterrupted);

private:
	// spring arm
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm; //여기서 우리가 만들어주면 cpp에서 CreateDefault로 만들어준다.

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = pawn)
	bool IsAttacking = false;

	UPROPERTY()
	class UMyAnimInstance* AnimInstance;

	UPROPERTY()
	int32 AttackIndex = 0;
};
