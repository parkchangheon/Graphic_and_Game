// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Master_Interact.h"
#include "S2R_Final_Gate.generated.h"

/**
 * 
 */
UCLASS()
class TPS_C_PROJECT_API AS2R_Final_Gate : public AMaster_Interact
{
	GENERATED_BODY()
	

public:
	AS2R_Final_Gate();
	virtual void BeginPlay() override;
	virtual void Interact() override;

public:
	UPROPERTY()
	bool First_Pannel;

	UPROPERTY()
	bool Second_Pannel;

	UPROPERTY()
	bool Third_Pannel;

	UPROPERTY()
	bool Gate_Status;

	class UStaticMeshComponent* Door;
	class UStaticMeshComponent* Door_Right;
	class UStaticMeshComponent* Door_Left;

	class UStaticMeshComponent* Pannel1;
	class UStaticMeshComponent* Pannel2;
	class UStaticMeshComponent* Pannel3;

};
