// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/ABCharacterStatComponent.h"

// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	MaxHP = 200.f;
	CurrentHp = MaxHP;
	
}


// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHp(MaxHP);
	
}

float UABCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);

	if (CurrentHp <= KINDA_SMALL_NUMBER)	//굉장히 작은 값보다 작다면
	{
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}

void UABCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp(NewHp, 0, MaxHP);

	OnHpChanged.Broadcast(CurrentHp);	//MultiDelegate 이므로 BroadCast를 날려줌
}

