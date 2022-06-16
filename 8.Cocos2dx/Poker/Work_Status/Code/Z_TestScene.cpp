#include "pch.h"
#include "Z_TestScene.h"
#include "HeroApp.h"
#include "CmdQueue.h"
#include "CmdList.h"
#include "SceneUtil.h"

#define FADE_DELAY 0.5f

#ifndef GOOGLE_PLAY_TW
#define SHOW_PUBLISHER	
#define LOGO_DELAY 2.f
#else
#define LOGO_DELAY 8.f
#endif


Z_TestScene::Z_TestScene()
{
}

Z_TestScene::~Z_TestScene()
{
}

void Z_TestScene::onLoad()
{

}

void Z_TestScene::onUnload()
{
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void Z_TestScene::onStart()
{
	auto visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	auto origin = CCDirector::sharedDirector()->getVisibleOrigin();
	mIsFadeOuting = false;
	mPublisher = new Panel();
	ccColor4B bgColor = ccc4(ccWHITE.r, ccWHITE.g, ccWHITE.b, 0xFF);
	mPublisher->makeColored(bgColor);
	//mPublisher->construct("mxml/logo_screen.mxml");
	//LayerManager::getSingleton().addLayer("Logo", mPublisher);
	//LayerManager::getSingleton().initLayer(this, "Logo");
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	//필요한 것들 삽입
#ifdef PAY_GOOGLE

#else
	//mStateContainer.push_back(ONE_STORE);
#endif	
	mStateContainer.push_back(GAME_MODE);
	mStateContainer.push_back(END);
	mBg = mPublisher->getSkel("skel_logo_numix");
	setState();

	auto skeletonNode = SkeletonAnimation::createWithFile("C:/Version3_Migrate/VersionUp/Resources/ui/alluse_board_8888.json", "C:/Version3_Migrate/VersionUp/Resources/ui/alluse_board_8888.atlas");
	skeletonNode->setPosition(CCPoint(0,
		origin.y + visibleSize.height / 2));
	this->addChild(skeletonNode, 1);

	skeletonNode->setAnimation(0, "autorefill_end", true);
}

void Z_TestScene::onEnd()
{
	LayerManager::getSingleton().clear();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool Z_TestScene::handling(STCMD& stCmd)
{
	return false;
}

void Z_TestScene::onUpdate(float dt)
{
	if (CCmdQueue::getSingletonPtr())
		CCmdQueue::getSingleton().update(this);

	if (mIsFadeOuting) {
		if (mPublisher->getOpacity() == 0x00 && mPublisher->isIdle()) {
			mIsFadeOuting = false;
			setState();
		}
	}
	else {

		//fadeout 이 아닐때

		if (mStateDelay > 0.f) {
			mStateDelay -= dt;
			if (mStateDelay <= 0.f) {
				mIsFadeOuting = true;
				mPublisher->fadeOut(FADE_DELAY);
			}
		}
	}
}

bool Z_TestScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return false;
}

void Z_TestScene::setState()
{
	if (mStateContainer.size() > 0) {
		mState = mStateContainer[0];
		mStateContainer.pop_front();
		mStateDelay = 2.0f;
		if (mState == GAME_MODE)
			mStateDelay = 3.0f;

		mPublisher->fadeIn(FADE_DELAY);
		//animation 실행
		if (mState == ONE_STORE)
			mBg->playAnimation("logo_one");
		else if (mState == NUMIX)
			mBg->playAnimation("logo_numix");
		else if (mState == GAME_MODE)
			mBg->playAnimation("screen_game_rating");
		else if (mState == END) {
			//SceneUtil::changeScene(SceneUtil::SceneTitle);
		}

	}
}
