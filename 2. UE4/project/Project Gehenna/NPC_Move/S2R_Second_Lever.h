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
	void OnBeginOverlap(AActor* Overlapped, AActor* Other);

	UFUNCTION()
	void OnOverlapEnd(AActor* Overlapped, AActor* Other);


public:
	FDelegateTriggerOVL DelegateTriggerOVL;
};
