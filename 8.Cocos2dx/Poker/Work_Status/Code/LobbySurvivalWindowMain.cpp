#include "pch.h"
#include "LobbySurvivalWindowMain.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "Web/WebService.h"
#include "GameStringDepot.h"
#include "LobbyScene.h"

LobbySurvivalWindowMain::LobbySurvivalWindowMain()
{
	m_MatchButton = nullptr;
	m_ReplayButton = nullptr;
	m_OkButton = nullptr;
	m_pTotalRewardGold = nullptr;

	m_SeletctedCellIndex = -1;
	m_pSurvivalListView = nullptr;
	m_pSurvivalListContainer = nullptr;
	for (int _i = 0; _i < SURVIVAL_RANK_CELL_MAX; _i++)
	{
		m_SurvivalInfoCell[_i] = nullptr;
	}

	m_CellIndex = 0;
	m_bMovingCell = false;
	m_fMoveG = 0.f;

	InitPanel();
	InitImage();
	InitButton();

	setButtonListener(this);
}

LobbySurvivalWindowMain::~LobbySurvivalWindowMain()
{
	RemoveRankinfoList();
	RemoveRankView();
}

void LobbySurvivalWindowMain::InitPanel()
{
	construct(getMxmlPath() + "pop_survival_rank.mxml");

	if (m_MatchButton == nullptr)
	{
		m_MatchButton = new Panel();
		m_MatchButton->construct(getMxmlPath() + "dmy_button_big.mxml");
		addChild(m_MatchButton);
		m_MatchButton->release();
		CCPoint _btnPos = getDummy("dmy_button_big").origin;
		m_MatchButton->setPosition(ccp(_btnPos.x, -_btnPos.y));
	}

	if (m_ReplayButton == nullptr)
	{
		m_ReplayButton = new Panel();
		m_ReplayButton->construct(getMxmlPath() + "dmy_button_middle.mxml");
		addChild(m_ReplayButton);
		m_ReplayButton->release();
		CCPoint _btnPos = getDummy("dmy_button_middle").origin;
		m_ReplayButton->setPosition(ccp(_btnPos.x, -_btnPos.y));
	}

	if (m_OkButton == nullptr)
	{
		m_OkButton = new Panel();
		m_OkButton->construct(getMxmlPath() + "dmy_button_middle.mxml");
		addChild(m_OkButton);
		m_OkButton->release();
		CCPoint _btnPos = getDummy("dmy_button_middle").origin;
		m_OkButton->setPosition(ccp(_btnPos.x, -_btnPos.y));
	}
}
void LobbySurvivalWindowMain::InitImage()
{
	//getSkel("skel_backcolor");
	//getSkel("skel_panel");
	//getSkel("skel_table");
	//getSkel("skel_myrank");
	//getSkel("skel_titlelight");
	//getSkel("skel_totalprize");

	getLabel("txt_chip")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_nickname")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_ranking")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//getLabel("txt_gamestate")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//getLabel("txt_title_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_mylank")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_myname")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_mymoney")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_enter")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_enter_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_moneyin")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_moneyin_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_nodata")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	getLabel("txt_nodata")->setVisible(false);
	getLabel("txt_nodata")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_USERINFO_EMPTY").c_str());

	getLabel("txt_chip")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT").c_str());
	getLabel("txt_nickname")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_NICKNAME_LABEL").c_str());
	getLabel("txt_ranking")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_RANK_LABEL").c_str());
	
	getLabel("txt_enter")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GAME_ENTER_LABEL").c_str());
	getLabel("txt_moneyin")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_MONEYIN_LABEL").c_str());
	//getLabel("txt_lefttime")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REGISTER_CLOSE_LABEL").c_str());

	getButton("sbtn_movearrow_r1")->setEnable(false);
	getButton("sbtn_movearrow_r1")->setVisible(false);
	getButton("sbtn_movearrow_l1")->setEnable(false);
	getButton("sbtn_movearrow_l1")->setVisible(false);

	if (m_pTotalRewardGold == nullptr)
	{
		m_pTotalRewardGold = CCLabelBMFont::create("", "fonts/number_gold.fnt");
		m_pTotalRewardGold->retain();
		m_pTotalRewardGold->setAnchorPoint(ccp(0.5f, 1.f));
		CCPoint _goldPos = getDummy("dmy_font_number_gold").origin;
		m_pTotalRewardGold->setPositionX(_goldPos.x);
		m_pTotalRewardGold->setPositionY(DESIGN_HEIGHT - _goldPos.y);
		m_pTotalRewardGold->setScale(1.f);
		addChild(m_pTotalRewardGold);
		m_pTotalRewardGold->release();
	}
	
	if (m_MatchButton)
	{
		m_MatchButton->getSkel("skel_icon_gold2")->setVisible(false);
		m_MatchButton->getLabel("txt_type1_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_MatchButton->getLabel("txt_type1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_MatchButton->getLabel("txt_gold_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_MatchButton->getLabel("txt_gold")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_MatchButton->getLabel("txt_type2_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_MatchButton->getLabel("txt_type2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		//
		m_MatchButton->getLabel("txt_type1_under")->setVisible(false);
		m_MatchButton->getLabel("txt_type1")->setVisible(false);
		//
		m_MatchButton->getLabel("txt_gold_under")->setVisible(false);
		m_MatchButton->getLabel("txt_gold")->setVisible(false);
		m_MatchButton->getLabel("txt_type2_under")->setVisible(false);
		m_MatchButton->getLabel("txt_type2")->setVisible(false);
	}

	if (m_ReplayButton)
	{
		m_ReplayButton->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ReplayButton->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		m_ReplayButton->getLabel("txt_button_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REPLAY_UNIT").c_str());
		m_ReplayButton->getLabel("txt_button")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REPLAY_UNIT").c_str());
	}

	//
	if (m_OkButton)
	{
		m_OkButton->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_OkButton->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		m_OkButton->getLabel("txt_button_under")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HELP_UNIT").c_str());
		m_OkButton->getLabel("txt_button")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_HELP_UNIT").c_str());
	}
}

void LobbySurvivalWindowMain::InitButton()
{
	//getButton("sbtn_movearrow_r1")->setType(Button::NoPressImg);
	//getButton("sbtn_movearrow_l1")->setType(Button::NoPressImg);
	//getButton("sbtn_cancel")->setType(Button::NoPressImg);

	getButton("sbtn_movearrow_r1")->setListener(this);
	getButton("sbtn_movearrow_l1")->setListener(this);
	getButton("sbtn_cancel")->setListener(this);

	if (m_MatchButton)
	{
		//m_MatchButton->getButton("sbtn_buttonwatch")->setType(Button::NoPressImg);
		m_MatchButton->getButton("sbtn_buttonwatch")->setListener(this);
	}
	if (m_ReplayButton)
	{
		m_ReplayButton->getButton("sbtn_button")->setName("sbtn_replay");
		//m_ReplayButton->getButton("sbtn_button")->setType(Button::NoPressImg);
		m_ReplayButton->getButton("sbtn_button")->setListener(this);
	}
	if (m_OkButton)
	{
		m_OkButton->getButton("sbtn_button")->setName("sbtn_help");
		//m_OkButton->getButton("sbtn_button")->setType(Button::NoPressImg);
		m_OkButton->getButton("sbtn_button")->setListener(this);
		m_OkButton->getButton("sbtn_button")->setSkelAnimation("button_middle_ostay");
	}
}

void LobbySurvivalWindowMain::update(float dt)
{
	ScrollViewOffsetProcess(dt);

	W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
	W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(m_SeletctedCellIndex);

	if (_matchInfo.registerabletime() > 0.f) {
		double finalDt = _matchInfo.registerabletime() - dt;
		if (finalDt < 0.f)
			finalDt = 0.f;
		_matchInfo.set_registerabletime(finalDt);
	}
}

void LobbySurvivalWindowMain::onClicked(const string& name)
{
	if (name == "sbtn_cancel")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}


	if (name == "sbtn_buttonwatch")
	{
		W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
		W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(m_SeletctedCellIndex);

		switch (_matchInfo.userstatus())
		{
		case W_DeathMatchInfo_eUserStatus_eRegister:
			if (GameDataManager::getSingletonPtr()->GetSuvivalGameEntertimeLeft() <= 0)
			{
				string _OkMsg = "Update_DeathmatchData";
				string _title = GameStringDepot::getSingletonPtr()->getString("TXT_ERROR_LABEL");
				string _content = GameStringDepot::getSingletonPtr()->getString("TXT_DATAUPDATE_LATE");

				SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, _content, _title);
				if (panel)
				{
					panel->SetOkEventMsg(_OkMsg);
					panel->setListener(WebService::getSingletonPtr());
					LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
				}
				return;
			}
			// 신청 아직 안되었을때 신청하는 버튼
			if (_matchInfo.isregister() == false)
			{
				WebService::getSingletonPtr()->SurvivalMatchRegistReq(_matchInfo.matchid());
			}
			else
			{
				WebService::getSingletonPtr()->SurvivalMatchRegistCancelReq(_matchInfo.matchid());
			}
			break;
		case W_DeathMatchInfo_eUserStatus_eWait:
			if (_matchInfo.isregister() == true)
			{
				ReadyToSurvival(&_matchInfo);
			}
		break;
		case W_DeathMatchInfo_eUserStatus_eGame:
			if (_matchInfo.isregister() == true)
			{
				ReadyToSurvival(&_matchInfo);
			}			
			break;
		}
	}

	if (name == "sbtn_replay")
	{
		W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
		W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(m_SeletctedCellIndex);

		WebService::getSingletonPtr()->SurvivalReplayListReq(_matchInfo.matchid());
	}

	if (name == "sbtn_help")
	{
		
	}
}

