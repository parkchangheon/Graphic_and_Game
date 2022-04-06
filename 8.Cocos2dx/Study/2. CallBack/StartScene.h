#pragma once
#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
	//cpp 에는 id 개념이 없다 => class instance pointer를 반환
	static cocos2d::Scene* createScene();
	virtual bool init();

	//selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(StartScene); //씬 생성 코드라 보면 된다
	//create_func 메크로는 
	//Create_FUNC(HelloWorld); 로 등록을 한다면, HelloWorld 객체를 생성하기전에
	// HelloWorld* hello = HelloWorld::Create(); 와 같은 코드로 생성 가능

	//씬을 생성하는 것은 간단하다
	//auto myScene = Scene::create(); 로 생성가능


	//버튼 클릭했을때 콜백함수 구현
	void OnClickButton(Ref *object);
};




