#include "pch.h"
#include "GameDataManager.h"
#include "PokerCardWidget.h"
#include "TypeDefine.pb.h"
#include "socket/TCPService.h"
#include "EnterRoomSuccess.pb.h"
#include "GameRoomInfo.h"
#include "RefApp.h"
#include "PlayerOutRes.pb.h"
#include "PlayerPoInfo.pb.h"
#include "BettingRes.pb.h"
#include "W_InvenModelData.pb.h"
#include "PokerPlayerInfoPanel.h"

#include "HeroUtil.h"
#include "RefDefine.h"
#include "NxUtil.h"
#include "SceneUtil.h"
#include "GameStringDepot.h"
#include "FightScene.h"
#include "md5.h"
#include "base64util.h"
#include "LobbyScene.h"
#include "MiniGamesScene.h"
#include "W_RankInfo.pb.h"
#include "LobbyUIPanel.h"
#include "PokerChipWidget.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/AndroidUtilManager.h"
#endif
#include "BankPopupPanel.h"
#include "AccountPopupPanel.h"

#include "PokerTopPanel.h"
#include "CmdList.h"
#include "SocialManager.h"
#include "CurlMgr.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#endif

#include "LobbyReplayPanel.h"
#include "PanelHelper.h"
#include "LobbyFriendPanel.h"
#include "LobbyMissionPanel.h"
#include "GoldRefillPopupPanel.h"
#include "GameService.h"
#include "NotiDataManager.h"
#include "ModelTempTabel.h"

#include <boost/lexical_cast.hpp>
#include <Component/PokerResourceHelper.h>
static int ONE_HOUR = 60 * 60;
static int PLAY_GAME = 60 * 60 * 2;

#define GAMBLE_HELP_URL				"poker_help/help.jsp"
#define ASK_URL					"poker_web/userInquiry/userInquiry.jsp"
#define GAMBLE_PRIVATE_POLICY			"private_info_policy.htm"
#define GAMBLE_MOBLIE_USAGE		"usage_terms.htm"
#define GAMBLE_TERM				"terms_menu.htm"
#define GAMBLE_NOTICE			"poker_web/term/term.jsp?state=5" //공지
#define SILVER_MEMBERSHIP_URL	"poker_help/help.jsp?go=monthly_membership/Membership"
#define GOLD_MEMBERSHIP_URL		"poker_help/help.jsp?go=monthly_membership/Membership"
#define GAMBLE_WEB_ADULT_URL	"poker_web/adultcheck/adultipincheck.jsp"
#define WEB_TOURNAMENT_URL		"poker_help/help.jsp?go=tournament_rule/Tour"
#define WEB_REFUND_URL			"poker_help/help.jsp?go=refund_terms/Refund"
#define CAMPAIGN_URL			"campaign.htm"
#define WEB_TERMS				"terms_menu.htm"

template<> GameDataManager* Singleton<GameDataManager>::msSingleton = 0;

GameDataManager::GameDataManager()
{
	setPassward("");
	mFightSceneChange_PlayerOut = false;
	mTicketStepIndex = -1;
	m_WebViewPanel = nullptr;
	mUserInfo = nullptr;
	createImageFolder();

	m_bEditTextField = false;

	m_onFocusTextFeild = nullptr;

	m_hasTourGameInfo = false;
	m_hasTourResultInfo = false;
	m_hasSurvivalGameInfo = false;

	m_bTournamentEnd = false;
	m_bGamePlayLater = false;

	mGameData = nullptr;
	m_GameRoomInfo = nullptr;
	m_pRecordInfo = nullptr;
	m_pPlayerData = new PlayerData();
	m_SlotMachineRewardInfo = nullptr;
	m_pMyRankInfo = nullptr;
	m_ReplayUserName = "";
	m_TourOfInfo = nullptr;
	m_SurvivalOfInfo = nullptr;
	m_FacebookUserId = "";
	m_GameSceneLoadStatus = GameSceneLoadeStatus::GAME_SCENE_NOT_LOAD;
	LastSendTimeUpdateSurvival = 0;
	SurvivalButtonPressed = false;
	m_Hash = "";
	m_PlayingTime = 0;
	m_ReplaySeqID = -1;
	m_ConnRoomId = -1;
	Survival_UserStatus = W_DeathMatchInfo::eUserStatus::W_DeathMatchInfo_eUserStatus_eNot;
	m_curPage = 1;

	mPutOutType = PUTOUT_NO;

	//m_bSynopsis = CCUserDefault::sharedUserDefault()->getBoolForKey(gSynopsisKey, false);
	//m_bTutorial = CCUserDefault::sharedUserDefault()->getBoolForKey(gTutorialKey, false);

	m_pOptionValue = new OptionDefineValue();
	m_pOptionValue->m_music = CCUserDefault::sharedUserDefault()->getBoolForKey(gOptionKey[eOption_BGM], true);
	m_pOptionValue->m_effect = CCUserDefault::sharedUserDefault()->getBoolForKey(gOptionKey[eOption_EFX], true);
	m_pOptionValue->m_voice = CCUserDefault::sharedUserDefault()->getBoolForKey(gOptionKey[eOption_VOICE], true);
	m_pOptionValue->m_hiddenCard = CCUserDefault::sharedUserDefault()->getBoolForKey(gOptionKey[eOption_HIDDEN], true);
	m_pOptionValue->m_popupAlram = CCUserDefault::sharedUserDefault()->getBoolForKey(gOptionKey[eOption_POPUP], true);

	m_RakingTutotial = CCUserDefault::sharedUserDefault()->getBoolForKey(gRankingTutorialKey, false);
	m_ReplayTutotial = CCUserDefault::sharedUserDefault()->getBoolForKey(gReplayTutorialKey, false);

	m_Path = CCFileUtils::sharedFileUtils()->getWritablePath() + "Game.dat";
	
	m_pChannelListPanel = nullptr;
	GAID = "";
	m_WebViewPanel = nullptr;

	m_SelectedGameKind = GameKind::GAMEKIND_7POKER;

	mRecordSeasonInfo = nullptr;
	mRecordDeathMatchInfo = nullptr;
	mAttendSevenInfo = nullptr;	

//시간 관련
	mPlayTimeHour = 0;
	mPlayTime = 0.f;
	setBeforeReputeRatio(0.f);
	setDisplayTimeAni(false);
	SurvivalUpdateRate = 5;
	initLimitedBuffer();
	setTicketStackIndex(-1);
}

GameDataManager::~GameDataManager()
{
	if (mGameData)
		delete mGameData;

	if (m_pPlayerData)
	{
		NX_SAFE_DELETE(m_pPlayerData);
		m_pPlayerData = nullptr;
	}

	RemoveUserDataInfo();
	RemoveChannelList();
	RemoveReplayDataList();
	RemoveRankDataList();
	RemoveMyRankData();
	ReomveChannelRoomInfoList();
	RemoveHistoryState();
	RemoveTournamentOfInfo();
	RemoveSurvivalOfInfo();

	delete m_pOptionValue;
}
bool GameDataManager::canUpdateSurvival()
{
	bool result = true;
	bool result2 = false;

	result &= m_LobbyUiState != LOBBY_UI_RANKING;
	result &= m_LobbyUiState != LOBBY_UI_RANKER_GAME_POPUP;
	result &= m_LobbyUiState != LOBBY_UI_RANKING_PROCESS;

	//result &= m_LobbyUiState != LOBBY_UI_CHANNELLIST;
	//result &= m_LobbyUiState != LOBBY_UI_CHANNELROOM;

	result &= m_LobbyUiState != LOBBY_UI_SURVIVAL;
	result &= m_LobbyUiState != LOBBY_UI_SURVIVAL_SELECT; //현재 플레이어가 있는 곳이 서바이벌, 랭킹UI가 아니면 true

	//result &= m_LobbyUiState != LOBBY_UI_TOURNAMENT;
	//result &= m_LobbyUiState != LOBBY_UI_TOURNAMENT_SELECT;

	//result &= m_LobbyUiState != LOBBY_UI_BANK;
	//result &= m_LobbyUiState != LOBBY_UI_MYHOME;

	
	auto Nowtime = GameDataManager::getSingletonPtr()->GetNowTime();
	struct tm* Nowtime_tm;
	Nowtime_tm = localtime(&Nowtime);

	if (Nowtime_tm == nullptr)
		result2 = false;

	
	if (((Nowtime - LastSendTimeUpdateSurvival) > 600) &&//패킷을 보낸지 10분이 지났고
		(Nowtime_tm->tm_min % 10 == 0) &&	//현재 시간이 10분단위이고
		(GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_UID != 0)) { //로그인을 한 상태

		LastSendTimeUpdateSurvival = Nowtime;
		result2 = true;
	}
	else
		return result2 = false;

	return result && result2;
}
void GameDataManager::SaveRankingTutorialComplate()
{
	m_RakingTutotial = true;
	CCUserDefault* _pUserDefault = CCUserDefault::sharedUserDefault();

	_pUserDefault->setBoolForKey(gRankingTutorialKey, m_RakingTutotial);
	_pUserDefault->flush();
}
void GameDataManager::SaveReplayTutorialComplate()
{
	m_ReplayTutotial = true;
	CCUserDefault* _pUserDefault = CCUserDefault::sharedUserDefault();

	_pUserDefault->setBoolForKey(gReplayTutorialKey, m_ReplayTutotial);
	_pUserDefault->flush();
}

PlayerData* GameDataManager::GetPlayerDataPtr()
{
	return m_pPlayerData;
}

void GameDataManager::SetPlayerData(PlayerData* _ptr)
{
	m_pPlayerData = _ptr;
}

GameRoomInfo* GameDataManager::GetGameRoomInfoPtr()
{
	return m_GameRoomInfo;
}

void GameDataManager::SetGameRoomInfo(GameRoomInfo* _ptr)
{
	if (SceneManager::getSingletonPtr()->hasScene(SceneUtil::SceneFight))
	{
		FightScene* _pScene = dynamic_cast<FightScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		_pScene->SetGameRoomInfo(_ptr);
	}

	m_GameRoomInfo = _ptr;
}

bool GameDataManager::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	switch (type)
	{
		case S2C_ENTER_ROOM_SUCCESS_IDX:
		{
			//할 필요없다.
			//if (GetChannelPanel() != nullptr)
			//	GetChannelPanel()->onClicked("sbtn_option_button");
			return MakeRoom((char*)_msg, parm1);
		}
		case S2C_PLAYER_OUT_IDX:
		case S2C_PLAYER_OUT_DISCONNECT_IDX :
		{
			PlayerOutRes res;
			res.ParseFromArray((char*)_msg, parm1);
			PlayerPoInfo poInfo = res.playerpoinfo();

			int _myPo = m_GameRoomInfo->GetMyPo();
			int _kind = GetGameRoomInfoPtr()->GetUserDataPtr(_myPo)->m_PlayerOutResrvKind;
			if (type == S2C_PLAYER_OUT_DISCONNECT_IDX)
			{
				RoomUserData* _pUser = GetGameRoomInfoPtr()->GetUserDataPtr(poInfo.po());
				if (_pUser)
				{
					_pUser->m_pPlayerData->m_UserKind = UserKind::DUMMY_TNMT;
				}
				
				if (res.has_disconnectcnt() == true)
				{
					PlayerOutResourceProcess(poInfo.po(), res.bossidx(), true, res.disconnectcnt());
				}
				else
				{
					PlayerOutResourceProcess(poInfo.po(), res.bossidx(), true);
				}
			}
			else
			{
				if (GetGameRoomInfoPtr()->GetGameMode() != GameMode::MODE_NORMAL)
				{
					PokerTopPanel* _pTopPanel = GetGameRoomInfoPtr()->GetTopPanel();
					if (_pTopPanel)
					{
						_pTopPanel->SetResultPlayerRank(poInfo.po(), false);
					}
				}
				PlayerOutResourceProcess(poInfo.po(), res.bossidx(), false);
			}
			
			if (_myPo == poInfo.po())
			{
				setPlayerOut(false);
				bool sceneChanging = SceneManager::getSingleton().isChanging();
				if (sceneChanging) {
					//지금 changescene 하면 안된다.
					setPlayerOut(true);
				}
				else {
					//내가 올인 됐을 경우 lobby 로 이동
					GameDataManager::getSingletonPtr()->ClearUiState();
					SoundManager::getSingletonPtr()->stopEffects();
					if (m_GameMode == MODE_NORMAL) {
						CSJson::Value params;
						params["LOBBY_UI_CHANNELLIST"] = true;
						SceneUtil::changeScene(SceneUtil::SceneLobby, params);
					}
					else if (m_GameMode == MODE_NORMAL_TOURNAMENT) {
						CSJson::Value params;
						params["LOBBY_UI_TOURNAMENT_SELECT"] = true;
						SceneUtil::changeScene(SceneUtil::SceneLobby, params);
					}
					else if (m_GameMode == MODE_SURVIVAL_TOURNAMENT) {
						CSJson::Value params;
						params["LOBBY_UI_SURVIVAL_SELECT"] = true;
						SceneUtil::changeScene(SceneUtil::SceneLobby, params);
					}
				}
			}
			break;
		}
		case S2C_PUT_OUT_IDX:
		{
			PlayerPoInfo res;
			res.ParseFromArray((char*)_msg, parm1);

			int _myPo = m_GameRoomInfo->GetMyPo();
			PlayerOutResourceProcess(res.po(), m_GameRoomInfo->GetBossPo());

			setPlayerOut(false);
			if (_myPo == res.po())
			{
				bool sceneChanging = SceneManager::getSingleton().isChanging();
				if (sceneChanging) {
					//지금 changescene 하면 안된다.
					setPlayerOut(true);
				}
				else {

					SoundManager::getSingletonPtr()->stopEffects();
					if (m_GameMode == MODE_NORMAL) {
						CSJson::Value params;
						params["LOBBY_UI_CHANNELLIST"] = true;
						SceneUtil::changeScene(SceneUtil::SceneLobby, params);
					}
					else if (m_GameMode == MODE_NORMAL_TOURNAMENT) {
						CSJson::Value params;
						params["LOBBY_UI_TOURNAMENT_SELECT"] = true;
						SceneUtil::changeScene(SceneUtil::SceneLobby, params);
					}
					else if (m_GameMode == MODE_SURVIVAL_TOURNAMENT) {
						CSJson::Value params;
						params["LOBBY_UI_SURVIVAL_SELECT"] = true;
						SceneUtil::changeScene(SceneUtil::SceneLobby, params);
					}
				}
			}			
			break;
		}
	}

	return true;
}

void GameDataManager::PlayerOutResourceProcess(int po, int bossIdx, bool isDisconnect, int _disconnectCnt)
{
	PokerPlayerInfoPanel* _pPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("PlayerInfo"));
	if (_pPanel != nullptr)
	{
		//_pPanel->ShowPlayerPanel(poInfo.po(), false);
		if (m_GameRoomInfo == NULL)
			return;

		if (m_GameRoomInfo->GetMyPo() != po)
		{
			//if (m_GameRoomInfo->GetGameMode() == GameMode::MODE_NORMAL || m_GameRoomInfo->m_PlayStatus == PLAY_NO)
			if (!isDisconnect)
			{
				if (GetGameRoomInfoPtr()->GetGameMode() != GameMode::MODE_NORMAL)
				{
					PokerPlayerInfoCommonPanel* _pUserPanel = GetGameRoomInfoPtr()->GetPlayerCommonPanel(po);
					if (_pUserPanel)
					{
						_pUserPanel->TurnOffPlayerDisconnect();
					}
				}

				_pPanel->RemoveCharacter(po);
				_pPanel->SetUserInfoPanelInit(po);
				m_GameRoomInfo->DeleteUser(po, bossIdx);
			}
			else
			{
				PokerPlayerInfoCommonPanel* _pUserPanel = GetGameRoomInfoPtr()->GetPlayerCommonPanel(po);
				if (_pUserPanel)
				{
					_pUserPanel->TurnOnPlayerDisconnect(_disconnectCnt);
				}

				string msgText = "[" + GetGameRoomInfoPtr()->GetUserDataPtr(po)->m_pPlayerData->m_NickName + "]" + GameStringDepot::getSingletonPtr()->getString("TXT_USER_DISCONNECT");
				SimplePopupPanel * _toastpanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ToastNotice, msgText);
					
				if (_toastpanel)
					LayerManager::getSingleton().pushDynamicLayer(_toastpanel, DYNAMIC_PUSH_LAYER);
			}
		}
		else
		{
			if (GetGameRoomInfoPtr()->isBigAnimation())
			{
				PlayGameSound(EFX_GAME_TENSION, false);
			}
			GetGameRoomInfoPtr()->RemoveDealer();
			_pPanel->RemoveAllCharacter();
			
			DestroyRoom();
		}
	}
}
void GameDataManager::RemoveGameRoomInfo()
{
	if (m_GameRoomInfo)
	{
		NX_SAFE_DELETE(m_GameRoomInfo);
		m_GameRoomInfo = nullptr;
	}
}