bool LobbySurvivalWindowMain::handling(STCMD &stCmd)
{
	return false;
}


bool LobbySurvivalWindowMain::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_bMovingCell = false;
	m_fMoveG = 0.f;

	CCPoint _pos = convertToNodeSpace(pTouch->getLocation());

	float _maxHight = DESIGN_HEIGHT - 130;
	float _minHight = 62;
	if (_maxHight < _pos.y || _minHight > _pos.y)
		return false;

	m_bTouchCancel = false;

	return true;
}
void LobbySurvivalWindowMain::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	Panel::ccTouchMoved(pTouch, pEvent);

	CCPoint _startTouch = pTouch->getStartLocationInView();
	CCPoint _moveTouch = pTouch->getLocationInView();

	float _defPos = abs(_startTouch.y - _moveTouch.y);

	if (_defPos > 10.f && m_bTouchCancel == false)
	{
		m_bTouchCancel = true;
	}

	if (m_pSurvivalListView == nullptr)
		return;

	CCPoint _offSetPoint = m_pSurvivalListView->getContentOffset();
	int _size = m_RankerInfoList.size();
	int _moveV = pTouch->getPreviousLocation().y - pTouch->getLocation().y;
	m_fMoveG = _moveV;
	if (_moveV > 0)
	{
		if (m_fMoveG > SURVIVAL_RANK_CELL_HIGHT)
		{
			m_fMoveG = SURVIVAL_RANK_CELL_HIGHT;
		}
	}
	else if (_moveV < 0)
	{
		if (m_fMoveG < -SURVIVAL_RANK_CELL_HIGHT)
		{
			m_fMoveG = -SURVIVAL_RANK_CELL_HIGHT;
		}
	}


	if (_size <= SURVIVAL_RANK_CELL_MAX)
	{
		m_pSurvivalListView->setContentOffset(_offSetPoint - ccp(0, _moveV));
		return;
	}

	//float _contentheight = getDummy("dmy_tab1_scrollsize_1").size.height;

	bool _bMove = false;
	if (_moveV > 0)
	{
		float _maxMove = -SURVIVAL_RANK_CELL_HIGHT * 1.5f;
		if (_offSetPoint.y <= _maxMove)
		{
			if (m_CellIndex > 0)
			{
				m_CellIndex--;
				m_pSurvivalListView->setContentOffset(_offSetPoint + ccp(0, SURVIVAL_RANK_CELL_HIGHT));
				for (int _i = 0; _i < SURVIVAL_RANK_CELL_MAX; _i++)
				{
					UpdateCell(_i, _size - SURVIVAL_RANK_CELL_MAX - m_CellIndex + _i);
				}
				_bMove = true;
			}
		}
	}
	else if (_moveV < 0)
	{
		float _minMove = -SURVIVAL_RANK_CELL_HIGHT;
		if (_offSetPoint.y >= _minMove)
		{
			if (m_CellIndex + SURVIVAL_RANK_CELL_MAX < _size)
			{
				m_CellIndex++;
				m_pSurvivalListView->setContentOffset(_offSetPoint - ccp(0, SURVIVAL_RANK_CELL_HIGHT));
				for (int _i = 0; _i < SURVIVAL_RANK_CELL_MAX; _i++)
				{
					UpdateCell(_i, _size - SURVIVAL_RANK_CELL_MAX - m_CellIndex + _i);
				}
				_bMove = true;
			}
		}
	}

	if (_bMove == false)
	{
		m_pSurvivalListView->setContentOffset(_offSetPoint - ccp(0, _moveV));
	}
}

