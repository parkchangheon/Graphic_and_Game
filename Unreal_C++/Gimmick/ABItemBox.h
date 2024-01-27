// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABItemBox.generated.h"

UCLASS()
class TESTTT_API AABItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AABItemBox();
	FORCEINLINE class UBoxComponent* GetTrigger() { return Trigger; }

protected:
	virtual void PostInitializeComponents() override;	//액터의 세팅이 마무리 되는 시점에 호출됨

protected:
	UPROPERTY(VisibleAnywhere, Category = BOX)
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY(VisibleAnywhere, Category=BOX)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category=BOX)
	TObjectPtr<class UParticleSystemComponent> Effect;

	UPROPERTY(EditAnywhere, Category=Item)
	TObjectPtr<class UABItemData> Item;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* ParticleSystem);

};
