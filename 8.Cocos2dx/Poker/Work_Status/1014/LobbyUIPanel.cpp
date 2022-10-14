#include "pch.h"
#include "LobbyUIPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "SimplePopupPanel.h"
#include "LobbyFriendPanel.h"
#include "CustomPopupPanel.h"
#include "LobbyScene.h"
#include "PokerPlayerInfoPanel.h"
#include "BankPopupPanel.h"
#include "GameStringDepot.h"
#include "AttendPopupPanel.h"
#include "LimitedGoodPanel.h"
#include "RefillMoviePanel.h"
#include "BigBonusPanel.h"
#include "LobbyOptionPanel.h"
#include "LobbyMissionPanel.h"
#include "LobbyRecordPanel.h"
#include "PanelHelper.h"
#include <ctime>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#include "android/IGAWorksManager.h"
	#include "android/AdmobManager.h"
#endif
#include "PokerRankHelper.h"
#include "PokerResourceHelper.h"
#include "NotiDataManager.h"

#define FONT_SIZE 4


LobbyUIPanel::LobbyUIPanel()
{
	//setKeypadEnabled(true);
	m_bOtherUi = false;
	m_UiState = LOBBY_UI_NO;
	mUiProcess = false;
	m_bShowExitPanel = false;
	m_ExitPanel = nullptr;
	m_pUserCharacter = nullptr;
	m_pUserCharaUnder = nullptr;
	m_pCharaShadow = nullptr;
	m_fMyCharacterTime = 0.f;
	m_fButtonLightTime = 0.f;
	mCommercialType = SHOP_COMMERCIAL_TYPE_NO;

	InitPanel();
	InitImage();
	InitButton();
	
	setButtonListener(this);

}

LobbyUIPanel::~LobbyUIPanel()
{
	//destruct();
}

void LobbyUIPanel::InitPanel()
{
	construct(getMxmlPath() + "lobby_ui.mxml");	
	setButtonListener(this);
	//m_ChannelPanel = new LobbyChannelPanel();
	//addChild(m_ChannelPanel);
	//m_ChannelPanel->InitPanel();
	//m_ChannelPanel->release();
	
	//InitBankStatePopup();


	getLabel("txt_sevenpoker")->setString(GameStringDepot::getSingleton().getString("LOBBYUI_txt_sevenpoker").c_str());
	getLabel("txt_sevenpoker")->setFontSize(14);
	getLabel("txt_highlow")->setString(GameStringDepot::getSingleton().getString("LOBBYUI_txt_highlow").c_str());
	getLabel("txt_texasholdem")->setString(GameStringDepot::getSingleton().getString("LOBBYUI_txt_texasholdem").c_str());
	getLabel("txt_texasholdem")->setFontSize(14);
	getLabel("txt_badugi")->setString(GameStringDepot::getSingleton().getString("LOBBYUI_txt_badugi").c_str());


	mFirsBuyBtn = getButton("sbtn_first_payment");
	mRefillBtn = getButton("sbtn_refill_icon");
	mCouponBtn = getButton("sbtn_coupon_icon");
	mGoShopEventBtn = getButton("sbtn_panel_shop_gold1");
	mGoShopEventBtn->setZOrder(2);
	mGoMissionEventBtn = getButton("sbtn_panel_mission_event");
	mGoMissionEventBtn->setZOrder(2);
	W_UserInfo* userInfo = GameDataManager::getSingleton().getUserInfo();
	mGoMissionEventBtn->setSkelAnimation(userInfo->eventcode());	
	mGoMissionEventBtn->setEnable(false);	

	mSeasonLockIcon = getImage("skel_lock_menu1");
	mServivalLockIcon = getImage("skel_lock_menu2");

	initNotiWidget();
}

void LobbyUIPanel::applyData()
{
	CCLOG("DRAW CHARACTER TRACKING: In apply Data");
	makeUserCharacter();
	applyUserData();
	ReadyAppear();
	AppearUi();
}

void LobbyUIPanel::InitTopUiPanel()
{
	m_pTopPanel = new LobbyTopUiPanel();
	CCPoint _TopUiPos = getDummy("dmy_top_panel").origin;
	_TopUiPos.y = -_TopUiPos.y;
	m_pTopPanel->setPosition(_TopUiPos);

	LayerManager::getSingleton().addLayer("LobbyTopUI", m_pTopPanel);
	LayerManager::getSingleton().pushLayer("LobbyTopUI", ZODER_LOBBY_TOPUI);

	m_pOptionBackButtion = m_pTopPanel->getButton("sbtn_option_button");	


	refreshNotiEffect(NotiData_eNotiType_NoType);
}

void LobbyUIPanel::InitButton()
{
	mSlotMachineBtn = getButton("sbtn_button_slot");
	getButton("sbtn_button_shop")->getButtonSkelObject()->setSkin("shop");
	getButton("sbtn_button_friend")->getButtonSkelObject()->setSkin("friend");
	getButton("sbtn_button_mission")->getButtonSkelObject()->setSkin("mission");
	getButton("sbtn_button_replay")->getButtonSkelObject()->setSkin("record");
	getButton("sbtn_button_inventory")->getButtonSkelObject()->setSkin("inventory");
	getButton("sbtn_button_slot")->getButtonSkelObject()->setSkin("inventory");
	getButton("sbtn_button_shop")->setType(Button::NoPressImg);
	getButton("sbtn_button_friend")->setType(Button::NoPressImg);
	getButton("sbtn_button_mission")->setType(Button::NoPressImg);
	getButton("sbtn_button_replay")->setType(Button::NoPressImg);
	mSlotMachineBtn->setType(Button::NoPressImg);
	getButton("sbtn_button_survival")->setType(Button::NoPressImg);
	getButton("sbtn_button_tournament")->setType(Button::NoPressImg);
	getButton("sbtn_button_casino")->setType(Button::NoPressImg);

	getButton("sbtn_usertouch")->setType(Button::NoPressImg);
	getButton("sbtn_usertouch")->setVisible(false);


	mLimitedIcon_1Btn = getButton("sbtn_limited_icon1");
	mLimitedIcon_2Btn = getButton("sbtn_limited_icon2");
	mBigBonusBtn = getButton("sbtn_time_reward");

	mLimitedIcon_1Btn->setEnable(false);
	mLimitedIcon_2Btn->setEnable(false);
	mLimitedIcon_1Btn->setVisible(false);
	mLimitedIcon_2Btn->setVisible(false);

	//mSlotMachineBtn->setSkelAnimation("button_slot");
	getButton("sbtn_button_survival")->setSkelAnimation("button_survival_off");		
	getButton("sbtn_button_tournament")->setSkelAnimation("button_tournament_off");
	mSeasonLockIcon->setVisible(true);
}

void LobbyUIPanel::InitImage()
{
	mRankIcon = getSkel("skel_rank");
	CCSize originSize = getDummy("skel_rank").size;
	CCSize iconSize = getDummy("dmy_rank_size").size;
	mRankIcon->setScale(getScaleFit(originSize, iconSize));
	PokerRankHelper::setRankIcon(mRankIcon, PokerRankHelper::getRank());
	mTourmentPointLabel = getLabel("txt_tournament_info1"); 
	string pointStr = StringConverter::toString(PokerRankHelper::getNowRepute());
	mTourmentPointLabel->setString(pointStr.c_str());
	int stringSize = pointStr.size();
	int width = FONT_SIZE * (5 - stringSize);
	mTourmentPointLabel->setPositionX(mTourmentPointLabel->getPositionX() + width);
	mRankIcon->setPositionX(mRankIcon->getPositionX() + width);
	m_pBackCover = getSkel("skel_backcolor");
	m_pBackCover->setVisible(false);		

	mSeasonOpenTimeLabel = getLabel("txt_tournament_info2");
	mSeasonLeftLabel = getLabel("txt_tournament_info3");
	mSeasonLeftLabel->setFontSize(14);
	mTournamentLeftLabel = getLabel("txt_survival_info1");
	mTournamentLeftLabel->setString(GameStringDepot::getSingleton().getString("LOBBY_UI_SURVIVAL_NO_OPEN").c_str());
	mTournamentStateLabelUnder = getLabel("txt_survival_info_under");
	mTournamentStateLabelUnder->setColor(ccc3(0, 40, 0));
	mTournamentStateLabelUnder->setString(GameStringDepot::getSingleton().getString("LOBBY_UI_SURVIVAL_NO_OPEN").c_str());
	mTournamentStateLabelUnder->setHorizontalAlignment(cocos2d::CCTextAlignment::CENTER);
	mTournamentStateLabelOver = getLabel("txt_survival_info_over");
	mTournamentStateLabelOver->setString(GameStringDepot::getSingleton().getString("LOBBY_UI_SURVIVAL_NO_OPEN").c_str());
	mTournamentStateLabelOver->setHorizontalAlignment(CCTextAlignment::CENTER);
	mLimitedcon_1Label = getLabel("txt_limited_time1");
	mLimitedcon_1Label->setVisible(false);
	mLimitedcon_2Label = getLabel("txt_limited_time2");
	mLimitedcon_2Label->setVisible(false);
	mGranChanceTimeLabel = getLabel("txt_limited_time3");
	
	mMenu_1 = getLabel("txt_shop");
	mMenu_2 = getLabel("txt_friend");
	mMenu_3 = getLabel("txt_mission");
	mMenu_4 = getLabel("txt_replay");
	mMenu_5 = getLabel("txt_inventory");
	//mMenu_6 = getLabel("txt_slot");
	mGoMenu_1 = getLabel("txt_casino");
	mGoMenu_2 = getLabel("txt_tournament");
	mGoMenu_3 = getLabel("txt_survival");

	mMenu_1->setString(GameStringDepot::getSingleton().getString("LOBBY_MENU_1").c_str());
	mMenu_2->setString(GameStringDepot::getSingleton().getString("LOBBY_MENU_2").c_str());
	mMenu_3->setString(GameStringDepot::getSingleton().getString("LOBBY_MENU_3").c_str());
	mMenu_4->setString(GameStringDepot::getSingleton().getString("LOBBY_MENU_4").c_str());
	mMenu_5->setString(GameStringDepot::getSingleton().getString("LOBBY_MENU_5").c_str());
	//mMenu_6->setString(GameStringDepot::getSingleton().getString("LOBBY_MENU_6").c_str());

	mGoMenu_1->setString(GameStringDepot::getSingleton().getString("LOBBY_GO_MENU_1").c_str());
	mGoMenu_2->setFontSize(12);
	mGoMenu_2->setString(GameStringDepot::getSingleton().getString("LOBBY_GO_MENU_2").c_str());
	mGoMenu_3->setFontSize(18);	// 서바이벌토너먼트 문자 양이 많아 줄임
	mGoMenu_3->setString(GameStringDepot::getSingleton().getString("LOBBY_GO_MENU_3").c_str());

	GameDataManager::getSingletonPtr()->m_bSurvivalTimeUpdate = true;
}

bool LobbyUIPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return false;
}

void LobbyUIPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void LobbyUIPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}