void LobbySurvivalWindowMain::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	Panel::ccTouchEnded(pTouch, pEvent);

	if (m_bTouchCancel == true)
	{
		m_bMovingCell = true;
		return;
	}
	m_fMoveG = 0.f;
}

void LobbySurvivalWindowMain::RemoveRankinfoList()
{
	for (W_DeathMatchInfo_W_DeathMatchRankInfo* _pInfo : m_RankerInfoList)
	{
		if (_pInfo) delete _pInfo;
		_pInfo = nullptr;
	}
	m_RankerInfoList.clear();
	m_SeletctedCellIndex = -1;
}

void LobbySurvivalWindowMain::RemoveRankView()
{
	if (m_pSurvivalListContainer)
	{
		m_pSurvivalListContainer->removeFromParentAndCleanup(true);
	}
	m_pSurvivalListContainer = nullptr;

	if (m_pSurvivalListView)
	{
		m_pSurvivalListView->removeFromParentAndCleanup(true);
	}
	m_pSurvivalListView = nullptr;


	for (int _i = 0; _i < SURVIVAL_RANK_CELL_MAX; _i++)
	{
		m_SurvivalInfoCell[_i] = nullptr;
	}
}

Panel* LobbySurvivalWindowMain::CreateSurvivalInfoPanel()
{
	Panel* _infoPanel = new Panel();
	_infoPanel->construct(getMxmlPath() + "dmy_surank_slot.mxml");

	//_infoPanel->getSkel("skel_line");
	_infoPanel->getSkel("skel_surank_slot"); // 2022.01.20 수정
	_infoPanel->getLabel("txt_rank1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	_infoPanel->getLabel("txt_name1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	_infoPanel->getLabel("txt_money1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	return _infoPanel;
}


void LobbySurvivalWindowMain::CreateCell()
{
	if (GameDataManager::getSingletonPtr()->m_SurvivalOfInfo == nullptr)
		return;

	RemoveRankinfoList();
	RemoveRankView();

	m_CellIndex = 0;

	CCSize _contentSize = getDummy("dmy_scrollsize").size;

	W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
	int _matchCount = _pInfo->matchinfo_size();
	for (int _i = 0; _i < _matchCount; _i++)
	{
		W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(_i);
		
		if (_matchInfo.matchid() == GameDataManager::getSingletonPtr()->m_TournamentId)
		{
			m_SeletctedCellIndex = _i;
			int _count = _matchInfo.rankinfo_size();
			
			for (int _index = _count - 1; _index >= 0; _index--)
			{
				m_RankerInfoList.push_back(new W_DeathMatchInfo_W_DeathMatchRankInfo(_matchInfo.rankinfo(_index)));
			}

			int _MakeCellSize = _count;
			if (_MakeCellSize > SURVIVAL_RANK_CELL_MAX)
				_MakeCellSize = SURVIVAL_RANK_CELL_MAX;

			m_pSurvivalListContainer = CCLayer::create();

			for (int _i = 0; _i < _MakeCellSize; _i++)
			{
				m_SurvivalInfoCell[_i] = CreateSurvivalInfoPanel();
				m_SurvivalInfoCell[_i]->setPosition(ccp(1.f, SURVIVAL_RANK_CELL_HIGHT - DESIGN_HEIGHT + (SURVIVAL_RANK_CELL_HIGHT * _i)));
				m_pSurvivalListContainer->addChild(m_SurvivalInfoCell[_i]);
				m_SurvivalInfoCell[_i]->release();
			}

			for (int _index = 0; _index < SURVIVAL_RANK_CELL_MAX; _index++)
			{
				// 2022.01.20 수정
				UpdateCell(_index, _count - _index - 1);
				//UpdateCell(_index, _count - SURVIVAL_RANK_CELL_MAX - m_CellIndex + _index);
			}

			if (_MakeCellSize > 0)
			{
				m_pSurvivalListContainer->setContentSize(CCSizeMake(_contentSize.width, SURVIVAL_RANK_CELL_HIGHT * _MakeCellSize));
			}
			else
			{
				m_pSurvivalListContainer->setContentSize(_contentSize);
			}

			m_pSurvivalListView = CCScrollView::create(_contentSize, m_pSurvivalListContainer);
			m_pSurvivalListView->setDirection(extension::ScrollView::Direction::VERTICAL);
			m_pSurvivalListView->setBounceable(false);
			//가장 상단으로 올리기.
			m_pSurvivalListView->setContentOffset(ccp(0, -(SURVIVAL_RANK_CELL_HIGHT * SURVIVAL_RANK_CELL_MAX)), false);

			CCPoint _ListPos = getDummy("dmy_scrollsize").origin;
			m_pSurvivalListView->setPosition(ccp(_ListPos.x, DESIGN_HEIGHT - _ListPos.y - _contentSize.height));
			addChild(m_pSurvivalListView);
			
			return;
		}
	}

	
}

void LobbySurvivalWindowMain::UpdateCell(int _to, int _dst)
{
	W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
	W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(m_SeletctedCellIndex);

	if (m_SurvivalInfoCell[_to] == nullptr)
	{
		return;
	}

	if (m_RankerInfoList[_dst]->rank() > 0)
	{
		if (m_RankerInfoList[_dst]->rank() == 10000000)
			m_SurvivalInfoCell[_to]->getLabel("txt_rank1")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GIVEUP").c_str());
		else
			m_SurvivalInfoCell[_to]->getLabel("txt_rank1")->setString(StringConverter::toString(m_RankerInfoList[_dst]->rank()).c_str());
	}
	else
		m_SurvivalInfoCell[_to]->getLabel("txt_rank1")->setString("");
	m_SurvivalInfoCell[_to]->getLabel("txt_name1")->setString(m_RankerInfoList[_dst]->name().c_str());
	m_SurvivalInfoCell[_to]->getLabel("txt_money1")->setString(m_RankerInfoList[_dst]->desc().c_str());
}

void LobbySurvivalWindowMain::ScrollViewOffsetProcess(float _dt)
{
	if (m_bMovingCell == false)
		return;

	if (m_pSurvivalListView == nullptr)
		return;

	CCPoint _offSetPoint = m_pSurvivalListView->getContentOffset();
	int _size = m_RankerInfoList.size();

	if (m_fMoveG < 0)
	{
		m_fMoveG += SURVIVAL_RANK_CELL_HIGHT * 0.5f * _dt;

		if (m_fMoveG > -5.f)
		{
			m_bMovingCell = false;
			m_fMoveG = 0.f;
			return;
		}

		float _minMove = -SURVIVAL_RANK_CELL_HIGHT;
		if (_offSetPoint.y >= _minMove && m_CellIndex + SURVIVAL_RANK_CELL_MAX < _size)
		{
			m_CellIndex++;
			m_pSurvivalListView->setContentOffset(_offSetPoint - ccp(0, SURVIVAL_RANK_CELL_HIGHT - m_fMoveG));
			for (int _i = 0; _i < SURVIVAL_RANK_CELL_MAX; _i++)
			{
				UpdateCell(_i, _size - SURVIVAL_RANK_CELL_MAX - m_CellIndex + _i);
			}
		}
		else
			m_pSurvivalListView->setContentOffset(_offSetPoint - ccp(0, m_fMoveG));
	}
	else
	{
		m_fMoveG -= SURVIVAL_RANK_CELL_HIGHT * 0.5f * _dt;

		if (m_fMoveG < 5.f)
		{
			m_bMovingCell = false;
			m_fMoveG = 0.f;
			return;
		}

		float _maxMove = -SURVIVAL_RANK_CELL_HIGHT * 1.5f;
		if (_offSetPoint.y <= _maxMove && m_CellIndex > 0)
		{
			m_CellIndex--;
			m_pSurvivalListView->setContentOffset(_offSetPoint + ccp(0, SURVIVAL_RANK_CELL_HIGHT - m_fMoveG));
			for (int _i = 0; _i < SURVIVAL_RANK_CELL_MAX; _i++)
			{
				UpdateCell(_i, _size - SURVIVAL_RANK_CELL_MAX - m_CellIndex + _i);
			}
		}
		else
			m_pSurvivalListView->setContentOffset(_offSetPoint - ccp(0, m_fMoveG));
	}
}


void LobbySurvivalWindowMain::SetResistTxt(int64 _money, bool _enable)
{
	//
	m_MatchButton->getLabel("txt_type1_under")->setVisible(false);
	m_MatchButton->getLabel("txt_type1")->setVisible(false);
	//
	m_MatchButton->getLabel("txt_gold_under")->setVisible(true);
	m_MatchButton->getLabel("txt_gold")->setVisible(true);
	m_MatchButton->getLabel("txt_type2_under")->setVisible(true);
	m_MatchButton->getLabel("txt_type2")->setVisible(true);

	string _goldText = "";
	if (_money == 0)
	{
		_goldText = GameStringDepot::getSingletonPtr()->getString("TXT_FREE_UNIT");
	}
	else{
		_goldText = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_money), 1);
		_goldText += GameStringDepot::getSingletonPtr()->getString("TXT_GOLD_UNIT");
	}
	m_MatchButton->getLabel("txt_gold_under")->setString(_goldText.c_str());
	m_MatchButton->getLabel("txt_gold")->setString(_goldText.c_str());

	string _text = GameStringDepot::getSingletonPtr()->getString("TXT_REGISTATION_LABEL");
	m_MatchButton->getLabel("txt_type2")->setString(_text.c_str());
	m_MatchButton->getLabel("txt_type2_under")->setString(_text.c_str());

	ccColor3B _color;
	if (_enable)
	{
		_color.r = 255;
		_color.g = 216;
		_color.b = 133;

		m_MatchButton->getButton("sbtn_buttonwatch")->getButtonSkelObject()->playAnimation("button_big_stay");
	}
	else
	{
		_color.r = 133;
		_color.g = 133;
		_color.b = 133;
		m_MatchButton->getButton("sbtn_buttonwatch")->getButtonSkelObject()->playAnimation("button_big_off");
	}

	m_MatchButton->getLabel("txt_gold")->setColor(_color);
	m_MatchButton->getLabel("txt_type2")->setColor(_color);
	
}

