#pragma once
#include "cocos2d.h"
class StartScene : public cocos2d::Layer
{
public:
	//cpp 에는 id 개념이 없다 => class instance pointer를 반환
	static cocos2d::Scene* createScene();
	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(StartScene);
};




