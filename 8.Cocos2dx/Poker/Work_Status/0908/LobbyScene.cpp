#include "pch.h"
#include "LobbyScene.h"
#include "LobbyUIPanel.h"
#include "LobbyBackPanel.h"
#include "TypeDefine.pb.h"
#include "SoundDataMgr.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "socket/TCPService.h"

#include "W_RestorePayReq.pb.h"
#include "W_RestorePayRes.pb.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#include "android/IGAWorksManager.h"
#endif
#include "base64util.h"
#include "HeroUtil.h"
#include "HeroApp.h"
#include "SceneUtil.h"

#include "SimplePopupPanel.h"
#include "LobbyFriendPanel.h"
#include "CmdQueue.h"
#include "NotiFocusPanel.h"
#include "NotiDataManager.h"
#include "LobbyMissionPanel.h"
#include "PanelHelper.h"
#include "PokerRankHelper.h"
#include "LimitedGoodPanel.h"
#include "W_PayReq.pb.h"
#include "W_PayRes.pb.h"


#ifdef _DEBUG
#define PATCH_ENABLED 1
#define INTRO_ENABLED 0	//0 이면 안 나오게
#else
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#ifdef TEST
#define PATCH_ENABLED 0
#else
#define PATCH_ENABLED 0
#endif
#define INTRO_ENABLED 1
#else // CC_PLATFORM_WIN32
#define PATCH_ENABLED 0
#define INTRO_ENABLED 1
#endif
#endif

#define GOLD_REFILL_POPUP_OCCUR_MONEY 5000000

#define USE_TUTORIAL

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/IGAWorksManager.h"
#include "android/AdmobManager.h"
#include "android/IapManager.h"
#endif

LobbyScene::LobbyScene()
{
	mGoogleTid = "";
	mShowCount = 0;
	m_LobbyBackPanel = nullptr;
	m_LobbyUIPanel = nullptr;			
}

LobbyScene::~LobbyScene()
{
	
}

void LobbyScene::onLoad()
{
	//SoundDataMgr::getSingleton().loadSceneSound("MenuScene");
	m_LobbyBackPanel = nullptr;
	m_LobbyUIPanel = nullptr;			
}

void LobbyScene::onUnload()
{
	//SoundDataMgr::getSingleton().unloadSceneSound("MenuScene");

	CCTextureCache::sharedTextureCache()->removeUnusedTextures();

	//m_maskImage->cleanup();
	//m_maskImage->removeFromParent();
	//m_maskImage = nullptr;
}

void LobbyScene::onStart()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//AdmobManager::getSingleton().hideAdmob();
#endif

	++mShowCount;
	mReplayBack = false;
	if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_music == true)
		SoundManager::getSingletonPtr()->playBGM("BGM_Lobby");

	m_LobbyBackPanel = new LobbyBackPanel();
	m_LobbyUIPanel = new LobbyUIPanel();

	LayerManager::getSingleton().addLayer("LobbyBack", m_LobbyBackPanel);
	LayerManager::getSingleton().initLayer(this, "LobbyBack");
	LayerManager::getSingleton().addLayer("LobbyUI", m_LobbyUIPanel);
	LayerManager::getSingleton().pushLayer("LobbyUI");	

	//m_LobbyUIPanel->InitLeftUiPanel();
	m_LobbyUIPanel->InitTopUiPanel();
	m_LobbyUIPanel->setShowCount(mShowCount);

	CCSize size = CCDirector::sharedDirector()->getWinSize() / 2.f;	
	CheckStopedGame();
	mNotiType = NotiData_eNotiType_NoType;
	if (m_MovePopup == true)
	{
		m_MovePopup = false;
	}
	else
	{
		const CSJson::Value& params = getParams();
		if (params.isMember("LOBBY_UI_CHANNELLIST")){
			//type = NotiDataManager::getSingleton().getEnterChannelNoti();		//chanenlist 창 뜰때 본다.
			mNotiType = NotiData_eNotiType_NoType;			
			WebService::getSingletonPtr()->SendChannelListReq();
			WebService::getSingletonPtr()->SendRefreshReq();
		}
		else if (params.isMember("LOBBY_UI_TOURNAMENT_SELECT")){			 			
			GameDataManager::getSingletonPtr()->CheckTournamentEnd();
		}
		else  if (params.isMember("LOBBY_UI_SURVIVAL_SELECT")){						
			GameDataManager::getSingletonPtr()->CheckDeathmatchEnd();
		}
		else if (params.isMember("REPLAY")) {
			mReplayBack = true;
			GameDataManager::getSingleton().setBeforeRepute(PokerRankHelper::getNowRepute());
			GameDataManager::getSingleton().setBeforeReputeRatio(PokerRankHelper::getRatioRepute());
			WebService::getSingletonPtr()->TournamentInfoReq();
		}
		else if (params.isMember("FIRST_ENTER")) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			IGAWorksManager::getSingleton().LoadPopup();
#endif
			mNotiType = NotiDataManager::getSingleton().getLobbyNoti();
			m_LobbyUIPanel->applyData();
			startPopupPanel();			

		}
		else
		{
			mNotiType = NotiDataManager::getSingleton().getLobbyNoti();			
			WebService::getSingletonPtr()->SendRefreshReq();
		}
	}	
	m_LobbyUIPanel->applyUserData();



	WebService::getSingletonPtr()->sendNoticeinfoReq();
	//vector<W_LimitShopData_eLimitType> types;
	//types.push_back(W_LimitShopData_eLimitType::W_LimitShopData_eLimitType_l_made);
	//WebService::getSingletonPtr()->sendLimitedReq(types);


	LobbyScene::sendW_Restore();

}

