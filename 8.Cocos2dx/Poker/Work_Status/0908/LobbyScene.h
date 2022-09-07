#pragma once

#include "assets-manager/AssetsManager.h"
#include "NxScene.h"
#include "NxPanel.h"

#include "LobbyShopPanel.h"
#include "LobbyLetterBoxPanel.h"
#include "LobbyMyHomeMainPanel.h"
#include "ChannelRoomMainPanel.h"
#include "LobbyTournamentMain.h"
#include "LobbySurvivalMain.h"
#include "LobbyRewardPanel.h"
#include "LobbyTourSelectPanel.h"
#include "LobbySurvivalWindowMain.h"
#include "LobbyRankerGamePopup.h"
#include "ChannelMainPannel.h"
#include "LobbyCharacterShopPanel.h"
#include "LobbyInventoryPanel.h"
#include "NotiData.pb.h"
#include "W_NotiData.pb.h"

class LobbyUIPanel;
class LobbyBackPanel;
class LobbyFriendPanel;
class LoadingPanel;

enum LobbyZOderList
{
	ZODER_LOBBY_UI,
	ZODER_LOBBY_RANKING,
	ZODER_LOBBY_REPLAY,
	ZODER_LOBBY_MYHOME,
	ZODER_LOBBY_FRIEND,
	ZODER_LOBBY_MISSION,
	ZODER_LOBBY_LETTERBOX,
	ZODER_LOBBY_LEFTUI,
	ZODER_LOBBY_OPTION,
	ZODER_LOBBY_CHANNEL,
	ZODER_LOBBY_TOURMAMENT,
	ZODER_LOBBY_TOURMAMENT_SELECT,
	ZODER_LOBBY_SURVIVAL,
	ZODER_LOBBY_CHARACTER,
	ZODER_LOBBY_INVEN,
	ZODER_LOBBY_RECORD,
	ZODER_LOBBY_SHOP,

	ZODER_LOBBY_TOPUI,
	ZODER_LOBBY_SURVIVAL_SELECT,
	ZODER_LOBBY_REWARD_POP,
	ZODER_LOBBY_RANKER_REPLAYLIST,	
	ZODER_BANK_POPUP,
	ZODER_LOBBY_CHARACTER_INFO,
	ZODER_GOLD_REFILL_POPUP,
	ZODER_POPUP,
	ZODER_EFFECT,
	
	ZODER_BLACKBOX,
};

class LobbyScene : public Nx::Scene, public CCTargetedTouchDelegate
{
	typedef vector<W_NotiData> NotiDataContainer;
public:
	LobbyScene();
	virtual ~LobbyScene();

	virtual void onLoad();
	virtual void onPreloadDynamicSetup();
	virtual void onUnload();
	virtual void onStart();
	virtual void onStartTransitionDidFinish();
	virtual void onEnd();
	virtual void onUpdate(float dt);

	virtual void onMessage(const string& msg);
	virtual bool handling(STCMD &stCmd);
// cocos2d::extension::AssetsManagerDelegateProtocol
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onSuccess();

	void setCredentials(const string& account, const string& password, bool record = true);
	void startLoading();
	
	void ShowLobbyUiChannelList();
	
	void ReloadLobbyUiFriendList();
	void UpdateRecommendData();
	void UpdateQuestList();
	void ShowLobbyUiLetterList();
	void UpdateLetterList();
	void UpdateRankingList();
	void UpdateReplayList();
	void PopupUserReplayBox();
	void UpdateMyRoomInfo();
	
	void UpdateEventListCell();

	void ApplyUserData();
	void EnterGameRoom();
	void EnterGameRoom(int roomIdx, string password);
	void MakeGameRoom(string password);
	void RoomList(int _page, int _count);
	void ShowChannelRoom();
	void HideChannelRoom();
	void SerchRoom(int _idx);

	void LobbyVisible(bool _visible);

	void MakeBonusEffect(int _kind, CCPoint _start, CCPoint _end);
	//void LobbyFadeOut(float _delay);
	//void LobbyFadeIn(float _delay);

	void ReloadLobbyUiGameFriendList();

	void showRecordPanel();
	void startPopupPanel();

	void addNotidata(W_NotiData notidata);

private:
	void CheckStopedGame();
	void CheckNotiInfo();
	void sendW_PayReq(string tID, string txId, string receipt);
	void recvW_PayRes(HttpMessage* msg);
	void sendW_Restore();
	void recvW_Restore(HttpMessage* msg);
	
	//void InitMaskImage(CCNode* _targetNode, CCNode* _pStencilNode);
	//void AddMaskTaget(CCNode* _targetNode);
public:
	LobbyUIPanel*			m_LobbyUIPanel;
	LobbyBackPanel*			m_LobbyBackPanel;

private:
	bool m_MovePopup;
	//Layer* m_pLobbyMainLayer;
	
	//CCClippingNode* m_maskImage;
	//CCSprite* m_pStencilImage;
	//SkelObject* m_pStencilImage;
	NotiData_eNotiType mNotiType;
	bool mReplayBack;	//리플레이에서 왔다면
	NotiDataContainer mNotidatas;
	int mShowCount;
	string mGoogleTid;
};
