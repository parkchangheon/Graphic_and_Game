// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Data/CharacterDataTables.h"
#include "DataManager.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API UDataManager : public UObject
{
	GENERATED_BODY()
	
public:
	const FABCharacterData GetCharacterData(const FName InCharacterName) const;

	static UDataManager* Ptr;

private:
	UPROPERTY()
	const class UDataTable* CharacterDataTable;
};
