#include "pch.h"
#include "GameRoomInfo.h"
#include "GameDataManager.h"
#include "EnterRoomSuccess.pb.h"
#include "TypeDefine.pb.h"
#include "socket/TCPService.h"
#include "PlayerInRes.pb.h"
#include "RoomPlayerInfo.pb.h"
#include "PlayerPoInfo.pb.h"
#include "PlayerOutRes.pb.h"
#include "BettingSeedRes.pb.h"
#include "ShareCardInfo.pb.h"
#include "BettingState.pb.h"
#include "CurBettingInfo.pb.h"
#include "BettingRes.pb.h"

#include "PokerBackgroundPanel.h"
#include "PokerPlayerInfoPanel.h"
#include "BettingCardOnOffPanel.h"
#include "BettingSevenPokerPanel.h"
#include "ResultInfo.pb.h"
#include "PokerResultPanel.h"
#include "ChoiceHighLowInfo.pb.h"
#include "HighLowUserInfo.pb.h"
#include "PlayerOutReserveRes.pb.h"

#include "UserJokboInfo.h"

#include "PokerChipWidget.h"
#include "PotMoneyPanel.h"
#include "JokboList.h"
#include "PokerTopPanel.h"
#include "RoomGameStatus.pb.h"
#include "UpdatePlayerInfo.pb.h"
#include "GamePlaySeqRes.pb.h"
#include "PlayerAdditionalResultInfo.pb.h"
#include "JackpotPanel.h"
#include "BettingMoneyReApply.pb.h"
#include "NxSkelObject.h"
#include "SceneUtil.h"
#include "FightScene.h"
#include "GameSavePlayDataRes.pb.h"
#include "GameStringDepot.h"
#include "SimplePopupPanel.h"
#include "EmoticonRoomRes.pb.h"
#include "GamePlayStatcsInfoRes.pb.h"
#include "PlayerPlayStatcsInfoRes.pb.h"
#include "ChangeCardInfo.pb.h"
#include "PlayersStatus.pb.h"
#include "ChangeSeedMoney.pb.h"
#include "CommonError.pb.h"
#include "BettingBlindRes.pb.h"
#include "ShowDownUserInfo.pb.h"
#include "ShareCardInfoList.pb.h"
#include "NotiDataManager.h"
#include "PanelHelper.h"
#include "PokerResourceHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/AdmobManager.h"
#endif

#define SHOW_ANI_TIME 0.2f;	//기존 0.1f


#define SHOW_HIDDEN_CARD_LIGHT_EFFECT 1.4f

GameRoomInfo::GameRoomInfo()
{
	for (int i = 0; i < GAME_USER_MAX; i++)
		m_UserList[i] = nullptr;

	mMadeJokbo = -1;
	m_bBigGameAction = false;
	m_IsHiddenCheck = false;
	m_pDealerTextBubble = nullptr;
	m_pStayPopup = nullptr;

	/*
	* 게등위 심의 위반, 보너스 칩 지급 제한
	PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
	mChipCount = GameDataManager::getSingleton().getPlayerInfo().chipplaycnt();
	string chipStr = "play" + StringConverter::toString(mChipCount);
	if (backGroundPanel->mPokerChip->hasAnimation(chipStr))
		backGroundPanel->mPokerChip->playAnimation(chipStr);*/

	InitData();
	SetStatus(PlayStatus::PLAY_NO);
}

GameRoomInfo::~GameRoomInfo()
{
	//if (m_pDealer)
	//{
		//m_pDealer->cleanup();
		//m_pDealer->subEventListener(this);
		//m_pDealer->removeFromParent();
		//m_pDealer = nullptr;
	//}

	for (int i = 0; i < GAME_USER_MAX; i++)
	{
		if (m_UserList[i] == nullptr)
			continue;

		NX_SAFE_DELETE(m_UserList[i]);
		m_UserList[i] = nullptr;
	}

	ReleaseCommunityCard();
}
void GameRoomInfo::InitData()
{
	m_isBigCommunityCard = false;
	m_bCommunityCardProcessing = false;
	m_fProcessTime = 0.f;

	m_UpdateTime = 0.f;
	m_GameTime = 0;
	m_ExitReserve = false;
	m_pLabelWinnerMoney = nullptr;
	m_bWinnerMonnyEffectUpdate = false;
	m_pDealer = nullptr;
	m_pDealerUnder = nullptr;
	m_pDealerTextBubble = nullptr;

	m_badugiSortedCard = false;
	m_badugiSortDelay = 0.f;

	m_myMadeCheck = false;
	//m_IsGetChip = false;
	m_IsLevelUp = false;
	m_RefillMoney = 0;
	m_IsCompleteQuest = false;

	m_madeMoney = 0;

	m_isInitGame = false;

	m_isReplayData = false;
	/*for (int _i = 0; _i < GAME_USER_MAX; _i++)
	{
		m_pWinnerText[_i] = nullptr;
	}*/

	m_fSoundDelayTime = 0.f;
	m_soundType = -1;

	m_bShowDown = false;

	m_bSendWait = false;
	m_bSendChanageRequest = false;
	m_bSendPassRequest = false;
	m_dayState = DAY_TYPE_END;
	m_SelectedNumber[0] = false;
	m_SelectedNumber[1] = false;
	m_SelectedNumber[2] = false;
	m_SelectedNumber[3] = false;

	if (GameDataManager::getSingletonPtr()->getGameKind() == GAMEKIND_HOLDEM)
		InitCommunityCard();
	else
		m_CommunityCardBackBoard = nullptr;

	//serverinfo 가 프렌즈일때 말창 보이게



}

void GameRoomInfo::GameStartCheck()
{
	if (GetGameMode() == GameMode::MODE_SURVIVAL_TOURNAMENT || GetGameMode() == GameMode::MODE_NORMAL_TOURNAMENT)
		return;
	//TODO : 플레이어가 방장이면서 게임이 대기 상태인 경우 시작 버튼을 활성화 한다.
	if (m_MyPo == m_MasterPo && m_PlayStatus == PlayStatus::PLAY_NO)
	{
		PokerTopPanel* _pTopLayer = GetTopPanel();
		if (_pTopLayer == nullptr)
			return;

		_pTopLayer->GameStart();
	}
}

void GameRoomInfo::ShowStartButton()
{
	if (GetGameMode() == GameMode::MODE_SURVIVAL_TOURNAMENT || GetGameMode() == GameMode::MODE_NORMAL_TOURNAMENT)
		return;
	//TODO : 플레이어가 방장이면서 게임이 대기 상태인 경우 시작 버튼을 활성화 한다.
	if (m_MyPo == m_MasterPo && m_PlayStatus == PlayStatus::PLAY_NO)
	{
		PokerTopPanel* _pTopLayer = GetTopPanel();
		if (_pTopLayer == nullptr)
			return;

		if (_pTopLayer->GetStartButton()->isVisible() == true)
			return;

		_pTopLayer->SetTurnOnGameStartButton();
		//_pTopLayer->SetTurnOnLight();

		//백판 안 보이게 한다.
		PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
		if (backGroundPanel) {
			backGroundPanel->setVibieCallBoard(false);
		}
	}
}

void GameRoomInfo::HideStartButton()
{
	PokerTopPanel* _pTopLayer = GetTopPanel();
	if (_pTopLayer == nullptr)
		return;

	_pTopLayer->SetTurnOffGameStartButton();
	//백판 안 보이게 한다.
	PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
	if (backGroundPanel) {
		backGroundPanel->setVibieCallBoard(true);
	}
}

void GameRoomInfo::MakeJokboInfoAndOtherInfo()
{
	PokerPlayerInfoPanel * infoPanel = GetPlayerInfoPanel();
	if (infoPanel == nullptr)
		return;

	PokerPlayerInfoCommonPanel * panel = nullptr;
	for (int i = 0; i < GAME_USER_MAX; i++)
	{
		
		panel = infoPanel->GetPlayerCommonPanelWithIndex(i);
		if (panel != nullptr)
		{
			panel->InitJokboInfo();
			panel->InitWinnerText();
			panel->InitAllBetImage();
			panel->InitWaitImage();
		}
	}
}

void GameRoomInfo::MakeMade()
{
	PokerPlayerInfoPanel * infoPanel = GetPlayerInfoPanel();
	if (infoPanel == nullptr)
		return;

	PokerPlayerInfoCommonPanel * panel = nullptr;
	panel = infoPanel->GetPlayerCommonPanelWithIndex(0);
	if (panel != nullptr)
		panel->InitMadeImage();
}

void GameRoomInfo::UpdateDealer(float dt)
{
	if (m_isBettingCount == true)
	{
		if (m_DealerTime > 6.f)
		{
			DealerAnimation(DEALER_HURRY);
		}
	}
	if (m_DealerTime > 25.f)
	{
		if (m_pDealer->getCurrentAnimation() == "idle")
		{
			int _act = rand() % 2;
			if (_act == 0)
				DealerAnimation(DealerAniKind::DEALER_ACT1);
			else if (_act == 1)
				DealerAnimation(DealerAniKind::DEALER_ACT2);
		}
			
	}

	if (m_soundType > -1)
	{
		if (m_fSoundDelayTime < 0.f)
		{
			DealerSound((DealerEfxKind)m_soundType);
			m_soundType = -1;
			m_fSoundDelayTime = 0.f;
		}
		m_fSoundDelayTime -= dt;
	}
}

void GameRoomInfo::UpdateWinnerTextEffect(float dt)
{
	if (m_bWinnerMonnyEffectUpdate == true)
	{
		if (m_fWinnerMoneyEfxTime <= 0.f)
		{
			m_bWinnerMonnyEffectUpdate = false;
			m_fWinnerMoneyEfxTime = 0.f;

			m_pLabelWinnerMoney->setString(m_WinnerMoneyStr.c_str());
			m_pLabelWinnerMoney->runAction(CCSequence::create(
				CCScaleTo::create(0.1f, 1.2f),
				CCScaleTo::create(0.1f, 1.f),
				NULL));
		}
		else
		{
			int64 _money = 0;
			if (WIN_TEXT_EFFFECT_TIME - m_fWinnerMoneyEfxTime != 0)
			{
				_money = m_EffectMoney * ((WIN_TEXT_EFFFECT_TIME - m_fWinnerMoneyEfxTime) / WIN_TEXT_EFFFECT_TIME);
			}
			m_pLabelWinnerMoney->setString(PokerResourceHelper::getImgFontForGameMoney(_money).c_str());
			m_fWinnerMoneyEfxTime -= dt;
		}
	}

}

void GameRoomInfo::UpdatePotMoneyEffect(float dt)
{
	if (m_PotMoneyEffectState == PotMoneyState::POT_UPDATE)
	{
		PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
		if (m_fPotMoneyEffectTime <= m_fPotMoneyUpdateTime)
		{
			//if (m_PotMoneyUpdateList.size() != 0  && m_PreMoneyUpdateList.size() != 0)

			m_PotMoneyEffectState = PotMoneyState::POT_END;
			if (backGroundPanel) {
				backGroundPanel->setTotalBettingMoney(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(m_UpdatePotMoney + m_PrePotMoney), 2));
			}
			return;
		}
		
		float _timeWeight = m_fPotMoneyUpdateTime / m_fPotMoneyEffectTime;
		int64 _money = m_UpdatePotMoney * _timeWeight;

		if (backGroundPanel) {
			backGroundPanel->setTotalBettingMoney(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_money + m_PrePotMoney), 2));
		}
		m_fPotMoneyUpdateTime += dt;
	}
}

void GameRoomInfo::Update(float dt)
{
	m_Dtime = dt;
	m_UpdateTime += dt;
	m_DealerTime += dt;
	if (m_UpdateTime >= 1.f)
	{
		int _nAddTime = m_UpdateTime / 1;
		m_GameTime += _nAddTime;
		m_UpdateTime = m_UpdateTime - (float)_nAddTime;

		if (GameDataManager::getSingletonPtr()->m_bSurvivalTimeUpdate == true && m_GameMode == GameMode::MODE_SURVIVAL_TOURNAMENT)
		{
			UpdateStayTime(GameDataManager::getSingletonPtr()->GetStringSuvivalLefttime());
		}
	}

	UpdateDealer(dt);
	UpdateWinnerTextEffect(dt);
	UpdatePotMoneyEffect(dt);
	UpdateMyMadeCheck(dt);
	UpdateBadugiSortCheck(dt);
	UpdateComminityProcess(dt);
	

	switch (m_PlayStatus)
	{
	case PLAY_NO:
	case PLAY_READY:
	case PLAY_BETTING_SEED_INIT:
	case PLAY_SHARE_CARD:
	case PLAY_SHARE_CARD_WAIT:
		break;
	case PLAY_CARD_CHOICE:
	{
		BettingCardOnOffPanel* _pBettingPanel = dynamic_cast<BettingCardOnOffPanel*>(LayerManager::getSingleton().getLayer("CardOnOffPanel"));
		if (_pBettingPanel == nullptr)
			break;

		if (_pBettingPanel->isVisible())
		{
			_pBettingPanel->update(dt);
		}
	}	
		break;
	case PLAY_BETTING_WAIT:
		break;
	case PLAY_BETTING:
	{
		if (m_BetPo == -1)
			break;

		PokerPlayerInfoPanel* _pPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("PlayerInfo"));
		PokerPlayerInfoCommonPanel* _pPlayerPanel = dynamic_cast<PokerPlayerInfoCommonPanel*>(_pPanel->GetPlayerPanel(m_BetPo));
		
		if (_pPlayerPanel != nullptr)
			_pPlayerPanel->update(dt);
		break;
	}
	case PLAY_JOKBO_CHOICE:
	case PLAY_RESULT_CHECK:
	case PLAY_RESULT_PAE_SHOW:
	case PLAY_NEXT_READY:
	case PLAY_SHARE_COMMUNITY_CARD:
		break;
	case PLAY_RESULT:
		ExeAfterResultUserInfoUI();
		break;
	case PLAY_CHANGE_CARD:
		break;
	default:
		break;
	}

	//유저들 update
	for (int _i=0; _i < GAME_USER_MAX; _i++)
	{
		if (m_UserList[_i] == nullptr)
			continue;

		m_UserList[_i]->Update(dt);
	}

	// 자신이 다이한 유저일 때, 포커칩회득, 레벨업 애니메이션 
	ExeAfterResultUserInfoUI();

	//TODO : make Rule.

	//Game is ready? (y/n) (start/wait)
	//card select. (number)
	//Who is boss? (number)
	//Draw Card						//Draw Card
	//Who is boss? ( 2/4card )		//Who is boss? ( 3/5card )
	//betting (1bet)				//betting (1bet)
	//Draw Card						//Draw Card
	//Who is boss? ( 3/5card )		//Who is boss? ( 4/6card )
	//betting (2bet)				//betting (2bet)
	//Draw Card						//Draw secret card	
	//Who is boss? ( 4/6card )		//Who is boss? ( 4/6card )
	//betting (2bet)				//betting (2bet)
	//Draw secret card				//Who is winner? ( 7card )
	//Who is boss? ( 4/6card )		//Give the money.
	//betting (2bet)				//Init Game.
	//Who is winner? ( 7card )
	//Give the money.
	//Init Game.

	
}

bool GameRoomInfo::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	if (_msg == NULL)
	{
		return false;
	}

	if (!IsGameLoaded())
		return false;

	//TODO : _msg 처리

	switch (type)
	{
		case S2C_PLAYER_IN_IDX:
			PlayerInProcess((char*)_msg, parm1);
			break;
		case S2C_PREPARE_END_IDX :
			SetPrepareEnd((char*)_msg, parm1);
			break;
		case S2C_CHANGE_MANAGER_IDX:
			ChangeManager((char*)_msg, parm1);
			break;
		case S2C_START_GAME_IDX:
		{
			SetStatus(PlayStatus::PLAY_READY);
			//SetVisibleLight(false);
			PokerTopPanel* _pTopLayer = GetTopPanel();
			if (_pTopLayer != nullptr)
			{
				if (m_MasterPo == GetUserDataPtr()->m_Po)
					_pTopLayer->SetTurnOffGameStartButton();

				//백판 안 보이게 한다.
				PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
				if (backGroundPanel) {
					backGroundPanel->setVibieCallBoard(true);
				}

				if (GameDataManager::getSingletonPtr()->m_GameMode != GameMode::MODE_NORMAL)
					_pTopLayer->TopButtonesEnable(false);
			}

			int _kind = EFX_DEALER_GAMESTART1 + (rand() % 3);
			DealerSound((DealerEfxKind)_kind);

			if (m_pStayPopup)
			{
				m_pStayPopup->closePanel(true);
				m_pStayPopup = nullptr;
			}

			mMadeJokbo = -1;
			//게임 시작
			//result에 madeResult false 로 init 한다.
			PokerResultPanel * panel = GetPokerResultPanel();
			if (panel)
			{
				panel->setMadeResult(mMadeJokbo);
			}

			PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
			backGroundPanel->mLimitedIcon->setVisible(false);			

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			//AdmobManager::getSingleton().showAdMob();
#endif
			break;
		}
		case S2C_END_GAME_IDX:
		{
			//게임이 종료되어 초기화, 최대 유저수 이하일 경우 시작 버튼 보임.
			InitGame();
			int canPlayCnt = GetCanPlayerCnt();
			if (canPlayCnt > 1 && canPlayCnt < 5)
			{
				ShowStartButton();
			}
			//if (canPlayCnt < 5)
			//	SetVisibleLight(true);
			break;
		}
		//NZ창헌 
		//룸재배치
		case S2C_ROOM_REARRANGE_IDX:
		{
			SetRoomRearrange();
			break;
		}
		case S2C_ROOM_REARRANGE_COMPLETE_IDX:
		{
			RearrangeComplete((char*)_msg, parm1);			
			break;
		}
		case S2C_MOVE_ROOM_SUCCESS_IDX:
		{
			TCPService::getSingletonPtr()->InitHandShakeProtocol();
			MoveRoom((char*)_msg, parm1);
			PanelHelper::popLoadingPanel(1.0f);

			PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
			backGroundPanel->refreshRoomNo();

			//string msgText = GameStringDepot::getSingletonPtr()->getString("TXT_CHANNEL_NOTICE_MAX_MONEY");
			//SimplePopupPanel* _toastpanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ToastNotice, msgText);

			//if (_toastpanel)
			//	LayerManager::getSingleton().pushDynamicLayer(_toastpanel, DYNAMIC_PUSH_LAYER);
			break;
		}
		case S2C_BETTING_SEED_RES_IDX:
		{
			if (m_isInitGame == false)
			{
				InitGame();
			}

			m_isInitGame = false;
			SetBettingSeedMoney((char*)_msg, parm1);
			break;
		}
		case S2C_BETTING_BLIND_RES_IDX:
			SetBettingBlindMoney((char*)_msg, parm1);
			break;
		case S2C_BETTING_BACK_RES_IDX :
			SetBettingBackMoney((char*)_msg, parm1);
			break;
		case S2C_SEND_CARD_IDX :
			CCLOG("S2C_SEND_CARD_IDX S2C_SEND_CARD_IDX S2C_SEND_CARD_IDXS2C_SEND_CARD_IDX");

			m_DealerShoot = false;
			if (GetGameKind() == GAMEKIND_BADUKI || m_GameKind == GameKind::GAMEKIND_HOLDEM)
			{
				BadugiShareCard((char*)_msg, parm1);
			}
			else
			{
				AddCard((char*)_msg, parm1);
			}

			//내 캐릭터 사라지게...

			break;
		case S2C_SHARE_CARD_END_REQ_IDX :
			SetStatus(PlayStatus::PLAY_SHARE_CARD_WAIT);
			break;
		case S2C_CARD_CHOICE_STATE_IDX :
			SetCardChoice();
			break;
		case S2C_CARD_CHOICE_RES_IDX :
			ChangeCards((char*)_msg, parm1);
			break;
		case S2C_BETTING_STATE_IDX:
			if (m_DealerShoot == true)
			{
				m_DealerShoot = false;
				//m_pDealer->appendAnimation("dealing_ready");
				m_pDealer->appendAnimation("idle", true);
			}
			SetBettingState((char*)_msg, parm1);
			break;
		case S2C_CUR_BETTING_INFO_IDX :
			SetCanMyBettingKind((char*)_msg, parm1);
			break;
		case S2C_BETTING_RES_IDX :
			SetBettingRes((char*)_msg, parm1);
			break;
		case S2C_BETTING_REAPPLY_IDX :
			SetBettingReApply((char*)_msg, parm1);
			break;
		case S2C_HIGHLOW_CHOICE_STATE_IDX:
			SetStatus(PlayStatus::PLAY_JOKBO_CHOICE);
			break;
		case S2C_HIGHLOW_CHOICE_RES_IDX :
			SetHighLow((char*)_msg, parm1);
			break;
		case S2C_7POKER_PAE_SHOW_RES_IDX:
			if (GetGameKind() == GAMEKIND_7POKER)
			{
				Show7PokerPae((char*)_msg, parm1);
			}
			else if (GetGameKind() == GAMEKIND_BADUKI)
			{
				ShowBadukiPae((char*)_msg, parm1);
			}
			else if (GetGameKind() == GAMEKIND_HOLDEM)
			{
				ShowHoldemPae((char*)_msg, parm1);
			}
			break;
		case S2C_HIGHLOW_PAE_SHOW_RES_IDX:
			ShowHighLowPae((char*)_msg, parm1);
			break;
		case S2C_SHARE_COMMUNITY_CARD_IDX:
			SetCommunityCard((char*)_msg, parm1);
			break;
		case S2C_RESULT_RES_IDX :
			SetResult((char*)_msg, parm1);
			break;
		case S2C_ADDITIONAL_RESULT_INFO_IDX:
			SetAdditionalResult((char*)_msg, parm1);
			break;
		case S2C_PLAYER_OUT_RESV_RES_IDX :
		case S2C_PUT_OUT_RESV_RES_IDX:
			SetPlayerOutReserve((char*)_msg, parm1);
			break;
		case S2C_NEXT_READY_IDX :
			SetStatus(PlayStatus::PLAY_NEXT_READY);
			//판이 끝날때 마다 count 를 저장한다.
			NotiDataManager::getSingleton().endGame();
			break;
		case S2C_GAME_ING_INFO_IDX :
			SetGameIngInfo((char*)_msg, parm1);
			break;
		case S2C_AFTER_RESULT_USER_INFO_IDX :
		case S2C_BETTING_DIE_RES_IDX:
			SetAfterResultUserInfo((char*)_msg, parm1);
			break;
		case S2C_GAME_PLAY_SAVE_SEQ_IDX:
			SetGamePlaySaveSeq((char*)_msg, parm1);
			break;
		case S2C_GAME_PLAY_STATCS_RES_IDX:
			ShowPlayGameStates((char*)_msg, parm1);
			break;
		case S2C_PLAYER_PLAY_STATCS_RES_IDX:
			ShowPlayerStates((char*)_msg, parm1);
			break;
		case S2C_HAZZ_UP_STATE_IDX :
			ShowLastLound();
			break;
		case S2C_SHOW_DOWN_STATE_IDX :
			ShowDownState((char*)_msg, parm1);
			break;
		case S2C_CHANGE_CARD_STATE_IDX:
			ShowBadugiSelectCard((char*)_msg, parm1);
			break;
		case S2C_CHANGE_CARD_RES_IDX:
			ChangeBadugiSelectCard((char*)_msg, parm1);
			break;
		case S2C_CUR_CHANGE_CARD_INFO_IDX:
			ShowChangeCardSeletPanel((char*)_msg, parm1);
			break;
		case S2C_EMOTICON_ROOM_IDX:
			SetPlayerEmotion((char*)_msg, parm1);
			break;
		case S2C_SAVE_GAME_PLAY_DATA_RES_IDX :
			SetSaveGamePlayData((char*)_msg, parm1);
			break;
		case S2C_CHANGE_BOSS_IDX :
			SetChangeBoss((char*)_msg, parm1);
			break;
		case S2C_PLAYERS_STATUS_IDX :
			SetPlayersStatus((char*)_msg, parm1);
			break;
		case S2C_CHANGE_SEED_MONEY_IDX:
			SetChangeSeedMoney((char*)_msg, parm1);
			break;
		case S2C_SURVIVAL_LAST_TABLE_IDX:
			ShowLastTableEffect();
			break;
	}

	return true;
}

void GameRoomInfo::OnError(int protocol, int errorCode)
{
	switch (protocol)
	{
		case S2C_PLAYER_OUT_RESV_RES_IDX:
		{
			PokerTopPanel * _pPanel = GetTopPanel();
			if (_pPanel != nullptr)
			{
				if (m_ExitReserve)
					_pPanel->SetPressExitReserveButton();
				else
					_pPanel->SetPressExitReserveCancelButton();

				_pPanel->SetOutButtonClick(false);
			}
			break;
		}
		default:
		{
			/*switch (errorCode)
			{
				case
			}*/
			break;
		}
	}
}

int GameRoomInfo::GetRoomId()
{
	return m_RoomIdx;
}

void GameRoomInfo::SetUserPo()
{
	//카드 위치를 더미에서 가져와서 셋팅한다.
	for (int _i = 0; _i < GAME_USER_MAX; _i++)
	{
		int _UserPo = (GetMyPo() + _i) % GAME_USER_MAX;
		if (m_UserList[_UserPo] != nullptr)
		{
			m_UserList[_UserPo]->GetCardManager()->SetData();
		}
	}
}

CCPoint GameRoomInfo::GetUserPosition(int _index)
{
	CCPoint _userPosition = m_UserList[_index]->GetCardManager()->GetTableCardRect(0).origin + ccp(90, 0);
	return _userPosition;
}

void GameRoomInfo::StartGameReq()
{
	//TODO : 게임 시작 요청
	TCPService::getSingletonPtr()->SendNormalPacket(CSProtocol::C2S_START_GAME_REQ_IDX);
}

void GameRoomInfo::ResourceLoadEndReq()
{
	//TODO : C2S_LOAD_END
	TCPService::getSingletonPtr()->SendNormalPacket(CSProtocol::C2S_LOAD_END_IDX);
}

void GameRoomInfo::SetCardChoicePanel(bool _visible)
{
	if (m_UserList[m_MyPo]->GetPlayerStatus() != PlayerStatus::PLAYER_INIT)
	{
		SetIsSelectedCard();
		return;
	}

	if (_visible == true)
	{
		//골랐을때
		RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(m_MyPo);
		if (_pPlayer)
			_pPlayer->setMyCharacterVisible(false);

		dynamic_cast<BettingCardOnOffPanel*>(LayerManager::getSingleton().getLayer("CardOnOffPanel"))->StartSetting();
	}
	else
	{
		LayerManager::getSingleton().getLayer("CardOnOffPanel")->setVisible(false);
	}
	
}

void GameRoomInfo::CardChoiceREQ(int _eraseCardIdx, int _openCardIdx)
{
	TCPService::getSingletonPtr()->SendCardChoiceReq(_eraseCardIdx, _openCardIdx);
}

//void GameRoomInfo::SetGameReady()
//{
//	//TODO : 유저 카드 초기화.
//	//TODO : 배팅&테이블 머니 초기화.
//}

void GameRoomInfo::SetMaster(int _userIdx)
{
	m_MasterPo = _userIdx;
	SetMarker(0, _userIdx);
}

void GameRoomInfo::SetBoss(int _userIdx)
{
	if (_userIdx != m_BossPo)
		SetMarker(1, _userIdx);
	m_BossPo = _userIdx;
}

void GameRoomInfo::SetHoldemDealer(int _userIdx)
{
	m_DealerPo = _userIdx;
}

void GameRoomInfo::SetBigBlind(int _userIdx)
{
	m_BigBlindPo = _userIdx;
}

void GameRoomInfo::SetMarker(int kind, int _userIdx)
{
	PokerPlayerInfoCommonPanel * _pPanel;
	for (int i = 0; i < GAME_USER_MAX; i++)
	{
		//if (m_UserList[i] == nullptr)
		//	continue;

		_pPanel = GetPlayerCommonPanel(i);

		if (_pPanel == nullptr)
			continue;

		
		if (kind == 0)	// 방장
			_pPanel->SetMasterMark(_userIdx == i, m_MyPo == i);
		else			// 보스
			_pPanel->SetBossMark(_userIdx == i, m_MyPo == i);
	}
}

void GameRoomInfo::SetUser(int _userIdx)
{
	m_MyPo = _userIdx;
}

//void GameRoomInfo::SetShareCard(int _userIdx, int _cardIdx, int _index)
//{
//	//TODO :  게임 카드를 설정한다.
//}

//void GameRoomInfo::ShareCardEndReq()
//{
//	TCPService::getSingletonPtr()->SendNormalPacket(CSProtocol::C2S_SHARE_CARD_END_RES_IDX);
//}