void LobbyScene::CheckStopedGame()
{
	//NZ창헌
	return;
	m_MovePopup = false;

	if (GameDataManager::getSingletonPtr()->m_hasSurvivalGameInfo && !GameDataManager::getSingletonPtr()->m_bDeathmatchEnd)
	{
		GameDataManager::getSingletonPtr()->ClearUiState();
		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_MAIN);

		GameDataManager::getSingletonPtr()->m_hasSurvivalGameInfo = false;

		string _OkMsg = "GO_GAME_SURVIVAL";
		string _title = GameStringDepot::getSingleton().getString("TXT_DIRECT_GAME_START_TITLE");
		string _content = GameStringDepot::getSingleton().getString("TXT_DIRECT_GAME_SURVIVAL_DESC");
		SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _content, _title);
		if (_popupPanel)
		{
			_popupPanel->SetOkEventMsg(_OkMsg);
			_popupPanel->setListener(WebService::getSingletonPtr());
			LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);

			m_MovePopup = true;
		}
	}

	if (GameDataManager::getSingletonPtr()->m_hasTourGameInfo)
	{
		GameDataManager::getSingletonPtr()->ClearUiState();
		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_MAIN);

		GameDataManager::getSingletonPtr()->m_hasTourGameInfo = false;

		string _OkMsg = "GO_GAME_TOURNAMENT";
		string _title = GameStringDepot::getSingleton().getString("TXT_DIRECT_GAME_START_TITLE");
		string _content = GameStringDepot::getSingleton().getString("TXT_DIRECT_GAME_TOURNAMENT_DESC");
		SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _content, _title);
		if (_popupPanel)
		{
			_popupPanel->SetOkEventMsg(_OkMsg);
			_popupPanel->setListener(WebService::getSingletonPtr());
			LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);

			m_MovePopup = true;
		}
	}
}

