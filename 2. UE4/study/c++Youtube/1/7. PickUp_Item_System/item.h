// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "tutorial_of_cCharacter.h"
#include "item.generated.h"

UCLASS()
class TUTORIAL_OF_C_API Aitem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aitem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




	UShapeComponent* TBox;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SM_TBox;

	Atutorial_of_cCharacter* MyPlayerController;

	UPROPERTY(EditAnywhere)
		FString ItemName = FString(TEXT(""));

	void Pickup(); //item을 가져오는데 사용

	void GetPlayer(AActor* Player); //player를 가져오는데 사용됨

	bool bItemIsWithinRange = false;


	UFUNCTION()
		void TriggerEnter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void TriggerExit(UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