//void LobbyUIPanel::setPage(int _index)
//{
//	for (int _i = 0; _i < 3; _i++)
//	{
//		if (_i == _index)
//		{
//			m_PageLight[_i]->playAnimation("pagemark_on_stay");
//		}
//		else
//		{
//			m_PageLight[_i]->playAnimation("pagemark_off_stay");
//		}
//	}
//}

//void LobbyUIPanel::VisiblePageLight(bool _show)
//{
//	for (int _i = 0; _i < 3; _i++)
//	{
//		m_PageLight[_i]->setVisible(_show);
//	}
//}


void LobbyUIPanel::resume()
{
}

void LobbyUIPanel::onClicked(const string& name)
{
	srand((unsigned int)time(NULL));
	int random_index = rand() % 2;//NZ창헌
	if (mUiProcess)
		return;

	if (LayerManager::getSingleton().getCurrentLayer()->isDynamic()) {

		if (LayerManager::getSingleton().hasLayerType<SimplePopupPanel>()) {
			SimplePopupPanel* _pPanel = dynamic_cast<SimplePopupPanel*>(LayerManager::getSingletonPtr()->getCurrentLayer());
			if (_pPanel->isGuideType())
				return;
		}
		else {
			return;
		}
	}
	
	if (name == "sbtn_button_shop")
	{
		//상점
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		PanelHelper::pushShopPanel();		
	}
	else if (name == "sbtn_button_friend")
	{
		//친구
		string title = GameStringDepot::getSingletonPtr()->getString("TXT_INFORMATION");
		string detail = GameStringDepot::getSingletonPtr()->getString("UPDATE_DESC");
		PanelHelper::pushSimpleConfirmPopupPanel(detail, title);
	}
	else if (name == "sbtn_button_mission")
	{
		//미션
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//mUiProcess = true;
		WebService::getSingletonPtr()->_sendQuestListUpdateReq();
	}
	else if (name == "sbtn_button_replay")
	{
		//기록
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		PanelHelper::pushRecordPanel();
		
	}
	else if (name == "sbtn_button_inventory") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (LayerManager::getSingleton().hasLayerType<LobbyInventoryPanel>()) {
			Layer* layer = LayerManager::getSingleton().getLayerType<LobbyInventoryPanel>();
			LayerManager::getSingleton().popLayer(layer);
		}
		//보관함
		PanelHelper::pushInventoryPanel();
	}
	else if (name == "sbtn_button_slot")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		SceneUtil::changeScene(SceneUtil::SceneMinigame);
	}
	else if (name == "sbtn_button_survival")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->SurvivalButtonPressed = true;
		WebService::getSingletonPtr()->SurvivalInfoReq();
	}
	else if (name == "sbtn_button_tournament")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingleton().setBeforeRepute(PokerRankHelper::getNowRepute());
		GameDataManager::getSingleton().setBeforeReputeRatio(PokerRankHelper::getRatioRepute());
		
		//WebService::getSingletonPtr()->TournamentInfoReq();
		//nz창헌 - 강제 패널 띄우기
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		_pScene->m_LobbyUIPanel->ShowTournamentUi();



	}
	else if (name == "sbtn_button_casino")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//mUiProcess = true;
		WebService::getSingletonPtr()->SendChannelListReq();
	}
	else if (name == "sbtn_lobbyleft_button1")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		mUiProcess = true;
		ShowMyRoomUi();
	}
	else if (name == "sbtn_usertouch")
	{
		MyCharacterAction();
	}
	else if (name == getButtonName(mGoMissionEventBtn)) {
		PanelHelper::pushEventMissionPanel();
	}
	else if (name == getButtonName(mGoShopEventBtn)) {		
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (mCommercialType == SHOP_COMMERCIAL_TYPE_MEMBERSHIP_MONTHLY_DISCOUNT) {
			PanelHelper::pushMemberShipShopPanel();
		}
		else if (mCommercialType == SHOP_COMMERCIAL_TYPE_MEMBERSHIP) {
			PanelHelper::pushMemberShipShopPanel();
		}
		else if (mCommercialType == SHOP_COMMERCIAL_TYPE_MEMBERSHIP_RUBY_PLUS) {
			PanelHelper::pushRubyShopPanel();
		}		
		else if (mCommercialType == SHOP_COMMERCIAL_TYPE_MEMBERSHIP_ETC) {
			PanelHelper::pushCharacterShopPanel();
		}
	}
	else if (name == "sbtn_lobbybottom_button1")
	{

	}
	else if (name == "sbtn_lobbybottom_button2")
	{
		if (m_UiState == LOBBY_UI_MAIN)
		{
			
		}
	}
	else if (name == "sbtn_option_button")
	{
		if (m_pTopPanel->isCloseBtn()) {
			if (LayerManager::getSingleton().getCurrentLayer()->isDynamic()) {
				LayerManager::getSingleton().popLayer();
				if (!LayerManager::getSingleton().getCurrentLayer()->isDynamic()) {
					if (m_pTopPanel->mCloseBtn->getButtonSkelObject()->getCurrentAnimation() == "cancel_stay") {
						m_pTopPanel->mCloseBtn->getButtonSkelObject()->playAnimation("option_change");
						m_pTopPanel->mCloseBtn->getButtonSkelObject()->appendAnimation("option_stay");
						m_pTopPanel->pushUiPanel(LOBBY_UI_MAIN);						
					}
				}				
				else {
					int uiState = PanelHelper::getUiState();
					m_pTopPanel->pushUiPanel(uiState);

				}
			}
		}
		else {
			LayerManager::getSingleton().pushDynamicLayer(new LobbyOptionPanel());
			m_pTopPanel->pushUiPanel(LOBBY_UI_OPTION);
		}
		return;
		switch (m_UiState)
		{
		case LOBBY_UI_NO:
			break;
		case LOBBY_UI_MAIN:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			mUiProcess = true;
			ShowOptionUi();
			break;
		case LOBBY_UI_MYHOME:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			mUiProcess = true;
			HideMyRoomUi();
			break;
		case LOBBY_UI_LETTER:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			mUiProcess = true;
			HideLetterBoxUi();
			break;
		case LOBBY_UI_FRIEND:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			mUiProcess = true;
			HideFriendUi();
			break;
		case LOBBY_UI_MISSION:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			mUiProcess = true;
			HideMissionUi();
			break;
		case LOBBY_UI_SHOP:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			mUiProcess = true;
			HideShopUi();
			break;
		//case LOBBY_UI_7POKER:
		//case LOBBY_UI_HIGHLOW:
		//case LOBBY_UI_BADUKI:
		//case LOBBY_UI_HOLDEM:
		case LOBBY_UI_CHANNELLIST:
			if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_music == true)
				SoundManager::getSingletonPtr()->playBGM("BGM_Lobby");
			HideChannelUi();
			break;
		case LOBBY_UI_OPTION:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			mUiProcess = true;
			HideOptionUi();
			break;
		case LOBBY_UI_TOURNAMENT:
			HideTournamentUi();
			break;
		case LOBBY_UI_TOURNAMENT_SELECT:
			//기덕수정
			GameDataManager::getSingletonPtr()->PopUiState();
			LayerManager::getSingletonPtr()->popLayer("TournamentSelect");			
			break;
		case LOBBY_UI_SURVIVAL:
			HideSurvivalUi();
			break;
		case LOBBY_UI_SURVIVAL_SELECT:
			//GameDataManager::getSingletonPtr()->PopUiState();
			//LayerManager::getSingletonPtr()->popLayer("SurvivalSelect");
			break;
		case LOBBY_UI_RANKER_GAME_POPUP:
			break;
		case LOBBY_UI_RANKING:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			mUiProcess = true;
			HideRanking();
			break;
		case  LOBBY_UI_REPLAY:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			mUiProcess = true;
			HideReplayUi();
			break;
// 		case LOBBY_UI_CHARACTER_SHOP:
// 			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
// 			HideCharacterShop();
// 			break;
		case LOBBY_UI_CHARACTER_INFO:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			HideCharacterInfo();
			break;
		case LOBBY_UI_INVEN:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			HideInventoryUi();			
			break;
		case LOBBY_UI_RECORD:
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			HideRecordUi();
		}

	}
	else if (name == "sbtn_rubby_button")
	{
		if (m_UiState == LOBBY_UI_SURVIVAL_SELECT)
			return;

		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);

		//현재창이 샵창이라면 바꾸고 아니라면 push 한다.
		LobbyShopPanel* lobbyShopPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingleton().getCurrentLayer());
		if (lobbyShopPanel) {
			//바꾸고
			lobbyShopPanel->SetTapIdx(TAB_RUBY);
			lobbyShopPanel->ShowShopPanel();
		}
		else {
			LobbyShopPanel* lobbyShopPanel = new LobbyShopPanel();
			LayerManager::getSingleton().pushDynamicLayer(lobbyShopPanel);
			lobbyShopPanel->SetTapIdx(TAB_RUBY);
			lobbyShopPanel->ShowShopPanel();
			m_pTopPanel->pushUiPanel(LOBBY_UI_RECORD);
		}		
	}	
	else if (name == getButtonName(mRefillBtn)) {
		// 무료 충전소		
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		PanelHelper::pushFreeMoviePanel();
	}
	else if (name == getButtonName(mCouponBtn)) {		
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		PanelHelper::pushCouponPanel();
	}
	else if (name == getButtonName(mLimitedIcon_1Btn)) {		 //NZ창헌
		if (isOpenLimitedJackpot())
			PanelHelper::pushJackpotPanel();
		else if (isOpenLimitedMade())
		{
			if (random_index == 0)
				PanelHelper::pushMadePanel();
			
			else
				PanelHelper::pushMadePanelB();
		}
	}
	else if (name == getButtonName(mLimitedIcon_2Btn)) {		
	if (random_index == 0)
		PanelHelper::pushMadePanel();

	else
		PanelHelper::pushMadePanelB();
	}





	else if (name == getButtonName(mBigBonusBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		const W_PlayerInfo& playerInfo = GameDataManager::getSingleton().getPlayerInfo();
		if (playerInfo.granchancelefttime() == 0.f)
			PanelHelper::pushBigBonusPanel();
		else {
			SimplePopupPanel * _panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice,GameStringDepot::getSingletonPtr()->getString("GranOpenError"));
			LayerManager::getSingleton().pushDynamicLayer(_panel, DYNAMIC_PUSH_LAYER);
		}
	}
	else if (name == getButtonName(mFirsBuyBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		PanelHelper::pushFirstBuyPanel();
	}
}

void LobbyUIPanel::ShowMyRoomUi()
{
	return;
	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		HideLobbyUi();
		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_MYHOME);
		//_scene->m_pMyHomePanel->ShowMyHomePanel();		
	}
}

void LobbyUIPanel::HideMyRoomUi()
{
	return;
	if (m_UiState == LOBBY_UI_MAIN)
		return;

	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		//_scene->m_pMyHomePanel->HideMyHomePanel();
		GameDataManager::getSingletonPtr()->PopUiState();
		m_pOptionBackButtion->setSkelAnimation("option_change", false);
		SetLobbyUi();
	}
}

