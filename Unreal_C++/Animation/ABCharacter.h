
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


	//combo Action Section
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAcces="true"))
	TObjectPtr<class UABComboActionData> ComboActionData;

	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnd);
	void SetComboTimerCheck();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;
};
