#include "pch.h"
#include "LobbyTourSelectPanel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "Web/WebService.h"
#include "GameStringDepot.h"
#include "LobbyUIPanel.h"
#include "PokerRankHelper.h"
#include "FriendHelper.h"
#include "PanelHelper.h"
#include "PokerResourceHelper.h"

LobbyTourSelectPanel::LobbyTourSelectPanel()
{
	m_SelectedIndex = -1;
	//m_SubTopPanel = nullptr;

	InitPanel();
	InitImage();
	InitButton();

	setButtonListener(this);
}

LobbyTourSelectPanel::~LobbyTourSelectPanel()
{
	CCLOG("~LobbyTourSelectPanel");
	Layer* temp = dynamic_cast<LobbyTournamentMain*>(LayerManager::getSingleton().getCurrentLayer());
	if (temp != nullptr) {
		LayerManager::getSingleton().popLayer();
	}
}

void LobbyTourSelectPanel::InitPanel()
{
	Panel* panel = addMouseBlockPanel(this, true);
	panel->setContentSize(CCSize(DESIGN_WIDTH, DESIGN_HEIGHT - 72));

	construct(getMxmlPath() + "dmy_tournament.mxml");
	mSeasonDesc = getLabel("txt_info1");
	mTournamentName = getLabel("txt_t_name");

	//보상 부분 관련
	mRewardBtn = getButton("sbtn_gift");
	mRewardStateLabel = getLabel("txt_win_count");

	mTournamentIcon = getSkel("skel_logo");
	mTournamentWindow = getSkel("skel_main_back");
	mNowSeasonBg = getSkel("skel_back_left1");
	mRewardBg = getSkel("skel_back_left2");
	mRecentWinnerBg = getSkel("skel_back_right1");
	
	mNowSeasonGrade = getLabel("txt_my_grade");
	mNowSeasonGradeUnder = getLabel("txt_my_grade_under");
	mReward = getLabel("txt_win_gift");
	mRewardUnder = getLabel("txt_win_gift_under");
	mRecentWinner = getLabel("txt_winner_user");
	mRecentWinnerUnder = getLabel("txt_winner_user_under");

	mTourRewardListPanel = new LobbyTourRewardListPanel();
	addChild(mTourRewardListPanel);
	mTourRewardListPanel->release();

	CCPoint _pos = getDummy("dmy_tournament_round").origin;
	_pos.y = -_pos.y;
	mTourRewardListPanel->setPosition(_pos);
	
	mCurrentRoundLabel = getLabel("txt_round");
	
	//
	mAddEnterPanel = new Panel();
	mAddEnterPanel->construct(getMxmlPath() + "dmy_button_tournament.mxml"); 
	addChild(mAddEnterPanel);
	mAddEnterPanel->release();
	_pos = getDummy("dmy_button_tournament").origin;
	_pos.y = -_pos.y;
	mAddEnterPanel->setPosition(_pos);

	mEnterBtn = mAddEnterPanel->getButton("sbtn_start");
	mEnterBtn->setListener(this); 
	mEnterPay = mAddEnterPanel->getLabel("txt_pay");
	mEnterIcon = mAddEnterPanel->getSkel("skel_icon");	
	mRankIconBtn = getButton("sbtn_rankicon");
	CCSize originSize = getDummy("sbtn_rankicon").size;
	CCSize iconSize = getDummy("dmy_rankicon").size;
	mRankIconBtn->getButtonSkelObject()->setScale(getScaleFit(originSize, iconSize));

	mAddEnterPanel->getLabel("txt_start_under")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyTourSelectPanel_ENTER_TITLE").c_str());
	mAddEnterPanel->getLabel("txt_start")->setString(GameStringDepot::getSingletonPtr()->getString("LobbyTourSelectPanel_ENTER_TITLE").c_str());


	mRuleBtn = getButton("sbtn_bo_button1");
	mRuleBtnLabel = getLabel("txt_rankinfo");
	mSeasonRankInfoBtn = getButton("sbtn_bo_button2");	
	mSeasonRankInfoBtnLabel = getLabel("txt_rule");
	mRewardCompleteIcon = getImage("skel_accept");

	//현재 시즌 등급
	mNowSeasonGrade->setString(GameStringDepot::getSingletonPtr()->getString("TXT_NOW_RANK_LABEL").c_str());
	mNowSeasonGradeUnder->setString(GameStringDepot::getSingletonPtr()->getString("TXT_NOW_RANK_LABEL").c_str());
	//5회 승리시 보상
	mReward->setString(GameStringDepot::getSingletonPtr()->getString("LobbyTourSelectPanel_REWARD_TITLE").c_str());
	mRewardUnder->setString(GameStringDepot::getSingletonPtr()->getString("LobbyTourSelectPanel_REWARD_TITLE").c_str());
	//시즌 랭킹 정보
	mRuleBtnLabel->setString(GameStringDepot::getSingletonPtr()->getString("LobbyTourSelectPanel_RANK_TITLE").c_str());
	//규칙
	mSeasonRankInfoBtnLabel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_RULE_LABEL").c_str());
	//최근 우승자
	mRecentWinner->setString(GameStringDepot::getSingletonPtr()->getString("LobbyTourSelectPanel_WINNER_TITLE").c_str());
	mRecentWinnerUnder->setString(GameStringDepot::getSingletonPtr()->getString("LobbyTourSelectPanel_WINNER_TITLE").c_str());
}