void LobbyUIPanel::ShowBankPanel()
{
	PlayerData * _playerData = GameDataManager::getSingletonPtr()->GetPlayerDataPtr();
	if (_playerData->m_MonthlyClassID == 0)
	{
		SimplePopupPanel * _panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::MonthlyBuyNotice, GameStringDepot::getSingletonPtr()->getString("TXT_MONTHLY_CLASS_IS_NOT"));
		LayerManager::getSingleton().pushDynamicLayer(_panel, DYNAMIC_PUSH_LAYER);

		_panel->SetOkEventMsg("monthly_buy");
		_panel->setListener(this);
	}
	else
	{
		new BankPopupPanel();
		//m_UiState = LOBBY_UI_BANK;
		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_BANK);
	}
}


void LobbyUIPanel::MyCharacterIdleAction()
{
	if (m_pUserCharacter == NULL)
		return;

	int _kind = rand() % 2;

	string _aniName = "";
	switch (GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_CharacterIdx)
	{
	case SANTIAGO:
	case SANTIAGO2:
		if (_kind == 0)
			_aniName = "gesture_laugh";
		else if (_kind == 1)
			_aniName = "idle1";
		break;
	case CHRISTINA:
	case CHRISTINA2:
		if (_kind == 0)
			_aniName = "idle1";
		else if (_kind == 1)
			_aniName = "idle2";
		break;
	case ALEXANDER:
	case ALEXANDER2:
		if (_kind == 0)
			_aniName = "die_act";
		else if (_kind == 1)
			_aniName = "gesture_good";
		break;
	case BLACKROSE:
	case BLACKROSE2:
		if (_kind == 0)
			_aniName = "die_act";
		else if (_kind == 1)
			_aniName = "gesture_pleasure";
		break;
	case JENIPER:
	case JENIPER2:
		if (_kind == 0)
			_aniName = "die_act";
		else if (_kind == 1)
			_aniName = "idle2";
		break;
	case MARTIN:
	case MARTIN2:
		if (_kind == 0)
			_aniName = "gesture_laugh";
		else if (_kind == 1)
			_aniName = "idle2";
		break;
	default:
		if (_kind == 0)
			_aniName = "gesture_laugh";
		else if (_kind == 1)
			_aniName = "idle1";
		break;
	}

	m_pUserCharacter->playAnimation(_aniName);
	m_pUserCharacter->appendAnimation("idle_stand", true);
	m_pUserCharaUnder->playAnimation(_aniName);
	m_pUserCharaUnder->appendAnimation("idle_stand", true);

	m_fMyCharacterTime = rand() % 5;
}

void LobbyUIPanel::MyCharacterAction()
{
	if (m_pUserCharacter == NULL)
		return;

	if (m_fMyCharacterTime <= 4.f)
		return;

	int _kind = rand() % 4;

	string _aniName = "";

	switch (GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_CharacterIdx)
	{
	case SANTIAGO:
	case SANTIAGO2:
		if (_kind == 0)
			_aniName = "gesture_thanks";
		else if (_kind == 1)
			_aniName = "gesture_sadness";
		else if (_kind == 2)
			_aniName = "gesture_hurry";
		else if (_kind == 3)
			_aniName = "gesture_good";
		break;
	case CHRISTINA:
	case CHRISTINA2:
		if (_kind == 0)
			_aniName = "gesture_good";
		else if (_kind == 1)
			_aniName = "gesture_surprize";
		else if (_kind == 2)
			_aniName = "gesture_hurry";
		else if (_kind == 3)
			_aniName = "gesture_thanks";
		break;
	case ALEXANDER:
	case ALEXANDER2:
		if (_kind == 0)
			_aniName = "idle2";
		else if (_kind == 1)
			_aniName = "gesture_pleasure";
		else if (_kind == 2)
			_aniName = "gesture_hurry";
		else if (_kind == 3)
			_aniName = "gesture_surprize";
		break;
	case BLACKROSE:
	case BLACKROSE2:
		if (_kind == 0)
			_aniName = "gesture_laugh";
		else if (_kind == 1)
			_aniName = "react_made";
		else if (_kind == 2)
			_aniName = "gesture_hurry";
		else if (_kind == 3)
			_aniName = "gesture_thanks";
		break;
	case JENIPER:
	case JENIPER2:
		if (_kind == 0)
			_aniName = "gesture_angry";
		else if (_kind == 1)
			_aniName = "gesture_sadness";
		else if (_kind == 2)
			_aniName = "gesture_hurry";
		else if (_kind == 3)
			_aniName = "gesture_surprize";
		break;
	case MARTIN:
	case MARTIN2:
		if (_kind == 0)
			_aniName = "gesture_pleasure";
		else if (_kind == 1)
			_aniName = "gesture_surprize";
		else if (_kind == 2)
			_aniName = "gesture_hurry";
		else if (_kind == 3)
			_aniName = "gesture_thanks";
		break;
	default:
		if (_kind == 0)
			_aniName = "gesture_thanks";
		else if (_kind == 1)
			_aniName = "gesture_sadness";
		else if (_kind == 2)
			_aniName = "gesture_hurry";
		else if (_kind == 3)
			_aniName = "gesture_good";
		break;
	}

	m_pUserCharacter->playAnimation(_aniName);
	m_pUserCharacter->appendAnimation("idle_stand", true);
	m_pUserCharaUnder->playAnimation(_aniName);
	m_pUserCharaUnder->appendAnimation("idle_stand", true);

	m_fMyCharacterTime = 0;
}

void LobbyUIPanel::update(float dt)
{	
	if (GameDataManager::getSingletonPtr()->m_pChannelListPanel != nullptr)
		return;

	if (m_pUserCharacter != nullptr)
	{
		m_fMyCharacterTime += dt;
		if (m_fMyCharacterTime >= 20.f)
		{
			MyCharacterIdleAction();
		}
	}
	int tmp = GameDataManager::getSingletonPtr()->GetUiState();
	if (m_fButtonLightTime >= 25.f)
	{
		m_fButtonLightTime = rand() % 10;
		//runAction(CCSequence::create(
		//	CCDelayTime::create(0.1f),
		//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayHomeButtonLight)),
		//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayGoldLight)),
		//	CCDelayTime::create(0.1f),
		//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayLetterButtonLight)),
		//	CCDelayTime::create(0.1f),
		//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayFriendButtonLight)),
		//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayChipLight)),
		//	CCDelayTime::create(0.1f),
		//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayMissionButtonLight)),
		//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayRubyLight)),
		//	CCDelayTime::create(0.1f),
		//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayShopButtonLight)),
		//	NULL));
		int _LightBtnVal = rand() % 9;
		switch (_LightBtnVal)
		{
		case 0:
			PlayHomeButtonLight();
			break;
		case 1:
			PlayGoldLight();
			break;
		case 2:
			PlayLetterButtonLight();
			break;
		case 3:
			PlayFriendButtonLight();
			break;
		case 4:
			PlayChipLight();
			break;
		case 5:
			PlayMissionButtonLight();
			break;
		case 6:
			PlayRubyLight();
			break;
		case 7:
			PlayShopButtonLight();
			break;
		case 8:
			break;
		}


		int _AniBtnVal = rand() % 5;
		switch (_AniBtnVal)
		{
		case 0:
			//m_p7PokerButton->getButtonSkelObject()->playAnimation("sevenpoker_stay");
			break;
		case 1:
			//m_pHighLowButton->getButtonSkelObject()->playAnimation("highlow_stay");
			break;
		case 2:
			//m_pBadugiButton->getButtonSkelObject()->playAnimation("badugi_stay");
			break;
		case 3:
			//m_pHoldemButton->getButtonSkelObject()->playAnimation("texasholdem_stay");
			break;
		case 4:
			//m_pMiniGameButton->getButtonSkelObject()->playAnimation("minigame_stay");
			break;
		}
	}
	m_fButtonLightTime += dt;

	const W_PlayerInfo& playerInfo = GameDataManager::getSingleton().getPlayerInfo();
	//대박찬스 시간 뿌린다.
	mGranChanceTimeLabel->setString(nxGetTimeFormatLong(playerInfo.granchancelefttime()).c_str());
	mGranChanceTimeLabel->setVisible(playerInfo.granchancelefttime() != 0.f);

	W_TourOfInfo* tourOfInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	string timeFormatStr = PokerResourceHelper::getPeroidDesc(tourOfInfo->endlefttime());
	string tourTimeStr = NxGetFormatString(GameStringDepot::getSingleton().getString("REMAIN_PERIOD"), timeFormatStr);
	mSeasonLeftLabel->setString(tourTimeStr.c_str());

	if (tourOfInfo->playlefttime() == 0.f) {
		if (mSeasonLockIcon->isVisible()) {
			getButton("sbtn_button_tournament")->setSkelAnimation("button_tournament");
			mSeasonLockIcon->setVisible(false);
		}		
		mSeasonOpenTimeLabel->setString(GameStringDepot::getSingleton().getString("TXT_DURING_LABEL").c_str());
	}
	else {
		if (!mSeasonLockIcon->isVisible()) {
			getButton("sbtn_button_tournament")->setSkelAnimation("button_tournament_off");
			mSeasonLockIcon->setVisible(true);
		}
		std::string openStr = PokerResourceHelper::getPeroidMinDesc(tourOfInfo->playlefttime());
		std::string openTimeStr = NxGetFormatString(GameStringDepot::getSingleton().getString("REMAIN_OPEN_PERIOD"), openStr);
		mSeasonOpenTimeLabel->setString(openTimeStr.c_str());
	}

	time_t timer = time(NULL);
	struct tm* t;
	t = localtime(&timer);
	int updateRate = GameDataManager::getSingletonPtr()->SurvivalUpdateRate;
	//10분마다 서바이벌 동기화 패킷을 보냄

	if (GameDataManager::getSingletonPtr()->canUpdateSurvival()) {
		WebService::getSingletonPtr()->SurvivalInfoReq();
	}

	//const W_DeathMatchInfo tmp = SurvivalInfo->matchinfo(0);

	UpdateSurvivalWidget();
	GameDataManager::getSingletonPtr()->CheckSurvivalPopup();
	GameDataManager::getSingletonPtr()->CheckSurvivalPreAlert();

	
	
	updateLimitedState();

	if (GameDataManager::getSingleton().getTicketStackIndex() != -1) {
		//만약 main이 떳다면
		Layer* curLayer = LayerManager::getSingleton().getCurrentLayer();
		LobbyTournamentMain* pPanel = dynamic_cast<LobbyTournamentMain*>(curLayer);
		if (pPanel) {
			pPanel->moveCellAndSelect(GameDataManager::getSingleton().getTicketStackIndex());			
		}
	}
	//버튼 확인
	if (isActivateShopCommercial()) {
		string btnStr = "";
		if (mCommercialType == SHOP_COMMERCIAL_TYPE_MEMBERSHIP_MONTHLY_DISCOUNT) {
			btnStr = "panel_shop_gold2";
		}
		else if (mCommercialType == SHOP_COMMERCIAL_TYPE_MEMBERSHIP) {
			btnStr = "panel_shop_gold1";
		}
		else if (mCommercialType == SHOP_COMMERCIAL_TYPE_MEMBERSHIP_RUBY_PLUS) {
			btnStr = "panel_shop_ruby";
		}
		else if (mCommercialType == SHOP_COMMERCIAL_TYPE_MEMBERSHIP_ETC) {
			btnStr = "panel_shop_character";
		}

		if (!btnStr.empty() && mGoShopEventBtn->getButtonSkelObject()->getCurrentAnimation() != btnStr) {
			mGoShopEventBtn->setSkelAnimation(btnStr);
		}
		mGoShopEventBtn->setEnable(true);
		mGoShopEventBtn->setVisible(true);		
	}
	else {
		mGoShopEventBtn->setEnable(false);
		mGoShopEventBtn->setVisible(false);
	}

	if (isActivateMissionCommercial()) {		
		mGoMissionEventBtn->setEnable(true);
		mGoMissionEventBtn->setVisible(true);
	}
	else {
		mGoMissionEventBtn->setEnable(false);
		mGoMissionEventBtn->setVisible(false);
	}

	//샀다 안 샀다.
	bool isFirstBuy = GameDataManager::getSingleton().getPlayerInfo().isbuyonetime();
#ifdef NO_USE_CHECK
	isFirstBuy = true;
#endif // NO_USE_CHECK


	mFirsBuyBtn->setEnable(!isFirstBuy);
	mFirsBuyBtn->setVisible(!isFirstBuy);
	updateNotiWidget();
}