void GameRoomInfo::SetBetWait(int _bossIdx)
{
	SetBoss(_bossIdx);
	//TODO : S2C_CUR_BETTING_INFO 대기
}

void GameRoomInfo::SetUserData(RoomUserData* _ptr, int _idx)
{
	if (_idx >= 5)
	{
		CCLOG("ERROR index overflow - GameRoom::SetUserData");
		return;
	}

	if (m_UserList[_idx] != NULL)
	{
		CCLOG("warnning Pointer is not empty!!! - GameRoom::SetUserData");
		m_UserList[_idx] = NULL;
	}
	m_UserList[_idx] = _ptr;
	
}

RoomUserData* GameRoomInfo::GetUserDataPtr(int _idx)
{
	if (_idx == -1)
		_idx = m_MyPo;

	if (_idx < 0 || _idx >= GAME_USER_MAX)
		return nullptr;

	return m_UserList[_idx];
}

void GameRoomInfo::SetEndGame(int _winner, int _money)
{
	RoomUserData* _userInfo = GetUserDataPtr(_winner);
	_userInfo->m_pPlayerData->m_GameMoney += _money;
}

void GameRoomInfo::SetStartGame()
{
	//TODO : 리소스를 로드한다. (로딩 완료시 로딩 완료 메세지 전송 : ResourceLoadEndReq(); )
}

void GameRoomInfo::InitGame()
{

	//TODO : 게임을 재시작 하기위한 정보를 초기화 한다.
	m_isInitGame = true;
	m_isShareCardEnd = false;
	m_BetMoney = 0;
	m_PotMoney = 0;
	m_UpdatePotMoney = 0;
	m_PrePotMoney = 0;
	m_fPotMoneyEffectTime = 0.f;
	m_fPotMoneyUpdateTime = 0.f;
	m_PotMoneyEffectState = PotMoneyState::POT_NONE;
	m_PreMoneyUpdateList.clear();
	m_PotMoneyUpdateList.clear();
	m_isSelectedCard = false;
	m_isBettingCount = false;
	m_bBigGameAction = false;
	m_IsHiddenCheck = false;
	m_badugiSortedCard = false;
	m_badugiSortDelay = 0.f;
	m_myMadeCheck = false;
	m_bShowDown = false;
	m_fSoundDelayTime = 0.f;
	m_soundType = -1;
	
	m_bSendWait = false;
	m_bSendChanageRequest = false;
	m_bSendPassRequest = false;
	ResetBadugiSelectNumber();
	SetBadugiSelectState(DAY_TYPE_ALL_CLOSE);
	m_dayState = DAY_TYPE_END;
	

	if (m_pLabelWinnerMoney == nullptr)
	{
		m_pLabelWinnerMoney = CCLabelBMFont::create("123", "fonts/number_big.fnt");
		m_pLabelWinnerMoney->retain();
		m_pLabelWinnerMoney->setAnchorPoint(ccp(0.5f, 1.f));
		m_pLabelWinnerMoney->setScale(1.f);
		
		if (GetCardPanel() != nullptr)
		{
			GetCardPanel()->addChild(m_pLabelWinnerMoney, 20);
			m_pLabelWinnerMoney->release();
		}
	}

	PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel(); 
	int gapHeight = (backGroundPanel->getDummy("dmy_centersum").size.height - m_pLabelWinnerMoney->getContentSize().height) * 0.5f;
	m_pLabelWinnerMoney->setPosition(backGroundPanel->getImage("dmy_centersum")->getPosition());	
	m_pLabelWinnerMoney->setPositionY(m_pLabelWinnerMoney->getPositionY() + backGroundPanel->getDummy("dmy_centersum").size.height * 0.5f);
	m_pLabelWinnerMoney->setVisible(false);
	GetBackgroundPanel()->setVisibleCenterUI(true);
	GetBackgroundPanel()->mJackPotRewardPanel->setVisible(false);	
	SetPotMoney(0);
	SetCallAmount(0);
	m_BetPo = -1;

	for (RoomUserData* _user : m_UserList)
	{
		if (_user == nullptr)
			continue;

		_user->InitData();
	}

	SetStatus(PlayStatus::PLAY_NO);
	SetChangeCardKind(ChangeCardKind::CHANGE_CARD_KIND_NO);
	SetBoss(-1);

	BettingSevenPokerPanel * betPanel = GetBettingSevenPokerPanel();
	if (betPanel != nullptr)
		betPanel->InitCanBetting();
	
	PokerTopPanel * _pBackPanel = GetTopPanel();
	if (_pBackPanel != nullptr)
	{
		_pBackPanel->SetPressExitReserveCancelButton();
	}
	
	
	PokerResultPanel * panel = GetPokerResultPanel();
	if (panel)
	{
		panel->SetTurnOffReplayButton();
		panel->SetPlayerResultPanelAllInit();
		panel->setVisible(false);
	}

	PokerPlayerInfoPanel * infoPanel = GetPlayerInfoPanel();
	if (infoPanel)
		infoPanel->SetAllUserGameStartPlayerInfo();

	BettingSevenPokerPanel * _bettingPanel = GetBettingSevenPokerPanel();
	if (_bettingPanel)
		_bettingPanel->MovePanel(false);

	SkelObject* _pPotMoneyEffect = GetTopPanel()->getSkel("skel_potmoney");
	if (_pPotMoneyEffect)
	{
		_pPotMoneyEffect->playAnimation("potmoney_end");
	}

	initHiddenTouchPanel();

	//FightScene* _pScene = dynamic_cast<FightScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
	//if (_pScene)
	//{
	//	_pScene->StopGameEndEffect();
	//}
	
	PokerUnderImoticonPanel* _pImotiPanel = GetResultImoticonPanel();
	if (_pImotiPanel)
	{
		_pImotiPanel->ShowResultImoticon(false);
	}

	if (m_GameKind == GameKind::GAMEKIND_BADUKI)
	{
		if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel"))
		{
			BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));
			if (_pSelectCardPanel->isVisible() == true && _pSelectCardPanel != nullptr)
			{
				_pSelectCardPanel->ShowBadugiSelectCardPanel(false);
			}
		}
	}

	if (m_GameKind == GameKind::GAMEKIND_HOLDEM)
		ResetCommunityCard();
	_initDealerfee();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//AdmobManager::getSingleton().showAdMob();
#endif


}

void GameRoomInfo::initHiddenTouchPanel()
{
	if (GetTopPanel() == nullptr)
	{
		return;
	}
	mShowTouchPanel = false;
	GetTopPanel()->m_HiddenTouchPanel->getButton("sbtn_hiddenback")->setEnable(false);
	GetTopPanel()->m_HiddenTouchPanel->setTouchable(false);
	GetTopPanel()->m_HiddenTouchPanel->setVisible(false);
	GetTopPanel()->m_HiddenTouchPanel->setPosition(GetTopPanel()->m_posStartHiddenPanel);
	GetTopPanel()->m_HiddenTouchPanel->getButton("sbtn_hiddenback")->setPosition(GetTopPanel()->m_posStartHiddenCard);

	GetTopPanel()->mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->setEnable(false);
	GetTopPanel()->mHiddenBigTouchPanel->setTouchable(false);
	GetTopPanel()->mHiddenBigTouchPanel->setVisible(false);
	GetTopPanel()->mHiddenBigTouchPanel->setPosition(GetTopPanel()->mBigPosStartHiddenPanel);
	GetTopPanel()->mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->setPosition(GetTopPanel()->mBigPosStartHiddenCard);
	GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hidden_light")->setScale(1.0f);
	GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hidden_light")->setVisible(true);
	GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hidden_light")->setOpacity(255 * 0.2f);
	GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hidden_black")->setScale(2.0f);
	GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hidden_black")->setVisible(true);
	GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hidden_black")->setOpacity(255 * 0.2f);

}

void GameRoomInfo::KickPlayerREQ(int po, int socketId)
{
	TCPService::getSingletonPtr()->SendNormalPacket(CSProtocol::C2S_PUT_OUT_IDX);
}

void GameRoomInfo::PlayerOutREQ(int po, int socketId)
{
	TCPService::getSingletonPtr()->SendNormalPacket(CSProtocol::C2S_PLAYER_OUT_RESV_REQ_IDX);
}

void GameRoomInfo::KickPlayerRES(int po, int socketId, PlayerOutResrvKind _kind)
{
	RoomUserData* _userInfo = GetUserDataPtr(po);
	_userInfo->m_KickReady = true;
}

void GameRoomInfo::PlayerOutRES(int po, int socketId, PlayerOutResrvKind _kind)
{
	RoomUserData* _userInfo = GetUserDataPtr(po);
	_userInfo->m_OutReady = true;
}

GameLogKind GameRoomInfo::GetGameState()
{
	return m_GameState;
}


void GameRoomInfo::SetCardChoice()
{
	if (m_DealerShoot == true)
	{
		m_DealerShoot = false;
		//m_pDealer->appendAnimation("dealing_ready");
		m_pDealer->appendAnimation("idle", true);
	}

	for (int _i = 0; _i < GAME_USER_MAX; _i++)
	{
		RoomUserData* _pUserData = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_i);
		if (_pUserData != nullptr)
		{
			if (_pUserData->GetPlayerStatus() != PLAYER_INIT)
				continue;
			
			if (_pUserData->m_pMyCharater != nullptr)
			{
				if (_pUserData->GetPlayerStatus() != PLAYER_SEE)
				{
					_pUserData->PlayCharacterAnimation(THINK2);
				}
			}

			if (_pUserData->m_Po == m_MyPo)
				continue;

			PokerPlayerInfoCommonPanel* _pPanel = GetPlayerCommonPanel(_pUserData->m_Po);
			_pPanel->turnOnTimeGauge();
		}
	}

	SetStatus(PlayStatus::PLAY_CARD_CHOICE);
	SortCard();

	//Todo:  기덕 추가 카드가 보여지는 애니가 완료되지 않았다면 어떻게 하지?
// 	for (int _i = 0; _i < GAME_USER_MAX; _i++)
// 	{
// 		RoomUserData* _pUserData = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_i);
// 		if (_pUserData != nullptr)
// 		{
// 			if (_pUserData->m_Po == m_MyPo) {				
// 				_pUserData->setActionSpeed();
// 			}				
// 		}
// 	}
}

void GameRoomInfo::SetData(EnterRoomSuccess * resData)
{
	m_RoomIdx = resData->roomidx();
	m_CurrentUser = resData->currentuser();
	m_MaxUser = resData->maxuser();
	m_SeedMoney = resData->permoney();
	m_bigGameMoney1 = GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney1;
	m_bigGameMoney2 = GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney2;
	m_BettingRule = (BettingRule)GameDataManager::getSingletonPtr()->m_BettingRule;
	m_BettingMaxMoney = GameDataManager::getSingletonPtr()->m_EnterGameRoomBettingMaxMoney;
	m_GameKind = resData->gamekind();

	if (m_GameKind == GameKind::GAMEKIND_HOLDEM)
		GameDataManager::getSingletonPtr()->m_isTraditionalHoldem = true;
	else
		GameDataManager::getSingletonPtr()->m_isTraditionalHoldem = false;

	m_MasterPo = resData->masterpo();
	m_MyPo = resData->po();

	if (resData->has_lossmaxmoneyperplay() == true)
		m_LossMaxMoneyPerDay = resData->lossmaxmoneyperplay();
	
	if (resData->has_bigpot1() == true)
		m_bigGameMoney1 = resData->bigpot1();
	if (resData->has_bigpot2() == true)
		m_bigGameMoney2 = resData->bigpot2();

	if (resData->has_gamemode())
	{
		m_GameMode = resData->gamemode();
	}
	else
	{
		m_GameMode = GameMode::MODE_NORMAL;
	}

	if (resData->has_curusercount())
	{
		m_SurvivalCurUserCount = resData->curusercount();
	}
	else
	{
		m_SurvivalCurUserCount = -1;
	}

	if (resData->has_totalusercount())
	{
		m_SurvivalTotalUserCount = resData->totalusercount();
	}
	else
	{
		m_SurvivalTotalUserCount = -1;
	}


	PokerTopPanel* _pTopPanel = GetTopPanel();
	if (_pTopPanel)
	{
		_pTopPanel->SetGameMode(m_GameMode);

		if (m_SurvivalCurUserCount > 0 && m_SurvivalTotalUserCount > 0)
		{
			_pTopPanel->SetPLayerCount(m_SurvivalCurUserCount, m_SurvivalTotalUserCount);
		}
	}
	
	//if (m_GameKind == GameKind::GAMEKIND_HOLDEM)
	//	InitCommunityCard();

	if (resData->has_gamemoney())
		GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney = resData->gamemoney();

	RoomPlayerInfo playerInfo;

	m_UserList[m_MyPo] = new RoomUserData();	//TODO : 자기 데이터 세팅. 현제는 빈 데이터를 연결 중.
	m_UserList[m_MyPo]->m_Po = m_MyPo;
	m_UserList[m_MyPo]->m_pPlayerData = GameDataManager::getSingleton().GetPlayerDataPtr();
	// 초기에 일단 내 상태는 Init 상태로 만들어놓는다.
	// 그리고, prepare end에서 다시 세팅한다.
	m_UserList[m_MyPo]->SetPlayerStatus(PlayerStatus::PLAYER_PREPARE);
	m_UserList[m_MyPo]->SetMe(true);
	m_UserList[m_MyPo]->GetCardManager()->m_UserIdx = 0;
	m_UserList[m_MyPo]->GetCardManager()->m_UserPo = m_MyPo;

	PokerPlayerInfoCommonPanel* _pMyPanel = GetPlayerCommonPanel(m_MyPo);
	if (_pMyPanel)
	{
		if (resData->isrankdecide() == false)
			_pMyPanel->TurnOnPlayerRank(resData->rank(), false);
	}

	for (int i = 0, j = resData->playerinfo_size(); i < j; i++)
	{
		playerInfo = resData->playerinfo(i);
		AddUser(&playerInfo);
	}

	if (m_pStayPopup)
	{
		m_pStayPopup->closePanel();
	}
	m_pStayPopup = nullptr;
	if (GetGameMode() != GameMode::MODE_NORMAL)
	{
		m_pStayPopup = new TournamentWaitingPanel();
		LayerManager::getSingleton().pushDynamicLayer(m_pStayPopup, DYNAMIC_PUSH_LAYER);
	}
	
}

void GameRoomInfo::SetReplayOtherData(int _kind, int _grade)
{
	int _size = 0;
	
	if (_kind == GAMEKIND_7POKER)
	{
		_size = GameDataManager::getSingletonPtr()->m_p7PokerChannelList.size();
	}
	else if (_kind == GAMEKIND_HIGH_LOW)
	{
		_size = GameDataManager::getSingletonPtr()->m_pHighLowChannelList.size();
	}
	else if (_kind == GAMEKIND_BADUKI)
	{
		_size = GameDataManager::getSingletonPtr()->m_pBadukiChannelList.size();
	}
	else if (_kind == GAMEKIND_HOLDEM)
	{
		_size = GameDataManager::getSingletonPtr()->m_pHoldemChannelList.size();
	}
	
	for (int _i = 0; _i < _size; _i++)
	{
		W_ChannelInfo* _pInfo = nullptr;
		if (_kind == GAMEKIND_7POKER)
		{
			_pInfo = GameDataManager::getSingletonPtr()->m_p7PokerChannelList[_i];
		}
		else if (_kind == GAMEKIND_HIGH_LOW)
		{
			_pInfo = GameDataManager::getSingletonPtr()->m_pHighLowChannelList[_i];
		}
		else if (_kind == GAMEKIND_BADUKI)
		{
			_pInfo = GameDataManager::getSingletonPtr()->m_pBadukiChannelList[_i];
		}
		else if (_kind == GAMEKIND_HOLDEM)
		{
			_pInfo = GameDataManager::getSingletonPtr()->m_pHoldemChannelList[_i];
		}

		if (_pInfo)
		{
			if (_grade == _pInfo->grade())
			{
				m_bigGameMoney1 = _pInfo->bigpot_1();
				m_bigGameMoney2 = _pInfo->bigpot_2();
				m_BettingRule = (BettingRule)_pInfo->bettingrule();
				m_BettingMaxMoney = _pInfo->bigbettingmaxmoney();
			}
		}
	}
}

void GameRoomInfo::SetReplayData(GamePlayData* _resData)
{
	m_isReplayData = true;

	m_RoomIdx = _resData->index();
	m_CurrentUser = _resData->current();
	m_MaxUser = _resData->max();
	m_SeedMoney = _resData->seedmoney();
	m_GameKind = _resData->gamekind();
	m_MasterPo = _resData->masteridx();
	SetReplayOtherData(m_GameKind, _resData->channelgrade());
	if (_resData->has_gamemode())
	{
		m_GameMode = _resData->gamemode();
	}
	else
	{
		m_GameMode = GameMode::MODE_NORMAL;
	}

	int32 _userDbIdx = GameDataManager::getSingletonPtr()->m_pPlayerData->m_DId;
	bool _firstUser = true;
	int _userIdx = 0;
	int _userSize = _resData->userinfo_size();
	for (int _i = 0; _i < _userSize; _i++)
	{
		if (_firstUser == true)
		{
			_firstUser = false;
			_userIdx = _resData->userinfo(_i).po();
		}
		else if (_resData->userinfo(_i).dbidx() == _userDbIdx)
			_userIdx = _resData->userinfo(_i).po();
	}
	m_MyPo = _userIdx;

	for (int i = 0, j = _resData->userinfo_size(); i < j; i++)
	{
		//_resData->userinfo(i)
		int _po = _resData->userinfo(i).po();
		
		m_UserList[_po] = new RoomUserData();
		
		m_UserList[_po]->m_Po = _po;
		if (m_MyPo == _po) m_UserList[_po]->SetMe(true);
		
		m_UserList[_po]->m_pPlayerData = new PlayerData();

		m_UserList[_po]->m_pPlayerData->m_UID = _resData->userinfo(i).socketid();
		m_UserList[_po]->m_pPlayerData->m_DId = _resData->userinfo(i).dbidx();
		m_UserList[_po]->m_pPlayerData->m_DGroup = _resData->userinfo(i).dbgroup();
		m_UserList[_po]->m_pPlayerData->m_NickName = _resData->userinfo(i).nickname();
		m_UserList[_po]->m_pPlayerData->m_WinCount[GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind()] = 0;
		m_UserList[_po]->m_pPlayerData->m_LoseCount[GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind()] = 0;
		//m_UserList[_po]->m_pPlayerData->m_CharacterIdx = _resData->userinfo(i).charidx();
		m_UserList[_po]->m_pPlayerData->SetCharacter(_resData->userinfo(i).charidx());
		m_UserList[_po]->m_pPlayerData->m_GameMoney = _resData->userinfo(i).gamemoney();
		m_UserList[_po]->m_pPlayerData->m_UserKind = _resData->userinfo(i).userkind();
		m_UserList[_po]->m_pPlayerData->m_Level = 1;
		m_UserList[_po]->m_pPlayerData->m_Exp = 0;

		m_UserList[_po]->GetCardManager()->m_UserIdx = GameDataManager::getSingletonPtr()->ServerToClientIndex(_po);
		m_UserList[_po]->GetCardManager()->m_UserPo = _po;

		m_UserList[_po]->SetPlayerStatus(_resData->userinfo(i).playerstatus());
	}
}

void GameRoomInfo::ResetReplayData(GamePlayData* _resData)
{
	m_bShowDown = false;
	m_fSoundDelayTime = 0.f;
	m_soundType = -1;

	m_isReplayData = true;
	m_UpdatePotMoney = 0;
	m_PrePotMoney = 0;
	m_PotMoney = 0;
	m_PreMoneyUpdateList.clear();
	m_PotMoneyUpdateList.clear();

	m_RoomIdx = _resData->index();
	m_CurrentUser = _resData->current();
	m_MaxUser = _resData->max();
	m_SeedMoney = _resData->seedmoney();
	m_GameKind = _resData->gamekind();
	m_MasterPo = _resData->masteridx();

	int32 _userDbIdx = GameDataManager::getSingletonPtr()->m_pPlayerData->m_DId;
	bool _firstUser = true;
	int _userIdx = 0;
	int _userSize = _resData->userinfo_size();
	for (int _i = 0; _i < _userSize; _i++)
	{
		if (_firstUser == true)
		{
			_firstUser = false;
			_userIdx = _resData->userinfo(_i).po();
		}
		else if (_resData->userinfo(_i).dbidx() == _userDbIdx)
			_userIdx = _resData->userinfo(_i).po();
	}
	m_MyPo = _userIdx;

	for (int i = 0, j = _resData->userinfo_size(); i < j; i++)
	{
		//_resData->userinfo(i)
		int _po = _resData->userinfo(i).po();

		if (m_UserList[_po] == NULL)
			continue;
		if (m_UserList[_po]->m_pPlayerData == NULL)
			continue;

		m_UserList[_po]->m_Po = _po;
		if (m_MyPo == _po) m_UserList[_po]->SetMe(true);
		m_UserList[_po]->m_pPlayerData->m_UID = _resData->userinfo(i).socketid();
		m_UserList[_po]->m_pPlayerData->m_DId = _resData->userinfo(i).dbidx();
		m_UserList[_po]->m_pPlayerData->m_DGroup = _resData->userinfo(i).dbgroup();
		m_UserList[_po]->m_pPlayerData->m_NickName = _resData->userinfo(i).nickname();
		m_UserList[_po]->m_pPlayerData->m_WinCount[GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind()] = 0;
		m_UserList[_po]->m_pPlayerData->m_LoseCount[GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetGameKind()] = 0;
		//m_UserList[_po]->m_pPlayerData->m_CharacterIdx = _resData->userinfo(i).charidx();
		m_UserList[_po]->m_pPlayerData->SetCharacter(_resData->userinfo(i).charidx());
		m_UserList[_po]->m_pPlayerData->m_GameMoney = _resData->userinfo(i).gamemoney();
		m_UserList[_po]->m_pPlayerData->m_UserKind = _resData->userinfo(i).userkind();
		m_UserList[_po]->m_pPlayerData->m_Level = 1;
		m_UserList[_po]->m_pPlayerData->m_Exp = 0;

		m_UserList[_po]->GetCardManager()->m_UserIdx = GameDataManager::getSingletonPtr()->ServerToClientIndex(_po);
		m_UserList[_po]->GetCardManager()->m_UserPo = _po;

		m_UserList[_po]->SetPlayerStatus(_resData->userinfo(i).playerstatus());
	}

	if (m_pDealer)
	{
		DealerAnimation(DealerAniKind::DEALER_IDLE);
	}
}

void GameRoomInfo::SetGameMoney(int po, int64 gameMoney)
{
	RoomUserData * roomUserData = GetUserDataPtr(po);
	if (roomUserData == nullptr)
		return;

	roomUserData->SetGameMoney(gameMoney);

	PokerPlayerInfoCommonPanel * _pPlayerPanel = GetPlayerCommonPanel(po);
	if (_pPlayerPanel != nullptr)
		_pPlayerPanel->SetGoldAmount(gameMoney);
}

void GameRoomInfo::SetPlayersStatus(char * data, int size)
{
	PlayersStatus res;
	res.ParseFromArray(data, size);

	PlayerPoInfo poInfo;
	RoomUserData * user;
	for (int i = 0, j = res.playerpoinfo_size(); i < j; i++)
	{
		poInfo = res.playerpoinfo(i);

		user = m_UserList[poInfo.po()];
		if (user == nullptr)
			continue;
		if (user->GetPlayerStatus() == poInfo.playerstatus())
			continue;

		user->SetPlayerStatus(poInfo.playerstatus());
	}
}

void GameRoomInfo::SetChangeSeedMoney(char * data, int size)
{
	ChangeSeedMoney res;

	res.ParseFromArray(data, size);

	m_SeedMoney = res.seedmoney();

	if (res.has_bigpot1() == true)
		m_bigGameMoney1 = res.bigpot1();
	if (res.has_bigpot2() == true)
		m_bigGameMoney2 = res.bigpot2();


	//씨드 머니 상승
	PanelHelper::pushSeedMoneyUpPanel(m_SeedMoney, res.islastplay() == 1);
}

void GameRoomInfo::SetBettingSeedMoney(char * data, int size)
{
	BettingSeedRes res;
	res.ParseFromArray(data, size);

	SetPotMoney(res.potmoney(), res.potmoney());
	SetPotMoneyUpdate(PotMoneyState::POT_UPDATE);
	//m_PotMoneyEffectState = PotMoneyState::POT_UPDATE;

	SetBoss(res.bosspo());

	SetMyCallMoney();

	GameMoneyInOutInfo gameMoneyInfo;
	RoomUserData * roomUserData;

	for (int i = 0, j = res.gamemoneyinoutinfo_size(); i < j; i++)
	{
		gameMoneyInfo = res.gamemoneyinoutinfo(i);
		SetGameMoney(gameMoneyInfo.po(), gameMoneyInfo.gamemoney());

		roomUserData = GetUserDataPtr(gameMoneyInfo.po());
		
		PokerChipWidget::create(gameMoneyInfo.inoutmoney(), (UserTablePosition)roomUserData->GetCardManager()->m_UserIdx, 0.f);
	}

	SetBettingInfoInit(true);
	if (res.has_curusercount())
	{
		m_SurvivalCurUserCount = res.curusercount();
	}
	else
	{
		m_SurvivalCurUserCount = -1;
	}

	if (res.has_totalusercount())
	{
		m_SurvivalTotalUserCount = res.totalusercount();
	}
	else
	{
		m_SurvivalTotalUserCount = -1;
	}

	PokerTopPanel* _pTopPanel = GetTopPanel();
	if (_pTopPanel)
	{
		if (m_SurvivalCurUserCount > 0 && m_SurvivalTotalUserCount > 0)
		{
			_pTopPanel->SetPLayerCount(m_SurvivalCurUserCount, m_SurvivalTotalUserCount);
		}
	}

	SetStatus(PlayStatus::PLAY_BETTING_SEED_INIT);

	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BET);
}

void GameRoomInfo::SetBettingBlindMoney(char * data, int size)
{
	BettingBlindRes res;
	res.ParseFromArray(data, size);

	SetPotMoney(res.potmoney(), res.bettingmoney());
	SetPotMoneyUpdate(PotMoneyState::POT_UPDATE);
	//m_PotMoneyEffectState = PotMoneyState::POT_UPDATE;

	SetBoss(res.smallblindpo());
	SetHoldemDealer(res.dealerpo());
	SetBigBlind(res.bigblindpo());

	GameMoneyInOutInfo gameMoneyInfo;
	RoomUserData * roomUserData;

	SetBettingInfoInit(true);

	for (int i = 0, j = res.gamemoneyinoutinfo_size(); i < j; i++)
	{
		gameMoneyInfo = res.gamemoneyinoutinfo(i);
		SetGameMoney(gameMoneyInfo.po(), gameMoneyInfo.gamemoney());

		roomUserData = GetUserDataPtr(gameMoneyInfo.po());

		roomUserData->m_BettingMoney = -gameMoneyInfo.inoutmoney();
		roomUserData->m_BettingKind = BettingKind::BBING;

		if (m_BetMoney < roomUserData->m_BettingMoney)
			m_BetMoney = roomUserData->m_BettingMoney;
		
		PokerChipWidget::create(gameMoneyInfo.inoutmoney(), (UserTablePosition)roomUserData->GetCardManager()->m_UserIdx, 0.f);
	}

	m_preUserBetMoney = m_BetMoney;

	
	SetMyCallMoney();


	if (res.has_curusercount())
	{
		m_SurvivalCurUserCount = res.curusercount();
	}
	else
	{
		m_SurvivalCurUserCount = -1;
	}

	if (res.has_totalusercount())
	{
		m_SurvivalTotalUserCount = res.totalusercount();
	}
	else
	{
		m_SurvivalTotalUserCount = -1;
	}

	PokerTopPanel* _pTopPanel = GetTopPanel();
	if (_pTopPanel)
	{
		if (m_SurvivalCurUserCount > 0 && m_SurvivalTotalUserCount > 0)
		{
			_pTopPanel->SetPLayerCount(m_SurvivalCurUserCount, m_SurvivalTotalUserCount);
		}
	}

	SetStatus(PlayStatus::PLAY_BETTING_BLIND);

	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BET);
}

