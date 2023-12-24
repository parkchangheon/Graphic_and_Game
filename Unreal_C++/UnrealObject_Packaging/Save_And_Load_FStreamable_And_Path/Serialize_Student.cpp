// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectReflection/Serialize_Student.h"

USerialize_Student::USerialize_Student()
{
	Order = -1;
	Name = TEXT("Gildong Hong");

}

void USerialize_Student::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	Ar << Order;
	Ar << Name;



}