void LobbyScene::CheckNotiInfo()
{
	if (GameDataManager::getSingletonPtr()->m_TourOfInfo == nullptr)
		return;

	if (GameDataManager::getSingletonPtr()->m_TourOfInfo->has_noticeinfo())
	{
		W_TourNoticeInfo _noti = GameDataManager::getSingletonPtr()->m_TourOfInfo->noticeinfo();

		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

		if (_pScene->m_LobbyUIPanel == nullptr)
			return;

		LobbyRewardPanel* pPanel = new LobbyRewardPanel(REWARD_TOURNAMENT);
		pPanel->init();
		pPanel->SetType(REWARD_TOURNAMENT);
		LayerManager::getSingletonPtr()->pushDynamicLayer(pPanel , DYNAMIC_PUSH_LAYER);
		if (pPanel)
		{
			int64 _gold = 0;
			int _fame = 0;

			int _size = _noti.rewardinfo().rewardset_size();
			for (int _i = 0; _i < _size; _i++)
			{
				W_RewardInfo_RewardSet _rewardset = _noti.rewardinfo().rewardset(_i);
				switch (_rewardset.type())
				{
				case CASH:
					break;
				case GAMEMONEY:
					_gold = _rewardset.amount();
					break;
				case CHIP:
					break;
				case REPUTE:
					_fame = _rewardset.amount();
					break;
				case CHARACTER:
					break;
				case TOUR_TICKET:
					break;
				}
			}
			pPanel->SetTitleText(_noti.title(), GameMode::MODE_NORMAL_TOURNAMENT);
			pPanel->SetMyRank(_noti.rank(), _noti.maxcnt());
			pPanel->SetRewardGold(_gold);
			pPanel->SetRewardFame(_fame);
			pPanel->SetDesc(_noti.desc());		
		}
	}

	if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo == nullptr)
		return;

	if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->has_noticeinfo())
	{
		W_DeathMatchNoticeInfo _noti = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo->noticeinfo();
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

		if (_pScene == nullptr)
			return;

		if (_pScene->m_LobbyUIPanel == nullptr)
			return;

		LobbyRewardPanel* pPanel = new LobbyRewardPanel(REWARD_TOURNAMENT);
		pPanel->init();
		pPanel->SetType(REWARD_TOURNAMENT);
		LayerManager::getSingletonPtr()->pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
		if (pPanel)
		{
			int64 _gold = 0;
			int _fame = 0;

			int _size = _noti.rewardinfo().rewardset_size();
			for (int _i = 0; _i < _size; _i++)
			{
				W_RewardInfo_RewardSet _rewardset = _noti.rewardinfo().rewardset(_i);
				switch (_rewardset.type())
				{
				case CASH:
					break;
				case GAMEMONEY:
					_gold = _rewardset.amount();
					break;
				case CHIP:
					break;
				case REPUTE:
					_fame = _rewardset.amount();
					break;
				case CHARACTER:
					break;
				case TOUR_TICKET:
					break;
				}
			}

			pPanel->SetTitleText(_noti.title(), GameMode::MODE_SURVIVAL_TOURNAMENT);
			pPanel->SetMyRank(_noti.rank(), _noti.maxcnt());
			pPanel->SetRewardGold(_gold);
			pPanel->SetRewardFame(_fame);
			pPanel->SetDesc(_noti.desc());
		}		
	}
}

void LobbyScene::onEnd()
{
	LayerManager::getSingleton().clear();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//AdmobManager::getSingleton().hideAdmob();	
#endif
}

void LobbyScene::onUpdate(float dt)
{
	if (CCmdQueue::getSingletonPtr())
		CCmdQueue::getSingleton().update(this);	//자바 명령 전달용.

	if (GameDataManager::getSingleton().isDisplayTimeAni()) {
		PanelHelper::pushGamePlayTimePanel();
		GameDataManager::getSingleton().setDisplayTimeAni(false);
	}

	if (mReplayBack && LayerManager::getSingleton().isCurrentLayerType<LobbyTournamentMain>()) {		
		//만약 toucment 창 뜨면 추가로 창 띄운다.
		PanelHelper::pushReplayPanel();
		mReplayBack = false;
	}
}

void LobbyScene::onMessage(const string& msg)
{
	if (msg == "SetFacebookFriendList") {
		if (LayerManager::getSingleton().hasLayerType<LobbyFriendPanel>()){
			LobbyFriendPanel* lobbyFriendPanel = dynamic_cast<LobbyFriendPanel*>(LayerManager::getSingleton().getLayerType<LobbyFriendPanel>());
			if (lobbyFriendPanel) {
				lobbyFriendPanel->facebookRefresh();
			}
		}
	}	
}

void LobbyScene::setCredentials(const string& account, const string& password, bool record /*= true*/)
{
	
}

void LobbyScene::startLoading()
{
}

void LobbyScene::onStartTransitionDidFinish()
{
}

bool LobbyScene::handling(STCMD &stCmd)
{
	if (auto *pstIt = castCMD<STCMD_IAP_GOOGLESTORE_CHECK_REQUEST_RESULT>(&stCmd))
	{
		STCMD_IAP_GOOGLESTORE_CHECK_REQUEST_RESULT res = *pstIt;
		if (res.isSucess) {
			mGoogleTid = res.inappId;
			CCLog("res.tid = %s", res.tid.c_str());
			sendW_PayReq(res.tid, res.orderId, res.purchaseToken);
		}
		return true;
	}

	if (auto* pstIt = castCMD<STCMD_IAP_ONESTORE_REQUEST_RESULT>(&stCmd))
	{
		STCMD_IAP_ONESTORE_REQUEST_RESULT res = *pstIt;
		if (res.isSucess) {
			CCLog("STCMD_IAP_REQUEST_RESULT sucess res.tid = %s , res.txid = %s , res.receipt = %s", res.tid.c_str(), res.txid.c_str(), res.receipt.c_str());
			sendW_PayReq(res.tid, res.txid, res.receipt);
		}
		else {
			CCLog("STCMD_IAP_REQUEST_RESULT false");
			SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errMsg, "IAP Request");
			LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
		}
		return true;
	}


	return false;
}

