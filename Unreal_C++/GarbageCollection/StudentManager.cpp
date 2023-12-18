// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectReflection/StudentManager.h"
#include "ObjectReflection/GCStudent.h"

void FStudentManager::AddReferencedObjects(FReferenceCollector& Collector)
{
	if (SafeStudent->IsValidLowLevel())
	{
		Collector.AddReferencedObject(SafeStudent);
	}
}

