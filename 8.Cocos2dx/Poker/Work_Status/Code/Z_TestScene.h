/********************************************************************
	file name:	LogoScene.h

	purpose:	로고 출력 장면
*********************************************************************/
#pragma once

class Z_TestScene : public Scene, public CCTargetedTouchDelegate
{
	enum LogoSceneState {
		ONE_STORE,	//원스토어
		NUMIX,		//누믹스
		GAME_MODE,	//게임 모드
		END,		//끝
	};

	typedef deque<LogoSceneState> StateContainer;

public:
	Z_TestScene();
	virtual ~Z_TestScene();

	virtual void onLoad();
	virtual void onUnload();

	virtual void onStart();
	virtual void onEnd();
	virtual void onUpdate(float dt);

	virtual bool handling(STCMD& stCmd);

public: // CCTargetedTouchDelegate
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);

public:
	LogoSceneState mState;
	Layer* mBackground;
	Panel* mPublisher;
	bool mSkip;
	bool mAuth;

private:
	StateContainer mStateContainer;
	SkelObject* mBg;
	float mStateDelay;
	void setState();
	float mDelay;
	bool mIsFadeOuting;
};
