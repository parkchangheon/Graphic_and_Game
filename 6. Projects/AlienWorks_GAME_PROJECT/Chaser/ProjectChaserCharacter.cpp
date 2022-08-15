// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectChaserCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


//캐릭터 상태
enum CHARATER_STATE
{
	NORMAL_STATE,     //일반상태
	SHOCK_STATE,      //감전상태
	EXPOSED_STATE,    //노출상태
	CLOAKING_STATE,  //은신상태
	FAST_STATE,      //신속상태
	ARRESTED_STATE   //체포상태
};


//////////////////////////////////////////////////////////////////////////
// AProjectChaserCharacter

AProjectChaserCharacter::AProjectChaserCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	jumpCount = 0;
	jumping = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectChaserCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AProjectChaserCharacter::CheckJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AProjectChaserCharacter::CheckJump);


	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AProjectChaserCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AProjectChaserCharacter::MoveRight);

	//PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AProjectChaserCharacter::StartCrouch);
	//PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AProjectChaserCharacter::StopCrouch);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AProjectChaserCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AProjectChaserCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProjectChaserCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProjectChaserCharacter::TouchStopped);
}

void AProjectChaserCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AProjectChaserCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AProjectChaserCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AProjectChaserCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

//void AProjectChaserCharacter::Tick(float deltaTime)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Tick"));
//	Super::Tick(deltaTime);
//	if (jumping)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Tick Jump"));
//		Jump();
//	}
//}


void AProjectChaserCharacter::CheckJump()
{
	UE_LOG(LogTemp, Warning, TEXT("press Jump"));
	if (jumping){
		UE_LOG(LogTemp, Warning, TEXT("now Jump"));
		jumping = false;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("not Jump"));
		Jump();
		jumping = true;
		jumpCount++;
		if (jumpCount == 2)
		{
			LaunchCharacter(FVector(0, 0, 500), false, true);
		}
	}
}

void AProjectChaserCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	jumpCount = 0;
}

void AProjectChaserCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AProjectChaserCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