bool GameDataManager::MakeRoom(char * data, int size)
{
	CCLOG("Make Room = %s GetGameSceneLoaded() = %d", data, GetGameSceneLoaded());
	//기덕 수정
// 	if (GetChannelPanel() != nullptr)
// 	{
// 		GetChannelPanel()->onClicked("sbtn_option_button");
// 		ReleaseChannelPanel();
// 	}

	CCLOG("GetGameSceneLoaded() = %d", GetGameSceneLoaded());

	switch (GetGameSceneLoaded())
	{
		case GameSceneLoadeStatus::GAME_SCENE_NOT_LOAD :
			if (m_isDirectTournamentLink == true)
			{
				m_isDirectTournamentLink = false;

				if (GetUiState() == LOBBY_UI_MAIN)
				{
					SetUiState(LOBBY_UI_TOURNAMENT);
					SetUiState(LOBBY_UI_TOURNAMENT_SELECT);
				}
			}

			if (m_isDirectSurvivalLink == true)
			{
				m_isDirectSurvivalLink = false;
				if (GetUiState() == LOBBY_UI_MAIN)
				{
					SetUiState(LOBBY_UI_SURVIVAL);
					SetUiState(LOBBY_UI_SURVIVAL_SELECT);
				}
			}

			SetGameSceneLoaded(GameSceneLoadeStatus::GAME_SCENE_LOADING);
			m_pChannelListPanel = nullptr;
			SceneUtil::changeScene(SceneUtil::SceneFight);
			PlayGameSound(EFX_GAME_ENTERGAME);
			//cout << U8("LOADING START!!!!") << endl;
			return false;
		case GameSceneLoadeStatus::GAME_SCENE_LOADED:
		{
			EnterRoomSuccess res;
			res.ParseFromArray(data, size);

			RemoveGameRoomInfo();
			m_GameRoomInfo = new GameRoomInfo();

			m_GameRoomInfo->SetData(&res);
			//CCLOG("Making room has Succeeded!!!");
			//cout << "Making room has Succeeded!!!" << "ROOM NUMBER[" << m_GameRoomInfo->GetRoomIdx() << "]" << endl;

			FightScene * scene = dynamic_cast<FightScene*>(SceneManager::getSingletonPtr()->getScene(SceneUtil::SceneFight));
			if (scene != nullptr)
				scene->FirstGameStateSetting();

			m_GameRoomInfo->GetUserDataPtr(m_GameRoomInfo->GetMyPo())->SetPlayerStatus(PlayerStatus::PLAYER_PREPARE);

			TCPService::getSingletonPtr()->SendNormalPacket(C2S_PREPARE_END_IDX);

			ActionPointer::createGameInfoShow(m_GameRoomInfo, 1.f);

			//int _kind = EFX_DEALER_INCOME2 + (rand() % 2);
			//GetGameRoomInfoPtr()->DealerSound((DealerEfxKind)_kind);

			int _kind = CharacterEfxKind::EFX_ENTER1 + (rand() % 2);
			m_GameRoomInfo->GetUserDataPtr(m_GameRoomInfo->GetMyPo())->PlayCharacterSound((CharacterEfxKind)_kind);

			m_GameRoomInfo->Action_EnterRoomCharacter(m_GameRoomInfo->GetMyPo());

			m_GameRoomInfo->refreshRoomNo();

			//cout << U8("SCENE LOADING END!!!!") << endl;

			return true;
		}
	}

	//cout << U8("SCENE LOADING!!!!") << endl;
	
	return false;
}

void GameDataManager::DestroyRoom()
{
	SetGameSceneLoaded(GameSceneLoadeStatus::GAME_SCENE_NOT_LOAD);
	if (m_GameRoomInfo != nullptr)
	{
		NX_SAFE_DELETE(m_GameRoomInfo);
	}
	SetGameRoomInfo(nullptr);
}

bool GameDataManager::IsFriendsChannel()
{
	if (m_Grade == 18 || m_Grade == 19 || m_Grade == 38 || m_Grade == 39)
		return true;

	return false;
}

string GameDataManager::GetJokboStr(int _kind)
{
	switch (_kind)
	{
	case HIGH_ROYAL_STRAIGHT_FLUSH:
		return GameStringDepot::getSingleton().getString("TXT_ROYAL_SHORT");//U8("로티플");
	case HIGH_STRAIGHT_FLUSH:
		return GameStringDepot::getSingleton().getString("TXT_STIFUL_SHORT");//U8("스티플");
	case HIGH_FOUR_CARD:
		return GameStringDepot::getSingleton().getString("TXT_FOURCARD");//U8("포카드");
	case HIGH_FULL_HOUSE:
		return GameStringDepot::getSingleton().getString("TXT_FULLHOUSE");//U8("풀하우스");
	case HIGH_FLUSH:
		return GameStringDepot::getSingleton().getString("TXT_FLUSH");//U8("플러쉬");
	case HIGH_MOUNTAIN:
		return GameStringDepot::getSingleton().getString("TXT_MAUNTAIN");//U8("마운틴");
	case HIGH_BACK_STRAIGHT:
		return GameStringDepot::getSingleton().getString("TXT_BACKSTRAIGHT");//U8("백스트레이트");
	case HIGH_STRAIGHT:
		return GameStringDepot::getSingleton().getString("TXT_STRAIGHT");// U8("스트레이트");
	case HIGH_TRIPLE:
		return GameStringDepot::getSingleton().getString("TXT_THREEFUL");//U8("트리플");
	case HIGH_TWO_PAIR:
	case LOW_TWO_PAIR:
		return GameStringDepot::getSingleton().getString("TXT_TWOFAIR");//U8("투페어");
	case HIGH_ONE_PAIR:
	case LOW_ONE_PAIR:
		return GameStringDepot::getSingleton().getString("TXT_ONEFAIR");//U8("원페어");
	case HIGH_TOP:
		return GameStringDepot::getSingleton().getString("TXT_UNDERTOP");//U8("탑이하");
	case LOW_K_TOP:
		return GameStringDepot::getSingleton().getString("TXT_KTOP");//U8("K탑");
	case LOW_Q_TOP:
		return GameStringDepot::getSingleton().getString("TXT_QTOP");//U8("Q탑");
	case LOW_J_TOP:
		return GameStringDepot::getSingleton().getString("TXT_JTOP");//U8("J탑");
	case LOW_TEN_TOP:
		return GameStringDepot::getSingleton().getString("TXT_10TOP");//U8("10탑");
	case LOW_NINE_TOP:
		return GameStringDepot::getSingleton().getString("TXT_9TOP");//U8("9탑");
	case LOW_EIGHT_TOP:
		return GameStringDepot::getSingleton().getString("TXT_8TOP");//U8("8탑");
	case LOW_SEVEN_TOP:
		return GameStringDepot::getSingleton().getString("TXT_7TOP");//U8("7탑");
	case LOW_SIX_TOP:
		return GameStringDepot::getSingleton().getString("TXT_6TOP");//U8("6탑");
	case HIGH_NO:
		return "";
	default:
		return GameStringDepot::getSingleton().getString("TXT_LESSTOP");//U8("탑 미만");
	}

	return "";
}

string GameDataManager::GetFullJokboStr(int _kind)
{
	CCLOG("GetFullJokboStr_________________________________________________________________________________________________");
	switch (_kind)
	{
	case HIGH_ROYAL_STRAIGHT_FLUSH:
		return GameStringDepot::getSingleton().getString("TXT_ROYAL_STRIGHT");//U8("로얄스트레이트플러쉬");
	case HIGH_STRAIGHT_FLUSH:
		return GameStringDepot::getSingleton().getString("TXT_STRIGHTFLUSH");//U8("스트레이트플러쉬");
	case HIGH_FOUR_CARD:
		return GameStringDepot::getSingleton().getString("TXT_FOURCARD");//U8("포카드");
	case HIGH_FULL_HOUSE:
		return GameStringDepot::getSingleton().getString("TXT_FULLHOUSE");//U8("풀하우스");
	case HIGH_FLUSH:
		return GameStringDepot::getSingleton().getString("TXT_FLUSH");//U8("플러쉬");
	case HIGH_MOUNTAIN:
		return GameStringDepot::getSingleton().getString("TXT_MAUNTAIN");//U8("마운틴");
	case HIGH_BACK_STRAIGHT:
		return GameStringDepot::getSingleton().getString("TXT_BACKSTRAIGHT");//U8("백스트레이트");
	case HIGH_STRAIGHT:
		return GameStringDepot::getSingleton().getString("TXT_STRAIGHT");// U8("스트레이트");
	case HIGH_TRIPLE:
		return GameStringDepot::getSingleton().getString("TXT_THREEFUL");//U8("트리플");
	case HIGH_TWO_PAIR:
	case LOW_TWO_PAIR:
		return GameStringDepot::getSingleton().getString("TXT_TWOFAIR");//U8("투페어");
	case HIGH_ONE_PAIR:
	case LOW_ONE_PAIR:
		return GameStringDepot::getSingleton().getString("TXT_ONEFAIR");//U8("원페어");
	case HIGH_TOP:
		return GameStringDepot::getSingleton().getString("TXT_TOP");//U8("탑");
	case LOW_K_TOP:
		return GameStringDepot::getSingleton().getString("TXT_KTOP");//U8("K탑");
	case LOW_Q_TOP:
		return GameStringDepot::getSingleton().getString("TXT_QTOP");//U8("Q탑");
	case LOW_J_TOP:
		return GameStringDepot::getSingleton().getString("TXT_JTOP");//U8("J탑");
	case LOW_TEN_TOP:
		return GameStringDepot::getSingleton().getString("TXT_10TOP");//U8("10탑");
	case LOW_NINE_TOP:
		return GameStringDepot::getSingleton().getString("TXT_9TOP");//U8("9탑");
	case LOW_EIGHT_TOP:
		return GameStringDepot::getSingleton().getString("TXT_8TOP");//U8("8탑");
	case LOW_SEVEN_TOP:
		return GameStringDepot::getSingleton().getString("TXT_7TOP");//U8("7탑");
	case LOW_SIX_TOP:
		return GameStringDepot::getSingleton().getString("TXT_6TOP");//U8("6탑");
	case HIGH_NO:
		return "";
	default:
		return GameStringDepot::getSingleton().getString("TXT_LESSTOP");//U8("탑 미만");
	}

	return "";
}

string GameDataManager::GetBadugiJokboStr(int _kind)
{
	CCLOG("GetBadugiJokboStr_________________________________________________________________________________________________");
	switch (_kind)
	{
	case BADUKI_GOLF:
		return GameStringDepot::getSingleton().getString("TXT_BADUGI_GOLF");
		break;
	case BADUKI_SECOND:
		return GameStringDepot::getSingleton().getString("TXT_BADUGI_SECOND");
		break;
	case BADUKI_THIRD:
		return GameStringDepot::getSingleton().getString("TXT_BADUGI_THIRD");
		break;
	case BADUKI_FIVE_TOP:
		return GameStringDepot::getSingleton().getString("TXT_BADUGI_5TOP");
		break;
	case BADUKI_SIX_TOP:
		return GameStringDepot::getSingleton().getString("TXT_6TOP");
		break;
	case BADUKI_SEVEN_TOP:
		return GameStringDepot::getSingleton().getString("TXT_7TOP");
		break;
	case BADUKI_EIGHT_TOP:
		return GameStringDepot::getSingleton().getString("TXT_8TOP");
		break;
	case BADUKI_NINE_TOP:
		return GameStringDepot::getSingleton().getString("TXT_9TOP");
		break;
	case BADUKI_TEN_TOP:
		return GameStringDepot::getSingleton().getString("TXT_10TOP");
		break;
	case BADUKI_J_TOP:
		return GameStringDepot::getSingleton().getString("TXT_JTOP");
		break;
	case BADUKI_Q_TOP:
		return GameStringDepot::getSingleton().getString("TXT_QTOP");
		break;
	case BADUKI_K_TOP:
		return GameStringDepot::getSingleton().getString("TXT_KTOP");
		break;
	case BADUKI_BASE:
		return GameStringDepot::getSingleton().getString("TXT_BADUGI_BASE");
		break;
	case BADUKI_TWO_BASE:
		return GameStringDepot::getSingleton().getString("TXT_BADUGI_TWOBASE");
		break;
	case BADUKI_TWO_BASE_DOWN:
		return GameStringDepot::getSingleton().getString("TXT_BADUGI_TWOBASE_DOWN");
		break;
	default:
		return GameStringDepot::getSingleton().getString("TXT_BADUGI_TWOBASE_DOWN");
	}
	return "";
}

string GameDataManager::GetCardNumStr(int number)
{
	if (number == 0)
		return GameStringDepot::getSingleton().getString("TXT_A");//"A";
	else if (number == 10)
		return GameStringDepot::getSingleton().getString("TXT_J");//"J";
	else if (number == 11)
		return GameStringDepot::getSingleton().getString("TXT_Q");//"Q";
	else if (number == 12)
		return GameStringDepot::getSingleton().getString("TXT_K");//"K";
	else
		return StringConverter::toString(number + 1);
}

string GameDataManager::GetKoreanLiteral(string number, int unit)
{
	string numberData = "";
	string::iterator itPos = number.begin();
	size_t size = number.size();
	int pos = 0;
	int startNumber = 0;
	int tmpNumber;
	int curUnit = 0;

	int tmpPos; 

	while (pos < (int)size)
	{
		itPos = number.begin() + pos;
		tmpNumber = (*itPos) - 48;

		if (tmpNumber == -3)
		{
			numberData.append("-");
			pos++;
			continue;
		}
		if (tmpNumber > 0 || startNumber > 0 || number == "0")
		{
			numberData.append(StringConverter::toString(tmpNumber));
			if (tmpNumber > 0)
				startNumber = tmpNumber;
		}

		tmpPos = size - pos;
		if (tmpPos == 17)
		{
			if (startNumber > 0)
			{
				numberData.append(GameStringDepot::getSingleton().getString("TXT_10000^4"));
				curUnit++;
			}
			startNumber = 0;
		}
		else if (tmpPos == 13)
		{
			if (startNumber > 0)
			{
				numberData.append(GameStringDepot::getSingleton().getString("TXT_10000^3"));
				curUnit++;
			}
			startNumber = 0;
		}
		else if (tmpPos == 9)
		{
			if (startNumber > 0)
			{
				numberData.append(GameStringDepot::getSingleton().getString("TXT_10000^2"));
				curUnit++;
			}
			startNumber = 0;
		}
		else if (tmpPos == 5)
		{
			if (startNumber > 0)
			{
				numberData.append(GameStringDepot::getSingleton().getString("TXT_10000^1"));
				curUnit++;
			}
			startNumber = 0;
		}

		pos++;

		if (curUnit >= unit)
			break;
	}

//	mBettingAmount->setString(bettingMoney.c_str());

	return numberData;
}

//글자단위로 잘라서 보내주는 함수
string GameDataManager::GetU8SubStr(string str, int size)
{
	string data = "";
	string::iterator itPos = str.begin();
	int len = str.size();
	int pos = 0;
	//int tmpPos;
	int tmpValue;
	int count = 0;
	bool isCopy = false;

	while (pos < (int)len)
	{
		itPos = str.begin() + pos;
		tmpValue = (*itPos);
		if (tmpValue < 0)
			tmpValue += 256;

		// asc는 그대로
		if (tmpValue < 0x80)
		{
			pos += 1;
		}
		else if (tmpValue < 0xE0)
		{
			pos += 2;
		}
		// 그외는 3바이트
		else if (tmpValue < 0xF0)
		{
			pos += 3;
		}
		else
		{
			pos += 4;
		}
		count++;

		if (count >= size)
		{
			data = str.substr(0, pos);
			isCopy = true;
			break;
		}
	}

	if (!isCopy)
		data = str;

	return data;
}

