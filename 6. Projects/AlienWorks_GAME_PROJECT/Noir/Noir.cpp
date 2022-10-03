// Fill out your copyright notice in the Description page of Project Settings.


#include "Noir.h"
#include "NoirActiveSkill.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystem.h"


enum NoirSkillTable {
	PassiveSkill,
	ActiveSkill1,
	ActiveSkill2,
	ActiveSkill3
};

ANoir::ANoir()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> NoirSkel(TEXT("SkeletalMesh'/Game/ProjectAsset/Character/Theif_Noir/SK_Noir_HumanIK.SK_Noir_HumanIK'"));
	if(NoirSkel.Succeeded())
		GetMesh()->SetSkeletalMesh(NoirSkel.Object);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	isJump = false;
	jumpCount = 0;

}

void ANoir::BeginPlay()
{
	Super::BeginPlay();
}

void ANoir::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (isJump)
		Jump();*/
}

void ANoir::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Check_JumpWall", IE_Pressed, this, &ANoir::CheckJump);
	InputComponent->BindAction("Check_JumpWall", IE_Released, this, &ANoir::CheckJump);

	InputComponent->BindAction("UseSkill_No1", IE_Released, this, &ANoir::NoirActiveSkill1);
}

void ANoir::CheckJump()
{
	if (isJump) {  //점프 2회차 시
		UE_LOG(LogTemp, Warning, TEXT("now Jump"));
		isJump = false;
	}

	else if(jumpCount < 2) { //점프 0~1회차시 
		UE_LOG(LogTemp, Warning, TEXT("not Jump"));
		
		/*Jump();*/
		isJump = true;
		jumpCount++;
		if (jumpCount == 2)
		{
			// 여기서 bool형식으로 라인트레이스 시, 벽이면 2단 점프 가능하게 
			TraceForward(); //트레이스 앞으로
			if (TraceForward()) {
				UE_LOG(LogTemp, Warning, TEXT("AfterHit"));
				LaunchCharacter(FVector(0, 0, 500), false, true);
				isJump = false;
			}
			
		}
	}
}

void ANoir::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	jumpCount = 0;
}

bool ANoir::onWall(bool wall)
{
	if (wall)
		return true;
	return false;
}

void ANoir::UseSkill(int32 SkillCode)
{
	switch (SkillCode) {
	case NoirSkillTable::PassiveSkill:
		break;
	default:
		break;
	}
}

bool ANoir::TraceForward() {
		FHitResult OutHit;
		FVector Start = GetActorLocation();
	
		FVector ForwardVector = GetActorForwardVector();
		FVector End = ((ForwardVector * 100.f) + Start);
		FCollisionQueryParams collisionParams;
	
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f,5.f, 5.f);
	
		bool isHit = ActorLineTraceSingle(OutHit, Start, End, ECC_WorldStatic, collisionParams);
		
		if (isHit)
		{
			if (GEngine) 
			{
				GEngine->AddOnScreenDebugMessage(01, 1.f, FColor::Blue, FString::Printf(TEXT("The Comp being hit is : %s"),
					*OutHit.GetComponent()->GetName()));
			}
			UE_LOG(LogTemp, Warning, TEXT("isHit isHit!!"));
			return true;
		}
		UE_LOG(LogTemp, Warning, TEXT("nothing happen!!"));
		return false;
}


void ANoir::NoirActiveSkill1()
{ 
	UE_LOG(LogTemp, Warning, TEXT("ActiveSkill Activated"));
	//Noir 스킬을 불러내어 spawn
	//스킬에서 init할때 생성하며, 적군에 맞았을때, 스킬 발동

	const FVector Location = GetActorLocation() + FVector(0, 0, 0);
	//const FRotator Rotation = GetActorRotation();
	const FRotator Rotation = GetControlRotation();
	GetWorld()->SpawnActor<ANoirActiveSkill>(SkillOBJ, Location, Rotation);


}






