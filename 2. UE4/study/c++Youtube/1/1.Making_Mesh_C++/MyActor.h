// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class TUTORIAL_OF_C_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(EditAnywhere)
		UShapeComponent* Root;
	// ����? �𸮾� ���÷��� �ý��ۿ� �ش� ������Ƽ�� ������ �˸�
	// ���÷����� ���α׷��� ����ð��� �ڱ��ڽ��� �����ϴ� ���.

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};