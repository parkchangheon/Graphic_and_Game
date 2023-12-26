#include "CommonUtility.h"
#include "Modules/ModuleManager.h"



//모듈 선언. 38:17 로 돌아갈것.
//IMPLEMENT_MODULE_GAME_MODULE();게임 모듈 : 게임제작에 관련있음.
//IMPLEMENT_MODULE_PRIMARY_GAME_MODULE() : 게임 주 모듈 : 게임의 주요 기능들이 모여있음.


IMPLEMENT_MODULE(FDefaultModuleImpl, CommonUtility);	//일반 모듈 : 게임과 직접적인 연관은 없지만 유용한 기능을 제공한다.

