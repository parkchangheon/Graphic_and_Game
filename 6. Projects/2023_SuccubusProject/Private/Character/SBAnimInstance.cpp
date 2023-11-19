// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SBAnimInstance.h"
#include "Character/SBCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USBAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SuccubusCharacter = Cast<ASBCharacter>(TryGetPawnOwner());

	if (SuccubusCharacter)
	{
		SuccubusCharacterMovement = SuccubusCharacter->GetCharacterMovement();
		SuccubusCharacterMovement->JumpZVelocity = 800.0f;
	}
}

void USBAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (SuccubusCharacterMovement)
	{
		BasicSpeed = UKismetMathLibrary::VSizeXY(SuccubusCharacterMovement->Velocity);
		IsFalling = SuccubusCharacterMovement->IsFalling();
	}

	

}
