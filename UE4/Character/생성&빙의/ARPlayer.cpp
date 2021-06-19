// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPlayer.h"

// Sets default values
AARPlayer::AARPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈 메시 로드 => Onlt at spawner... 캐릭터 레퍼런스 불러오기로 불러오는 방법
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyAsset(TEXT("SkeletalMesh'/Game/ParagonCountess/Characters/Heroes/Countess/Meshes/SM_Countess.SM_Countess'"));

	//하지만 언리얼에서 지울 수 있으므로, 확인하는 작업이 필요함
	if (BodyAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(BodyAsset.Object);
	//저장하고 로드하면 언리얼 c++ 클래스 및에 생성된다.

	//캐릭터가 떠있기 때문에 상대적인 위치를 조정하기 위해 다음 처리를 해준다. 나는 언리얼에서 직접 트랜스폼으로 조절함 
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.f));
}

// Called when the game starts or when spawned
void AARPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input 입력처리 
void AARPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

