#include "pch.h"
#include "PanelHelper.h"
#include "LobbyUIPanel.h"
#include "LobbyMissionPanel.h"
#include "LobbyShopPanel.h"
#include "LobbyReplayPanel.h"
#include "SceneUtil.h"
#include "LobbyOptionPanel.h"
#include "ChannelRoomMainPanel.h"
#include "LobbyTournamentMain.h"
#include "LobbySurvivalMain.h"
#include "LobbyRewardPanel.h"
#include "LobbyTourSelectPanel.h"
#include "LobbySurvivalWindowMain.h"
#include "GoldrefillPanel.h"
#include "LobbyRecordPanel.h"
#include "LobbyFriendPanel.h"
#include "BankPopupPanel.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "GoldRefillPopupPanel.h"
#include "BigBonusPanel.h"
#include "RefillMoviePanel.h"
#include "AttendPopupPanel.h"
#include "LimitedGoodPanel.h"
#include "MoviePopupPanel.h"
#include "VipInfoPanel.h"
#include "SeasonResultPanel.h"
#include "NotiFocusPanel.h"
#include "SeasonRatingPanel.h"
#include "BuySucessPanel.h"
#include "RewardAllPanel.h"
#include "SeasonRankInfoPanel.h"
#include "CouponPopupPanel.h"
#include "AnnouncePanel.h"
#include "LoadingPanel.h"
#include "BuyMemberShipConfirmPanel.h"
#include "BuyCharacterConfirmPanel.h"
#include "ChannelRoomPanel.h"
#include "WeeklyResultPanel.h"
#include "FirstBuyPanel.h"
#include "BuySkinConfirmPanel.h"
#include "BankInOutPanel.h"
#include "BuyMemberNoticePanel.h"
#include "TournamentSeedUpPanel.h"
#include "TournamentResultPanel.h"
#include "ModelPopupShot.h"
#include "ModellsBackPopupPanel.h"

#define DYNAMIC_ZORDER 64

int PanelHelper::getUiState()
{
	Nx::Layer* currentLayer = LayerManager::getSingleton().getCurrentLayer();

	//lobby UI
	{
		//상점창
		LobbyShopPanel* pPanel = dynamic_cast<LobbyShopPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_SHOP;
		}
	}

	{
		//친구창
		LobbyFriendPanel* pPanel = dynamic_cast<LobbyFriendPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_FRIEND;
		}
	}

	{
		//미션창
		LobbyMissionPanel* pPanel = dynamic_cast<LobbyMissionPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_MISSION;
		}
	}

	{
		//기록창
		LobbyRecordPanel* pPanel = dynamic_cast<LobbyRecordPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_RECORD;
		}
	}

	{
		//인벤창
		LobbyInventoryPanel* pPanel = dynamic_cast<LobbyInventoryPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_INVEN;
		}
	}



	//Top UI
	{
		LobbyMyHomeMainPanel* pPanel = dynamic_cast<LobbyMyHomeMainPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_MYHOME;
		}
	}


	{
		//환경설정
		LobbyOptionPanel* pPanel = dynamic_cast<LobbyOptionPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_OPTION;
		}
	}

	// 채널
	{
		ChannelMainPannel* pPanel = dynamic_cast<ChannelMainPannel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_CHANNELLIST;
		}
	}

	{
		//토너먼트
		LobbyTournamentMain* pPanel = dynamic_cast<LobbyTournamentMain*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_TOURNAMENT;
		}
	}

	{
		// 리플레이 , 챔피언스 tv
		LobbyReplayPanel* pPanel = dynamic_cast<LobbyReplayPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_REPLAY;
		}
	}

	{
		// 리플레이 , 챔피언스 tv
		LobbySurvivalMain* pPanel = dynamic_cast<LobbySurvivalMain*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_SURVIVAL;
		}
	}

	return -1;

	{
		LobbySurvivalMain* pPanel = dynamic_cast<LobbySurvivalMain*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_MISSION;
		}
	}

	{
		LobbyRewardPanel* pPanel = dynamic_cast<LobbyRewardPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_MISSION;
		}
	}

	{
		LobbyTourSelectPanel* pPanel = dynamic_cast<LobbyTourSelectPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_MISSION;
		}
	}

	{
		LobbySurvivalWindowMain* pPanel = dynamic_cast<LobbySurvivalWindowMain*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_MISSION;
		}
	}

	{
		LobbyRankerGamePopup* pPanel = dynamic_cast<LobbyRankerGamePopup*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_MISSION;
		}
	}

	{
		ChannelRoomMainPanel* pPanel = dynamic_cast<ChannelRoomMainPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_MISSION;
		}
	}

	{
		LobbyCharacterShopPanel* pPanel = dynamic_cast<LobbyCharacterShopPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_MISSION;
		}
	}

	{
		GoldrefillPanel* pPanel = dynamic_cast<GoldrefillPanel*>(currentLayer);
		if (pPanel) {
			return LOBBY_UI_MISSION;
		}
	}
	return -1;
}