void LobbyScene::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void LobbyScene::onSuccess()
{
	SceneUtil::changeScene(SceneUtil::SceneFight);
}

//void LobbyScene::InitMaskImage(CCNode* _targetNode, CCNode* _pStencilNode)
//{
	//if (m_maskImage)
	//	return;

	//m_maskImage = CCClippingNode::create();
	//m_maskImage->setInverted(false);
	//m_maskImage->setAlphaThreshold(0);
	//m_maskImage->addChild(_targetNode);
	//m_maskImage->setStencil(_pStencilNode);	

	//m_pLobbyMainLayer = new Layer();
	//m_pLobbyMainLayer->addChild(m_maskImage);
	//
	//LayerManager::getSingletonPtr()->addLayer("LobbyMainLayer", m_pLobbyMainLayer);
	//LayerManager::getSingletonPtr()->initLayer(this, "LobbyMainLayer");

	//_targetNode->release();
//}

//void LobbyScene::AddMaskTaget(CCNode* _targetNode)
//{
//	if (m_maskImage == nullptr)
//		return;
//
//	m_maskImage->addChild(_targetNode);
//	_targetNode->release();
//}

void LobbyScene::ShowLobbyUiChannelList()
{
	if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_music == true)
		SoundManager::getSingletonPtr()->playBGM("BGM_CHANNEL");

	if (m_LobbyUIPanel)
	{
		m_LobbyUIPanel->SetChannel();
	}


	if (GameDataManager::getSingletonPtr()->getPutOut() != PUTOUT_NO)
	{
		switch (GameDataManager::getSingletonPtr()->getPutOut())
		{
		case PUTOUT_LOSS_MONEY_DAY:
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, GameStringDepot::getSingleton().getString("TXT_ERROR_LOSS_MONEY_LIMIT_DAY")), DYNAMIC_PUSH_LAYER);
			break;
		case PUTOUT_PLAY_MIN_MONEY:
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, GameStringDepot::getSingleton().getString("TXT_ERROR_PLAY_MIN_MONEY")), DYNAMIC_PUSH_LAYER);
			break;
		default:
			break;
		}
		GameDataManager::getSingletonPtr()->SetPutOut(PUTOUT_NO);
	}
}

void LobbyScene::ReloadLobbyUiGameFriendList()
{
	m_LobbyUIPanel->applyUserData();
	m_LobbyUIPanel->ReloadFriendUi();	
}

void LobbyScene::ReloadLobbyUiFriendList()
{
	m_LobbyUIPanel->applyUserData();
	m_LobbyUIPanel->ReloadFriendUi();
}

void LobbyScene::UpdateRecommendData()
{
	//기덕개발	
	//m_pLobbyFriendPanel->m_pRecommendPanel->UpdateRecommendCellData();
}

void LobbyScene::RoomList(int _page, int _count)
{
	//int _id = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_id;

	//GameDataManager::getSingletonPtr()->m_RoomId = _id;
	//GameDataManager::getSingletonPtr()->m_BettingRule = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_bettingRule;
	//GameDataManager::getSingletonPtr()->m_seedMoney = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_seedMoney;

	//TCPService::getSingletonPtr()->SendRoomListReq(_id, _page, _count);
	
	int _id = GameDataManager::getSingletonPtr()->m_RoomId;
	TCPService::getSingletonPtr()->SendRoomListReq(_id, _page, _count);
}

void LobbyScene::SerchRoom(int _idx)
{
	//int _index = m_LobbyUIPanel->m_ChannelPanel->m_SelectedIndex;
	//int _id = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_index]->m_id;
	//TCPService::getSingletonPtr()->SendSerchRoomReq(_id, _idx);

	
	int _id = GameDataManager::getSingletonPtr()->m_RoomId;
	TCPService::getSingletonPtr()->SendSerchRoomReq(_id, _idx);
}

void LobbyScene::EnterGameRoom()
{
	//int _idx = m_LobbyUIPanel->m_ChannelPanel->m_SelectedIndex;
	//int _id = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_id;

	//GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney1 = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_bigpot_1;
	//GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney2 = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_bigpot_2;
	//GameDataManager::getSingletonPtr()->m_BettingRule = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_bettingRule;
	//
	//TCPService::getSingletonPtr()->SendEnterRoomReq(_id);
	int _id = GameDataManager::getSingletonPtr()->m_RoomId;
	TCPService::getSingletonPtr()->SendEnterRoomReq(_id);
}

