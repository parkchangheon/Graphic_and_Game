// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyCharacter.h"

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

	auto Character = Cast<AMyCharacter>(Pawn);
		if (Character)
		{
			isFalling = Character->GetMovementComponent()->IsFalling();
			Vertical = Character->UpDownValue;
			Horizontal = Character->LeftRightValue;
		}
}

//캐릭터에서 역으로 호출함.
void UMyAnimInstance::PlayAttackMontage()
{
	//if (!Montage_IsPlaying(AttackMontage))//중복 실행 방지. 이미 실행중이면 작동 x
	// 위는 OnAttacking Ended를 사용함으로써, 필요가 없어졌다.

	Montage_Play(AttackMontage, 1.f); // 몽타주 재생
}

void UMyAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage);
}

FName UMyAnimInstance::GetAttackMontageName(int32 SectionIndex) //0 1 2 몽타주가 들어온다.
{
	return FName(*FString::Printf(TEXT("Attack%d"),SectionIndex));
}

void UMyAnimInstance::AnimNotify_AttackHit()
{
	UE_LOG(LogTemp, Warning, TEXT("NOTIFY"));
}
