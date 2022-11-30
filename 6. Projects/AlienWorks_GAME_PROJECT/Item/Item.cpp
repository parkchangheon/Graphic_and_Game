// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Item = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM(TEXT(""));
	if (SM.Succeeded())
	{
		Item->SetStaticMesh(SM.Object);
	}

	this->BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	this->BoxCollider->SetGenerateOverlapEvents(true);
	this->BoxCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));


	Item->SetupAttachment(RootComponent);
	this->BoxCollider->SetupAttachment(Item);

	Item->SetCollisionProfileName(TEXT("NoCollision"));
	this->BoxCollider->SetCollisionProfileName(TEXT("MyItem"));
	
}

void AItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
}


void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped 1"));
	AProjectChaserCharacter* character = Cast<AProjectChaserCharacter>(OtherActor);
	if (character)
	{
		UE_LOG(LogTemp, Log, TEXT("Overlapped 2"));
	}

	this->Destroy();

}  

