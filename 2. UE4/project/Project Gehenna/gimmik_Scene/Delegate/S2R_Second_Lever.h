// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "S2R_Final_PannelLever.h"
#include "S2R_Second_Lever.generated.h"


//Single Cast
DECLARE_DELEGATE(FDele_Single);  // 메크로를 델리게이트화 시켰다.(인자가 없는 함수에 사용)

UCLASS()
class TPS_C_PROJECT_API AS2R_Second_Lever : public AS2R_Final_PannelLever
{
	GENERATED_BODY()

private:
	bool IsMoonStand_Lever;
	bool IsYoolStand_Lever;
	
public:
	DECLARE_EVENT(AS2R_Second_Lever, FDele_Event); // 이벤트!
	AS2R_Second_Lever();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	class UStaticMeshComponent* NPC_Lever;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	class UBoxComponent* BoxMesh;


public:
	char answer[4] = { 'w','s','d','a' };

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCharacterOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
	void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
	bool SecondLeverResult(char answer);

public:
	FDele_Single Fuc_DeleSingle;
};
