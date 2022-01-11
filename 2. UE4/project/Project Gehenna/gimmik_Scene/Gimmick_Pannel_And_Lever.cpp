// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick_Pannel_And_Lever.h"
#include <Engine/StaticMesh.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

AGimmick_Pannel_And_Lever::AGimmick_Pannel_And_Lever()
{

	//오브젝트 할당
	{
		Pannel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pannel1"));
		Pannel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pannel2"));
		Pannel3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pannel3"));
		Pannel4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pannel4"));
		Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));

		Locker1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Locker1"));
		Locker2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Locker2"));
		Locker3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Locker3"));
		Locker4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Locker4"));

	}

	//스태틱메시 할당
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/Inventory_Weapon_Portal/Geometry/Meshes/1M_Cube.1M_Cube'"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM2(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM3(TEXT("StaticMesh'/Game/MAP_CONTENTS/Door/BluePrintDoorSlide/door.door'"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SM4(TEXT("StaticMesh'/Game/MAP_CONTENTS/Scene_props/Locker.Locker'"));


		Pannel1->SetStaticMesh(SM.Object);
		Pannel2->SetStaticMesh(SM.Object);
		Pannel3->SetStaticMesh(SM.Object);
		Pannel4->SetStaticMesh(SM.Object);
		Door->SetStaticMesh(SM3.Object);

		Locker1->SetStaticMesh(SM4.Object);
		Locker2->SetStaticMesh(SM4.Object);
		Locker3->SetStaticMesh(SM4.Object);
		Locker4->SetStaticMesh(SM4.Object);

			
	}

	//콜리전 할당
	{
		Pannel1_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Pannel1_Collision"));
		Pannel2_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Pannel2_Collision"));
		Pannel3_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Pannel3_Collision"));
		Pannel4_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Pannel4_Collision"));
		Door_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Door_Collision"));

		Locker1_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Locker1_Collision"));
		Locker2_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Locker2_Collision"));
		Locker3_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Locker3_Collision"));
		Locker4_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Locker4_Collision"));

	}

	//콜리전 크기 조정
	{
		Pannel1_Collision->SetSphereRadius(142.f);
		Pannel2_Collision->SetSphereRadius(142.f);
		Pannel3_Collision->SetSphereRadius(142.f);
		Pannel4_Collision->SetSphereRadius(142.f);

		Door_Collision->SetSphereRadius(150.f);
	}

	//스태틱메시 위치 조정
	{
		Pannel1_Collision->SetRelativeLocation(FVector(-1000.f, 0.f, 0.f));
		Pannel2_Collision->SetRelativeLocation(FVector(-600.f, 0.f, 0.f));
		Pannel3_Collision->SetRelativeLocation(FVector(-200.f, 0.f, 0.f));
		Pannel4_Collision->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
		Door_Collision->SetRelativeLocation(FVector(1000.f, 0.f, 0.f));
		Door->SetRelativeLocation(FVector(0.f, 0.f, -132.f));
	}

	//스태틱메시를 콜리전에 어태치
	{
		Pannel1->SetupAttachment(Pannel1_Collision);
		Pannel2->SetupAttachment(Pannel2_Collision);
		Pannel3->SetupAttachment(Pannel3_Collision);
		Pannel4->SetupAttachment(Pannel4_Collision);
		Door->SetupAttachment(Door_Collision);

		Locker1->SetupAttachment(Locker1_Collision);
		Locker2->SetupAttachment(Locker2_Collision);
		Locker3->SetupAttachment(Locker3_Collision);
		Locker4->SetupAttachment(Locker4_Collision);

	}


	//콜리전 오버랩 이벤트 할당
	{
		Pannel1_Collision->OnComponentBeginOverlap.AddDynamic(this, &AGimmick_Pannel_And_Lever::Pannel1_Overlapped);
		Pannel2_Collision->OnComponentBeginOverlap.AddDynamic(this, &AGimmick_Pannel_And_Lever::Pannel2_Overlapped);
		Pannel3_Collision->OnComponentBeginOverlap.AddDynamic(this, &AGimmick_Pannel_And_Lever::Pannel3_Overlapped);
		Pannel4_Collision->OnComponentBeginOverlap.AddDynamic(this, &AGimmick_Pannel_And_Lever::Pannel4_Overlapped);
		Door_Collision->OnComponentBeginOverlap.AddDynamic(this, &AGimmick_Pannel_And_Lever::Door_Overlapped);
	}

	//콜리전 엔드오버랩 이벤트 할당
	{
		Pannel1_Collision->OnComponentEndOverlap.AddDynamic(this, &AGimmick_Pannel_And_Lever::Pannel1_EndOverlapped);
		Pannel2_Collision->OnComponentEndOverlap.AddDynamic(this, &AGimmick_Pannel_And_Lever::Pannel1_EndOverlapped);
		Pannel3_Collision->OnComponentEndOverlap.AddDynamic(this, &AGimmick_Pannel_And_Lever::Pannel1_EndOverlapped);
		Pannel4_Collision->OnComponentEndOverlap.AddDynamic(this, &AGimmick_Pannel_And_Lever::Pannel1_EndOverlapped);
		Door_Collision->OnComponentEndOverlap.AddDynamic(this, &AGimmick_Pannel_And_Lever::Pannel1_EndOverlapped);
	}

	//위젯 레퍼런스 할당
	{
		ConstructorHelpers::FClassFinder<UUserWidget> PannelObj(TEXT("WidgetBlueprint'/Game/Map/Interaction/Gimmick/Lever_And_Pannel/PannelWidget.PannelWidget_C'"));


		WidgetClass2 = PannelObj.Class;
	}
}