void LobbyTourSelectPanel::InitImage()
{
	mReputeGaugebar = getImage("skel_guage_bar1");
	mReputeGaugebar->setAnchorPoint(ccp(0.f, 0.5f));
	mReputeGaugebar->setPositionX(mReputeGaugebar->getPositionX() - getDummy("skel_guage_bar1").size.width / 2.0f);

	mWinGaugebar = getImage("skel_guage_bar2");
	mWinGaugebar->setAnchorPoint(ccp(0.f, 0.5f));
	mWinGaugebar->setPositionX(mWinGaugebar->getPositionX() - getDummy("skel_guage_bar2").size.width / 2.0f);


	for (int _i = 0; _i < 3; _i++)
	{
		string _photoName = "dmy_photo" + StringConverter::toString(_i + 1);
		m_pRankerPhoto[_i] = new Widget();
		m_pRankerPhoto[_i]->setVisible(false);
		getImage(_photoName)->addChild(m_pRankerPhoto[_i]);
		m_pRankerPhoto[_i]->release();
	}		
}

void LobbyTourSelectPanel::InitButton()
{
	mLeftRoundBtn = getButton("sbtn_previous_round");
	mRightRoundBtn = getButton("sbtn_next_round");
// 	getButton("sbtn_usertable1")->setType(Button::NoPressImg);
// 	getButton("sbtn_usertable2")->setType(Button::NoPressImg);
// 	getButton("sbtn_usertable3")->setType(Button::NoPressImg);
// 	getButton("sbtn_qbox")->setType(Button::NoPressImg);
// 
// 	getButton("sbtn_usertable1")->setListener(this);
// 	getButton("sbtn_usertable2")->setListener(this);
// 	getButton("sbtn_usertable3")->setListener(this);
// 	getButton("sbtn_qbox")->setListener(this);
// 	
// 	CCPoint _btnPos[3];
// 	_btnPos[0] = getDummy("dmy_button_big1").origin;
// 	_btnPos[1] = getDummy("dmy_button_big2").origin;
// 
// 	for (int _i = 0; _i < 2; _i++)
// 	{
// 		m_pEnterButton[_i] = new Panel();
// 		m_pEnterButton[_i]->construct(getMxmlPath() + "dmy_button_big.mxml");
// 		m_pEnterButton[_i]->getButton("sbtn_buttonwatch")->setListener(this);
// 		m_pEnterButton[_i]->getButton("sbtn_buttonwatch")->setName("sbtn_enter" + StringConverter::toString(_i + 1));
// 		m_pEnterButton[_i]->setPositionX(_btnPos[_i].x);
// 		m_pEnterButton[_i]->setPositionY(-_btnPos[_i].y);
// 		addChild(m_pEnterButton[_i]);
// 		m_pEnterButton[_i]->release();
// 		
// 		m_pEnterButton[_i]->getSkel("skel_icon_gold2");
// 		m_pEnterButton[_i]->getLabel("txt_type1_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
// 		m_pEnterButton[_i]->getLabel("txt_type1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
// 		m_pEnterButton[_i]->getLabel("txt_type2_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
// 		m_pEnterButton[_i]->getLabel("txt_type2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
// 		m_pEnterButton[_i]->getLabel("txt_gold_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
// 		m_pEnterButton[_i]->getLabel("txt_gold")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
// 	}

}

void LobbyTourSelectPanel::update(float dt)
{

}