void LobbyScene::EnterGameRoom(int roomIdx, string password)
{
	//int _idx = m_LobbyUIPanel->m_ChannelPanel->m_SelectedIndex;
	//int _id = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_id;

	//GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney1 = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_bigpot_1;
	//GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney2 = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_bigpot_2;

	//TCPService::getSingletonPtr()->SendEnterRoomReq(_id, roomIdx, password);

	int _id = GameDataManager::getSingletonPtr()->m_RoomId;

	if (GameDataManager::getSingletonPtr()->m_GameMode != GameMode::MODE_NORMAL)
	{
		TCPService::getSingletonPtr()->SendEnterTournamentRoomReq(_id, roomIdx, password);
	}
	else
	{
		TCPService::getSingletonPtr()->SendEnterRoomReq(_id, roomIdx, password);
	}
}

void LobbyScene::MakeGameRoom(string password)
{
	//int _idx = m_LobbyUIPanel->m_ChannelPanel->m_SelectedIndex;
	//int _id = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_id;

	//GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney1 = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_bigpot_1;
	//GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney2 = m_LobbyUIPanel->m_ChannelPanel->m_CellDataList[_idx]->m_bigpot_2;

	//TCPService::getSingletonPtr()->SendMakeRoomReq(_id, password);

	int _id = GameDataManager::getSingletonPtr()->m_RoomId;
	TCPService::getSingletonPtr()->SendMakeRoomReq(_id, password);
}

void LobbyScene::UpdateQuestList()
{
	m_LobbyUIPanel->applyUserData();	
	if (LayerManager::getSingleton().hasLayerType<LobbyMissionPanel>()){
		LobbyMissionPanel* lobbyMissionPanel = dynamic_cast<LobbyMissionPanel*>(LayerManager::getSingleton().getLayerType<LobbyMissionPanel>());
		if (lobbyMissionPanel) {
			lobbyMissionPanel->SetMissionlList();
		}
	}
}

void LobbyScene::ShowLobbyUiLetterList()
{
	//switch (m_LobbyUIPanel->m_UiState)
	//{
	//case LOBBY_UI_7POKER:
	//	m_LobbyUIPanel->HideGameButton();
	//	m_LobbyUIPanel->HideMenuButton();
	//	break;
	//case LOBBY_UI_HIGHLOW:
	//	m_LobbyUIPanel->HideGameButton();
	//	m_LobbyUIPanel->HideMenuButton();
	//	break;
	//case LOBBY_UI_BADUKI:
	//	m_LobbyUIPanel->HideGameButton();
	//	m_LobbyUIPanel->HideMenuButton();
	//	break;
	//case LOBBY_UI_HOLDEM:
	//	m_LobbyUIPanel->HideGameButton();
	//	m_LobbyUIPanel->HideMenuButton();
	//	break;
	//}

	m_LobbyUIPanel->SetLetterBoxUi();
}

void LobbyScene::UpdateLetterList()
{
	m_LobbyUIPanel->applyUserData();
	//m_pLetterBoxPanel->SetLetterlList();
}

void LobbyScene::UpdateRankingList()
{
	if (m_LobbyUIPanel->m_UiState == LOBBY_UI_RANKING_PROCESS)
	{
		m_LobbyUIPanel->SetRanking();
	}	
}

void LobbyScene::UpdateReplayList()
{
	if (m_LobbyUIPanel->m_UiState == LOBBY_UI_REPLAY_PROCESS)
	{
		m_LobbyUIPanel->SetReplayUi();
	}
	else if (m_LobbyUIPanel->m_UiState == LOBBY_UI_REPLAY)
	{
		//기덕개발
		//m_pReplayPanel->SetReplayList();
	}
}

void LobbyScene::PopupUserReplayBox()
{
	if (m_LobbyUIPanel->m_UiState == LOBBY_UI_RANKING)
	{
		
	}	
}

void LobbyScene::ApplyUserData()
{
	m_LobbyUIPanel->applyUserData();
	UpdateMyRoomInfo();
}

void LobbyScene::UpdateMyRoomInfo()
{
// 	if (m_pMyHomePanel == nullptr)
// 		return;
// 
// 	if (m_pMyHomePanel->_pBasicPanel)
// 	{
// 		m_pMyHomePanel->_pBasicPanel->SetUserInfo();
// 		m_pMyHomePanel->_pBasicPanel->SetMyCharacter();
// 	}
// 	if (m_pMyHomePanel->_pRecordPanel)
// 	{
// 		m_pMyHomePanel->_pRecordPanel->UpdateRankInfo();
// 	}	
	m_LobbyUIPanel->makeUserCharacter();
	//m_LobbyUIPanel->UpdateUserCharacter();
}

