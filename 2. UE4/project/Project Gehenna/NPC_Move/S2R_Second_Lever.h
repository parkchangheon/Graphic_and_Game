// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S2R_Final_PannelLever.h"
#include "S2R_Second_Lever.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API AS2R_Second_Lever : public AS2R_Final_PannelLever
{
	GENERATED_BODY()
	
public:
	AS2R_Second_Lever();
	virtual void BeginPlay() override;
	void StartTimer();
	void AdvanceTimer();   // 타이머가 돌아가면서 호출될 함수
	void CountdownHasFinished();  //advanceTimer가 지정한 만큼 작동한 뒤에 마무리 처리하기 위함


	FTimerHandle CountdownTimerHandle; // 타이머를 컨트롤 하기 위한 구조체, 카운트다운 종료 후, 타이머 종료 후 돌아가지 않게 하려고

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	class UStaticMeshComponent* NPC_Lever;

protected: 
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit); 

public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	class UBoxComponent* BoxMesh;



public:
	char answer[4] = { 'w','s','d','a' };
	UPROPERTY(EditAnywhere)
	int32 CountdownTime;
	bool isholding;


};
