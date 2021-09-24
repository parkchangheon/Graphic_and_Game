// Copyright Epic Games, Inc. All Rights Reserved.

#include "C_Plus_projectGameMode.h"
#include "C_Plus_projectCharacter.h"
#include "UObject/ConstructorHelpers.h"

void AC_Plus_projectGameMode::BeginPlay() {
	Super::BeginPlay();

	//기본적인 UE_LOG 메시지
	// LogTemp는 로그 메시지를 임시 로그에 표시  , LOG 레벨 warning을 통해 노란색으로 표시,    로그 메시지 자체를 표현하는 텍스트 문자열(TEXT)

	UE_LOG(LogTemp, Warning, TEXT("Some warning message")); 

	int intVar = 5;
	float floatVar = 3.7f;
	FString fstringVar = "an fstring variable";
	UE_LOG(LogTemp, Warning, TEXT("Text, %d %f %s"), intVar, floatVar, *fstringVar);   // *은 포인터가 가리키는 실제 값을 가리키려고.


	FString name = "SEAN PARKER";
	int32 mana = 450;
	//FString string = FString::Printf(TEXT("NAME = %s  MANA=%d"), *name, mana); //FString::Printf로 출력하는 방식


	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(name));
	args.Add(FStringFormatArg(mana));

	FString string = FString::Format(TEXT("NAME = {0}  MANA={1}"), args);
	UE_LOG(LogTemp, Warning, TEXT("Your String is %s"), *string);

}



AC_Plus_projectGameMode::AC_Plus_projectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
