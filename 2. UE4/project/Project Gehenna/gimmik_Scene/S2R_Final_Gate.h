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
	void BeginPlay();
	void virtual Interact() override;
	void OpenDoor();




public:
	UPROPERTY()
	bool Gate_Status;


	class UStaticMeshComponent* Master_Gate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")	
	class UStaticMeshComponent* Door_Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	class UStaticMeshComponent* Door_Left;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	class UStaticMeshComponent* Pannel1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	class UStaticMeshComponent* Pannel2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	class UStaticMeshComponent* Pannel3;

};
