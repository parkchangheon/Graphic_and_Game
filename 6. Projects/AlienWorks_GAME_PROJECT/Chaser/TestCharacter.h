// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestCharacter.generated.h"

UCLASS()
class PROJECTCHASER_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

	//카메라 붐은 캐릭터 뒤에 존재하는 카메라에 위치함.
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	//카메라
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
//캐릭터 
protected:
	UPROPERTY(VisibleAnywhere)
	float CharacterSpeed;   // 이동속도
	int RoundMoneyGain;     // 라운드 시작 재화 획득량
	int FieldMoneyGain;     // 필드루팅 재화 획득량
	int FieldItemGain;      // 필드루팅아이템 획득량
	float FootPrintSound;   // 발자국 소리

public:
	// Sets default values for this character's properties
	ATestCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	float TurnRateGamepad;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);
	void Yaw(float value);
	//void TurnAtRate(float Rate);
	//void LookUpAtRate(float Rate);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	///** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	///** Returns FollowCamera subobject **/
	//FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	

};