void LobbyScene::UpdateEventListCell()
{
	m_LobbyUIPanel->applyUserData();		
}

void LobbyScene::ShowChannelRoom()
{
	m_LobbyUIPanel->setVisible(false);
	m_LobbyBackPanel->setVisible(false);		
}

void LobbyScene::HideChannelRoom()
{
	m_LobbyUIPanel->setVisible(true);
	m_LobbyBackPanel->setVisible(true);			
}

void LobbyScene::LobbyVisible(bool _visible)
{
	if (m_LobbyUIPanel)	
		m_LobbyUIPanel->setVisible(_visible);
	if (m_LobbyBackPanel)
		m_LobbyBackPanel->setVisible(_visible);			
}

void LobbyScene::showRecordPanel()
{
	m_LobbyUIPanel->showRecordUi();
}

void LobbyScene::startPopupPanel()
{
	vector<Panel*> visibleLayer;
	m_LobbyUIPanel->applyData();
	HeroApp::getSingleton().setConnected(true);

	for (int _i = 0; _i < mNotidatas.size(); _i++)
	{
		W_NotiData _data = mNotidatas[_i];		
		CCLOG("index = %d desc = %s , title = %s", _i, _data.desc().c_str(), _data.title().c_str());
		Panel* popupPanel = PanelHelper::pushNotiPanel(_data);
		visibleLayer.push_back(popupPanel);
	}
	mNotidatas.clear();	
	//기존에 떠 있는 팝업창
	if (LayerManager::getSingleton().hasLayerType<LimitedGoodPanel>()) {
		LimitedGoodPanel* pPanel = dynamic_cast<LimitedGoodPanel*>(LayerManager::getSingleton().getLayerType<LimitedGoodPanel>());
		visibleLayer.push_back(pPanel);
	}

	if (LayerManager::getSingleton().hasLayerType<SimplePopupPanel>()) {
		SimplePopupPanel* pPanel = dynamic_cast<SimplePopupPanel*>(LayerManager::getSingleton().getLayerType<SimplePopupPanel>());
		visibleLayer.push_back(pPanel);
	}

	//출석창
	W_AttendSevenInfo* sevenInfo = GameDataManager::getSingleton().getAttendSevenInfo();
	if (sevenInfo && sevenInfo->has_attendday()) {
		Panel* pPanel = PanelHelper::pushAttendPopupPanel();
		sevenInfo->clear_attendday();
		visibleLayer.push_back(pPanel);
	}

	int64 _money = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
	int64 _bankMonety = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoneyBank;
	CCLOG("gamemoney = %d", _money);
	if (_money < GOLD_REFILL_POPUP_OCCUR_MONEY &&  _bankMonety < GOLD_REFILL_POPUP_OCCUR_MONEY) {
		Panel* pPanel = PanelHelper::pushGoldRefilPopupPanel();
		visibleLayer.push_back(pPanel);
	}

	//현재 activate 된게 없고
	vector <W_LimitShopData_eLimitType> limteds;
	if (!GameDataManager::getSingleton().isActivateLimitedTime(W_LimitShopData_eLimitType::W_LimitShopData_eLimitType_l_jackpot)) {
		if (GameDataManager::getSingleton().isActivateLimitedBuffer(W_LimitShopData_eLimitType_l_jackpot)) {
			//창을 띄운다.
			limteds.push_back(W_LimitShopData_eLimitType_l_jackpot);
			Panel* pPanel = PanelHelper::pushJackpotPanel();
			visibleLayer.push_back(pPanel);
		}
	}

	//세트A
	if (!GameDataManager::getSingleton().isActivateLimitedTime(W_LimitShopData_eLimitType::W_LimitShopData_eLimitType_l_made)) {
		if (GameDataManager::getSingleton().isActivateLimitedBuffer(W_LimitShopData_eLimitType_l_made)) {
			//창을 띄운다.
			limteds.push_back(W_LimitShopData_eLimitType_l_made);
			Panel* pPanel = PanelHelper::pushMadePanel();
			visibleLayer.push_back(pPanel);
		}
	}

	////세트B
	//if (!GameDataManager::getSingleton().isActivateLimitedTime(W_LimitShopData_eLimitType::W_LimitShopData_eLimitType_l_allin)) {
	//	if (GameDataManager::getSingleton().isActivateLimitedBuffer(W_LimitShopData_eLimitType_l_allin)) {
	//		//창을 띄운다.
	//		limteds.push_back(W_LimitShopData_eLimitType_l_allin);
	//		Panel* pPanel = PanelHelper::pushMadePanelB();
	//		visibleLayer.push_back(pPanel);
	//	}
	//}

	if (limteds.size() > 0) {
		WebService::getSingleton().sendLimitedReq(limteds);
	}

	GameDataManager::getSingleton().initLimitedBuffer();

	W_TourOfInfo* tourofInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo;

	if (tourofInfo->has_noticeinfo() && tourofInfo->noticeinfo().ByteSize() != 0) {
		
			W_TourNoticeInfo _noti = tourofInfo->noticeinfo();

			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

			if (_pScene->m_LobbyUIPanel == nullptr)
				return;

			//TODO : SHOW NOTI WINDOW 
			LobbyRewardPanel* pPanel = new LobbyRewardPanel(REWARD_TOURNAMENT);
			pPanel->init();
			pPanel->SetType(REWARD_TOURNAMENT);
			LayerManager::getSingletonPtr()->pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
			if (pPanel)
			{
				//TODO : Set RewardPanel

				int64 _gold = 0;
				int _fame = 0;

				int _size = _noti.rewardinfo().rewardset_size();
				for (int _i = 0; _i < _size; _i++)
				{
					W_RewardInfo_RewardSet _rewardset = _noti.rewardinfo().rewardset(_i);
					switch (_rewardset.type())
					{
					case CASH:
						break;
					case GAMEMONEY:
						_gold = _rewardset.amount();
						break;
					case CHIP:
						break;
					case REPUTE:
						_fame = _rewardset.amount();
						break;
					case CHARACTER:
						break;
					case TOUR_TICKET:
						break;
					}
				}

				pPanel->SetTitleText(_noti.title(), GameMode::MODE_NORMAL_TOURNAMENT);
				pPanel->SetMyRank(_noti.rank(), _noti.maxcnt());
				pPanel->SetRewardGold(_gold);
				pPanel->SetRewardFame(_fame);
				pPanel->SetDesc(_noti.desc());
			}

			tourofInfo->mutable_noticeinfo()->Clear();
		
	}

	//만약 시즌이 끝났다면 
	if (tourofInfo->has_resultinfo() && tourofInfo->resultinfo().ByteSize() != 0) {
		Panel* pPanel = PanelHelper::pushSeasonResultPanel();
		visibleLayer.push_back(pPanel);
		tourofInfo->mutable_resultinfo()->Clear();
	}

	if (tourofInfo->has_weeklyrewardinfo() && tourofInfo->weeklyrewardinfo().ByteSize() != 0) {
		Panel* pPanel = PanelHelper::pushWeeklyResultPanel();
		visibleLayer.push_back(pPanel);
		tourofInfo->mutable_weeklyrewardinfo()->Clear();
	}

#ifdef USE_TUTORIAL
	if (mNotiType != NotiData_eNotiType_NoType) {
		Panel* pPanel = PanelHelper::pushNotiFocusPanel(mNotiType);
		visibleLayer.push_back(pPanel);
	}
#endif // USE_TUTORIAL

	//시즌 등급 업 정보		
	if (tourofInfo->has_ratingupinfo() && tourofInfo->ratingupinfo().ByteSize() != 0) {
		Panel* pPanel = PanelHelper::pushRatingUpPanel();
		tourofInfo->mutable_ratingupinfo()->Clear();
	}

	for (int i = 0; i < visibleLayer.size(); i++)
	{
		if (i == visibleLayer.size() - 1) {
			visibleLayer[i]->setVisible(true);
			SimplePopupPanel* pPanel = dynamic_cast<SimplePopupPanel*>(visibleLayer[i]);
			if (pPanel) {
				pPanel->setLayerActivate(true);
			}
		}
		else {
			visibleLayer[i]->setVisible(false);
			SimplePopupPanel* pPanel = dynamic_cast<SimplePopupPanel*>(visibleLayer[i]);
			if (pPanel) {
				pPanel->setLayerActivate(false);
			}
		}
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE) {
		IapManager::getSingleton().checkAsyncInventory();
	}
#endif

}