void LobbySurvivalWindowMain::SetResistEndTxt(std::string _txt, SURVIVAL_BUTTON_KIND btnKind)
{
	//
	m_MatchButton->getLabel("txt_type1_under")->setVisible(true);
	m_MatchButton->getLabel("txt_type1")->setVisible(true);
	m_MatchButton->getLabel("txt_type1_under")->setString(_txt.c_str());
	m_MatchButton->getLabel("txt_type1")->setString(_txt.c_str());

	//
	m_MatchButton->getLabel("txt_gold_under")->setVisible(false);
	m_MatchButton->getLabel("txt_gold")->setVisible(false);
	m_MatchButton->getLabel("txt_type2_under")->setVisible(false);
	m_MatchButton->getLabel("txt_type2")->setVisible(false);

	ccColor3B _color;

	switch (btnKind)
	{
	case DISABLE:
		_color.r = 133;
		_color.g = 133;
		_color.b = 133;
		m_MatchButton->getButton("sbtn_buttonwatch")->setSkelAnimation("button_big_off");
		m_MatchButton->getButton("sbtn_buttonwatch")->setEnable(false);
		break;
	case ENABLE:
		_color.r = 255;
		_color.g = 216;
		_color.b = 133;
		m_MatchButton->getButton("sbtn_buttonwatch")->setSkelAnimation("button_big_stay");
		m_MatchButton->getButton("sbtn_buttonwatch")->setEnable(true);
		break;
	case HIGHLIGHT1:
		_color.r = 255;
		_color.g = 240;
		_color.b = 159;
		m_MatchButton->getButton("sbtn_buttonwatch")->setSkelAnimation("button_big_ystay");
		m_MatchButton->getButton("sbtn_buttonwatch")->setEnable(true);
		break;
	case HIGHLIGHT2:
		_color.r = 255;
		_color.g = 235;
		_color.b = 221;
		m_MatchButton->getButton("sbtn_buttonwatch")->setSkelAnimation("button_big_rstay");
		m_MatchButton->getButton("sbtn_buttonwatch")->setEnable(true);
		break;
	}

	m_MatchButton->getLabel("txt_type1")->setColor(_color);
}

