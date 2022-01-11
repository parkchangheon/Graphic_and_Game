// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick_Master.h"
#include <Engine/Classes/Components/SphereComponent.h>
#include "Components/BoxComponent.h"
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include "DoorWidget.h"
#include "PannelWidget.h"
#include "TPS_C_ProjectCharacter.h"
#include "Gimmick_Pannel_And_Lever.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API AGimmick_Pannel_And_Lever : public AGimmick_Master
{
	GENERATED_BODY()
private:
	//오버랩 비긴 함수
	UFUNCTION()
	void Pannel1_Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Pannel2_Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Pannel3_Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Pannel4_Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void Door_Overlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void StartPannelTimer();
	UFUNCTION()
	void ButtonRequiredEndTimer();

	UFUNCTION()
	bool CheckKey();
	UFUNCTION()
	void ActivateLever();
	UFUNCTION()
	void OpenDoor();

	APlayerController* PlayerController;
	AActor* Player;
	//오버랩 엔드 함수
	UFUNCTION()
	void Pannel1_EndOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	AGimmick_Pannel_And_Lever();
	virtual void Interact() override;
	virtual void BeginPlay() override;

	//정수형 변수
	int32 LastUpdated_Component_Index = -1;
	int32 RemainObject = 4;
	int32 Pw1[4] = { 12,6,9,3 };
	int32 Pw2[4] = { 3,9,6,12 };

	//스태틱메시
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pannel1;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pannel2;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pannel3;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pannel4;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UStaticMeshComponent* Door;

	UPROPERTY(Editanywher, BlueprintReadWrite)
	UStaticMeshComponent* Locker1;
	UPROPERTY(Editanywher, BlueprintReadWrite)
	UStaticMeshComponent* Locker2;
	UPROPERTY(Editanywher, BlueprintReadWrite)
	UStaticMeshComponent* Locker3;
	UPROPERTY(Editanywher, BlueprintReadWrite)
	UStaticMeshComponent* Locker4;


	//콜리전
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	USphereComponent* Pannel1_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	USphereComponent* Pannel2_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	USphereComponent* Pannel3_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	USphereComponent* Pannel4_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	USphereComponent* Door_Collision;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UBoxComponent* Locker1_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UBoxComponent* Locker2_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UBoxComponent* Locker3_Collision;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UBoxComponent* Locker4_Collision;


	//bool
	bool Pannel1_IsActivated = false;
	bool Pannel2_IsActivated = false;
	bool Pannel3_IsActivated = false;
	bool Pannel4_IsActivated = false;
	bool Door_IsActivated = false;
	bool Activated[5] = { false ,false ,false ,false ,false };

	//위젯
	UPROPERTY(EditAnyWhere)
	TSubclassOf<UDoorWidget> WidgetClass1;

	UPROPERTY(EditAnyWhere)
	TSubclassOf<UPannelWidget> WidgetClass2;

	UPannelWidget* PannelWidgetRef;

	//타이머 핸들러
	FTimerHandle WholeTimerHanlder;
	FTimerHandle SwitchTimerHandler;
	FTimerHandle SetRelativeLocationHandler;
	FTimerHandle Delay;
	
};