void LobbyTourSelectPanel::onClicked(const string& name)
{
	if (GameDataManager::getSingletonPtr()->GetUiState() == LOBBY_UI_RANKER_GAME_POPUP)
		return;

	/*
	if (name == "sbtn_user_back1")
	{
		//show ReplayPopup
		W_TourInfo _tourInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo->tourinfo(m_SelectedIndex);
		int64 _uid = _tourInfo.tranker(0).uid();
		int64 _gamekey = _tourInfo.tranker(0).gamekey();
		WebService::getSingletonPtr()->TournamentReplayListReq(_uid, _gamekey);
	}
	else if (name == "sbtn_user_back2")
	{
		//show ReplayPopup
		W_TourInfo _tourInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo->tourinfo(m_SelectedIndex);
		int64 _uid = _tourInfo.tranker(1).uid();
		int64 _gamekey = _tourInfo.tranker(1).gamekey();
		WebService::getSingletonPtr()->TournamentReplayListReq(_uid, _gamekey);
	}
	else if (name == "sbtn_user_back3")
	{
		//show ReplayPopup
		W_TourInfo _tourInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo->tourinfo(m_SelectedIndex);
		int64 _uid = _tourInfo.tranker(2).uid();
		int64 _gamekey = _tourInfo.tranker(2).gamekey();
		WebService::getSingletonPtr()->TournamentReplayListReq(_uid, _gamekey);
	}
	*/
	if (name == mEnterBtn->getName()) {
		if (GameEnterCheck(mRoundIndex + 1)) {
			SendTournamentReady(m_SelectedIndex, mRoundIndex);
		}
	}
	else if (name == "sbtn_enter1")
	{
		//EnterGame
		if (GameEnterCheck(1) == true)
		{
			SendTournamentReady(m_SelectedIndex, 0);
		}
	}

	else if (name == "sbtn_enter2")
	{
		//EnterGame
		if (GameEnterCheck(2) == true)
		{
			SendTournamentReady(m_SelectedIndex, 1);
		}
	}

	else if (name == getButtonName(mRewardBtn))
	{
		WebService::getSingletonPtr()->TournamentRewardReq(GameDataManager::getSingletonPtr()->m_TournamentId);
	}
	else if (name == mLeftRoundBtn->getName()) {
		if (mRoundIndex > 0)
			mRoundIndex--;
		refreshReward();
	}
	else if (name == mRightRoundBtn->getName()) {
		W_TourInfo _tourInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo->tourinfo(m_SelectedIndex);
		int _stepinfoSize = _tourInfo.stepinfo_size();
		if (mRoundIndex <_stepinfoSize - 1)
			mRoundIndex++;
		refreshReward();
	}
	else if (name == getButtonName(mRankIconBtn)) {

	}
	else if (name == getButtonName(mRuleBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->ShowCustomWebview(
			WEB_TOURNAMENT_TYPE);
	}
	else if (name == getButtonName(mSeasonRankInfoBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		PanelHelper::pushSeasonRankInfoPanel();
	}
}

bool LobbyTourSelectPanel::GameEnterCheck(int _step)
{
	bool _isAble = false;

	W_TourOfInfo* _info = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	W_TourInfo _tourInfo = _info->tourinfo(m_SelectedIndex);
	W_TourStepInfo _stepinfo = _tourInfo.stepinfo(_step-1);
		
	string _OkMsg = "";

	switch(_stepinfo.status())
	{
	case W_TourStepInfo_eTourStatus_free:
		_isAble = true;
		break;
	case W_TourStepInfo_eTourStatus_ticket:
		_isAble = true;
		break;
	case W_TourStepInfo_eTourStatus_gomoney:
		_isAble = (_stepinfo.joinmoney() <= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney);
		if (_isAble == false)
			_OkMsg = "GO_TO_CHARACTER_SHOP_FROM_TOURNAMENT_SELECT";
		break;
	case W_TourStepInfo_eTourStatus_gocash:
		_isAble = (_stepinfo.joincash() <= GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash);
		if (_isAble == false)
			_OkMsg = "GO_TO_RUBYSHOP_FROM_TOURNAMENT_SELECT";
		break;
	}
	
	if (_isAble == false)
	{
		string _title = GameStringDepot::getSingleton().getString("TXT_NEED_ENTERGAME_TITLE");
		string _content = GameStringDepot::getSingleton().getString("TXT_NEED_ENTERGAME_DESC");

		SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::YESNONotice, _content, _title);
		if (_popupPanel)
		{
			_popupPanel->SetOkEventMsg(_OkMsg);
			_popupPanel->setListener(this);
			LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
		}

		return false;
	}

	return true;
	
}

bool LobbyTourSelectPanel::handling(STCMD &stCmd)
{
	if (auto *pstIt = castCMD<STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK>(&stCmd))
	{
		STCMD_CURL_DOWNLOAD_SOCIAL_PROFILE_ACK res = *pstIt;

		if (res.param != TOURNAMENT_PHOTO)
			return false;

		if (!res.imagePath.empty())
		{
			int _index = res.dParam;

			InitRankPhoto(_index, false);
		}
		return true;
	}

	return false;
}


bool LobbyTourSelectPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}
void LobbyTourSelectPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyTourSelectPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyTourSelectPanel::SetMyRank()
{
	W_TourOfInfo* _info = GameDataManager::getSingletonPtr()->m_TourOfInfo;	
	int _curRank = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Rating;	
	getLabel("txt_grade_name")->setString(PokerRankHelper::getRankTitleStr(_curRank).c_str());
	getLabel("txt_grade_name")->setColor(StringConverter::parseColor3B(PokerRankHelper::getRankTitleColorStr(_curRank)));
	SetRankPercentBar();
}

void LobbyTourSelectPanel::SetMyBonus()
{
	W_TourOfInfo* _info = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	W_TourInfo _tourInfo = _info->tourinfo(m_SelectedIndex);
	mRewardCompleteIcon->setVisible(false);
	if (_tourInfo.has_treward())
	{
		W_TourInfo_W_TourReward _bonusInfo = _tourInfo.treward();

		bool _isTodayReward = false;
		if (_bonusInfo.has_istodayreward())
		{
			_isTodayReward = _bonusInfo.istodayreward();
		}
		
		
		if (_isTodayReward == true)
		{
			//오늘 보상을 받았다.
			//버튼 비활성화			
			mRewardBtn->setEnable(false);
			mRewardBtn->setGrayscale(true);
			mRewardCompleteIcon->setVisible(true);
			//완료 표시만 넣자.
			mRewardStateLabel->setString("0 / 0");			
			SetBonusPercentBar(0, 1);		//아무것도 안 보인다.
		}
		else
		{
			int _now = _bonusInfo.cnt();
			int _max = _bonusInfo.maxcnt();
			string rewardStateStr = StringConverter::toString(_now) + " / " + StringConverter::toString(_max);
			mRewardStateLabel->setString(rewardStateStr.c_str());
			SetBonusPercentBar(_now, _max);
			if (_now < _max)
			{
				mRewardBtn->setEnable(false);
				mRewardBtn->setGrayscale(true);
			}
			else
			{
				mRewardBtn->setEnable(true);
				mRewardBtn->setGrayscale(false);
			}
		}
	}
}

