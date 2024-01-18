
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/ABAnimationAttackInterface.h"
#include "Interface/ABCharacterWidgetInterface.h"

#include "ABCharacter.generated.h"

UENUM()
enum class ECharacterControlType : uint8 
{
	Shoulder,
	Quater
};

UCLASS()
class TESTTT_API AABCharacter : public ACharacter, public IABAnimationAttackInterface, public IABCharacterWidgetInterface
{
	GENERATED_BODY()

public:
	AABCharacter();

	virtual void PostInitializeComponents()override;

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


	//Attack Hit Section
protected:
	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

//Dead Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animation)
	TObjectPtr<class UAnimMontage> DeadActionMontage;

	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;


	//Stat Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Stat, Meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UABCharacterStatComponent> Stat;

//UI Widget
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Stat, Meta=(AllowPrivateAccess="true"))
	TObjectPtr<class UABWidgetComponent> HpBar;

	virtual void SetupCharacterWidget(class UABUserWidget* InUserWidget)override;

};
