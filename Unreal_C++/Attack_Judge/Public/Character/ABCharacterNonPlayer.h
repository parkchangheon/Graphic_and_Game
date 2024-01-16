// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacter.h"
#include "ABCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TESTTT_API AABCharacterNonPlayer : public AABCharacter
{
	GENERATED_BODY()
	
public:

	AABCharacterNonPlayer();

	void SetDead()override;
};
