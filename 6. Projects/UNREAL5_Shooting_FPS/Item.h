// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class SHOOTERGAME_PRO_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	//아이템 스켈레탈 메시
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"));
	USkeletalMeshComponent* ItemMesh;

	//라인트레이스가 아이템 박스와 충돌했을때, HUD 위젯을 보여준다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* CollisionBox;


public:

};
