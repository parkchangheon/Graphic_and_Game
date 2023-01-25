// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	EIR_Damaged UMETA(DisplayName = "Damaged"),
	EIR_Common UMETA(DisplayName = "Common"),
	EIR_Uncommon UMETA(DisplayName = "Uncommon"),
	EIR_Rare UMETA(DisplayName = "Rare"),
	EIR_Legendary UMETA(DisplayName = "Legendary"),
	EIR_Max UMETA(DisplayName = "DefaultMax")

};


UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_PickUp UMETA(DisplayName = "Pickup"),
	EIS_EquipInterping UMETA(DisplayName = "Pickup"),
	EIS_PickedUp UMETA(DisplayName = "Pickup"),
	EIS_Equipped UMETA(DisplayName = "Equipped"),
	EIS_Falling UMETA(DisplayName = "Falling"),
	EIS_MAX UMETA(DisplayName = "DefaultMax"),




};

UCLASS()
class SHOOTERGAME_PRO_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);


	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void SetActiveStarts();
	void SetItemProperties(EItemState State);
	void FinishInterping();
	void ItemInterp(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	//아이템 스켈레탈 메시
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"));
	USkeletalMeshComponent* ItemMesh;

	//라인트레이스가 아이템 박스와 충돌했을때, HUD 위젯을 보여준다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"));
	class UBoxComponent* CollisionBox;

	//유저가 아이템 봤을때 팝업 시킨다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* PickUpWidget;

	//아이템 오버랩 되었을때 보이게 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AreaSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	int32 ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	EItemRarity ItemRarity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	TArray<bool> ActiveStars;

	//아이템 버리고 주울때 사용
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	EItemState ItemState;

	//Curve Assets to use for the item's Z Location when Interping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	class UCurveFloat* ItemZCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	FVector ItemInterpStartLocation;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	FVector CameraTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	bool bInterping;



	FTimerHandle ItemInterpTimer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	float ZCurveTime;

	//pointer to the character 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	class AShooterCharacter* Character;

	float ItemInterpX;
	float ItemInterpY;

	float InterpInitialYawOffset; // 카메라와 아이템 사이 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Property", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* ItemScaleCurve;

public:
	FORCEINLINE UWidgetComponent* GetPickUpWidget() const { return PickUpWidget; }
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }
	FORCEINLINE UBoxComponent* GetCollisionBox() const { return CollisionBox; }
	FORCEINLINE EItemState GetItemState() const { return ItemState; }
	void SetItemState(EItemState State);
	FORCEINLINE USkeletalMeshComponent* GetItemMesh() const { return ItemMesh; }

	void StartItemCurve(AShooterCharacter* Char);


};