void LobbyTourSelectPanel::SetBonusPercentBar(int _now, int _max)
{
	float _scaleX = (float)_now / (float)_max;
	mWinGaugebar->setScaleX(_scaleX);	
}

void LobbyTourSelectPanel::SetRankPercentBar()
{
	int beforeInit = 0;
	int nowRepute = 0;
	int maxRepute = 0;
	float ratio = 0.f;
	string _curString = "";
	if (PokerRankHelper::getRank() == 0) {
		nowRepute = PokerRankHelper::getNowRepute();
		maxRepute = PokerRankHelper::getLevelupRepute();
		ratio = PokerRankHelper::getRatioRepute();
		_curString = StringConverter::toString(nowRepute) + "/" + StringConverter::toString(maxRepute);
	}
	else {
		if (PokerRankHelper::getLevelupRepute() == -1) {
			beforeInit = PokerRankHelper::getReputeAmount(PokerRankHelper::getRank());
			nowRepute = PokerRankHelper::getNowRepute();
			maxRepute = beforeInit;
			ratio = 1.0f;
			_curString = StringConverter::toString(nowRepute);
		}
		else {
			beforeInit = PokerRankHelper::getReputeAmount(PokerRankHelper::getRank());
			nowRepute = PokerRankHelper::getNowRepute() - beforeInit;
			maxRepute = PokerRankHelper::getLevelupRepute() - beforeInit;
			ratio = (float)nowRepute / (float)maxRepute;
			_curString = StringConverter::toString(nowRepute) + "/" + StringConverter::toString(maxRepute);
		}		
	}


	
	getLabel("txt_grade_count")->setString(_curString.c_str());	
	mReputeGaugebar->setScaleX(ratio);
}


void LobbyTourSelectPanel::SetJoinButton(int _index, W_TourStepInfo _info)
{
	switch (_info.status())
	{
	case W_TourStepInfo_eTourStatus_no:
	{
		mEnterBtn->setEnable(false);
		mEnterIcon->setVisible(false);
		string _doorMoney = GameStringDepot::getSingletonPtr()->getString("TXT_CANT_JOIN_LABEL");
		mEnterPay->setString(_doorMoney.c_str());
		break;
	}
	case W_TourStepInfo_eTourStatus_free:
	{
		mEnterBtn->setEnable(true);
		mEnterIcon->setVisible(false);
		string _doorMoney = GameStringDepot::getSingletonPtr()->getString("TXT_FREE_UNIT");
		mEnterPay->setString(_doorMoney.c_str());
		break;
	}
	case W_TourStepInfo_eTourStatus_ticket:
	{
		mEnterBtn->setEnable(true);
		mEnterIcon->setVisible(true);		
		mEnterIcon->playAnimation("image_chip");
		mEnterIcon->setScale(0.5f);
		//mEnterIcon->playAnimation(PokerResourceHelper::getTicketResourceIconStr(_info.ticketid()));
		string _doorMoney = "x1";
		mEnterPay->setString(_doorMoney.c_str());
		break;
	}
	case W_TourStepInfo_eTourStatus_gomoney:
	{
		mEnterIcon->setVisible(true);
		mEnterIcon->playAnimation("image_chip");
		mEnterIcon->setScale(0.5f);
		string _doorMoney = "x" + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_info.joinmoney()), 1);
		mEnterPay->setString(_doorMoney.c_str());
		mEnterBtn->setEnable(true);
		break;
	}
	case W_TourStepInfo_eTourStatus_gocash:
	{
		mEnterIcon->setVisible(true);
		mEnterIcon->playAnimation("image_chip");
		mEnterIcon->setScale(0.5f);
		string _doorMoney = "x" + StringConverter::toString(_info.joincash());
		mEnterPay->setString(_doorMoney.c_str());
		mEnterBtn->setEnable(true);
		break;
	}
	}
}


void LobbyTourSelectPanel::SetRound()
{
	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	if (_pInfoData)
	{
		W_TourInfo _tourInfo = _pInfoData->tourinfo(m_SelectedIndex);
		SetRoundInfoTable(_tourInfo);
	}
}
		