void GameRoomInfo::SetBettingBackMoney(char * data, int size)
{
	BettingSeedRes res;
	res.ParseFromArray(data, size);

	SetPotMoney(res.potmoney(), res.bettingmoney());
	SetPotMoneyUpdate(PotMoneyState::POT_UPDATE);
	//m_PotMoneyEffectState = PotMoneyState::POT_UPDATE;

	GameMoneyInOutInfo gameMoneyInfo;
	RoomUserData * roomUserData;

	for (int i = 0, j = res.gamemoneyinoutinfo_size(); i < j; i++)
	{
		gameMoneyInfo = res.gamemoneyinoutinfo(i);
		SetGameMoney(gameMoneyInfo.po(), gameMoneyInfo.gamemoney());

		roomUserData = GetUserDataPtr(gameMoneyInfo.po());

		PokerChipWidget::create(gameMoneyInfo.inoutmoney(), (UserTablePosition)roomUserData->GetCardManager()->m_UserIdx, 0.f);
	}

	if (res.has_curusercount())
	{
		m_SurvivalCurUserCount = res.curusercount();
	}
	else
	{
		m_SurvivalCurUserCount = -1;
	}

	if (res.has_totalusercount())
	{
		m_SurvivalTotalUserCount = res.totalusercount();
	}
	else
	{
		m_SurvivalTotalUserCount = -1;
	}

	PokerTopPanel* _pTopPanel = GetTopPanel();
	if (_pTopPanel)
	{
		if (m_SurvivalCurUserCount > 0 && m_SurvivalTotalUserCount > 0)
		{
			_pTopPanel->SetPLayerCount(m_SurvivalCurUserCount, m_SurvivalTotalUserCount);
		}
	}
}

void GameRoomInfo::SetBettingInfoInit(bool isAll)
{
	m_BetMoney = 0;
	m_preUserBetMoney = 0;

	for (int i = 0, j = GAME_USER_MAX; i < j; i++)
	{
		if (m_UserList[i] == nullptr)
			continue;

		m_UserList[i]->SetBettingInfoInit(isAll);
	}
}

BettingKind GameRoomInfo::GetPreviousBattingKind(int _idx)
{
	BettingKind _kind = BETTING_NO;

	for (int _i = 0; _i < GAME_USER_MAX - 1; _i++)
	{
		_idx--;
		if (_idx < 0 )
		{
			_idx = GAME_USER_MAX - 1;
		}

		if (m_UserList[_idx] == nullptr)
			continue;

		if (m_UserList[_idx]->m_BettingKind == CHECK ||
			m_UserList[_idx]->m_BettingKind == BBING ||
			m_UserList[_idx]->m_BettingKind == DDADANG ||
			m_UserList[_idx]->m_BettingKind == QUARTER ||
			m_UserList[_idx]->m_BettingKind == HALF	||
			m_UserList[_idx]->m_BettingKind == MAX_BETTING)
		{
			_kind = m_UserList[_idx]->m_BettingKind;
			break;
		}
		
	}
	return _kind;
}

void GameRoomInfo::SetBettingRes(char * data, int size)
{
	BettingRes res;
	res.ParseFromArray(data, size);

	BettingKind betKind = res.bettingkind();

	int po = res.po();
	if (m_UserList[po] == nullptr)
		return;

	/*int64 myBettingMoney = m_BetMoney - m_UserList[po]->GetBettingMoney();
	int64 tmpPotMoney = m_PotMoney + myBettingMoney;

	int64 tmpPreMoney = GetBettingMoney(betKind, tmpPotMoney);
	if (tmpPreMoney > 0)
	{
		m_preUserBetMoney = tmpPreMoney;
		m_BetMoney += m_preUserBetMoney;
	}*/

	m_preUserBetMoney = res.preuserbettingmoney();	// 이전 사람의 최종 베팅 금액
	m_BetMoney = res.turnallbettingmoney();		// 현재 턴의 최고 베팅 머니

	//Betting animation
	//PokerChipWidget::create(res.bettingmoney(), (UserTablePosition)m_UserList[po]->GetCardManager()->m_UserIdx);
	m_UserList[po]->SetBettingChipAmount(res.bettingmoney());
	switch (betKind)
	{
	case CHECK:
		if (IsBigGame())
		{
			DealerAnimation(DealerAniKind::DEALER_REACT_SMALLBET);
		}
		else
		{
			if (m_UserList[po]->m_pCardManager->IsLastCard())//마지막 게임
			{
				DealerAnimation(DealerAniKind::DEALER_GESTURE_BAD);
			}
		}
		m_UserList[po]->PlayCharacterAnimation(BET_CHECK);
		break;
	case CALL:
	{
		BettingKind _preBet = GetPreviousBattingKind(po);
		if (_preBet == CHECK)
			m_UserList[po]->PlayCharacterAnimation(BET_CHECK);
		else if (_preBet == BBING)
			m_UserList[po]->PlayCharacterAnimation(BET_BBING);
		else if (_preBet == DDADANG || _preBet == QUARTER || _preBet == HALF || _preBet == MAX_BETTING)
			m_UserList[po]->PlayCharacterAnimation(BET_RAISE);
		break;
	}

	case BBING:
		if (IsBigGame())
		{
			DealerAnimation(DealerAniKind::DEALER_REACT_SMALLBET);
		}
		else
		{
			if (m_UserList[po]->m_pCardManager->IsLastCard())//마지막 게임
			{
				DealerAnimation(DealerAniKind::DEALER_GESTURE_BAD);
			}
		}
		m_UserList[po]->PlayCharacterAnimation(BET_BBING);
		break;
	case HALF:
		if (IsBigGame())
		{
			if (m_UserList[po]->m_pCardManager->IsLastCard())//마지막 게임
			{
				DealerAnimation(DealerAniKind::DEALER_GESTURE_GOOD);
			}
			m_UserList[po]->PlayCharacterAnimation(BET_BIG_RAISE);
		}
		else
		{
			m_UserList[po]->PlayCharacterAnimation(BET_RAISE);
		}

		break;
	case QUARTER:
		if (IsBigGame())
		{
			m_UserList[po]->PlayCharacterAnimation(BET_BIG_RAISE);
		}
		else
		{
			m_UserList[po]->PlayCharacterAnimation(BET_RAISE);
		}

		break;
	case DDADANG:
		m_UserList[po]->PlayCharacterAnimation(BET_RAISE);
		break;
	case DIE:
	{
		if (po == m_MyPo)
		{
			GetTopPanel()->m_bMoveHiddenCard = false;
			ShowHiddenCardAnimaion(false);
		}
		m_UserList[po]->SetPlayerStatus(PlayerStatus::PLAYER_DIE);
		m_UserList[po]->GetCardManager()->ActionAllCloseCard((po == m_MyPo && m_ExitReserve));

		if (isBigAnimation())
		{
			m_UserList[po]->PlayCharacterAnimation(BET_BIGFOLD);
		}
		else
		{
			m_UserList[po]->PlayCharacterAnimation(DIE_IDLE);
		}

		int _po = m_UserList[po]->m_Po;
		PokerPlayerInfoCommonPanel* _pPanel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(_po);

		if (_pPanel) {
			_pPanel->turnOffTimeGauge();
			_pPanel->setGameStartPlayerInfo();
			_pPanel->turnOnUserInfoBack();
		}
		break;
	}
	case MAX_BETTING:
		if (m_UserList[po]->m_pCardManager->IsLastCard())//마지막 게임
		{
			DealerAnimation(DealerAniKind::DEALER_GESTURE_GOOD);
		}
		m_UserList[po]->PlayCharacterAnimation(BET_BIG_RAISE);
		break;
	}

	SetPotMoney(res.potmoney(), res.realbettingmoney());

	m_UserList[po]->SetBetting(&res);

	PokerPlayerInfoCommonPanel* _pPlayerPanel = GetPlayerCommonPanel(po);
	if (_pPlayerPanel)
	{
		_pPlayerPanel->turnOffTimeGauge();
		m_isBettingCount = false;
		_pPlayerPanel->SetBetting(betKind, m_MyPo == po, res.bettingmoney());
		_pPlayerPanel->SetGoldAmount(res.gamemoney());
		InitCanBettingPanel();
		if (m_MyPo == po)
		{
			GetBettingSevenPokerPanel()->MovePanel(false);
			//_pPlayerPanel->TurnOffJokboInfo();
		}
		if (res.isallbet() != AllBetKind::ALLBET_NO)
		{
			_pPlayerPanel->SetAllBet(res.isallbet());

			int _clientIndex = GameDataManager::getSingletonPtr()->ServerToClientIndex(po);
			if (_clientIndex > 2)
			{
				DealerAnimation(DealerAniKind::DEALER_REACT_ALLIN_L);
			}
			else
			{
				DealerAnimation(DealerAniKind::DEALER_REACT_ALLIN_R);
			}
		}
	}	
}

void GameRoomInfo::SetDealerSoundDelayPlay(float _delay, int _type)
{
	//Dealer Only
	m_fSoundDelayTime = _delay;
	m_soundType = _type;
}

void GameRoomInfo::SetBettingReApply(char * data, int size)
{
	BettingMoneyReApplyList res;
	res.ParseFromArray(data, size);

	int po;
	for (int i = 0, j = res.bettingmoneyapplyres_size(); i < j; i++)
	{
		BettingMoneyReApply reApply = res.bettingmoneyapplyres(i);
		po = reApply.po();

		if (m_UserList[po] == nullptr)
			continue;

		SetGameMoney(po, reApply.gamemoney());
	}
}


void GameRoomInfo::SetResultExceptPanelOff()
{
	if (LayerManager::getSingleton().hasLayer("BettingPanel"))
	{
		BettingSevenPokerPanel * _bPanel = dynamic_cast<BettingSevenPokerPanel *>(LayerManager::getSingleton().getLayer("BettingPanel"));
		if (_bPanel && _bPanel->isVisible())
			_bPanel->MovePanel(false);
	}

	if (LayerManager::getSingleton().hasLayer("CardOnOffPanel"))
	{
		BettingCardOnOffPanel * _cPanel = dynamic_cast<BettingCardOnOffPanel *>(LayerManager::getSingleton().getLayer("CardOnOffPanel"));
		if (_cPanel && _cPanel->isVisible())
		{
			_cPanel->_makeCardPosition(false);
			_cPanel->setVisible(false);
		}
	}
}

void GameRoomInfo::SetResult(char * data, int size)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//AdmobManager::getSingleton().hideAdmob();	
#endif

	if (GetGameKind() == GAMEKIND_BADUKI)
	{
		SetBadugiSelectState(DAY_TYPE_END);
	}

	if (isBigAnimation())
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_TENSION, false);
	}
	

	FightScene* _pScene = dynamic_cast<FightScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
	if (_pScene)
	{
		//_pScene->SetCardExploreEffect();
		//_pScene->SetCardExploreEffect2();

		_pScene->GameEndEffect();
	}

	ResultInfo res;
	res.ParseFromArray(data, size);

	GetPlayerInfoPanel()->ClearAllPanelAction();
	SetResultExceptPanelOff();

	int infosize = res.playerresultinfo_size();
	// 순서 정하기
	PlayerResultInfo playerInfo;
	GameMoneyInOutInfo gameMoneyInfo;
	int * index = new int[infosize];
	int64 * money = new int64[infosize];

	for (int i = 0; i < infosize; i++)
	{
		index[i] = i;
		money[i] = 0;
	}

	for (int i = 0; i < infosize; i++)
	{
		playerInfo = res.playerresultinfo(i);
		gameMoneyInfo = playerInfo.gamemoneyinoutinfo();
		index[i] = i;
		money[i] = gameMoneyInfo.inoutmoney();
	}

	// 획득 머니에 따라 소팅 시작.
	int max, tmp;
	int64 data1, data2;
	for (int i = 0; i < infosize - 1; i++)
	{
		max = i;
		for (int j = i + 1; j < infosize; j++)
		{
			data1 = money[index[max]];
			data2 = money[index[j]];

			if (data1 < data2)
				max = j;
		}

		if (i != max)
		{
			tmp = index[i];
			index[i] = index[max];
			index[max] = tmp;
		}
	}
	// 실제 데이터 넣기
	

	PotMoneyPanel* _potMoneyPanel = dynamic_cast<PotMoneyPanel*>(LayerManager::getSingletonPtr()->getLayer("PotMoney"));
	if (_potMoneyPanel)
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_TAKECHIP);
		_potMoneyPanel->ClearPotMoney();
	}
	
	int po;
	PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
	backGroundPanel->setMadeResult(mMadeJokbo);

	PokerResultPanel* _pPanel = GetPokerResultPanel();
	_pPanel->SetPlayerResultPaenlAllVisible(false);
	_pPanel->setMadeResult(mMadeJokbo);

	
	PlayerData * playerData;
	bool isWin = false;
	for (int i = 0; i < infosize; i++)
	{
		playerInfo = res.playerresultinfo(index[i]);
		gameMoneyInfo = playerInfo.gamemoneyinoutinfo();

		if (!isWin && playerInfo.winkind() >= GIVEUP_WIN)
		{
			isWin = true;
			m_EffectMoney = money[index[i]];
			SetWinnerMoneyString(money[index[i]]);
		}

		po = gameMoneyInfo.po();

		if (m_UserList[po] == nullptr)
			continue;

		playerData = m_UserList[po]->m_pPlayerData;


		SetGameMoney(po, gameMoneyInfo.gamemoney());
		
		_pPanel->SetData(i,
						m_GameKind,
						playerInfo.winkind(),
						playerData->m_NickName,
						m_MyPo == po,
						m_UserList[po]->m_pJokboInfo->GetHighJokboKind(),
						m_UserList[po]->m_pJokboInfo->GetLowJokboKind(),
						gameMoneyInfo.inoutmoney()
		);

		PokerPlayerInfoCommonPanel* _pMyPanel = GetPlayerCommonPanel(m_MyPo);

		int myJokboKinds = m_UserList[m_MyPo]->m_pJokboInfo->GetHighJokboKind();
		int myLowJokboKinds = m_UserList[m_MyPo]->m_pJokboInfo->GetLowJokboKind();

		CCLOG("MyHigh = %d , myLow = %d", myJokboKinds, myLowJokboKinds);


		switch (playerInfo.winkind())
		{
			case GIVEUP_LOSE:
				GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_LOSE);
				DealerSound(EFX_DEALER_SORRY);
				break;
			case SWING_LOSE:
			case LOW_LOSE:
			case HIGH_LOSE:
			case NORMAL_LOSE:
				if (m_UserList[po]->m_AllBetKind == ALL_BET || m_UserList[po]->m_AllBetKind == MAX_BET)
				{
					m_UserList[po]->PlayCharacterAnimation(RESULT_ALLIN);
				}
				else if (isBigAnimation())
				{
					m_UserList[po]->PlayCharacterAnimation(LOSE_BIG);
				}				
				else
				{
					//TODO : 작은 패배 적용
					m_UserList[po]->PlayCharacterAnimation(LOSE_SMALL);
				}

				if (po == m_MyPo)
				{
					if (isBigAnimation())
					{
						m_UserList[po]->PlayCharacterSound(EFX_LOSEBIG);
					}
					else
					{
						m_UserList[po]->PlayCharacterSound(EFX_LOSESMALL);
					}
					GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_LOSE);
					DealerSound(EFX_DEALER_SORRY);
				}
				break;
			case GIVEUP_WIN:
			case NORMAL_WIN:
			case HIGH_WIN:
			case LOW_WIN:
			case SWING_WIN:
			case SPLIT_WIN:
			{
				Action_WinnerText(po, gameMoneyInfo.inoutmoney());
				if (isBigAnimation())
				{
					m_UserList[po]->PlayCharacterAnimation(WIN_BIG);

				}
				else
				{
					m_UserList[po]->PlayCharacterAnimation(WIN_SMALL);
				}

				if (po == m_MyPo)
				{
					if (isBigAnimation())
					{
						m_UserList[po]->PlayCharacterSound(EFX_WINBIG);
					}
					else
					{
						m_UserList[po]->PlayCharacterSound(EFX_WINSMALL);
					}
					GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_CHEER);
					GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_WIN);
					DealerSound(EFX_DEALER_CELEBRATE);
				}
				break;
			}
		}

		if (gameMoneyInfo.inoutmoney() > 0 && _potMoneyPanel)
		{
			_potMoneyPanel->Action_MovePotMoney(gameMoneyInfo.inoutmoney(), GetUserPosition(po), 1.6f);
		}
		
	}
	_pPanel->ShowPanel();

	//emotionPanel 이 open 되어 있을 경우 처리
	emoticonPanel* pPanel = dynamic_cast<emoticonPanel*>(LayerManager::getSingleton().getLayer("EmoticonPanel"));
	if (pPanel)
		pPanel->SetVisiebleEmotiWindow(false);

	PokerPlayerInfoCommonPanel * _commonPanel;
	for (int i = 0; i < GAME_USER_MAX; i++)
	{
		if (m_UserList[i] == nullptr)
			continue;

		_commonPanel = GetPlayerCommonPanel(i);
		if (_commonPanel == nullptr)
			continue;

		_commonPanel->SetAllBet(AllBetKind::ALLBET_NO);
		if (m_UserList[i]->m_pPlayerData->m_GameMoney <= 0)
		{
			_commonPanel->SetAllIn(true);
			DealerAnimation(DealerAniKind::DEALER_REACT_BANKRUPT);
			DealerSound(DealerEfxKind::EFX_DEALER_BANKRUPT);
			//Request 머니 충전.
		}
	}

	SetHighLowChoice(false);

	//pot money 제거.
	if (_potMoneyPanel)
	{
		_potMoneyPanel->ActionWinnerTakeAll(1.6f);
		//팟머니 연출 종료.
		SkelObject* _pPotMoneyEffect = GetTopPanel()->getSkel("skel_potmoney");
		if (_pPotMoneyEffect)
		{
			_pPotMoneyEffect->playAnimation("potmoney_end");
		}
	}

	//족보 초기화
	if (m_GameKind == GameKind::GAMEKIND_BADUKI)
	{
		SetMyBadugiJokbo(LowJokboKind::LOW_NO);
	}
	else
	{
		SetMyHighJokbo(HighJokboKind::HIGH_NO);
		if (m_GameKind == GameKind::GAMEKIND_HIGH_LOW)
			SetMyLowJokbo(LowJokboKind::LOW_NO);
	}
		

	SetStatus(PlayStatus::PLAY_RESULT);

	if (!m_isReplayData)
	{
		PokerUnderImoticonPanel* _pImotiPanel = GetResultImoticonPanel();
		if (_pImotiPanel)
		{
			_pImotiPanel->ShowResultImoticon(true);
		}
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//AdmobManager::getSingleton().hideAdmob();
#endif

	NX_SAFE_DELETE_ARRAY(index);
	NX_SAFE_DELETE_ARRAY(money);

	//히든 카드도 없앤다.
	initHiddenTouchPanel();
}

void GameRoomInfo::SetAdditionalResult(char * data, int size)
{
	PokerTopPanel* _pTopPanel = GetTopPanel();
	if (_pTopPanel == nullptr)
		return;

	PlayerAdditionalResultInfoList res;
	res.ParseFromArray(data, size);

	if (GetGameMode() == GameMode::MODE_SURVIVAL_TOURNAMENT)
	{
		int _curUserCount = res.curusercount();
		int _totalUserCount = res.totalusercount();

		_pTopPanel->SetPLayerCount(_curUserCount, _totalUserCount);
	}

	int _rankInfoSize = res.playerrankinfo_size();
	for (int _i = 0; _i < _rankInfoSize; _i++)
	{
		PlayerAdditionalRankInfo _rankInfo = res.playerrankinfo(_i);

		int _po = _rankInfo.po();
		int _socketId = _rankInfo.socketid();
		int _rank = _rankInfo.rank();
		int _isDecide = _rankInfo.isdecide();
		PokerPlayerInfoCommonPanel* _pCommonPanel = GetPlayerCommonPanel(_po);
		int _disconnectCnt = _rankInfo.disconnectcnt();

		if (_pCommonPanel == nullptr)
			continue;

		if (m_UserList[_po]->m_pPlayerData->m_UserKind == DUMMY_TNMT)
		{
			_pCommonPanel->TurnOnPlayerDisconnect(_disconnectCnt);
		}

		//if (_isDecide == 1)
		if (_isDecide == 1)
		{
			_pTopPanel->SetResultPlayerRank(_po, true, _rank);
			m_UserList[_po]->GetCardManager()->setVisibleCard(false);
			if (_po == m_MyPo)
			{

				//기덕 추가				
				Panel* cardPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("CardLayer"));
				cardPanel->setVisible(false);

				PanelHelper::pushTouramentRankPanel(_rank);
				if (GetGameMode() == GameMode::MODE_SURVIVAL_TOURNAMENT)
				{
					GameDataManager::getSingletonPtr()->m_bDeathmatchEnd = true;
				}
				else
				{
					GameDataManager::getSingletonPtr()->m_bTournamentEnd = true;
				}

			}

		}
		else if (GetGameMode() == GameMode::MODE_SURVIVAL_TOURNAMENT)
		{
			if (m_UserList[_po]->m_pPlayerData->m_UserKind != DUMMY_TNMT)
			{
				_pCommonPanel->TurnOnPlayerRank(_rank);
			}
		}
	}

	int _size = res.playeradditionalresultinfo_size();
	for (int _i = 0; _i < _size; _i++)
	{
		PlayerAdditionalResultInfo _info = res.playeradditionalresultinfo(_i);

		int _po = _info.po();
		int _kind = _info.jackpotjokbokind();
		int64 _jackpotMoney = _info.jackpotmoney();
		int64 _inoutMoney = _info.inoutmoney();
		int64 _userGameMoney = _info.gamemoney();
		

		if (m_UserList[_po] == NULL)
			continue;

		SetGameMoney(_po, _userGameMoney);

		if (_info.jackpotjokbokind() != HighJokboKind::HIGH_NO &&
			(_info.jackpotjokbokind() <= HighJokboKind::HIGH_FOUR_CARD ||
			(m_GameKind == GameKind::GAMEKIND_BADUKI &&
			_info.jackpotjokbokind() <= LowJokboKind::BADUKI_THIRD)
			)
			)
		{
			if (_jackpotMoney == 0)
				continue;

			JackpotPanel* _pPanel = nullptr;

			if (LayerManager::getSingletonPtr()->hasLayer("JackpotPanel"))
			{
				_pPanel = dynamic_cast<JackpotPanel*>(LayerManager::getSingletonPtr()->getLayer("JackpotPanel"));
			}

			if (_pPanel)
			{
				RoomUserData* userData = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_po);
				int  _idx = 0;

				if (GetGameKind() == GameKind::GAMEKIND_BADUKI)
				{
					_idx = 1;
					for (CardData* _CardData : userData->m_pJokboInfo->GetLowJokboCardList())
					{
						PokerCardSetContainer::iterator findIter = PokerCardHelper::getSingleton().getPockerSet().find(_CardData->m_pCard->GetCardId());

						_pPanel->SetCard(_idx, findIter->second);
						_idx++;

						if (_idx >= 5) break;
					}
				}
				else
				{
					if (_kind == HighJokboKind::HIGH_FOUR_CARD)	_idx = 1;

					for (CardData* _CardData : userData->m_pJokboInfo->GetHighJokboCardList())
					{
						PokerCardSetContainer::iterator findIter = PokerCardHelper::getSingleton().getPockerSet().find(_CardData->m_pCard->GetCardId());

						_pPanel->SetCard(_idx, findIter->second);
						_idx++;

						if (_idx >= 5) break;
					}
				}

				mJackPotRewardGameMoney = _jackpotMoney;
				_pPanel->StartJackpotAnimation(_kind);				
				GetBackgroundPanel()->setVisibleCenterUI(false);
			}
		}
	}
	if (ShouldDisplayDealerfee) {
		PokerPlayerInfoCommonPanel* _panel = GetPlayerCommonPanel(m_MyPo);
		std::string DealerDeduction = GameStringDepot::getSingleton().getString("TXT_DEALERFEE_DEDUCTION");
		std::string DelerfeeStringVal = "-" + GameDataManager::getSingleton().GetKoreanLiteral(StringConverter::toString(Dealerfee));

		_panel->mGoldAmount->setString(DealerDeduction.c_str());
		_panel->mGoldAmount->setOpacity(255);
		_panel->mPlayerName->setString(DelerfeeStringVal.c_str());
		_panel->mPlayerName->setOpacity(255);
		

		ShouldDisplayDealerfee = false;

	}
}


void GameRoomInfo::SetAfterResultUserInfo(char * data, int size)
{
	UpdatePlayerInfo res;
	res.ParseFromArray(data, size);

	int po = res.po();

	if (po != m_MyPo)
		return;

	PlayerData * playerData = GameDataManager::getSingletonPtr()->GetPlayerDataPtr();

	if (playerData == nullptr)
		return;

	if (m_GameMode == GameMode::MODE_NORMAL)
	{
		playerData->m_Level = res.level();
		playerData->m_Exp = res.exp();
	}
	//else
	//	m_rank = res.tournamentrank();

	mChipCount = res.gotchipcnt();
	//m_IsGetChip = res.gotchip() > 0 ? true : false;
	m_IsLevelUp = res.islevelup() == 1 ? true : false;
	m_RefillMoney = res.refillgamemoney();
	m_IsCompleteQuest = res.completequest() > 0 ? true : false;
	m_madeMoney = res.mademoney();
	isCharacterEffect = true;
	ExeAfterResultUserInfoUI();
	initHiddenTouchPanel();
}


// 세이브된 플레이어 번호를 받아 처리하는 함수
void GameRoomInfo::SetGamePlaySaveSeq(char * data, int size)
{
	GamePlaySeqRes res;
	res.ParseFromArray(data, size);

	m_GamePlaySeq = res.gameplayseq();

	RoomUserData* _pPlayer = GetUserDataPtr(m_MyPo);
	if (_pPlayer)
	{
		if (_pPlayer->GetPlayerStatus() == PLAYER_SEE)
		{
			return;
		}

	}
	// insert auto play UI!!!!!!!
	PokerResultPanel * _pPanel = GetPokerResultPanel();
	if (_pPanel != nullptr)
		_pPanel->SetTurnOnReplayButton();
}

// 플레이 영상을 내 보관함에 저장한 결과를 보여주는 함수
void GameRoomInfo::SetSaveGamePlayData(char * data, int size)
{
	GameSavePlayDataRes res;
	res.ParseFromArray(data, size);

	ResultCode resultCode = res.resultcode();

	string msgText;
	SimplePopupPanel * panel = nullptr;

	if (resultCode == RESULT_SUCCESS)
	{
		msgText = GameStringDepot::getSingleton().getString("TXT_INFO_REPLAY_SAVE_SUCCESS");//U8("게임중이 아니라 실행할 수 없습니다."); 
	}
	else
	{
		msgText = GameStringDepot::getSingleton().getString("TXT_INFO_REPLAY_SAVE_ERROR") + "[ErrorCode:" + StringConverter::toString(resultCode) + "]";//U8("게임중이 아니라 실행할 수 없습니다."); 
	}
	panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ToastNotice, msgText);

	if (panel)
		LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
}

void GameRoomInfo::SetChangeBoss(char * data, int size)
{
	PlayerPoInfo res;
	res.ParseFromArray(data, size);

	if (m_PlayStatus != PlayStatus::PLAY_NO && m_PlayStatus != PlayStatus::PLAY_NEXT_READY && m_PlayStatus != PlayStatus::PLAY_READY)
		SetBoss(res.po());
}

void GameRoomInfo::ExeAfterResultUserInfoUI()
{
	// 결과 이상이면 바로 실행
	if (m_PlayStatus == PlayStatus::PLAY_RESULT || m_PlayStatus == PlayStatus::PLAY_NEXT_READY)
	{
		// 게등위 심의 위반, 보너스 칩 지급 제한
		/*PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
		string chipStr = "play" + StringConverter::toString(mChipCount);
		if (backGroundPanel->mPokerChip->hasAnimation(chipStr))
			backGroundPanel->mPokerChip->playAnimation(chipStr);

		if (m_IsGetChip)
		{
			PokerTopPanel* _bPanel = GetTopPanel();
			if (_bPanel)
			{
				_bPanel->TurnOnGetChip();
				m_IsGetChip = false;
			}
		}*/

		if (m_IsLevelUp)
		{
			m_IsLevelUp = false;
			PokerTopPanel* _bPanel = GetTopPanel();
			if (_bPanel)
			{
				_bPanel->ShowLevelUpEffect();
			}
		}

		if (m_RefillMoney > 0)
		{
			//skel_autorefill_start
			PokerTopPanel* _bPanel = GetTopPanel();
			if (_bPanel)
			{
				_bPanel->ShowAutoRefillEffect();
			}
			m_RefillMoney = 0;
		}
			

		if (m_IsCompleteQuest)
		{
			m_IsCompleteQuest = false;
			string msgText = GameStringDepot::getSingleton().getString("TXT_GAME_QUEST_COMPLETE");
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ToastNotice, msgText), DYNAMIC_PUSH_LAYER);
		}

		if (isCharacterEffect) {
			isCharacterEffect = false;
			PokerTopPanel* _bPanel = GetTopPanel();
			if (_bPanel)
			{
				PlayerData * playerData = GameDataManager::getSingletonPtr()->GetPlayerDataPtr();
				_bPanel->showCharacterEffect(playerData->m_CharacterIdx , m_madeMoney > 0);
			}
		}

		// 메이드 머니 추가 획득 했을때 캐릭터 근처에 획득한 메이드 머니 띄워주세요~
		if (m_madeMoney > 0)
		{
			PokerTopPanel* _bPanel = GetTopPanel();
			if (_bPanel)
			{
				_bPanel->ShowMadeBonusEffect();
			}

			m_madeMoney = 0;
		}		
	}
}

