// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/Revenant_Skeleton_Montage.Revenant_Skeleton_Montage'"));
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
		Speed = Pawn->GetVelocity().Size();
	}

	auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			isFalling = Character->GetMovementComponent()->IsFalling();

		}
}

//캐릭터에서 역으로 호출함.
void UMyAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))//중복 실행 방지. 이미 실행중이면 작동 x
	{
		Montage_Play(AttackMontage, 1.f);
	}
}