void LobbyTourSelectPanel::SetRoundInfoTable(W_TourInfo _info)
{
	mTourRewardListPanel->setTourStepInfo(_info.stepinfo(mRoundIndex));
	//
	return;
	int _stepinfoSize = _info.stepinfo_size();

	if (_stepinfoSize == 2)
	{
		getLabel("txt_roundguide")->setVisible(true);
	}
	else
	{
		getLabel("txt_roundguide")->setVisible(false);
	}

	for (int _i = 0; _i < 2; _i++)
	{
		string _roundName = "txt_r" + StringConverter::toString(_i + 1);
		string _tableName = "skel_table" + StringConverter::toString(_i + 1);
		
		if (_i < _stepinfoSize)
		{
			W_TourStepInfo _stepInfo = _info.stepinfo(_i);

			getSkel(_tableName)->setVisible(true);
			getLabel(_roundName + "_title")->setVisible(true);
			getLabel(_roundName + "_ruleunder")->setVisible(true);
			getLabel(_roundName + "_rule")->setVisible(true);
			m_pEnterButton[_i]->setVisible(true);
			m_pEnterButton[_i]->getButton("sbtn_buttonwatch")->setEnable(true);
			SetJoinButton(_i, _info.stepinfo(_i));

			string _title = "ROUND" + StringConverter::toString(_i + 1);
			getLabel(_roundName + "_title")->setString(_title.c_str());

			string _rule = "";

			_rule = "[" + GameStringDepot::getSingletonPtr()->getString("TXT_SEED_MONEY_LABEL") + "]";
			_rule += GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_stepInfo.seedmoney()), 1);
			_rule += "     [" + GameStringDepot::getSingletonPtr()->getString("TXT_STANDARD_MONEY_LABEL") + "]";
			_rule += GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_stepInfo.startmoney()), 1);
			
			getLabel(_roundName + "_rule")->setString(_rule.c_str());
			getLabel(_roundName + "_ruleunder")->setString(_rule.c_str());

			for (int _num = 0; _num < 3; _num++)
			{
				int _rank = _num + 1;
				int64 _gold = 0;
				int _fame = 0;
				if (_num < _stepInfo.rewardinfo_size())
				{
					int _rewardSize = _stepInfo.rewardinfo(_num).rewardset_size();
					for (int _index = 0; _index < _rewardSize; _index++)
					{
						W_RewardInfo_RewardSet _rewardset = _stepInfo.rewardinfo(_num).rewardset(_index);
						if (_rewardset.type() == GAMEMONEY)
						{
							_gold = _rewardset.amount();
						}
						else if (_rewardset.type() == REPUTE)
						{
							_fame = _rewardset.amount();
						}
					}
					//getLabel("str_r3_gift" + StringConverter::toString(_num + 1))->setString(_bonus.c_str());
					SetRankGift((_i * 3) + _num, _rank, _gold, _fame);
				}
				else
				{
					SetRankGift((_i * 3) + _num, _rank, _gold, _fame, false);
				}
			}
		}
		else
		{
			getSkel(_tableName)->setVisible(false);
			getLabel(_roundName + "_title")->setVisible(false);
			getLabel(_roundName + "_ruleunder")->setVisible(false);
			getLabel(_roundName + "_rule")->setVisible(false);
			m_pEnterButton[_i]->setVisible(false);
			m_pEnterButton[_i]->getButton("sbtn_buttonwatch")->setEnable(false);
			for (int _num = 0; _num < 3; _num++)
			{
				SetRankGift((_i * 3) + _num, 0, 0, 0, false);
			}
		}
		
	}
}

void LobbyTourSelectPanel::SetRankGift(int _index, int _rank, int64 _gold, int _fame, bool _visible)
{
	Panel* _pPanel = m_pRankGift[_index];

	if (_visible == false || (_gold == 0 && _fame == 0))
	{
		_pPanel->setVisible(false);
		return;
	}

	_pPanel->setVisible(true);

	if (_gold == 0)
	{
		_pPanel->getSkel("skel_gold")->setVisible(false);
		_pPanel->getLabel("txt_gold_sum")->setVisible(false);
	}
	else
	{
		_pPanel->getSkel("skel_gold")->setVisible(true);
		_pPanel->getLabel("txt_gold_sum")->setVisible(true);

		string _goldTxt = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_gold), 2);
		_pPanel->getLabel("txt_gold_sum")->setString(_goldTxt.c_str());
	}

	if (_fame == 0)
	{
		_pPanel->getSkel("skel_trophy")->setVisible(false);
		_pPanel->getLabel("txt_fame_sum")->setVisible(false);
	}
	else
	{
		_pPanel->getSkel("skel_trophy")->setVisible(true);
		_pPanel->getLabel("txt_fame_sum")->setVisible(true);

		string _fameTxt = StringConverter::toString(_fame);
		_pPanel->getLabel("txt_fame_sum")->setString(_fameTxt.c_str());
	}

	_pPanel->getLabel("txt_rank")->setVisible(true);
	string _rankTxt = StringConverter::toString(_rank) + GameStringDepot::getSingletonPtr()->getString("TXT_RANK");
	_pPanel->getLabel("txt_rank")->setString(_rankTxt.c_str());

	_pPanel->getSkel("skel_table")->setVisible(true);
}

