// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABStageGimmick.generated.h"

DECLARE_DELEGATE(FOnStageChangedDelegate);
USTRUCT(BlueprintType)
struct FStageChangedDelegateWrapper
{
	GENERATED_BODY()
	FStageChangedDelegateWrapper() { }
	FStageChangedDelegateWrapper(const FOnStageChangedDelegate& InDelegate) : StageDelegate(InDelegate) {}
	FOnStageChangedDelegate StageDelegate;
};

UENUM(BlueprintType)
enum class EStageState : uint8
{
	READY = 0,
	FIGHT,
	REWARD,
	NEXT
};


UCLASS()
class TESTTT_API AABStageGimmick : public AActor
{
	GENERATED_BODY()
	
public:	
	AABStageGimmick();

protected:
	virtual void OnConstruction(const FTransform& Transform);

protected:
	UPROPERTY(VisibleAnywhere, Category=Stage, Meta = (AllowPrivateAccess="true"))
	TObjectPtr<class UStaticMeshComponent> Stage;

	UPROPERTY(VisibleAnywhere, Category=Stage, Meta = (AllowPrivateAccess="true"))
	TObjectPtr<class UBoxComponent> StageTrigger;

	UFUNCTION()
	void OnStageTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, Category=Gate, Meta = (AllowPrivateAccess="true"))
	TMap<FName, TObjectPtr<class UStaticMeshComponent>> Gates;

	UPROPERTY(VisibleAnywhere, Category=Gate, Meta = (AllowPrivateAccess="true"))
	TArray<TObjectPtr<class UBoxComponent>> GateTriggers;

	UFUNCTION()
	void OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OpenAllGates();
	void CloseAllGates();

protected:
	UPROPERTY(EditAnywhere, Category = Stage, Meta=(AllowPrivateAccess = "true"))
	EStageState CurrentState;

	void SetState(EStageState InNewState);

	UPROPERTY()
	TMap<EStageState, FStageChangedDelegateWrapper> StateChangeActions;

	void SetReady();
	void SetFight();
	void SetChooseReward();
	void SetChooseNext();


protected:
	UPROPERTY(EditAnywhere, Category=Fight, Meta=(AllowPrivateAccess="true"))
	TSubclassOf<class AABCharacterNonPlayer> OpponentClass;

	UPROPERTY(EditAnywhere, Category=Fight, Meta=(AllowPrivateAccess="true"))
	float OpponentSpawnTime;

	UFUNCTION()
	void OnOpponentDestroyed(AActor* DetroyedActor);

	FTimerHandle OpponentTimerHandle;
	void OnOpponentSpawn();

protected:
	UPROPERTY(EditAnywhere, Category=Reward, Meta=(AllowPrivateAccess="true"))
	TSubclassOf<class AABItemBox> RewardBoxClass;

	UPROPERTY(EditAnywhere, Category=Reward, Meta=(AllowPrivateAccess="true"))
	TArray<TWeakObjectPtr<class AABItemBox>> RewardBoxes;	
	//스테이지 기믹 액터와는 무관하게 스스로 동작.
	//TObjectPtr = 강참조 -> UnrealEngine은 아직도 사용된다고 판단하여 메모리에서 소멸시키지 않음.
	//TWeakObjectPtr = 약참조 -> 무관하지만 내가 관리해야한다고 생각되면 참조.


	TMap<FName, FVector> RewardBoxLocations;

	UFUNCTION()
	void OnRewardTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SpawnRewardBoxes();

};
