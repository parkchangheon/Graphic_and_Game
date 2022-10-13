// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"


//UMyAnimInstance::UMyAnimInstance()
//{
//	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/ProjectAsset/Character/Theif_Noir/Noir_Mixamo_Standing_Melee_Attack_360_High_Anim_Retargeted_Montage.Noir_Mixamo_Standing_Melee_Attack_360_High_Anim_Retargeted_Montage'"));
//	if (AM.Succeeded())
//	{
//		NoirSkillMontage = AM.Object;
//
//	}
//}


void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)  //프레임마다 꺼낸다.
{
	Super::NativeUpdateAnimation(DeltaSeconds); 
	
	auto pawn = TryGetPawnOwner();   //이 클래스를 포함하고 있는 Pawn을 받아와서
	if (IsValid(pawn)) {  //있다면
		Speed = pawn->GetVelocity().Size();   //Speed 변수에 pawn의 속도를 매 프레임마다 세팅해준다.
	
		auto Character = Cast<ACharacter>(pawn);
		if (Character) {
			isFalling = Character->GetMovementComponent()->IsFalling();
		}
	}


}

//void UMyAnimInstance::PlaySkillMontage()
//{
//	if (!Montage_IsPlaying(NoirSkillMontage)) {
//		Montage_Play(NoirSkillMontage, 1.f);
//	}
//
//}

