// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("CHARACTER Spwan"));
	Super::BeginPlay();
	
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATestCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATestCharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ATestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ATestCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
}



void ATestCharacter::MoveForward(float value) 
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		//정면을 확인하는 코드
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		//정면 벡터 받기
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}
