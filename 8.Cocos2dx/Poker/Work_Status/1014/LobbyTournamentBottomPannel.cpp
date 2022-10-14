#include "pch.h"
#include "LobbyTournamentBottomPannel.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "CustomPopupPanel.h"
#include "GameStringDepot.h"
#include "LobbyScene.h"
#include "PokerResourceHelper.h"
#include "PanelHelper.h"

LobbyTournamentBottomPannel::LobbyTournamentBottomPannel()
{
	m_catchCenterIndex = -1;
	m_totalChannelCount = 0;
	m_curChannelIndex = 0;

	m_pChannelView = nullptr;
	m_pChannelContainer = nullptr;

	for (int _i = 0; _i < TOURNAMENT_CELL_MAX; _i++)
	{
		m_pChannel[_i] = nullptr;
	}

	InitPanel();
	InitImage();
	initButton();

	setTouchable(false);
	setButtonListener(this);	
}

LobbyTournamentBottomPannel::~LobbyTournamentBottomPannel()
{
	//destruct();
}

void LobbyTournamentBottomPannel::InitPanel()
{
	construct(getMxmlPath() + "dmy_tournament_position.mxml");
	
	InitChannelList();
	//CreateChannelCell();
}

void LobbyTournamentBottomPannel::InitImage()
{
	InitCenterPanel();
}

void LobbyTournamentBottomPannel::initButton()
{
	mRuleBtn = getButton("sbtn_bo_button1");
	mRuleBtnLabel = getLabel("txt_rankinfo");
	mSeasonRankInfoBtn = getButton("sbtn_bo_button2");
	mSeasonRankInfoBtnLabel = getLabel("txt_rule");
	//시즌 랭킹 정보
	mRuleBtnLabel->setString(GameStringDepot::getSingletonPtr()->getString("LobbyTourSelectPanel_RANK_TITLE").c_str());
	//규칙
	mSeasonRankInfoBtnLabel->setString(GameStringDepot::getSingletonPtr()->getString("TXT_RULE_LABEL").c_str());

	string seasonBtnStr = "";
	string seasonGradeUnderColor = "";

	switch (GameDataManager::getSingletonPtr()->getGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		seasonGradeUnderColor = "b62d37";
		seasonBtnStr = "button2_seven";

		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		seasonGradeUnderColor = "1D79E3";
		seasonBtnStr = "button2_highlow";
		break;
	case GameKind::GAMEKIND_BADUKI:
		seasonGradeUnderColor = "258830";
		seasonBtnStr = "button2_badugi";
		break; 
	case GameKind::GAMEKIND_HOLDEM:
		seasonGradeUnderColor = "208775";
		seasonBtnStr = "button2_texas";
		break;
	}

	mRuleBtn->setSkelAnimation(seasonBtnStr);
	mSeasonRankInfoBtn->setSkelAnimation(seasonBtnStr);

	mRuleBtnLabel->setColor(StringConverter::parseColor3B(seasonGradeUnderColor));
	mSeasonRankInfoBtnLabel->setColor(StringConverter::parseColor3B(seasonGradeUnderColor));
}


bool LobbyTournamentBottomPannel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}


void LobbyTournamentBottomPannel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	
}

void LobbyTournamentBottomPannel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void LobbyTournamentBottomPannel::resume()
{
}

