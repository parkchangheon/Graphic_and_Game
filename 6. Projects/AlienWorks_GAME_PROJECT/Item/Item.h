// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ProjectChaserCharacter.h"
#include "Item.generated.h"

UCLASS()
class PROJECTCHASER_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();


public :
	UPROPERTY(VisibleAnywhere, Category = Item)
	UStaticMeshComponent* Item;

	UPROPERTY(VisibleAnywhere, Category = Item)
	UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Item)
	class UTexture2D* ItemImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Item)
	float speed;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	virtual void PostInitializeComponents();

};
