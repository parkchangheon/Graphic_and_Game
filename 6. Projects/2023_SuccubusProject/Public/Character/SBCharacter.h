// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "SBCharacter.generated.h"

UCLASS()
class SUCCUBUSAD_API ASBCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASBCharacter();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE USpringArmComponent* GetCameraBoom() { return CameraBoom; }

	FORCEINLINE UCameraComponent* GetFollowCamera() { return FollowCamera; }

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);


//protected:
//
//	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
//	TObjectPtr<USkeletalMeshComponent> SBMesh;
//
//	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
//	TObjectPtr<UCapsuleComponent> SBCapsuleComponent;
//
//	UPROPERTY()
//	TObjectPtr<UArrowComponent> SBArrowComponent;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* FollowCamera;



};
