// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectChaserGameMode.h"
//#include "ProjectChaserCharacter.h"
#include "TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectChaserGameMode::AProjectChaserGameMode()
{
	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
	DefaultPawnClass = ATestCharacter::StaticClass();
}
