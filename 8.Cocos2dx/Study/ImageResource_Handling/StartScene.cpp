#include "StartScene.h"


USING_NS_CC;   //using namespace cocos2d

Scene *StartScene::createScene() {
	auto scene = Scene::create();
	auto layer = StartScene::create();

	scene->addChild(layer);
	return scene;
}


bool StartScene::init()
{
	if (!Layer::init())
		return false;

	/*****디바이스의 크기를 가져옵니다.*****/

	//director를 가져옵니다.
	auto director = Director::getInstance();

	//OpenGLView를 가져옵니다.
	auto glview = director->getOpenGLView();

	//OpenGL에서 DesingResolutionSize를 가져옵니다.
	auto winSize = glview->getDesignResolutionSize();



	/*****배경 이미지 back을 넣습니다.****/
	//Sprite 생성하여 이미지 삽입
	auto back = Sprite::create("INU.png");

	back->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(back);


	return true;

}





