#pragma once
#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
	//cpp ���� id ������ ���� => class instance pointer�� ��ȯ
	static cocos2d::Scene* createScene();
	virtual bool init();

	//selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(StartScene); //�� ���� �ڵ�� ���� �ȴ�
	//create_func ��ũ�δ� 
	//Create_FUNC(HelloWorld); �� ����� �Ѵٸ�, HelloWorld ��ü�� �����ϱ�����
	// HelloWorld* hello = HelloWorld::Create(); �� ���� �ڵ�� ���� ����

	//���� �����ϴ� ���� �����ϴ�
	//auto myScene = Scene::create(); �� ��������


	//��ư Ŭ�������� �ݹ��Լ� ����
	void OnClickButton(Ref *object);
};