void LobbyTourSelectPanel::SetRanker()
{
	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;

	if (_pInfoData)
	{
		string _rankLabel = "";
		string _nameLabel = "";
		string _userPhoto = "";
		string _dmyPhoto = "";
		string _userButton = "";

		int _tourInfoSize = _pInfoData->tourinfo_size();
		for (int _i = 0; _i < _tourInfoSize; _i++)
		{
			W_TourInfo _tourInfo = _pInfoData->tourinfo(_i);

			if (GameDataManager::getSingletonPtr()->m_TournamentId == _tourInfo.tourid())
			{
				m_SelectedIndex = _i;
				int _size = _tourInfo.tranker_size();
				if (_size > 3)
					_size = 3;

				for (int _i = 0; _i < 3; _i++)
				{
					//_rankLabel = "txt_rank" + StringConverter::toString(_i + 1);
					_nameLabel = "txt_usernickname" + StringConverter::toString(_i + 1);					
					_userButton = "sbtn_user_back" + StringConverter::toString(_i + 1);
					if (_size > _i)
					{
						//getLabel(_rankLabel)->setVisible(true);
						getLabel(_nameLabel)->setVisible(true);						
						getButton(_userButton)->setVisible(true);
						getButton(_userButton)->setEnable(true);

						W_TourInfo_W_TourRanker _rankerInfo = _tourInfo.tranker(_i);
						int64 _uid = _rankerInfo.uid();
						int64 _gamekey = _rankerInfo.gamekey();
						string _name = _rankerInfo.name();
						string _imgUrl = _rankerInfo.imageurl();
						getLabel(_nameLabel)->setString(_name.c_str());
						InitRankPhoto(_i, true);
					}
					else
					{
						//getLabel(_rankLabel)->setVisible(false);
						getLabel(_nameLabel)->setVisible(false);						
						getButton(_userButton)->setVisible(false);
						getButton(_userButton)->setEnable(false);
					}
				}
			}
		}
	}
}

void LobbyTourSelectPanel::ShowSelectPanel(int round /*= 0*/)
{
	mRoundIndex = round;		
	if (mRoundIndex == -1)
		mRoundIndex = 0;

	SetRanker();
	SetMyRank();
	SetMyBonus();		
	SetTitleName();
	refreshReward();

	initSeasonDesc();
	initRoundState();
	refreshWindowColor();

	if (LayerManager::getSingleton().hasLayerType<LobbyTournamentMain>()) {
		LobbyTournamentMain* pLobbyTournmaneMainPanel = dynamic_cast<LobbyTournamentMain*>(LayerManager::getSingleton().getLayerType<LobbyTournamentMain>());
		pLobbyTournmaneMainPanel->setVisibleChannelCell(false);
	}			
}


void LobbyTourSelectPanel::SendTournamentReady(int _index, int _stepIndex)
{
	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	W_TourInfo _tourInfo = _pInfoData->tourinfo(_index);

	if (_tourInfo.stepinfo_size() == 0)
		return;

	W_TourStepInfo _stepInfo = _tourInfo.stepinfo(_stepIndex);
	W_ChannelInfo _ChannelInfo = _stepInfo.channelinfo();

	GameDataManager::getSingletonPtr()->mTourSelectIndex = _index;
	GameDataManager::getSingletonPtr()->mTourStep = _stepIndex;
	GameDataManager::getSingletonPtr()->m_seasonId = _pInfoData->seasonid();

	GameDataManager::getSingletonPtr()->m_TournamentId = _tourInfo.tourid();
	GameDataManager::getSingletonPtr()->m_TournamentStep = _stepInfo.stepid();
	GameDataManager::getSingletonPtr()->m_TournamentStatus = _stepInfo.status();

	GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney1 = _ChannelInfo.bigpot_1();
	GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney2 = _ChannelInfo.bigpot_2();
	GameDataManager::getSingletonPtr()->m_RoomId = _ChannelInfo.id();
	GameDataManager::getSingletonPtr()->m_BettingRule = _ChannelInfo.bettingrule();
	GameDataManager::getSingletonPtr()->m_seedMoney = _ChannelInfo.seedmoney();
	GameDataManager::getSingletonPtr()->m_Grade = _ChannelInfo.grade();
	GameDataManager::getSingletonPtr()->m_EnterGameRoomBettingMaxMoney = _ChannelInfo.bigbettingmaxmoney();
	GameDataManager::getSingletonPtr()->m_GameMode = _ChannelInfo.gamemode();

	GameDataManager::getSingletonPtr()->m_TournamentIp = _ChannelInfo.ip();
	GameDataManager::getSingletonPtr()->m_TournamentPort = _ChannelInfo.port();

	WebService::getSingletonPtr()->TournamentEnterReq();

}

void LobbyTourSelectPanel::ApplyRankGamePopup()
{
	W_TourOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	W_TourInfo _tourInfo = _pInfo->tourinfo(m_SelectedIndex);
	string name = _tourInfo.name() + " " + GameStringDepot::getSingletonPtr()->getString("TXT_CHAMPIONSHIP_LABEL");

	LobbyRankerGamePopup* pPanel = new LobbyRankerGamePopup();
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
	pPanel->ShowPanel(true);
	pPanel->SetData(name);
	pPanel->SetType(GameMode::MODE_NORMAL_TOURNAMENT);	
}

void LobbyTourSelectPanel::SetTitleName()
{
	//W_TourOfInfo* _info = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	//W_TourInfo _tourInfo = _info->tourinfo(m_SelectedIndex);

	//string _titleTxt =_tourInfo.name() + " " + GameStringDepot::getSingletonPtr()->getString("TXT_CHAMPIONSHIP_LABEL");
	//m_SubTopPanel->SetVisibleTitle(SUB_TOP_TOURNAMENT, _titleTxt);
}