bool LobbyUIPanel::handling(STCMD &stCmd)
{
//	if (!mLoginProcess)
//		return false;
//
//	if (auto *pstIt = castCMD<STCMD_ILOVEGAME_LOGINWITHTOKEN_RESULT>(&stCmd))
//	{
//		STCMD_ILOVEGAME_LOGINWITHTOKEN_RESULT res = *pstIt;
//		if (res.success) {
//
//			if (res.isSimple) {
//				string id = *mIdField->getInputText();
//				string pw = *mPassField->getInputText();
//				SocialManager::getSingleton().getInterface()->loginId(id, pw);
//			}
//			else {
//				SocialManager::getSingleton().getInterface()->login();
//			}
//
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
//			if (LayerManager::getSingleton().getCurrentLayer() == this)
//				LayerManager::getSingleton().popLayer();
//#endif
//		}		
//		else {
//			mLoginProcess = false;
//
//			CSJson::Reader reader;
//			CSJson::Value params;
//			reader.parse(res.result, params);
//			string msg = "";
//			string notice = "";
//			if (params.isMember("error"))
//				msg = params["error"].asString();
//			else
//				msg = "LOGINWITHTOKEN Failed.";
//
//			//HeroApp::getSingleton().notiServerErrorMessage(msg, "", notice);
//
//			return true;
//		}
//	}
	return false;
}

void LobbyUIPanel::makeUserCharacter()
{
	CCLOG("DRAW CHARACTER TRACKING: In makeUserCharacter");
	if (m_pCharaShadow == nullptr)
	{
		CCLOG("DRAW CHARACTER TRACKING: In m_pCharaShadow is null");
		m_pCharaShadow = new SkelObject();

		m_pCharaShadow->setSkelAnim("ui/character_shadow_8888.json");
		m_pCharaShadow->setPosition(getImage("dmy_character1")->getPosition());
		m_pCharaShadow->playAnimation("height_32");
		m_pCharaShadow->setScale(1.f);
		this->addChild(m_pCharaShadow, 1);
		m_pCharaShadow->release();
	}
	else
		CCLOG("DRAW CHARACTER TRACKING: In m_pCharaShadow is not null");
	UpdateUserCharacter();
}

void LobbyUIPanel::UpdateUserCharacter()
{
	int _characterID = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_CharacterIdx;
	
	bool isRemake = false;
	if (m_pUserCharacter == nullptr && m_pUserCharaUnder == nullptr) {
		isRemake = true;
	}
	else {
		string nowSpineName = m_pUserCharacter->getModelName();
		string nextSpineName = PokerResourceHelper::getCharacterOverSpineName(_characterID);
		if (nowSpineName != nextSpineName)
			isRemake = true;
	}

	if (isRemake) {
		if (m_pUserCharacter)
		{
			m_pUserCharacter->removeFromParent();
			m_pUserCharacter = nullptr;
		}

		if (m_pUserCharaUnder)
		{
			m_pUserCharaUnder->removeFromParent();
			m_pUserCharaUnder = nullptr;
		}

		int _characterID = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_CharacterIdx;
		m_pUserCharacter = new SkelObject();
		m_pUserCharaUnder = new SkelObject();
		m_pUserCharacter->setSkelAnim(PokerResourceHelper::getCharacterOverSpineName(_characterID));
		m_pUserCharaUnder->setSkelAnim(PokerResourceHelper::getCharacterUnderSpineName(_characterID));
		m_pUserCharacter->playAnimation("idle_stand", true);
		m_pUserCharaUnder->playAnimation("idle_stand", true);
		m_pCharaShadow->addChild(m_pUserCharaUnder);
		m_pUserCharaUnder->release();
		m_pCharaShadow->addChild(m_pUserCharacter);
		m_pUserCharacter->release();
		CCLOG("DRAW CHARACTER TRACKING: In UpdateUserCharacter");
	}	
}

void LobbyUIPanel::applyUserData()
{
	UpdateUserMoney();
	UpdateUserLevel();
	UpdateUserNickName();
	UpdateUserChip();
	UpdateUserCash();
	UpdateUserVip();
	//m_pLeftUiPanel->UpdateNotiData();
	//업데이트 포토
	m_pTopPanel->refreshBank();
	m_pTopPanel->refreshUserPhoto();
}

void LobbyUIPanel::UpdateChannelList()
{
	if (LayerManager::getSingleton().hasLayerType<ChannelMainPannel>()) {
		ChannelMainPannel* pChanelMainPanel = dynamic_cast<ChannelMainPannel*>(LayerManager::getSingleton().getLayerType<ChannelMainPannel>());
		pChanelMainPanel->UpdateGameMode();
	}
}

void LobbyUIPanel::UpdateUserVip()
{
	m_pTopPanel->updateVip();	
}

void LobbyUIPanel::UpdateUserMoney()
{
	m_pTopPanel->UpdatePlayerInfo();
}

void LobbyUIPanel::UpdateUserLevel()
{
	int _level = PokerRankHelper::getLevel();
	string _strLevel = StringConverter::toString(_level);
	m_pTopPanel->getLabel("str_userlevel")->setString(_strLevel.c_str());
	
	int32 _exp = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Exp;
	int32 _accumExp = GameDataManager::getSingletonPtr()->GetGameDataPtr()->leveldata(_level - 1).accumexp();
	int32 _needExp = GameDataManager::getSingletonPtr()->GetGameDataPtr()->leveldata(_level - 1).needexp();

	int32 _leftExp = _accumExp - _exp;
	if (_leftExp < 0)
		_leftExp = 0;
	int _ExpPer = (_needExp - _leftExp) * 100 / _needExp;

	if (_ExpPer >= 100)
		_ExpPer = 100;

	float _width = 142.f;
	float _startPos = m_pTopPanel->m_ExpStartPos.x;
	float _barWidth = m_pTopPanel->getSkel("skel_expbar_center")->getBounding().size.width;
	float _scaleX = _width / _barWidth;

	if (_scaleX > 71.f)
		_scaleX = 71.f;

	m_pTopPanel->getSkel("skel_expbar_center")->setPositionX(_startPos + (_width * ((float)_ExpPer / 200.f)));
	m_pTopPanel->getSkel("skel_expbar_center")->setScaleX(_scaleX * ((float)_ExpPer / 100.f));
}

void LobbyUIPanel::UpdateUserNickName()
{
	string _strName = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_NickName;
	CCLOG("nickname = %s", _strName.c_str());
	m_pTopPanel->getLabel("txt_username")->setString(_strName.c_str());
	m_pTopPanel->getLabel("txt_usernameshadow")->setString(_strName.c_str());	
}

void LobbyUIPanel::UpdateUserChip()
{
	int64 _chip = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
	string _strChip = StringConverter::toString(_chip);

	m_pTopPanel->getLabel("txt_chip")->setString(_strChip.c_str());
	
	if (_chip / 10000000 != 0)
		m_pTopPanel->getLabel("txt_chip")->setFontSize(17.0);
	else
		m_pTopPanel->getLabel("txt_chip")->setFontSize(19.0);
}

void LobbyUIPanel::UpdateUserCash()
{
	int32 _ruby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
	string _strRuby = StringConverter::toString(_ruby);
	m_pTopPanel->getLabel("txt_rubby")->setString(_strRuby.c_str());
}

void LobbyUIPanel::ReadyAppear()
{
	//m_pMyHomeButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button1");
	//m_pLetterButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button2");
	//m_pFriendButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button3");
	//m_pMissionButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4");
	//m_pShopButton = m_pLeftUiPanel->getButton("sbtn_lobbyleft_button5");

	//m_pLeftLabel[0] = m_pLeftUiPanel->getLabel("txt_myroom");
	//m_pLeftLabel[1] = m_pLeftUiPanel->getLabel("txt_letter");
	//m_pLeftLabel[2] = m_pLeftUiPanel->getLabel("txt_friend");
	//m_pLeftLabel[3] = m_pLeftUiPanel->getLabel("txt_mission");
	//m_pLeftLabel[4] = m_pLeftUiPanel->getLabel("txt_shop");
	//m_pLeftLabelBack[0] = m_pLeftUiPanel->getLabel("txt_myroom_back");
	//m_pLeftLabelBack[1] = m_pLeftUiPanel->getLabel("txt_letter_back");
	//m_pLeftLabelBack[2] = m_pLeftUiPanel->getLabel("txt_friend_back");
	//m_pLeftLabelBack[3] = m_pLeftUiPanel->getLabel("txt_mission_back");
	//m_pLeftLabelBack[4] = m_pLeftUiPanel->getLabel("txt_shop_back");

	//for (int _i = 0; _i < 5; _i++)
	//{
	//	m_LeftLabelShowPos[_i] = m_pLeftLabel[_i]->getPosition();
	//	m_LeftLabelHidePos[_i] = m_pLeftLabel[_i]->getPosition() - ccp(300.f, 0.f);
	//	
	//	m_LeftLabelBackShowPos[_i] = m_pLeftLabelBack[_i]->getPosition();
	//	m_LeftLabelBackHidePos[_i] = m_pLeftLabelBack[_i]->getPosition() - ccp(300.f, 0.f);

	//	m_pLeftLabel[_i]->setPosition(m_LeftLabelHidePos[_i]);
	//	m_pLeftLabelBack[_i]->setPosition(m_LeftLabelBackHidePos[_i]);
	//}

	//m_MyHomeposHide = m_pMyHomeButton->getPosition() - ccp(300.f, 0.f);
	//m_MyHomeposSHow = m_pMyHomeButton->getPosition();
	//m_LetterposHide = m_pLetterButton->getPosition() - ccp(300.f, 0.f);
	//m_LetterposSHow = m_pLetterButton->getPosition();
	//m_FriendposHide = m_pFriendButton->getPosition() - ccp(300.f, 0.f);
	//m_FriendposSHow = m_pFriendButton->getPosition();
	//m_MissionposHide = m_pMissionButton->getPosition() - ccp(300.f, 0.f);
	//m_MissionposSHow = m_pMissionButton->getPosition();
	//m_ShopposHide = m_pShopButton->getPosition() - ccp(300.f, 0.f);
	//m_ShopposSHow = m_pShopButton->getPosition();
	//m_pos7PokerHide = m_p7PokerButton->getPosition() + ccp(600.f, 0.f);
	//m_pos7PokerSHow = m_p7PokerButton->getPosition();
	//m_posHighLowHide = m_pHighLowButton->getPosition() + ccp(600.f, 0.f);
	//m_posHighLowShow = m_pHighLowButton->getPosition();
	//m_posBadugiHide = m_pBadugiButton->getPosition() + ccp(600.f, 0.f);
	//m_posBadugiShow = m_pBadugiButton->getPosition();
	//m_posHoldemHide = m_pHoldemButton->getPosition() + ccp(600.f, 0.f);
	//m_posHoldemShow = m_pHoldemButton->getPosition();
	//m_posMiniGameHide = m_pMiniGameButton->getPosition() + ccp(600.f, 0.f);
	//m_posMiniGameShow = m_pMiniGameButton->getPosition();

	//m_posDailyCheckHide = m_pDailyCheckButton->getPosition() - ccp(0.f, 300.f);
	//m_posDailyCheckShow = m_pDailyCheckButton->getPosition();
	//m_posRankingHide = m_pRankingButton->getPosition() - ccp(0.f, 300.f);
	//m_posRankingShow = m_pRankingButton->getPosition();
	//m_posReplayHide = m_pReplayButton->getPosition() - ccp(0.f, 300.f);
	//m_posReplayShow = m_pReplayButton->getPosition();

	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button1")->setPosition(m_MyHomeposHide);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button2")->setPosition(m_LetterposHide);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button3")->setPosition(m_FriendposHide);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4")->setPosition(m_MissionposHide);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button5")->setPosition(m_ShopposHide);
	//m_p7PokerButton->setPosition(m_pos7PokerHide);
	//m_pHighLowButton->setPosition(m_posHighLowHide);
	//m_pBadugiButton->setPosition(m_posBadugiHide);
	//m_pHoldemButton->setPosition(m_posHoldemHide);
	//m_pMiniGameButton->setPosition(m_posMiniGameHide);
	//m_pDailyCheckButton->setPosition(m_posDailyCheckHide);
	//m_pRankingButton->setPosition(m_posRankingHide);
	//m_pReplayButton->setPosition(m_posReplayHide);
}