void LobbyTournamentBottomPannel::onClicked(const string& name)
{
	if (name == "sbtn_button_enter")
	{
		LobbyTournamentCell* _pCell = m_pChannel[m_catchCenterIndex];
		if (_pCell == nullptr)
			return;

		W_ChannelInfo* _pInfo = _pCell->m_CellInfo;
		if (_pInfo == nullptr)
			return;

		if (_pCell->getButton("sbtn_tournament_button")->isEnabled() == true)
		{
			int _dst = _pCell->getButton("sbtn_tournament_button")->getTag();
			_pCell->SelectTournamentCell(_dst);
		}
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

void LobbyTournamentBottomPannel::update(float dt)
{
}

bool LobbyTournamentBottomPannel::handling(STCMD &stCmd)
{
	return false;
}

void LobbyTournamentBottomPannel::UpdateChannelCell()
{
	if (m_pChannelView == NULL)
		return;

	for (int _i = 0; _i < TOURNAMENT_CELL_MAX; _i++)
	{
		if (m_totalChannelCount <= _i)
			continue;

		int _index = _i + m_curChannelIndex;
		if (m_totalChannelCount <= _index)
		{
			_index = _index % m_totalChannelCount;
		}

		if (_index < 0)
		{
			_index = m_totalChannelCount + (_index % m_totalChannelCount);
			if (_index == m_totalChannelCount)
			{
				_index = 0;
			}
		}

		m_pChannel[_i]->SetCellData(_index);
	}
}

//void LobbyTournamentBottomPannel::CreateChannelCell()
//{
//	if (GameDataManager::getSingletonPtr()->m_TourOfInfo == nullptr)
//		return;
//
//	CCSize _contentSize = getDummy("dmy_channel_position").size;
//
//	m_totalChannelCount = GameDataManager::getSingletonPtr()->m_TourOfInfo->tourinfo_size();
//
//	m_pChannelContainer = CCLayer::create();
//	if ((TOURNAMENT_CELL_INIT_X * 2) + (m_totalChannelCount * TOURNAMENT_CELL_WIDTH) > DESIGN_WIDTH)
//	{
//		if (m_totalChannelCount > TOURNAMENT_CELL_MAX)
//		{
//			m_pChannelContainer->setContentSize(CCSizeMake((TOURNAMENT_CELL_INIT_X * 2) + (TOURNAMENT_CELL_MAX * TOURNAMENT_CELL_WIDTH), TOURNAMENT_CELL_HIGHT));
//		}
//		else
//		{
//			m_pChannelContainer->setContentSize(CCSizeMake((TOURNAMENT_CELL_INIT_X * 2) + (m_totalChannelCount * TOURNAMENT_CELL_WIDTH), TOURNAMENT_CELL_HIGHT));
//		}
//	}
//	else
//	{
//		m_pChannelContainer->setContentSize(CCSizeMake(DESIGN_WIDTH, TOURNAMENT_CELL_HIGHT));
//	}
//
//
//	for (int _i = 0; _i < TOURNAMENT_CELL_MAX; _i++)
//	{
//		if (m_totalChannelCount <= _i)
//			continue;
//
//		m_pChannel[_i] = new LobbyTournamentCell();
//		m_pChannelContainer->addChild(m_pChannel[_i], 1);
//		m_pChannel[_i]->setPositionX(TOURNAMENT_CELL_WIDTH * _i + TOURNAMENT_CELL_INIT_X);
//		m_pChannel[_i]->setPositionY(TOURNAMENT_CELL_HIGHT - DESIGN_HEIGHT);
//		m_pChannel[_i]->release();
//	}
//
//	UpdateChannelCell();
//
//	m_pChannelView = extension::CCScrollView::create(_contentSize, m_pChannelContainer);
//	m_pChannelView->setDirection(extension::kCCScrollViewDirectionHorizontal);
//	m_pChannelView->setBounceable(false);
//	m_pChannelView->setContentOffset(ccp(0, 0), false);
//	m_pChannelView->setTouchEnabled(false);
//
//	m_pChannelView->setPosition(ccp(0.f, DESIGN_HEIGHT - _contentSize.height - 50.f));
//	addChild(m_pChannelView);
//}

//void LobbyTournamentBottomPannel::RemoveChannelCell()
//{
//	if (m_pChannelView)
//	{
//		m_pChannelView->removeFromParentAndCleanup(true);
//		m_pChannelView = nullptr;
//	}
//
//}

void LobbyTournamentBottomPannel::UpdateCellScale()
{
	if (m_pChannelView == NULL)
		return;

	ReleseCenterCell();
	m_catchCenterIndex = -1;

	for (int _i = 0; _i < TOURNAMENT_CELL_MAX; _i++)
	{
		if (m_totalChannelCount <= _i)
			continue;

		float _initScale = 0.5f;
		float _weightScale = 0.5f;
		//float _weightX = TOURNAMENT_CELL_WIDTH * 6.f;
		float _startRange = TOURNAMENT_CELL_WIDTH * 0.5f;
		float _endRange = DESIGN_WIDTH;

		int _cellX = TOURNAMENT_CELL_WIDTH * (_i)+ TOURNAMENT_CELL_INIT_X;
		int _cellY = TOURNAMENT_CELL_HIGHT - DESIGN_HEIGHT - 15.f;
		int _offset = m_pChannelView->getContentOffset().x;
		int _diffCellX = _cellX + _offset - _startRange + TOURNAMENT_CELL_WIDTH;
		int _cellScaleX = _cellX + _offset - (TOURNAMENT_CELL_WIDTH * 0.5f) + TOURNAMENT_CELL_WIDTH;

		int _diffX = 0;
		int _diffY = 0;
		float _diffScale = ((float)_diffCellX) / _endRange;
		float _diffcellScale = ((float)_cellScaleX) / DESIGN_WIDTH;

		if (_diffScale > 0.49f && _diffScale < 0.51f)
		{
			m_catchCenterIndex = _i;
		}

		if (_diffCellX < _endRange / 2.f && _diffCellX >= 0)
		{
			float _cellScale = _initScale + (_weightScale * _diffcellScale * 2.f);
			m_pChannel[_i]->setScale(_cellScale);
			_diffX = getCellMetrics(_diffScale);//_weightX * ((0.5f - (0.5f - _diffScale)) * (0.5f - _diffScale));
			_diffY = _cellY * (0.9f - _cellScale);
		}
		else if (_diffCellX < _endRange && _diffCellX >= _endRange / 2.f)
		{
			float _cellScale = _initScale + (_weightScale * (1.f - _diffcellScale) * 2.f);
			m_pChannel[_i]->setScale(_cellScale);
			_diffX = getCellMetrics(_diffScale);// -_weightX *((0.5f - (_diffScale - 0.5f)) * (_diffScale - 0.5f));// ((_diffScale - 0.5f) * 1.6f);
			_diffY = _cellY * (0.9f - _cellScale);
		}
		else if (_diffCellX < 0)
		{
			float _cellScale = _initScale + (_weightScale * _diffcellScale * 2.f);
			m_pChannel[_i]->setScale(_cellScale);
			_diffX = _cellX;
			_diffY = _cellY * (0.9f - _cellScale);
		}
		else
		{
			float _cellScale = _initScale + (_weightScale * (1.f - _diffcellScale) * 2.f);
			m_pChannel[_i]->setScale(_cellScale);
			_diffX = _cellX;
			_diffY = _cellY * (0.9f - _cellScale);
		}

		m_pChannel[_i]->setPositionX(_diffX);
		m_pChannel[_i]->setPositionY(_cellY - _diffY);
	}
}

void LobbyTournamentBottomPannel::SetCenterCell()
{
	if (m_catchCenterIndex == -1 || m_catchCenterIndex >= TOURNAMENT_CELL_MAX)
		return;

	Button* _btn = m_pChannel[m_catchCenterIndex]->m_btnChannel;

	string _frameName1 = "";
	string _frameName2 = "";

	switch (GameDataManager::getSingletonPtr()->getGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		_frameName1 = "seven_";
		_frameName2 = "seven_";
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		_frameName1 = "highlow_";
		_frameName2 = "highlow_";
		break;
	case GameKind::GAMEKIND_BADUKI:
		_frameName1 = "badugi_";
		_frameName2 = "badugi_";
		break;
	case GameKind::GAMEKIND_HOLDEM:
		_frameName1 = "texas_";
		_frameName2 = "texas_";
		break;
	}

	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	W_TourInfo _tourInfo = _pInfoData->tourinfo(m_catchCenterIndex);

	if (_btn->isEnabled() && _tourInfo.isopen())
	{
		_frameName1 += "change";
		_frameName2 += "center";		
	}
	else
	{
		_frameName1 += "stayoff";
		_frameName2 += "changeoff";		
	}

	/*_btn->getButtonSkelObject()->playAnimation(_frameName1);
	_btn->getButtonSkelObject()->appendAnimation(_frameName2, _btn->isEnabled() && _tourInfo.isopen());*/

	//getSkel("skel_light")->setVisible(true);

	m_pChannel[m_catchCenterIndex]->m_labelTitle->setVisible(false);
	m_pChannel[m_catchCenterIndex]->m_labelTicket->setVisible(false);
	m_pChannel[m_catchCenterIndex]->m_labelTicketSum->setVisible(false);
	m_pChannel[m_catchCenterIndex]->m_labelGift1->setVisible(false);
	m_pChannel[m_catchCenterIndex]->m_labelGift2->setVisible(false);
	m_pChannel[m_catchCenterIndex]->m_labelGift->setVisible(false);
	CCLOG("SetCenterCell vfalse -> idex = %d", m_catchCenterIndex);
	m_pChannel[m_catchCenterIndex]->getSkel("skel_lock")->setVisible(false);

	UpdateCenterCell();
	m_pCenterPanel->setVisible(true);
}

void LobbyTournamentBottomPannel::ReleseCenterCell()
{
	if (m_catchCenterIndex == -1 || m_catchCenterIndex >= TOURNAMENT_CELL_MAX)
		return;

	Button* _btn = m_pChannel[m_catchCenterIndex]->m_btnChannel;

	string _frameName1 = "";

	switch (GameDataManager::getSingletonPtr()->getGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		_frameName1 = "seven_";
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		_frameName1 = "highlow_";
		break;
	case GameKind::GAMEKIND_BADUKI:
		_frameName1 = "badugi_";
		break;
	case GameKind::GAMEKIND_HOLDEM:
		_frameName1 = "texas_";
		break;
	}

	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	W_TourInfo _tourInfo = _pInfoData->tourinfo(m_catchCenterIndex);

	if (_btn->isEnabled() && _tourInfo.isopen())
	{
		_frameName1 += "stay";
	}
	else
	{
		_frameName1 += "stayoff";
	}

	/*_btn->getButtonSkelObject()->playAnimation(_frameName1, true);*/
	//getSkel("skel_light")->setVisible(false);

	m_pChannel[m_catchCenterIndex]->m_labelTitle->setVisible(true);
	m_pChannel[m_catchCenterIndex]->m_labelTicket->setVisible(true);
	m_pChannel[m_catchCenterIndex]->m_labelTicketSum->setVisible(true);
	m_pChannel[m_catchCenterIndex]->m_labelGift1->setVisible(true);
	m_pChannel[m_catchCenterIndex]->m_labelGift2->setVisible(true);
	m_pChannel[m_catchCenterIndex]->m_labelGift->setVisible(true);
	if (m_pChannel[m_catchCenterIndex]->m_btnChannel->isEnabled() == false)
	{
		CCLOG("ReleseCenterCell true -> idx = %d", m_catchCenterIndex);
		m_pChannel[m_catchCenterIndex]->getSkel("skel_lock")->setVisible(true);
	}
	else {
		m_pChannel[m_catchCenterIndex]->getSkel("skel_lock")->setVisible(false);
	}

	m_pCenterPanel->getButton("sbtn_button_enter")->setEnable(false);

	m_pCenterPanel->setVisible(false);
}

void LobbyTournamentBottomPannel::UpdateCenterCell()
{
	//W_ChannelInfo* _pInfo = getChannelInfo(m_catchCenterIndex);
	//if (_pInfo == nullptr)
	//	return;

	int _index = m_catchCenterIndex + m_curChannelIndex;

	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;

	if (_pInfoData == nullptr)
		return;

	W_TourInfo _tourInfo = _pInfoData->tourinfo(_index);
	W_TourStepInfo _stepInfo = _tourInfo.stepinfo(0);

	W_TourInfo_W_TourWinner _tWinnerInfo = _tourInfo.twinner();
	W_TourInfo_W_TourCharge _tChargeInfo = _tourInfo.tcharge();

	W_ChannelInfo _Info = _stepInfo.channelinfo();

	//string _roundTxt = GameStringDepot::getSingletonPtr()->getString("TXT_ROUND_LABEL") + StringConverter::toString(_tourInfo.roundcnt());
	string _roundTxt = StringConverter::toString(_tourInfo.roundcnt()) + " ROUND";
	int _haveticketCount = GameDataManager::getSingletonPtr()->getTicketCount(_tourInfo.ticketid());
	string _ticketCount = StringConverter::toString(_haveticketCount);
	string _fameCount = StringConverter::toString(_tWinnerInfo.repute());
	string _winMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_tWinnerInfo.money()), 1);

	m_pCenterPanel->getLabel("txt_round_sum")->setString(_roundTxt.c_str());
	m_pCenterPanel->getLabel("txt_ticket_sum")->setString(_ticketCount.c_str());
	m_pCenterPanel->getLabel("txt_fame_sum")->setString(_fameCount.c_str());
	m_pCenterPanel->getLabel("txt_gold1_sum")->setString(_winMoney.c_str());
	m_pCenterPanel->getLabel("txt_daysum")->setString(_pInfoData->title().c_str());
	m_pCenterPanel->getLabel("txt_tournament_title")->setString(_tourInfo.name().c_str());

	string _frameName = "";
	string _btnName = "";
	//ccColor3B _titleColor;
	//ccColor3B _descColor;
	switch (GameDataManager::getSingletonPtr()->getGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		_frameName = "lock_saven";
		_btnName = "button_seven";
		//_titleColor = ccc3(255, 241, 233);
		//_descColor = ccc3(235, 122, 122);
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		_frameName = "lock_highlow";
		_btnName = "button_highlow";
		//_titleColor = ccc3(233, 246, 255);
		//_descColor = ccc3(111, 151, 224);
		break;
	case GameKind::GAMEKIND_BADUKI:
		_frameName = "lock_badugi";
		_btnName = "button_badugi";
		//_titleColor = ccc3(243, 255, 233);
		//_descColor = ccc3(128, 228, 114);
		break;
	case GameKind::GAMEKIND_HOLDEM:
		_frameName = "lock_texas";
		_btnName = "button_texas";
		//_titleColor = ccc3(233, 255, 255);
		//_descColor = ccc3(105, 228, 212);
		break;
	}
	string titleColor = "";
	string periodColor = "";
	string roundColor = "";
	string rewardColor = "";
	string sumColor = "";
	if (m_pChannel[m_catchCenterIndex]->m_btnChannel->isEnabled())
	{
		m_pCenterPanel->getSkel("skel_lock")->setVisible(false);
		m_pCenterPanel->getButton("sbtn_button_enter")->getButtonSkelObject()->playAnimation(_btnName.c_str());
		m_pCenterPanel->getButton("sbtn_button_enter")->setType(Button::Normal);
		m_pCenterPanel->getButton("sbtn_button_enter")->setEnable(true);
		titleColor = "FFF7FF";
		periodColor = "E17BBF";
		roundColor = "F694D5";
		rewardColor = "FFFFFF";
		sumColor = "FFFFFF";
	}
	else
	{
		m_pCenterPanel->getSkel("skel_lock")->playAnimation(_frameName);
		m_pCenterPanel->getSkel("skel_lock")->setVisible(true);

		m_pCenterPanel->getButton("sbtn_button_enter")->getButtonSkelObject()->playAnimation("button_off");
		m_pCenterPanel->getButton("sbtn_button_enter")->setType(Button::NoPressImg);
		m_pCenterPanel->getButton("sbtn_button_enter")->setEnable(false);
		titleColor = "94758c";
		periodColor = "7a426a";
		roundColor = "7c4068";
		rewardColor = "8b859c";
		sumColor = "827a9c"; 
	}

	//채널 제목
	m_pCenterPanel->getLabel("txt_tournament_title")->setColor(StringConverter::parseColor3B(titleColor));
	m_pCenterPanel->getLabel("txt_daysum")->setColor(StringConverter::parseColor3B(periodColor));
	m_pCenterPanel->getLabel("txt_round_sum")->setColor(StringConverter::parseColor3B(roundColor));

	m_pCenterPanel->getLabel("txt_gift")->setColor(StringConverter::parseColor3B(rewardColor));
	m_pCenterPanel->getLabel("txt_myticket")->setColor(StringConverter::parseColor3B(rewardColor));
	m_pCenterPanel->getLabel("txt_ticket_sum")->setColor(StringConverter::parseColor3B(sumColor));
	m_pCenterPanel->getLabel("txt_fame_sum")->setColor(StringConverter::parseColor3B(sumColor));
	m_pCenterPanel->getLabel("txt_gold1_sum")->setColor(StringConverter::parseColor3B(sumColor));
	
	
	//시드니는 저급 , 파리 중급 마키오 고급	
	//m_pCenterPanel->getSkel("skel_myticket")->playAnimation(PokerResourceHelper::getTicketSmallIconStr(_tourInfo.ticketid()));
}