void LobbyTourSelectPanel::InitRankPhoto(int _index, bool isTryDownload)
{
	W_TourOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	W_TourInfo _tourInfo = _pInfo->tourinfo(m_SelectedIndex);
	
	W_TourInfo_W_TourRanker _info = _tourInfo.tranker(_index);
	bool _ret;

	//if (_info.has_imageurl() && _info.imageurl() != "")
	//{
	//	_ret = GameDataManager::getSingletonPtr()->LoadFileImage(
	//		_info.name(),
	//		_info.imageurl(),
	//		DOWNLOAD_FILE_TYPE::TOURNAMENT_PHOTO,
	//		m_pRankerPhoto[_index],
	//		isTryDownload,
	//		TEMP_PHOTO_FOLDER,
	//		_index
	//		);

	//	// 로딩되었으면 이미지를 교체한다.
	//	if (_ret)
	//	{
	//		UpdateRankPhoto(_index);
	//	}
	//}
	//else
	//{
	//	m_pRankerPhoto[_index]->setSpriteFrameWithFile("ui/default_photo.png");
	//	UpdateRankPhoto(_index);
	//}
	m_pRankerPhoto[_index]->setSpriteFrameWithFile(PokerResourceHelper::getCharacterPhotoImg(_info.characterid()));
	UpdateRankPhoto(_index);
}

void LobbyTourSelectPanel::UpdateRankPhoto(int _cellIndex)
{
	string _dmyPhoto = "dmy_photo" + StringConverter::toString(_cellIndex + 1);	
	CCRect rect = getDummy(_dmyPhoto);
	m_pRankerPhoto[_cellIndex]->fit(CCSize(rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY()));
	m_pRankerPhoto[_cellIndex]->setVisible(true);
}

void LobbyTourSelectPanel::refreshReward()
{
	//라운드 표시
	string curRoundStr = "ROUND" + StringConverter::toString(mRoundIndex + 1);
	mCurrentRoundLabel->setString(curRoundStr.c_str());		
	SetRound();

	//mEnterPay

	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	if (_pInfoData)
	{
		W_TourInfo _tourInfo = _pInfoData->tourinfo(m_SelectedIndex);
		SetJoinButton(mRoundIndex, _tourInfo.stepinfo(mRoundIndex));
	}	
}

void LobbyTourSelectPanel::initSeasonDesc()
{

}

void LobbyTourSelectPanel::initRoundState()
{
	//라운드가 1개라면
	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	W_TourInfo _tourInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo->tourinfo(m_SelectedIndex);

	mSeasonDesc->setString(_pInfoData->title().c_str());
	int _stepinfoSize = _tourInfo.stepinfo_size();
	//홀수라면
	if (_stepinfoSize == 1) {
		mLeftRoundBtn->setEnable(false);
		mLeftRoundBtn->setVisible(false);
		mRightRoundBtn->setEnable(false);
		mRightRoundBtn->setVisible(false);
	}
	else {
		mLeftRoundBtn->setEnable(true);
		mLeftRoundBtn->setVisible(true);
		mRightRoundBtn->setEnable(true);
		mRightRoundBtn->setVisible(true);		
	}
}