bool GameRoomInfo::MoveRoom(char * data, int size)
{
	EnterRoomSuccess res;
	res.ParseFromArray(data, size);

	PokerPlayerInfoPanel* _pPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("PlayerInfo"));
	if (_pPanel != nullptr)
	{
		if (isBigAnimation())
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_TENSION, false);
		}
		_pPanel->RemoveAllCharacter();
	}

	m_pDealerTextBubble->getSkel("skel_dealer_bubbler")->setVisible(false);
	m_pDealerTextBubble->getLabel("txt_dealer_speech_under")->setVisible(false);
	m_pDealerTextBubble->getLabel("txt_dealer_speech")->setVisible(false);
	RemoveDealer();
	

	for (int i = 0; i < GAME_USER_MAX; i++)
	{
		if (m_UserList[i] == nullptr)
			continue;
		
		PokerPlayerInfoCommonPanel* _pUserPanel = GetPlayerCommonPanel(i);
		if (_pUserPanel)
		{
			_pUserPanel->TurnOffPlayerRank();
			_pUserPanel->setEmptyPlayerInfo();
		}
		NX_SAFE_DELETE(m_UserList[i]);
		m_UserList[i] = nullptr;
	}

	SetData(&res);

	FightScene * scene = dynamic_cast<FightScene*>(SceneManager::getSingletonPtr()->getScene(SceneUtil::SceneFight));
	if (scene != nullptr)
		scene->FirstGameStateSetting();
	else
		return false;

	GetUserDataPtr(GetMyPo())->SetPlayerStatus(PlayerStatus::PLAYER_PREPARE);
	TCPService::getSingletonPtr()->SendNormalPacket(C2S_PREPARE_END_IDX);

	ActionPointer::createGameInfoShow(this, 1.f);

	//int _kind = EFX_DEALER_INCOME2 + (rand() % 2);
	//DealerSound((DealerEfxKind)_kind);
	int _kind = CharacterEfxKind::EFX_ENTER1 + (rand() % 2);
	GetUserDataPtr(GetMyPo())->PlayCharacterSound((CharacterEfxKind)_kind);

	Action_EnterRoomCharacter(GetMyPo());

	HideStartButton();

	MoveRoomEffect();

	return true;
}

void GameRoomInfo::MoveRoomEffect()
{
	if (SceneUtil::getCurrentSceneId() != SceneUtil::SceneFight)
		return;

	LayerManager::getSingletonPtr()->getLayer("Background")->runAction(CCSequence::create(
		CCFadeOut::create(0.f),
		CCDelayTime::create(0.2f),
		CCFadeIn::create(0.3f),
		NULL));
}


void GameRoomInfo::AddUser(RoomPlayerInfo * playerInfo)
{
	if (playerInfo == nullptr)
		return;

	cout << U8("ADD USER!!!!") << endl;
	//if (m_CurrentUser > m_MaxUser)
	//	return;

	int po = playerInfo->po();

	if (GetUserDataPtr(po))
		return;

	m_UserList[po] = new RoomUserData();
	//클라이언트 상의 위치 와 서버상의 위치를 저장.
	
	RoomUserData * userData = m_UserList[po];
	userData->m_Po = po;
	userData->m_pPlayerData = new PlayerData();
	userData->m_pPlayerData->SetData(playerInfo);

	userData->GetCardManager()->m_UserIdx = GameDataManager::getSingletonPtr()->ServerToClientIndex(po);
	userData->GetCardManager()->m_UserPo = po;

	userData->SetPlayerStatus(playerInfo->playerstatus());

	if (GetGameMode() != GameMode::MODE_NORMAL)
	{
		PokerPlayerInfoCommonPanel* _pUserPanel = GetPlayerCommonPanel(po);
		if (_pUserPanel)
		{
			if (playerInfo->userkind() == DUMMY_TNMT)
			{
				_pUserPanel->TurnOnPlayerDisconnect(playerInfo->disconnectcnt());
			}
			else
			{
				if (playerInfo->isrankdecide() == false)
				{
					_pUserPanel->TurnOnPlayerRank(playerInfo->rank(), false);
				}
			}
		}
	}

	cout << "유저 [" << playerInfo->nickname() << "] 를 추가하였습니다." << endl;
}

void GameRoomInfo::DeleteUser(int _po, int bossPo)
{
	m_BossPo = bossPo;

	m_CurrentUser--;	//유저 감소

	if (m_CurrentUser == 1)
	{
		HideStartButton();
	}
	
	if (!GetUserDataPtr(_po))
		return;

	NX_SAFE_DELETE(m_UserList[_po]);
	m_UserList[_po] = nullptr;

	
}

void GameRoomInfo::SetStatus(PlayStatus status)
{
	if (m_PlayStatus == PLAY_BETTING)
		InitOldBetting();

	m_PlayStatus = status;

	switch (m_PlayStatus)
	{
		case PLAY_NO:
			break;
		case PLAY_READY:
			TCPService::getSingletonPtr()->SendNormalPacket(CSProtocol::C2S_LOAD_END_IDX);
			break;
		case PLAY_BETTING_SEED_INIT :
			break;
		case PLAY_SHARE_CARD :
			m_isShareCardEnd = false;
			break;
		case PLAY_SHARE_CARD_WAIT:
			SetShareCardEnd();
			break;
		// 카드 초이스 상태로 전환해야 함.
		case PLAY_CARD_CHOICE :
			SetCardChoicePanel();
			break;
		case PLAY_BETTING :
			//TODO : 배팅 버튼 활성화.
			SetBettingInfoInit(false);
			break;
		case PLAY_JOKBO_CHOICE :
			if (m_GameKind == GameKind::GAMEKIND_HIGH_LOW)
				SetHighLowChoice(true);
			break;
		case PLAY_NEXT_READY :
			NextReadyProcess();
			break;
		case PLAY_SHARE_COMMUNITY_CARD:
			break;
		case PLAY_CHANGE_CARD:
			break;
	}
}

void GameRoomInfo::SetShareCardEnd()
{
	m_isShareCardEnd = true;

	if (m_isReplayData == false)
	{
		if (GetGameKind() == GameKind::GAMEKIND_BADUKI)
		{
			RoomUserData * userData = GetUserDataPtr(m_MyPo);
			if (userData->GetPlayerStatus() == PLAYER_INIT)
			{
				SetBadugiSortTime(0.5f);
			}
		}

		RoomUserData * userData = GetUserDataPtr(m_MyPo);
		if (userData != nullptr && userData->GetPlayerStatus() == PLAYER_INIT)
		{
			TCPService::getSingletonPtr()->SendNormalPacket(CSProtocol::C2S_SHARE_CARD_END_RES_IDX);
		}
	}
	else if(GetGameKind() == GameKind::GAMEKIND_BADUKI)
	{
		for (RoomUserData* userData : m_UserList)
		{
			if (userData == nullptr)
				continue;

			if (userData->GetPlayerStatus() == PLAYER_INIT)
			{
				if (m_MyPo == userData->m_Po)
					SetBadugiSortTime(0.5f);
				else
					userData->BadugiSortCard(0.5f);
			}
		}
	}
}

void GameRoomInfo::AddCard(char * data, int size)
{
	// 쉐어 카드 상태가 아닐때만 상태를 바꾼다.
	if (m_PlayStatus != PLAY_SHARE_CARD)
		SetStatus(PlayStatus::PLAY_SHARE_CARD);

	ShareCardInfoList res;
	ShareCardInfo shareCardInfo;
	res.ParseFromArray(data, size);

	if (res.sharecardinfo_size() <= 0)
	{
		shareCardInfo.ParseFromArray(data, size);
		CardInfo cardInfo;
		RoomUserData * userData;
		float _delayTime = 0.f;

		userData = GetUserDataPtr(shareCardInfo.po());

		if (userData == nullptr)
			return;

		for (int i = 0, j = shareCardInfo.cardinfo_size(); i < j; i++)
		{
			_delayTime += SHOW_ANI_TIME;

			cardInfo = shareCardInfo.cardinfo(i);
			if (cardInfo.cardnumber() != -1)
			{
				DealerAnimation(DealerAniKind::DEALER_DEALING_SHOOT);

				int _idx = userData->m_pCardManager->m_CardList.size();

				if (m_isSelectedCard == false)
				{
					userData->AddCard(cardInfo.cardnumber(), cardInfo.cardkind(), true, true, _delayTime);
				}
				else
				{
					if (m_isReplayData == true)
					{
						userData->AddCard(cardInfo.cardnumber(), cardInfo.cardkind(), false, true, _delayTime);
					}
					else
					{
						userData->AddCard(cardInfo.cardnumber(), cardInfo.cardkind(), _idx == 6, true, _delayTime);
					}
				}

				CCRect _move = userData->m_pCardManager->GetTableCardRect(_idx);
				if (m_isSelectedCard == false)
					userData->m_pCardManager->ActionShareMoveCard(_idx, _move.origin, true, _delayTime);
				else
					userData->m_pCardManager->ActionShareMoveCard(_idx, _move.origin, false, _delayTime);

				if (shareCardInfo.po() == m_MyPo && m_isSelectedCard == true)
				{
					//MyMadeCheck();
					if (userData->m_pCardManager->IsLastCard() == false || !isBigAnimation() || GameDataManager::getSingletonPtr()->m_pOptionValue->m_hiddenCard == false)
					{
						SetMyMadeCheckTime(0.5f + _delayTime);
					}
				}

				if (_idx == 3 && shareCardInfo.po() == m_MyPo && m_isSelectedCard == false && m_isReplayData == false)
				{
					SetIsSelectedCard();
					//GetPlayerCommonPanel(m_MyPo)->SetShareEndCard();
				}
				//cout << "User : " << res.po() << " card(number/kind) : " << cardInfo.cardnumber() << "/" << cardInfo.cardkind() << "\n\n" << endl;
			}
		}

		SetBoss(shareCardInfo.bosspo());

		return;
	}
	
	CardInfo cardInfo;
	RoomUserData * userData;
	float _delayTime = 0.f;
	for (int k = 0, l = res.sharecardinfo_size(); k < l; k++)
	{
		shareCardInfo = res.sharecardinfo(k);

		userData = GetUserDataPtr(shareCardInfo.po());
		CCLOG("________________________________________________________________________shareCardInfo.po() = %d , playerdata = %s", shareCardInfo.po(), userData->m_pPlayerData->m_NickName.c_str());

		if (userData == nullptr)
			continue;


		for (int i = 0, j = shareCardInfo.cardinfo_size(); i < j; i++)
		{
			_delayTime += SHOW_ANI_TIME;

			cardInfo = shareCardInfo.cardinfo(i);
			if (cardInfo.cardnumber() != -1)
			{
				DealerAnimation(DealerAniKind::DEALER_DEALING_SHOOT);

				int _idx = userData->m_pCardManager->m_CardList.size();

				if (m_isSelectedCard == false)
				{
					userData->AddCard(cardInfo.cardnumber(), cardInfo.cardkind(), true, true, _delayTime);
				}
				else
				{
					if (m_isReplayData == true)
					{
						userData->AddCard(cardInfo.cardnumber(), cardInfo.cardkind(), false, true, _delayTime);
					}
					else
					{
						userData->AddCard(cardInfo.cardnumber(), cardInfo.cardkind(), _idx == 6, true, _delayTime);
					}
				}

				CCRect _move = userData->m_pCardManager->GetTableCardRect(_idx);
				if (m_isSelectedCard == false)
					userData->m_pCardManager->ActionShareMoveCard(_idx, _move.origin, true, _delayTime);
				else
					userData->m_pCardManager->ActionShareMoveCard(_idx, _move.origin, false, _delayTime);

				if (shareCardInfo.po() == m_MyPo && m_isSelectedCard == true)
				{
					//MyMadeCheck();
					if (userData->m_pCardManager->IsLastCard() == false || !isBigAnimation() || GameDataManager::getSingletonPtr()->m_pOptionValue->m_hiddenCard == false)
					{
						SetMyMadeCheckTime(0.5f + _delayTime);
					}
				}

				if (_idx == 3 && shareCardInfo.po() == m_MyPo && m_isSelectedCard == false && m_isReplayData == false)
				{
					SetIsSelectedCard();
					//GetPlayerCommonPanel(m_MyPo)->SetShareEndCard();
				}
				//cout << "User : " << res.po() << " card(number/kind) : " << cardInfo.cardnumber() << "/" << cardInfo.cardkind() << "\n\n" << endl;
			}
		}

		if (k == 0)
			SetBoss(shareCardInfo.bosspo());
	}
	
}

void GameRoomInfo::SetBadugiSortTime(float _delay)
{
	m_badugiSortedCard = true;
	m_badugiSortDelay = _delay;
}

void GameRoomInfo::UpdateBadugiSortCheck(float _dt)
{
	if (!m_badugiSortedCard)
		return;

	if (m_badugiSortDelay <= 0)
	{
		m_badugiSortedCard = false;
		m_badugiSortDelay = 0.f;
		MyBadugiMadeCheck();
	}
	m_badugiSortDelay -= _dt;
}

void GameRoomInfo::SetMyMadeCheckTime(float _delay)
{
	m_myMadeCheck = true;
	m_myMadeCheckDelay = _delay;
}


void GameRoomInfo::UpdateMyMadeCheck(float _dt)
{
	if (!m_myMadeCheck)
		return;

	if (m_myMadeCheckDelay <= 0)
	{
		m_myMadeCheck = false;
		m_myMadeCheckDelay = 0.f;
		if (m_GameKind == GameKind::GAMEKIND_HOLDEM)
		{
			MyHoldemCheck();
		}
		else
		{
			MyMadeCheck();
		}
	}
	m_myMadeCheckDelay -= _dt;	

}

void GameRoomInfo::MyBadugiMadeCheck()
{
	//int yetBadugiJokbo = GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetLowJokboKind();
	GetUserDataPtr(m_MyPo)->BadugiSortCard();
	int curBadugiJokbo = GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetLowJokboKind();

	SetMyBadugiJokbo((LowJokboKind)curBadugiJokbo);
	bool _MadeCheck = false;
	int badugiMadeJokbo = LowJokboKind::LOW_NO;

	for (CardData* _CardData : GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList)
	{
		_CardData->m_pCard->setTag(0);
	}

	if (curBadugiJokbo != LowJokboKind::LOW_NO && curBadugiJokbo <= LowJokboKind::BADUKI_K_TOP)
	{
		//if (yetBadugiJokbo == LowJokboKind::LOW_NO || yetBadugiJokbo >= curBadugiJokbo)
		{
			badugiMadeJokbo = curBadugiJokbo;
			GetUserDataPtr(m_MyPo)->PlayCharacterAnimation(REACT_MADE);

			//_MadeCheck = true;
			for (CardData* _CardData : GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetLowJokboCardList())
			{
				_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_STARDUST);
				_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_EXPLORE);
				_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_NO, 1.f);
				_CardData->m_pCard->setTag(1);
			}
		}
	}

	//Show Made effect
	//if (_MadeCheck == true)
	//{
	for (CardData* _CardData : GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList)
	{
		int _cardPo = _CardData->m_pCard->GetCardPo();
		int _endCardPo = GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList.back()->m_pCard->GetCardPo();
		float _cardCount = _endCardPo - _cardPo;
		CCPoint _cardStartPos = GetUserDataPtr(m_MyPo)->GetCardManager()->GetTableCardRect(_CardData->m_idx).origin;
		CCPoint _cardMovePos = _cardStartPos + ccp(0, 15.f);

		if (_CardData->m_pCard->getTag() == 0)
		{
			_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_NO);
			_CardData->m_pCard->setTag(-1);
		}
		else if (_CardData->m_pCard->getTag() == 1)
		{
			_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_MADE, 1.2f + _cardCount*0.05f);
			_CardData->m_pCard->Action_ShowMadeCard(1.f + _cardCount*0.05f, _cardMovePos, 2.f, _cardStartPos);
			_CardData->m_pCard->setTag(-1);
		}
	}
	//}


	if (badugiMadeJokbo != LowJokboKind::LOW_NO)
	{
		PokerPlayerInfoPanel* _pInfoPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingleton().getLayer("PlayerInfo"));
		PokerPlayerInfoCommonPanel*  _panel = dynamic_cast<PokerPlayerInfoCommonPanel*>(_pInfoPanel->GetPlayerCommonPanel(m_MyPo));
		_panel->ShowMade((int)GameKind::GAMEKIND_BADUKI, HighJokboKind::HIGH_NO, curBadugiJokbo);
	}

	PokerPlayerInfoCommonPanel*  _panel = GetPlayerCommonPanel(m_MyPo);
	if (_panel != nullptr)
	{
		_panel->TurnOnJokboInfo(GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetBadukiJokboString());
	}

	GetUserDataPtr(m_MyPo)->SelectBadugiRecommendCard();
	GetUserDataPtr(m_MyPo)->SetBadugiSelectedCardEffect(0.f);

	if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel"))
	{
		BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));

		for (int _i = 0; _i < 4; _i++)
		{
			bool _touch = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_i];
			_pSelectCardPanel->SetSeletBtn(_i, _touch);
		}
		_pSelectCardPanel->ApplyChangeButtonState();
	}
	
}

void GameRoomInfo::MyHoldemCheck()
{
	int yetHighJokbo = GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetHighJokboKind();
	GetUserDataPtr(m_MyPo)->m_pJokboInfo->HoldemJokboCheck();
	int curHighJokbo = GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetHighJokboKind();
	SetMyHighJokbo((HighJokboKind)curHighJokbo);

	bool _MadeCheck = false;
	CCLOG("MyHoldemCheck init");
	int highMadeJokbo = HighJokboKind::HIGH_NO;
	int lowMadeJokbo = LowJokboKind::LOW_NO;
	if (curHighJokbo != HighJokboKind::HIGH_NO && curHighJokbo <= HighJokboKind::HIGH_TRIPLE)
	{
		if (yetHighJokbo == HighJokboKind::HIGH_NO || yetHighJokbo > curHighJokbo)
		{
			highMadeJokbo = curHighJokbo;
			GetUserDataPtr(m_MyPo)->PlayCharacterAnimation(REACT_MADE);
			mMadeJokbo = curHighJokbo;
			CCLOG("mMadeJokbo = %d", mMadeJokbo);
			_MadeCheck = true;
			for (CardData* _CardData : GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList)
			{
				_CardData->m_pCard->setTag(0);
			}

			for (CardData* _CardData : GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetHighJokboCardList())
			{
				if (GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList.back()->m_pCard->GetCardId() == _CardData->m_pCard->GetCardId())
				{
					_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_STARDUST);
					_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_EXPLORE);
					_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_NO, 1.f);
				}

				if (curHighJokbo == HighJokboKind::HIGH_TRIPLE || curHighJokbo == HighJokboKind::HIGH_FOUR_CARD)
				{
					auto _beginCard = GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetHighJokboCardList().at(0);
					if (_CardData->m_Number == _beginCard->m_Number)
					{
						_CardData->m_pCard->setTag(1);
					}
				}
				else
				{
					_CardData->m_pCard->setTag(1);
				}
			}
		}
	}

	if (_MadeCheck == true)
	{
		for (CardData* _CardData : GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList)
		{
			int _cardPo = _CardData->m_pCard->GetCardPo();
			int _endCardPo = GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList.back()->m_pCard->GetCardPo();
			float _cardCount = _endCardPo - _cardPo;
			CCPoint _cardStartPos = GetUserDataPtr(m_MyPo)->GetCardManager()->GetTableCardRect(_cardPo).origin;
			CCPoint _cardMovePos = _cardStartPos + ccp(0, 15.f);

			if (_CardData->m_pCard->getTag() == 0)
			{
				_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_NO);
				_CardData->m_pCard->setTag(-1);
			}
			else if (_CardData->m_pCard->getTag() == 1 || _CardData->m_pCard->getTag() == 2 || _CardData->m_pCard->getTag() == 3)
			{
				_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_MADE, 1.2f + _cardCount*0.05f);
				_CardData->m_pCard->Action_ShowMadeCard(1.f + _cardCount*0.05f, _cardMovePos, 2.f, _cardStartPos);
				_CardData->m_pCard->setTag(-1);
			}
		}

		for (CardData* _CardData : m_CommunityCardList)
		{
			if (_CardData->m_pCard->getTag() == 0)
			{
				_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_NO);
				_CardData->m_pCard->setTag(-1);
			}
			else if (_CardData->m_pCard->getTag() == 1 || _CardData->m_pCard->getTag() == 2 || _CardData->m_pCard->getTag() == 3)
			{
				if (m_isBigCommunityCard == true)
				{
					_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_MADE, 1.2f);
					_CardData->m_pCard->setTag(-1);
				}
				else
				{
					_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_SMALL_MADE1 + _CardData->m_idx, 1.2f);
					_CardData->m_pCard->setTag(-1);
				}
				
			}
		}
	}


	if (highMadeJokbo != HighJokboKind::HIGH_NO)
	{
		PokerPlayerInfoPanel* _pInfoPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingleton().getLayer("PlayerInfo"));
		PokerPlayerInfoCommonPanel*  _panel = dynamic_cast<PokerPlayerInfoCommonPanel*>(_pInfoPanel->GetPlayerCommonPanel(m_MyPo));
		_panel->ShowMade((int)m_GameKind, highMadeJokbo, lowMadeJokbo);
	}

	PokerPlayerInfoCommonPanel*  _panel = GetPlayerCommonPanel(m_MyPo);
	if (_panel != nullptr)
	{
		_panel->TurnOnJokboInfo(GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetFullJokboString());
	}
}

void GameRoomInfo::MyMadeCheck()
{
	//현재 카드 포시젼이 마지막 카드 이고 auto 가 자동이 아니면 체크 하지 말고
	//열었을때... 체크 한다.
	if (GetUserDataPtr(m_MyPo)->GetCardManager()->IsLastCard()) {
		if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_hiddenCard) {  
			if(mShowTouchPanel == false)
				return;			
		}		
	}

	//메이드 체크.
	int yetHighJokbo = GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetHighJokboKind();
	int yetLowJokbo = LowJokboKind::LOW_NO;

	GetUserDataPtr(m_MyPo)->m_pJokboInfo->HighJokboCheck();
	int curHighJokbo = GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetHighJokboKind();
	int curLowJokbo = yetLowJokbo;
	SetMyHighJokbo((HighJokboKind)curHighJokbo);
	if (m_GameKind == GameKind::GAMEKIND_HIGH_LOW)
	{
		yetLowJokbo = GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetLowJokboKind();
		GetUserDataPtr(m_MyPo)->m_pJokboInfo->LowJokboCheck();
		curLowJokbo = GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetLowJokboKind();
		SetMyLowJokbo((LowJokboKind)curLowJokbo);
	}

	bool _MadeCheck = false;
	CCLOG("MyMadeCheck init");
	int highMadeJokbo = HighJokboKind::HIGH_NO;
	int lowMadeJokbo = LowJokboKind::LOW_NO;
	if (curHighJokbo != HighJokboKind::HIGH_NO && curHighJokbo <= HighJokboKind::HIGH_TRIPLE)
	{
		if (yetHighJokbo == HighJokboKind::HIGH_NO || yetHighJokbo > curHighJokbo)
		{
			highMadeJokbo = curHighJokbo;
			GetUserDataPtr(m_MyPo)->PlayCharacterAnimation(REACT_MADE);
			mMadeJokbo = curHighJokbo;
			CCLOG("mMadeJokbo = %d", mMadeJokbo);
			_MadeCheck = true;
			for (CardData* _CardData : GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList)
			{
				_CardData->m_pCard->setTag(0);
			}

			for (CardData* _CardData : GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetHighJokboCardList())
			{
				if (GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList.back()->m_pCard->GetCardId() == _CardData->m_pCard->GetCardId())
				{
					_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_STARDUST);
					_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_EXPLORE);
					_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_NO, 1.f);
				}
				if (curHighJokbo == HighJokboKind::HIGH_TRIPLE || curHighJokbo == HighJokboKind::HIGH_FOUR_CARD)
				{
					auto _beginCard = GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetHighJokboCardList().at(0);
					if (_CardData->m_Number == _beginCard->m_Number)
					{
						_CardData->m_pCard->setTag(1);
					}
				}
				else
				{
					_CardData->m_pCard->setTag(1);
				}
			}
		}
	}

	if (curLowJokbo != LowJokboKind::LOW_NO && curLowJokbo <= LowJokboKind::LOW_EIGHT_TOP)
	{
		if (yetLowJokbo == LowJokboKind::LOW_NO || yetLowJokbo > curLowJokbo)
		{
			lowMadeJokbo = curLowJokbo;
			GetUserDataPtr(m_MyPo)->PlayCharacterAnimation(REACT_MADE);
			mMadeJokbo = curLowJokbo;
			CCLOG("No mMadeJokbo = %d", mMadeJokbo);
			_MadeCheck = true;
			for (CardData* _CardData : GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList)
			{
				if (_CardData->m_pCard->getTag() != 1)
				{
					_CardData->m_pCard->setTag(0);
				}
				/*_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_NO_MADE);*/
			}

			for (CardData* _CardData : GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetLowJokboCardList())
			{
				if (GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList.back()->m_pCard->GetCardId() == _CardData->m_pCard->GetCardId())
				{
					_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_STARDUST);
					_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_EXPLORE);
					_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_NO, 1.f);
				}

				if (curHighJokbo == HighJokboKind::HIGH_FOUR_CARD)
				{
					auto _beginCard = GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetHighJokboCardList().at(0);
					if (_CardData->m_Number == _beginCard->m_Number)
					{
						if (_CardData->m_pCard->getTag() == 1)
						{
							_CardData->m_pCard->setTag(3);
						}
						else
						{
							_CardData->m_pCard->setTag(2);
						}
					}
				}
				else
				{
					if (_CardData->m_pCard->getTag() == 1)
					{
						_CardData->m_pCard->setTag(3);
					}
					else
					{
						_CardData->m_pCard->setTag(2);
					}
				}
			}
		}
	}

	//Show Made effect
	if (_MadeCheck == true)
	{
		for (CardData* _CardData : GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList)
		{
			int _cardPo = _CardData->m_pCard->GetCardPo();
			int _endCardPo = GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList.back()->m_pCard->GetCardPo();
			float _cardCount = _endCardPo - _cardPo;
			CCPoint _cardStartPos = GetUserDataPtr(m_MyPo)->GetCardManager()->GetTableCardRect(_cardPo).origin;
			CCPoint _cardMovePos = _cardStartPos + ccp(0, 15.f);

			if (_CardData->m_pCard->getTag() == 0)
			{
				_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_NO_MADE);
				_CardData->m_pCard->setTag(-1);
			}
			else if (_CardData->m_pCard->getTag() == 1 || _CardData->m_pCard->getTag() == 2 || _CardData->m_pCard->getTag() == 3)
			{
				_CardData->m_pCard->PlayCardEffect(CARD_EFFECT_MADE, 1.2f + _cardCount*0.05f);
				_CardData->m_pCard->Action_ShowMadeCard(1.f + _cardCount*0.05f, _cardMovePos, 2.f, _cardStartPos);
				_CardData->m_pCard->setTag(-1);
			}
		}
	}


	if (highMadeJokbo != HighJokboKind::HIGH_NO || lowMadeJokbo != LowJokboKind::LOW_NO)
	{
		PokerPlayerInfoPanel* _pInfoPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingleton().getLayer("PlayerInfo"));
		PokerPlayerInfoCommonPanel*  _panel = dynamic_cast<PokerPlayerInfoCommonPanel*>(_pInfoPanel->GetPlayerCommonPanel(m_MyPo));
		_panel->ShowMade((int)m_GameKind, highMadeJokbo, lowMadeJokbo);
	}

	PokerPlayerInfoCommonPanel*  _panel = GetPlayerCommonPanel(m_MyPo);
	if (_panel != nullptr)
	{
		_panel->TurnOnJokboInfo(GetUserDataPtr(m_MyPo)->m_pJokboInfo->GetFullJokboString());
	}
}