void LobbyTournamentBottomPannel::InitChannelList()
{
	if (GameDataManager::getSingletonPtr()->m_TourOfInfo == nullptr)
		return;
	
	m_totalChannelCount = GameDataManager::getSingletonPtr()->m_TourOfInfo->tourinfo_size();

	CCSize _contentSize = getDummy("dmy_scroll_size").size;
	_contentSize.height = _contentSize.height + 140.f;
	string _frameName = "";
	if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_7POKER)
	{
		_frameName = "tone_seven";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HIGH_LOW)
	{
		_frameName = "tone_highlow";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_BADUKI)
	{
		_frameName = "tone_badugi";
	}
	else if (GameDataManager::getSingletonPtr()->getGameKind() == GameKind::GAMEKIND_HOLDEM)
	{
		_frameName = "tone_texas";
	}

	getSkel("skel_uitone")->playAnimation(_frameName.c_str());

	m_curChannelIndex = 0;

	ReleaseChannelList();

	m_pChannelContainer = CCLayer::create();
	if ((m_totalChannelCount * TOURNAMENT_CELL_WIDTH) + (TOURNAMENT_CELL_INIT_X * 2) > DESIGN_WIDTH)
	{
		if (m_totalChannelCount > TOURNAMENT_CELL_MAX)
		{
			m_pChannelContainer->setContentSize(CCSizeMake((TOURNAMENT_CELL_MAX * TOURNAMENT_CELL_WIDTH) + (TOURNAMENT_CELL_INIT_X * 2), TOURNAMENT_CELL_HIGHT));
		}
		else
		{
			m_pChannelContainer->setContentSize(CCSizeMake((m_totalChannelCount * TOURNAMENT_CELL_WIDTH) + (TOURNAMENT_CELL_INIT_X * 2), TOURNAMENT_CELL_HIGHT));
		}
	}
	else
	{
		m_pChannelContainer->setContentSize(CCSizeMake(DESIGN_WIDTH, TOURNAMENT_CELL_HIGHT));
	}

	for (int _i = 0; _i < TOURNAMENT_CELL_MAX; _i++)
	{
		if (m_totalChannelCount <= _i)
			continue;

		m_pChannel[_i] = new LobbyTournamentCell();
		m_pChannelContainer->addChild(m_pChannel[_i], 1);
		m_pChannel[_i]->setPositionX(TOURNAMENT_CELL_WIDTH * (_i)+TOURNAMENT_CELL_INIT_X);
		m_pChannel[_i]->setPositionY(TOURNAMENT_CELL_HIGHT - DESIGN_HEIGHT);
		m_pChannel[_i]->release();
	}

	UpdateChannelCell();

	m_pChannelView = CCScrollView::create(_contentSize, m_pChannelContainer);
	m_pChannelView->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	m_pChannelView->setBounceable(false);
	m_pChannelView->setContentOffset(ccp(0, 0), false);
	m_pChannelView->setTouchEnabled(false);
	m_pChannelView->setPosition(ccp(0.f, DESIGN_HEIGHT - _contentSize.height));
	addChild(m_pChannelView, 2);	
}

