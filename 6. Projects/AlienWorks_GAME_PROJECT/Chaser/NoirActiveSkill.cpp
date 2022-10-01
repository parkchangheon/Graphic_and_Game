// Fill out your copyright notice in the Description page of Project Settings.

#include "Noir.h"
#include "NoirActiveSkill.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ANoirActiveSkill::ANoirActiveSkill()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//createdefaultsubobject를 쓰면, 메시를 직접 delete 안해줘도 됨 -> 스마트 포인터같은 느낌
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/PCH_PRIVATE/SM_airConditioner01.SM_airConditioner01'"));
	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object);
	}
	RootComponent = Mesh;
	Mesh->OnComponentHit.AddDynamic(this, &ANoirActiveSkill::OnHit);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(Mesh);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	/*ProjectileMovementComponent->Bounciness = 0.3f;*/

	InitialLifeSpan = 3.0f;
}

//void ANoirActiveSkill::FireInDirection(const FVector& ShootDirection)
//{
//	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
//}


void ANoirActiveSkill::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) 
{

	
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	
	if (OtherActor->ActorHasTag("Police"))
	{
		UE_LOG(LogTemp, Warning, TEXT("It is a police"));

	}
}


//collision 했을때, spawn emitter at location을 한번 써보자