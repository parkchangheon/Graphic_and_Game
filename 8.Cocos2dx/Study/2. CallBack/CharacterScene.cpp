#include "CharacterScene.h"

USING_NS_CC;

Scene* CharacterScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CharacterScene::create();

	scene->addChild(layer);

	return scene;
}

bool CharacterScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}