void LobbyUIPanel::AppearUi()
{
	//for (int _i = 0; _i < 5; _i++)
	//{
	//	m_pLeftLabel[_i]->runAction(CCSequence::create(
	//		CCDelayTime::create(0.6f + (0.1f *(_i))),
	//		CCMoveTo::create(0.4f, m_LeftLabelShowPos[_i]),
	//		NULL));

	//	m_pLeftLabelBack[_i]->runAction(CCSequence::create(
	//		CCDelayTime::create(0.6f + (0.1f *(_i))),
	//		CCMoveTo::create(0.4f, m_LeftLabelBackShowPos[_i]),
	//		NULL));
	//}

	//left
	//CCPoint _lastPos = m_pMyHomeButton->getPosition() + ccp(300, 0);
	//m_pMyHomeButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.6f),
	//	CCMoveTo::create(0.4f, _lastPos),
	//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayHomeButtonLight)),
	//	NULL));
	//
	//_lastPos = m_pLetterButton->getPosition() + ccp(300, 0);
	//m_pLetterButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.7f),
	//	CCMoveTo::create(0.4f, _lastPos),
	//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayLetterButtonLight)),
	//	NULL));

	//_lastPos = m_pFriendButton->getPosition() + ccp(300, 0);
	//m_pFriendButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.8f),
	//	CCMoveTo::create(0.4f, _lastPos),
	//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayFriendButtonLight)),
	//	NULL));

	//_lastPos = m_pMissionButton->getPosition() + ccp(300, 0);
	//m_pMissionButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.9f),
	//	CCMoveTo::create(0.4f, _lastPos),
	//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayMissionButtonLight)),
	//	NULL));

	//_lastPos = m_pShopButton->getPosition() + ccp(300, 0);
	//m_pShopButton->runAction(CCSequence::create(
	//	CCDelayTime::create(1.f),
	//	CCMoveTo::create(0.4f, _lastPos),
	//	CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::PlayShopButtonLight)),
	//	NULL));

	//right
	//m_p7PokerButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.6f),
	//	CCMoveTo::create(0.4f, m_pos7PokerSHow),
	//	NULL));

	//m_pHighLowButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.7f),
	//	CCMoveTo::create(0.4f, m_posHighLowShow),
	//	NULL));

	//m_pBadugiButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.8f),
	//	CCMoveTo::create(0.4f, m_posBadugiShow),
	//	NULL));

	//m_pHoldemButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.9f),
	//	CCMoveTo::create(0.4f, m_posHoldemShow),
	//	NULL));

	//m_pMiniGameButton->runAction(CCSequence::create(
	//	CCDelayTime::create(1.f),
	//	CCMoveTo::create(0.4f, m_posMiniGameShow),
	//	NULL));

	//m_pDailyCheckButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.8f),
	//	CCMoveTo::create(0.4f, m_posDailyCheckShow),
	//	NULL));

	//m_pRankingButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.7f),
	//	CCMoveTo::create(0.4f, m_posRankingShow),
	//	NULL));

	//m_pReplayButton->runAction(CCSequence::create(
	//	CCDelayTime::create(0.6f),
	//	CCMoveTo::create(0.4f, m_posReplayShow),
	//	NULL));
}

void LobbyUIPanel::PlayHomeButtonLight()
{
	//m_pLeftUiPanel->PlayButtonEffect(0);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button1")->setSkelAnimation("lobbyleft_off_shine", false);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button1")->setSkelAppendAnimation("lobbyleft_off_stay", false);
}

void LobbyUIPanel::PlayLetterButtonLight()
{
	//m_pLeftUiPanel->PlayButtonEffect(1);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button2")->setSkelAnimation("lobbyleft_off_shine", false);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button2")->setSkelAppendAnimation("lobbyleft_off_stay", false);
}

void LobbyUIPanel::PlayFriendButtonLight()
{
	//m_pLeftUiPanel->PlayButtonEffect(2);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button3")->setSkelAnimation("lobbyleft_off_shine", false);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button3")->setSkelAppendAnimation("lobbyleft_off_stay", false);
}

void LobbyUIPanel::PlayMissionButtonLight()
{
	//m_pLeftUiPanel->PlayButtonEffect(3);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4")->setSkelAnimation("lobbyleft_off_shine", false);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4")->setSkelAppendAnimation("lobbyleft_off_stay", false);
}

void LobbyUIPanel::PlayShopButtonLight()
{
	//m_pLeftUiPanel->PlayButtonEffect(4);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4")->setSkelAnimation("lobbyleft_off_shine", false);
	//m_pLeftUiPanel->getButton("sbtn_lobbyleft_button4")->setSkelAppendAnimation("lobbyleft_off_stay", false);
}

void LobbyUIPanel::PlayGoldLight()
{
	if (!hasElement("skel_gold_light"))
		return;

	getSkel("skel_gold_light")->playAnimation("gold_light");
}

void LobbyUIPanel::PlayChipLight()
{
	if (!hasElement("skel_chip_light"))
		return;

	getSkel("skel_chip_light")->playAnimation("gold_light");
}

void LobbyUIPanel::PlayRubyLight()
{
	if (!hasElement("skel_rubby_light"))
		return;

	getSkel("skel_rubby_light")->playAnimation("rubby_light");
}

LobbyScene* LobbyUIPanel::GetLobbyScene()
{
	if (SceneManager::getSingletonPtr()->getCurrentSceneID() == SceneUtil::SceneLobby)
	{
		LobbyScene* _scene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		if (_scene)
			return _scene;
	}
	return nullptr;
}

void LobbyUIPanel::SetChannel()
{
	ChannelMainPannel* chanelMainPanel = new ChannelMainPannel();
	LayerManager::getSingleton().pushDynamicLayer(chanelMainPanel);
	chanelMainPanel->UpdateGameMode();
	m_pTopPanel->pushUiPanel(LOBBY_UI_CHANNELLIST);
	return;

	HideLobbyUi();
	if (!LayerManager::getSingleton().hasPushedLayer("LobbyChannel"))
		LayerManager::getSingleton().pushLayer("LobbyChannel", ZODER_LOBBY_CHANNEL);

	//if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_7POKER)
	//{
	//	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_7POKER);
	//}
	//else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HIGH_LOW)
	//{
	//	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_HIGHLOW);
	//}
	//else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_BADUKI)
	//{
	//	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_BADUKI);
	//}
	//else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HOLDEM)
	//{
	//	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_HOLDEM);
	//}

	//set list
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_CHANNELLIST);

	if (LayerManager::getSingleton().hasLayer("LobbyChannel"))
	{
		ChannelMainPannel* _pPanel = dynamic_cast<ChannelMainPannel*>(LayerManager::getSingleton().getLayer("LobbyChannel"));

		_pPanel->UpdateGameMode();
	}

	m_pOptionBackButtion->getButtonSkelObject()->playAnimation("cancel_change");
	m_pOptionBackButtion->getButtonSkelObject()->appendAnimation("cancel_stay");
	
}

void LobbyUIPanel::ReloadFriendUi()
{
	//기덕개발
	if (LayerManager::getSingleton().hasLayerType<LobbyFriendPanel>()){
		LobbyFriendPanel* lobbyFriendPanel = dynamic_cast<LobbyFriendPanel*>(LayerManager::getSingleton().getLayerType<LobbyFriendPanel>());
		if (lobbyFriendPanel) {
			CCLog("ReloadFriendUi = %d", lobbyFriendPanel->m_TapIndex);
			switch (lobbyFriendPanel->m_TapIndex)
			{
			case 2:
				lobbyFriendPanel->refreshFriendPanel();
				break;
			case 1:
				lobbyFriendPanel->refreshRecommendPanel();
				break;
			case 0:
				lobbyFriendPanel->refreshFaceookPanel();
				break;
			default:
				break;
			}
		}
	}	
	else {
		PanelHelper::pushFriendPanel();
	}
}

void LobbyUIPanel::HideFriendUi()
{
	if (m_UiState == LOBBY_UI_MAIN)
		return;

	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		GameDataManager::getSingletonPtr()->PopUiState();
		m_pOptionBackButtion->setSkelAnimation("option_change", false);
		//_scene->m_pLobbyFriendPanel->HideFriendPanel();
		SetLobbyUi();
	}
}

void LobbyUIPanel::ShowFriendLeftBack()
{
	//for (int _i = 0; _i < 4; _i++)
	//{
	//	m_LeftBack[_i]->setVisible(true);
	//}
	//m_UiState = LOBBY_UI_FRIEND;
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_FRIEND);

	getSkel("skel_backcolor")->setVisible(true);
}

