// Fill out your copyright notice in the Description page of Project Settings.


#include "Noir.h"

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
	if (isJump)
		Jump();
}

void ANoir::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Check_JumpWall", IE_Pressed, this, &ANoir::CheckJump);
	InputComponent->BindAction("Check_JumpWall", IE_Released, this, &ANoir::CheckJump);

}

void ANoir::CheckJump()
{
	UE_LOG(LogTemp, Warning, TEXT("press Jump"));
	if (isJump) {
		UE_LOG(LogTemp, Warning, TEXT("now Jump"));
		isJump = false;
	}

	else {
		UE_LOG(LogTemp, Warning, TEXT("not Jump"));
		Jump();
		isJump = true;
		jumpCount++;
		if (jumpCount == 2)
		{
			LaunchCharacter(FVector(0, 0, 500), false, true);
			jumpCount = 0;
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