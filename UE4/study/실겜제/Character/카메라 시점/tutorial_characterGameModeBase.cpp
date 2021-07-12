// Copyright Epic Games, Inc. All Rights Reserved.


#include "tutorial_characterGameModeBase.h"
#include "ARPlayer.h" // include 해준다.

Atutorial_characterGameModeBase::Atutorial_characterGameModeBase() {

	//여기서object는 실제 객체를 class는 어떤 클래스로 정의를 하는것.
	DefaultPawnClass = AARPlayer::StaticClass(); // 생성자로 하여금 .. 그 캐릭터로 설정해준다.(시작할떄)
}