void GameRoomInfo::ChangeCards(char * data, int size)
{
	ShareCardInfo res;
	res.ParseFromArray(data, size);

	RoomUserData * userData = GetUserDataPtr(res.po());

	if (userData == nullptr)
		return;

	if (res.po() == m_MyPo)
	{
		//카드 선택창 제거.
		BettingCardOnOffPanel* _pBettingPanel = dynamic_cast<BettingCardOnOffPanel*>(LayerManager::getSingleton().getLayer("CardOnOffPanel"));
		_pBettingPanel->ClosePanel();
		userData->setMyCharacterVisible(true);
	}
	else
	{
		userData->PlayThinkAnimation(0.f, false);
		GetPlayerCommonPanel(userData->m_Po)->turnOffTimeGauge();
	}

	userData->ClearCardList();
	userData->PlayCharacterAnimation(IDLE);

	CardInfo cardInfo;
	for (int i = 0, j = res.cardinfo_size(); i < j; i++)
	{
		cardInfo = res.cardinfo(i);

		if (i == 2)
		{
			if (cardInfo.cardnumber() != -1)
				userData->AddCard(cardInfo.cardnumber(), cardInfo.cardkind(), true);

			if (userData->m_isMe == false)
				userData->GetCardManager()->ActionFlipCard(2, true, 0);
			else
				userData->GetCardManager()->m_CardList[2]->m_pCard->SetFront();
		}
		else
		{
			if (cardInfo.cardnumber() != -1)
				userData->AddCard(cardInfo.cardnumber(), cardInfo.cardkind());
		}

	}
}

void GameRoomInfo::InitOldBetting()
{
	PokerPlayerInfoCommonPanel* _pPlayerPanel;

	for (int i = 0, j = GAME_USER_MAX; i < j; i++)
	{
		if (m_UserList[i] == nullptr)
			continue;

		_pPlayerPanel = GetPlayerCommonPanel(i);
		if (_pPlayerPanel == nullptr)
			continue;

		_pPlayerPanel->SetBetting(BettingKind::BETTING_NO, false, -1);
	}
}

void GameRoomInfo::SetBettingState(char * data, int size)
{
	BettingState res;
	res.ParseFromArray(data, size);
	SetBoss(res.bosspo());

	PokerPlayerInfoPanel* _pPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingleton().getLayer("PlayerInfo"));

	_pPanel->SetAllUserBettingAmountInit();

	RoomUserData * userData = GetUserDataPtr(m_MyPo);
	if (userData == nullptr)
		return;

	if (m_isReplayData == false)
	{
		if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_hiddenCard == false)
		{
			userData->LastCardCheck(false);
		}
		else
		{
			userData->LastCardCheck(true);
		}
	}

	SetStatus(PlayStatus::PLAY_BETTING);
}

void GameRoomInfo::InitCanMyBettingKind()
{
	for (int i = 0; i < BETTING_KIND_CNT; i++)
		m_CanMyBettingKind[i] = false;
}

void GameRoomInfo::InitCanBettingPanel()
{
	BettingSevenPokerPanel * _pPanel = GetBettingSevenPokerPanel();
	if (_pPanel != nullptr)
	{
		_pPanel->InitCanBetting();
	}
}

void GameRoomInfo::SetCanMyBettingKind(char * data , int size)
{
	CurBettingInfo res;
	res.ParseFromArray(data, size);

	int po = res.po();
	m_BetPo = po;

	//프로그래스바 설정.
	PokerPlayerInfoPanel* _pPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingleton().getLayer("PlayerInfo"));
	PokerPlayerInfoCommonPanel* _pPlayerPanel = dynamic_cast<PokerPlayerInfoCommonPanel*>(_pPanel->GetPlayerCommonPanel(m_BetPo));
	if (_pPlayerPanel)
	{
		_pPlayerPanel->turnOnTimeGauge();

		//if (IsBigGame())

		//int _randValue = CharacterAniKind::THINK1 + ( rand() % 2 );
		//GetUserDataPtr(m_BetPo)->PlayCharacterAnimation((CharacterAniKind)_randValue);
		GetUserDataPtr(m_BetPo)->PlayThinkAnimation(5.f);

		m_isBettingCount = true;
	}

	if (po != m_MyPo || m_isReplayData == true)
		return;
		
	TCPService::getSingletonPtr()->SendNormalPacket(C2S_BETTING_TIMECOUNT_START_IDX);
	InitCanMyBettingKind();

	BettingSevenPokerPanel  * bettingPanel = GetBettingSevenPokerPanel();

	bettingPanel->InitCanBetting();

	for (int i = 0, j = res.canbettingkind_size(); i < j; i++)
	{
		m_CanMyBettingKind[res.canbettingkind(i)] = true;
		bettingPanel->SetCanBetting(res.canbettingkind(i), true);
	}
	bettingPanel->MovePanel(true);



	bettingPanel->SetBettingMoney(GetTotalBettingMoney(m_MyPo, BettingKind::QUARTER, true), GetTotalBettingMoney(m_MyPo, BettingKind::HALF, true), GetTotalBettingMoney(m_MyPo, BettingKind::MAX_BETTING, true));
	SetMyCallMoney();
}

int GameRoomInfo::GetCanPlayerCnt()
{
	int _cnt = 0;
	for (int _i = 0; _i < GAME_USER_MAX; _i++)
	{
		if (m_UserList[_i] == nullptr)
			continue;

		//if (_i != m_MyPo)
		if (m_UserList[_i]->GetPlayerStatus() == PlayerStatus::PLAYER_INIT)
			_cnt++;
	}

	return _cnt;
}

void GameRoomInfo::SetPlayerOutReserve(char * data, int size)
{
	// 이런 상황은 무시한다.
	if (m_PlayStatus <= PLAY_READY || m_PlayStatus >= PLAY_NEXT_READY)
		return;

	
	PlayerOutReserveRes res;
	res.ParseFromArray(data, size);

	PlayerPoInfo poInfo = res.playerpoinfo();
	PlayerOutResrvKind reserveKind = res.reservekind();
	int po = poInfo.po();

	if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(po)->m_PlayerOutResrvKind == PlayerOutResrvKind::RESERVE_PUT_OUT)
	{
		if (reserveKind == RESERVE_PLAYER_OUT)
		{
			return;
		}
	}

	if (po == m_MyPo)
	{
		PokerTopPanel * _pTopPanel = GetTopPanel();
		if (reserveKind == PlayerOutResrvKind::RESERVE_PLAYER_OUT)
		{
			m_ExitReserve = true;
			if (_pTopPanel != nullptr)
				_pTopPanel->SetPressExitReserveButton();
		}
		else
		{
			m_ExitReserve = false;
			if (_pTopPanel != nullptr)
				_pTopPanel->SetPressExitFailButton();
		}

		_pTopPanel->SetOutButtonClick(false);
	}

	PokerPlayerInfoCommonPanel * _pCommonPanel = GetPlayerCommonPanel(po);
	if (_pCommonPanel != nullptr)
	{
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(po)->m_PlayerOutResrvKind = reserveKind;
		if (reserveKind == PlayerOutResrvKind::RESERVE_PLAYER_OUT)
		{
			_pCommonPanel->TurnOnGameOut(0);
			
		}
		else if (reserveKind == PlayerOutResrvKind::RESERVE_PUT_OUT)
		{
			_pCommonPanel->TurnOnGameOut(1);
		}
		else
		{
			_pCommonPanel->TurnOffGameOut();
		}
	}
}

int64 GameRoomInfo::CalcMyBettingMoney(int64 myMoney, int64 addMoney)
{
	//m_preUserBetMoney = addMoney;
	myMoney += addMoney;

	return myMoney;
}

int64 GameRoomInfo::GetTotalBettingMoney(int po, BettingKind betKind, bool isReal)
{
	if (m_UserList[po] == nullptr)
		return 0;

	// 나의 현재 콜머니
	int64 myBettingMoney = m_BetMoney - m_UserList[po]->GetBettingMoney();
	// 내 콜 머니를 더했을 때 나오는 최종 팟머니
	int64 tmpPotMoney = m_PotMoney + myBettingMoney;

	// 게임에 따른 비용 계산

	// 배팅 데이터 처리
	switch (betKind)
	{
		case CHECK:
		case DIE:
			myBettingMoney = 0;
			break;
		case BBING:
		case HALF:
		case QUARTER:
		case DDADANG:
		case MAX_BETTING :
			myBettingMoney = CalcMyBettingMoney(myBettingMoney, GetBettingMoney(betKind, tmpPotMoney));
			break;
		default: break;
	}
	// 현재 소유금액까지 감안한 배팅 금액
	if (isReal)
	{
		if (myBettingMoney > 0)
		{
			int64 userMoney = m_UserList[po]->m_pPlayerData->m_GameMoney;

			if (userMoney == 0)
				myBettingMoney = 0;
			else if (userMoney < myBettingMoney)
				myBettingMoney = userMoney;
		}
	}

	return myBettingMoney;
}

int64 GameRoomInfo::GetBettingMoney(BettingKind betKind, int64 potMoney)
{
	switch (betKind)
	{
	case BBING:
		return m_SeedMoney;
	case HALF:
		return potMoney / 2;
	case QUARTER:
		return potMoney / 4;
	case DDADANG:
		return m_preUserBetMoney * 2;
	case MAX_BETTING:
		return GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetMaxBetMoney();
	}

	return 0;
}


void GameRoomInfo::_initDealerfee()
{
	int _size = 0;
	W_ChannelInfo* _pInfo = nullptr;

	if (!m_GameMode == GameMode::MODE_NORMAL) {
		Dealerfee = 0;
		return;
	}

	if (m_GameKind == GAMEKIND_7POKER)
	{
		_size = GameDataManager::getSingletonPtr()->m_p7PokerChannelList.size();
	}
	else if (m_GameKind == GAMEKIND_HIGH_LOW)
	{
		_size = GameDataManager::getSingletonPtr()->m_pHighLowChannelList.size();
	}
	else if (m_GameKind == GAMEKIND_BADUKI)
	{
		_size = GameDataManager::getSingletonPtr()->m_pBadukiChannelList.size();
	}
	else if (m_GameKind == GAMEKIND_HOLDEM)
	{
		_size = GameDataManager::getSingletonPtr()->m_pHoldemChannelList.size();
	}

	for (int _i = 0; _i < _size; _i++)
	{
		
		if (m_GameKind == GAMEKIND_7POKER)
		{
			_pInfo = GameDataManager::getSingletonPtr()->m_p7PokerChannelList[_i];
		}
		else if (m_GameKind == GAMEKIND_HIGH_LOW)
		{
			_pInfo = GameDataManager::getSingletonPtr()->m_pHighLowChannelList[_i];
		}
		else if (m_GameKind == GAMEKIND_BADUKI)
		{
			_pInfo = GameDataManager::getSingletonPtr()->m_pBadukiChannelList[_i];
		}
		else if (m_GameKind == GAMEKIND_HOLDEM)
		{
			_pInfo = GameDataManager::getSingletonPtr()->m_pHoldemChannelList[_i];
		}
	}

	DealerPercent = _pInfo->dealerfee()/100.0;
	CCLOG("\ndealerfee = %f\n", DealerPercent);
}

BettingSevenPokerPanel * GameRoomInfo::GetBettingSevenPokerPanel()
{
	if (!LayerManager::getSingleton().hasLayer("BettingPanel"))
		return nullptr;

	BettingSevenPokerPanel * panel = dynamic_cast<BettingSevenPokerPanel*>(LayerManager::getSingleton().getLayer("BettingPanel"));
	return panel;
}

PokerResultPanel * GameRoomInfo::GetPokerResultPanel()
{
	PokerResultPanel* _pPanel = nullptr;
	if (LayerManager::getSingleton().hasLayer("ResultLayer"))
		_pPanel = dynamic_cast<PokerResultPanel*>(LayerManager::getSingleton().getLayer("ResultLayer"));
	return _pPanel;
}

PokerTopPanel * GameRoomInfo::GetPokerTopPanel()
{
	PokerTopPanel* _pPanel = nullptr;
	if (LayerManager::getSingleton().hasLayer("TopLayer"))
		_pPanel = dynamic_cast<PokerTopPanel*>(LayerManager::getSingleton().getLayer("TopLayer"));
	return _pPanel;
}

void GameRoomInfo::SetPotMoney(int64 potMoney, int64 betMoney)
{
	if (potMoney == 0)
	{
		PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
		m_PotMoney = potMoney;
		if (backGroundPanel) {
			backGroundPanel->setTotalBettingMoney(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(potMoney), 2));
		}
		return;
	}

	if (betMoney > 0)
	{
		//if (m_PotMoneyEffectState == PotMoneyState::POT_READY || m_PotMoneyEffectState == PotMoneyState::POT_UPDATE)
		//{
		//	//m_PrePotMoneyUpdateList.push(m_PotMoney);
		//	
		//}
		//else
		//{
		//	m_PrePotMoney = m_PotMoney;
		//	m_UpdatePotMoney = potMoney;
		//	m_fPotMoneyEffectTime = POT_EFFECT_TIME;
		//	m_fPotMoneyUpdateTime = 0.f;
		//	m_PotMoneyEffectState = PotMoneyState::POT_READY;
		//	
		//}
		m_PreMoneyUpdateList.push_back(m_PotMoney);
		m_PotMoneyUpdateList.push_back(betMoney);
	}
	
	m_PotMoney = potMoney;
	SetBettingAmount(potMoney);
}

void GameRoomInfo::SetMyCallMoney()
{
	SetCallAmount(GetTotalBettingMoney(m_MyPo, BettingKind::CALL, true));
}

void GameRoomInfo::SetCallAmount(int64 _money)
{
	PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
	if (backGroundPanel) {
		backGroundPanel->setCallBettingMoney(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_money), 2));
	}
}

void GameRoomInfo::SetBettingAmount(int64 _money)
{
	//PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
	//if (backGroundPanel) {
	//	backGroundPanel->setTotalBettingMoney(GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_money)));
	//}

	if (LayerManager::getSingleton().hasLayer("PotMoney"))
	{
		PotMoneyPanel* _potMoneyPanel = dynamic_cast<PotMoneyPanel*>(LayerManager::getSingletonPtr()->getLayer("PotMoney"));
		if (_potMoneyPanel)
		{
			_potMoneyPanel->SetMoney(_money);

			if (IsBigGame())
			{
				ShowBigGameEffect();
			}
			//else if (_money != 0)
		}
	}
}


void GameRoomInfo::BettingChoice(BettingKind _kind)
{
	if (m_MyPo != m_BetPo)
		return;

	BettingKind kind;
	int64 bettingMoney = 0;
	if (GameDataManager::getSingletonPtr()->m_isTraditionalHoldem)
	{
		if (_kind == BettingKind::CHECK)
			kind = BettingKind::HOLDEM_CHECK;
		else if (_kind == BettingKind::CALL)
			kind = BettingKind::HOLDEM_CALL;
		else if (_kind == BettingKind::BBING)
		{
			bettingMoney = m_SeedMoney;
			kind = BettingKind::HOLDEM_BETTING;
		}
		else if (_kind == BettingKind::DDADANG)
		{
			bettingMoney = m_SeedMoney;
			kind = BettingKind::HOLDEM_RAIZE;
		}
		else if (_kind == BettingKind::QUARTER)
			kind = BettingKind::HOLDEM_RAIZE;
		else if (_kind == BettingKind::HALF)
			kind = BettingKind::HOLDEM_RAIZE;
		else if (_kind == BettingKind::DIE)
			kind = BettingKind::HOLDEM_FOLD;
		else if (_kind == BettingKind::MAX_BETTING)
			kind = BettingKind::HOLDEM_RAIZE;
	}

	

	switch (_kind)
	{
		case HOLDEM_BETTING :
			bettingMoney = m_PotMoney / 4;
			break;
		case HOLDEM_RAIZE :
			bettingMoney = m_PotMoney / 2;
			break;
	}

	TCPService::getSingletonPtr()->SendBettingReq(_kind, bettingMoney);

	PokerPlayerInfoCommonPanel* _pPlayerPanel = GetPlayerCommonPanel(m_BetPo);
	if (_pPlayerPanel)
	{
		GetUserDataPtr(m_BetPo)->PlayThinkAnimation(0.f, false);
		_pPlayerPanel->turnOffTimeGauge();
		m_isBettingCount = false;
	}

	//만약 hidden 이 있다면
	if (GetTopPanel()->m_HiddenTouchPanel->isVisible() || GetTopPanel()->mHiddenBigTouchPanel->isVisible()) {
		initHiddenTouchPanel();
		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->TouchHiddenCard();
	}
}

void GameRoomInfo::HighLowBettingChoice(HighLowBettingKind _kind)
{
	BettingHighLowPanel * _pPanel = GetHighLowPanel();

	if (_pPanel != nullptr)
		_pPanel->InitHighLowButton();

	switch (_kind)
	{
	case HighLowBettingKind::HIGH_BET:
		GetUserDataPtr(m_MyPo)->PlayCharacterSound(EFX_HIGH);
		break;
	case HighLowBettingKind::LOW_BET:
		GetUserDataPtr(m_MyPo)->PlayCharacterSound(EFX_LOW);
		break;
	case HighLowBettingKind::SWING_BET:
		GetUserDataPtr(m_MyPo)->PlayCharacterSound(EFX_SWING);
		break;
	}

	TCPService::getSingletonPtr()->SendHighLowBettingReq(m_MyPo, _kind);
}

PokerBackgroundPanel * GameRoomInfo::GetBackgroundPanel()
{
	if (!LayerManager::getSingleton().hasLayer("Background"))
		return nullptr;

	PokerBackgroundPanel* _pBackLayer = dynamic_cast<PokerBackgroundPanel*>(LayerManager::getSingleton().getLayer("Background"));
	return _pBackLayer;
}

BettingHighLowPanel * GameRoomInfo::GetHighLowPanel()
{
	if (!LayerManager::getSingleton().hasLayer("BettingHighLowPanel"))
		return nullptr;

	BettingHighLowPanel * _pPanel = dynamic_cast<BettingHighLowPanel*>(LayerManager::getSingleton().getLayer("BettingHighLowPanel"));

	return _pPanel;
}

PokerUnderImoticonPanel* GameRoomInfo::GetResultImoticonPanel()
{
	if (!LayerManager::getSingleton().hasLayer("ResultImoticonPanel"))
		return nullptr;

	PokerUnderImoticonPanel * _pPanel = dynamic_cast<PokerUnderImoticonPanel*>(LayerManager::getSingleton().getLayer("ResultImoticonPanel"));

	return _pPanel;
}

PokerPlayerInfoCommonPanel * GameRoomInfo::GetPlayerCommonPanel(int po)
{
	if (!LayerManager::getSingleton().hasLayer("PlayerInfo"))
		return nullptr;

	PokerPlayerInfoPanel* _pPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingleton().getLayer("PlayerInfo"));
	if (_pPanel == nullptr)
		return nullptr;

	PokerPlayerInfoCommonPanel* _pPlayerPanel = dynamic_cast<PokerPlayerInfoCommonPanel*>(_pPanel->GetPlayerCommonPanel(po));
	return _pPlayerPanel;
}

PokerPlayerInfoPanel * GameRoomInfo::GetPlayerInfoPanel()
{
	if (!LayerManager::getSingleton().hasLayer("PlayerInfo"))
		return nullptr;
	PokerPlayerInfoPanel* _pInfoPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingleton().getLayer("PlayerInfo"));

	return _pInfoPanel;
}

PokerTopPanel * GameRoomInfo::GetTopPanel()
{
	if (!LayerManager::getSingleton().hasLayer("TopLayer"))
		return nullptr;

	PokerTopPanel* _pLayer = dynamic_cast<PokerTopPanel*>(LayerManager::getSingleton().getLayer("TopLayer"));

	return _pLayer;
}

void GameRoomInfo::SetMyBadugiJokbo(LowJokboKind _kind)
{
	JokboList* _pPanel = dynamic_cast<JokboList*>(LayerManager::getSingletonPtr()->getLayer("JokboLayer"));
	if (_pPanel == nullptr)
		return;

	switch (_kind)
	{
	case LOW_NO:
	case BADUKI_GOLF:
	case BADUKI_SECOND:
	case BADUKI_THIRD:
	case BADUKI_FIVE_TOP:
	case BADUKI_SIX_TOP:
	case BADUKI_SEVEN_TOP:
	case BADUKI_EIGHT_TOP:
	case BADUKI_NINE_TOP:
	case BADUKI_TEN_TOP:
	case BADUKI_J_TOP:
	case BADUKI_Q_TOP:
	case BADUKI_K_TOP:
	case BADUKI_BASE:
	case BADUKI_TWO_BASE:
	case BADUKI_TWO_BASE_DOWN:
		_pPanel->ShowBadugiLabel(_kind);
		break;
	default:
		break;
	}
}

void GameRoomInfo::SetMyHighJokbo(HighJokboKind _kind)
{
	JokboList* _pPanel = dynamic_cast<JokboList*>(LayerManager::getSingletonPtr()->getLayer("JokboLayer"));
	if (_pPanel == nullptr)
		return;

	switch (_kind)
	{
	case HIGH_NO:
		_pPanel->ShowHighLabel(HIGH_NO);
		break;
	case HIGH_ROYAL_STRAIGHT_FLUSH:
	case HIGH_STRAIGHT_FLUSH:
	case HIGH_FOUR_CARD:
	case HIGH_FULL_HOUSE:
	case HIGH_FLUSH:
	case HIGH_MOUNTAIN:
	case HIGH_BACK_STRAIGHT:
	case HIGH_STRAIGHT:
	case HIGH_TRIPLE:
	case HIGH_TWO_PAIR:
	case HIGH_ONE_PAIR:
	case HIGH_TOP:
		_pPanel->ShowHighLabel(_kind);
		break;
	default:
		break;
	}
}

void GameRoomInfo::SetMyLowJokbo(LowJokboKind _kind)
{
	if (GetGameKind() != GAMEKIND_HIGH_LOW)
		return;

	JokboList* _pPanel = dynamic_cast<JokboList*>(LayerManager::getSingletonPtr()->getLayer("JokboLayer"));
	if (_pPanel == nullptr)
		return;

	switch (_kind)
	{
		case LOW_NO:
			_pPanel->ShowLowLabel(LOW_NO);
			break;
		case LOW_ROYAL_STRAIGHT_FLUSH:
		case LOW_STRAIGHT_FLUSH:
		case LOW_FOUR_CARD:
		case LOW_SIX_TOP:
		case LOW_SEVEN_TOP:
		case LOW_EIGHT_TOP:
		case LOW_NINE_TOP:
		case LOW_TEN_TOP:
		case LOW_J_TOP:
		case LOW_Q_TOP:
		case LOW_K_TOP:
		case LOW_ONE_PAIR:
		case LOW_TWO_PAIR:
		case LOW_TRIPLE:
		case LOW_STRAIGHT:
		case LOW_TOP_DOWN:
		{
			_pPanel->ShowLowLabel(_kind);
			break;
		}
	}
}

void GameRoomInfo::ShowHoldemPae(char * data, int size)
{
	PlayShowDownEfx();

	ShareCardInfo res;
	res.ParseFromArray(data, size);
	RoomUserData * userData = GetUserDataPtr(res.po());

	if (userData == nullptr)
		return;

	CardInfo cardInfo;
	for (int i = 0, j = res.cardinfo_size(); i < j; i++)
	{
		cardInfo = res.cardinfo(i);
		if (cardInfo.cardnumber() != -1)
		{
			userData->ChangeCard(cardInfo.cardpo(), cardInfo.cardnumber(), cardInfo.cardkind(), true);
			//cout << "User : " << res.po() << " card(number/kind) : " << cardInfo.cardnumber() << "/" << cardInfo.cardkind() << "\n\n" << endl;
		}
	}

	//if (userData->m_isMe == true)
	//{
	//	for (CardData* _pCard : userData->GetCardManager()->m_CardList)
	//	{
	//		_pCard->m_pCard->CardEffectSelectBoxOff();
	//		GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_pCard->m_idx] = false;
	//	}
	//}

	ActionPointer::createHoldemPaeShow(userData, 0.5f);
	//ShowLastBadugiAnimation(res.po());

	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerInfoPanel()->ClearAllPanelAction();
	PokerPlayerInfoCommonPanel*  _panel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(res.po());
	if (_panel != nullptr)
	{
		_panel->ClearBettingAmount();
		_panel->turnOnTimeGauge(true);
	}
}

void GameRoomInfo::ShowBadukiPae(char * data, int size)
{
	PlayShowDownEfx();

	ShareCardInfo res;
	res.ParseFromArray(data, size);
	RoomUserData * userData = GetUserDataPtr(res.po());

	if (userData == nullptr)
		return;

	CardInfo cardInfo;
	for (int i = 0, j = res.cardinfo_size(); i < j; i++)
	{
		cardInfo = res.cardinfo(i);
		if (cardInfo.cardnumber() != -1)
		{
			userData->ChangeCard(cardInfo.cardpo(), cardInfo.cardnumber(), cardInfo.cardkind(), true);
			//cout << "User : " << res.po() << " card(number/kind) : " << cardInfo.cardnumber() << "/" << cardInfo.cardkind() << "\n\n" << endl;
		}
	}

	if (userData->m_isMe == true)
	{
		for (CardData* _pCard : userData->GetCardManager()->m_CardList)
		{
			_pCard->m_pCard->CardEffectSelectBoxOff();
			GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_pCard->m_idx] = false;
		}
	}

	ActionPointer::createBadugiPaeShow(userData, 0.5f);
	ShowLastBadugiAnimation(res.po());

	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerInfoPanel()->ClearAllPanelAction();
	PokerPlayerInfoCommonPanel*  _panel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(res.po());
	if (_panel != nullptr)
	{
		_panel->ClearBettingAmount();
		_panel->turnOnTimeGauge(true);
	}
}


void GameRoomInfo::Show7PokerPae(char * data, int size)
{
	PlayShowDownEfx();

	ShareCardInfo res;
	res.ParseFromArray(data, size);

	RoomUserData * userData = GetUserDataPtr(res.po());

	if (userData == nullptr)
		return;

	CardInfo cardInfo;
	for (int i = 0, j = res.cardinfo_size(); i < j; i++)
	{
		cardInfo = res.cardinfo(i);
		if (cardInfo.cardnumber() != -1)
		{
			userData->ChangeCard(cardInfo.cardpo(), cardInfo.cardnumber(), cardInfo.cardkind(), true);
			//cout << "User : " << res.po() << " card(number/kind) : " << cardInfo.cardnumber() << "/" << cardInfo.cardkind() << "\n\n" << endl;
		}
	}

	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerInfoPanel()->ClearAllPanelAction();
	PokerPlayerInfoCommonPanel*  _panel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(res.po());
	if (_panel != nullptr)
	{
		_panel->ClearBettingAmount();
		_panel->turnOnTimeGauge(true);
	}

	//userData->ShowHighJokboCheck();
	ActionPointer::createLastPaeShow(userData, 1.f);
	ShowLastCardAnimation(res.po());

	

	//if (userData->m_pJokboInfo->GetHighJokboKind() <= HighJokboKind::HIGH_TRIPLE)
	//{
	//	ActionPointer::createLastPaeHighLowEvent(DealerAniKind::DEALER_REACT_MADE, EFX_DEALER_NOVOICE, 1.f);
	//}
	//else if (userData->m_pJokboInfo->GetHighJokboKind() >= HighJokboKind::HIGH_ONE_PAIR)
	//{
	//	ActionPointer::createLastPaeHighLowEvent(DealerAniKind::DEALER_REACT_SMALLOPEN, EFX_DEALER_NOVOICE, 1.f);
	//}
}