void LobbyScene::onPreloadDynamicSetup()
{
	addPreloadDynamicResource("ui/main_screen_back_8888.png");

	vector<string> skels;
	skels.push_back("ui/main_screen_8888");
	skels.push_back("ui/main_menu_button_8888");
	skels.push_back("ui/back_image_8888");
	skels.push_back("ui/lobby_back_8888");
	skels.push_back("ui/lobby_button_8888");
	skels.push_back("ui/lobby_effect_8888");
	skels.push_back("ui/limited_goods_8888");
	skels.push_back("ui/main_menu_image_8888");
	skels.push_back("ui/main_screen_back_8888");	
	skels.push_back("ui/main_screen_8888");
	
	//상점 관련 이름
	skels.push_back("ui/shop_image_8888");
	skels.push_back("ui/uipanel_8888");
	addPreloadDynamicResource("ui/character_alexanderv.png");
	addPreloadDynamicResource("ui/character_blackrose.png");
	addPreloadDynamicResource("ui/character_blackrosev.png");
	addPreloadDynamicResource("ui/character_boxer.png");
	addPreloadDynamicResource("ui/character_christina.png");
	addPreloadDynamicResource("ui/character_christinav.png");
	addPreloadDynamicResource("ui/character_jennifer.png");
	addPreloadDynamicResource("ui/character_jenniferv.png");
	addPreloadDynamicResource("ui/character_martin.png");
	addPreloadDynamicResource("ui/character_martinv.png");
	addPreloadDynamicResource("ui/character_santiago.png");
	addPreloadDynamicResource("ui/character_santiagov.png");

	for (const auto& skel : skels)
	{
		string file = "";
		ResourceList list;
		file = skel + ".json";
		if (isFileExist(file)) {
			addPreloadDynamicResource(file);
		}
		file = skel + ".atlas";
		if (isFileExist(file))
			nxSkelAtlasGetTextureList(file, list);
		for (const auto& tex : list)
		{
			addPreloadDynamicResource(tex);
		}
	}

}