void AGimmick_Pannel_And_Lever::BeginPlay()
{

	if (WidgetClass1 && WidgetClass2)
	{
		DoorWidgetRef = Cast<UDoorWidget>(CreateWidget(GetWorld(), WidgetClass1));
		PannelWidgetRef = Cast<UPannelWidget>(CreateWidget(GetWorld(), WidgetClass2));

		if (DoorWidgetRef != nullptr) {
			DoorWidgetRef->AddToViewport();
			//UE_LOG(LogTemp, Warning, TEXT("DoorWidgetRef Class Is Valid"));
		}

		if (PannelWidgetRef != nullptr) {
			PannelWidgetRef->AddToViewport();
			PannelWidgetRef->SetVisibility(ESlateVisibility::Hidden);
			//UE_LOG(LogTemp, Warning, TEXT("PannelWidgetRef Class Is Valid"));
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("The Classes Is Not Valid"));

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void AGimmick_Pannel_And_Lever::Pannel1_Overlapped(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		LastUpdated_Component_Index = 1;
	}
	
}

void AGimmick_Pannel_And_Lever::Pannel2_Overlapped(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		LastUpdated_Component_Index = 2;
	}
}

void AGimmick_Pannel_And_Lever::Pannel3_Overlapped(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		LastUpdated_Component_Index = 3;
	}
}

void AGimmick_Pannel_And_Lever::Pannel4_Overlapped(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		LastUpdated_Component_Index = 4;
	}
}



void AGimmick_Pannel_And_Lever::Door_Overlapped(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		LastUpdated_Component_Index = 6;
	}
}

void AGimmick_Pannel_And_Lever::Pannel1_EndOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		LastUpdated_Component_Index = -1;
	}
}

void AGimmick_Pannel_And_Lever::StartPannelTimer()
{
	GetWorldTimerManager().SetTimer(SwitchTimerHandler, this, &AGimmick_Pannel_And_Lever::ButtonRequiredEndTimer, 1.f, false);
	PannelWidgetRef->ButtonRequired = true;
	UE_LOG(LogTemp, Error, TEXT("Now!"));
	//Printf(TEXT("Now"));
}

void AGimmick_Pannel_And_Lever::ButtonRequiredEndTimer()
{
	PannelWidgetRef->ButtonRequired = false;
	PannelWidgetRef->PannelCnt++;
	if (PannelWidgetRef->PannelCnt > 3)
	{
		GetWorld()->GetTimerManager().ClearTimer(SwitchTimerHandler);
		GetWorld()->GetTimerManager().ClearTimer(WholeTimerHanlder);
		PannelWidgetRef->SetVisibility(ESlateVisibility::Hidden);
		PlayerController->SetInputMode(FInputModeGameOnly());

		if (CheckKey())
		{
			//PlaySound
			RemainObject--;
			DoorWidgetRef->DecrementSnake();
			(LastUpdated_Component_Index == 2? Pannel2_IsActivated : Pannel3_IsActivated) = true;
			UE_LOG(LogTemp, Warning, TEXT("Pannel Minigame Is Successed"));
		}
		else {
			//printString(TEXT("Failed"));
			UE_LOG(LogTemp, Warning, TEXT("Pannel Minigame Is Failed"));
		}

	}

}

