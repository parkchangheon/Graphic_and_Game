// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_Thief.h"
#include "Noir.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCHASER_API ANoir : public ACharacter_Thief
{
	GENERATED_BODY()
	
public:
	ANoir();
	bool onWall(bool wall);
	void CheckJump();
	virtual void Landed(const FHitResult& Hit)override;
	 
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void UseSkill(int32 SkillCode) override;

public:
	UPROPERTY()
		bool isJump;
	int jumpCount;

};