void LobbySurvivalWindowMain::SetTotalRewardGold(int64 _gold)
{
	if (m_pTotalRewardGold == nullptr)
		return;

	string _text = StringConverter::toString(_gold);

	int _len = _text.length();

	int _pointCount = _len / 3;

	for (int _i = 1; _i <= _pointCount; _i++)
	{
		if (_len - (_i * 3) == 0)
			continue;

		_text.insert(_len - (_i * 3), ",");
	}
		
	m_pTotalRewardGold->setString(_text.c_str());
}

void LobbySurvivalWindowMain::ApplyData()
{
	CreateCell();

	W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
	W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(m_SeletctedCellIndex);

	// int64 _totalMoney = _matchInfo.joinmoney() * _matchInfo.registermax();
	int64 _totalMoney = _matchInfo.joinmoney() * _matchInfo.registercnt();

	//여기서 ApplyData를 한번만 해준다고라?
	GameDataManager::getSingletonPtr()->SetSelectedLeftGameTime(_matchInfo.gameabletime());
	GameDataManager::getSingletonPtr()->SetSelectedGameEnterTime(_matchInfo.waitabletime());
	
	ApplyGameTitle();
	SetTotalRewardGold(_totalMoney);
	ApplyBtnSetting();
	ApplyMyInfo();
	ApplyGameInfo();
}