bool AGimmick_Pannel_And_Lever::CheckKey()
{
	for (int i = 0;i < 4;i++)
	{
		if ((LastUpdated_Component_Index == 2? Pw1 : Pw2)[i] != PannelWidgetRef->PressedKey[i])
			return false;
	}
	return true;
}


void AGimmick_Pannel_And_Lever::ActivateLever()
{
	//레버 애니메이션 재생
	Lever_IsActivated = true;
	UE_LOG(LogTemp, Warning, TEXT("Lever Is Activated"));
}


void AGimmick_Pannel_And_Lever::OpenDoor()
{
	Door->SetRelativeLocation(Door->GetRelativeLocation() + FVector(0.f, 1.f, 0.f));
	if (Door->GetRelativeLocation().Y == 300)
	{
		GetWorld()->GetTimerManager().ClearTimer(SetRelativeLocationHandler);
		Door_IsActivated = true;
	}
}


void AGimmick_Pannel_And_Lever::Interact()
{
	switch (LastUpdated_Component_Index)
	{
	case 1:
		if (Pannel1_IsActivated)
			break;
		RemainObject--;
		Pannel1_IsActivated = true;
		DoorWidgetRef->DecrementSnake();
		UE_LOG(LogTemp, Warning, TEXT("Pannel1 Is Activated"));
		break;


	case 2:
		if (Pannel2_IsActivated)
			break;
		PannelWidgetRef->SetVisibility(ESlateVisibility::Visible);
		PannelWidgetRef->SetFocus();
		PlayerController->SetInputMode(FInputModeUIOnly());
		GetWorld()->GetTimerManager().ClearTimer(WholeTimerHanlder);
		GetWorld()->GetTimerManager().ClearTimer(SwitchTimerHandler);
		PannelWidgetRef->PannelCnt = 0;
		PannelWidgetRef->StopAllAnimations();
		GetWorldTimerManager().SetTimer(WholeTimerHanlder, this, &AGimmick_Pannel_And_Lever::StartPannelTimer, 3.f, true);
		UE_LOG(LogTemp, Warning, TEXT("Pannel2 Is Activated"));
		break;


	case 3:
		if (Pannel3_IsActivated)
			break;
		PannelWidgetRef->SetVisibility(ESlateVisibility::Visible);
		PannelWidgetRef->SetFocus();
		PlayerController->SetInputMode(FInputModeUIOnly());
		GetWorld()->GetTimerManager().ClearTimer(WholeTimerHanlder);
		GetWorld()->GetTimerManager().ClearTimer(SwitchTimerHandler);
		PannelWidgetRef->StopAllAnimations();
		PannelWidgetRef->PannelCnt = 0;
		GetWorldTimerManager().SetTimer(WholeTimerHanlder, this, &AGimmick_Pannel_And_Lever::StartPannelTimer, 3.f, true);
		UE_LOG(LogTemp, Warning, TEXT("Pannel3 Is Activated"));
		break;


	case 4:
		if (Pannel4_IsActivated)
			break;
		RemainObject--;
		Pannel4_IsActivated = true;
		DoorWidgetRef->DecrementSnake();
		UE_LOG(LogTemp, Warning, TEXT("Pannel4 Is Activated"));
		break;


	case 5:
		if (Lever_IsActivated)
			break;

		if (Pannel1_IsActivated && Pannel2_IsActivated && Pannel3_IsActivated && Pannel4_IsActivated)
			ActivateLever();

		break;


	case 6:
		if (Door_IsActivated){break;}
		DoorWidgetRef->SetCanvasVisibillity(ESlateVisibility::Visible);
		Player->DisableInput(PlayerController);
		GetWorld()->GetTimerManager().ClearTimer(Delay);
		GetWorld()->GetTimerManager().SetTimer(Delay, FTimerDelegate::CreateLambda([&]()
			{
				Player->EnableInput(PlayerController);
				DoorWidgetRef->SetCanvasVisibillity(ESlateVisibility::Hidden);
				if (Lever_IsActivated) { GetWorld()->GetTimerManager().SetTimer(SetRelativeLocationHandler,this,&AGimmick_Pannel_And_Lever::OpenDoor,0.016f,true);}
			}), 2.f, false); 
		UE_LOG(LogTemp, Warning, TEXT("Door Is Activated"));
		break;


	default:
		UE_LOG(LogTemp, Warning, TEXT("Default Switch Is Activated"));
		break;
	}
}