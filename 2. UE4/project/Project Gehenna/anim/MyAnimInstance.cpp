// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"


UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/LeeAnimation/Attack_Mon.Attack_Mon'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size(); // pawn의 speed를 적용

		auto Character = Cast<ACharacter>(Pawn);

		if (Character)
		{
			IsFalling = Character->GetMovementComponent()->IsFalling();
		}
	}


}

void UMyAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.f);
	}
}