void GameRoomInfo::SortCard()
{
	for (int _i = 0; _i < GAME_USER_MAX; _i++)
	{
		if (m_UserList[_i] == nullptr)
			continue;

		//if (_i != m_MyPo)
		m_UserList[_i]->GetCardManager()->ActionCardSort();
	}
}
void GameRoomInfo::ShowHighLowPae(char * data, int size)
{
	PlayShowDownEfx();

	HighLowUserInfo res;
	res.ParseFromArray(data, size);

	int userSize = res.highlowselectcardinfo_size();
	HighLowSelectCardInfo highLowCardInfo;
	RoomUserData * userData;
	CardInfo cardInfo;
	HighLowBettingKind betKind;
	int _DealerReaction = -1;

	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerInfoPanel()->ClearAllPanelAction();
	
		
	for (int i = 0; i < userSize; i++)
	{
		highLowCardInfo = res.highlowselectcardinfo(i);
		userData = GetUserDataPtr(highLowCardInfo.po());

		if (userData == nullptr)
			return;

		for (int i = 0, j = highLowCardInfo.cardinfo_size(); i < j; i++)
		{
			cardInfo = highLowCardInfo.cardinfo(i);
			if (cardInfo.cardnumber() != -1)
			{
				userData->ChangeCard(cardInfo.cardpo(), cardInfo.cardnumber(), cardInfo.cardkind(), true);
				//cout << "User : " << highLowCardInfo.po() << " card(number/kind) : " << cardInfo.cardnumber() << "/" << cardInfo.cardkind() << "\n\n" << endl;
			}
		}

		userData->m_pJokboInfo->HighJokboCheck();
		userData->m_pJokboInfo->LowJokboCheck();

		betKind = highLowCardInfo.highlowbettingkind();
		userData->SetHighLowBettingKind(betKind);
		SetHighLow(highLowCardInfo.po(), betKind);

		switch (betKind)
		{
		case HIGH_BET:
			
			if (userData->m_pJokboInfo->GetHighJokboKind() <= HighJokboKind::HIGH_TRIPLE && _DealerReaction < 1)
			{
				_DealerReaction = 1;
			}
			else if (userData->m_pJokboInfo->GetHighJokboKind() >= HighJokboKind::HIGH_ONE_PAIR && _DealerReaction < 0)
			{
				_DealerReaction = 0;
			}
			break;
		case LOW_BET:
			if (userData->m_pJokboInfo->GetLowJokboKind() <= LowJokboKind::LOW_EIGHT_TOP && _DealerReaction < 1)
			{
				_DealerReaction = 1;
			}
			else if (userData->m_pJokboInfo->GetLowJokboKind() >= LowJokboKind::LOW_K_TOP && _DealerReaction < 0)
			{
				_DealerReaction = 0;
			}
			break;
		case SWING_BET:
			if (userData->m_pJokboInfo->GetHighJokboKind() <= HighJokboKind::HIGH_TRIPLE && _DealerReaction < 1)
			{
				_DealerReaction = 1;
			}
			else if (userData->m_pJokboInfo->GetHighJokboKind() >= HighJokboKind::HIGH_ONE_PAIR && _DealerReaction < 0)
			{
				_DealerReaction = 0;
			}

			if (userData->m_pJokboInfo->GetLowJokboKind() <= LowJokboKind::LOW_EIGHT_TOP && _DealerReaction < 1)
			{
				_DealerReaction = 1;
			}
			else if (userData->m_pJokboInfo->GetLowJokboKind() >= LowJokboKind::LOW_K_TOP && _DealerReaction < 0)
			{
				_DealerReaction = 0;
			}
			break;
		}
	
		PokerPlayerInfoCommonPanel*  _panel = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetPlayerCommonPanel(highLowCardInfo.po());
		if (_panel != nullptr)
		{
			_panel->ClearBettingAmount();
			_panel->turnOnTimeGauge(true);
		}

		ActionPointer::createLastPaeShow(userData, 1.f);
		ShowLastCardAnimation(highLowCardInfo.po());
	}
}

void GameRoomInfo::SetHighLowChoice(bool isOn)
{
	BettingHighLowPanel * pPanel = GetHighLowPanel();
	if (pPanel == nullptr)
		return;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (isOn) {
		//AdmobManager::getSingleton().hideAdmob();
	}
	else {
		//AdmobManager::getSingleton().showAdMob();
	}
#endif

	if (isOn)
	{
		if (m_UserList[m_MyPo]->GetPlayerStatus() == PLAYER_INIT)
		{
			HighJokboKind tmpJokbo = m_UserList[m_MyPo]->m_pJokboInfo->GetHighJokboKind();
			pPanel->ShowHighLowButton();
			if (tmpJokbo != HighJokboKind::HIGH_NO && tmpJokbo <= HighJokboKind::HIGH_FOUR_CARD)
			{
				pPanel->DisableHighLowButton(HighLowBettingKind::HIGH_BET);
				pPanel->DisableHighLowButton(HighLowBettingKind::LOW_BET);
			}
			pPanel->setVisible(true);
		}

		PokerPlayerInfoCommonPanel * _pPanel;
		for (int i = 0; i < GAME_USER_MAX; i++)
		{
			if (m_UserList[i] == nullptr || m_UserList[i]->GetPlayerStatus() != PLAYER_INIT)
				continue;

			_pPanel = GetPlayerCommonPanel(i);

			_pPanel->TurnOnHighLowChoice();
			_pPanel->SetHighLowChoice(HighLowBettingKind::HIGHLOW_NO_BET, m_MyPo == i);
		}
	}
	else
	{
		pPanel->InitHighLowButton();
		// I have removed this code to show until Result screen
		/*
		PokerPlayerInfoCommonPanel * _pPanel;
		for (int i = 0; i < GAME_USER_MAX; i++)
		{
			if (m_UserList[i] == nullptr)
				continue;

			_pPanel = GetPlayerCommonPanel(i);

			_pPanel->TurnOffHighLowChoice();
		}
		*/
	}
}

void GameRoomInfo::SetHighLow(char * data, int size)
{
	ChoiceHighLowInfo res;
	res.ParseFromArray(data, size);

	int po = res.po();
	HighLowBettingKind _betKind = res.highlowbettingkind();
	if (m_UserList[po] == nullptr)
		return;

	m_UserList[po]->SetHighLowBettingKind(_betKind);

	SetHighLow(po, _betKind);
}

void GameRoomInfo::SetPrepareEnd(char * data, int size)
{
	PlayerPoInfo res;
	res.ParseFromArray(data, size);

	int po = res.po();

	if (m_UserList[po] == nullptr)
		return;

	m_UserList[po]->SetPlayerStatus(res.playerstatus());

	int canPlayCnt = GetCanPlayerCnt();

	if (canPlayCnt == 5)
	{
		GameStartCheck();
		//ShowStartButton();
	}
	else if (canPlayCnt >= 2)
	{
		ShowStartButton();
	}
}

void GameRoomInfo::SetHighLow(int po, HighLowBettingKind _kind)
{
	BettingHighLowPanel * _pBPanel = GetHighLowPanel();
	if (_pBPanel == nullptr)
		return;

	if (po == m_MyPo)
	{
		if (_pBPanel->isVisible())
		{
			_pBPanel->InitHighLowButton();
			_pBPanel->setVisible(false);
		}
	}
	
	PokerPlayerInfoCommonPanel * _pPanel = GetPlayerCommonPanel(po);

	if (_pPanel == nullptr)
		return;
	_pPanel->SetHighLowChoice(_kind, po == m_MyPo);
}

bool GameRoomInfo::CanExit(int _idx)
{
	int _po = _idx;
	if (_po == -1)
	{
		_po = m_MyPo;
	}
	PlayerStatus status = m_UserList[_po]->GetPlayerStatus();
	if (status != PlayerStatus::PLAYER_INIT)
		return true;

	if (m_PlayStatus <= PLAY_READY || m_PlayStatus == PLAY_RESULT || m_PlayStatus == PLAY_NEXT_READY)
		return true;
	
	return false;
}

void GameRoomInfo::SetExit(bool isExe)
{
	// 나갈수 있는 상황이면 나간다.
	if (CanExit())
	{
		PokerTopPanel * _pTopPanel = GetTopPanel();
		if (!isExe)
		{
			if (_pTopPanel != nullptr)
				_pTopPanel->SetPressExitStartButton();
			_pTopPanel->SetOutButtonClick(true);
		}
		else
		{
			if (_pTopPanel != nullptr)
				_pTopPanel->SetPressExitFailButton();
			TCPService::getSingletonPtr()->SendNormalPacket(CSProtocol::C2S_PLAYER_OUT_IDX);
		}
	}
	// 나갈 수 없는 상황이면 예약을 건다.
	else
	{
		PokerTopPanel * _pTopPanel = GetTopPanel();
		if (!isExe)
		{
			if (_pTopPanel != nullptr)
			{
				if (!m_ExitReserve)
					_pTopPanel->SetPressExitStartButton();
				else
					_pTopPanel->SetPressExitReserveCancelButton();

				_pTopPanel->SetOutButtonClick(true);
			}
		}
		else
		{
			/*if (_pPanel != nullptr)
			{
				if (!m_ExitReserve)
					_pPanel->SetPressExitReserveButton();
				else
					_pPanel->SetPressExitFailButton();
			}
			m_ExitReserve ^= true;*/
			TCPService::getSingletonPtr()->SendPlayerOutResvReq(m_MyPo, m_UserList[m_MyPo]->m_pPlayerData->m_UID);
		}
	}
}

void GameRoomInfo::NextReadyProcess()
{
	//
	//if (m_ExitReserve)
	//{
	//	TCPService::getSingletonPtr()->SendNormalPacket(CSProtocol::C2S_PLAYER_OUT_IDX);
	//}
	//else if (GetUserDataPtr(m_MyPo)->m_pPlayerData->m_GameMoney <= 0)
	//{
	//	TCPService::getSingletonPtr()->SendNormalPacket(CSProtocol::C2S_PLAYER_OUT_IDX);
	//}
	//
}

int GameRoomInfo::IsBigGame()
{
	if (m_bigGameMoney2 < m_PotMoney)
	{
		return 2;
	}
	else if (m_bigGameMoney1 < m_PotMoney)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void GameRoomInfo::DealerAnimation(DealerAniKind _kind)
{
	string _frameName;
	switch (_kind)
	{
	case DEALER_ACT1:
		_frameName = "act1";
		break;
	case DEALER_ACT2:
		_frameName = "act2";
		break;
	case DEALER_DEALING_READY:
		_frameName = "dealing_ready";
		break;
	case DEALER_DEALING_SHOOT:
	{
		m_pDealer->playAnimation("dealing_loop"); 
		m_pDealer->setAnimationSpeed(1.f);

		m_pDealerUnder->playAnimation("dealing_loop");
		m_pDealerUnder->setAnimationSpeed(1.f);
		
		m_DealerTime = 0;
		return;
	}	
		break;
	case DEALER_GESTURE_BAD:
		_frameName = "gesture_bad";
		break;
	case DEALER_GESTURE_GOOD:
		_frameName = "gesture_good";
		break;
	case DEALER_HURRY:
		_frameName = "hurry";
		break;
	case DEALER_IDLE:
		_frameName = "idle";
		break;
	case DEALER_REACT_ALLIN_L:
		_frameName = "react_allin_l";
		break;
	case DEALER_REACT_ALLIN_R:
		_frameName = "react_allin_r";
		break;
	case DEALER_REACT_BANKRUPT:
		_frameName = "react_bankrupt";
		break;
	case DEALER_REACT_BIGPOT:
		GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_CROWD);
		_frameName = "react_bigpot";
		break;	
	case DEALER_REACT_MADE:
		_frameName = "react_made";
		break;
	case DEALER_REACT_SMALLBET:
		_frameName = "react_smallbet";
		break;
	case DEALER_REACT_SMALLOPEN:
		_frameName = "react_smallopen";
		break;
	case DEALER_REACT_TIP:
		_frameName = "react_tip";
		break;
	case DEALER_SHUFFLING:
		_frameName = "shuffling";
		break;
	default:
		return;
	}
	m_pDealer->playAnimation(_frameName);
	m_pDealer->appendAnimation("idle", true);
	m_pDealerUnder->playAnimation(_frameName);
	m_pDealerUnder->appendAnimation("idle", true);
	m_DealerTime = 0;
}

void GameRoomInfo::DealerSound(DealerEfxKind _kind)
{
	if (_kind == EFX_DEALER_NOVOICE)
		return;

	if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_voice == false)
		return;

	string _filename = "dealer_";
	switch (_kind)
	{
	case EFX_DEALER_BACKSTRAIGHT:
		_filename += "backstraight";
		break;
	case EFX_DEALER_BANKRUPT:
		_filename += "bankrupt";
		break;
	case EFX_DEALER_BIGPOT1:
		_filename += "bigpot1";
		break;
	case EFX_DEALER_BIGPOT2:
		_filename += "bigpot2";
		break;
	case EFX_DEALER_BIGPOT3:
		_filename += "bigpot3";
		break;
	case EFX_DEALER_CELEBRATE:
		_filename += "celebrate";
		break;
	case EFX_DEALER_DIE:
		_filename += "die";
		break;
	case EFX_DEALER_FLUSH:
		_filename += "flush";
		break;
	case EFX_DEALER_FOURCARD:
		_filename += "fourcard";
		break;
	case EFX_DEALER_FULLHOUSE:
		_filename += "fullhouse";
		break;
	case EFX_DEALER_GAMESTART1:
		_filename += "gamestart1";
		break;
	case EFX_DEALER_GAMESTART2:
		_filename += "gamestart2";
		break;
	case EFX_DEALER_GAMESTART3:
		_filename += "gamestart3";
		break;
	case EFX_DEALER_HIGH:
		_filename += "high";
		break;
	case EFX_DEALER_INCOME1:
		_filename += "income1";
		break;
	case EFX_DEALER_INCOME2:
		_filename += "income2";
		break;
	case EFX_DEALER_INCOME3:
		_filename += "income3";
		break;
	case EFX_DEALER_LOW:
		_filename += "low";
		break;
	case EFX_DEALER_MOUNTAIN:
		_filename += "mountain";
		break;
	case EFX_DEALER_ONEPAIR:
		_filename += "onepair";
		break;
	case EFX_DEALER_ROYALFLUSH:
		_filename += "royalflush";
		break;
	case EFX_DEALER_SHOWDOWN:
		_filename += "showdown";
		break;
	case EFX_DEALER_SORRY:
		_filename += "sorry";
		break;
	case EFX_DEALER_STRAIGHT:
		_filename += "straight";
		break;
	case EFX_DEALER_STRAIGHTFLUSH:
		_filename += "straightflush";
		break;
	case EFX_DEALER_SWING:
		_filename += "swing";
		break;
	case EFX_DEALER_TOP:
		_filename += "top";
		break;
	case EFX_DEALER_TRIPLE:
		_filename += "triple";
		break;
	case EFX_DEALER_TURN:
		_filename += "turn";
		break;
	case EFX_DEALER_TWOPAIR:
		_filename += "twopair";
		break;
	case EFX_DEALER_5TOP:
		_filename += "5top";
		break;
	case EFX_DEALER_6TOP:
		_filename += "6top";
		break;
	case EFX_DEALER_7TOP:
		_filename += "7top";
		break;
	case EFX_DEALER_8TOP:
		_filename += "8top";
		break;
	case EFX_DEALER_9TOP:
		_filename += "9top";
		break;
	case EFX_DEALER_10TOP:
		_filename += "10top";
		break;
	case EFX_DEALER_BASE:
		_filename += "base";
		break;
	case EFX_DEALER_DAY:
		_filename += "day";
		break;
	case EFX_DEALER_GOLF:
		_filename += "golf";
		break;
	case EFX_DEALER_JTOP:
		_filename += "jtop";
		break;
	case EFX_DEALER_KTOP:
		_filename += "ktop";
		break;
	case EFX_DEALER_MORNING:
		_filename += "morning";
		break;
	case EFX_DEALER_NIGHT:
		_filename += "night";
		break;
	case EFX_DEALER_NOTHING:
		_filename += "nothing";
		break;
	case EFX_DEALER_QTOP:
		_filename += "qtop";
		break;
	case EFX_DEALER_SECOND:
		_filename += "second";
		break;
	case EFX_DEALER_THIRD:
		_filename += "third";
		break;
	case EFX_DEALER_TWOBASE:
		_filename += "twobase";
		break;
	}

	if (SoundManager::getSingletonPtr()->isPlayingEffect(_filename) == false)
	{
		SoundManager::getSingletonPtr()->playEffect(_filename);
	}
}


void GameRoomInfo::SetDealer()
{
	m_pDealer = new SkelObject();
	m_pDealerUnder = new SkelObject();

	m_pDealer->setSkelAnim(PokerResourceHelper::getDealerOverSpineName());
	m_pDealerUnder->setSkelAnim(PokerResourceHelper::getDealerUnderSpineName());

	Panel* _panel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
	CCPoint _pos = _panel->getImage("dmy_dealer")->getPosition();

	m_pDealer->setPosition(_pos);
	m_pDealer->setScale(0.7f);		
	m_pDealer->playAnimation("idle", true);
	m_pDealer->addEventListener(this);

	m_pDealerUnder->setPosition(_pos);
	m_pDealerUnder->setScale(0.7f);
	m_pDealerUnder->playAnimation("idle", true);

	GetBackgroundPanel()->addChild(m_pDealerUnder, -1);
	m_pDealerUnder->release();
	GetChracterPanel()->addChild(m_pDealer);
	m_pDealer->release();

	CCPoint _dmyPos = _panel->getDummy("dmy_dealer_bubbler").origin;
	m_pDealerTextBubble = new Panel();
	m_pDealerTextBubble->construct(getMxmlPath() + "dmy_dealer_bubbler.mxml");
	m_pDealerTextBubble->setPosition(ccp(_dmyPos.x, -_dmyPos.y));
	GetTopPanel()->addChild(m_pDealerTextBubble);
	m_pDealerTextBubble->release();

	m_pDealerTextBubble->getSkel("skel_dealer_bubbler")->playAnimation("dealer_bubbler_end");
	m_pDealerTextBubble->getSkel("skel_dealer_bubbler")->setVisible(false);
	m_pDealerTextBubble->getLabel("txt_dealer_speech_under")->setVisible(false);
	m_pDealerTextBubble->getLabel("txt_dealer_speech")->setVisible(false);

	m_pDealerTextBubble->getLabel("txt_dealer_speech_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pDealerTextBubble->getLabel("txt_dealer_speech")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
}

void GameRoomInfo::RemoveDealer()
{
	if (m_pDealer)
	{
		//m_pDealer->cleanup();
		//m_pDealer->subEventListener(this);
		//m_pDealer->removeFromParent();
		m_pDealer->removeFromParentAndCleanup(true);
	}
	m_pDealer = nullptr;

	if (m_pDealerUnder)
	{
		//m_pDealerUnder->cleanup();
		//m_pDealerUnder->removeFromParent();
		m_pDealerUnder->removeFromParentAndCleanup(true);
	}
	m_pDealerUnder = nullptr;

	if (m_pDealerTextBubble)
	{
		StopDealerTextBubble();
		m_pDealerTextBubble->destruct();
		//m_pDealerTextBubble->cleanup();
		//m_pDealerTextBubble->removeFromParent();
		m_pDealerTextBubble->removeFromParentAndCleanup(true);
	}
	m_pDealerTextBubble = nullptr;
}

void GameRoomInfo::RemovePotMoney()
{
	if (LayerManager::getSingletonPtr()->hasLayer("PotMoney"))
	{
		PotMoneyPanel* _potMoneyPanel = dynamic_cast<PotMoneyPanel*>(LayerManager::getSingletonPtr()->getLayer("PotMoney"));
		if (_potMoneyPanel)
		{
			_potMoneyPanel->ClearPotMoney();
		}
	}
}

Panel* GameRoomInfo::GetChracterPanel()
{
	Panel* _returnPanel = nullptr;
	if (LayerManager::getSingletonPtr()->hasLayer("CharacterLayer"))
	{
		_returnPanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("CharacterLayer"));
	}
	return _returnPanel;
}

Panel* GameRoomInfo::GetCardPanel()
{
	Panel* _returnPanel = nullptr;
	if (LayerManager::getSingletonPtr()->hasLayer("CardLayer"))
	{
		_returnPanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("CardLayer"));
	}
	return _returnPanel;
}
void GameRoomInfo::SetVisibleLight(bool isView)
{
	PokerTopPanel * _pPanel = GetTopPanel();
	if (_pPanel == nullptr)
		return;

	if (isView)
		_pPanel->SetTurnOnLight();
	else
		_pPanel->SetTurnOffLight();
}
void GameRoomInfo::SetWinnerMoneyString(int64 _money)
{
	m_WinnerMoneyStr = PokerResourceHelper::getImgFontForGameMoney(_money);
	m_pLabelWinnerMoney->setString(m_WinnerMoneyStr.c_str());
	m_pLabelWinnerMoney->setScale(0.4f);
	m_pLabelWinnerMoney->setVisible(true);

	m_pLabelWinnerMoney->setString(m_WinnerMoneyStr.c_str());
	m_pLabelWinnerMoney->runAction(CCSequence::create(
		CCScaleTo::create(0.1f, 1.2f),
		CCScaleTo::create(0.1f, 1.f),
		NULL));

	m_bWinnerMonnyEffectUpdate = true;
	m_fWinnerMoneyEfxTime = WIN_TEXT_EFFFECT_TIME;
}


void GameRoomInfo::Action_WinnerText(int _po, int64 _money)
{
	PokerPlayerInfoCommonPanel* _panel = GetPlayerCommonPanel(_po);
	if (_panel == nullptr)
		return;

	Panel* _ShowPanel = GetCardPanel();
	if (_ShowPanel == nullptr)
		return;

	if (_po == m_MyPo && m_GameMode == GameMode::MODE_NORMAL) {
		ShouldDisplayDealerfee = true;
		Dealerfee = DealerPercent * _money / (1-DealerPercent);
	}
	else
		ShouldDisplayDealerfee = false;

	_panel->SetWinnerText(_money);


}

//void GameRoomInfo::Remove_WinnerText()
//{
//	for (int _i = 0; _i < GAME_USER_MAX; _i++)
//	{
//		if (m_pWinnerText[_i] == nullptr)
//			continue;
//
//		m_pWinnerText[_i]->cleanup();
//		m_pWinnerText[_i]->removeFromParent();
//		m_pWinnerText[_i] = nullptr;
//	}
//}

void GameRoomInfo::onEvent(int trackIdx, spEvent* event)
{
	string _EventName = event->data->name;
	if (strncmp(_EventName.c_str(), "dealer_", 7) == 0)
	{
		_EventName = nxReplace(event->data->name, "dealer_", "");
		if (_EventName == "dealing_shoot_shoot")
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_CARDDEAL);
			m_DealerShoot = true;
		}
	}
}

//void GameRoomInfo::StartCardMadeEffect()
//{
//
//}

bool GameRoomInfo::PlayerInProcess(char * msg, int size)
{
	if (!IsGameLoaded())
		return false;
	
	RoomPlayerInfo res;
	res.ParseFromArray((char*)msg, size);

	if (GetGameMode() != GameMode::MODE_NORMAL && GetUserDataPtr(res.po()) != nullptr)
	{
		PokerPlayerInfoCommonPanel* _pUserPanel = GetPlayerCommonPanel(res.po());
		if (_pUserPanel)
		{
			_pUserPanel->TurnOffPlayerDisconnect();
		}

		GetUserDataPtr(res.po())->m_pPlayerData->m_UserKind = res.userkind();

		string msgText = "[" + res.nickname() + "]" + GameStringDepot::getSingletonPtr()->getString("TXT_USER_RECONNECTED");
		SimplePopupPanel * _toastpanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ToastNotice, msgText);

		if (_toastpanel)
			LayerManager::getSingleton().pushDynamicLayer(_toastpanel, DYNAMIC_PUSH_LAYER);
		return true;
	}

	AddUser(&res);
	m_CurrentUser++;		// 유저 증가.
	cout << "Player came in!!" << endl;

	PokerPlayerInfoPanel* _pPanel = dynamic_cast<PokerPlayerInfoPanel*>(LayerManager::getSingletonPtr()->getLayer("PlayerInfo"));

	int _UserClientIndex = GameDataManager::getSingletonPtr()->ServerToClientIndex(res.po());
	//GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(res.po())->GetCardManager()->m_UserIdx;

	int _UserCharacterIdx = GetUserDataPtr(res.po())->m_pPlayerData->m_CharacterIdx;
	//_pPanel->ShowPlayerPanel(_UserClientIndex, true);
	_pPanel->SetCharacter(res.po(), _UserCharacterIdx, true);
	_pPanel->SetUserInfoPanelUpdate(res.po(), GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(res.po()));
	SetUserPo();
	SetMaster(m_MasterPo);
	//GetPlayerCommonPanel(0)->TurnOnHighLowChoice();

	//DealerSound((DealerEfxKind)EFX_DEALER_INCOME1);
	int _kind = CharacterEfxKind::EFX_ENTER1 + (rand() % 2);
	GetUserDataPtr(res.po())->PlayCharacterSound((CharacterEfxKind)_kind);

	Action_EnterRoomCharacter(res.po());

	return true;
}

