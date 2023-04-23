// Fill out your copyright notice in the Description page of Project Settings.


#include "../Data/DataManager.h"
#include "Engine/DataTable.h"


const FABCharacterData UDataManager::GetCharacterData(const FName InCharacterName) const
{
	if(auto* CharData = CharacterDataTable->FindRow<FABCharacterData>(InCharacterName, TEXT("")))
		return *CharData;

	return FABCharacterData();
}