//void LobbyUIPanel::HideLeftBack()
//{
//	for (int _i = 0; _i < 5; _i++)
//	{
//		m_LeftBack[_i]->setVisible(false);
//	}
//
//	getSkel("skel_backcolor")->setVisible(false);
//}

void LobbyUIPanel::HideMissionUi()
{
	//기덕개발
	return;
	if (m_UiState == LOBBY_UI_MAIN)
		return;

	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		GameDataManager::getSingletonPtr()->PopUiState();
		m_pOptionBackButtion->setSkelAnimation("option_change", false);
		//_scene->m_pMissionPanel->HideMissionPanel();
		SetLobbyUi();
	}
}

void LobbyUIPanel::ShowMissoionLeftBack()
{
	//for (int _i = 0; _i < 2; _i++)
	//{
	//	m_LeftBack[_i]->setVisible(true);
	//}
	//m_UiState = LOBBY_UI_MISSION;
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_MISSION);

	getSkel("skel_backcolor")->setVisible(true);
}

void LobbyUIPanel::SetShopUi(int tapIdx)
{
	
}

void LobbyUIPanel::FromOtherUiToShop(int _tapIdx)
{
	
}

void LobbyUIPanel::HideChannelUi()
{
	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		GameDataManager::getSingletonPtr()->PopUiState();
		LayerManager::getSingletonPtr()->popLayer("LobbyChannel");

		SetLobbyUi();
		m_pOptionBackButtion->setSkelAnimation("option_change", false);

	}
}


void LobbyUIPanel::HideShopUi()
{
	
}

void LobbyUIPanel::ShowMyHomeLeftback()
{
	//for (int _i = 0; _i < 4; _i++)
	//{
	//	m_LeftBack[_i]->setVisible(true);
	//}
	//m_UiState = LOBBY_UI_MYHOME;
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_MYHOME);

	getSkel("skel_backcolor")->setVisible(true);
}

void LobbyUIPanel::ShowShopLeftback()
{
	//for (int _i = 0; _i < 4; _i++)
	//{
	//	m_LeftBack[_i]->setVisible(true);
	//}
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SHOP);

	getSkel("skel_backcolor")->setVisible(true);
}


void LobbyUIPanel::SetLetterBoxUi()
{
	//inventory 가 push 되어 있고
	if (LayerManager::getSingleton().hasPushedLayer("LobbyInven")) {
		LobbyInventoryPanel* inventoryPanel = dynamic_cast<LobbyInventoryPanel*>(LayerManager::getSingleton().getLayer("LobbyInven"));
		if (inventoryPanel)
			inventoryPanel->UpdateCell();
	}

	return;
	
}

void LobbyUIPanel::HideLetterBoxUi()
{
	if (m_UiState == LOBBY_UI_MAIN)
		return;

	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		//ShowGameButton();
		//ShowMenuButton();
		//HideLeftBack();
		//VisiblePageLight(true);

		//m_UiState = LOBBY_UI_MAIN;
		GameDataManager::getSingletonPtr()->PopUiState();
		//m_UiState = GameDataManager::getSingletonPtr()->GetUiState();
		
		m_pOptionBackButtion->setSkelAnimation("option_change", false);
		//_scene->m_pLetterBoxPanel->HideLetterPanel();
		SetLobbyUi();
	}
}

void LobbyUIPanel::ShowLetterLeftback()
{
	//for (int _i = 0; _i < 2; _i++)
	//{
	//	m_LeftBack[_i]->setVisible(true);
	//}
	//m_UiState = LOBBY_UI_LETTER;
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_LETTER);

	getSkel("skel_backcolor")->setVisible(true);
}

void LobbyUIPanel::SetRanking()
{
	if (m_UiState != LOBBY_UI_RANKING_PROCESS)
		return;

	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		HideLobbyUi();

		m_pOptionBackButtion->setSkelAnimation("cancel_change", false);
		m_UiState = LOBBY_UI_NO;
		runAction(CCSequence::create(
			CCDelayTime::create(0.8f),
			CCCallFunc::create(this, callfunc_selector(LobbyUIPanel::ShowRankingRighttback)),
			NULL));
	}
}

void LobbyUIPanel::HideRanking()
{
	if (m_UiState == LOBBY_UI_MAIN)
		return;

	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		//ShowGameButton();
		//ShowMenuButton();
		//HideLeftBack();
		//setPage(1);
		//m_UiState = LOBBY_UI_NO;
		GameDataManager::getSingletonPtr()->PopUiState();
		m_pOptionBackButtion->setSkelAnimation("option_change", false);
	}
}

void LobbyUIPanel::ShowRankingRighttback()
{
	//for (int _i = 0; _i < 2; _i++)
	//{
	//	m_RightBack[_i]->setVisible(true);
	//}
	//for (int _i = 0; _i < 2; _i++)
	//{
	//	m_LeftBack[_i]->setVisible(true);
	//}
	//m_UiState = LOBBY_UI_RANKING;
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_RANKING);
	getSkel("skel_backcolor")->setVisible(true);

	if (GameDataManager::getSingletonPtr()->m_RakingTutotial == false)
	{
		CustomPopupPanel * panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::RANKING_TUTORIAL_TYPE);
		if (panel)
		{
			LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
		}
	}

}

void LobbyUIPanel::HideRighttback()
{
	for (int _i = 0; _i < 2; _i++)
	{
		m_RightBack[_i]->setVisible(false);
	}
}

void LobbyUIPanel::SetReplayUi()
{
	return;
	if (m_UiState != LOBBY_UI_REPLAY_PROCESS)
		return;

	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		HideLobbyUi();
		LayerManager::getSingleton().pushLayer("LobbyReplay", ZODER_LOBBY_REPLAY);
		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_REPLAY);
		//_scene->m_pReplayPanel->ShowReplayPanel();
		m_pOptionBackButtion->setSkelAnimation("cancel_change", false);		
	}
}

void LobbyUIPanel::ShowReplayLeftBack()
{
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_REPLAY);
	getSkel("skel_backcolor")->setVisible(true);

	if (GameDataManager::getSingletonPtr()->m_ReplayTutotial == false)
	{
		CustomPopupPanel * panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::REPLAY_TUTORIAL_TYPE);
		if (panel)
		{
			LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
		}
	}
}

void LobbyUIPanel::HideReplayUi()
{
	return;
	if (m_UiState != LOBBY_UI_REPLAY)
		return;

	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		GameDataManager::getSingletonPtr()->PopUiState();
		m_pOptionBackButtion->setSkelAnimation("option_change", false);
		//_scene->m_pReplayPanel->HideReplayPanel();
		SetLobbyUi();
	}
}

void LobbyUIPanel::onLayerMessage(const string& msg)
{
	if (msg == "EXIT_GAME")
	{
		CCDirector::sharedDirector()->end();
	}

	if (msg == "PopupCancel")
	{
		m_bShowExitPanel = false;
	}
}

void LobbyUIPanel::ShowOptionUi()
{
	return;
	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		HideLobbyUi();
		LayerManager::getSingleton().pushLayer("LobbyOption", ZODER_LOBBY_OPTION);
		GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_OPTION);
		//_scene->m_pOptionPanel->ShowOptionStart();
		m_pOptionBackButtion->setSkelAnimation("cancel_change", false);		
	}
}

void LobbyUIPanel::HideOptionUi()
{
	return;
	if (m_UiState == LOBBY_UI_MAIN)
		return;

	LobbyScene* _scene = GetLobbyScene();
	if (_scene)
	{
		GameDataManager::getSingletonPtr()->PopUiState();
		m_pOptionBackButtion->setSkelAnimation("option_change", false);
		//_scene->m_pOptionPanel->HideOptionEnd();
		SetLobbyUi();
	}
}


void LobbyUIPanel::ShowOptionLeftback()
{
	//for (int _i = 0; _i < 2; _i++)
	//{
	//	m_LeftBack[_i]->setVisible(true);
	//}
	//m_UiState = LOBBY_UI_OPTION;
	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_OPTION);

	getSkel("skel_backcolor")->setVisible(true);
}

void LobbyUIPanel::ShowTournamentUi()
{
	applyData();
	PanelHelper::pushTournamentPanel();	
}

void LobbyUIPanel::UpdateTournamentUi()
{

	if (LayerManager::getSingleton().hasLayerType<LobbyTournamentMain>()) {
		LobbyTournamentMain* pLobbyTournamentMainPanel = dynamic_cast<LobbyTournamentMain*>(LayerManager::getSingleton().getLayerType<LobbyTournamentMain>());
		pLobbyTournamentMainPanel->m_BottomUi->UpdateChannelCell();
	}

	if (LayerManager::getSingleton().hasLayerType<LobbyTourSelectPanel>()) {
		LobbyTourSelectPanel* pLobbyTourSelectPanel = dynamic_cast<LobbyTourSelectPanel*>(LayerManager::getSingleton().getLayerType<LobbyTourSelectPanel>());
		pLobbyTourSelectPanel->SetRanker();
		pLobbyTourSelectPanel->SetMyRank();
		pLobbyTourSelectPanel->SetMyBonus();
		pLobbyTourSelectPanel->SetRound();
		pLobbyTourSelectPanel->SetTitleName();		
	}	
}

void LobbyUIPanel::HideTournamentUi()
{
	//ShowGameButton();
	//ShowMenuButton();

	m_pOptionBackButtion->getButtonSkelObject()->playAnimation("option_change");
	m_pOptionBackButtion->getButtonSkelObject()->appendAnimation("option_stay");

	GameDataManager::getSingletonPtr()->PopUiState();
	LayerManager::getSingletonPtr()->popLayer("LobbyTournamet");

	SetLobbyUi();
}


void LobbyUIPanel::ShowSurvivalUi()
{
	PanelHelper::pushServivalPanel();
	//m_pTopPanel->pushUiPanel(LOBBY_UI_SURVIVAL);
	return;
	//HideGameButton();
	//HideMenuButton();

	HideLobbyUi();

	m_pOptionBackButtion->getButtonSkelObject()->playAnimation("cancel_change");
	m_pOptionBackButtion->getButtonSkelObject()->appendAnimation("cancel_stay");

	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SURVIVAL);
	LayerManager::getSingletonPtr()->pushLayer("LobbySurvival", ZODER_LOBBY_SURVIVAL);

	LobbySurvivalMain* _pPanel = dynamic_cast<LobbySurvivalMain*>(LayerManager::getSingletonPtr()->getLayer("LobbySurvival"));
	if (_pPanel)
	{
		_pPanel->SelectGameMode((GameKind)GameDataManager::getSingletonPtr()->getGameKind());
		//_pPanel->CreateCell();
	}
}