void LobbyTournamentBottomPannel::ReleaseChannelList()
{
	if (m_pChannelContainer)
	{
		m_pChannelContainer->cleanup();
		m_pChannelContainer->removeFromParent();
	}
	m_pChannelContainer = nullptr;

	if (m_pChannelView)
	{
		m_pChannelView->cleanup();
		m_pChannelView->removeFromParent();

	}
	m_pChannelView = nullptr;

	for (int _i = 0; _i < TOURNAMENT_CELL_MAX; _i++)
	{
		m_pChannel[_i] = nullptr;
	}
}

//W_ChannelInfo* LobbyTournamentBottomPannel::getChannelInfo(int _cellIndex)
//{
//	/*int _index = _cellIndex + m_curChannelIndex;
//	if (m_totalChannelCount <= _index)
//	{
//		_index = _index % m_totalChannelCount;
//	}
//
//	if (_index < 0)
//	{
//		_index = m_totalChannelCount + (_index % m_totalChannelCount);
//		if (_index == m_totalChannelCount)
//		{
//			_index = 0;
//		}
//	}
//
//	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
//	W_TourInfo _tourInfo = _pInfoData->tourinfo(_index);
//	W_TourStepInfo _stepInfo = _tourInfo.stepinfo(0);
//	W_ChannelInfo* _pInfo = *(_stepInfo.channelinfo());*/
//
//	if (_cellIndex >= TOURNAMENT_CELL_MAX)
//		return nullptr;
//
//	W_ChannelInfo* _pInfo = m_pChannel[_cellIndex]->m_CellInfo;
//
//	return _pInfo;
//}

