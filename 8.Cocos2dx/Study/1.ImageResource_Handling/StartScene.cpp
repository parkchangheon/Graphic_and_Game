#include "StartScene.h"


USING_NS_CC;   //using namespace cocos2d

Scene *StartScene::createScene() {
	auto scene = Scene::create();  //scene은 autorelease 객체이다. 즉 메모리 해제를 안해줘도 자동으로 됨
	auto layer = StartScene::create(); //layer 역시 "

	scene->addChild(layer);  //layer 
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
	auto back = Sprite::create("INU.png"); //resource 폴더에 있는..

	back->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(back);


	//title을 해당 포인트에 위치시킵니다. 화면의 가로 중앙에 위치하도록 했다.
	auto title = Sprite::create("Title.png");
	title->setAnchorPoint(Point(0.5f, 1)); //앵커포인트 변경
	title->setPosition(Point(winSize.width / 2, winSize.height - 30));
	this->addChild(title);

	auto character = Sprite::create("mugosa.png");
	character->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(character);

	//그리고 화면에 나오는 GL verts: GL calls는 버텍스 개수와 openGL이 호출된 횟수다
	//FPS는 초당 화면이 갱신되는 횟수. -> 60.1이란 60FPS


	/*****menuitemImage와 menu 클래스의 사용*****/


	//버튼추가
	//버튼은 메뉴 클래스에 담아야만 화면에 붙일 수 있다. 
	//아래버튼은 첫번째 인자가 이미지로 보이고 두번째 인자가 클릭시 보인다.
	auto button1 = MenuItemImage::create("button_ch1.png", "button_ch1_on.png", "button_ch1_dis.png", [&](Ref *sender) {});
	//[&](Ref *sender){} 은 콜백 메서드이다. 즉 이 버튼을 눌렀을때 자동으로 실행되는 메서드라고 보면됨
	//->이름없는 메서드를 즉석에서 선언않고 등록 -> 람다 방식
	button1->setEnabled(true); //해당 메서드는 버튼을 누를 수 있게할지 없게 할지 설정함. true는 누르기 가능
	button1->setPosition(Point(winSize.width / 2, 100));
	
	//menuItemImage의 create에는 normalImage와 selectImage외에도 disabledImage를 매개변수로 추가할 수 있다.
	//disabledImage란 버튼이 사용가능하지 않을때(누를 수 없을때) 표시될 이미지를 뜻함.

	//menuitem에는 menuitemsprite 등의 하위 클래스가 있고, 그 아래 MenuItemImage가 존재
	//MenuItemImage는 파일명을 받아 MenuItem을 생성하고 (MenuItem은 Menu에 추가되야 동작)
	//MenuItemSprite는 Sprite를 받아 MenuItem을 생성한다.
	
	//menuitem >> menuitemsprite >> menuitemimage
	//그러므로 menuitem을 생성한 이후에는 Menu도 생성하고, 앞에서 생성한 menuitem을 menu에 추가한다

	auto button2 = MenuItemImage::create("Button_ch2.png","button_ch1_on.png");
	button2->setPosition(Point(winSize.width / 2, 40));

	//생성된 버튼을 메뉴에 추가한다.
	auto menu = Menu::create(button1, button2, NULL); //마지막 항목에는 NULL을 입력하는 습관을 가진다
	menu->setPosition(Point::ZERO);  //버튼 위치 지정
	//menu를 붙일때는 setPoint(Point::Zero)를 꼭해준다.==>터치좌표가 정확하게 나옴
	//Point::ZERO는 point(0,0)과 같은 의미

	this->addChild(menu);
	// 버튼 종류는 메뉴에 붙여야만 보여준다.

	return true;

}






