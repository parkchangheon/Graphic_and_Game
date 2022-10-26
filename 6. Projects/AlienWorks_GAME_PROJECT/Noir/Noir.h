// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NoirActiveSkill.h"
#include "Character_Thief.h"
#include "Net/UnrealNetwork.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WallJump")
	float TraceDistance;

	UFUNCTION()
	bool TraceForward();
	//UFUNCTION()
	//bool DoubleJumpCheck();

public:
	UFUNCTION(BlueprintCallable)
	void NoirActiveSkill1();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_OnFire(FVector Location, FRotator Rotation);
	void Server_OnFire_Implementation(FVector Location, FRotator Rotation);
	bool Server_OnFire_Validate(FVector Location, FRotator Rotation);

public:
	UPROPERTY()
	bool isJump;
	int jumpCount;
	bool jumpTrace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AActor> SkillOBJ;

	UCameraComponent* NoirCam;

};