void LobbyUIPanel::UpdateSurvivalUi()
{
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

void LobbyUIPanel::UpdateSurvivalWidget()
{
	W_DeathMatchOfInfo* SurvivalInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
	W_DeathMatchInfo::eUserStatus tmp =  GameDataManager::getSingletonPtr()->Survival_UserStatus;
	switch (GameDataManager::getSingletonPtr()->Survival_UserStatus)
	{
		mTournamentStateLabelOver->setPositionX(846);
	case 0://eNot
		mTournamentStateLabelUnder->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_GAMENO").c_str());
		mTournamentStateLabelOver->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_GAMENO").c_str());
		break;
	case 1://eDisplay
		mTournamentStateLabelUnder->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_REGIWAIT").c_str());
		mTournamentStateLabelOver->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_REGIWAIT").c_str());
		break;
	case 2://eRegister
		mTournamentStateLabelUnder->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_REGISTING").c_str());
		mTournamentStateLabelOver->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_REGISTING").c_str());
		mTournamentStateLabelOver->setPositionX(836);
		break;
	case 3://eWait
		mTournamentStateLabelUnder->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_GAMEWAIT").c_str());
		mTournamentStateLabelOver->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_GAMEWAIT").c_str());
		break;
	case 4://eGame
		mTournamentStateLabelUnder->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_GAMING").c_str());
		mTournamentStateLabelOver->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_GAMING").c_str());
		break;
	case 5://eEnd
		mTournamentStateLabelUnder->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_REGIWAIT").c_str());
		mTournamentStateLabelOver->setString(GameStringDepot::getSingleton().getString("TXT_TOUT_STAT_REGIWAIT").c_str());
		break;
	}

	if (SurvivalInfo->matchinfo().size() != 0)
	{
		auto UserStatus = GameDataManager::getSingletonPtr()->Survival_UserStatus;
		string DisplayStr;
		if (UserStatus == 2 || UserStatus == 3 || UserStatus == 4) //등록가능 상태냐
		{
			if (mServivalLockIcon->isVisible()) {//이 if문 없이 그냥 돌리면 프레임 드랍현상 발생
				mServivalLockIcon->setVisible(false);//생각보다 리소스를 많이 먹는 작업
				getButton("sbtn_button_survival")->setSkelAnimation("button_survival");
			}

			switch (UserStatus) {
			case 2:
				DisplayStr = "TXT_TOUT_STAT_REGISTING_NOBLANK";
				break;
			case 3:
				DisplayStr = "TXT_TOUT_STAT_GAMEWAIT";
				break;
			case 4:
				DisplayStr = "LOBBY_UI_SURVIVAL_OPEN";
				break;
			}

			if (mTournamentLeftLabel->getString() != GameStringDepot::getSingleton().getString(DisplayStr).c_str())
				mTournamentLeftLabel->setString(GameStringDepot::getSingleton().getString(DisplayStr).c_str());
			GameDataManager::getSingletonPtr()->m_bSurvivalTimeUpdate = true;
		}
		else {
			if (!mServivalLockIcon->isVisible()) { //이 if문 없이 그냥 돌리면 프레임 드랍현상 발생
				mServivalLockIcon->setVisible(true); //생각보다 리소스를 많이 먹는 작업
				getButton("sbtn_button_survival")->setSkelAnimation("button_survival_off");
				GameDataManager::getSingletonPtr()->m_bSurvivalTimeUpdate = true;
			}

		}

		std::string openStr = "";
		std::string openTimeStr = "";
		if (!mTournamentLeftLabel->isVisible() && UserStatus == 1, 2, 3, 5)
			mTournamentLeftLabel->setVisible(true);
		switch (UserStatus) {
		case 1:
			openStr = PokerResourceHelper::getPeroidMinDesc(GameDataManager::getSingletonPtr()->Survival_RegisterableTime);
			openTimeStr = NxGetFormatString(GameStringDepot::getSingleton().getString("REMAIN_OPEN_PERIOD"), openStr);
			break;
		case 2:
			openStr = PokerResourceHelper::getPeroidMinDesc(GameDataManager::getSingletonPtr()->Survival_RegisterExpireTime);
			openTimeStr = NxGetFormatString(GameStringDepot::getSingleton().getString("REMAIN_CLOSE_PERIOD"), openStr);
			break;
		case 3:
			openStr = PokerResourceHelper::getPeroidMinDesc(GameDataManager::getSingletonPtr()->Survival_WaitExpireTime);
			openTimeStr = NxGetFormatString(GameStringDepot::getSingleton().getString("REMAIN_OPEN_PERIOD"), openStr);
			break;
		case 5:
			openStr = PokerResourceHelper::getPeroidMinDesc(GameDataManager::getSingletonPtr()->Survival_RegisterableTime);
			openTimeStr = NxGetFormatString(GameStringDepot::getSingleton().getString("REMAIN_OPEN_PERIOD"), openStr);
			break;
		default:
			mTournamentLeftLabel->setVisible(false);
		}
		mTournamentLeftLabel->setString(openTimeStr.c_str());
	}
}

void LobbyUIPanel::HideSurvivalUi()
{
	//ShowGameButton();
	//ShowMenuButton();

	m_pOptionBackButtion->getButtonSkelObject()->playAnimation("option_change");
	m_pOptionBackButtion->getButtonSkelObject()->appendAnimation("option_stay");

	GameDataManager::getSingletonPtr()->PopUiState();
	LayerManager::getSingletonPtr()->popLayer("LobbySurvival");

	SetLobbyUi();
}

void LobbyUIPanel::SetRankingTimeLimitUpdate(string _time)
{
	if (m_UiState != LOBBY_UI_RANKING)
		return;

	if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
// 		if (_pScene->m_pRankingPanel == nullptr)
// 			return;

		//_pScene->m_pRankingPanel->UpdateTimeString(_time);
	}
}

void LobbyUIPanel::HideLobbyMenu()
{
	LobbyScene* _scene = GetLobbyScene();
	if (!_scene)
		return;

	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
	switch (m_UiState)
	{
	case LOBBY_UI_NO:
		break;
	case LOBBY_UI_MAIN:
		LayerManager::getSingleton().popLayer("LobbyUI");
		//LayerManager::getSingleton().popLayer("LobbyTopUI");
		break;
	case LOBBY_UI_MYHOME:
		//_scene->m_pMyHomePanel->HideMyHomePanel();
		break;
	case LOBBY_UI_LETTER:
		//_scene->m_pLetterBoxPanel->HideLetterPanel();
		break;
	case LOBBY_UI_FRIEND:
		//_scene->m_pLobbyFriendPanel->HideFriendPanel();
		break;
	case LOBBY_UI_MISSION:
		//_scene->m_pMissionPanel->HideMissionPanel();
		break;
	case LOBBY_UI_SHOP:
		//_scene->m_pShopPanel->HideShopPanel();
		break;
	case LOBBY_UI_RANKING:
		//_scene->m_pRankingPanel->HideRankingPanel();
		break;
	case LOBBY_UI_RANKING_PROCESS:
		break;
	case LOBBY_UI_REPLAY:
		//_scene->m_pReplayPanel->HideReplayPanel();
		break;
	case LOBBY_UI_REPLAY_PROCESS:
		
		break;
	//case LOBBY_UI_7POKER:
	//case LOBBY_UI_HIGHLOW:
	//case LOBBY_UI_BADUKI:
	//case LOBBY_UI_HOLDEM:
	case LOBBY_UI_CHANNELLIST:
		LayerManager::getSingletonPtr()->popLayer("LobbyChannel");
		break;
	case LOBBY_UI_TOURNAMENT:
		//LayerManager::getSingletonPtr()->popLayer("LobbyTournamet");
		break;
	case LOBBY_UI_SURVIVAL:
		//LayerManager::getSingleton().popLayer("LobbySurvival");
		//LayerManager::getSingleton().popLayer("LobbyTopUI");
		break;
	case LOBBY_UI_TOURNAMENT_SELECT:
		//기덕수정
		//LayerManager::getSingletonPtr()->popLayer("TournamentSelect");
		//LayerManager::getSingletonPtr()->popLayer("LobbyTournamet");
		break;
	case LOBBY_UI_SURVIVAL_SELECT:
		LayerManager::getSingletonPtr()->popLayer("SurvivalSelect");
		LayerManager::getSingleton().popLayer("LobbySurvival");
		break;
	case LOBBY_UI_BANK:
	case LOBBY_UI_RANKER_GAME_POPUP:
		break;
	case LOBBY_UI_OPTION:
		//_scene->m_pOptionPanel->HideOptionStart();
		break;
	
	case LOBBY_UI_INVEN:
		LayerManager::getSingleton().popLayer("LobbyInven");
		break;

	default:
		break;
	}
}

void LobbyUIPanel::HideLobbyUi()
{
	if (m_bOtherUi == false)
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
		//HideGameButton();
		//HideMenuButton();
		LayerManager::getSingleton().popLayer("LobbyUI");
		//LayerManager::getSingleton().popLayer("LobbyTopUI");
		m_pOptionBackButtion->setSkelAnimation("cancel_change", false);
	}
	m_bOtherUi = false;
}

void LobbyUIPanel::SetLobbyUi()
{
	if (LayerManager::getSingleton().hasPushedLayer("LobbyUI") == false)
		LayerManager::getSingleton().pushLayer("LobbyUI", ZODER_LOBBY_UI);
	//LayerManager::getSingleton().pushLayer("LobbyTopUI", ZODER_LOBBY_TOPUI);
}

void LobbyUIPanel::ShowCharacterShop()
{
	NXASSERT(false, "NO HERE1");
}

void LobbyUIPanel::HideCharacterShop()
{
	m_pOptionBackButtion->getButtonSkelObject()->playAnimation("option_change");
	m_pOptionBackButtion->getButtonSkelObject()->appendAnimation("option_stay");

	GameDataManager::getSingletonPtr()->PopUiState();
	LayerManager::getSingletonPtr()->popLayer("LobbyCharacterShop");

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_MAIN);
		}
	}

	SetLobbyUi();
}

void LobbyUIPanel::ShowCharacterInfo(int _characterId)
{
	m_pOptionBackButtion->getButtonSkelObject()->playAnimation("cancel_stay");

	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_CHARACTER_INFO);
	LayerManager::getSingletonPtr()->pushLayer("LobbyCharacterInfo", ZODER_LOBBY_CHARACTER_INFO);
}

void LobbyUIPanel::HideCharacterInfo()
{
	GameDataManager::getSingletonPtr()->PopUiState();
	LayerManager::getSingletonPtr()->popLayer("LobbyCharacterInfo");
}

void LobbyUIPanel::ShowGoldRefillPopup()
{
	return;
// 	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_GOLD_REFILL_POPUP);
// 	LayerManager::getSingleton().pushLayer("GoldRefillPopup", ZODER_GOLD_REFILL_POPUP);

}

void LobbyUIPanel::HideGoldRefillPopup()
{
	return;
// 	GameDataManager::getSingletonPtr()->PopUiState();
// 	LayerManager::getSingletonPtr()->popLayer("GoldRefillPopup");
}