int GameDataManager::CheckNickname(string str, int size)
{
	string data = "";
	string::iterator itPos = str.begin();
	int len = str.size();
	int pos = 0;
	//int tmpPos;
	int tmpValue;
	int count = 0;

	bool isAllSpace = true;

	while (pos < (int)len)
	{
		itPos = str.begin() + pos;
		tmpValue = (*itPos);
		if (tmpValue < 0)
			tmpValue += 256;

		if (tmpValue != 0x20)
			isAllSpace = false;
		
		// asc는 그대로
		if (tmpValue < 0x80)
		{
			pos += 1;
			if (tmpValue == 0x60 || tmpValue == 0x26 || tmpValue == 0x24)	// @, &, $
				return NICKNAME_CHECK_ERROR::NCE_SPECIAL_LETTER_ERROR;
		}
		else if (tmpValue < 0xE0)
		{
			pos += 2;
		}
		// 그외는 3바이트
		else if (tmpValue < 0xF0)
		{
			pos += 3;
		}
		else
		{
			pos += 4;
		}
		count++;
	}

	if (count > size || len == 0)
		return NICKNAME_CHECK_ERROR::NCE_LENGTH_ERROR;
	else if (isAllSpace)
		return NICKNAME_CHECK_ERROR::NCE_SPACE_ERROR;

	return NICKNAME_CHECK_ERROR::NCE_SUCCESS;
}

int GameDataManager::CheckText(string str, int size)
{
	string data = "";
	string::iterator itPos = str.begin();
	int len = str.size();
	int pos = 0;
	//int tmpPos;
	int tmpValue;
	int count = 0;

	bool isAllSpace = true;

	while (pos < (int)len)
	{
		itPos = str.begin() + pos;
		tmpValue = (*itPos);
		if (tmpValue < 0)
			tmpValue += 256;

		if (tmpValue != 0x20)
			isAllSpace = false;

		// asc는 그대로
		if (tmpValue < 0x80)
		{
			pos += 1;
		}
		else if (tmpValue < 0xE0)
		{
			pos += 2;
		}
		// 그외는 3바이트
		else if (tmpValue < 0xF0)
		{
			pos += 3;
		}
		else
		{
			pos += 4;
		}
		count++;
	}

	if (count > size || len == 0)
		return NICKNAME_CHECK_ERROR::NCE_LENGTH_ERROR;
	else if (isAllSpace)
		return NICKNAME_CHECK_ERROR::NCE_SPACE_ERROR;

	return NICKNAME_CHECK_ERROR::NCE_SUCCESS;
}

void GameDataManager::PlayGameSound(GameEfxKind _kind, bool _play, bool _loop)
{
	if (m_pOptionValue->m_effect == false)
		return;

	string _name;
	switch (_kind)
	{
	case EFX_GAME_BBING:
		_name = "game_bbing";
		break;
	case EFX_GAME_BET:
		_name = "game_bet";
		break;
	case EFX_GAME_BIGBET:
		_name = "game_bigbet";
		break;
	case EFX_GAME_CARDDEAL:
		_name = "game_carddeal";
		break;
	case EFX_GAME_CARDDOWN:
		_name = "game_carddown";
		break;
	case EFX_GAME_CARDFLOP:
		_name = "game_cardflop";
		break;
	case EFX_GAME_CARDOPEN:
		_name = "game_cardopen";
		break;
	case EFX_GAME_CHEER:
		_name = "game_cheer";
		break;
	case EFX_GAME_CROWD:
		_name = "game_crowd";
		break;
	case EFX_GAME_EXIT:
		_name = "game_exit";
		break;
	case EFX_GAME_WIN:
		_name = "Game_win";
		break;
	case EFX_GAME_LOSE:
		_name = "game_lose";
		break;
	case EFX_GAME_TENSION:
		_name = "game_tension";
		break;
	case EFX_GAME_TIMER:
		_name = "game_timer";
		break;
	case EFX_GAME_TAKECHIP:
		_name = "game_win_takechip";
		break;
	case EFX_GAME_BTN:
		_name = "menu_btn";
		break;
	case EFX_GAME_CHECK:
		_name = "menu_check";
		break;
	case EFX_GAME_ENTERGAME:
		_name = "menu_entergame";
		break;
	case EFX_GAME_PAGE:
		_name = "menu_page";
		break;
	case EFX_GAME_POPUPOPEN:
		_name = "menu_popupopen";
		break;
	case EFX_GAME_MADE:
		_name = "game_made";
		break;
	case EFX_GAME_SLOTCOIN:
		_name = "Slot_coin";
		break;
	case EFX_GAME_SLOTLEVER:
		_name = "slot_lever";
		break;
	case EFX_GAME_SLOTSPIN:
		_name = "slot_spin";
		break;
	case EFX_GAME_SLOTSTOP:
		_name = "slot_stop";
		break;
	case EFX_GAME_SLOTJACKPOT:
		_name = "slot_jackpot";
		break;
	case EFX_GAME_SLOTWIN:
		_name = "Slot_win"; 
		break;
	case EFX_GAME_KIND_MAX:
		_name = "game_kind_max";
		break;
	default:
		return;
	}
	if(_play == true)
		SoundManager::getSingletonPtr()->playEffect(_name, _loop);
	else
		SoundManager::getSingletonPtr()->stopEffect(_name);
}

int GameDataManager::ClientToServerIndex(int _idx)
{
	return (GetGameRoomInfoPtr()->GetMyPo() + _idx) % GAME_USER_MAX;
}

int GameDataManager::ServerToClientIndex(int _idx)
{
	int _returnValue = _idx - GetGameRoomInfoPtr()->GetMyPo();
	if (_returnValue < 0)
		_returnValue += GAME_USER_MAX;

	return _returnValue;
}

std::string GameDataManager::GetChannelGradeName(int grade)
{
	int size = mGameData->channelgradedata_size();
	if (size == 0)
		return "";

	W_ChannelGradeData gradeData;
	for (int i = 0; i < size; i++)
	{
		gradeData = mGameData->channelgradedata(i);
		if (grade == gradeData.grade())
			return gradeData.name();
	}
	return "";
}

std::string GameDataManager::GetJokboFrameName(int _kind, bool _on)
{
	string _name;
	switch (_kind)
	{
	case HIGH_ROYAL_STRAIGHT_FLUSH:
		_name = "font_royal";
		break;
	case HIGH_STRAIGHT_FLUSH:
		_name = "font_straifl";
		break;
	case HIGH_FOUR_CARD:
		_name = "font_four";
		break;
	case HIGH_FULL_HOUSE:
		_name = "font_fullhouse";
		break;
	case HIGH_FLUSH:
		_name = "font_flush";
		break;
	case HIGH_MOUNTAIN:
		_name = "font_mountain";
		break;
	case HIGH_BACK_STRAIGHT:
		_name = "font_backst";
		break;
	case HIGH_STRAIGHT:
		_name = "font_straight";
		break;
	case HIGH_TRIPLE:
		_name = "font_three";
		break;
	case HIGH_TWO_PAIR:
	case LOW_TWO_PAIR:
		_name = "font_two";
		break;
	case HIGH_ONE_PAIR:
	case LOW_ONE_PAIR:
		_name = "font_one";
		break;
	case HIGH_TOP:
		_name = "font_topunder";
		break;
	case LOW_K_TOP:
		_name = "font_ktop";
		break;
	case LOW_Q_TOP:
		_name = "font_qtop";
		break;
	case LOW_J_TOP:
		_name = "font_jtop";
		break;
	case LOW_TEN_TOP:
		_name = "font_10top";
		break;
	case LOW_NINE_TOP:
		_name = "font_9top";
		break;
	case LOW_EIGHT_TOP:
		_name = "font_8top";
		break;
	case LOW_SEVEN_TOP:
		_name = "font_7top";
		break;
	case LOW_SIX_TOP:
		_name = "font_6top";
		break;
	case HIGH_NO:
		return "";
	default:
		_name = "font_topunder2";
		break;
	}

	if (_on == true)
	{
		_name += "_on";
	}
	else
	{
		_name += "_off";
	}

	return _name;
}

std::string GameDataManager::GetBadukiJokboFrameName(int _kind, bool _on)
{
	string _name;
	switch (_kind)
	{
	case BADUKI_GOLF:
		_name = "font_golf";
		break;
	case BADUKI_SECOND:
		_name = "font_second";
		break;
	case BADUKI_THIRD:
		_name = "font_third";
		break;
	case BADUKI_FIVE_TOP:
		_name = "font_5top";
		break;
	case BADUKI_SIX_TOP:
		_name = "font_6top";
		break;
	case BADUKI_SEVEN_TOP:
		_name = "font_7top";
		break;
	case BADUKI_EIGHT_TOP:
		_name = "font_8top";
		break;
	case BADUKI_NINE_TOP:
		_name = "font_9top";
		break;
	case BADUKI_TEN_TOP:
		_name = "font_10top";
		break;
	case BADUKI_J_TOP:
		_name = "font_jtop";
		break;
	case BADUKI_Q_TOP:
		_name = "font_qtop";
		break;
	case BADUKI_K_TOP:
		_name = "font_ktop";
		break;
	case BADUKI_BASE:
		_name = "font_base";
		break;
	case BADUKI_TWO_BASE:
		_name = "font_twobase";
		break;
	case BADUKI_TWO_BASE_DOWN:
		_name = "font_top";
		break;
	default:
		_name = "font_top";
		break;
	}

	if (_on == true)
	{
		_name += "_on";
	}
	else
	{
		_name += "_off";
	}

	return _name;
}

bool GameDataManager::_checkFile(const string& path)
{
	ifstream stream(path.c_str(), ios_base::in | ios_base::binary);

	if (false == stream.is_open())
		return false;

	stream.seekg(0, stream.end);
	if (0 >= stream.tellg())
		return false;

	return true;
}

void GameDataManager::_readFile(const string& path)
{
	NXASSERT(!mGameData);

	ssize_t size = 0;
	unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	mGameData = new W_GameData();
	mGameData->ParseFromArray(data, size);
	if (!mGameData->IsInitialized()) {
		NX_SAFE_DELETE(mGameData);
	}
	NX_SAFE_DELETE_ARRAY(data);
}

void GameDataManager::_writeFile(const string& path)
{
	NXASSERT(mGameData);

	int bufferSize = mGameData->ByteSize();
	char* buffer = new char[bufferSize];
	mGameData->SerializeToArray(buffer, bufferSize);

	ofstream stream;
	stream.open(path.c_str(), ios_base::out | ios_base::binary);
	if (true == stream.is_open())
	{
		stream.write(buffer, bufferSize);
		stream.flush();
		stream.close();
	}

	delete[] buffer;
}

void GameDataManager::_makeHash()
{
	if (!mGameData)
		return;

	int bufferSize = mGameData->ByteSize();
	char* buffer = new char[bufferSize];
	mGameData->SerializeToArray(buffer, bufferSize);

	md5_byte_t digest[16];
	md5_state_t state;

	md5_init(&state);
	md5_append(&state, (const md5_byte_t *)buffer, bufferSize);
	md5_finish(&state, digest);

	delete[] buffer;

	char hex_output[16 * 2 + 1];
	for (int di = 0; di < 16; ++di)
	{
		sprintf(hex_output + di * 2, "%02X", digest[di]);
	}

	m_Hash = hex_output;
}

void GameDataManager::CheckSurvivalPopup()
{
	int i = GetUiState();
	if (!m_SurvivalOfInfo)
		return;
	if (m_SurvivalOfInfo->matchinfo_size() == 0)
		return;

	if (!m_SurvivalOfInfo->matchinfo(0).isregister())
		return;

	bool Survival_Popup_Alarm = CCUserDefault::sharedUserDefault()->getBoolForKey("Survival_Popup_Alarm", false);
	if (!Survival_Popup_Alarm)
		return;

	if (Survival_Popup_Alarm) {
		bool ShouldPopup = m_IsSurvivalReservated; //예약여부
		ShouldPopup &= Survival_UserStatus == 4; //게임중인가
		ShouldPopup &= (GetUiState() == LobbyUiStatus::LOBBY_UI_MAIN); 

		if (ShouldPopup) {
			CCUserDefault::sharedUserDefault()->setBoolForKey("Survival_Popup_Alarm", false);
			string _OkMsg = "GO_GAME_SURVIVAL";
			string _title = GameStringDepot::getSingleton().getString("TXT_DIRECT_GAME_START_TITLE");
			string _content = GameStringDepot::getSingleton().getString("TXT_DIRECT_GAME_SURVIVAL_DESC");
			SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _content, _title);
			if (_popupPanel)
			{
				_popupPanel->SetOkEventMsg(_OkMsg);
				_popupPanel->setListener(WebService::getSingletonPtr());
				LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
			}
		}
	}

}

void GameDataManager::CheckSurvivalPreAlert()
{
	if (!m_SurvivalOfInfo)
		return;
	if (m_SurvivalOfInfo->matchinfo_size() == 0)
		return;

	if (!m_SurvivalOfInfo->matchinfo(0).isregister())
		return;

	bool Survival_Pre_Alarm = CCUserDefault::sharedUserDefault()->getBoolForKey("Survival_Pre_Alarm", false);
	if (!Survival_Pre_Alarm)
		return;

	if (Survival_Pre_Alarm) {
		bool ShouldPre = m_IsSurvivalReservated; //예약 여부
		ShouldPre &= (GetUiState() == LobbyUiStatus::LOBBY_UI_MAIN); //플레이어가 로비에 있는가
		ShouldPre &= Survival_GameableTime <= 1800; //게임시간이 30분 이하로 남았는가
		
		if (ShouldPre) {
			CCUserDefault::sharedUserDefault()->setBoolForKey("Survival_Pre_Alarm", false);
			string _title = GameStringDepot::getSingleton().getString("TXT_NOT_SURVIVAL_ALERT");
			string _content = NxGetFormatString(GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_PREALERT_CONTENT"), PokerResourceHelper::getPeroidMinDesc(GameDataManager::getSingletonPtr()->Survival_GameableTime) );
			
			SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _content, _title);
			if (_popupPanel)
				LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
		}
	}
}
EncryptString GameDataManager::getEncryptString(const string& in, const string& key, const string& iv)
{
	int pre, post;
	string outStr;
	NxGetEncryptString(in, outStr, key, iv, pre, post);

	vector<string> splits;
	nxSplit(outStr, 2, back_inserter(splits));

	EncryptString str;
	str.set_pre(splits.front().c_str(), splits.front().size());
	string preSize = StringConverter::toString(pre);
	str.set_presize(base64_encode(reinterpret_cast<const unsigned char*>(preSize.c_str()), preSize.length()));
	str.set_post(splits.back().c_str(), splits.back().size());
	string postSize = StringConverter::toString(post);
	str.set_postsize(base64_encode(reinterpret_cast<const unsigned char*>(postSize.c_str()), postSize.length()));
	return str;
}

string GameDataManager::strtoupper(string str) {
	for (auto& c : str) c = toupper(c);
	return str;
}

W_GameData* GameDataManager::InitGameData(const W_GameData& data)
{
	mGameData = new W_GameData();
	mGameData->CopyFrom(data);

	_writeFile(m_Path);
	_makeHash();
	setModel();

	CCLOG("GameData initialized!");

	return mGameData;
}

void GameDataManager::RemoveUserDataInfo()
{
	if (m_pRecordInfo)
		delete m_pRecordInfo;
	m_pRecordInfo = nullptr;

	RemoveCharacterInfoList();
	RemoveLetterInfoList();
	RemoveQuestInfoList();
	RemoveEventList();
	//RemoveChannelList();
	RemoveFriendList();
}