float LobbyTournamentBottomPannel::getCellMetrics(float _per)
{
	if (_per <= 0.5f) 
	{ 
		float _value = DESIGN_WIDTH * 0.5f * 4.f * _per * _per;
		return _value - m_pChannelView->getContentOffset().x - TOURNAMENT_CELL_WIDTH * 0.5f;
	}
	else  
	{  
		float _value = DESIGN_WIDTH - (DESIGN_WIDTH * 0.5f * 4.f * (1.f - _per) * (1.f - _per));
		return _value - m_pChannelView->getContentOffset().x - TOURNAMENT_CELL_WIDTH * 0.5f; 
	}
} 

void LobbyTournamentBottomPannel::InitCenterPanel()
{ 
	CCPoint _pos = getDummy("dmy_tournament_center").origin;
	_pos.y = -_pos.y;

	m_pCenterPanel = new Panel();
	m_pCenterPanel->construct(getMxmlPath() + "dmy_tournament_center.mxml");
	m_pCenterPanel->setPosition(_pos);
	addChild(m_pCenterPanel, 10);  
	m_pCenterPanel->release();  

	m_pCenterPanel->getLabel("txt_round_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_gift")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));  
	m_pCenterPanel->getLabel("txt_myticket")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_ticket_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_fame_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_gold1_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_enter_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_enter")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_daysum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_pCenterPanel->getLabel("txt_tournament_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	m_pCenterPanel->getLabel("txt_gift")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_WINNER_GIFT").c_str());
	m_pCenterPanel->getLabel("txt_myticket")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_TICKET_UNIT").c_str());
	m_pCenterPanel->getLabel("txt_enter_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str());
	m_pCenterPanel->getLabel("txt_enter")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str());
	

	m_pCenterPanel->getButton("sbtn_button_enter")->setListener(this);
	m_pCenterPanel->setVisible(false);	
	getImage("skel_prize1")->setScale(0.5f);
	getImage("skel_prize2")->setScale(0.5f);
}
