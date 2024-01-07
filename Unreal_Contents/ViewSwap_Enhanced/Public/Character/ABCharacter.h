
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

UENUM()
enum class ECharacterControlType : uint8 
{
	Shoulder,
	Quater
};

UCLASS()
class TESTTT_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AABCharacter();

protected:
	virtual void SetCharacterControlData(const class UABChracterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta=(AllowPrivate = "true"))
	TMap<ECharacterControlType, class UABChracterControlData*> CharacterControlManager;
};