bool GameRoomInfo::SetGameIngInfo(char * msg, int size)
{
	RoomGameStatus res;
	PlayerGameStatus status;
	CardInfo cardInfo;
	RoomUserData * userData;
	PokerPlayerInfoCommonPanel* _pPlayerPanel;

	int po;
	res.ParseFromArray((char*)msg, size);

	m_BetMoney = res.allbetmoney();
	SetPotMoney(res.potmoney(), res.potmoney());
	SetPotMoneyUpdate(PotMoneyState::POT_UPDATE);
	//m_PotMoneyEffectState = PotMoneyState::POT_UPDATE;
	SetBoss(res.bossidx());
	m_preUserBetMoney = res.betmoney();
	m_BetPo = res.betpo();

	m_PlayStatus = (PlayStatus)(res.playstatus());

	m_isInitGame = false;

	if (m_PlayStatus > PlayStatus::PLAY_NO)
	{
		PokerTopPanel * panel = GetPokerTopPanel();
		if (panel)
		{
			panel->SetTurnOffLight();

			if (GameDataManager::getSingletonPtr()->m_GameMode != GameMode::MODE_NORMAL)
				panel->TopButtonesEnable(false);
		}

		m_isSelectedCard = (res.isaftercardselect() != 0);
	}

	if (m_PlayStatus != PlayStatus::PLAY_NO && m_PlayStatus != PlayStatus::ROOM_REARRANGE)
	{
		if (m_pStayPopup)
		{
			m_pStayPopup->closePanel(true);
			m_pStayPopup = nullptr;
		}
	}



	int openCnt = 0;

	if (m_GameKind == GameKind::GAMEKIND_HOLDEM)
	{
		int _familyCardsize = res.familycards_size();
		for (int _i = 0; _i < _familyCardsize; _i++)
		{
			AddCommunityCard(res.familycards(_i).cardnumber(), res.familycards(_i).cardkind(), false, false);
		}
	}

	for (int i = 0, j = res.playergamestatus_size(); i < j; i++)
	{
		status = res.playergamestatus(i);
		po = status.po();

		userData = m_UserList[po];
		userData->m_AllBetKind = status.isallbet();
		userData->m_BettingMoney = status.curbettingmoney();
		userData->m_TotalBettingMoney = status.bettingtotalmoney();
		userData->m_BettingKind = status.userbettingkind();
		userData->SetPlayerStatus(status.userstate());

		if (userData->GetPlayerStatus() == PLAYER_DIE)
		{
			userData->m_pMyCharater->appendAnimation("die_idle_loop", true);
			userData->m_pMyCharaterUnder->appendAnimation("die_idle_loop", true);
		}

		_pPlayerPanel = GetPlayerCommonPanel(po);
		if (_pPlayerPanel)
		{
			if (status.isallbet() != AllBetKind::ALLBET_NO)
				_pPlayerPanel->SetAllBet(status.isallbet());

			if (status.outreserve() == PlayerOutResrvKind::RESERVE_PLAYER_OUT)
			{
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(po)->m_PlayerOutResrvKind = PlayerOutResrvKind::RESERVE_PLAYER_OUT;
				_pPlayerPanel->TurnOnGameOut(0);
			}
			else if (status.putoutreserve() == PlayerOutResrvKind::RESERVE_PUT_OUT)
			{
				GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(po)->m_PlayerOutResrvKind = PlayerOutResrvKind::RESERVE_PUT_OUT;
				_pPlayerPanel->TurnOnGameOut(1);
			}

			openCnt = 0;
			for (int k = 0, l = status.cardinfo_size(); k < l; k++)
			{
				if (cardInfo.cardnumber() == -1)
					continue;
				if (cardInfo.cardnumber() != 100 && cardInfo.cardnumber() >= 0)
					openCnt++;

				cardInfo = status.cardinfo(k);
				if (m_GameKind == GameKind::GAMEKIND_BADUKI || m_GameKind == GameKind::GAMEKIND_HOLDEM)
				{
					CCLOG("SetGameIngInfo status = %d", userData->GetPlayerStatus());
					if (userData->GetPlayerStatus() == PLAYER_DIE)
						userData->BadugiAddCard(cardInfo.cardnumber(), cardInfo.cardkind(), true);
					else
						userData->BadugiAddCard(cardInfo.cardnumber(), cardInfo.cardkind());

					if (m_GameKind == GameKind::GAMEKIND_HOLDEM)
					{
						int _idx = userData->GetCardManager()->m_CardList.size() - 1;
						userData->GetCardManager()->m_CardList[_idx]->m_pCard->GetCardSkelObj()->setScale(0.7f);
					}
						
				}
				else
				{
					if (!m_isSelectedCard || userData->GetPlayerStatus() == PLAYER_DIE)
						userData->AddCard(cardInfo.cardnumber(), cardInfo.cardkind(), true);
					else
						userData->AddCard(cardInfo.cardnumber(), cardInfo.cardkind(), k == 6);

					if (cardInfo.cardnumber() != 100 && userData->GetPlayerStatus() != PLAYER_DIE && userData->m_Po == m_MyPo)
					{
						if (k < 2 || k == 6)
						{
							userData->ChangeCard(cardInfo.cardpo(), cardInfo.cardnumber(), cardInfo.cardkind(), true);
						}
					}
				}
			
			}

			// 패 보여주기 체크
			if (openCnt == 7)
			{
				if (m_GameKind == GameKind::GAMEKIND_HIGH_LOW)
				{
					userData->m_pJokboInfo->HighJokboCheck();
					userData->m_pJokboInfo->LowJokboCheck();

					if (userData->m_HighLowBettingKind == HighLowBettingKind::HIGH_BET || userData->m_HighLowBettingKind == HighLowBettingKind::SWING_BET)
					{
						for (CardData* _CardData : userData->m_pJokboInfo->GetHighJokboCardList())
							_CardData->m_pCard->runAction(CCMoveBy::create(0.3f, ccp(0.f, 20.f)));
					}

					if (userData->m_HighLowBettingKind == HighLowBettingKind::LOW_BET || userData->m_HighLowBettingKind == HighLowBettingKind::SWING_BET)
					{
						for (CardData* _CardData : userData->m_pJokboInfo->GetLowJokboCardList())
						{
							_CardData->m_pCard->cleanup();
							_CardData->m_pCard->runAction(CCMoveBy::create(0.3f, ccp(0.f, 20.f)));
						}
					}

					//switch (userData->m_HighLowBettingKind)
					//{
					//case HighLowBettingKind::HIGH_BET:
					//	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_HIGH);
					//	break;
					//case HighLowBettingKind::LOW_BET:
					//	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_LOW);
					//	break;
					//case HighLowBettingKind::SWING_BET:
					//	GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->DealerSound(EFX_DEALER_SWING);
					//	break;
					//default:
					//	break;
					//}
				}
				else
				{
					userData->m_pJokboInfo->HighJokboCheck();

					for (CardData* _CardData : userData->m_pJokboInfo->GetHighJokboCardList())
						_CardData->m_pCard->runAction(CCMoveBy::create(0.3f, ccp(0.f, 20.f)));
				}
			}

			if (m_GameKind == GameKind::GAMEKIND_HIGH_LOW)
			{
				userData->SetHighLowBettingKind(status.userhighlowbettingkind());
				if (m_PlayStatus == PlayStatus::PLAY_JOKBO_CHOICE)
				{
					if (userData->GetPlayerStatus() == PLAYER_INIT)
						SetHighLow(po, status.userhighlowbettingkind());
				}
				else if (m_PlayStatus > PlayStatus::PLAY_JOKBO_CHOICE)
				{
					if (userData->GetPlayerStatus() == PLAYER_INIT && status.userhighlowbettingkind() != HIGHLOW_NO_BET)
						SetHighLow(po, status.userhighlowbettingkind());
				}
			}
		}
	}

	if (m_GameKind == GameKind::GAMEKIND_BADUKI)
	{
		ChangeCardKind _kind = res.changecardkind();
		SetChangeCardKind(_kind);

		switch (_kind)
		{
		case ChangeCardKind::CHANGE_CARD_KIND_MORNING:
			SetBadugiSelectState(DAY_TYPE_MORNING);
			break;
		case ChangeCardKind::CHANGE_CARD_KIND_NOON:
			SetBadugiSelectState(DAY_TYPE_AFTERNOON);
			break;
		case ChangeCardKind::CHANGE_CARD_KIND_EVENING:
			SetBadugiSelectState(DAY_TYPE_NIGHT);
			break;
		}

		int _size = res.changecardcnt_size();
		for (int _UserIndex = 0; _UserIndex < _size; _UserIndex++)
		{
			ChangeCardCnt _ChangeCountData = res.changecardcnt(_UserIndex);
			int _dayPo = _ChangeCountData.po();
			int _daySize = _ChangeCountData.count_size();
			for (int _day = 0; _day < _daySize; _day++)
			{
				int _chanheCardNum = _ChangeCountData.count(_day);
				if (_chanheCardNum == -1)
				{
					continue;
				}
				PokerPlayerInfoCommonPanel* _pDayUserPanel = GetPlayerCommonPanel(_dayPo);
				if (_pDayUserPanel)
				{
					_pDayUserPanel->SetBadukiNumber(_day, _chanheCardNum, true);
				}
			}
		}
	}

	// 결과일 때 결과 처리
	if (m_PlayStatus >= PlayStatus::PLAY_RESULT && m_PlayStatus < PlayStatus::PLAY_SHARE_COMMUNITY_CARD)
	{
		int infosize = res.playergamestatus_size();
		int * index = new int[infosize];
		int64 * money = new int64[infosize];

		for (int i = 0; i < infosize; i++)
		{
			index[i] = i;
			money[i] = 0;
		}

		for (int i = 0; i < infosize; i++)
		{
			status = res.playergamestatus(i);
			index[i] = i;
			money[i] = status.inoutmoney();
		}

		// 획득 머니에 따라 소팅 시작.
		int max, tmp;
		int64 data1, data2;
		for (int i = 0; i < infosize - 1; i++)
		{
			max = i;
			for (int j = i + 1; j < infosize; j++)
			{
				data1 = money[index[max]];
				data2 = money[index[j]];

				if (data1 < data2)
					max = j;
			}

			if (i != max)
			{
				tmp = index[i];
				index[i] = index[max];
				index[max] = tmp;
			}
		}

		PokerResultPanel* _pPanel = GetPokerResultPanel();
		_pPanel->SetPlayerResultPaenlAllVisible(false);

		PotMoneyPanel* _potMoneyPanel = dynamic_cast<PotMoneyPanel*>(LayerManager::getSingletonPtr()->getLayer("PotMoney"));
		if (_potMoneyPanel)
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_TAKECHIP);
			_potMoneyPanel->ClearPotMoney();
		}

		PlayerData * playerData;

		for (int i = 0; i < infosize; i++)
		{
			status = res.playergamestatus(index[i]);

			if (i == 0) SetWinnerMoneyString(money[index[i]]);

			po = status.po();

			if (m_UserList[po] == nullptr)
				continue;

			playerData = m_UserList[po]->m_pPlayerData;

			_pPanel->SetData(i,
				m_GameKind,
				status.userwinkind(),
				playerData->m_NickName,
				m_MyPo == po,
				m_UserList[po]->m_pJokboInfo->GetHighJokboKind(),
				m_UserList[po]->m_pJokboInfo->GetLowJokboKind(),
				money[index[i]]
				);

			switch (status.userwinkind())
			{
				case GIVEUP_LOSE:
					GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_LOSE);
					DealerSound(EFX_DEALER_SORRY);
					break;
				case SWING_LOSE:
				case LOW_LOSE:
				case HIGH_LOSE:
				case NORMAL_LOSE:
					if (isBigAnimation())
					{
						m_UserList[po]->PlayCharacterAnimation(LOSE_BIG);
					}
					else
					{
						//TODO : 작은 패배 적용
						m_UserList[po]->PlayCharacterAnimation(LOSE_SMALL);
					}
					GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_LOSE);
					DealerSound(EFX_DEALER_SORRY);
					break;
				case GIVEUP_WIN:
				case NORMAL_WIN:
				case HIGH_WIN:
				case LOW_WIN:
				case SWING_WIN:
				case SPLIT_WIN:
				{
					Action_WinnerText(po, money[index[i]]);
					if (isBigAnimation())
					{
						m_UserList[po]->PlayCharacterAnimation(WIN_BIG);
					}
					else
					{
						m_UserList[po]->PlayCharacterAnimation(WIN_SMALL);
					}
					GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_CHEER);
					GameDataManager::getSingletonPtr()->PlayGameSound(GameEfxKind::EFX_GAME_WIN);
					DealerSound(EFX_DEALER_CELEBRATE);
					break;
				}
			}

			if (money[index[i]] > 0 && _potMoneyPanel)
			{
				_potMoneyPanel->Action_MovePotMoney(money[index[i]], GetUserPosition(po), 1.6f);
			}

		}
		_pPanel->ShowPanel();

		NX_SAFE_DELETE_ARRAY(index);
		NX_SAFE_DELETE_ARRAY(money);
	}

	return true;
}

bool GameRoomInfo::ChangeManager(char * msg, int size)
{
	if (!IsGameLoaded())
		return false;

	PlayerPoInfo res;
	res.ParseFromArray(msg, size);
	int po = res.po();
	int socketId = res.socketid();
	SetMaster(po);
	cout << "MASTER IS CHANGED!!" << endl;

	if (m_MasterPo == m_MyPo && m_CurrentUser >= 2)
	{
		ShowStartButton();
	}

	return true;
}

bool GameRoomInfo::IsGameLoaded()
{
	if (m_UserList[m_MyPo] == nullptr)
		return false;

	//if (m_UserList[m_MyPo]->GetPlayerStatus() <= PlayerStatus::PLAYER_PREPARE)
	//	return false;
	if (GameDataManager::getSingletonPtr()->GetGameSceneLoaded() != GameSceneLoadeStatus::GAME_SCENE_LOADED)
		return false;

	return true;
}

void GameRoomInfo::SetPotMoneyUpdate(PotMoneyState _state)
{
	m_PotMoneyEffectState = _state; 

	switch (_state)
	{
	case POT_NONE:
		break;
	case POT_READY:
		break;
	case POT_UPDATE:
		if (m_PotMoneyUpdateList.size() != 0 && m_PreMoneyUpdateList.size() != 0)
		{
			m_PrePotMoney = m_PreMoneyUpdateList[0];
			m_UpdatePotMoney = m_PotMoneyUpdateList[0];

			m_PreMoneyUpdateList.erase(m_PreMoneyUpdateList.begin());
			m_PotMoneyUpdateList.erase(m_PotMoneyUpdateList.begin());

			m_fPotMoneyEffectTime = POT_EFFECT_TIME;
			m_fPotMoneyUpdateTime = 0.f;
		}
		break;
	case POT_END:
		break;
	}
}

void GameRoomInfo::ShowHiddenCardAnimaion(bool _action)
{
	if (GetTopPanel() == nullptr)
		return;
	//GetTopPanel()->m_HiddenTouchButton->setEnable(false);
	//GetTopPanel()->m_HiddenTouchButton->getButtonSkelObject()->playAnimation("hidden_card_end");
	
	if (GetTopPanel()->m_bMoveHiddenCard == true)
		return;

	GetTopPanel()->m_bMoveHiddenCard = true;

	if (GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList.size() < 7)
		return;

	if (_action == false)
	{
		if (GetTopPanel()->m_HiddenTouchPanel->getButton("sbtn_hiddenback")->isEnabled() == false && GetTopPanel()->m_HiddenTouchPanel->isVisible() == false)
			return;

		GetTopPanel()->m_HiddenTouchPanel->getButton("sbtn_hiddenback")->setEnable(false);
		GetTopPanel()->m_HiddenTouchPanel->setTouchable(false);
		GetTopPanel()->m_HiddenTouchPanel->getSkel("skel_hiddenfront")->setVisible(false);
		GetTopPanel()->m_HiddenTouchPanel->setVisible(false);

		CCPoint _movePos = GetUserDataPtr(m_MyPo)->GetCardManager()->GetTableCardRect(6).origin;
		GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList[6]->m_pCard->setPosition(_movePos);


		if (GetTopPanel()->mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->isEnabled() == false && GetTopPanel()->mHiddenBigTouchPanel->isVisible() == false)
			return;

		GetTopPanel()->mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->setEnable(false);
		GetTopPanel()->mHiddenBigTouchPanel->setTouchable(false);
		GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hiddenfront_big")->setVisible(false);
		GetTopPanel()->mHiddenBigTouchPanel->setVisible(false);

		_movePos = GetUserDataPtr(m_MyPo)->GetCardManager()->GetTableCardRect(6).origin;
		GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList[6]->m_pCard->setPosition(_movePos);

		return;
	}

	GetTopPanel()->m_HiddenTouchPanel->getSkel("skel_hiddenfront")->playAnimation("hiddenfront_end");
	GetTopPanel()->m_HiddenTouchPanel->getSkel("skel_hiddenfront")->setVisible(false);
	CCPoint _movePos = GetUserDataPtr(m_MyPo)->GetCardManager()->GetTableCardRect(6).origin;
	GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList[6]->m_pCard->Action_MoveToCard(_movePos);
	GetTopPanel()->m_HiddenTouchPanel->runAction(CCMoveTo::create(0.2f, GetTopPanel()->m_posStartHiddenPanel));
	

	GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hiddenfront_big")->playAnimation("hiddenfront_big_end");
	GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hiddenfront_big")->setVisible(false);
	_movePos = GetUserDataPtr(m_MyPo)->GetCardManager()->GetTableCardRect(6).origin;
	GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList[6]->m_pCard->Action_MoveToCard(_movePos);

	GetTopPanel()->mHiddenBigTouchPanel->runAction(CCMoveTo::create(0.2f, GetTopPanel()->mBigPosMoveHiddenPanel));
	//배경 두개 안 보이게 한다.
	GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hidden_black")->setScale(2.f);
	GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hidden_light")->setVisible(false);
	GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hidden_black")->setVisible(false);

}

void GameRoomInfo::ShowLastCardAnimation(int _po)
{
	//if (_po == m_MyPo)
	//{
	//	ShowHiddenCardAnimaion();
	//}

	CardManager* _pCardManager = GetUserDataPtr(_po)->GetCardManager();
	for (int _i = 0; _i < 7; _i++)
	{
		
		_pCardManager->m_CardList[_i]->m_pCard->SetBack(false);

		//left
		CCPoint _moveTo = _pCardManager->GetTableCardRect(0).origin;
		_pCardManager->ActionMoveCard(_i, _moveTo, 0.2f, 1.f, 0.f);

		_moveTo = _pCardManager->GetTableCardRect(_i).origin;
		_pCardManager->ActionMoveCard(_i, _moveTo, 0.3f, 1.f, 0.5f);

		_pCardManager->m_CardList[_i]->m_pCard->Action_FlipOpen(0.4f + (0.02f * _i), true);

		_pCardManager->m_CardList[_i]->m_pCard->PlayCardEffect(CARD_EFFECT_NO);
		

		//center 
		//CCPoint _moveTo = _pCardManager->GetTableCardRect(3).origin;
		//_pCardManager->ActionMoveCard(_i, _moveTo, 0.1f, 1.f, 0.f);

		//_moveTo = _pCardManager->GetTableCardRect(_i).origin;
		//_pCardManager->ActionMoveCard(_i, _moveTo, 0.1f, 1.f, 0.2f);

		//_pCardManager->m_CardList[_i]->m_pCard->Action_FlipOpen(0.4f + (0.03f * _i));
	}
}

void GameRoomInfo::ShowLastBadugiAnimation(int _po)
{
	CardManager* _pCardManager = GetUserDataPtr(_po)->GetCardManager();
	for (int _i = 0; _i < 4; _i++)
	{
		//int _idx = _pCardManager->m_CardList[_i]->m_idx;
		_pCardManager->m_CardList[_i]->m_pCard->SetBack(false);

		//left
		CCPoint _moveTo = _pCardManager->GetTableCardRect(0).origin;
		_pCardManager->ActionMoveCard(_i, _moveTo, 0.2f, 1.f, 0.f);

		//_moveTo = _pCardManager->GetTableCardRect(_idx).origin;
		//_pCardManager->ActionMoveCard(_i, _moveTo, 0.3f, 1.f, 0.5f);

		//_pCardManager->m_CardList[_i]->m_pCard->Action_BadugiFlipOpen(0.4f + (0.02f * _idx));
		_pCardManager->m_CardList[_i]->m_pCard->PlayCardEffect(CARD_EFFECT_NO);
	}
}

void GameRoomInfo::SetPlayerEmotion(char* data, int size)
{
	EmoticonRoomRes res;
	res.ParseFromArray(data, size);

	RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(res.po());
	if (_pPlayer == nullptr)
		return;
	
	if (_pPlayer->m_pPlayerData->m_UID != res.socketid())
		return;

	if (_pPlayer->m_bEmotionBlock == true)
		return;

	switch (res.emoticonidx())
	{
	case EMOTION_ANGRY:
		_pPlayer->PlayCharacterAnimation(GESTURE_ANGRY);
		break;
	case EMOTION_GOOD:
		_pPlayer->PlayCharacterAnimation(GESTURE_GOOD);
		break;
	case EMOTION_CELEBRATE:
		_pPlayer->PlayCharacterAnimation(GESTURE_CELEBRATE);
		break;
	case EMOTION_LAUGH:
		_pPlayer->PlayCharacterAnimation(GESTURE_LAUGH);
		break;
	case EMOTION_PLEASURE:
		_pPlayer->PlayCharacterAnimation(GESTURE_PLEASURE);
		break;
	case EMOTION_HURRY:
		_pPlayer->PlayCharacterAnimation(GESTURE_HURRY);
		break;
	case EMOTION_SADNESS:
		_pPlayer->PlayCharacterAnimation(GESTURE_SADNESS);
		break;
	case EMOTION_SORRY:
		_pPlayer->PlayCharacterAnimation(GESTURE_SORRY);
		break;
	case EMOTION_SURPRIZE:
		_pPlayer->PlayCharacterAnimation(GESTURE_SURPRIZE);
		break;
	case EMOTION_THANKS:
		_pPlayer->PlayCharacterAnimation(GESTURE_THANKS);
		break;
	default:
		break;
	}

}

void GameRoomInfo::ShowPlayGameStates(char* data, int size)
{
	GamePlayStatcsInfoRes res;
	res.ParseFromArray(data, size);

	GameRoomInfo* _pRoomInfo = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr();
	if (_pRoomInfo)
	{
		_pRoomInfo->m_avgPotMoney = res.avgpotmoney();
		if (LayerManager::getSingletonPtr()->hasLayer("OptionPanel"))
		{
			InGameOptionPanel* _pPanel = dynamic_cast<InGameOptionPanel*>(LayerManager::getSingletonPtr()->getLayer("OptionPanel"));
			_pPanel->SetOptionValue();
		}
	}
		
}

void GameRoomInfo::ShowPlayerStates(char* data, int size)
{
	PlayerPlayStatcsInfoRes res;
	res.ParseFromArray(data, size);

	int32 _po = res.po();

	RoomUserData* _pPlayer = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(_po);

	_pPlayer->m_IsStatcsUpdated = true;
	_pPlayer->m_CurWin = res.curwin();
	_pPlayer->m_CurLose = res.curlose();
	_pPlayer->m_AcqMoney = res.acqmoney();
	_pPlayer->m_MadeCount = res.madecount();

	int _clientIndex = GameDataManager::getSingletonPtr()->ServerToClientIndex(_po);
	GetTopPanel()->setPlayerInfoUserOptionPanel(_clientIndex, true);
}

void GameRoomInfo::ShowLastLound()
{
	PokerTopPanel* _pPanel = GetTopPanel();
	if (_pPanel == nullptr)
		return;

	if (isBigAnimation())
	{
		_pPanel->ShowLastRoundEffect(2);
	}
	else
	{
		_pPanel->ShowLastRoundEffect(1);
	}
	
}

void GameRoomInfo::ShowDownState(char* data, int size)
{
	ShowDownUserInfo res;
	res.ParseFromArray(data, size);

	PokerTopPanel* _pPanel = GetTopPanel();
	if (_pPanel == nullptr)
		return;

	if (isBigAnimation())
	{
		_pPanel->ShowLastRoundEffect(2);
	}
	else
	{
		_pPanel->ShowLastRoundEffect(1);
	}

	int userSize = res.cardinfo_size();
	ShareCardInfo shareCardInfo;
	RoomUserData * userData;
	CardInfo cardInfo;
	int _DealerReaction = -1;

	for (int i = 0; i < userSize; i++)
	{
		shareCardInfo = res.cardinfo(i);
		userData = GetUserDataPtr(shareCardInfo.po());

		if (shareCardInfo.po() == m_MyPo)
			continue;

		if (userData == nullptr)
			return;

		for (int i = 0, j = shareCardInfo.cardinfo_size(); i < j; i++)
		{
			cardInfo = shareCardInfo.cardinfo(i);
			if (cardInfo.cardnumber() != -1)
			{
				userData->ChangeCard(cardInfo.cardpo(), cardInfo.cardnumber(), cardInfo.cardkind(), true);
				//cout << "User : " << highLowCardInfo.po() << " card(number/kind) : " << cardInfo.cardnumber() << "/" << cardInfo.cardkind() << "\n\n" << endl;
			}
		}
	}

}


void GameRoomInfo::ShowBadugiSelectCard(char* data, int size)
{
	//TODO : SHOW BADUGI SELECT CARD PANEL
	
	ChangeCardInfo res;
	res.ParseFromArray(data, size);
	SetStatus(PlayStatus::PLAY_CHANGE_CARD);

	ChangeCardKind _kind = res.changecardkind();
	SetChangeCardKind(_kind);

	RoomUserData* _pUserData = GetUserDataPtr(m_MyPo);
	if (_pUserData != nullptr)
	{
		if (_pUserData->GetPlayerStatus() == PLAYER_INIT && m_isReplayData != true)
		{
			if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel"))
			{
				//_pUserData->SelectBadugiRecommendCard();
				//_pUserData->SetBadugiSelectedCardEffect(0.2f);
				BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));
				_pSelectCardPanel->ShowBadugiSelectCardPanel(true);
			}
		}
	}

	m_bSendWait = true;
	m_bSendChanageRequest = false;
	m_bSendPassRequest = false;

	switch(_kind)
	{
	case ChangeCardKind::CHANGE_CARD_KIND_MORNING:
		SetBadugiSelectState(DAY_TYPE_MORNING);
		break;
	case ChangeCardKind::CHANGE_CARD_KIND_NOON:
		SetBadugiSelectState(DAY_TYPE_AFTERNOON);
		break;
	case ChangeCardKind::CHANGE_CARD_KIND_EVENING:
		SetBadugiSelectState(DAY_TYPE_NIGHT);
		break;
	}
}

void GameRoomInfo::ChangeBadugiSelectCard(char* data, int size)
{
	//TODO : CHANGE BADUGI SELECT CARD
	ShareCardInfo res;
	res.ParseFromArray(data, size);

	RoomUserData * userData = GetUserDataPtr(res.po());

	if (userData == nullptr)
		return;

	userData->PlayCharacterAnimation(IDLE);

	CardInfo cardInfo;
	int _size = res.cardinfo_size();
	for (int i = 0, j = _size; i < j; i++)
	{
		cardInfo = res.cardinfo(i);
		if (cardInfo.cardnumber() != -1)
		{
			userData->ChangeCard(cardInfo.cardpo(), cardInfo.cardnumber(), cardInfo.cardkind(), false);
		}
	}

	if (_size != 0)
	{
		m_pDealer->playAnimation("dealing_ready", false, false, 0.6f);
		m_pDealer->appendAnimation("dealing_loop", false, false, 2.f);
		m_pDealer->appendAnimation("idle", true);

		m_pDealerUnder->playAnimation("dealing_ready", false, false, 0.6f);
		m_pDealerUnder->appendAnimation("dealing_loop", false, false, 2.f);
		m_pDealerUnder->appendAnimation("idle", true);

		m_DealerTime = 0;

		userData->PlaySoundBadugiSelectChangeCard(_size);
	}
	else
	{
		userData->PlayCharacterSound(EFX_PASS);
	}

	if (m_isReplayData == true)
	{
		if (_size != 0)
		{
			if (res.po() == m_MyPo)
			{
				SetBadugiSortTime(1.2f);
			}
			else
			{
				userData->BadugiSortCard(1.2f);
			}
		}
		else
		{
			userData->BadugiSortCard();
		}
	}
	else
	{
		if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel") && res.po() == m_MyPo)
		{
			BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));
			if (_pSelectCardPanel->isVisible())
			{
				_pSelectCardPanel->ShowBadugiSelectCardPanel(false);
			}

			if (_size != 0)
			{
				SetBadugiSortTime(1.2f);
			}
			else
			{
				userData->PlayCharacterSound(EFX_PASS);
				userData->BadugiSortCard();
				userData->SelectBadugiRecommendCard();
				userData->SetBadugiSelectedCardEffect(0.4f);
			}
		}
	}

	PokerPlayerInfoCommonPanel* _pPanel = GetPlayerCommonPanel(userData->m_Po);
	if (_pPanel)
	{
		_pPanel->turnOffTimeGauge();
		int _dayKind = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_dayState;
		_pPanel->SetBadukiNumber(_dayKind, _size, true);
	}
	
}

void GameRoomInfo::ShowBigGameEffect()
{
	GetBackgroundPanel()->ShowCenterBoxEffect(1.3f);

	if (m_bBigGameAction == false)
	{
		m_bBigGameAction = true;
		DealerAnimation(DEALER_REACT_BIGPOT);
	}

	SkelObject* _pPotMoneyEffect = GetTopPanel()->getSkel("skel_potmoney");
	if (_pPotMoneyEffect)
	{

		if (IsBigGame() == 1)
		{
			if (!_pPotMoneyEffect->isPlayingAnimation())
			{
				DealerSound(DealerEfxKind::EFX_DEALER_BIGPOT1);
				_pPotMoneyEffect->setVisible(true);
				_pPotMoneyEffect->playAnimation("potmoney_start");
				_pPotMoneyEffect->appendAnimation("potmoney_loop", true);
			}
		}
		else if (IsBigGame() == 2)
		{
			if (_pPotMoneyEffect->isPlayingAnimation())
			{
				if (_pPotMoneyEffect->getCurrentAnimation() != "bigpotmoney_start" && _pPotMoneyEffect->getCurrentAnimation() != "bigpotmoney_loop")
				{
					int _kind = EFX_DEALER_BIGPOT2 + rand() % 2;
					DealerSound((DealerEfxKind)_kind);
					GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_TENSION, true, true);
					_pPotMoneyEffect->setVisible(true);
					_pPotMoneyEffect->playAnimation("bigpotmoney_start");
					_pPotMoneyEffect->appendAnimation("bigpotmoney_loop", true);
				}
			}
			else
			{
				int _kind = EFX_DEALER_BIGPOT2 + rand() % 2;
				DealerSound((DealerEfxKind)_kind);
				_pPotMoneyEffect->setVisible(true);
				_pPotMoneyEffect->playAnimation("bigpotmoney_start");
				_pPotMoneyEffect->appendAnimation("bigpotmoney_loop", true);
			}
		}

	}
}

void GameRoomInfo::ShowStartGameInfomation()
{
	if (m_pDealerTextBubble == nullptr)
		return;

	string _infoText = "[";  //"[NO." + StringConverter::toString(GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetRoomIdx()) + "/";

	switch (GetBettingRule())
	{
	case BettingRule::RULE_FOUR_CARD:
		_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_RULE_FOUR_CARD");
		break;
	case BettingRule::RULE_FIVE_CARD:
		_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_RULE_FIVE_CARD");
		break;
	case BettingRule::RULE_SIX_CARD:
		_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_RULE_SIX_CARD");
		break;
	}
	//SeedMoney
	_infoText += "/" + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(GetSeedMoney()), 1);
	_infoText += GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT");
	_infoText += "]" + GameStringDepot::getSingletonPtr()->getString("TXT_START_GAME_ROOM_INFOMATION");

	m_pDealerTextBubble->getSkel("skel_dealer_bubbler")->playAnimation("dealer_bubbler_start");
	m_pDealerTextBubble->getSkel("skel_dealer_bubbler")->appendAnimation("dealer_bubbler_stay");
	
	m_pDealerTextBubble->getSkel("skel_dealer_bubbler")->setVisible(true);


	m_pDealerTextBubble->getLabel("txt_dealer_speech_under")->setString(_infoText.c_str());
	m_pDealerTextBubble->getLabel("txt_dealer_speech_under")->setOpacity(0);
	m_pDealerTextBubble->getLabel("txt_dealer_speech_under")->runAction(CCFadeIn::create(0.1f));
	m_pDealerTextBubble->getLabel("txt_dealer_speech")->setString(_infoText.c_str());
	m_pDealerTextBubble->getLabel("txt_dealer_speech")->setOpacity(0);
	m_pDealerTextBubble->getLabel("txt_dealer_speech")->runAction(CCFadeIn::create(0.1f));

	m_pDealerTextBubble->getLabel("txt_dealer_speech_under")->setVisible(true);
	m_pDealerTextBubble->getLabel("txt_dealer_speech")->setVisible(true);
}