void LobbySurvivalWindowMain::ApplyMyInfo()
{
	W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
	W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(m_SeletctedCellIndex);

	if (_matchInfo.has_myinfo())
	{
		W_DeathMatchInfo_W_DeathMatchRankInfo _myinfo = _matchInfo.myinfo();
		if (_myinfo.rank() > 0)
		{
			if (_matchInfo.matchstatus() == W_DeathMatchInfo_eMatchStatus_eGameEnd && _myinfo.rank() == 100000)
				getLabel("txt_mylank")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GIVEUP").c_str());
			else
				getLabel("txt_mylank")->setString(StringConverter::toString(_myinfo.rank()).c_str());
		}
		else
			getLabel("txt_mylank")->setString("");

		getLabel("txt_myname")->setString(_myinfo.name().c_str());
		getLabel("txt_mymoney")->setString(_myinfo.desc().c_str());
		getLabel("txt_nodata")->setVisible(false);
	}
	else
	{
		getLabel("txt_mylank")->setString("");
		getLabel("txt_myname")->setString("");
		getLabel("txt_mymoney")->setString("");
		getLabel("txt_nodata")->setVisible(true);
	}
	
}

void LobbySurvivalWindowMain::ApplyGameInfo()
{
	W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
	W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(m_SeletctedCellIndex);

	string _enterCount = StringConverter::toString(_matchInfo.registercnt()) + "/" + StringConverter::toString(_matchInfo.registermax());
	string _moneyinMax = StringConverter::toString(_matchInfo.moneyincnt()) + GameStringDepot::getSingletonPtr()->getString("TXT_PEOPLE_COUNT");
	getLabel("txt_enter_sum")->setString(_enterCount.c_str());
	getLabel("txt_moneyin_sum")->setString(_moneyinMax.c_str());
	//getLabel("txt_lefttime_sum")->setString(_moneyinMax.c_str());

	//string _leftTimeText = "[" + StringConverter::toString(_matchInfo.registerabletime) + GameStringDepot::getSingletonPtr()->getString("TXT_SECOND") + "] ";
	//_leftTimeText += GameStringDepot::getSingletonPtr()->getString("TXT_UNTIL_GAME_START_LABEL");

	//string timeFormatStr = PokerResourceHelper::getPeroidDesc(tourOfInfo->endlefttime());
	//string tourTimeStr = NxGetFormatString(GameStringDepot::getSingleton().getString("REMAIN_PERIOD"), timeFormatStr);
	//mSeasonLeftLabel->setString(tourTimeStr.c_str());
}