void LobbyScene::addNotidata(W_NotiData notidata)
{
	mNotidatas.push_back(notidata);
}

void LobbyScene::sendW_PayReq(string tID, string txId, string receipt)
{
	W_PayReq req;
	req.set_tid(tID);
	req.set_txid(txId);
	req.set_receipt(receipt);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE) {
		req.set_order_id(txId);
	}
#endif
	HttpMessage msg(req, HttpResponseHandler(LobbyScene::recvW_PayRes), this);
	HttpManager::getSingleton().send(msg);
}

void LobbyScene::recvW_PayRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_PayRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());
	if (res.success()) {
		CCLog("recvW_PayRes sucess");
	}
	else {
		CCLog("recvW_PayRes fail");
		//실패시 아무것도 보이지 않는다.

	}	
	//똑같은 걸 두번 보낼수도 있어서...
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE && !mGoogleTid.empty()) {
		IapManager::getSingleton().consumeProduceId(mGoogleTid);
		mGoogleTid = "";
	}

	if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE) {
		CCLog("W_PayRes checkAsyncInventory");
		IapManager::getSingleton().checkAsyncInventory();
	}
#endif

	if (res.has_playerinfo()) {
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
		GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_PLAYER_INFO_RES);
	}

}

void LobbyScene::sendW_Restore()
{
	CCLog("000000000000000000000");
	W_RestorePayReq req;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE) {
	}

#endif
	HttpMessage msg(req, HttpResponseHandler(LobbyScene::recvW_Restore), this);
	HttpManager::getSingleton().send(msg);
}



void LobbyScene::recvW_Restore(HttpMessage* msg)
{

	W_RestorePayRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success()) {
		CCLog("recvW_Restore sucess");
	}

	else {
		CCLog("recvW_Restore fail");
	}

	CCLog("restorelist_size = %d", res.restorelist_size());
	CCLog("I GOT IT BLABLA ");
	for (int i = 0; i < res.restorelist_size(); i++)
	{
		CCLog("success is is ??? = %s", res.errorcode().c_str());
		CCLog("%s %s", res.restorelist(i).tid().c_str(), res.restorelist(i).pid().c_str());
		//GameDataManager::getSingletonPtr()->m_pPlayerData->GetUID()
		CCLog("ddddasdasds = %s", StringConverter::toString(GameDataManager::getSingletonPtr()->m_pPlayerData->GetUID()).c_str());
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//IapManager::getSingletonPtr()->checkUnpaid(res.restorelist(i).tid(), res.restorelist(i).pid(), getUUID());
		IapManager::getSingletonPtr()->checkUnpaid(res.restorelist(i).tid(), res.restorelist(i).pid(), StringConverter::toString(GameDataManager::getSingletonPtr()->m_pPlayerData->GetUID()).c_str());
#endif
	}


}