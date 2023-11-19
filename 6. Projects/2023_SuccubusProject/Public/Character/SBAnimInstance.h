// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SBAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SUCCUBUSAD_API USBAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	class ASBCharacter* SuccubusCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* SuccubusCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category=Movement)
	float BasicSpeed;

	UPROPERTY(BlueprintReadOnly, Category=Movement)
	bool IsFalling;
};