void LobbySurvivalWindowMain::ApplyBtnSetting()
{
	W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
	W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(m_SeletctedCellIndex);

	if (_matchInfo.matchstatus() == W_DeathMatchInfo_eMatchStatus_eGameEnd)
	{
		getLabel("txt_chip")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GET_WIN_MONEY").c_str());
		
		m_ReplayButton->getButton("sbtn_button")->setEnable(true);
		m_ReplayButton->getButton("sbtn_button")->getButtonSkelObject()->playAnimation("button_middle_ystay");


		ccColor3B _color;
		_color.r = 255;
		_color.g = 240;
		_color.b = 159;

		m_ReplayButton->getLabel("txt_button")->setColor(_color);
	}
	else
	{
		if (_matchInfo.matchstatus() == W_DeathMatchInfo_eMatchStatus_eGameIng)
		{
			getLabel("txt_chip")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GAMEGOLD_LABEL").c_str());
		}
		else
		{
			getLabel("txt_chip")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_ENTERTIME_LABEL").c_str());
		}


		m_ReplayButton->getButton("sbtn_button")->getButtonSkelObject()->playAnimation("button_middle_off");
		m_ReplayButton->getButton("sbtn_button")->setEnable(false);
		ccColor3B _color;
		_color.r = 133;
		_color.g = 133;
		_color.b = 133;
		m_ReplayButton->getLabel("txt_button")->setColor(_color);
	}

	m_MatchButton->getSkel("skel_icon_gold2")->setVisible(false);

	W_DeathMatchInfo::eMatchStatus _status = _matchInfo.matchstatus();
	
	string upperStr = "";
	switch (_status)
	{
	case W_DeathMatchInfo_eMatchStatus_eGameEnd:
		upperStr = _matchInfo.desc() + "(" + GameStringDepot::getSingletonPtr()->getString("TXT_GAME_END_LABEL") + ")";
		//getLabel("txt_gamestate")->setString(upperStr.c_str());
		break;
	case W_DeathMatchInfo_eMatchStatus_eGameIng:
		upperStr = GameStringDepot::getSingletonPtr()->getString("TXT_DURING_LABEL");
		if (_matchInfo.isregister())
			upperStr += " (" + GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_JOIN") + ")";
		else
			upperStr += " (" + GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_NOT_JOIN") + ")";
		//getLabel("txt_gamestate")->setString(upperStr.c_str());
		break;
		
	default:
		upperStr = _matchInfo.desc() + " " + GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_START") + "";
		//getLabel("txt_gamestate")->setString(upperStr.c_str());
		break;
	}


	// 등록 기간중일때
	if (_matchInfo.isregistertime())
	{
		// 참여한적 없을때
		if (_matchInfo.isregister() == false)
		{
			SetResistTxt(_matchInfo.joinmoney());
			m_MatchButton->getSkel("skel_icon_gold2")->setVisible(true);
		}
		// 참여했을 때
		else
		{
			SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_SURVIVAL_JOIN_CANCEL").c_str(), ENABLE);
		}
	}
	// 대기중일때
	else if (_matchInfo.matchstatus() == W_DeathMatchInfo_eMatchStatus_eGameWait)
	{
		// 참여한적 없을때
		if (_matchInfo.isregister() == false)
		{
			SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_RESIST_OVER").c_str(), DISABLE);
		}
		// 참여했을때
		else
		{
			SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str(),  HIGHLIGHT2);
		}
	}
	// 게임 중일때
	else if (_matchInfo.matchstatus() == W_DeathMatchInfo_eMatchStatus_eGameIng)
	{
		// 참여한적 없을때
		if (_matchInfo.isregister() == false)
		{
			SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_DURING_LABEL").c_str(), DISABLE);
		}
		// 참여했을 때
		else
		{
			// 아직 개인이 게임중일때
			if (_matchInfo.userstatus() == W_DeathMatchInfo_eUserStatus_eGame)
				SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str(), HIGHLIGHT2);
			// 내 게임은 끝났을 때
			else
				SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_DURING_LABEL").c_str(), DISABLE);
		}

	}
	else   // 이건 뭐에대한 상태야?
	{
		// 게임 끝났으면 상세보기
		if (_matchInfo.matchstatus() == W_DeathMatchInfo_eMatchStatus_eGameEnd)
		{
			SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_GAME_END_LABEL").c_str(), DISABLE);
		}
		// 디스플레이 타임 (등록 시간은 남아 잇으나, 등록시간이 안되었을때
		else if (_matchInfo.registerabletime() > 0)
		{
			SetResistTxt(_matchInfo.joinmoney());
			m_MatchButton->getSkel("skel_icon_gold2")->setVisible(false);
		}
		// 웨이트 타임 전이면서 등록은 완료되었을 때 
		else if (_matchInfo.waitabletime() > 0)
		{
			if (_matchInfo.isregister() == false)
				SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_RESIST_OVER").c_str(), DISABLE);
			else
				SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str(), DISABLE);
		}
		// 게임 진행전이면서 대기 상태인경우
		else if (_matchInfo.gameabletime() > 0)
		{
			if (_matchInfo.isregister() == false)
				SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_DURING_LABEL").c_str(), DISABLE);
			else
				SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_WAITTING_LABEL").c_str(), HIGHLIGHT2);
		}
		// 그외 모두
		else
			SetResistEndTxt(GameStringDepot::getSingletonPtr()->getString("TXT_GAME_END_LABEL").c_str(), DISABLE);
	}


	
}