void PanelHelper::setLobbyTopUi()
{
	if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		int uiState = getUiState();
		if (uiState != -1) {
			_pScene->m_LobbyUIPanel->m_pTopPanel->pushUiPanel(uiState);
			GameDataManager::getSingletonPtr()->SetUiState(uiState);
		}
	}
}

void PanelHelper::pushMissionPanel()
{
	if (LayerManager::getSingleton().hasLayerType<LobbyMissionPanel>()) {
		LobbyMissionPanel* lobbyMissionPanel = dynamic_cast<LobbyMissionPanel*>(LayerManager::getSingleton().getLayerType<LobbyMissionPanel>());
		lobbyMissionPanel->SetMissionlList();
	}
	else {
		LobbyMissionPanel* pPanel = new LobbyMissionPanel();
		LayerManager::getSingleton().pushDynamicLayer(pPanel);
		setLobbyTopUi(); 
		pPanel->SetMissionlList();		
	}	
}

void PanelHelper::pushEventMissionPanel()
{
	if (LayerManager::getSingleton().hasLayerType<LobbyMissionPanel>()) {
		LobbyMissionPanel* lobbyMissionPanel = dynamic_cast<LobbyMissionPanel*>(LayerManager::getSingleton().getLayerType<LobbyMissionPanel>());
		lobbyMissionPanel->onClicked("btn_tap2");		
	}
	else {
		LobbyMissionPanel* pPanel = new LobbyMissionPanel();
		LayerManager::getSingleton().pushDynamicLayer(pPanel);
		setLobbyTopUi();
		pPanel->onClicked("btn_tap2");
	}
}

void PanelHelper::pushShopPanel()
{
	LobbyShopPanel* pPanel = new LobbyShopPanel();
	LayerManager::getSingleton().pushDynamicLayer(pPanel);	
	setLobbyTopUi(); 
	pPanel->ShowShopPanel();	
}

void PanelHelper::pushFriendPanel()
{
	if (LayerManager::getSingleton().hasLayerType<LobbyFriendPanel>()) {
		LobbyFriendPanel* lobbyFriendPanel = dynamic_cast<LobbyFriendPanel*>(LayerManager::getSingleton().getLayerType<LobbyFriendPanel>());
		lobbyFriendPanel->ClickTapButton(2);
	}
	else {
		LobbyFriendPanel* pPanel = new LobbyFriendPanel();
		LayerManager::getSingleton().pushDynamicLayer(pPanel);
		setLobbyTopUi();
		pPanel->SetFriendlList();
	}	
}

void PanelHelper::pushRecordPanel()
{
	LobbyRecordPanel* pPanel = new LobbyRecordPanel();
	LayerManager::getSingleton().pushDynamicLayer(pPanel);
	setLobbyTopUi();	
	pPanel->showPanel();	
}

void PanelHelper::pushInventoryPanel()
{
	LayerManager::getSingleton().pushDynamicLayer(new LobbyInventoryPanel());
	setLobbyTopUi();
}

