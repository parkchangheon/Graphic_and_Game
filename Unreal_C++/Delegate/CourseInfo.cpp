// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectReflection/CourseInfo.h"

UCourseInfo::UCourseInfo()
{
	Contents = TEXT("Origin Info of academic");
}

void UCourseInfo::ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents)
{
	Contents = InNewContents;
	UE_LOG(LogTemp, Warning, TEXT("[CourseInfo] 학사 정보가 변경되어 알림을 전송합니다."));

	CourseInfoOnChanged.Broadcast(InSchoolName, InNewContents);
	// CourseInfoChanged에 연결된 모든 함수들에게 BroadCast.


}