void LobbySurvivalWindowMain::ApplyGameTitle()
{
	W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
	W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(m_SeletctedCellIndex);

	//getLabel("txt_title_under")->setString(_matchInfo.name().c_str());
	getLabel("txt_title")->setString(_matchInfo.name().c_str());

	if (_matchInfo.gamekind() == GAMEKIND_7POKER)
	{
		getSkel("skel_panel")->playAnimation("panel_suresult_s", true);
		getSkel("skel_titlelight")->playAnimation("titlelight_seven", true);
	}
	else if (_matchInfo.gamekind() == GAMEKIND_HIGH_LOW)
	{
		getSkel("skel_panel")->playAnimation("panel_suresult_h", true);
		getSkel("skel_titlelight")->playAnimation("titlelight_highlow", true);
	}
	else if (_matchInfo.gamekind() == GAMEKIND_BADUKI)
	{
		getSkel("skel_panel")->playAnimation("panel_suresult_b", true);
		getSkel("skel_titlelight")->playAnimation("titlelight_badugi", true);
	}
	else if (_matchInfo.gamekind() == GAMEKIND_HOLDEM)
	{
		getSkel("skel_panel")->playAnimation("panel_suresult_t", true);
		getSkel("skel_titlelight")->playAnimation("titlelight_texas", true);
	}
}

void LobbySurvivalWindowMain::ReadyToSurvival(W_DeathMatchInfo *_matchInfo)
{
	if (_matchInfo->isregister() == false)
		return;

	W_ChannelInfo _ChannelInfo = _matchInfo->channelinfo();
	GameDataManager::getSingleton().setGameKind(_ChannelInfo.gamekind());
	GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney1 = _ChannelInfo.bigpot_1();
	GameDataManager::getSingletonPtr()->m_EnterGameRoomBigPotMoney2 = _ChannelInfo.bigpot_2();
	GameDataManager::getSingletonPtr()->m_RoomId = _ChannelInfo.id();
	GameDataManager::getSingletonPtr()->m_BettingRule = _ChannelInfo.bettingrule();
	GameDataManager::getSingletonPtr()->m_seedMoney = _ChannelInfo.seedmoney();
	GameDataManager::getSingletonPtr()->m_Grade = _ChannelInfo.grade();
	GameDataManager::getSingletonPtr()->m_EnterGameRoomBettingMaxMoney = _ChannelInfo.bigbettingmaxmoney();
	GameDataManager::getSingletonPtr()->m_GameMode = _ChannelInfo.gamemode();

	GameDataManager::getSingletonPtr()->m_seasonId = _matchInfo->matchid();
	GameDataManager::getSingletonPtr()->m_TournamentIp = _ChannelInfo.ip();
	GameDataManager::getSingletonPtr()->m_TournamentPort = _ChannelInfo.port();

	WebService::getSingletonPtr()->SurvivalEnterReq(_matchInfo->matchid());
}

void LobbySurvivalWindowMain::ApplyRankGamePopup()
{
	LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());

	W_DeathMatchOfInfo* _pInfo = GameDataManager::getSingletonPtr()->m_SurvivalOfInfo;
	W_DeathMatchInfo _matchInfo = _pInfo->matchinfo(m_SeletctedCellIndex);
		
	LobbyRankerGamePopup* pPanel = new LobbyRankerGamePopup();
	LayerManager::getSingleton().pushDynamicLayer(pPanel, DYNAMIC_PUSH_LAYER);
	string name = _matchInfo.name();
	pPanel->ShowPanel(true);
	pPanel->SetData(name);
	pPanel->SetType(GameMode::MODE_SURVIVAL_TOURNAMENT);	
}

void LobbySurvivalWindowMain::onEnter()
{
	Panel::onEnter();

	setTouchable(true);
	scheduleUpdate();
}