void GameDataManager::RemoveCharacterInfoList()
{
	for (W_CharacterInfo* _pInfo : m_pCharacterInfoList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_pCharacterInfoList.clear();
}

void GameDataManager::RemoveLetterInfoList()
{
	for (W_LetterInfo* _pInfo : m_pLetterInfoList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_pLetterInfoList.clear();
}

void GameDataManager::RemoveQuestInfoList()
{
	for (W_QuestInfo* _pInfo : m_pQuestDailyList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_pQuestDailyList.clear();

	for (W_QuestInfo* _pInfo : m_pQuestWeeklyList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_pQuestWeeklyList.clear();
}

void GameDataManager::RemoveEventList()
{
	for (W_EventInfo* _pInfo : m_EventList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_EventList.clear();
}

void GameDataManager::RemoveChannelList()
{
	RemoveLobbyList();
	Remove7PokerList();
	RemoveHighLowList();
	RemoveBadukiList();
	RemoveHoldemList();
}

void GameDataManager::RemoveLobbyList()
{
	for (W_ChannelInfo* _pInfo : m_pLobbyChannelList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_pLobbyChannelList.clear();
}

void GameDataManager::Remove7PokerList()
{
	for (W_ChannelInfo* _pInfo : m_p7PokerChannelList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_p7PokerChannelList.clear();
}

void GameDataManager::RemoveHighLowList()
{
	for (W_ChannelInfo* _pInfo : m_pHighLowChannelList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_pHighLowChannelList.clear();
}

void GameDataManager::RemoveBadukiList()
{
	for (W_ChannelInfo* _pInfo : m_pBadukiChannelList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_pBadukiChannelList.clear();
}

void GameDataManager::RemoveHoldemList()
{
	for (W_ChannelInfo* _pInfo : m_pHoldemChannelList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_pHoldemChannelList.clear();
}

void GameDataManager::OnWebserviceMassage(int _type)
{
	//여기는 있으면 update 없으면 push 한다.
	switch (_type)
	{
	case W_S2C_CHANNEL_LIST_RES:
	{
		if (m_pOptionValue->m_music == true)
			SoundManager::getSingletonPtr()->playBGM("BGM_CHANNEL");

		if (LayerManager::getSingleton().hasLayerType<ChannelMainPannel>()) {
			ChannelMainPannel* pChannelMainPanel = dynamic_cast<ChannelMainPannel*>(LayerManager::getSingleton().getLayerType<ChannelMainPannel>());
			pChannelMainPanel->UpdateGameMode();
		}
		else {
			PanelHelper::pushChannelListPanel();
		}

		NotiData_eNotiType type = NotiDataManager::getSingleton().getEnterChannelNoti();
		if (type != NotiData_eNotiType_NoType) {
			PanelHelper::pushNotiChannelListPanel(type);			
		}
	}
		break;
	case W_S2C_FRIEND_LIST_RES:
		PanelHelper::pushFriendPanel();		
		break;
	case W_S2C_ADD_FRIEND_LIST_RES:
		if (LayerManager::getSingleton().hasLayerType<LobbyFriendPanel>()) {
			LobbyFriendPanel* pLobbyFriendPanel = dynamic_cast<LobbyFriendPanel*>(LayerManager::getSingleton().getLayerType<LobbyFriendPanel>());
			pLobbyFriendPanel->SetFriendlList();
		}
		else {
			PanelHelper::pushChannelListPanel();
		}
		
		//appdata update 한다.
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ReloadLobbyUiGameFriendList();
		}
		break;
	case W_S2C_UPDATE_FRIEND_LIST_RES:
		//appdata update 한다.
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ReloadLobbyUiFriendList();
		}
		break;
	case W_S2C_UPDATE_RECOMMEND_FRIEND_LIST_RES:
	case W_S2C_FRIEND_SEARCH_RES:
		//appdata update 한다.
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ReloadLobbyUiFriendList();
		}
		break;
	case W_S2C_UPDATE_RECOMMEND_FRIEND_DATA_RES:
		if (LayerManager::getSingleton().hasLayerType<LobbyFriendPanel>()) {
			LobbyFriendPanel* pLobbyFriendPanel = dynamic_cast<LobbyFriendPanel*>(LayerManager::getSingleton().getLayerType<LobbyFriendPanel>());
			pLobbyFriendPanel->m_pRecommendPanel->refreshTableView();
		}
		break;
	case W_S2C_OPEN_QUEST_LIST_RES:		
		PanelHelper::pushMissionPanel();
		break;
	case W_S2C_UPDATE_QUEST_LIST_RES:
		if (LayerManager::getSingleton().hasLayerType<LobbyMissionPanel>()){
			LobbyMissionPanel* lobbyMissionPanel = dynamic_cast<LobbyMissionPanel*>(LayerManager::getSingleton().getLayerType<LobbyMissionPanel>());
			if (lobbyMissionPanel) {
				lobbyMissionPanel->SetMissionlList();
			}
		}
		break;
	case W_S2C_SHOW_LETTER_LIST_RES:
		if (LayerManager::getSingleton().hasLayerType<LobbyInventoryPanel>()) {
			LobbyInventoryPanel* pLobbyInventoryPanel = dynamic_cast<LobbyInventoryPanel*>(LayerManager::getSingleton().getLayerType<LobbyInventoryPanel>());
			pLobbyInventoryPanel->UpdateCell();
		}
		else  {
			PanelHelper::pushLetterPanel();
		}
		break;
	case W_S2C_UPDATE_LETTER_LIST_RES:

		if (LayerManager::getSingleton().hasLayerType<LobbyInventoryPanel>()) {
			LobbyInventoryPanel* pLobbyInventoryPanel = dynamic_cast<LobbyInventoryPanel*>(LayerManager::getSingleton().getLayerType<LobbyInventoryPanel>());
			pLobbyInventoryPanel->UpdateCell();
		}

		//편지 보상은 애니메이션 후에 받아진다.
// 		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
// 		{
// 			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
// 			_pScene->UpdateLetterList();
// 		}
		break;
	case W_S2C_UPDATE_PLAYER_INFO_RES:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ApplyUserData();
		}

		if (LayerManager::getSingleton().hasLayerType<LobbyShopPanel>()) {
			LobbyShopPanel* pLobbyShopPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingleton().getLayerType<LobbyShopPanel>());
			pLobbyShopPanel->onRefresh();
		}

		break;
	case W_S2C_UPDATE_SLOTMACHINE_INFO_RES:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneMinigame)
		{
			MiniGamesScene* _pScene = dynamic_cast<MiniGamesScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->m_pSlotMachinePanel->SetSlotMachine();
		}
		break;
	case W_S2C_UPDATE_REPLAY_INFO_RES:
		if (LayerManager::getSingleton().hasLayerType<LobbyReplayPanel>()) {
			LobbyReplayPanel* pReplayPanel = dynamic_cast<LobbyReplayPanel*>(LayerManager::getSingleton().getLayerType<LobbyReplayPanel>());
			pReplayPanel->SetReplayList(); 
		}
		else {
			PanelHelper::pushReplayPanel();
		}
		break;
	case W_S2C_UPDATE_RANK_INFO_RES:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			PanelHelper::pushRankingTutorialPanel();
		}
		break;
	case W_S2C_POPUP_REPLAYBOX_LIST_RES:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			PanelHelper::pushReplayBoxPanel();			
		}
		break;
	case W_S2C_SELECT_CHARACTER_RES:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ApplyUserData();

			if (LayerManager::getSingleton().hasLayerType<LobbyInventoryPanel>()) {
				LobbyInventoryPanel* pInventoryPanel = dynamic_cast<LobbyInventoryPanel*>(LayerManager::getSingleton().getLayerType<LobbyInventoryPanel>());
				pInventoryPanel->UpdateCell();
			}
		}
		break;
	case W_S2C_EVENT_LIST_RES:
		PanelHelper::pushMissionPanel();		
		break;
	case W_S2C_EVENT_UPDATE_RES:
		if (LayerManager::getSingleton().hasLayerType<LobbyMissionPanel>()){
			LobbyMissionPanel* lobbyMissionPanel = dynamic_cast<LobbyMissionPanel*>(LayerManager::getSingleton().getLayerType<LobbyMissionPanel>());
			if (lobbyMissionPanel) {
				lobbyMissionPanel->SetMissionlList();
			}
		}

		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->UpdateEventListCell();
		}
		break;
	case W_S2C_PLAYER_NAME_RES:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ApplyUserData();
		}

		if (LayerManager::getSingleton().hasLayerType<LobbyMyHomeMainPanel>()){
			LobbyMyHomeMainPanel* homeMainPanel = dynamic_cast<LobbyMyHomeMainPanel*>(LayerManager::getSingleton().getLayerType<LobbyMyHomeMainPanel>());
			if (homeMainPanel) {
				homeMainPanel->refreshUserName();
			}
		}


		break;
	case W_S2C_FreeRefillRes:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->m_LobbyUIPanel->applyUserData();
			if (LayerManager::getSingleton().hasLayerType<GoldRefillPopupPanel>()) {
				GoldRefillPopupPanel* goldRefillPopupPanel = dynamic_cast<GoldRefillPopupPanel*>(LayerManager::getSingleton().getLayerType<GoldRefillPopupPanel>());
				if (goldRefillPopupPanel) {
					goldRefillPopupPanel->refreshData();
				}
			}

		}
		break;
	case W_S2C_RefreshRes:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->startPopupPanel();
			_pScene->ApplyUserData();
		}
		break;
	case W_S2C_BUY_CHARACTER_RES:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ApplyUserData();
		}
		break;
	case W_S2C_TOURNAMENT_REPLAY_RES:
		if (LayerManager::getSingleton().hasLayerType<LobbyTourSelectPanel>()) {
			LobbyTourSelectPanel* pLobbyTourSelectPanel = dynamic_cast<LobbyTourSelectPanel*>(LayerManager::getSingleton().getLayerType<LobbyTourSelectPanel>());
			pLobbyTourSelectPanel->ApplyRankGamePopup();
		}
		break;
	case W_S2C_TOURNAMENT_REWARD_RES:
	{
		if (LayerManager::getSingleton().hasLayerType<LobbyTourSelectPanel>()) {
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ApplyUserData();
			
			if (LayerManager::getSingleton().hasLayerType<LobbyTournamentMain>()) {
				LobbyTournamentMain* pLobbyTournamentMainPanel = dynamic_cast<LobbyTournamentMain*>(LayerManager::getSingleton().getLayerType<LobbyTournamentMain>());
				pLobbyTournamentMainPanel->m_BottomUi->UpdateChannelCell();
			}

			if (LayerManager::getSingleton().hasLayerType<LobbyTourSelectPanel>()) {
				LobbyTourSelectPanel* pLobbyTourSelectPanel = dynamic_cast<LobbyTourSelectPanel*>(LayerManager::getSingleton().getLayerType<LobbyTourSelectPanel>());
				pLobbyTourSelectPanel->refreshData();
			}
		}		
	}
		
		break;
	case W_S2C_TOURNAMENT_REFREASH_RES:
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		if (_pScene)
			_pScene->ApplyUserData();
	}
		break;
	case W_S2C_DEATHMATCH_REPLAY_RES:
	{
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			if (LayerManager::getSingleton().hasLayerType<LobbySurvivalWindowMain>()) {
				LobbySurvivalWindowMain* pLobbySurvivalWindowMainPanel = dynamic_cast<LobbySurvivalWindowMain*>(LayerManager::getSingleton().getLayerType<LobbySurvivalWindowMain>());
				pLobbySurvivalWindowMainPanel->ApplyRankGamePopup();
			}			
		}
	}
		break;
	case W_S2C_DEATHMATCH_CANCEL_RES:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			if (_pScene->m_LobbyUIPanel)
			{
				_pScene->ApplyUserData();
			}

			if (LayerManager::getSingleton().hasLayerType<LobbySurvivalMain>()) {
				LobbySurvivalMain* pLobbySurvivalMainPanel = dynamic_cast<LobbySurvivalMain*>(LayerManager::getSingleton().getLayerType<LobbySurvivalMain>());
				pLobbySurvivalMainPanel->m_BottomUi->UpdateChannelCell();
			}

			LobbySurvivalWindowMain* _SelectedPanel = dynamic_cast<LobbySurvivalWindowMain*>(LayerManager::getSingleton().getLayerType<LobbySurvivalWindowMain>());
			if (_SelectedPanel)
			{
				_SelectedPanel->ApplyData();
				//_SelectedPanel->ApplyGameTitle();
				//_SelectedPanel->ApplyBtnSetting();
				//_SelectedPanel->ApplyMyInfo();
				//_SelectedPanel->ApplyGameInfo();
			}
		}
		break;
	case W_S2C_DEATHMATCH_REFREASH_RES:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ApplyUserData();						
		}
		break;
	case W_S2C_BANK_IN_RES:

		if (LayerManager::getSingleton().hasLayerType<ChannelMainPannel>()) {
			ChannelMainPannel* pChanelMainPanel = dynamic_cast<ChannelMainPannel*>(LayerManager::getSingleton().getLayerType<ChannelMainPannel>());
			pChanelMainPanel->UpdateGameMode();
		}

		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ApplyUserData();
			
		}
		break;
	case W_S2C_BANK_OUT_RES:
	{
		if (LayerManager::getSingleton().hasLayerType<ChannelMainPannel>()) {
			ChannelMainPannel* pChanelMainPanel = dynamic_cast<ChannelMainPannel*>(LayerManager::getSingleton().getLayerType<ChannelMainPannel>());
			pChanelMainPanel->UpdateGameMode();
		}



		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ApplyUserData();
		}
	}
		break;
	case ERROR_MASSGE_WAITING_OVER:
		if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneTitle)
		{
			string _text = GameStringDepot::getSingletonPtr()->getString("TXT_ERROR_WAITINGTIME_OVER");
			SimplePopupPanel* _pErrorPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _text);
			LayerManager::getSingleton().pushDynamicLayer(_pErrorPopup, DYNAMIC_PUSH_LAYER);

			if (LayerManager::getSingletonPtr()->hasLayer("Title"))
			{
				TitlePanel* _panel = dynamic_cast<TitlePanel*>(LayerManager::getSingletonPtr()->getLayer("Title"));
				if (_panel)
				{
					_panel->showLoginButton(true);
				}
			}
		}
		else if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
		{

		}
		break;
	default:
		break;
	}
}

void GameDataManager::RemoveFriendList()
{
	RemoveSnsDataList();
	RemoveFriendDataList();
	RemoveRecommendDataList();
	RemoveRequestDataList();
}