void GameRoomInfo::HideStartGameInfomation()
{
	m_pDealerTextBubble->getSkel("skel_dealer_bubbler")->playAnimation("dealer_bubbler_end");
	m_pDealerTextBubble->getLabel("txt_dealer_speech_under")->setVisible(false);
	m_pDealerTextBubble->getLabel("txt_dealer_speech")->setVisible(false);
}

void GameRoomInfo::StopDealerTextBubble()
{
	m_pDealerTextBubble->stopAllActions();
	m_pDealerTextBubble->getLabel("txt_dealer_speech_under")->setVisible(false);
	m_pDealerTextBubble->getLabel("txt_dealer_speech")->setVisible(false);
}

void GameRoomInfo::TouchHiddenCard()
{
	
	//GetTopPanel()->m_HiddenTouchButton->setEnable(false);
	//GetTopPanel()->m_HiddenTouchButton->getButtonSkelObject()->playAnimation("hidden_card_end");
	mShowTouchPanel = true;
	ShowHiddenCardAnimaion();

	SetMyMadeCheckTime(0.3f);
	RoomUserData * userData = GetUserDataPtr(m_MyPo);
	if (userData == nullptr)
		return;

	userData->LastCardCheck(false);

}

void GameRoomInfo::SetHiddenTouch()
{
	if (GetTopPanel() == nullptr)
		return;

	if (getHiddenCardState() == 1) {
		GetTopPanel()->m_HiddenTouchPanel->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(0.2f), CCMoveTo::create(0.2f, GetTopPanel()->m_posMoveHiddenPanel)));

		CCPoint _movePos = GetUserDataPtr(m_MyPo)->GetCardManager()->GetTableCardRect(6).origin + ccp(150, 0);
		GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList[6]->m_pCard->Action_MoveToCard(_movePos, 0.2f);

		int _cardId = GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList[6]->m_pCard->GetCardId();
		PokerCardSetContainer::iterator findIter = PokerCardHelper::getSingleton().getPockerSet().find(_cardId);
		GetTopPanel()->m_HiddenTouchPanel->getSkel("skel_hiddenfront")->setSkin(findIter->second);

		GetTopPanel()->m_HiddenTouchPanel->setVisible(true);
		GetTopPanel()->m_HiddenTouchPanel->setTouchable(false);
		GetTopPanel()->m_HiddenTouchPanel->getSkel("skel_hiddenfront")->setVisible(true);

		GetTopPanel()->m_bTouchHiddenCard = true;

		GetTopPanel()->m_HiddenTouchPanel->getSkel("skel_hiddenfront")->playAnimation("hiddenfront_start");
		GetTopPanel()->m_HiddenTouchPanel->getSkel("skel_hiddenfront")->appendAnimation("hiddenfront_stay", true);
		GetTopPanel()->m_HiddenTouchPanel->getSkel("skel_hidden_card_start")->playAnimation("hidden_card_start");
		GetTopPanel()->m_HiddenTouchPanel->getSkel("skel_hidden_card_start")->appendAnimation("hidden_card_stay", true);
		GetTopPanel()->m_HiddenTouchPanel->getButton("sbtn_hiddenback")->getButtonSkelObject()->playAnimation("hiddenback_start");
		GetTopPanel()->m_HiddenTouchPanel->getButton("sbtn_hiddenback")->getButtonSkelObject()->appendAnimation("hiddenback_stay", true);
		GetTopPanel()->m_HiddenTouchPanel->getButton("sbtn_hiddenback")->setEnable(true);
	}
	else if (getHiddenCardState() == 2) {
		GetTopPanel()->mHiddenBigTouchPanel->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(0.2f), CCMoveTo::create(0.2f, GetTopPanel()->mBigPosMoveHiddenPanel)));

		CCPoint _movePos = GetUserDataPtr(m_MyPo)->GetCardManager()->GetTableCardRect(6).origin + ccp(150, 0);
		GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList[6]->m_pCard->Action_MoveToCard(_movePos, 0.2f);

		int _cardId = GetUserDataPtr(m_MyPo)->GetCardManager()->m_CardList[6]->m_pCard->GetCardId();
		PokerCardSetContainer::iterator findIter = PokerCardHelper::getSingleton().getPockerSet().find(_cardId);
		GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hiddenfront_big")->setSkin(findIter->second);

		GetTopPanel()->mHiddenBigTouchPanel->setVisible(true);
		GetTopPanel()->mHiddenBigTouchPanel->setTouchable(false);
		GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hiddenfront_big")->setVisible(true);

		GetTopPanel()->m_bTouchHiddenCard = true;

		GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hiddenfront_big")->playAnimation("hiddenfront_big_start");
		GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hiddenfront_big")->appendAnimation("hiddenfront_big_stay", true);
		GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hidden_card_start")->playAnimation("hidden_card_start");
		GetTopPanel()->mHiddenBigTouchPanel->getSkel("skel_hidden_card_start")->appendAnimation("hidden_card_stay", true);
		GetTopPanel()->mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->getButtonSkelObject()->playAnimation("hiddenback_big_start");
		GetTopPanel()->mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->getButtonSkelObject()->appendAnimation("hiddenback_big_stay", true);
		GetTopPanel()->mHiddenBigTouchPanel->getButton("sbtn_hiddenback_big")->setEnable(true);
	}	
}

void GameRoomInfo::SetHiddenCheck(bool _hidden)
{
	m_IsHiddenCheck = _hidden;
	SetHiddenTouch();
}

void GameRoomInfo::PlayShowDownEfx()
{
	if (m_bShowDown)
		return;

	m_bShowDown = true;
	if (GetGameKind() == GameKind::GAMEKIND_BADUKI)
	{
		//case badugi
	}
	else
	{
		GetTopPanel()->m_bMoveHiddenCard = false;
		ShowHiddenCardAnimaion(false);
	}
	DealerSound(DealerEfxKind::EFX_DEALER_SHOWDOWN);

	
}

void GameRoomInfo::SetChangeCardKind(ChangeCardKind kind)
{
	m_changeCardKind = kind;
}

void GameRoomInfo::SetBadugiSelectState(int _kind)
{
	PokerBackgroundPanel* _pPanel = GetBackgroundPanel();
	if (_pPanel)
	{
		_pPanel->setBadukiDayPanel(_kind);
		
		if (_kind >= DAY_TYPE_END)
			return;
	}

	GameDataManager::getSingletonPtr()->SetBadugiDayKind(_kind);

	if (_kind == DAY_TYPE_MORNING)
	{
		DealerSound(EFX_DEALER_MORNING);
	}
	else if (_kind == DAY_TYPE_AFTERNOON)
	{
		DealerSound(EFX_DEALER_DAY);
	}
	else if (_kind == DAY_TYPE_NIGHT)
	{
		DealerSound(EFX_DEALER_NIGHT);
	}

	PokerTopPanel* _pTopPanel = GetTopPanel();
	if(_pTopPanel)
	{
		_pTopPanel->ShowBadugiEffect(_kind);
	}
}

void GameRoomInfo::ShowChangeCardSeletPanel(char * data, int size)
{
	PlayerPoInfo res;
	res.ParseFromArray(data, size);
	
	int _po = res.po();

	RoomUserData* _pUserData = GetUserDataPtr(_po);
	if (_pUserData != nullptr)
	{
		if (_pUserData->GetPlayerStatus() != PLAYER_INIT)
			return;

		if (_pUserData->m_pMyCharater != nullptr)
		{
			if (_pUserData->GetPlayerStatus() != PLAYER_SEE)
			{
				CharacterAniKind _kind = (CharacterAniKind)(THINK1 + (rand() % 2));
				_pUserData->PlayCharacterAnimation(_kind);
			}
		}

		PokerPlayerInfoCommonPanel* _pPanel = GetPlayerCommonPanel(_pUserData->m_Po);
		_pPanel->turnOnTimeGauge();

		if (_pUserData->m_Po == m_MyPo)
		{
			if (m_bSendChanageRequest == true)
			{
				SendBadugiChangeCardReq();
				m_bSendChanageRequest = false;

				if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel") && m_isReplayData == false)
				{
					BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));
					if (_pSelectCardPanel->isVisible() == true)
					{
						_pSelectCardPanel->ShowBadugiSelectCardPanel(false);
						_pSelectCardPanel->SetEnableButton(true);
					}
				}

			}
			else if (m_bSendPassRequest == true)
			{
				SendBadugiChangePassReq();
				m_bSendPassRequest = false;

				if (LayerManager::getSingletonPtr()->hasLayer("BadugiSelectCardPanel") && m_isReplayData == false)
				{
					BadugiSelectCardPanel* _pSelectCardPanel = dynamic_cast<BadugiSelectCardPanel*>(LayerManager::getSingletonPtr()->getLayer("BadugiSelectCardPanel"));
					if (_pSelectCardPanel->isVisible() == true)
					{
						_pSelectCardPanel->ShowBadugiSelectCardPanel(false);
						_pSelectCardPanel->SetEnableButton(true);
					}
				}
			}
			else
			{
				m_bSendWait = false;
			}
		}
	}
}

void GameRoomInfo::SendBadugiChangeCardReq()
{
	ChangeCardKind _DayKind = GameDataManager::getSingletonPtr()->GetBadugiDayKind();
	if (_DayKind == CHANGE_CARD_KIND_NO)
		return;

	RoomUserData* _pUser = GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->GetUserDataPtr(m_MyPo);
	vector<int> _cardList;
	for (int _i = 0; _i < 4; _i++)
	{
		int _idx = _pUser->GetCardManager()->m_CardList[_i]->m_idx;
		if (GameDataManager::getSingletonPtr()->GetGameRoomInfoPtr()->m_SelectedNumber[_idx] == true)
		{
			_cardList.push_back(_i);
		}
	}

	TCPService::getSingletonPtr()->SendChangeCardReq(_DayKind, _cardList);
}

void GameRoomInfo::SendBadugiChangePassReq()
{
	ChangeCardKind _DayKind = GameDataManager::getSingletonPtr()->GetBadugiDayKind();
	if (_DayKind == CHANGE_CARD_KIND_NO)
		return;

	vector<int> _cardList;

	TCPService::getSingletonPtr()->SendChangeCardReq(_DayKind, _cardList);
}

void GameRoomInfo::BadugiShareCard(char * data, int size)
{
	if (m_PlayStatus != PLAY_SHARE_CARD)
		SetStatus(PlayStatus::PLAY_SHARE_CARD);

	ShareCardInfoList res;
	ShareCardInfo shareCardInfo;
	res.ParseFromArray(data, size);

	if (res.sharecardinfo_size() <= 0)
	{
		shareCardInfo.ParseFromArray(data, size);

		RoomUserData * userData;
		CardInfo cardInfo;
		float _delayTime = 0.f;

		userData = GetUserDataPtr(shareCardInfo.po());

		if (userData == nullptr)
			return;

		for (int i = 0, j = shareCardInfo.cardinfo_size(); i < j; i++)
		{
			cardInfo = shareCardInfo.cardinfo(i);
			if (cardInfo.cardnumber() != -1)
			{
				DealerAnimation(DealerAniKind::DEALER_DEALING_SHOOT);
				int _idx = userData->m_pCardManager->m_CardList.size();

				if (m_isReplayData == true)
				{
					userData->BadugiAddCard(cardInfo.cardnumber(), cardInfo.cardkind(), false);
				}
				else
				{
					userData->BadugiAddCard(cardInfo.cardnumber(), cardInfo.cardkind());
				}
				//userData->BadugiAddCard(cardInfo.cardnumber(), cardInfo.cardkind(), false, true, _delayTime);

				CCRect _move = userData->m_pCardManager->GetTableCardRect(_idx);
				userData->m_pCardManager->ActionShareMoveCard(_idx, _move.origin, false, _delayTime);
				//m_isSelectedCard
			}
		}

		SetBoss(shareCardInfo.bosspo());

		return;
	}
	
	RoomUserData * userData;
	CardInfo cardInfo;
	float _delayTime = 0.f;
	for (int k = 0, l = res.sharecardinfo_size(); k < l; k++)
	{
		shareCardInfo = res.sharecardinfo(k);

		userData = GetUserDataPtr(shareCardInfo.po());

		if (userData == nullptr)
			continue;
		for (int i = 0, j = shareCardInfo.cardinfo_size(); i < j; i++)
		{
			_delayTime += 0.1f;

			cardInfo = shareCardInfo.cardinfo(i);
			if (cardInfo.cardnumber() != -1)
			{
				DealerAnimation(DealerAniKind::DEALER_DEALING_SHOOT);
				int _idx = userData->m_pCardManager->m_CardList.size();

				//if (m_isReplayData == true)
				//{
				//	userData->BadugiAddCard(cardInfo.cardnumber(), cardInfo.cardkind(), false);
				//}
				//else
				//{
				//	userData->BadugiAddCard(cardInfo.cardnumber(), cardInfo.cardkind());
				//}
				userData->BadugiAddCard(cardInfo.cardnumber(), cardInfo.cardkind(), false, true, _delayTime);

				CCRect _move = userData->m_pCardManager->GetTableCardRect(_idx);
				userData->m_pCardManager->ActionShareMoveCard(_idx, _move.origin, false, _delayTime);
				//m_isSelectedCard
			}
		}
		if (k == 0)
			SetBoss(shareCardInfo.bosspo());
	}
}

void GameRoomInfo::ResetBadugiSelectNumber()
{
	for (int _i = 0; _i < 4; _i++)
		m_SelectedNumber[_i] = false;
}


void GameRoomInfo::InitCommunityCard()
{
	for (int _i = 0; _i < 5; _i++)
	{
		CCPoint _pos =  GetBackgroundPanel()->m_HoldemCommunityCard[_i]->getPosition();
		m_CommunityCardRect[_i] = CCRectMake(_pos.x, _pos.y, 45, 66);
		m_CommunityCardRectBig[_i] = CCRectMake(363 + (72*_i), DESIGN_HEIGHT - 211, 72, 106);
	}

	m_CommunityCardBackBoard = new SkelObject();
	m_CommunityCardBackBoard->setSkelAnim("ui/card_back_8888.json");
	m_CommunityCardBackBoard->setVisible(false);

	if (LayerManager::getSingleton().hasLayer("CardLayer") == true)
	{
		Panel* _pCardPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("CardLayer"));
		if (_pCardPanel)
		{
			m_CommunityCardBackBoard->setPosition(ccp(507, DESIGN_HEIGHT - 197));
			_pCardPanel->addChild(m_CommunityCardBackBoard, 19);
			m_CommunityCardBackBoard->release();
		}
	}
}

void GameRoomInfo::ReleaseCommunityCard()
{
	if (m_CommunityCardBackBoard)
	{
		m_CommunityCardBackBoard->removeFromParentAndCleanup(true);
		ResetCommunityCard();
	}
}

void GameRoomInfo::ShowCommnityBig(bool _big)
{
	if (m_bCommunityCardProcessing == true)
		return;


	m_isBigCommunityCard = _big;

	int _size = m_CommunityCardList.size();
	for (int _i = 0; _i < _size; _i++)
	{
		PokerCardWidget* _pCard = m_CommunityCardList[_i]->m_pCard;

		if (_big == true)
		{
			_pCard->GetCardSkelObj()->playAnimation("smallcard_"+ StringConverter::toString(_i+1) +"_off");
			_pCard->GetCardSkelObj()->appendAnimation("smallcard_" + StringConverter::toString(_i + 1) + "_offstay");
			_pCard->runAction(CCMoveTo::create(0.1f, m_CommunityCardRectBig[_i].origin));
			_pCard->setZOrder(20);

			if (_pCard->ChangeCommunityCardEffect() == true)
			{
				_pCard->PlayCardEffect(CARD_EFFECT_BIG_MADE);
			}
		}
		else
		{
			_pCard->GetCardSkelObj()->playAnimation("smallcard_" + StringConverter::toString(_i + 1) + "_on");
			_pCard->GetCardSkelObj()->appendAnimation("smallcard_" + StringConverter::toString(_i + 1) + "_stay");
			_pCard->runAction(CCMoveTo::create(0.1f, m_CommunityCardRect[_i].origin));
			_pCard->setZOrder(0);

			if (_pCard->ChangeCommunityCardEffect() == true)
			{
				_pCard->PlayCardEffect(CARD_EFFECT_SMALL_MADE1 + _i);
			}
		}
	}

	if (_big == true)
	{
		m_CommunityCardBackBoard->playAnimation("back_5_start");
		m_CommunityCardBackBoard->appendAnimation("back_5_stay");
		m_CommunityCardBackBoard->setVisible(true);
	}
	else
	{
		m_CommunityCardBackBoard->setVisible(false);
	}

	SetCommunityCardProcessTime(0.2f);
}

void GameRoomInfo::SetCommunityCard(char* data, int size)
{
	CardInfo res;
	res.ParseFromArray(data, size);

	//int _idx = m_CommunityCardList.size();
	AddCommunityCard(res.cardnumber(), res.cardkind(), false);

	if (GetUserDataPtr(m_MyPo)->GetPlayerStatus() != PLAYER_SEE && GetUserDataPtr(m_MyPo)->GetPlayerStatus() != PLAYER_DIE)
	{
		SetMyMadeCheckTime(0.5f);
	}

	NotiFocusPanel* pPanel = nullptr;
	if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HOLDEM) {
		if (NotiDataManager::getSingleton().getHoldemNoti() == NotiData_eNotiType_HoldemComunityCard) {
			//창이 없으면 뿌려주고 visible 이면 끈다		
			if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
				pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
			}
			else {
				PanelHelper::pushNotiFocusPanel(NotiData_eNotiType_HoldemComunityCard);
			}
			pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
		}
	}

	if (pPanel && NotiDataManager::getSingleton().getHoldemNoti() == NotiData_eNotiType_HoldemComunityCard) {
		pPanel->setVisible(true);
		pPanel->setSubList();
	}		
}

void GameRoomInfo::AddCommunityCard(int _number, int _kind, bool _showBack, bool _action)
{
	int _cardIdx = (_number * 4) + _kind;

	if (_number == 100 && _kind == -1)
	{
		_showBack = true;
		_cardIdx = 0;
	}

	if (_cardIdx < 52)
	{
		CardData* _pCardData = new CardData();
		_pCardData->m_Number = _number;
		_pCardData->m_Kind = _kind;
		_pCardData->m_idx = m_CommunityCardList.size();
		_pCardData->m_pCard = new PokerCardWidget(m_CommunityCardList.size(), _cardIdx, PokerCardWidget::PokerCardWidetBig);
		//_pCardData->m_pCard->setZOrder(_pCardData->m_idx);
		

		if (_showBack == true)
		{
			_pCardData->m_pCard->PlayCardEffect(CARD_EFFECT_SMALL_DUST1 + _pCardData->m_idx, 0.2f);
			//_pCardData->m_pCard->SetBack(false);
		}
		else
		{
			_pCardData->m_pCard->PlayCardEffect(CARD_EFFECT_SMALL_DUST1 + _pCardData->m_idx, 0.2f);
		}

		m_CommunityCardList.push_back(_pCardData);

		if (LayerManager::getSingleton().hasLayer("CardLayer") == true)
		{
			Panel* _pCardPanel = dynamic_cast<Panel*>(LayerManager::getSingleton().getLayer("CardLayer"));
			if (_pCardPanel)
			{
				_pCardData->m_pCard->setPosition(m_CommunityCardRect[m_CommunityCardList.size() - 1].origin);
				_pCardPanel->addChild(_pCardData->m_pCard, 0);
				_pCardData->m_pCard->release();
			}
		}

		if (_action == true)
		{
			SetCommunityCardProcessTime(0.4f);
			if (m_isBigCommunityCard == true)
			{
				ActionMoveCommunityCard(_pCardData->m_idx, m_CommunityCardRectBig[m_CommunityCardList.size() - 1].origin);
			}
			else
			{
				ActionMoveCommunityCard(_pCardData->m_idx, m_CommunityCardRect[m_CommunityCardList.size() - 1].origin);
			}
		}
		else
		{
			if (m_isBigCommunityCard == true)
			{
				m_CommunityCardList[_pCardData->m_idx]->m_pCard->GetCardSkelObj()->playAnimation("smallcard_" + StringConverter::toString(_pCardData->m_idx + 1) + "_offstay");
				m_CommunityCardList[_pCardData->m_idx]->m_pCard->setZOrder(20);
			}
			else
			{
				m_CommunityCardList[_pCardData->m_idx]->m_pCard->GetCardSkelObj()->playAnimation("smallcard_" + StringConverter::toString(_pCardData->m_idx + 1) + "_stay");
				m_CommunityCardList[_pCardData->m_idx]->m_pCard->setZOrder(0);
			}
		}
	}
}

void GameRoomInfo::ActionMoveCommunityCard(int _idx, CCPoint _moveto)
{
	if (LayerManager::getSingletonPtr()->hasLayer("Background"))
	{
		Panel* _prepanel = dynamic_cast<Panel*>(LayerManager::getSingletonPtr()->getLayer("Background"));
		CCPoint _pos = _prepanel->getImage("dmy_dealer")->getPosition();
		m_CommunityCardList[_idx]->m_pCard->setPosition(_pos);
	}
	m_CommunityCardList[_idx]->m_pCard->runAction(CCMoveTo::create(0.2f, _moveto));

	if (m_isBigCommunityCard == true)
	{
		m_CommunityCardList[_idx]->m_pCard->GetCardSkelObj()->playAnimation("smallcard_" + StringConverter::toString(_idx + 1) + "_offstay");
		m_CommunityCardList[_idx]->m_pCard->setZOrder(20);
	}
	else
	{
		m_CommunityCardList[_idx]->m_pCard->GetCardSkelObj()->playAnimation("smallcard_" + StringConverter::toString(_idx + 1) + "_stay");
		m_CommunityCardList[_idx]->m_pCard->setZOrder(0);
	}
	
	
	m_CommunityCardList[_idx]->m_pCard->GetCardSkelObj()->setScale(0.3f);
	m_CommunityCardList[_idx]->m_pCard->GetCardSkelObj()->runAction(CCSequence::create(
		CCScaleTo::create(0.2f, 1.1f),
		CCScaleTo::create(0.1f, 1.f),
		NULL));

	//m_CommunityCardList[_idx]->m_pCard->GetCardSkelObj()->setRotation(180);
	//m_CommunityCardList[_idx]->m_pCard->GetCardSkelObj()->runAction(CCRotateTo::create(0.2f, 0));

}

void GameRoomInfo::ResetCommunityCard()
{
	CardData* _data;
	while (!m_CommunityCardList.empty())
	{
		_data = m_CommunityCardList[0];
		//_data->m_pCard->CardClear();
		m_CommunityCardList.erase(m_CommunityCardList.begin());
		NX_SAFE_DELETE(_data);
	}
	m_CommunityCardList.clear();

	NotiFocusPanel* pPanel = nullptr;
	if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HOLDEM) {
		if (NotiDataManager::getSingleton().getHoldemNoti() == NotiData_eNotiType_HoldemComunityCard) {
			//창이 없으면 뿌려주고 visible 이면 끈다		
			if (LayerManager::getSingleton().hasLayerType<NotiFocusPanel>()) {
				pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
			}
			else {
				PanelHelper::pushNotiFocusPanel(NotiData_eNotiType_HoldemComunityCard);
			}
			pPanel = dynamic_cast<NotiFocusPanel*>(LayerManager::getSingleton().getLayerType<NotiFocusPanel>());
		}
	}

	if (pPanel)
		pPanel->setVisible(false);

}

void GameRoomInfo::SetMyHoldemJokbo(HighJokboKind _kind)
{

}

void GameRoomInfo::Action_EnterRoomCharacter(int _po)
{
	RoomUserData* _userInfo = GetUserDataPtr(_po);
	CCPoint _moveTo = _userInfo->m_pMyCharater->getPosition();
	CCPoint _StartMovoPoint = _moveTo;

	int _userIdx = _userInfo->m_pCardManager->m_UserIdx;
	switch (_userIdx)
	{
	case 0:
		//My
		_StartMovoPoint = CCPoint(_moveTo.x, _moveTo.y - 50);
		break;
	case 1:
	case 2:
		//Left
		_StartMovoPoint = CCPoint(_moveTo.x - 50, _moveTo.y);
		break;
	case 3:
	case 4:
		//Right
		_StartMovoPoint = CCPoint(_moveTo.x + 50, _moveTo.y);
		break;
	default:
		break;
	}

	_userInfo->SetCharacterPosition(_StartMovoPoint);
	_userInfo->MoveCharacterPosition(_moveTo, 1.f);
}

void GameRoomInfo::SetCommunityCardProcessTime(float _time)
{
	m_fProcessTime = _time;
	m_bCommunityCardProcessing = true;
}

void GameRoomInfo::UpdateComminityProcess(float _dt)
{
	if (m_bCommunityCardProcessing == false)
		return;

	m_fProcessTime -= _dt;
	if (m_fProcessTime <= 0.f)
	{
		m_bCommunityCardProcessing = false;
		m_fProcessTime = 0.f;
	}
}

void GameRoomInfo::SetRoomRearrange()
{
	SetStatus(ROOM_REARRANGE);
	//InitGame();
	
	//PokerPlayerInfoPanel* _pInfoPanel = GetPlayerInfoPanel();
	//if (_pInfoPanel)
	//{
	//	for (int _i = 0; _i < 5; _i++)
	//	{
	//		PokerPlayerInfoCommonPanel* _pPlayerPanel = _pInfoPanel->GetPlayerCommonPanelWithIndex(_i);
	//		if (_pPlayerPanel == nullptr)
	//			continue;
	//		_pPlayerPanel->TurnOffPlayerRank();
	//	}
	//}

	if (m_pStayPopup)
	{
		m_pStayPopup->closePanel();
	}
	m_pStayPopup = nullptr;
	
	m_pStayPopup = new TournamentWaitingPanel();
	LayerManager::getSingleton().pushDynamicLayer(m_pStayPopup, DYNAMIC_PUSH_LAYER);
	m_pStayPopup->setDesc(GameStringDepot::getSingleton().getString("TXT_ROOM_REARRANGE"));
}

void GameRoomInfo::RearrangeComplete(char * data, int size)
{
	CommonError res;
	res.ParseFromArray(data, size);

	if (m_pStayPopup)
	{
		m_pStayPopup->closePanel();
		m_pStayPopup = nullptr;
	}

	if (res.has_result())
	{
		if (res.result() == ResultCode::RESULT_FALSE)
			return;
	}
	PanelHelper::pushRearrangePanel();
}

void GameRoomInfo::ShowLastTableEffect()
{
	if (SceneUtil::getCurrentSceneId() != SceneUtil::SceneFight)
		return;

	PokerTopPanel* _pTopPanel = GetTopPanel();
	if (_pTopPanel)
	{
		_pTopPanel->runAction(CCSequence::create(
			CCCallFunc::create(_pTopPanel, callfunc_selector(PokerTopPanel::ShowCurtainClose)),
			CCDelayTime::create(0.5f),
			CCCallFunc::create(_pTopPanel, callfunc_selector(PokerTopPanel::SetCutainClose)),
			CCCallFunc::create(_pTopPanel, callfunc_selector(PokerTopPanel::ShowLastTable)),
			CCDelayTime::create(1.6f),
			CCCallFunc::create(_pTopPanel, callfunc_selector(PokerTopPanel::ShowCurtainOpen)),
			CCDelayTime::create(0.5f),
			CCCallFunc::create(_pTopPanel, callfunc_selector(PokerTopPanel::SetCutainOpen)),
			NULL));
	}
}

void GameRoomInfo::UpdateStayTime(std::string _time)
{
	if (m_pStayPopup)
	{
		m_pStayPopup->setDesc(_time);
	}
}

void GameRoomInfo::playJackpotBonusPanel()
{
	PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
	if (backGroundPanel)
		backGroundPanel->setJackPotRewardPanel(PokerResourceHelper::getImgFontForGameMoney(mJackPotRewardGameMoney, false));
}

void GameRoomInfo::refreshRoomNo()
{
	PokerBackgroundPanel* backGroundPanel = GetBackgroundPanel();
	if (backGroundPanel)
		backGroundPanel->refreshRoomNo();
}

bool GameRoomInfo::isBigAnimation()
{
	return IsBigGame() != 0;
}

int GameRoomInfo::getHiddenCardState()
{
	//수동이라면
	if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_hiddenCard) {
		if (m_bigGameMoney2 < m_PotMoney)
		{
			return 2;
		}
		else {
			return 1;
		}
	}
	else {
		return 0;
	}
}