void PanelHelper::pushMyHomePanel()
{
	LobbyMyHomeMainPanel* pPanel = new LobbyMyHomeMainPanel();
	LayerManager::getSingleton().pushDynamicLayer(pPanel);
	setLobbyTopUi(); 
	pPanel->ShowMyHomePanel();	
}

void PanelHelper::pushBankPanel()
{
	LayerManager::getSingleton().pushDynamicLayer(new BankPopupPanel(), DynamicPush_Zorder);
}

void PanelHelper::pushRubyShopPanel()
{
	if (LayerManager::getSingleton().hasLayerType<LobbyShopPanel>()) {
		LobbyShopPanel* pLobbyShoPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingleton().getLayerType<LobbyShopPanel>());
		pLobbyShoPanel->SetTapIdx(TAB_RUBY);
	}
	else {
		LobbyShopPanel* pPanel = new LobbyShopPanel();
		LayerManager::getSingleton().pushDynamicLayer(pPanel);
		setLobbyTopUi(); 		
		pPanel->ShowShopPanel();		
		pPanel->SetTapIdx(TAB_RUBY);
	}
}

void PanelHelper::pushMemberShipShopPanel()
{
	if (LayerManager::getSingleton().hasLayerType<LobbyShopPanel>()) {
		LobbyShopPanel* pLobbyShoPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingleton().getLayerType<LobbyShopPanel>());
		pLobbyShoPanel->SetTapIdx(TAB_MEBERSHIP);
	}
	else {
		LobbyShopPanel* pPanel = new LobbyShopPanel();
		LayerManager::getSingleton().pushDynamicLayer(pPanel);				
		setLobbyTopUi();
		pPanel->ShowShopPanel();
		pPanel->SetTapIdx(TAB_MEBERSHIP);
		
	}
}

void PanelHelper::pushCharacterShopPanel()
{
	if (LayerManager::getSingleton().hasLayerType<LobbyShopPanel>()) {
		LobbyShopPanel* pLobbyShoPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingleton().getLayerType<LobbyShopPanel>());
		pLobbyShoPanel->SetTapIdx(TAB_CHARACTER);
	}
	else {
		LobbyShopPanel* pPanel = new LobbyShopPanel();
		LayerManager::getSingleton().pushDynamicLayer(pPanel);
		setLobbyTopUi();
		pPanel->ShowShopPanel();
		pPanel->SetTapIdx(TAB_CHARACTER);		
	}
}

void PanelHelper::pushChannelListPanel()
{
	ChannelMainPannel* chanelMainPanel = new ChannelMainPannel();
	LayerManager::getSingleton().pushDynamicLayer(chanelMainPanel);
	setLobbyTopUi(); 
	chanelMainPanel->UpdateGameMode();	
	if (GameDataManager::getSingletonPtr()->getPutOut() != PUTOUT_NO)
	{
		switch (GameDataManager::getSingletonPtr()->getPutOut())
		{
		case PUTOUT_LOSS_MONEY_DAY:
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, GameStringDepot::getSingleton().getString("TXT_ERROR_LOSS_MONEY_LIMIT_DAY")), DynamicPush_Zorder);
			break;
		case PUTOUT_PLAY_MIN_MONEY:
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, GameStringDepot::getSingleton().getString("TXT_ERROR_PLAY_MIN_MONEY")), DynamicPush_Zorder);
			break;
		default:
			break;
		}
		GameDataManager::getSingletonPtr()->SetPutOut(PUTOUT_NO);
	}
}

void PanelHelper::pushTournamentPanel()
{
	if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_music == true)
		SoundManager::getSingletonPtr()->playBGM("BGM_CHANNEL");

	LobbyTournamentMain* pLobbyTournamentMainPanel = new LobbyTournamentMain(GameDataManager::getSingleton().getTicketStackIndex());
	LayerManager::getSingleton().pushDynamicLayer(pLobbyTournamentMainPanel);
	setLobbyTopUi();
	pLobbyTournamentMainPanel->SelectGameMode((GameKind)GameDataManager::getSingletonPtr()->getGameKind());
	GameDataManager::getSingleton().setTicketStackIndex(-1);

	if (GameDataManager::getSingleton().getTicketStepIndex() != -1) {
		pLobbyTournamentMainPanel->m_BottomUi->onClicked("sbtn_button_enter");
	}
}