void GameDataManager::RemoveSnsDataList()
{
	for (W_FriendInfo* _pInfo : m_SnsDataList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_SnsDataList.clear();
}

void GameDataManager::RemoveFriendDataList()
{
	for (W_FriendInfo* _pInfo : m_FriendDataList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_FriendDataList.clear();
}

void GameDataManager::RemoveRecommendDataList()
{
	for (W_FriendInfo* _pInfo : m_RecommendDataList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_RecommendDataList.clear();
}

void GameDataManager::RemoveRequestDataList()
{
	for (W_FriendInfo* _pInfo : m_RequestDataList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_RequestDataList.clear();
}

void GameDataManager::SetSlotMachineRewardInfo(W_RewardInfo* _pInfo)
{
	if (m_SlotMachineRewardInfo)
	{
		delete m_SlotMachineRewardInfo;
		m_SlotMachineRewardInfo = nullptr;
	}
	m_SlotMachineRewardInfo = _pInfo;
}

void GameDataManager::RemoveReplayDataList()
{
	int _size = m_ReplaySaveList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		if (m_ReplaySaveList[_i])
			delete m_ReplaySaveList[_i];

		m_ReplaySaveList[_i] = nullptr;
	}

	m_ReplaySaveList.clear();
}

void GameDataManager::RemoveRankDataList()
{
	for (W_RankInfo* _pInfo : m_RankInfoList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_RankInfoList.clear();
}

void GameDataManager::RemoveMyRankData()
{
	if (m_pMyRankInfo) delete m_pMyRankInfo;
	m_pMyRankInfo = nullptr;
}

void GameDataManager::ReomveChannelRoomInfoList()
{
	for (RoomInfo* _pinfo : m_RoomInfoList)
	{
		if (_pinfo) delete _pinfo;
		_pinfo = nullptr;
	}
	m_RoomInfoList.clear();
}

//void GameDataManager::SetLobbyUIState(int _state)
//{
//	if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
//	{
//		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
//
//		if (_pScene)
//		{
//			LobbyUIPanel* _pPanel = _pScene->m_LobbyUIPanel;
//			if (_pPanel)
//			{
//				_pPanel->m_UiState = _state;
//			}
//		}
//	}
//}

void GameDataManager::update(float dt)
{
	if (m_bEditTextField == true)
	{
		CCLog("GameDataManager::update m_bEditTextField");
		if (m_onFocusTextFeild)
		{
			CCLog("m_onFocusTextFeild setstring = %s", m_eidtText.c_str());
			m_onFocusTextFeild->setString(m_eidtText.c_str());
		}
		m_bEditTextField = false;
	}

	if (m_pPlayerData)
	{
		m_pPlayerData->UpdateTime(dt);
	}

	if (mUserInfo) {
		if (mUserInfo->playerinfo().granchancelefttime() > 0.f) {
			double finalDt = mUserInfo->playerinfo().granchancelefttime() - dt;
			if (finalDt < 0.f)
				finalDt = 0.f;
			mUserInfo->mutable_playerinfo()->set_granchancelefttime(finalDt);
		}

		if (mUserInfo->playerinfo().bankexpiretime() > 0.f) {
			double finalDt = mUserInfo->playerinfo().bankexpiretime() - dt;
			if (finalDt < 0.f)
				finalDt = 0.f;
			mUserInfo->mutable_playerinfo()->set_bankexpiretime(finalDt);
		}
	}

	if (m_TourOfInfo) {
		if (m_TourOfInfo->endlefttime() > 0.f) {
			double finalDt = m_TourOfInfo->endlefttime() - dt;
			if (finalDt < 0.f)
				finalDt = 0.f;
			m_TourOfInfo->set_endlefttime(finalDt);
		}

		if (m_TourOfInfo->playlefttime() > 0.f) {
			double finalDt = m_TourOfInfo->playlefttime() - dt;
			if (finalDt < 0.f)
				finalDt = 0.f;
			m_TourOfInfo->set_playlefttime(finalDt);
		}
	}
	
	SceneManager::getSingletonPtr()->getCurrentScene();
	//캐릭터 남은 시간
	//한정 상품 관련
	updateLimitedShop(dt);	

	//게임 플레이 남은 시간
	if (!mPlayTimeAni) {
		mPlayTime += (dt);
		if (mPlayTime > PLAY_GAME) {
			mPlayTimeAni = true;
			mPlayTime = 0.f;
			int perHour = (float)PLAY_GAME / (float)ONE_HOUR;			
			mPlayTimeHour += perHour;
		}
	}
}

std::string GameDataManager::GetRemainWeeklyBonusTime(int _type)
{
	if (!m_pPlayerData)
		return "";

	double _time = m_pPlayerData->m_WeeklyRankExpireTime;
	double _gone = m_pPlayerData->m_GoneTime;

	int64 _remain = _time - _gone;

	double _day = _remain / (24*60*60);
	double _hour = _remain % (24 * 60 * 60) / (60*60);
	double _min = _remain % (60 * 60) / 60;
	double _sec = _remain % 60;

	if (_type == SHOW_TIME_DAY)
	{
		_day += 1;
	}

	string _textTime = "";
	bool _isTimeLeft = false;
	if (_day > 0 && _type >= SHOW_TIME_DAY)
	{
		_textTime += StringConverter::toString(_day);
		_textTime += GameStringDepot::getSingleton().getString("TXT_DAY");
		_isTimeLeft = true;
	}
	if (_hour > 0 && _type >= SHOW_TIME_HOUR)
	{
		_textTime += StringConverter::toString(_hour);
		_textTime += GameStringDepot::getSingleton().getString("TXT_HOUR_LEFT");
		_isTimeLeft = true;
	}
	if (_min > 0 && _type >= SHOW_TIME_MIN)
	{
		_textTime += StringConverter::toString(_min);
		_textTime += GameStringDepot::getSingleton().getString("TXT_MINUTE");
		_isTimeLeft = true;
	}
	if (_sec > 0 && _type >= SHOW_TIME_ALL)
	{
		_textTime += StringConverter::toString(_sec);
		_textTime += GameStringDepot::getSingleton().getString("TXT_SECOND");
		_isTimeLeft = true;
	}

	if (_isTimeLeft)
	{
		_textTime += " ";
		_textTime += GameStringDepot::getSingleton().getString("TXT_TIMELEFT");
	}
	else
	{
		_textTime = "0" + GameStringDepot::getSingleton().getString("TXT_SECOND") + " " + GameStringDepot::getSingleton().getString("TXT_TIMELEFT");
	}

	return _textTime;
}

std::string GameDataManager::GetTimeString(int64 _remain, bool _noSec)
{
	double _day = _remain / (24 * 60 * 60);
	double _hour = _remain % (24 * 60 * 60) / (60 * 60);
	double _min = _remain % (60 * 60) / 60;
	double _sec = _remain % 60;
	string _textTime = "";

	if (_day > 0)
	{
		_textTime += StringConverter::toString(_day);
		_textTime += GameStringDepot::getSingleton().getString("TXT_DAY");
	}
	if (_hour > 0)
	{
		_textTime += StringConverter::toString(_hour);
		_textTime += GameStringDepot::getSingleton().getString("TXT_HOUR_LEFT");
	}
	if (_min > 0)
	{
		_textTime += StringConverter::toString(_min);
		_textTime += GameStringDepot::getSingleton().getString("TXT_MINUTE");
	}
	if (_sec > 0 && !_noSec)
	{
		_textTime += StringConverter::toString(_sec);
		_textTime += GameStringDepot::getSingleton().getString("TXT_SECOND");
	}

	return _textTime;
}

std::string GameDataManager::GetRemainTime(int64 _remainTime, bool isFull, bool useSec , bool useRemainText)
{
	if (!m_pPlayerData)
		return "";

	double _time = _remainTime;
	double _gone = m_pPlayerData->m_GoneTime;

	int64 _remain = _time - _gone;

	double _day = _remain / (24 * 60 * 60);
	double _hour = _remain % (24 * 60 * 60) / (60 * 60);
	double _min = _remain % (60 * 60) / 60;
	double _sec = _remain % 60;

	string _textTime = "";
	bool _isTimeLeft = false;
	if (_day > 0)
	{
		_textTime += StringConverter::toString(_day);
		_textTime += GameStringDepot::getSingleton().getString("TXT_DAY");
		_isTimeLeft = true;
	}
	if ((!_isTimeLeft || (_isTimeLeft  && isFull)) && _hour > 0)
	{
		_textTime += StringConverter::toString(_hour);
		_textTime += GameStringDepot::getSingleton().getString("TXT_HOUR_LEFT");
		_isTimeLeft = true;
	}
	if ((!_isTimeLeft || (_isTimeLeft  && isFull)) && _min > 0)
	{
		_textTime += StringConverter::toString(_min);
		_textTime += GameStringDepot::getSingleton().getString("TXT_MINUTE");
		_isTimeLeft = true;
	}
	if ((!_isTimeLeft || (_isTimeLeft  && isFull)) && useSec && _sec > 0)
	{
		_textTime += StringConverter::toString(_sec);
		_textTime += GameStringDepot::getSingleton().getString("TXT_SECOND");
		_isTimeLeft = true;
	}

	if (_isTimeLeft)
	{
		_textTime += " ";
		if(useRemainText)
			_textTime += GameStringDepot::getSingleton().getString("TXT_TIMELEFT");
	}
	else
	{
		_textTime = "0" + GameStringDepot::getSingleton().getString("TXT_SECOND") + " ";
		if (useRemainText)
			_textTime += GameStringDepot::getSingleton().getString("TXT_TIMELEFT");
	}

	return _textTime;
}

bool CompvarReplayScore(W_ReplaySaveInfo* a, W_ReplaySaveInfo* b)
{
	return a->point() > b->point();
}

bool CompvarReplayDate(W_ReplaySaveInfo* a, W_ReplaySaveInfo* b)
{
	return a->time() > b->time();
}

bool CompvarRankingScore(W_RankInfo* a, W_RankInfo* b)
{
	return a->point() < b->point();
}

bool CompvarRankingKill(W_RankInfo* a, W_RankInfo* b)
{
	return a->kill() < b->kill();
}

bool CompvarFriendDate(W_FriendInfo* a, W_FriendInfo* b)
{
	return a->time() < b->time();
}

bool CompvarFriendLevel(W_FriendInfo* a, W_FriendInfo* b)
{
	return a->level() < b->level();
}

void GameDataManager::SortReplayData(int _type)
{
	switch (_type)
	{
	case SORT_TYPE_SCORE:
		sort(m_ReplaySaveList.begin(), m_ReplaySaveList.end(), CompvarReplayScore);
		break;
	case SORT_TYPE_DATE:
		sort(m_ReplaySaveList.begin(), m_ReplaySaveList.end(), CompvarReplayDate);
		break;
	}
}

void GameDataManager::SortRankingData(int _type)
{
	switch (_type)
	{
	case SORT_TYPE_SCORE:
		sort(m_RankInfoList.begin(), m_RankInfoList.end(), CompvarRankingScore);
		break;
	case SORT_TYPE_KILL:
		sort(m_RankInfoList.begin(), m_RankInfoList.end(), CompvarRankingKill);
		break;
	}
}

void GameDataManager::SortFriendData(int _type, int _ndataType)
{
	switch (_type)
	{
	case SORT_TYPE_DATE:
		if (_ndataType == FRIEND_DATA_SNS)
		{
			sort(m_SnsDataList.begin(), m_SnsDataList.end(), CompvarFriendDate);
		}
		else if (_ndataType == FRIEND_DATA_GAME)
		{
			sort(m_FriendDataList.begin(), m_FriendDataList.end(), CompvarFriendDate);
		}
		//else if (_ndataType == FRIEND_DATA_REQUEST)
		//{
		//	sort(m_RequestDataList.begin(), m_RequestDataList.end(), CompvarFriendDate);
		//}
		//else if (_ndataType == FRIEND_DATA_RECOMMEND)
		//{
		//	sort(m_RecommendDataList.begin(), m_RecommendDataList.end(), CompvarFriendDate);
		//}
		break;
	case SORT_TYPE_LEVEL:
		if (_ndataType == FRIEND_DATA_SNS)
		{
			sort(m_SnsDataList.begin(), m_SnsDataList.end(), CompvarFriendLevel);
		}
		else if (_ndataType == FRIEND_DATA_GAME)
		{
			sort(m_FriendDataList.begin(), m_FriendDataList.end(), CompvarFriendLevel);
		}
		//else if (_ndataType == FRIEND_DATA_REQUEST)
		//{
		//	sort(m_RequestDataList.begin(), m_RequestDataList.end(), CompvarFriendLevel);
		//}
		//else if (_ndataType == FRIEND_DATA_RECOMMEND)
		//{
		//	sort(m_RecommendDataList.begin(), m_RecommendDataList.end(), CompvarFriendLevel);
		//}
		break;
	}
}

void GameDataManager::FreeUiProcess()
{
	if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		_pScene->m_LobbyUIPanel->mUiProcess = false;
	}
}

void GameDataManager::RemoveHistoryState()
{
	m_uiHistoryList.clear();
}

void GameDataManager::HistoryStatePush(int _state)
{
	m_uiHistoryList.push_back(_state);
}

int GameDataManager::HistoryPop()
{
	vector<int>::iterator _itor = m_uiHistoryList.end();
	int _uiState = (*_itor);

	m_uiHistoryList.pop_back();
	return _uiState;
}

void GameDataManager::OpenUrl(string url)
{	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AndroidUtilManager::getSingletonPtr()->ReleaseWebView();
	int Height = AndroidUtilManager::getSingletonPtr()->GetScreenHeight();
	float Width = (16.f/9.f)*Height;
	int WebviewPosionX = (AndroidUtilManager::getSingletonPtr()->GetScreenWidth() - Width)/2;
    //AndroidUtilManager::getSingletonPtr()->InitWebView(url, 0, 0, AndroidUtilManager::getSingletonPtr()->GetScreenWidth() - 58 * AndroidUtilManager::getSingletonPtr()->GetScreenWidth() /1024, AndroidUtilManager::getSingletonPtr()->GetScreenHeight());
	CCLOG("Width = %f", Width); CCLOG("Height = %f", Height); CCLOG("WebviewPosionX = %d", WebviewPosionX);
	AndroidUtilManager::getSingletonPtr()->InitWebView(url, WebviewPosionX, 0, Width-100, Height);
#endif
}

void GameDataManager::openAdultUrl(string token_version_id, string enc_data, string integrity_value)
{	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManager::getSingletonPtr()->ReleaseWebView();
	string url = GAMBLE_WEB_ADULT_URL;
	//url.append("?uid=" + StringConverter::toString(uid));	
	CCLog("adultUrl = %s", url.c_str());
	AndroidUtilManager::getSingletonPtr()->InitWebView(url, 0, 0, AndroidUtilManager::getSingletonPtr()->GetScreenWidth(), AndroidUtilManager::getSingletonPtr()->GetScreenHeight());
#endif
}

void GameDataManager::CloseUrl()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManager::getSingletonPtr()->ReleaseWebView();
	//AndroidUtilManager::getSingletonPtr()->DeleteWebView();
#endif
}

void GameDataManager::HideUrl()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManager::getSingletonPtr()->HideWebView();
#endif
}

void GameDataManager::ShowUrl()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	AndroidUtilManager::getSingletonPtr()->ShowWebView();
#endif
}

string GameDataManager::GetParamUrl(string& url)
{
	string urlStr = "";
	urlStr.append(url);
	if (m_pPlayerData->GetUID() > 0)
	{
		urlStr.append("&umidx=");
		urlStr.append(StringConverter::toString(m_pPlayerData->GetUID()));
	}

	urlStr.append("&tel=");
	urlStr.append(StringConverter::toString(STORE_KIND));

	return urlStr;
}

void GameDataManager::ShowCustomWebview(WebPageType type)
{
	string url = "";
	switch (type)
	{
		case WEB_HELP_TYPE :
			url = GAMBLE_DEFAULT_URL + GAMBLE_HELP_URL;
			break;
		case WEB_ASK_TYPE:
			url = GAMBLE_DEFAULT_URL + ASK_URL;
			break;
		case WEB_POLICY_TYPE:
			url = GAMBLE_DEFAULT_URL + GAMBLE_PRIVATE_POLICY;
			break;
		case WEB_TERM_TYPE:
			url = GAMBLE_DEFAULT_URL + GAMBLE_TERM;
			break;
		case WEB_SILVER_MEMBER_TYPE:
			url = GAMBLE_DEFAULT_URL + SILVER_MEMBERSHIP_URL;
			break;
		case WEB_GOLD_MEMBER_TYPE:
			url = GAMBLE_DEFAULT_URL + GOLD_MEMBERSHIP_URL;
			break;
		case WEB_ADULT:
			url = GAMBLE_DEFAULT_URL + GAMBLE_WEB_ADULT_URL;
			break;
		case WEB_TOURNAMENT_TYPE:
			url = GAMBLE_DEFAULT_URL + WEB_TOURNAMENT_URL;
			break;
		case WEB_REFUND_TYPE:
			url = GAMBLE_DEFAULT_URL + WEB_REFUND_URL;
			break;
		case WEB_CAMPAIGN_TYPE:
			url = GAMBLE_DEFAULT_URL + CAMPAIGN_URL;
			break;
		case WEB_MOBLIE_USAGE:
			url = GAMBLE_DEFAULT_URL + GAMBLE_MOBLIE_USAGE;
			break;
	}

	if (m_WebViewPanel != nullptr) {
	}

	if (type == WEB_HELP_TYPE || type == WEB_ASK_TYPE || type == WEB_POLICY_TYPE || type == WEB_ADULT || type == WEB_TOURNAMENT_TYPE || type == WEB_SILVER_MEMBER_TYPE || type == WEB_GOLD_MEMBER_TYPE || type == WEB_TOURNAMENT_TYPE || type == WEB_CAMPAIGN_TYPE || type == WEB_MOBLIE_USAGE || type == WEB_TERM_TYPE)
		m_WebViewPanel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::WEB_VIEW_TYPE, 0, 0, 0, url);
	else
		m_WebViewPanel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::WEB_VIEW_TYPE, 0, 0, 0, GetParamUrl(url));

	LayerManager::getSingleton().pushDynamicLayer(m_WebViewPanel, DYNAMIC_PUSH_LAYER);
}

bool GameDataManager::IsPushCustomWebview()
{
	return m_WebViewPanel != nullptr;
}

