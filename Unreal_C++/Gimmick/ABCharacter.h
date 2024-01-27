
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/ABAnimationAttackInterface.h"
#include "Interface/ABCharacterWidgetInterface.h"
#include "Interface/ABCharacterItemInterface.h"

#include "ABCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogABCharacter, Log, All);

UENUM()
enum class ECharacterControlType : uint8 
{
	Shoulder,
	Quater
};

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UABItemData*);
USTRUCT(BlueprintType)
struct FTakeItemDelegateWrapper
{
	GENERATED_BODY()
	FTakeItemDelegateWrapper() {}
	FTakeItemDelegateWrapper(const FOnTakeItemDelegate& InItemDelegate) : ItemDelegate(InItemDelegate) {}


	FOnTakeItemDelegate ItemDelegate;
};

UCLASS()
class TESTTT_API AABCharacter : public ACharacter, public IABAnimationAttackInterface, public IABCharacterWidgetInterface, public IABCharacterItemInterface
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


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Equipment, Meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> Weapon;
	
	//하드 레퍼런싱.
	//TobjectPtr -> 액터 로딩시, TObjectPtr로 선언한 언리얼 오브젝트도 따라서 메모리에 로딩.

	//필요한 데이터만 로딩하도록 TSoftObjectPtr로 선언하고 대신 애셋 주소 문자열을 지정.

	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemActions;

	virtual void TakeItem(class UABItemData* InItemData) override;

	virtual void DrinkPotion(class UABItemData* InItemData) ;
	virtual void EquipWeapon(class UABItemData* InItemData) ;
	virtual void ReadScroll(class UABItemData* InItemData) ;

};
