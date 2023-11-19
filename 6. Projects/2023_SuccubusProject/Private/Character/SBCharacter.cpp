// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SBCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"



// Sets default values
ASBCharacter::ASBCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	

}

// Called when the game starts or when spawned
void ASBCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input 
void ASBCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ASBCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ASBCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ASBCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ASBCharacter::LookUp);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ASBCharacter::Jump);
}

void ASBCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		/*FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Value);*/

		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASBCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		/*FVector Right = GetActorRightVector();
		AddMovementInput(Right, Value);*/

		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ASBCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASBCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