void PanelHelper::pushReplayPanel()
{
	LobbyReplayPanel* pPanel = new LobbyReplayPanel();
	LayerManager::getSingleton().pushDynamicLayer(pPanel);
	setLobbyTopUi();
	pPanel->SetReplayList();	
}

void PanelHelper::pushLetterPanel()
{
	LobbyInventoryPanel* pPanel = new LobbyInventoryPanel();
	LayerManager::getSingleton().pushDynamicLayer(pPanel);	
	setLobbyTopUi();
}

void PanelHelper::pushRankingTutorialPanel()
{
	CustomPopupPanel * panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::RANKING_TUTORIAL_TYPE);
	LayerManager::getSingleton().pushDynamicLayer(panel);	
}

void PanelHelper::pushReplayBoxPanel()
{
	CustomPopupPanel * panel = new CustomPopupPanel(CustomPopupPanel::CustomPopupType::USER_REPLAY_BOX_TYPE);
	if (panel)
	{
		LayerManager::getSingleton().pushDynamicLayer(panel);
	}
}

Panel* PanelHelper::pushGoldRefilPopupPanel()
{
	GoldRefillPopupPanel* pPanel = new GoldRefillPopupPanel();
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DynamicPush_Zorder);
	return pPanel;
}

void PanelHelper::pushBigBonusPanel()
{
	LayerManager::getSingleton().pushDynamicLayer(new BigBonusPanel(), DynamicPush_Zorder);
}

void PanelHelper::pushFreeMoviePanel()
{
	LayerManager::getSingleton().pushDynamicLayer(new RefillMoviePanel(), DynamicPush_Zorder);
}

Panel* PanelHelper::pushAttendPopupPanel()
{
	AttendPopupPanel* pPanel = new AttendPopupPanel();
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DynamicPush_Zorder);
	return pPanel;
}

Panel* PanelHelper::pushJackpotPanel()
{
	LimitedGoodPanel* pPanel = new LimitedGoodPanel(LimitedGoodPanel::LIMITED_JACKPOT);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DynamicPush_Zorder);
	return pPanel;
}

Panel* PanelHelper::pushMadePanel()
{
	LimitedGoodPanel* pPanel = new LimitedGoodPanel(LimitedGoodPanel::LIMITED_MADE);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DynamicPush_Zorder);
	return pPanel;
}

Panel* PanelHelper::pushMadePanelB()
{
	LimitedGoodPanel* pPanel = new LimitedGoodPanel(LimitedGoodPanel::ALLIN);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DynamicPush_Zorder);
	return pPanel;
}

void PanelHelper::pushAllinPopupPanel()
{
	//무료 리필
	LayerManager::getSingleton().pushDynamicLayer(new LimitedGoodPanel(LimitedGoodPanel::ALLIN), DynamicPush_Zorder);	
}

