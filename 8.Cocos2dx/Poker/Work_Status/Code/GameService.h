/********************************************************************
	file name:	GameService.h
	
	purpose:	
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "NxSingleton.h"

/*
http://ilovepoker-staging-world.numixent.com:8200/poker_server/gateway_servlet
http ://192.168.1.184:8200/poker_server/gateway_servlet
http ://ilovepoker-live-world.numixent.com:8200/poker_server/gateway_servlet
http ://14.63.198.175:8200/poker_server/gateway_servlet
*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
static const string GAMBLE_DEFAULT_URL = "http://106.243.69.210:8200/poker_server/";		// 테스트 외부 서버
//static const string GAMBLE_DEFAULT_URL = "https://game.playpotpoker.com/poker_server/"; // 외부 아마존 NEW
static const std::string GAMBLE_GAME_URL = "";//"192.168.0.161";
//static const string GAMBLE_GAME_IP = "106.243.69.210";
static const string GAMBLE_GAME_IP = "game.playpotpoker.com";
#else
//static const std::string GAMBLE_DEFAULT_URL = "https://game.playpotpoker.com/poker_server/"; // 외부 아마존 NEW
static const string GAMBLE_DEFAULT_URL = "http://192.168.0.161:8200/poker_server/";		// 내부 서버
static const std::string GAMBLE_GAME_URL = "";//"192.168.0.161";
static const string GAMBLE_GAME_IP = "";

#endif // DEBUG

class GameService : public CCObject, public Singleton<GameService>
{
	enum StartStep
	{
		StartUp,
		LoadGameData,
		LoadUserInfo,
		LoadChatServer,
		Started,
	};

public:
	GameService();
	~GameService();

public:
	void update(float dt);

	void start();
	void stop();
	void resume();
	bool isStarted() { return mStep == Started; }
	float getProgress();
	const string& getStatus();
	void ready();

	void checkChatService(bool force = false);

	const string& getPatchPath() { return mPatchPath; }

	void reloadXml();

private:
	void sendGameDataReq();
	void recvGameDataRes(HttpMessage* msg);
	void sendUserDataReq();
	void recvUserDataRes(HttpMessage* msg);
	void sendChatServerReq();
	void recvChatServerRes(HttpMessage* msg);

	void onFailed(const string& msg);

private:
	StartStep mStep;
	string mStatus;
	string mPatchPath;
};