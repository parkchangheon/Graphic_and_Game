// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "ProjectChaserCharacter.generated.h"

enum SkillOpt
{
	Passive = 1,
	Active = 2,
};

enum TeamOpt
{
	Policec = 1,
	Thief,
};

enum CharacterClass
{
	Ace = 1,
	Maker,
	SpecialList,
};

struct CharacterProfile
{
	std::string CodeName;  // What is this for?
	TeamOpt TOpt;  // What is this for?
	CharacterClass CC; 
	int Sex; //0 = Man, 1 = Female, Other is ErrorCode
	std::string HomeGround; // What is this for?
	float MovingSpeed=0;

};

struct Skill
{
	SkillOpt Opt = Passive;
	//public val low security
	std::string SkillName;
	std::string SkillDesc;

	//private val high level security required
	std::string CallBackMethodName;
	//std::vector<std::string> CallBackParam;

};

UCLASS(config=Game)
class AProjectChaserCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimelineComponent* TimelineComp;

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* Curvefloat; 

	FVector StartLoc;
	FVector EndLoc;
	float ZOffset;
public:
	AProjectChaserCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	UMaterialInterface* Material;

protected:

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

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

	virtual void UseSkill(int32 SkillCode);
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	void ChangeMat(float changeTime, FName ParamName, UTexture* texture);

	UFUNCTION()
		void TimelineProgress(float val);

	Skill PassiveSkill;
	Skill ActiveSkill1;
	Skill ActiveSkill2;
	Skill ActiveSkill3;

	CharacterProfile CP;

};
 