void PanelHelper::pushCommonRewardPanel(string title, string content, W_RewardInfo rewardInfo)
{
	RewardPopupPanel* pPanel = new RewardPopupPanel(RewardPopupPanel::COMMON_REWARD);
	string rewardType = "";
	string descStr = content;
	string amountStr = "";
	if (content.empty()) {
		eResourceType type = rewardInfo.rewardset(0).type();
		switch (type)
		{
		case CASH:
			rewardType = GameStringDepot::getSingleton().getString("TXT_RUBY_UNIT");
			amountStr = StringConverter::toString(rewardInfo.rewardset(0).amount());
			descStr += NxGetFormatString(GameStringDepot::getSingleton().getString("REWARD_POPUP_DESC"), rewardType, amountStr);
			break;
		case GAMEMONEY:
		{
			rewardType = GameStringDepot::getSingleton().getString("TXT_GOLD_UNIT");
			string _gameMoney = StringConverter::toString(rewardInfo.rewardset(0).amount());
			amountStr = GameDataManager::getSingletonPtr()->GetKoreanLiteral(_gameMoney, 3);
			descStr += NxGetFormatString(GameStringDepot::getSingleton().getString("REWARD_POPUP_DESC"), rewardType, amountStr);
		}
			break;
		case CHIP:
			rewardType = GameStringDepot::getSingleton().getString("TXT_CHIP_UNIT");
			amountStr = StringConverter::toString(rewardInfo.rewardset(0).amount());
			descStr += NxGetFormatString(GameStringDepot::getSingleton().getString("REWARD_POPUP_DESC"), rewardType, amountStr);
			break;
		}
		
	}
	pPanel->setDesc(title, descStr);
	pPanel->setRewardInfo(rewardInfo);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushCommonRewardPanel(string title, string content)
{
	RewardPopupPanel* pPanel = new RewardPopupPanel(RewardPopupPanel::COMMON_REWARD);	
	pPanel->setDesc(title, content);	
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

Panel* PanelHelper::pushSeasonResultPanel()
{
	SeasonResultPanel* pPanel = new SeasonResultPanel();
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
	return pPanel;
}

void PanelHelper::pushVipInfoPanel()
{
	LayerManager::getSingleton().pushDynamicLayer(new VipInfoPanel(), DYNAMIC_PUSH_LAYER);
}

Panel* PanelHelper::pushNotiFocusPanel(NotiData_eNotiType type)
{
	NotiFocusPanel* pPanel = new NotiFocusPanel(type);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);

	if (SceneUtil::getCurrentSceneId() == SceneUtil::SceneLobby)
	{
		LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
		if (_pScene)
			_pScene->m_LobbyUIPanel->refreshNotiEffect(type);		
	}
	return pPanel;
}

void PanelHelper::pushNotiChannelListPanel(NotiData_eNotiType type)
{
	LayerManager::getSingleton().pushDynamicLayer(new NotiFocusPanel(type), DYNAMIC_PUSH_LAYER);	
}

Panel* PanelHelper::pushRatingUpPanel()
{
	SeasonRatingPanel* pPanel = new SeasonRatingPanel();
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
	return pPanel;
}

void PanelHelper::pushReceiveAllPanel(W_RewardInfo rewardInfo)
{
	RewardAllPanel* pPanel = new RewardAllPanel();
	pPanel->setRewardInfo(rewardInfo);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushConfirmCharacterPanel(int characterId)
{
	BuyCharacterConfirmPanel* pPanel = new BuyCharacterConfirmPanel();
	pPanel->setCharacterConfirm(characterId);
	LayerManager::getSingleton().pushDynamicLayer(pPanel);
}

void PanelHelper::pushModellsBackPopupPanel(int modelListIdx, MODEL_TYPE modelType, TAB_TYPE tapType)
{
	ModellsBackPopupPanel* _popupPanel = new ModellsBackPopupPanel(modelListIdx,modelType, tapType);
	_popupPanel->setIndex(modelListIdx, tapType);	// 여기서 아이디가 모델리스트의 모델 id이다
	LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushConfirmMemberShipPanel(int membershipId)
{
	BuyMemberShipConfirmPanel* pPanel = new BuyMemberShipConfirmPanel();
	pPanel->setMemberConfirm(membershipId);
	LayerManager::getSingleton().pushDynamicLayer(pPanel);
}


void PanelHelper::pushRubyRewardPanel(int rewardRuby, int rubyId, bool isFirstBuy)
{
	BuySucessPanel* pPanel = new BuySucessPanel(BuySucessPanel::BUY_RUBY);
	pPanel->setRubySucess(rewardRuby, rubyId, isFirstBuy);
	LayerManager::getSingleton().pushDynamicLayer(pPanel);

}

void PanelHelper::pushCharacterBuySucessPanel(int characterInfoId, int useRuby)
{
	BuySucessPanel* pPanel = new BuySucessPanel(BuySucessPanel::BUY_CHARACTER);
	pPanel->setCharacterSucess(characterInfoId, useRuby);
	LayerManager::getSingleton().pushDynamicLayer(pPanel);
}

void PanelHelper::pushMemberShipBuySucessPanel(int membetrShipId, W_RewardInfo rewardInfo)
{
	BuySucessPanel* pPanel = new BuySucessPanel(BuySucessPanel::BUY_MEMBERSHIP);
	pPanel->setMemberShipSucess(membetrShipId, rewardInfo);
	LayerManager::getSingleton().pushDynamicLayer(pPanel);
}

void PanelHelper::pushLetterRewardPanel(W_RewardInfo rewardInfo)
{
	RewardPopupPanel* pPanel = new RewardPopupPanel(RewardPopupPanel::LETTER_REWARD);
	pPanel->setLetterReward(rewardInfo);
	if (rewardInfo.rewardset(0).type() == TOUR_TICKET || rewardInfo.rewardset(0).type() == CHARACTER || rewardInfo.rewardset(0).type() == SKIN)
		pPanel->setDesc(GameStringDepot::getSingleton().getString("LETTER_TITLE"), GameStringDepot::getSingleton().getString("LETTER_INVEN_REWARD_DESC"));
	else
		pPanel->setDesc(GameStringDepot::getSingleton().getString("LETTER_TITLE"), GameStringDepot::getSingleton().getString("REWARD_CONFIRM_TOPUI"));
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushBigPotRewardPanel(string desc , W_RewardInfo rewardInfo)
{
	RewardPopupPanel* pPanel = new RewardPopupPanel(RewardPopupPanel::BIG_POT);
	pPanel->setLetterReward(rewardInfo);
	pPanel->setDesc(GameStringDepot::getSingleton().getString("BIG_POT_TITLE"), desc);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushEventRewardPanel(W_RewardInfo rewardInfo)
{
	RewardPopupPanel* pPanel = new RewardPopupPanel(RewardPopupPanel::EVENT_REWARD);
	pPanel->setLetterReward(rewardInfo);
	if (rewardInfo.rewardset(0).type() == TOUR_TICKET || rewardInfo.rewardset(0).type() == CHARACTER)
		pPanel->setDesc(GameStringDepot::getSingleton().getString("EVENT_TITLE"), GameStringDepot::getSingleton().getString("EVENT_INVEN_REWARD_DESC"));
	else
		pPanel->setDesc(GameStringDepot::getSingleton().getString("EVENT_TITLE"), GameStringDepot::getSingleton().getString("REWARD_CONFIRM_TOPUI"));
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushLimitedAllRewardPanel(W_RewardInfo rewardInfo)
{
	RewardAllPanel* pPanel = new RewardAllPanel();
	pPanel->setRewardInfo(rewardInfo);
	pPanel->setTitle(GameStringDepot::getSingleton().getString("LIMITED_REWARD_ALL_TITLE"));
	pPanel->setDesc(GameStringDepot::getSingleton().getString("LIMITED_REWARD_ALL_DESC"));
	pPanel->setItemDesc(GameStringDepot::getSingleton().getString("LIMITED_REWARD_ALL_ITEM_DESC"));
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushSeasonRankInfoPanel()
{
	LayerManager::getSingleton().pushDynamicLayer(new SeasonRankInfoPanel(), DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushCouponPanel()
{
	LayerManager::getSingleton().pushDynamicLayer(new CouponPopupPanel(), DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushModelShotPanel(int tIdx,int idx)
{
    LayerManager::getSingleton().pushDynamicLayer(new ModelPopupShot(tIdx,idx), DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushGamePlayTimePanel()
{
	AnnouncePanel* pPanel = new AnnouncePanel();
	int playTIme = GameDataManager::getSingleton().getPlayTime();
	pPanel->setDesc(NxGetFormatString(GameStringDepot::getSingleton().getString("GAME_ALARM_DESC"), playTIme));
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushAnnounceNotiPanel(string str)
{
	AnnouncePanel* pPanel = new AnnouncePanel();	
	pPanel->setDesc(str);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

Panel* PanelHelper::pushLoadingPanel(string str)
{
	if (LayerManager::getSingleton().hasLayerType<LoadingPanel>()) {
		LoadingPanel* loadingPanel = dynamic_cast<LoadingPanel*>(LayerManager::getSingleton().getLayerType<LoadingPanel>());
		loadingPanel->setTextStr(str);
		return loadingPanel;
	}
	else {
		LoadingPanel* pPanel = new LoadingPanel();
		pPanel->setTextStr(str);
		LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
		return pPanel;
	}	
	return nullptr;
}

void PanelHelper::popLoadingPanel(float delayTime)
{
	if (LayerManager::getSingleton().hasLayerType<LoadingPanel>()) {
		LoadingPanel* loadingPanel = dynamic_cast<LoadingPanel*>(LayerManager::getSingleton().getLayerType<LoadingPanel>());
		loadingPanel->setDelayClose(delayTime);
	}
}

void PanelHelper::pushSimpleConfirmPopupPanel(string text, string title)
{
	LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, text, title), DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushTourRewardPanel(W_RewardInfo rewardInfo)
{
	RewardPopupPanel* pPanel = new RewardPopupPanel(RewardPopupPanel::LETTER_REWARD);
	pPanel->setLetterReward(rewardInfo);
	pPanel->setDesc(GameStringDepot::getSingleton().getString("TXT_DALIY_BONUS_TITLE"), GameStringDepot::getSingleton().getString("REWARD_CONFIRM_TOPUI"));
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

Panel* PanelHelper::pushRoomListPanel()
{
	ChannelRoomPanel* _panel = new ChannelRoomPanel();
	LayerManager::getSingleton().pushDynamicLayer(_panel);	
	return _panel;
}

Panel* PanelHelper::pushWeeklyResultPanel()
{
	WeeklyResultPanel* pPanel = new WeeklyResultPanel();
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
	return pPanel;
}

void PanelHelper::pushFirstBuyPanel()
{
	LayerManager::getSingleton().pushDynamicLayer(new FirstBuyPanel(), DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushConfirmSkinPanel(int skinId)
{
	BuySkinConfirmPanel* pPanel = new BuySkinConfirmPanel();
	pPanel->setCharacterConfirm(skinId);
	LayerManager::getSingleton().pushDynamicLayer(pPanel);
}

void PanelHelper::pushSkinBuySucessPanel(int characterInfoId, int useRuby)
{
	BuySucessPanel* pPanel = new BuySucessPanel(BuySucessPanel::BUY_CARD);
	pPanel->setSkinSucess(characterInfoId, useRuby);
	LayerManager::getSingleton().pushDynamicLayer(pPanel);
}

void PanelHelper::pushServivalPanel()
{
	if (GameDataManager::getSingletonPtr()->m_pOptionValue->m_music == true)
		SoundManager::getSingletonPtr()->playBGM("BGM_CHANNEL");

	LobbySurvivalMain* pLobbySurvivalMainPanel = new LobbySurvivalMain();
	LayerManager::getSingleton().pushDynamicLayer(pLobbySurvivalMainPanel);
	pLobbySurvivalMainPanel->SelectGameMode((GameKind)GameDataManager::getSingletonPtr()->getGameKind());
	setLobbyTopUi();	
}

void PanelHelper::pushSurvivalWindowMainPanel()
{
	LobbySurvivalWindowMain* _pSelectPanel = new LobbySurvivalWindowMain();
	LayerManager::getSingleton().pushDynamicLayer(_pSelectPanel);
	_pSelectPanel->ApplyData();
}

void PanelHelper::pushFirstBuyRewardPanel(W_RewardInfo rewardInfo)
{
	RewardAllPanel* pPanel = new RewardAllPanel();
	pPanel->setRewardInfo(rewardInfo);
	pPanel->setTitle(GameStringDepot::getSingleton().getString("FIRST_REWARD_ALL_TITLE"));
	pPanel->setDesc(GameStringDepot::getSingleton().getString("FIRST_REWARD_ALL_DESC"));
	pPanel->setItemDesc(GameStringDepot::getSingleton().getString("FIRST_REWARD_ALL_ITEM_DESC"));
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushBankInResultPanel(int64 changeMoney)
{
	string amountStr = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(changeMoney));
	string str = NxGetFormatString(GameStringDepot::getSingleton().getString("TXT_INPUT_BANK_SUCCESS"), amountStr);
	BankInOutPanel* pPanel = new BankInOutPanel(true, str);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushBankOutResultPanel(int64 changeMoney)
{
	string amountStr = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(changeMoney));
	string str = NxGetFormatString(GameStringDepot::getSingleton().getString("TXT_OUTPUT_BANK_SUCCESS"), amountStr);
	BankInOutPanel* pPanel = new BankInOutPanel(false, str);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

Panel*  PanelHelper::pushBuyMemberConfirmPanel(string message)
{
	BuyMemberShipConfirmPanel* pPanel = new BuyMemberShipConfirmPanel(message);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
	return pPanel;
}

void PanelHelper::pushBuyMemberNoticePanel()
{
	BuyMemberNoticePanel* pPanel = new BuyMemberNoticePanel();
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

Panel* PanelHelper::pushNotiPanel(W_NotiData notidata)
{
	string _desc = notidata.desc();
	string _title = notidata.title();
	if (notidata.notitype() == W_NotiData_eNotiType_eBank)
	{
		SimplePopupPanel* _pNotiPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ToaseLobbyNoMoneyNotice, notidata.desc(), _title);
		LayerManager::getSingleton().pushDynamicLayer(_pNotiPopup, DYNAMIC_PUSH_LAYER);
		return _pNotiPopup;
	}
	else if (notidata.notitype() == W_NotiData_eNotiType_eSafeMoney) {
		SimplePopupPanel* _pNotiPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::SAFE_MONEY_TYPE, notidata.desc(), _title);
		LayerManager::getSingleton().pushDynamicLayer(_pNotiPopup, DYNAMIC_PUSH_LAYER);
		return _pNotiPopup;
	}
	else if (notidata.notitype() == W_NotiData_eNotiType_eMaxGold) {
		//max 수치
		SimplePopupPanel* _pNotiPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::MAX_MONEY_TYPE, notidata.desc(), _title);
		LayerManager::getSingleton().pushDynamicLayer(_pNotiPopup, DYNAMIC_PUSH_LAYER);
		return _pNotiPopup;
	}	
	SimplePopupPanel* _pNotiPopup = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, notidata.desc(), _title);
	LayerManager::getSingleton().pushDynamicLayer(_pNotiPopup, DYNAMIC_PUSH_LAYER);
	return _pNotiPopup;	
}

void PanelHelper::pushSeedMoneyUpPanel(int64 seedMoney, bool isMax)
{
	TournamentSeedUpPanel* pPanel = new TournamentSeedUpPanel(seedMoney,isMax);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushRearrangePanel()
{
	string msgText = GameStringDepot::getSingleton().getString("TXT_ROOM_REARRANGE_COMPLETE");
	TournamentSeedUpPanel* pPanel = new TournamentSeedUpPanel("stay" , msgText);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushRearrangeCompletePanel()
{
	string msgText = GameStringDepot::getSingleton().getString("TXT_ROOM_REARRANGE_COMPLETE");
	TournamentSeedUpPanel* pPanel = new TournamentSeedUpPanel("stay", msgText);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::pushTouramentRankPanel(int rank)
{
	TournamentResultPanel* pPanel = new TournamentResultPanel(rank);
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
}

void PanelHelper::setCompactImage(Widget* img, const CCRect& rtSize)
{
    const CCRect& imgSize = img->getTextureRect();
    img->setScaleX(rtSize.size.width / imgSize.size.width);
    img->setScaleY(rtSize.size.height / imgSize.size.height);
}
