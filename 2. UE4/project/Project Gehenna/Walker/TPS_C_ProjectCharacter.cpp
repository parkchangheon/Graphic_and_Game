 // Copyright Epic Games, Inc. All Rights Reserved.

#include "TPS_C_ProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gimmick.h"
#include "Master_Interact.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "DrawDebugHelpers.h"
#include "StatComponent.h"
#include "MyAnimInstance.h"

//////////////////////////////////////////////////////////////////////////
// ATPS_C_ProjectCharacter

ATPS_C_ProjectCharacter::ATPS_C_ProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	MovePlayerTo(250);

	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("STAT"));
	StatComponent->SetName(FName(TEXT("LeeYul")));
	StatComponent->SetStat(StatComponent->GetName());

	// set our turn rates for input
	{
		BaseTurnRate = 45.f;
		BaseLookUpRate = 45.f;
	}


	//캡슐 콜리전 설정
	{
		CapsuleHalfScale = 96.0f;
		CapsuleCrawlScale = 42.0f;
	}


	//참조용 불린값 설정
	{
		IsCrowching = false;
		IsCrawling = false;
	}

	//위치벡터변수 초기화
	{
		CrawlingMeshVector = GetMesh()->GetRelativeLocation() + FVector(0.0f, 0.0f, -42.0f);
		BaseLocationVector = FVector(0.0f, 0.0f, -97.0f);
	}


	CrawlCameraLocation = FVector(200.0f, -27.0f, -15.0f);
	CrawlCameraRotation = FRotator(0.0f, 0.0f, 0.0f);
	

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	{
		GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
		GetCharacterMovement()->JumpZVelocity = 600.f;
		GetCharacterMovement()->AirControl = 0.2f;
	}


	// Create a camera boom (pulls in towards the player if there is a collision)
	{
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
		CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	}

	{
		// Create a follow camera
		FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
		FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	}


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	{
		StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerception Stimulate Component"));
		Gimmick_Component = CreateDefaultSubobject<UGimmick>(TEXT("Gimmick Component"));

	}

}



void ATPS_C_ProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATPS_C_ProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPS_C_ProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATPS_C_ProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATPS_C_ProjectCharacter::LookUpAtRate);

	// VR headset functionality
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ATPS_C_ProjectCharacter::Interaction);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ATPS_C_ProjectCharacter::Attack);

}

void ATPS_C_ProjectCharacter::Interaction()
{
	//라인트레이싱 코드 - 창헌
	FHitResult OutHit;
	FVector Start = GetFollowCamera()->GetComponentLocation();
	FVector End = Start + GetFollowCamera()->GetForwardVector() * 400.0f;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, Params, FCollisionResponseParams()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *OutHit.GetActor()->GetName());

		AMaster_Interact* Obj = Cast<AMaster_Interact>(OutHit.Actor);
		if (Obj)
		{
			Obj->Interact();
		}
	}
	//라인트레이스 시각화
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f, 0, 1.0f);


	//기존 익재님의 코드
	//Gimmick_Component->Interact_With_Key();
}

void ATPS_C_ProjectCharacter::InterpCameraCrawl()
{
	//마우스 인풋 무력화
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreLookInput(true);

	//타이머 설정, 타이머를 이용하여 부드럽게 카메라를 이동할 예정
	GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (FollowCamera->GetRelativeLocation() == CrawlCameraLocation && FollowCamera->GetRelativeRotation() == CrawlCameraRotation) {
				GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
			}
			//followcamera의 relative위치를 vinterp를 이용하여 옮길 코드
			FollowCamera->SetRelativeLocation(FMath::VInterpTo(
				FollowCamera->GetRelativeLocation(),
				CrawlCameraLocation,
				UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
				1.0f));

			FollowCamera->SetRelativeRotation(FMath::RInterpTo(
				FollowCamera->GetRelativeRotation(),
				CrawlCameraRotation,
				UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
				1.0f));

			//cameraboom의 회전치를 초기화 시킴


		}), 0.005f, true);
	
}

void ATPS_C_ProjectCharacter::InterpCameraNormal()
{
	//마우스 인풋 무력화
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetIgnoreLookInput(false);

	//타이머 설정, 타이머를 이용하여 부드럽게 카메라를 이동할 예정
	GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (FollowCamera->GetRelativeLocation() == FVector(0,0,0) && FollowCamera->GetRelativeRotation() == FRotator(0,0,0)) {
				GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
			}
			//followcamera의 relative위치를 vinterp를 이용하여 옮길 코드
			FollowCamera->SetRelativeLocation(FMath::VInterpTo(
				FollowCamera->GetRelativeLocation(),
				FVector(0, 0, 0),
				UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
				1.0f));

			FollowCamera->SetRelativeRotation(FMath::RInterpTo(
				FollowCamera->GetRelativeRotation(),
				FRotator(0,0,0),
				UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
				1.0f));

		}), 0.005f, true);
}

void ATPS_C_ProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATPS_C_ProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATPS_C_ProjectCharacter::Attack()
{

	auto AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance()); //animinstance를 찾는다

	if (AnimInstance)
	{
		AnimInstance->PlayAttackMontage(0);
	}

}

void ATPS_C_ProjectCharacter::MoveForward(float Value)
{
	UpDownVal = Value;

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

void ATPS_C_ProjectCharacter::MoveRight(float Value)
{
	LeftRightVal = Value;
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


void ATPS_C_ProjectCharacter::Yaw(float Value)
{
	AddControllerYawInput(Value);
}



void ATPS_C_ProjectCharacter::MovePlayerTo(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;

}