void GameDataManager::SetUiState(int _state)
{
	if (SceneManager::getSingletonPtr()->getCurrentSceneID() == SceneUtil::SceneLobby)
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getScene(SceneUtil::SceneLobby));
		if (_pScene)
		{
			m_LobbyUiHistory.push_back(_state);
			m_LobbyUiState = _state;
			_pScene->m_LobbyUIPanel->m_UiState = _state;
		}
	}
}

int GameDataManager::PopUiState()
{
	int _returnValue = -1;

	if (SceneManager::getSingletonPtr()->getCurrentSceneID() == SceneUtil::SceneLobby)
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		if (_pScene)
		{
			int _size = m_LobbyUiHistory.size();
			if (_size == 0)
				return -1;

			_returnValue = m_LobbyUiState;
			m_LobbyUiHistory.pop_back();
			_size = m_LobbyUiHistory.size();
			if (_size == 0)
				return -1;

			m_LobbyUiState = m_LobbyUiHistory[_size - 1];

			_pScene->m_LobbyUIPanel->m_UiState = m_LobbyUiState;

			if (_returnValue == LOBBY_UI_MISSION || _returnValue == LOBBY_UI_LETTER || _returnValue == LOBBY_UI_SHOP || _returnValue == LOBBY_UI_INVEN)
			{
				if (m_LobbyUiHistory.size() != 1) {
					if (m_LobbyUiState == LOBBY_UI_CHANNELLIST) {
						m_LobbyUiHistory.pop_back();
						_pScene->ShowLobbyUiChannelList();
						FreeUiProcess();
					}
					else {
						MoveToHistoryState(m_LobbyUiState);
					}
				}
			}
			else if (_returnValue == LOBBY_UI_TOURNAMENT_SELECT) {
				//기덕수정
// 				LobbyTournamentMain* _pPanel = dynamic_cast<LobbyTournamentMain*>(LayerManager::getSingletonPtr()->getLayer("LobbyTournamet"));
// 				if (_pPanel)
// 				{
// 					_pPanel->setVisibleChannelCell(true);
// 				}
			}			
		}
	}
	
	return _returnValue;
}

//void GameDataManager::FadeoutLobby(float _delay)
//{
//	if (SceneUtil::getCurrentSceneId() != SceneUtil::SceneLobby)
//		return;
//
//	if (CCDirector::sharedDirector()->getActionManager() == NULL)
//		return;
//
//	LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
//
//	if (_pScene == nullptr)
//		return;
//
//	_pScene->LobbyFadeOut(_delay);
//
//}
//void GameDataManager::FadeinLobby(float _delay)
//{
//	if (SceneUtil::getCurrentSceneId() != SceneUtil::SceneLobby)
//		return;
//
//	LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
//
//	if (_pScene == nullptr)
//		return;
//
//	_pScene->LobbyFadeIn(_delay);
//}

void GameDataManager::MoveToUiState(int _state)
{
	if (SceneUtil::getCurrentSceneId() != SceneUtil::SceneLobby)
		return;

	LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

	if (_pScene == nullptr)
		return;

	if (_pScene->m_LobbyUIPanel == nullptr)
		return;

	if (_state == LOBBY_UI_CHANNELLIST)
		_pScene->m_LobbyUIPanel->m_bOtherUi = false;
	else
		_pScene->m_LobbyUIPanel->m_bOtherUi = true;

	switch (_state)
	{
	case LOBBY_UI_MYHOME:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		_pScene->m_LobbyUIPanel->ShowMyRoomUi();
		break;
	case LOBBY_UI_LETTER:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		WebService::getSingletonPtr()->_sendLetterListReq();
		break;
	case LOBBY_UI_FRIEND:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		WebService::getSingletonPtr()->_sendFriendOfInfoReq();
		break;
	case LOBBY_UI_MISSION:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		WebService::getSingletonPtr()->_sendQuestListUpdateReq();
		break;
	case LOBBY_UI_SHOP:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		_pScene->m_LobbyUIPanel->SetShopUi();
		break;
	case LOBBY_UI_DAYCHECK:
		break;
	case LOBBY_UI_RANKING:
	{
	}
		break;
	case LOBBY_UI_REPLAY:
	{
// 		_pScene->m_LobbyUIPanel->m_UiState = LOBBY_UI_REPLAY_PROCESS;
// 		int _Tapindex = _pScene->m_pReplayPanel->m_TapIndex;
// 		switch (_Tapindex)
// 		{
// 		case 0:
// 			WebService::getSingletonPtr()->_sendReplayWeeklyReq();
// 			break;
// 		case 1:
// 			WebService::getSingletonPtr()->_sendReplayDailyReq();
// 			break;
// 		case 2:
// 			WebService::getSingletonPtr()->_sendReplayListReq(GetPlayerDataPtr()->GetUID());
// 			break;
// 		default:
// 			break;
// 		}
	}
		break;
	
	case LOBBY_UI_CHANNELLIST:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		WebService::getSingletonPtr()->SendChannelListReq();
		break;
	case LOBBY_UI_OPTION:
// 		_pScene->m_LobbyUIPanel->mUiProcess = true;
// 		_pScene->m_LobbyUIPanel->ShowOptionUi();
		break;
	}
}

void GameDataManager::MoveToHistoryState(int _state)
{
	if (SceneUtil::getCurrentSceneId() != SceneUtil::SceneLobby)
		return;
	
	LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

	if (_pScene == nullptr)
		return;

	if (_pScene->m_LobbyUIPanel == nullptr)
		return;

	m_LobbyUiHistory.pop_back();
	m_LobbyUiState = m_LobbyUiHistory[m_LobbyUiHistory.size() - 1];

	if (_state == LOBBY_UI_CHANNELLIST || _state == LOBBY_UI_TOURNAMENT_SELECT || _state == LOBBY_UI_SURVIVAL_SELECT)
		_pScene->m_LobbyUIPanel->m_bOtherUi = false;
	else 
		_pScene->m_LobbyUIPanel->m_bOtherUi = true;

	switch (_state)
	{
	case LOBBY_UI_MYHOME:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		_pScene->m_LobbyUIPanel->ShowMyRoomUi();
		break;
	case LOBBY_UI_LETTER:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		WebService::getSingletonPtr()->_sendLetterListReq();
		break;
	case LOBBY_UI_FRIEND:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		WebService::getSingletonPtr()->_sendFriendOfInfoReq();
		break;
	case LOBBY_UI_MISSION:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		WebService::getSingletonPtr()->_sendQuestListUpdateReq();
		break;
	case LOBBY_UI_SHOP:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		_pScene->m_LobbyUIPanel->SetShopUi();
		break;
	case LOBBY_UI_DAYCHECK:
		break;
	case LOBBY_UI_RANKING:
	{
// 		_pScene->m_LobbyUIPanel->m_UiState = LOBBY_UI_RANKING_PROCESS;
// 		int _Tapindex = _pScene->m_pRankingPanel->m_TapIndex;
// 		if (_Tapindex == 0)
// 		{
// 			WebService::getSingletonPtr()->_sendRankInfoReq(W_RankInfoReq_eRankType_All);
// 		}
// 		else if (_Tapindex == 1)
// 		{
// 			WebService::getSingletonPtr()->_sendRankInfoReq(W_RankInfoReq_eRankType_Friend);
// 		}
	}
		break;
	case LOBBY_UI_REPLAY:
	{
		if (LayerManager::getSingleton().hasLayerType<LobbyReplayPanel>()){
			LobbyReplayPanel* lobbyReplayPanel = dynamic_cast<LobbyReplayPanel*>(LayerManager::getSingleton().getLayerType<LobbyReplayPanel>());
			if (lobbyReplayPanel) {
				int _Tapindex = lobbyReplayPanel->m_TapIndex;
				switch (_Tapindex)
				{
				case 0:
					WebService::getSingletonPtr()->_sendReplaySeasonReq();
					break;
				case 1:
					WebService::getSingletonPtr()->_sendReplayDeathMatchReq();
					break;
				case 2:
					WebService::getSingletonPtr()->_sendReplayListReq(GetPlayerDataPtr()->GetUID());
					break;
				default:
					break;
				}
			}
		}

		return;
		/*
		_pScene->m_LobbyUIPanel->m_UiState = LOBBY_UI_REPLAY_PROCESS;
		int _Tapindex = _pScene->m_pReplayPanel->m_TapIndex;
		switch (_Tapindex)
		{
		case 0:
			WebService::getSingletonPtr()->_sendReplayWeeklyReq();
			break;
		case 1:
			WebService::getSingletonPtr()->_sendReplayDailyReq();
			break;
		case 2:
			WebService::getSingletonPtr()->_sendReplayListReq(GetPlayerDataPtr()->GetUID());
			break;
		default:
			break;
		}
		*/
	}
		break;	
	case LOBBY_UI_CHANNELLIST:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		WebService::getSingletonPtr()->SendChannelListReq();
		break;
	case LOBBY_UI_OPTION:
		_pScene->m_LobbyUIPanel->mUiProcess = true;
		_pScene->m_LobbyUIPanel->ShowOptionUi();
		break;
	case LOBBY_UI_TOURNAMENT:		
		//기덕수정
		//LayerManager::getSingletonPtr()->pushLayer("LobbyTournamet", ZODER_LOBBY_TOURMAMENT);
		//GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_TOURNAMENT);
		break;
	case LOBBY_UI_TOURNAMENT_SELECT:
		//기덕수정
		//LayerManager::getSingletonPtr()->pushLayer("LobbyTournamet", ZODER_LOBBY_TOURMAMENT);
		//LayerManager::getSingletonPtr()->pushLayer("TournamentSelect", ZODER_LOBBY_TOURMAMENT_SELECT);
		//GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_TOURNAMENT_SELECT);
		break;
	case LOBBY_UI_SURVIVAL:
		//기덕수정
		//LayerManager::getSingletonPtr()->pushLayer("LobbySurvival", ZODER_LOBBY_SURVIVAL);
		//GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SURVIVAL);
		break;
	case LOBBY_UI_SURVIVAL_SELECT:
		//기덕수정
		//LayerManager::getSingletonPtr()->pushLayer("LobbySurvival", ZODER_LOBBY_SURVIVAL);
		//LayerManager::getSingletonPtr()->pushLayer("SurvivalSelect", ZODER_LOBBY_SURVIVAL_SELECT);
		//GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SURVIVAL_SELECT);
		break;

	case LOBBY_UI_INVEN:
// 		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_INVEN);
// 		if (LayerManager::getSingleton().hasLayer("LobbyInven")){
// 			LobbyInventoryPanel* inventoryPanel = dynamic_cast<LobbyInventoryPanel*>(LayerManager::getSingleton().getLayer("LobbyInven"));
// 			if (inventoryPanel)
// 				inventoryPanel->setActivate();
// 		}
// 
// 		if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
// 		{
// 			LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
// 			if (_pTopUiPanel)
// 			{
// 				_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_INVEN);
// 			}
// 		}
		break;
	}
}

int GameDataManager::GetUiState()
{
	return m_LobbyUiState;
}

void GameDataManager::ClearUiState()
{
	m_LobbyUiHistory.clear();
	m_LobbyUiState = LOBBY_UI_NO;
	m_pChannelListPanel = nullptr;
}

bool GameDataManager::hasUiHistoryState(int _state)
{
	for (int _uiHistory : m_LobbyUiHistory)
	{
		if (_uiHistory == _state)
		{
			return true;
		}
	}
	return false;
}

void GameDataManager::CloseTopCoustomPopup()
{
	CustomPopupPanel* _pPanel = dynamic_cast<CustomPopupPanel*>(LayerManager::getSingletonPtr()->getCurrentLayer());
	if (_pPanel)
	{
		//PopUiState();
		_pPanel->ShowPanel(false);
	}
}

void GameDataManager::CloseTopSimplePopup()
{
	SimplePopupPanel* _pPanel = dynamic_cast<SimplePopupPanel*>(LayerManager::getSingletonPtr()->getCurrentLayer());
	if (_pPanel)
	{
		//PopUiState();
		_pPanel->ShowPanel(false);
		_pPanel->OnExitEvent();
	}
}

void GameDataManager::CloseTopAccountPopup()
{
	AccountPopupPanel* _pPanel = dynamic_cast<AccountPopupPanel*>(LayerManager::getSingletonPtr()->getCurrentLayer());
	if (_pPanel)
	{
		_pPanel->ShowPanel(false);
	}
}

void GameDataManager::CloseSelectCharactePopup()
{
	//SelectCharacterPanel* _pPanel = dynamic_cast<SelectCharacterPanel*>(LayerManager::getSingletonPtr()->getCurrentLayer());
	//if (_pPanel)
	//{
	//	_pPanel->ShowPanel(false);
	//}
}

ChangeCardKind GameDataManager::GetBadugiDayKind()
{
	ChangeCardKind _returnValue = ChangeCardKind::CHANGE_CARD_KIND_NO;

	switch (m_kindBadugiDay)
	{
	case DAY_TYPE_MORNING:
		_returnValue = ChangeCardKind::CHANGE_CARD_KIND_MORNING;
		break;
	case DAY_TYPE_AFTERNOON:
		_returnValue = ChangeCardKind::CHANGE_CARD_KIND_NOON;
		break;
	case DAY_TYPE_NIGHT:
		_returnValue = ChangeCardKind::CHANGE_CARD_KIND_EVENING;
		break;
	}

	return _returnValue;
}

void GameDataManager::RemoveTournamentOfInfo()
{
	if (m_TourOfInfo)
	{
		NX_SAFE_DELETE(m_TourOfInfo);
		m_TourOfInfo = nullptr;
	}
}

void GameDataManager::CheckTournamentEnd()
{
	if (m_bTournamentEnd == true)
	{
		m_bTournamentEnd = false;
		WebService::getSingletonPtr()->TournamentRefreshReq();
	}
	else
	{
		WebService::getSingletonPtr()->SendRefreshReq();
	}
}

void GameDataManager::CheckDeathmatchEnd()
{
	if (m_bDeathmatchEnd == true)
	{
		m_bDeathmatchEnd = false;
		int32 _matchId = m_seasonId;
		WebService::getSingletonPtr()->SurvivalRefreshReq(_matchId);
	}
	else
	{
		WebService::getSingletonPtr()->SendRefreshReq();
	}
}


void GameDataManager::RemoveSurvivalOfInfo()
{
	if (m_SurvivalOfInfo)
	{
		NX_SAFE_DELETE(m_SurvivalOfInfo);
		m_SurvivalOfInfo = nullptr;
	}
}

void GameDataManager::SetFacebookUesrName(std::string _name)
{
	m_FacebookUserName = _name;	
}

void GameDataManager::SetFacebookUesrId(std::string _id)
{
	m_FacebookUserId = _id;
}

void GameDataManager::SetFacebookUesrEmail(std::string _id)
{
	m_FacebookUserEmail = _id;
}

void GameDataManager::SetFacebookUesrPhotoUrl(std::string _url)
{
	m_FacebookUserPhotoUrl = _url;
}

void GameDataManager::ResetSurvivalLeftTime()
{
	m_bSurvivalTimeUpdate = false;
	m_fTimeSecond = 0.f;
	m_PastTime = 0;
}


