// Fill out your copyright notice in the Description page of Project Settings.

#include "tutorial_of_c.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Engine.h" //intput this to make sprint
#include "Kismet/GameplayStatics.h"
#include "item.h"

// Sets default values
Aitem::Aitem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	TBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	TBox->SetGenerateOverlapEvents(true);

	TBox->OnComponentBeginOverlap.AddDynamic(this, &Aitem::TriggerEnter);
	TBox->OnComponentEndOverlap.AddDynamic(this, &Aitem::TriggerExit);


	RootComponent = TBox;

	SM_TBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX MESH"));
	SM_TBox->AttachTo(RootComponent);
}

void Aitem::GetPlayer(AActor* Player) {
	MyPlayerController = Cast<Atutorial_of_cCharacter>(Player);
}

// Called when the game starts or when spawned
void Aitem::BeginPlay()
{
	Super::BeginPlay();
	
}

void Aitem::Pickup()
{
	MyPlayerController->Inventory.Add(*ItemName);
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,TEXT("you Pick the item Up!!!"));
	Destroy(); // 아이템을 주우면 없어지게 삭제해줌
}

// Called every frame
void Aitem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyPlayerController!=NULL) { // NULL Check player Controller 
		if (MyPlayerController->bIsPickingUp && bItemIsWithinRange)
		{
			Pickup();
		}
	}

}

void Aitem::TriggerEnter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	bItemIsWithinRange = true;
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Press E to pickup %s"),*ItemName));
	GetPlayer(OtherActor);
}


void Aitem::TriggerExit(UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	bItemIsWithinRange = false;
}
