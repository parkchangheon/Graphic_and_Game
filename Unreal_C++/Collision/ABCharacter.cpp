

#include "Character/ABCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/ABChracterControlData.h"
#include "Animation/AnimMontage.h"
#include "Character/ABComboActionData.h"
#include "Physics/ABCollision.h"

#include "Engine/DamageEvents.h"
#include "CharacterStat/ABCharacterStatComponent.h"
#include "UI/ABWidgetComponent.h"
#include "UI/ABHPBar.h"
#include "Item/ABWeaponItemData.h"
//#include "Components/WidgetComponent.h"

DEFINE_LOG_CATEGORY(LogABCharacter);

AABCharacter::AABCharacter()
{
	//Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_ABCAPSULE);

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/ArenaBattle/Animation/ABP_ABCharacter.ABP_ABCharacter_C"));	///Script/Engine.AnimBlueprint' ..... ' 작은 따옴표 삭제는 AnimBlueprint형으로 바꿀 것이 아니기 때문에 제거. + _C 클래스 정보이기 떄문
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}


	static ConstructorHelpers::FObjectFinder<UABChracterControlData> ShoulderDataRef(TEXT("/Script/testtt.ABChracterControlData'/Game/ArenaBattle/CharacterControl/ABC_Shoulder.ABC_Shoulder'"));
	if (ShoulderDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UABChracterControlData> QuarterDataRef(TEXT("/Script/testtt.ABChracterControlData'/Game/ArenaBattle/CharacterControl/ABC_Quarter.ABC_Quarter'"));
	if (QuarterDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Quater, QuarterDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattle/Animation/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UABComboActionData> ComboActionDataRef(TEXT("/Script/testtt.ABComboActionData'/Game/ArenaBattle/CharacterAction/ABA_ComboAttack.ABA_ComboAttack'"));
	if (ComboActionDataRef.Object)
	{
		ComboActionData = ComboActionDataRef.Object;
	}

	//static ConstructorHelpers::FObjectFinder<UABComboActionData> ComboActionDataRef(TEXT("/Script/testtt.ABComboActionData'/Game/ArenaBattle/CharacterAction/ABA_ComboAttack.ABA_ComboAttack'"));
	//if (ComboActionDataRef.Object)
	//{
	//	ComboActionData = ComboActionDataRef.Object;
	//}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ArenaBattle/Animation/AM_Dead.AM_Dead'"));
	if (DeadActionMontageRef.Object)
	{
		DeadActionMontage = DeadActionMontageRef.Object;
	}


	//Stat
	Stat = CreateDefaultSubobject<UABCharacterStatComponent>(TEXT("Stat"));

	//UI
	HpBar = CreateDefaultSubobject<UABWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget>HPBarWidgetRef(TEXT("/Game/ArenaBattle/UI/WBP_HPBar.WBP_HPBar_C"));
	if (HPBarWidgetRef.Class)
	{
		HpBar->SetWidgetClass(HPBarWidgetRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AABCharacter::EquipWeapon)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AABCharacter::DrinkPotion)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AABCharacter::ReadScroll)));
}

void AABCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->OnHpZero.AddUObject(this, &AABCharacter::SetDead);

}



void AABCharacter::SetCharacterControlData(const UABChracterControlData* CharacterControlData)
{
	//Pawn
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

	//CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
}

void AABCharacter::ProcessComboCommand()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}

	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}

	else
	{
		HasNextComboCommand = true;
	}
	
}

void AABCharacter::ComboActionBegin()
{
	//Combo
	CurrentCombo = 1;

	//Movement
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	//Animation
	const float AttackSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &AABCharacter::ComboActionEnd);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

		ComboTimerHandle.Invalidate();
		SetComboTimerCheck();
	}

}

void AABCharacter::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnd)
{
	ensure(CurrentCombo != 0);	//0 이 아닌지를 검사
	CurrentCombo = 0;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AABCharacter::SetComboTimerCheck()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	const float AttackSpeedRate = 1.0f;
	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate / AttackSpeedRate);

	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AABCharacter::ComboCheck, ComboEffectiveTime, false);
	}

}

void AABCharacter::ComboCheck()
{
	ComboTimerHandle.Invalidate();

	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);

		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
		SetComboTimerCheck();

		HasNextComboCommand = false;
	}
}

void AABCharacter::AttackHitCheck()
{
	//{ 처리방법} { 대상 } { 처리설정 } ==> Sweep Single ByChannel
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackRange = 40.0f;
	const float AttackRadius = 50.0f;
	const float AttackDamage = 30.0f;

	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_ABACTION, FCollisionShape::MakeSphere(AttackRadius), Params);

	if (HitDetected)	//무언가 감지가 되었다면.
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);

	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);

#endif

}

float AABCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->ApplyDamage(DamageAmount);

	return DamageAmount;
}

void AABCharacter::SetDead()
{
	//EMovementMode::MOVE_NONE을 설정하면 캐릭터는 더이상 움직이지 않게된다.
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();	//몽타주 재생
	SetActorEnableCollision(false);	//죽었으니, 더이상 콜리전  처리는 x
	HpBar->SetHiddenInGame(true);
}

void AABCharacter::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(0.0f);
		AnimInstance->Montage_Play(DeadActionMontage, 1.0f);
	}

}


void AABCharacter::SetupCharacterWidget(class UABUserWidget* InUserWidget)
{
	UABHPBar* HpBarWidget = Cast<UABHPBar>(InUserWidget);
	if (HpBarWidget)
	{
		HpBarWidget->SetMaxHp(Stat->GetMaxHp());
		HpBarWidget->UpdateHpBar(Stat->GetCurrentHP());
		Stat->OnHpChanged.AddUObject(HpBarWidget, &UABHPBar::UpdateHpBar);
	}
}

void AABCharacter::TakeItem(UABItemData* InItemData)
{
	if (InItemData)
	{
		TakeItemActions[(uint8)InItemData->Type].ItemDelegate.ExecuteIfBound(InItemData);
	}
}

void AABCharacter::DrinkPotion(UABItemData* InItemData)
{
	UE_LOG(LogABCharacter, Log, TEXT("Drink Potion"));
}

void AABCharacter::EquipWeapon(UABItemData* InItemData)
{
	UE_LOG(LogABCharacter, Log, TEXT("EquipWeapon"));
}

void AABCharacter::ReadScroll(UABItemData* InItemData)
{
	UE_LOG(LogABCharacter, Log, TEXT("ReadScroll"));
}
