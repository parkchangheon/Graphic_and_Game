// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "S2R_Final_PannelLever.h"
#include "S2R_Second_Lever.generated.h"

DECLARE_DELEGATE(FDelegateTriggerOVL)

UCLASS()
class TPS_C_PROJECT_API AS2R_Second_Lever : public AS2R_Final_PannelLever
{
	GENERATED_BODY()

private:
	bool IsMoonStand_Lever;
	bool IsYoolStand_Lever;
	
public:
	AS2R_Second_Lever();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	class UStaticMeshComponent* NPC_Lever;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lever")
	class UBoxComponent* BoxMesh;


public:
	char answer[4] = { 'w','s','d','a' };

public:
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
	FDelegateTriggerOVL DelegateTriggerOVL;
};