void LobbyTourSelectPanel::refreshWindowColor()
{
	string tournameIconAniStr = "";
	string tournameWindowAniStr = "";
	//현재 시즌 등급 
	string seasonGradeColor = "";
	string seasonGradeUnderColor = "";
	//5회 승리시 보상
	string rewardColor = "";
	string rewardUnderColor = "";
	//최근 우승자
	string recentWinnerColor = "";
	string recentWinnerUnderColor = "";
	
	//현재 시즌 등급 , 5회 승리시 보상 
	string tabLeftBgAniStr = "";
	//최근 우승자 
	string tabRightgAniStr = "";
	//유저 이름 뒤 배경
	string userBgAniStr = "";
	string seasonUnderColor = "";

	//버튼 ani
	string leftButtonAniStr = "";
	string rightButtonAniStr = "";

	//user 버튼 aniStr
	string userBtnStr = "";
	string seasonBtnStr = "";
	

	switch (GameDataManager::getSingletonPtr()->getGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		userBtnStr = "user_back_seven";
		tournameIconAniStr = "logo_seven";
		tournameWindowAniStr = "main_back_seven";
		tabLeftBgAniStr = "back_left_seven";
		tabRightgAniStr = "back_right_seven";
		userBgAniStr = "user_back_seven";
		seasonGradeColor = "ffd6d5";
		seasonGradeUnderColor = "b62d37";
		rewardColor = "ffd6d5";
		rewardUnderColor = "b62d37";
		recentWinnerColor = "ffd6d5";
		recentWinnerUnderColor = "b62d37";
		seasonUnderColor = "5f0808";
		leftButtonAniStr = "btn_arrow_pre_seven";
		rightButtonAniStr = "btn_arrow_next_seven";
		seasonBtnStr = "button2_seven";

		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		userBtnStr = "user_back_highlow";
		tournameIconAniStr = "logo_highlow";
		tournameWindowAniStr = "main_back_highlow";
		tabLeftBgAniStr = "back_left_highlow";
		tabRightgAniStr = "back_right_highlow";
		userBgAniStr = "user_back_highlow"; 
		seasonGradeColor = "D4FAFF";
		seasonGradeUnderColor = "1D79E3";
		rewardColor = "D4FAFF";
		rewardUnderColor = "1D79E3";
		recentWinnerColor = "D4FAFF";
		recentWinnerUnderColor = "1D79E3";
		seasonUnderColor = "08225F";
		leftButtonAniStr = "btn_arrow_pre_highlow";
		rightButtonAniStr = "btn_arrow_next_highlow";
		seasonBtnStr = "button2_highlow";
		break;
	case GameKind::GAMEKIND_BADUKI:
		userBtnStr = "user_back_badugi";
		tournameIconAniStr = "logo_badugi";
		tournameWindowAniStr = "main_back_badugi";
		tabLeftBgAniStr = "back_left_badugi";
		tabRightgAniStr = "back_right_badugi";
		userBgAniStr = "user_back_badugi";

		seasonGradeColor = "c5ffb2";
		seasonGradeUnderColor = "258830";
		rewardColor = "c5ffb2";
		rewardUnderColor = "258830";
		recentWinnerColor = "c5ffb2";
		recentWinnerUnderColor = "258830";
		seasonUnderColor = "1b510e";

		leftButtonAniStr = "btn_arrow_pre_badugi";
		rightButtonAniStr = "btn_arrow_next_badugi";
		seasonBtnStr = "button2_badugi";
		break;
	case GameKind::GAMEKIND_HOLDEM:
		userBtnStr = "user_back_texas";
		tournameIconAniStr = "logo_texas";
		tournameWindowAniStr = "main_back_texas";
		tabLeftBgAniStr = "back_left_texas";
		tabRightgAniStr = "back_right_texas";
		userBgAniStr = "user_back_texas";
		
		seasonGradeColor = "cdfff4";
		seasonGradeUnderColor = "208775";
		rewardColor = "cdfff4";
		rewardUnderColor = "208775";
		recentWinnerColor = "cdfff4";
		recentWinnerUnderColor = "208775";
		seasonUnderColor = "085e55";

		leftButtonAniStr = "btn_arrow_pre_texas";
		rightButtonAniStr = "btn_arrow_next_texas";
		seasonBtnStr = "button2_texas";
		break;
	}

	mTournamentIcon->playAnimation(tournameIconAniStr);
	mTournamentWindow->playAnimation(tournameWindowAniStr);
	//현재 시즌 등급
	mNowSeasonBg->playAnimation(tabLeftBgAniStr);
	mNowSeasonGrade->setColor(StringConverter::parseColor3B(seasonGradeColor));
	mNowSeasonGradeUnder->setColor(StringConverter::parseColor3B(seasonGradeUnderColor));

	//5회 승리시 보상
	mRewardBg->playAnimation(tabLeftBgAniStr);	
	mReward->setColor(StringConverter::parseColor3B(rewardColor));
	mRewardUnder->setColor(StringConverter::parseColor3B(rewardUnderColor));

	//최근 우승자
	mRecentWinnerBg->playAnimation(tabRightgAniStr);
	mRecentWinner->setColor(StringConverter::parseColor3B(recentWinnerColor));
	mRecentWinnerUnder->setColor(StringConverter::parseColor3B(recentWinnerUnderColor));

	//
	mSeasonDesc->setStrokeColor((ccColor4B)StringConverter::parseColor3B(seasonUnderColor));
	mTournamentName->setStrokeColor((ccColor4B)StringConverter::parseColor3B(seasonUnderColor));
	mCurrentRoundLabel->setStrokeColor((ccColor4B)StringConverter::parseColor3B(seasonUnderColor));

	W_TourInfo _tourInfo = GameDataManager::getSingletonPtr()->m_TourOfInfo->tourinfo(m_SelectedIndex);
	mTournamentName->setString(_tourInfo.name().c_str());
	PokerRankHelper::setRankIcon(mRankIconBtn->getButtonSkelObject(), PokerRankHelper::getRank());

	mLeftRoundBtn->setSkelAnimation(leftButtonAniStr);
	mRightRoundBtn->setSkelAnimation(rightButtonAniStr);

	getButton("sbtn_user_back1")->setSkelAnimation(userBtnStr);
	getButton("sbtn_user_back2")->setSkelAnimation(userBtnStr);
	getButton("sbtn_user_back3")->setSkelAnimation(userBtnStr);


	mRuleBtn->setSkelAnimation(seasonBtnStr);
	mSeasonRankInfoBtn->setSkelAnimation(seasonBtnStr);

	mRuleBtnLabel->setColor(StringConverter::parseColor3B(seasonGradeUnderColor));
	mSeasonRankInfoBtnLabel->setColor(StringConverter::parseColor3B(seasonGradeUnderColor));

}

void LobbyTourSelectPanel::refreshData()
{
	SetRanker();
	SetMyRank();
	SetMyBonus();
	SetRound();
	SetTitleName();
}

void LobbyTourSelectPanel::onLayerMessage(const string& msg)
{
	if (msg == "GO_TO_CHARACTER_SHOP_FROM_TOURNAMENT_SELECT") {
		PanelHelper::pushCharacterShopPanel();
	}
	else if (msg == "GO_TO_RUBYSHOP_FROM_TOURNAMENT_SELECT") {
		PanelHelper::pushRubyShopPanel();
	}
}

void LobbyTourSelectPanel::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}