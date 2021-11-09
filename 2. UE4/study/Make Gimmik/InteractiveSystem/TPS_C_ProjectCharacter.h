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

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ATPS_C_ProjectCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = AI)
	UAIPerceptionStimuliSourceComponent* StimuliSource;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = Interaction)
	UGimmick* Gimmick_Component;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float CrawlSpeed;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float BaseSpeed;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float CrouchSpeed;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float CapsuleHalfScale;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Movement)
	float CapsuleCrawlScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsCrowching;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool IsCrawling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector BaseLocationVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector CrawlingMeshVector;

	FTimerHandle WaitHandle;

	UFUNCTION(BlueprintCallable)
	void InterpCameraCrawl();

	UFUNCTION(BlueprintCallable)
	void InterpCameraNormal();

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void Interaction();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