void LobbyUIPanel::refreshNotiEffect(NotiData_eNotiType type)
{
	getImage("skel_underb1")->setVisible(false);		//상점
	getImage("skel_underb2")->setVisible(false);		//친구
	getImage("skel_underb3")->setVisible(false);		//미션
	getImage("skel_underb4")->setVisible(false);		//기록실
	getImage("skel_underb5")->setVisible(false);		//보관함	
	getImage("skel_beffect3_1")->setVisible(false);		//서바이벌
	getImage("skel_beffect3_2")->setVisible(false);
	getImage("skel_beffect2_1")->setVisible(false);		//토너먼트
	getImage("skel_beffect2_2")->setVisible(false);
	getImage("skel_beffect1_1")->setVisible(false);		//카지노입장
	getImage("skel_beffect1_2")->setVisible(false);
	m_pTopPanel->getImage("skel_beffect1")->setVisible(false);	//마이룸
	//m_pTopPanel->getImage("skel_beffect2")->setVisible(false);	//금고
	m_pTopPanel->getImage("skel_beffect3")->setVisible(false);	//루비이동
	m_pTopPanel->getImage("skel_beffect4")->setVisible(false);	//옵션
	bool isSlotOn = false;
	if (type == NotiData_eNotiType_TutorialEnd) {
		//3. 투토리얼 종료
		getImage("skel_beffect1_1")->setVisible(true);		//카지노입장
		getImage("skel_beffect1_2")->setVisible(true);
	}
	else if (type == NotiData_eNotiType_Gold_100) {	
		//4, 골드n 억 이상 보유 시즌 토너먼트
		getImage("skel_beffect2_1")->setVisible(true);		//토너먼트
		getImage("skel_beffect2_2")->setVisible(true);
	}
	else if (type == NotiData_eNotiType_Chip_50) {	
		//5. 칩50개 이상 보유시
		//슬롯 머신 애만 버튼 라벨을 바꿔준다.
		isSlotOn = true;		
	}
	else if (type == NotiData_eNotiType_DailyNewMission) {
		//6.새로운 미션							//미션 노티
		getImage("skel_underb3")->setVisible(true);		//미션
	}
	else if (type == NotiData_eNotiType_DailyMissionComplete) {
		//7.미션 완료시
		getImage("skel_underb3")->setVisible(true);		//미션
	}
	else if (type == NotiData_eNotiType_NewEvent) {
		//8.새로운 이벤트							//
		getImage("skel_underb3")->setVisible(true);		//미션
	}
	else if (type == NotiData_eNotiType_CharacterExpired) {
		//9.캐릭터 기간 만료
		getImage("skel_underb5")->setVisible(true);		//보관함
	}
	else if (type == NotiData_eNotiType_Friend) {
		//10. 첫 친구 추가
		getImage("skel_underb2")->setVisible(true);		//친구
	}
	else if (type == NotiData_eNotiType_Allin) {
		//11. 첫 올인당함
		//무료 충전소 노티
	}
	else if (type == NotiData_eNotiType_Safe) {
		//12. 금고 사용 가능
		//금고 노티
		m_pTopPanel->getImage("skel_beffect2")->setVisible(true);
	}	

	string curAni = mSlotMachineBtn->getButtonSkelObject()->getCurrentAnimation();
	if (isSlotOn) {
		if (curAni != "button_slot_on")
			mSlotMachineBtn->setSkelAnimation("button_slot_on");
	}
	else {
		if (curAni != "button_slot")
			mSlotMachineBtn->setSkelAnimation("button_slot");
	}
}

void LobbyUIPanel::HideInventoryUi()
{
	
}

void LobbyUIPanel::showRecordUi()
{
	//기덕수정
	return;
// 	HideLobbyUi();
// 	m_pOptionBackButtion->getButtonSkelObject()->playAnimation("cancel_change");
// 	m_pOptionBackButtion->getButtonSkelObject()->appendAnimation("cancel_stay");
// 	GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_RECORD);
// 	LayerManager::getSingletonPtr()->pushLayer("LobbyRecord", ZODER_LOBBY_RECORD);
// 
// 	LobbyRecordPanel* lobbyRecordPanel = dynamic_cast<LobbyRecordPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyRecord"));
// 	lobbyRecordPanel->showPanel();
// 
// 	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
// 	{
// 		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
// 		if (_pTopUiPanel)
// 		{
// 			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_RECORD);
// 		}
// 	}
}

void LobbyUIPanel::HideRecordUi()
{
	//기덕수정
	return;
// 	LobbyScene* _scene = GetLobbyScene();
// 	if (_scene)
// 	{
// 		GameDataManager::getSingletonPtr()->PopUiState();
// 		SetLobbyUi();
// 		m_pOptionBackButtion->setSkelAnimation("option_change", false);		
// 		_scene->mLobbyRecordPanel->HidePanel();
// 	}
}

bool LobbyUIPanel::isOpenLimitedJackpot()
{
	return GameDataManager::getSingleton().isActivateLimitedTime(W_LimitShopData_eLimitType_l_jackpot);
}

bool LobbyUIPanel::isOpenLimitedMade()
{
	return GameDataManager::getSingleton().isActivateLimitedTime(W_LimitShopData_eLimitType_l_made);
}

void LobbyUIPanel::updateLimitedState()
{
	mLimitedIcon_1Btn->setEnable(false);
	mLimitedIcon_1Btn->setVisible(false);
	mLimitedcon_1Label->setVisible(false);
	mLimitedIcon_2Btn->setEnable(false);
	mLimitedIcon_2Btn->setVisible(false);
	mLimitedcon_2Label->setVisible(false);


	if (isOpenLimitedJackpot()) {
		//잭팟... 설정
		//버튼 오픈
		mLimitedIcon_1Btn->setEnable(true);		
		mLimitedIcon_1Btn->setVisible(true);
		mLimitedcon_1Label->setVisible(true);
		string curStr = mLimitedIcon_1Btn->getButtonSkelObject()->getCurrentAnimation();
		if (curStr != "lobby_limited_icon1")
			mLimitedIcon_1Btn->setSkelAnimation("lobby_limited_icon1");

		mLimitedcon_1Label->setString(nxGetTimeFormatLong(GameDataManager::getSingleton().getJackPotLimitedTime()).c_str());
	}

	if (isOpenLimitedMade()) {
		if (isOpenLimitedJackpot()) {
			mLimitedIcon_2Btn->setEnable(true);
			mLimitedIcon_2Btn->setVisible(true);
			string curStr = mLimitedIcon_2Btn->getButtonSkelObject()->getCurrentAnimation();
			if (curStr != "lobby_limited_icon2")
				mLimitedIcon_2Btn->setSkelAnimation("lobby_limited_icon2");
			mLimitedcon_2Label->setVisible(true); 			
			mLimitedcon_2Label->setString(nxGetTimeFormatLong(GameDataManager::getSingleton().getMadeLimitedTime()).c_str());
		}
		else {
			mLimitedIcon_1Btn->setEnable(true);
			mLimitedIcon_1Btn->setVisible(true);
			string curStr = mLimitedIcon_1Btn->getButtonSkelObject()->getCurrentAnimation();
			if (curStr != "lobby_limited_icon2")
				mLimitedIcon_1Btn->setSkelAnimation("lobby_limited_icon2");			
			mLimitedcon_1Label->setVisible(true);
			mLimitedcon_1Label->setString(nxGetTimeFormatLong(GameDataManager::getSingleton().getMadeLimitedTime()).c_str());
		}
	}
	else {
		mLimitedIcon_2Btn->setEnable(false);
		mLimitedIcon_2Btn->setVisible(false);
		mLimitedcon_2Label->setVisible(false);
	}
}

bool LobbyUIPanel::isActivateShopCommercial()
{
	mCommercialType = SHOP_COMMERCIAL_TYPE_MEMBERSHIP_ETC;
	bool isMemberShip = false;
	bool isRubyPlus = false;

	//맴버쉽 관련
	//만약 멤버쉽이 0 이거나 가지고 있더라도 기간이라면 보여준다.
	if (!PokerRankHelper::hasMemberShip())
		isMemberShip = true;
	else {
		//기간이 얼마 안 남았다면
		if (GameDataManager::getSingleton().getPlayerInfo().ismonthlyclassdiscount()) {
			isMemberShip = true;
		}
	}
	//만약 루비 상품이 없다면 보여준다.
	if (!PokerRankHelper::hasRubyPlus())
		isRubyPlus = true;

	if (isMemberShip && isRubyPlus) {
		//둘다
		int randomType = mShowCount % 2;
		if (randomType == 0)
			mCommercialType = SHOP_COMMERCIAL_TYPE_MEMBERSHIP_RUBY_PLUS;
		else {
			setShopCommercial();
		}

	}
	else if (isMemberShip) {
		//member
		setShopCommercial();
	}
	else if (isRubyPlus) {
		//ruby
		mCommercialType = SHOP_COMMERCIAL_TYPE_MEMBERSHIP_RUBY_PLUS;
	}

	return mCommercialType != SHOP_COMMERCIAL_TYPE_NO;
}

bool LobbyUIPanel::isActivateMissionCommercial()
{
	//return NotiDataManager::getSingleton().isActivateLobbyNoti(LOBBY_NOTI_TYPE_EVENT);
 	int size = 0;
 	for (W_EventInfo* _pInfo : GameDataManager::getSingletonPtr()->m_EventList)
 	{
 		if (_pInfo->status() == W_QuestInfo_eQuestStatus_Process)
 		{
 			size++;
 		}
 	}
 
 	return size > 0;
}

void LobbyUIPanel::setShopCommercial()
{
	if (!PokerRankHelper::hasMemberShip())
		mCommercialType = SHOP_COMMERCIAL_TYPE_MEMBERSHIP;
	else {
		//만약 
		if(GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_MonthlyClassID == 2)
			mCommercialType = SHOP_COMMERCIAL_TYPE_MEMBERSHIP_MONTHLY_DISCOUNT;
		else
			mCommercialType = SHOP_COMMERCIAL_TYPE_MEMBERSHIP;
	}
}

void LobbyUIPanel::initNotiWidget()
{
	//1번 상점
	{
		NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_LOBBY_SHOP);
		addChild(notiWidget);
		notiWidget->release();
		notiWidget->setPosition(getImage("dmy_notification_icon1")->getPosition());
		mNotiWidgets.push_back(notiWidget);
	}
	//2번 친구
	{
		NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_LOBBY_FRIEND);
		addChild(notiWidget);
		notiWidget->release();
		notiWidget->setPosition(getImage("dmy_notification_icon2")->getPosition());
		mNotiWidgets.push_back(notiWidget);
	}
	//3번 미션
	{
		NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_LOBBY_MISSION);
		mNotiWidgets.push_back(notiWidget);
		addChild(notiWidget);
		notiWidget->release();
		notiWidget->setPosition(getImage("dmy_notification_icon3")->getPosition());
		mNotiWidgets.push_back(notiWidget);
	}
	//4번 기록실
	{
		NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_LOBBY_RECORD);
		addChild(notiWidget);
		notiWidget->release();
		notiWidget->setPosition(getImage("dmy_notification_icon4")->getPosition());
		mNotiWidgets.push_back(notiWidget);
	}
	//5번 보관함
	{
		NotiWidget* notiWidget = new NotiWidget(NotiWidget::NOTI_LOBBY_INVENTORY);
		addChild(notiWidget);
		notiWidget->release();
		notiWidget->setPosition(getImage("dmy_notification_icon5")->getPosition());
		mNotiWidgets.push_back(notiWidget);
	}

}

void LobbyUIPanel::updateNotiWidget()
{
	for (int i = 0; i < mNotiWidgets.size(); i++)
	{
		mNotiWidgets[i]->refresh();
	}
}

void LobbyUIPanel::setShowCount(int showCount)
{
	mShowCount = showCount;
}

void LobbyUIPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}