//서바이벌 남은 시간 업데이트 
void GameDataManager::UpdateSurvivalLeftTime(float _dt)
{
	if (m_bSurvivalTimeUpdate == false)
		return;

	if (m_SurvivalOfInfo)
	{
		m_fTimeSecond += _dt;
		if (m_fTimeSecond >= 1.f)
		{
			m_fTimeSecond -= 1.f;
			m_PastTime++;
		}
	}

	if (Survival_RegisterableTime > 0.f) {  //등록 가능한 시간
		double finalDt = Survival_RegisterableTime - _dt;
		if (finalDt < 0.f) {
			finalDt = 0.f;
			Survival_UserStatus = W_DeathMatchInfo_eUserStatus::W_DeathMatchInfo_eUserStatus_eRegister; //등록시간이 
		}
		
		Survival_RegisterableTime = finalDt;
	}

	if (Survival_RegisterExpireTime > 0.f) {  // 등록 만료 시간 나타냄
		double finalDt = Survival_RegisterExpireTime - _dt;
		if (finalDt < 0.f) {
			finalDt = 0.f;
			Survival_UserStatus = W_DeathMatchInfo_eUserStatus::W_DeathMatchInfo_eUserStatus_eWait;
		}
		Survival_RegisterExpireTime = finalDt;
	}

	if (Survival_WaitableTime > 0.f) {       //등록만료 시간을나타냄
		double finalDt = Survival_WaitableTime - _dt;
		if (finalDt < 0.f) {
			finalDt = 0.f;
			Survival_UserStatus = W_DeathMatchInfo_eUserStatus::W_DeathMatchInfo_eUserStatus_eWait;
		}
		Survival_WaitableTime = finalDt;
	}

	if (Survival_WaitExpireTime > 0.f) {   //대기시간
		double finalDt = Survival_WaitExpireTime - _dt;
		if (finalDt < 0.f) {
			finalDt = 0.f;
			Survival_UserStatus = W_DeathMatchInfo_eUserStatus::W_DeathMatchInfo_eUserStatus_eGame;
		}
		Survival_WaitExpireTime = finalDt;
	}

	if (Survival_GameableTime > 0.f) {   //등록이 끝나고 00분 후 게임이 시작한다는 걸 알려주며 상태를 세팅 6분 23초였음
		double finalDt = Survival_GameableTime - _dt;
		if (finalDt < 0.f) {
			finalDt = 0.f;
			Survival_UserStatus = W_DeathMatchInfo_eUserStatus::W_DeathMatchInfo_eUserStatus_eGame;
		}
		Survival_GameableTime = finalDt;
	}

	if (Survial_gameexpiretime > 0.f) {   //게임이 아예 끝나는 시간을 세팅함. -> 1시간 36분 -> 1시간 30 +6분23초
		double finalDt = Survial_gameexpiretime - _dt;
		if (finalDt < 0.f) {
			finalDt = 0.f;
			Survival_UserStatus = W_DeathMatchInfo_eUserStatus::W_DeathMatchInfo_eUserStatus_eEnd;
		}
		Survial_gameexpiretime = finalDt;
	}
}


// 서바이벌 입장 시간?
int64 GameDataManager::GetSuvivalGameEntertimeLeft()
{
	int64 _leftTime = m_selectedGameEnterTime - m_PastTime;

	if (_leftTime < 0)
		_leftTime = 0;

	return _leftTime;
}

int64 GameDataManager::GetSuvivalLefttime()
{
	int64 _leftTime = Survival_WaitExpireTime;

	if (_leftTime < 0)
		_leftTime = 0;

	return _leftTime;
}

void GameDataManager::SetSelectedLeftGameTime(double _second)
{
	m_selectedGameTime = _second;
}

void GameDataManager::SetSelectedGameEnterTime(double _second)
{
	m_selectedGameEnterTime = _second;
}

std::string GameDataManager::GetStringSuvivalLefttime()
{
	int64 _leftTime = GetSuvivalLefttime();
	if (_leftTime <= 0)
	{
		m_bSurvivalTimeUpdate = false;

	}
	else if (_leftTime <= 60)
	{
		string _leftTimeText = "[" + StringConverter::toString(_leftTime) + GameStringDepot::getSingletonPtr()->getString("TXT_SECOND") + "] ";
		_leftTimeText += GameStringDepot::getSingletonPtr()->getString("TXT_UNTIL_GAME_START_LABEL");
		return _leftTimeText;
	}
	else if (_leftTime <= 3600)
	{
		_leftTime = _leftTime / 60;
		string _leftTimeText = "[" + StringConverter::toString(_leftTime) + GameStringDepot::getSingletonPtr()->getString("TXT_MINUTE") + "] ";
		_leftTimeText += GameStringDepot::getSingletonPtr()->getString("TXT_UNTIL_GAME_START_LABEL");
		return _leftTimeText;
	}
	else if (_leftTime <= 3600 * 24)
	{
		int64 _hour = _leftTime / 3600;
		int64 _minute = (_leftTime - (3600 * _hour)) / 60;
		string _leftTimeText = "[" + StringConverter::toString(_hour) + GameStringDepot::getSingletonPtr()->getString("TXT_HOUR_LEFT");
		_leftTimeText += StringConverter::toString(_minute) + GameStringDepot::getSingletonPtr()->getString("TXT_MINUTE") + "] ";
		_leftTimeText += GameStringDepot::getSingletonPtr()->getString("TXT_UNTIL_GAME_START_LABEL");
		return _leftTimeText;
	}
	else
	{
		_leftTime = _leftTime / (3600 * 24);
		string _leftTimeText = "[" + StringConverter::toString(_leftTime) + GameStringDepot::getSingletonPtr()->getString("TXT_DAY") + "] ";
		_leftTimeText += GameStringDepot::getSingletonPtr()->getString("TXT_UNTIL_GAME_START_LABEL");
		return _leftTimeText;
	}

	return "";
}

bool GameDataManager::LoadFileImage(std::string _userId, std::string _url, DOWNLOAD_FILE_TYPE imgType, Widget * _image, bool isDownload, std::string _folderName, int _index)
{
	string savePath = SocialManager::getProfileImagePath(_url, _folderName);
	
	if (!CCFileUtils::sharedFileUtils()->isFileExist(savePath) && isDownload)
	{
		STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_REQ * commonProfileReq = new STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_REQ();
		commonProfileReq->userId = _userId;
		commonProfileReq->downloadUrl = _url;
		commonProfileReq->param = imgType;
		commonProfileReq->dParam = _index;

		CCUrlMgr::getSingletonPtr()->pushBack(commonProfileReq);
	}
	else
	{
		_image->setSpriteFrameWithFile(savePath);
		return true;
	}

	return false;
}

time_t GameDataManager::GetNowTime()
{
	time_t timer;
	//struct tm* t;
	timer = time(NULL); // 1970년 1월 1일 0시 0분 0초부터 시작하여 현재까지의 초
	//t = localtime(&timer); // 포맷팅을 위해 구조체에 넣기
	return timer;
}

int GameDataManager::getTicketCount(int _ticketId)
{
	if (m_TourOfInfo == NULL)
		return 0;

	int _size = m_TourOfInfo->ticketinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		W_TourTicketInfo _info = m_TourOfInfo->ticketinfo(_i);
		if (_info.id() == _ticketId)
		{
			int _tickcnt = _info.amount();
			return _tickcnt;
		}
	}

	return 0;
}

