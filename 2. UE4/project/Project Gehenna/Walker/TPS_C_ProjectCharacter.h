// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gimmick.h"
#include <Perception/AIPerceptionStimuliSourceComponent.h>
#include "TPS_C_ProjectCharacter.generated.h"

UCLASS(config=Game)
class ATPS_C_ProjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere)
	class UStatComponent* StatComponent;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	UAIPerceptionStimuliSourceComponent* StimuliSource;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = Interaction)
	UGimmick* Gimmick_Component;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float CapsuleHalfScale;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float CapsuleCrawlScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsCrowching;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsCrawling;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	bool IsPlayingMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector BaseLocationVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector CrawlingMeshVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector CrawlCameraLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FRotator CrawlCameraRotation;

	FTimerHandle WaitHandle;

	float LeftRightVal;
	float UpDownVal;
protected:
	void Attack();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Yaw(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

public:
	ATPS_C_ProjectCharacter();

	UFUNCTION(BlueprintCallable)
	void MovePlayerTo(float speed);

	UFUNCTION(BlueprintCallable)
	void Interaction();

	UFUNCTION(BlueprintCallable)
	void InterpCameraCrawl();

	UFUNCTION(BlueprintCallable)
	void InterpCameraNormal();
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