void GameDataManager::createImageFolder()
{
	CCFileUtils* _fileUtil = CCFileUtils::sharedFileUtils();
	string _tempDir = _fileUtil->getWritablePath();
	_tempDir += TEMP_PHOTO_FOLDER;
	string _staticDir = _fileUtil->getWritablePath();
	_staticDir += STATIC_PHOTO_FOLDER;
	// Create the folder if it doesn't exist
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	DIR *pDir = NULL;

	pDir = opendir(_tempDir.c_str());
	if (!pDir)
	{
		mkdir(_tempDir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	}

	pDir = NULL;

	pDir = opendir(_staticDir.c_str());
	if (!pDir)
	{
		mkdir(_staticDir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	}
#else
	if ((GetFileAttributesA(_tempDir.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(_tempDir.c_str(), 0);
	}

	if ((GetFileAttributesA(_staticDir.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(_staticDir.c_str(), 0);
	}
#endif
}

void GameDataManager::DeleteImageFolder()
{
	CCFileUtils* _fileUtil = CCFileUtils::sharedFileUtils();
	vector<string> searchPaths = _fileUtil->getSearchPaths();
	std::string _dir = _fileUtil->getWritablePath();
	_dir += TEMP_PHOTO_FOLDER;
	searchPaths.insert(searchPaths.begin(), _dir);
	_fileUtil->setSearchPaths(searchPaths);

	int _size = searchPaths.size();
	std::string _fileName = "";
	for (int _i = 0; _i < _size; _i++)
	{
		_fileName = _dir + "\\" + searchPaths[_i];
		remove(_fileName.c_str());
	}
}

void GameDataManager::DeleteStaticImage()
{
	CCFileUtils* _fileUtil = CCFileUtils::sharedFileUtils();
	vector<string> searchPaths = _fileUtil->getSearchPaths();
	std::string _dir = _fileUtil->getWritablePath();
	_dir += STATIC_PHOTO_FOLDER;
	searchPaths.insert(searchPaths.begin(), _dir);
	_fileUtil->setSearchPaths(searchPaths);

	int _size = searchPaths.size();
	std::string _fileName = "";
	for (int _i = 0; _i < _size; _i++)
	{
		_fileName = _dir + "\\" + searchPaths[_i];
		remove(_fileName.c_str());
	}
}

void GameDataManager::SetEdittextString(std::string _editText)
{
	m_eidtText = _editText;
	m_bEditTextField = true;
}

const W_CharacterData* GameDataManager::getCharacterData(int id)
{
	const RepeatedPtrField<W_CharacterData>& characterdatas = mGameData->characterdata();
	for (RepeatedPtrField<W_CharacterData>::const_iterator it = characterdatas.begin(); it != characterdatas.end(); ++it)
	{
		if ((*it).id() == id){
			return &(*it);
		}
	}

	return nullptr;
}

W_RecordSeasonInfo* GameDataManager::getRecordSeasonInfo()
{
	return mRecordSeasonInfo;
}

void GameDataManager::setRecordSeasonInfo(const W_RecordSeasonInfo& recordSeasonInfo)
{
	if (mRecordSeasonInfo == nullptr)
		mRecordSeasonInfo = new W_RecordSeasonInfo(recordSeasonInfo);
	else
		mRecordSeasonInfo->CopyFrom(recordSeasonInfo);
}

W_RecordDeathMatchInfo* GameDataManager::getRecordDeathMatchInfo()
{
	return mRecordDeathMatchInfo;
}

void GameDataManager::setRecordDeathMatchInfo(const W_RecordDeathMatchInfo& recordDeathMatchInfo)
{
	if (mRecordDeathMatchInfo == nullptr)
		mRecordDeathMatchInfo = new W_RecordDeathMatchInfo(recordDeathMatchInfo);
	else
		mRecordDeathMatchInfo->CopyFrom(recordDeathMatchInfo);
}

W_AttendSevenInfo* GameDataManager::getAttendSevenInfo()
{
	return mAttendSevenInfo;
}

void GameDataManager::setAttendSevenInfo(const W_AttendSevenInfo& attendSevenInfo)
{
	if (mAttendSevenInfo == nullptr)
		mAttendSevenInfo = new W_AttendSevenInfo(attendSevenInfo);
	else
		mAttendSevenInfo->CopyFrom(attendSevenInfo);
}

void GameDataManager::closeCustomView()
{
	if (m_WebViewPanel) {
		LayerManager::getSingleton().popLayer(m_WebViewPanel);
		m_WebViewPanel = nullptr;
	}
}

const W_PlayerInfo& GameDataManager::getPlayerInfo()
{
	return mUserInfo->playerinfo();
}

void GameDataManager::setPlayerInfo(const W_PlayerInfo& playerInfo)
{
	if (mUserInfo) {
		mUserInfo->mutable_playerinfo()->CopyFrom(playerInfo);
	}	

	int size = mUserInfo->payfirstinfo_size();	
	PlayerData* playerData = GetPlayerDataPtr();
	if (playerData)
		playerData->SetData(&playerInfo);
}

void GameDataManager::pokerResultMade(int madeResult)
{
	CCLOG("pokerResultMade madeResult = %d", madeResult);
	if ((madeResult > HighJokboKind::HIGH_NO && madeResult <= HighJokboKind::HIGH_FOUR_CARD) || (madeResult >= HighJokboKind::HIGH_BADUKI_GOLF && madeResult <= HighJokboKind::HIGH_BADUKI_THIRD)) {
		//잭팟 상품
		if (isActivateShopInfo(W_LimitShopData_eLimitType_l_jackpot)) {
			if (isActivateLimitedTime(W_LimitShopData_eLimitType_l_jackpot) == false) {
				mActivateJackpot = true;
			}
		}		
	}
	else  {
		//made 상품
		if (isActivateShopInfo(W_LimitShopData_eLimitType_l_made)) {
			if (isActivateLimitedTime(W_LimitShopData_eLimitType_l_made) == false) {
				mActivateMade = true;
			}
		}					
	}
}

void GameDataManager::setLimitShopInfo(const W_LimitShopInfo limitShopInfo)
{
	for (int i = 0; i < mUserInfo->limitshopinfo_size(); i++)
	{
		W_LimitShopInfo shopInfo = mUserInfo->limitshopinfo(i);
		if (shopInfo.limittype() == limitShopInfo.limittype()) {
			mUserInfo->mutable_limitshopinfo(i)->CopyFrom(limitShopInfo);
		}
	}
}

W_UserInfo* GameDataManager::getUserInfo()
{
	return mUserInfo;
}

void GameDataManager::setUserInfo(const W_UserInfo& userInfo)
{
	if (mUserInfo == nullptr)
		mUserInfo = new W_UserInfo(userInfo);
	else
		mUserInfo->CopyFrom(userInfo);

	if (mUserInfo->isnextday()) {
		//true 라면
		NotiDataManager::getSingleton().setNextDay();
		mUserInfo->set_isnextday(false);
	}

	CCLOG("setUserInfo notisize =%d", mUserInfo->notiinfo().info_size());
}

double GameDataManager::getJackPotLimitedTime()
{
	for (int i = 0; i < mUserInfo->limitshopinfo_size(); i++)
	{
		if (mUserInfo->limitshopinfo(i).limittype() == W_LimitShopData_eLimitType_l_jackpot) {
			return mUserInfo->limitshopinfo(i).lefttime();
		}
	}
	return 0.f;
}

double GameDataManager::getMadeLimitedTime()
{
	for (int i = 0; i < mUserInfo->limitshopinfo_size(); i++)
	{
		if (mUserInfo->limitshopinfo(i).limittype() == W_LimitShopData_eLimitType_l_made) {
			return mUserInfo->limitshopinfo(i).lefttime();
		}
	}

	return 0.f;
}

bool GameDataManager::isActivateLimitedTime(W_LimitShopData_eLimitType limitType)
{
	for (int i = 0; i < mUserInfo->limitshopinfo_size(); i++)
	{
		if (mUserInfo->limitshopinfo(i).limittype() == limitType) {
			return mUserInfo->limitshopinfo(i).isactive();
		}
	}

	return false;
}

void GameDataManager::updateLimitedShop(float dt)
{
	if (mUserInfo == nullptr)
		return;

	for (int i = 0; i < mUserInfo->limitshopinfo_size(); i++)
	{
		if (mUserInfo->limitshopinfo(i).lefttime() > 0.f) {
			double nowDt = mUserInfo->limitshopinfo(i).lefttime() - dt;
			if (nowDt < 0.f) {
				mUserInfo->mutable_limitshopinfo(i)->set_isactive(false);
				nowDt = 0.f;
			}
			mUserInfo->mutable_limitshopinfo(i)->set_lefttime(nowDt);
		}
	}
}

bool GameDataManager::isActivateLimitedBuffer(W_LimitShopData_eLimitType limitType)
{
	if (limitType == W_LimitShopData_eLimitType_l_jackpot)
		return mActivateJackpot;
	else if (limitType == W_LimitShopData_eLimitType_l_made)
		return mActivateMade;

	return false;
}

void GameDataManager::initLimitedBuffer()
{
	mActivateJackpot = false;
	mActivateMade = false;
}

void GameDataManager::setPayFirstInfo(int payInfo)
{
	int size = mUserInfo->payfirstinfo_size();
	bool isNotFind = true;
	for (int i = 0; i < size; i++)
	{
		if (mUserInfo->payfirstinfo(i) == payInfo) {
			isNotFind = false;
		}			
	}
	if (isNotFind) {
		mUserInfo->mutable_payfirstinfo()->Add(payInfo);
	}	
}

bool GameDataManager::isActivateShopInfo(W_LimitShopData_eLimitType limitType)
{
	for (int i = 0; i < mUserInfo->limitshopinfo_size(); i++)
	{
		W_LimitShopInfo shopInfo = mUserInfo->limitshopinfo(i);
		if (shopInfo.limittype() == limitType) {
			return shopInfo.iscontrol();
		}		
	}

	return false;
}

void GameDataManager::setNotiInfo(const W_NotiInfo& notiInfo)
{
	if (mUserInfo)
		mUserInfo->mutable_notiinfo()->CopyFrom(notiInfo);

	CCLOG("notisize = %d , =%d", notiInfo.info_size(), mUserInfo->notiinfo().info_size());
}

void GameDataManager::setFightSceneEnd()
{
	if (mFightSceneChange_PlayerOut) {
		mFightSceneChange_PlayerOut = false;

		GameDataManager::getSingletonPtr()->ClearUiState();
		SoundManager::getSingletonPtr()->stopEffects();
		if (m_GameMode == MODE_NORMAL) {
			CSJson::Value params;
			params["LOBBY_UI_CHANNELLIST"] = true;
			SceneUtil::changeScene(SceneUtil::SceneLobby, params);
		}
		else if (m_GameMode == MODE_NORMAL_TOURNAMENT) {
			CSJson::Value params;
			params["LOBBY_UI_TOURNAMENT_SELECT"] = true;
			SceneUtil::changeScene(SceneUtil::SceneLobby, params);
		}
		else if (m_GameMode == MODE_SURVIVAL_TOURNAMENT) {
			CSJson::Value params;
			params["LOBBY_UI_SURVIVAL_SELECT"] = true;
			SceneUtil::changeScene(SceneUtil::SceneLobby, params);
		}
	}
}

W_AttendSevenData GameDataManager::getAttendSevenData(int idx)
{
	W_AttendSevenInfo* senvenInfo = getAttendSevenInfo();
	if (senvenInfo->isfinishfirstattend())
		return mGameData->attendsevendata(idx);
	else
		return mGameData->attendsevenfirstdata(idx);
}

const W_SkinData* GameDataManager::getSkinData(int id)
{
	const RepeatedPtrField<W_SkinData>& skinDatas = mGameData->skindata();
	for (RepeatedPtrField<W_SkinData>::const_iterator it = skinDatas.begin(); it != skinDatas.end(); ++it)
	{
		if ((*it).id() == id){
			return &(*it);
		}
	}

	return nullptr;
}

void GameDataManager::setGameKind(int kind)
{
	if (kind == -1)
		m_SelectedGameKind = GAMEKIND_7POKER;
	else
		m_SelectedGameKind = kind;
}

bool GameDataManager::isLaterThanCurrent(tm Current, tm Target)
{
	if (Current.tm_year == Target.tm_year) {
		if (Current.tm_mon == Target.tm_mon) {
			if (Current.tm_mday == Target.tm_mday) {
				if (Current.tm_hour == Target.tm_hour) {
					if (Current.tm_min == Target.tm_min) {
						return false;
					}
					else {
						return Current.tm_min < Target.tm_min;
					}
				}
				else {
					return Current.tm_hour < Target.tm_hour;
				}
			}
			else {
				return Current.tm_mday < Target.tm_mday;
			}
		}
		else {
			return Current.tm_mon < Target.tm_mon;
		}
	}
	else {
		return Current.tm_year < Target.tm_year;
	}
}

bool GameDataManager::CanDisplay(string StartDt, string EndDt)
{
	time_t CURRENT = time(NULL), START, END;
	bool isLaterThanStart = false;
	bool isEarlerThanEnd = false;
	struct tm start;
	struct tm end;
	struct tm* current = localtime(&CURRENT);
	
	start = StringToTime(StartDt);
	isLaterThanStart = !isLaterThanCurrent(*current, start);

	end = StringToTime(EndDt); 
	isEarlerThanEnd = isLaterThanCurrent(*current, end);
	
	return isLaterThanStart && isEarlerThanEnd;
}

string GameDataManager::GetGAID()
{
	if (GAID != "")
		return GAID;
	else {
		GAID = getUUID();
		return GAID;
	}
}

tm GameDataManager::StringToTime(string timeStr)
{
	if(timeStr == "")
		return tm();

	struct tm time;

	//string format from server ===>  "0000-00-00 00:00"
	time.tm_year = boost::lexical_cast<int>(timeStr.substr(0, 4)) - 1900; //year
	time.tm_mon = boost::lexical_cast<int>(timeStr.substr(5, 2)) - 1; //month
	time.tm_mday = boost::lexical_cast<int>(timeStr.substr(8, 2)); //day
	time.tm_hour = boost::lexical_cast<int>(timeStr.substr(11, 2)); //Hour
	time.tm_min = boost::lexical_cast<int>(timeStr.substr(14, 2)); //minute
	time.tm_sec = 0;
	time.tm_isdst = 0;
	time.tm_wday = 0;
	time.tm_yday = 0;
	
	return time;
}

void GameDataManager::setModel() //init Player Model Data
{
	int model_sublist = DEFAULT_MODEL_SUBLIST_UNIT;
	int index_head = DEFAULT_MODEL_INDEX_HEAD_NUMBER;
	int index_middle = DEFAULT_MODEL_INDEX_MIDDLE_NUMBER;
	
	int currenttIdx;
	if (mGameData->modeldata_size() == 0)
		return;

	W_ModelData begin = mGameData->modeldata(0);

	if (mGameData->modeldata().size() == 0)
		currenttIdx = -1;
	else
		currenttIdx = (begin.id() % index_head) / index_middle; //이 모델이 몇번째로 추가된 모델인지
	
	if (currenttIdx < 0)
		return;

	std::vector<W_ModelData> temp;
	for (int i = 0; i < mGameData->modeldata().size(); i++)
	{
		int tIdx = (mGameData->modeldata(i).id() % index_head) / index_middle;
		W_ModelData MD = mGameData->modeldata(i); //MD => ModelData


		if (currenttIdx == tIdx)
			temp.push_back(MD);
		else {
			m_ModelShopList_MAXIM.push_back(temp);
			temp.clear();
			currenttIdx = tIdx;
			temp.push_back(MD);
		}

		if (i == mGameData->modeldata().size() - 1)
		{
			if (temp.size() > 0)
				m_ModelShopList_MAXIM.push_back(temp);

			temp.clear();
		}
	}
	int testsize = mGameData->invenmodeldata_size();
	ModelInvenTableData.clear();
	for (int i = 0; i < mGameData->invenmodeldata_size(); i++)
	{
		ModelInvenTableData.push_back(mGameData->invenmodeldata(i));
	}
	
	for (int i = 0; i < mGameData->displaymodeldata().size(); i++)
	{
		TitleModel_MAXIM.push_back(mGameData->displaymodeldata(i));
	}

	mSlotEXNeedGold = mGameData->startassets().model_inventory_up();
	mTapEXNeedGold = mGameData->startassets().model_tap_up();
	mMaxSlotIndex = mGameData->startassets().model_max_inventory();
	
	{
		//W_DisplayModelData tmp1; tmp1.set_id(20001); tmp1.set_name(StringConverter::toString(L"김세라")); tmp1.set_filename("Racing_01_001.jpg"); tmp1.set_startdt("2000-01-01 00:00"); tmp1.set_enddt("2099-01-01 00:00");
		//TitleModel_RACING.push_back(tmp1);

		//W_DisplayModelData tmp2; tmp2.set_id(20101); tmp2.set_name(StringConverter::toString(L"윤지")); tmp2.set_filename("Racing_02_001.jpg"); tmp2.set_startdt("2070-01-01 00:00"); tmp2.set_enddt("2099-01-01 00:00");
		//TitleModel_RACING.push_back(tmp2);

		//W_DisplayModelData tmp3; tmp3.set_id(20101); tmp3.set_name(StringConverter::toString(L"이제니")); tmp3.set_filename("Racing_03_001.jpg"); tmp3.set_startdt("2070-01-01 00:00"); tmp3.set_enddt("2099-01-01 00:00");
		//TitleModel_RACING.push_back(tmp3);
	}
	/*std::vector<int> tmp;
	BuyList_RACING.push_back(tmp);*/

	{
		/*std::vector<W_ModelData> temp;

		W_ModelData tmp1; tmp1.set_id(20001); tmp1.set_name(StringConverter::toString(L"김세라1")); tmp1.set_filename("Racing_01_001.jpg"); tmp1.set_startdt("2000-01-01 00:00"); tmp1.set_gold(500000000000); tmp1.set_gnumber(1); tmp1.set_enddt("2099-01-01 00:00");
		temp.push_back(tmp1); 

		W_ModelData tmp2; tmp2.set_id(20002); tmp2.set_name(StringConverter::toString(L"김세라2")); tmp2.set_filename("Racing_01_002.jpg"); tmp2.set_startdt("2000-01-01 00:00"); tmp2.set_gold(500000000000); tmp2.set_gnumber(1); tmp2.set_enddt("2099-01-01 00:00");
		temp.push_back(tmp2);

		W_ModelData tmp3; tmp3.set_id(20003); tmp3.set_name(StringConverter::toString(L"김세라3")); tmp3.set_filename("Racing_01_003.jpg"); tmp3.set_startdt("2000-01-01 00:00"); tmp3.set_gold(500000000000); tmp3.set_gnumber(1); tmp3.set_enddt("2099-01-01 00:00");
		temp.push_back(tmp3);

		W_ModelData tmp4; tmp4.set_id(20004); tmp4.set_name(StringConverter::toString(L"김세라4")); tmp4.set_filename("Racing_01_004.jpg"); tmp4.set_startdt("2000-01-01 00:00"); tmp4.set_gold(500000000000); tmp4.set_gnumber(1); tmp4.set_enddt("2099-01-01 00:00");
		temp.push_back(tmp4);

		W_ModelData tmp5; tmp5.set_id(20005); tmp5.set_name(StringConverter::toString(L"김세라5")); tmp5.set_filename("Racing_01_005.jpg"); tmp5.set_startdt("2000-01-01 00:00"); tmp5.set_gold(500000000000); tmp5.set_gnumber(1); tmp5.set_enddt("2099-01-01 00:00");
		temp.push_back(tmp5);

		W_ModelData tmp6; tmp6.set_id(20006); tmp6.set_name(StringConverter::toString(L"김세라6")); tmp6.set_filename("Racing_01_006.jpg"); tmp6.set_startdt("2000-01-01 00:00"); tmp6.set_gold(500000000000); tmp6.set_gnumber(1); tmp6.set_enddt("2099-01-01 00:00");
		temp.push_back(tmp6);

		W_ModelData tmp7; tmp7.set_id(20007); tmp7.set_name(StringConverter::toString(L"김세라7")); tmp7.set_filename("Racing_01_007.jpg"); tmp7.set_startdt("2000-01-01 00:00"); tmp7.set_gold(500000000000); tmp7.set_gnumber(1); tmp7.set_enddt("2099-01-01 00:00");
		temp.push_back(tmp7);

		W_ModelData tmp8; tmp8.set_id(20008); tmp8.set_name(StringConverter::toString(L"김세라8")); tmp8.set_filename("Racing_01_008.jpg"); tmp8.set_startdt("2000-01-01 00:00"); tmp8.set_gold(500000000000); tmp8.set_gnumber(1); tmp8.set_enddt("2099-01-01 00:00");
		temp.push_back(tmp8);

		W_ModelData tmp9; tmp9.set_id(20009); tmp9.set_name(StringConverter::toString(L"김세라9")); tmp9.set_filename("Racing_01_009.jpg"); tmp9.set_startdt("2000-01-01 00:00"); tmp9.set_gold(500000000000); tmp9.set_gnumber(1); tmp9.set_enddt("2099-01-01 00:00");
		temp.push_back(tmp9);

		W_ModelData tmp10; tmp10.set_id(20010); tmp10.set_name(StringConverter::toString(L"김세라10")); tmp10.set_filename("Racing_01_010.jpg"); tmp10.set_startdt("2000-01-01 00:00"); tmp10.set_gold(500000000000); tmp10.set_gnumber(1); tmp10.set_enddt("2099-01-01 00:00");
		temp.push_back(tmp10);

		m_ModelShopList_RACING.push_back(temp);*/
	}
	
}

bool GameDataManager::hasModel(int tIdx, int subidx, TAB_TYPE tapType)
{
	ModelShopList shop_list;
	std::vector<std::vector<int>> buylist;
	if (tapType == MAXIM_TAB) {
		shop_list = m_ModelShopList_MAXIM;
		buylist = BuyList_MAXIM;
	}
	else {
		shop_list = m_ModelShopList_RACING;
		buylist = BuyList_RACING;
	}

	if (subidx<0 || subidx>shop_list[tIdx].size() || tIdx<0 || tIdx > shop_list.size() || buylist.size() == 0)return false;
	for (int i = 0; i < buylist[tIdx].size(); i++)
	{
		if (buylist[tIdx][i] == FindShopModel(tIdx, subidx, tapType).id())return true;
	}
	return false;
	
}

W_DisplayModelData GameDataManager::FindTitleModel(int idx, TAB_TYPE tapType)
{
	if(idx < 0 )return W_DisplayModelData();

	switch (tapType)
	{
	case MAXIM_TAB:
		if (TitleModel_MAXIM[idx].id() != 0)
			return TitleModel_MAXIM[idx];
		break;
	case RACING_TAB:
		if (TitleModel_RACING[idx].id() != 0)
			return TitleModel_RACING[idx];
		break;
	default:
		break;
	}
	
	return W_DisplayModelData();


}

W_ModelData GameDataManager::FindShopModel(int modelId, TAB_TYPE tapType)
{
	int tapIdx = getModelInfo(modelId, TAP_ID);
	int subIdx = getModelInfo(modelId, MODEL_INDEX);

	return FindShopModel(tapIdx, subIdx, tapType);
}

W_ModelData GameDataManager::FindShopModel(int tid, int subIdx, TAB_TYPE tapType)
{
	ModelShopList temp;

	if (tapType == MAXIM_TAB)
		temp = m_ModelShopList_MAXIM;
	else
		temp = m_ModelShopList_RACING;
	int d = temp[tid].size();
	if (tid < temp.size())
	{
		if (subIdx < temp[tid].size())
		{
			return temp[tid][subIdx];
		}
	}
	return W_ModelData();
}

std::vector<std::vector<int>> GameDataManager::getModelList(TAB_TYPE tabtype)
{
	if (tabtype == TAB_TYPE::MAXIM_TAB)
		return BuyList_MAXIM;
	else if (tabtype == TAB_TYPE::RACING_TAB)
		return BuyList_RACING;
}

bool GameDataManager::hasSlot(int tapIdx, int idx, TAB_TYPE tapType)
{
	std::vector<std::vector<int>> temp_buylist;
	std::vector<W_ModelTabInfo*> temp_tapinfo;

	if (tapType == MAXIM_TAB) {
		temp_buylist = BuyList_MAXIM;
		temp_tapinfo = InvenTapInfo_MAXIM;
	}
	else {
		temp_buylist = BuyList_RACING;
		temp_tapinfo = InvenTapInfo_RACING;
	}

	if (0 <= idx && idx <= 2)	// 첫 슬롯은 구매가 된 상태로 표시
	{
		return true;
	} 
	else if (idx == -1)
	{
        uint modelUnit = temp_buylist[tapIdx].size();
        uint slotUnit = temp_tapinfo[tapIdx]->tabinventorycount();
		return modelUnit < slotUnit;
	}
	else
		return idx > 0 && temp_tapinfo[tapIdx]->tabinventorycount() > idx; //

}

bool GameDataManager::hasTap(int idx, TAB_TYPE tapType)
{
	std::vector<W_ModelTabInfo*> temp;

	if (tapType == MAXIM_TAB) {
		temp = InvenTapInfo_MAXIM;
	}
	else {
		temp = InvenTapInfo_RACING;
	}

	for (int _i = 0; _i < temp.size(); _i++)
	{
		if (idx == temp[_i]->tabid())
			return true;
	}

	return false;
	
}

int GameDataManager::getModelInfo(int id , ModelInfo val)
{
	int default_model_index_head_number = DEFAULT_MODEL_INDEX_HEAD_NUMBER;
	int default_model_index_middle_number = DEFAULT_MODEL_INDEX_MIDDLE_NUMBER;

	switch (val)
	{
	case TAP_ID:
		return (id % default_model_index_head_number) / default_model_index_middle_number + 1;
		break;
	case TAP_INDEX:
		return (id % default_model_index_head_number) / default_model_index_middle_number;
		break;
	case MODEL_INDEX:
		if (id < default_model_index_head_number)
			return id;
		else
			return (id % default_model_index_head_number) % default_model_index_middle_number - 1;
		break;
	default:
		return -1;
		break;
	}
	
}
