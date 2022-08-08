#include "pch.h"
#include "LobbyShopPanel.h"

#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "SimplePopupPanel.h"
#include "GameStringDepot.h"
#include "CustomPopupPanel.h"
#include "LobbyScene.h"
#include "LobbyUIPanel.h"
#include "W_PayReq.pb.h"
#include "W_PayRes.pb.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	#include "android/IapManager.h"
#endif
#include "W_PayReserveReq.pb.h"
#include "W_PayReserveRes.pb.h"
#include "CmdQueue.h"
#include "PanelHelper.h"
#include "PokerRankHelper.h"
#include "PokerRecordHelper.h"
#include "PokerShopHelper.h"
#include "BuyCharacterConfirmPanel.h"
//#include "ModelTabPanel.h"

//#define USE_ONE_STORE

LobbyShopPanel::LobbyShopPanel()
{

	m_TapIndex = 0;
	m_CellIndex = 0;
	mLoginProcess = false;
	m_pShopListView = nullptr;
	m_pShopListContainer = nullptr;


	m_MemberShipPanel = nullptr;
	m_RubyShopPanel = nullptr;
	mCharacterShopPanel = nullptr;
	mCardListShopPanel = nullptr;
	mModelTabPanel = nullptr;

	
	InitPanel();
	InitImage();
	initButton();	
	setButtonListener(this);
	

	//unscheduleUpdate();

	m_ViewDataIndex = 10;

	//SetShopVipInfo();
}

LobbyShopPanel::~LobbyShopPanel()
{
	//destruct();
}

void LobbyShopPanel::InitPanel()
{
	//Panel* panel = addMouseBlockPanel(this, true);
	//panel->setContentSize(CCSize(DESIGN_WIDTH, DESIGN_HEIGHT - 72));
	construct(getMxmlPath() + "dmy_shop.mxml");

	InitShopPanel();
	InitTapButtonPanel();		
}

void LobbyShopPanel::InitImage()
{
	m_ShadowBg = getSkel("skel_backimge");
}

void LobbyShopPanel::initButton()
{
	m_TapBtn[0] = m_TapBtnPanel[0]->getButton("sbtn_button");
	m_TapBtn[0]->setEnable(false);
	m_TapBtn[0]->setSkelAnimation("tab_on");
	m_TapBtn[0]->setListener(this);
	m_TapBtn[0]->setName("button_tap1");

	m_TapBtn[1] = m_TapBtnPanel[1]->getButton("sbtn_button");
	m_TapBtn[1]->setEnable(false);
	m_TapBtn[1]->setSkelAnimation("tab_off");
	m_TapBtn[1]->setListener(this);
	m_TapBtn[1]->setName("button_tap2");

	m_TapBtn[2] = m_TapBtnPanel[2]->getButton("sbtn_button");
	m_TapBtn[2]->setEnable(false);
	m_TapBtn[2]->setSkelAnimation("tab_off");
	m_TapBtn[2]->setListener(this);
	m_TapBtn[2]->setName("button_tap3");

#ifdef NO_USE_CHECK
	m_TapBtn[3] = nullptr;
#else
	m_TapBtn[3] = m_TapBtnPanel[3]->getButton("sbtn_button");
	m_TapBtn[3]->setEnable(false);
	m_TapBtn[3]->setSkelAnimation("tab_off");
	m_TapBtn[3]->setListener(this);
	m_TapBtn[3]->setName("button_tap4");
#endif // NO_USE_CHECK	

	// 모델
	m_TapBtn[4] = m_TapBtnPanel[4]->getButton("sbtn_button");
	m_TapBtn[4]->setEnable(false);
	m_TapBtn[4]->setSkelAnimation("tab_off");
	m_TapBtn[4]->setListener(this);	// 게등위 임시
	m_TapBtn[4]->setName("button_tap5");
	
}


bool LobbyShopPanel::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (pTouch->getLocation().y >= DESIGN_HEIGHT - 72.f)
		return false;
	
	if (pTouch->getLocation().x < 180.f)
		return false;

	m_bMovingCell = false;
	m_fMoveG = 0.f;
	m_bTouchCancel = false;	
	return true;	
}


void LobbyShopPanel::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	Panel::ccTouchMoved(pTouch, pEvent);

	if (m_RubyShopPanel && !m_RubyShopPanel->isVisible())
		return;


	CCPoint _startTouch = pTouch->getStartLocationInView();
	CCPoint _moveTouch = pTouch->getLocationInView();

	float _defPos = abs(_startTouch.x - _moveTouch.x);

	if (_defPos > 10.f && m_bTouchCancel == false)
	{
		m_bTouchCancel = true;
		cellTouchCancel(pTouch->getLocation());
	}
	if (m_TapIndex == TAB_MEBERSHIP)
		return;

	int _moveV = pTouch->getPreviousLocation().x - pTouch->getLocation().x;
	MoveCellUpdate(_moveV);
}

void LobbyShopPanel::MoveCellUpdate(int _moveV)
{
	if (m_pShopListView == nullptr)
		return;

	CCPoint _offSetPoint = m_pShopListView->getContentOffset();
	int _size = 0;
	if (m_TapIndex == TAB_RUBY)
	{
		_size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->cashshopdata_size();
	}

	
	m_fMoveG = _moveV;

	if (_moveV > 0)
	{
		if (m_fMoveG > mRubyCellSize.width)
		{
			m_fMoveG = mRubyCellSize.width;
		}
	}
	else if (_moveV < 0)
	{
		if (m_fMoveG < -mRubyCellSize.width)
		{
			m_fMoveG = -mRubyCellSize.width;
		}
	}

	if (_size <= SHOP_CELL_MAX)	//셀 수가 MAX보다 많고
	{
		m_pShopListView->setContentOffset(_offSetPoint - ccp(_moveV, 0));
		return;
	}

	bool _bMove = false;
	if (_moveV > 0)
	{
		float _maxMove = -mRubyCellSize.width * 2.5f;
		if (_offSetPoint.x <= _maxMove)
		{
			if (m_CellIndex + SHOP_CELL_MAX < _size)
			{
				m_CellIndex++;
				m_pShopListView->setContentOffset(_offSetPoint + ccp(mRubyCellSize.width, 0));
				for (int _i = 0; _i < SHOP_CELL_MAX; _i++)
				{
					if (m_TapIndex == TAB_RUBY)
						UpdateRubyShopList(_i, m_CellIndex + _i);
				}
				_bMove = true;
			}
		}
	}
	else if (_moveV < 0)
	{
		float _minMove = -mRubyCellSize.width;
		if (_offSetPoint.x >= _minMove)
		{
			if (m_CellIndex > 0)
			{
				m_CellIndex--;
				m_pShopListView->setContentOffset(_offSetPoint - ccp(mRubyCellSize.width, 0));
				for (int _i = 0; _i < SHOP_CELL_MAX; _i++)
				{
					if (m_TapIndex == TAB_RUBY)
						UpdateRubyShopList(_i, m_CellIndex + _i);
				}
				_bMove = true;
			}
		}
	}

	if (_bMove == false)
	{
		m_pShopListView->setContentOffset(_offSetPoint - ccp(_moveV, 0));
	}
}


void LobbyShopPanel::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	Panel::ccTouchEnded(pTouch, pEvent);

	if (m_RubyShopPanel && !m_RubyShopPanel->isVisible())
		return;


	if (m_bTouchCancel == true)
	{
		m_bMovingCell = true;
		return;
	}
	m_fMoveG = 0.f;

	CCPoint _startTouch = pTouch->getStartLocationInView();
	CCPoint _EndTouch = pTouch->getLocationInView();

	float _defPos = abs(_startTouch.x - _EndTouch.x);

	if (_defPos <= 10.f && m_TapIndex == TAB_RUBY)
	{
		/*cellTouch(pTouch->getLocation());*/
		CCPoint tableTouchPoint = pTouch->getLocation();

		//TODO : TOUCH
		auto& panelNodes = m_pShopListContainer->getChildren();
		for(auto _node : panelNodes)
		{
			Panel* _panel = dynamic_cast<Panel*>(_node);
			Button* _OkBtn = m_ListBtnCell[_panel->getTag()]->getButton("sbtn_button");
			if (_OkBtn->hasCollided(_OkBtn->convertToNodeSpace(tableTouchPoint))){
				if (_OkBtn->isEnabled()){
					onClicked(_OkBtn->getName());
				}
			}
		}
	}
}

void LobbyShopPanel::resume()
{
}

void LobbyShopPanel::SetBuyPopup(int _index)
{
	if (m_TapIndex == TAB_MEBERSHIP)
	{
		W_MonthlyClassShopData _DataSilver = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(0);
		W_MonthlyClassData _pDataSilver = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassdata(PokerShopHelper::getMonthlyClassData(_DataSilver.id()));

		W_MonthlyClassShopData _DataGold = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(0);
		W_MonthlyClassData _pDataGold = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassdata(PokerShopHelper::getMonthlyClassData(_DataGold.id()));
		if (_pDataSilver.isbuy() && !_pDataGold.isbuy()) {
			//실버가 있다면
			int _monthlyClass = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_MonthlyClassID;
			if (_monthlyClass == 0)
				PanelHelper::pushConfirmMemberShipPanel(_index);
			else {
				Panel* buyConfirm = PanelHelper::pushBuyMemberConfirmPanel("GO_MEMBERSHIP" + StringConverter::toString(_index));
				buyConfirm->setListener(this);				
			}
		}
		else
			PanelHelper::pushConfirmMemberShipPanel(_index);		
	}
}

void LobbyShopPanel::onClicked(const string& name)
{
	if (mLoginProcess)
		return;

	if (name == "button_tap1")
	{
		ClickTapButton(0);
		return;
	}
	else if (name == "button_tap2")
	{
		ClickTapButton(1);
		return;
	}
	else if (name == "button_tap3")
	{
		ClickTapButton(2);
		return;
	}
	else if (name == "button_tap4")
	{
		ClickTapButton(3);
		return;
	}
	// 모델
	else if (name == "button_tap5")
	{
		ClickTapButton(4);
		return;
	}

	if (name == "sbtn_tab_out")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
		LayerManager::getSingleton().popLayer(this);
		PanelHelper::pushInventoryPanel();		
		return;
	}

	if (name == "sbtn_button_info") {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_REFUND_TYPE);
		return;
	}

	if (m_TapIndex == TAB_MEBERSHIP)
	{

		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//MonthlyClass_Shop_Res_
		if (name == "BTN_DETAIL1")
		{
			GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_SILVER_MEMBER_TYPE);
		}

		if (name == "BTN_DETAIL2")
		{
			GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_GOLD_MEMBER_TYPE);
		}

		if (name == "BuyRubyButton0")
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			SetBuyPopup(0);			
		}
		else if (name == "BuyRubyButton1")
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			SetBuyPopup(1);			
		}
		else if (name == "BuyCashButton0")
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			SetBuyPopup(0);			
		}
		else if (name == "BuyCashButton1")
		{
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
			SetBuyPopup(1);
		}
		else if (name == "InformationButton0")
		{
			
		}
		else if (name == "InformationButton1")
		{

		}
	}
	else if (m_TapIndex == TAB_RUBY)
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		if (strncmp("RubyShopButton", name.c_str(), 14) == 0)
		{
			int _index = nxExtractInt(name, "RubyShopButton");
			int32 _id = GameDataManager::getSingletonPtr()->GetGameDataPtr()->cashshopdata(_index).id();
			//sendWPayReserveReq(_id);

			PanelHelper::pushSimpleConfirmPopupPanel("Protocol Is Developing", "Client Message");

		}
	}
	

	//if (name == "sbtn_tapbutton_on_stay1" || name == "sbtn_tapbutton_on_stay2" || name == "sbtn_tapbutton_on_stay3")
	//{
	//	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	//	int _index = nxExtractInt(name, "sbtn_tapbutton_on_stay");
	//	m_TapIndex = _index - 1;
	//	ClickTapButton(m_TapIndex);
	//}
}

void LobbyShopPanel::ClickTapButton(int _idx, bool playSound /*= true*/)
{
	m_CellIndex = 0;
	m_bMovingCell = false;

	m_TapIndex = _idx;
	switch (_idx)
	{
	case TAB_MEBERSHIP:
		if (playSound)
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);

		if (m_MemberShipPanel) {
			m_MemberShipPanel->setVisible(true);			
		}
		else {
			InitMemberShipPanel();
		}

		if (m_RubyShopPanel) {
			m_RubyShopPanel->setVisible(false);
		}

		if (mModelTabPanel)
			mModelTabPanel->setActivate(false);
		
		if (mCharacterShopPanel)
			mCharacterShopPanel->setActivate(false);

		if (mCardListShopPanel)
			mCardListShopPanel->setActivate(false);

		break;
	case TAB_RUBY:
		if (playSound)
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
		
		if (m_MemberShipPanel)
			m_MemberShipPanel->setVisible(false);
		if (m_RubyShopPanel) {
			m_RubyShopPanel->setVisible(true);
		}
		else {
			InitRubyShopPanel();
		}

        if (mModelTabPanel)
			mModelTabPanel->setActivate(false);

		if (mCharacterShopPanel)
			mCharacterShopPanel->setActivate(false);

		if (mCardListShopPanel)
			mCardListShopPanel->setActivate(false);
		
		break;
	case TAB_CHARACTER:
		if (playSound)
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
		if (m_MemberShipPanel)
			m_MemberShipPanel->setVisible(false);
		if (m_RubyShopPanel)
			m_RubyShopPanel->setVisible(false);
		if (mModelTabPanel)
			mModelTabPanel->setActivate(false);
		if (mCharacterShopPanel) {
			mCharacterShopPanel->setActivate(true);
		}
		else {
			initCharacterShopPanel();
		}

		if (mCardListShopPanel)
			mCardListShopPanel->setActivate(false);
		break;

	case TAB_CARD:
		if (playSound)
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
		if (m_MemberShipPanel)
			m_MemberShipPanel->setVisible(false);
		if (m_RubyShopPanel)
			m_RubyShopPanel->setVisible(false);
		if (mModelTabPanel)
			mModelTabPanel->setActivate(false);

		if (mCharacterShopPanel) {
			mCharacterShopPanel->setActivate(false);
		}
				
		if (mCardListShopPanel) {
			mCardListShopPanel->setActivate(true);
		}
		else {
			initCardShopPanel();
		}

		break;

	case TAB_MODEL:
		if (playSound)
			GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_PAGE);
		if (m_MemberShipPanel)
			m_MemberShipPanel->setVisible(false);
		if (m_RubyShopPanel)
			m_RubyShopPanel->setVisible(false);
		if (mCharacterShopPanel)
			mCharacterShopPanel->setActivate(false);
		if (mCardListShopPanel)
			mCardListShopPanel->setActivate(false);

		if (mModelTabPanel) {
			mModelTabPanel->setActivate(true);
		}
		else {
			initModelShopPanel();
		}

		break;
	}
	
	int tabSize = 5;
#ifdef NO_USE_CHECK
	tabSize = 3;
#endif // NO_USE_CHECK


	for (int _i = 0; _i < tabSize; _i++)
	{
		if (_i == _idx)
		{
			m_TapBtn[_i]->setSkelAnimation("tab_on");
			m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setVisible(false);
			m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setVisible(true);
		}
		else
		{
			m_TapBtn[_i]->setSkelAnimation("tab_off");
			m_TapBtnPanel[_i]->getLabel("txt_off_tab")->setVisible(true);
			m_TapBtnPanel[_i]->getLabel("txt_on_tab")->setVisible(false);
		}
	}
	
}

void LobbyShopPanel::update(float dt)
{
	ScrollViewOffsetProcess(dt);
	updateNotiWidget();
}

bool LobbyShopPanel::handling(STCMD &stCmd)
{
	if (LayerManager::getSingleton().hasLayerType<BuyCharacterConfirmPanel>()) {
		return false;
	}

	if (!isVisible()) {
		CCLog("NO vislble false");
		return false;
	}

	if (auto *pstIt = castCMD<STCMD_IAP_ONESTORE_REQUEST_RESULT>(&stCmd))
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
	else if (auto *pstIt = castCMD<STCMD_IAP_GOOGLESTORE_REQUEST_RESULT>(&stCmd))
	{
		STCMD_IAP_GOOGLESTORE_REQUEST_RESULT res = *pstIt;
		if (res.isSucess) {
			CCLog("STCMD_IAP_REQUEST_RESULT sucess res.tid = %s , res.txid = %s , res.receipt = %s", res.tid.c_str(), res.orderId.c_str(), res.purchaseToken.c_str());			
			sendW_PayReq(res.tid, res.orderId, res.purchaseToken);
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

void LobbyShopPanel::SetTapIdx(int idx)
{
	if (idx == -1)
		m_TapIndex = 0;
	else
		ClickTapButton(idx,false);
}

void LobbyShopPanel::ShowShopPanel()
{
	ClickTapButton(0,false);	
	m_bMovingCell = false;
	ShowShopUi();	
	ShowShopTitie();
}
void LobbyShopPanel::HideShopPanel()
{
	HideShopTitie();
	HideShopUi();
	//runAction(CCSequence::create(
	//	CCCallFunc::create(this, callfunc_selector(LobbyShopPanel::HideShopTitie)),
	//	CCMoveTo::create(0.3f, m_HidePosition),
	//	CCCallFunc::create(this, callfunc_selector(LobbyShopPanel::HideShopUi)),
	//	NULL));
}

void LobbyShopPanel::ShowShopUi()
{
	//unscheduleUpdate();
	//scheduleUpdate();

}

void LobbyShopPanel::HideShopUi()
{
	
}

void LobbyShopPanel::ShowShopTitie()
{
	//m_ShopTitleLabel->setVisible(true);
	//m_ShopTitleMark->setVisible(true);
	//m_ShopTitleBg->setVisible(true);

	for (Button* _btn : m_TapBtn)
	{
		if (_btn)
			_btn->setEnable(true);
	}

	//setTouchable(true);

	GameDataManager::getSingletonPtr()->FreeUiProcess();

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_SHOP);
		}
	}
}

void LobbyShopPanel::HideShopTitie()
{
	//m_ShopTitleLabel->setVisible(false);
	//m_ShopTitleMark->setVisible(false);
	//m_ShopTitleBg->setVisible(false);

	for (Button* _btn : m_TapBtn)
	{
		if (_btn)
			_btn->setEnable(false);
	}

	//setTouchable(false);

	if (LayerManager::getSingletonPtr()->hasLayer("LobbyTopUI"))
	{
		LobbyTopUiPanel* _pTopUiPanel = dynamic_cast<LobbyTopUiPanel*>(LayerManager::getSingletonPtr()->getLayer("LobbyTopUI"));
		if (_pTopUiPanel)
		{
			_pTopUiPanel->SetTopTitle(LobbyUiStatus::LOBBY_UI_MAIN);
		}
	}
}
//
//void LobbyShopPanel::SetCharacterShopList()
//{
//	ClearCharacterShopList();
//
//	m_pShopListContainer = CCLayer::create();
//	CCSize _contentSize = getDummy("dmy_tab1_scrollsize_1").size - ccp(0.f, 10.f);
//
//	int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata_size();
//	CreateCharacterCell(_size);
//
//	if (m_CellIndex < 0)
//		m_CellIndex = 0;
//
//	for (int _i = 0; _i < SHOP_CELL_MAX; _i++)
//	{
//		if (_i < _size)
//		{
//			UpdateCharacterShopList(_i, m_CellIndex + _i);
//		}
//	}
//
//	if (_size > 0)
//	{
//		getSkel("skel_tab1_empty_mark1")->setVisible(false);
//		getLabel("txt_tab1_empty")->setVisible(false);
//
//		int _listSize = _size;
//		if (_listSize > SHOP_CELL_MAX)
//			_listSize = SHOP_CELL_MAX;
//
//		m_pShopListContainer->setContentSize(CCSizeMake(SHOP_CELL_SIZE * _listSize, _contentSize.height));
//	}
//	else
//	{
//		getSkel("skel_tab1_empty_mark1")->setVisible(true);
//		getLabel("txt_tab1_empty")->setVisible(true);
//		m_pShopListContainer->setContentSize(_contentSize);
//	}
//
//	m_pShopListView = extension::CCScrollView::create(_contentSize, m_pShopListContainer);
//	m_pShopListView->setDirection(extension::kCCScrollViewDirectionHorizontal);
//	m_pShopListView->setBounceable(false);
//	//가장 상단으로 올리기.
//	m_pShopListView->setContentOffset(ccp(0, 0), false);
//
//	CCPoint _ListPos = (_contentSize / -2.f);
//	m_pShopListView->setPosition(_ListPos);
//	getSkel("skel_tab1_panel_f1_2_center")->addChild(m_pShopListView, 10);
//	m_pShopListView->setTouchEnabled(false);
//}
//
//void LobbyShopPanel::ClearCharacterShopList()
//{
//	ClearShopList();
//}

void LobbyShopPanel::SetMembershipShop()
{
	ClearMembershipShopList();

	m_pShopListContainer = CCLayer::create();
	CCSize _contentSize = getDummy("dmy_tab1_scrollsize_1").size - CCSize(ccp(0.f, 10.f));
	
	int _size = 2; 
	CreateClassShopCell();

	m_pShopListContainer->setContentSize(_contentSize);

	m_pShopListView = CCScrollView::create(_contentSize, m_pShopListContainer);
	m_pShopListView->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	m_pShopListView->setBounceable(false);
	//가장 상단으로 올리기.
	//m_pFrinedListView->setContentOffset(ccp(-88.f * (_size-1) , 0), false);
	m_pShopListView->setContentOffset(ccp(0, 0), false);

	CCPoint _ListPos = (_contentSize / -2.f);
	m_pShopListView->setPosition(_ListPos);
	getSkel("skel_tab1_panel_f1_2_center")->addChild(m_pShopListView, 10);
	getLabel("txt_tab1_empty")->setVisible(false);
}

void LobbyShopPanel::ClearMembershipShopList()
{
	ClearShopList();
}

void LobbyShopPanel::SetRubyShopList()
{
	//ClearCharacterShopList();

	m_pShopListContainer = CCLayer::create();
	CCSize _contentSize = m_RubyShopPanel->getDummy("dmy_scrollsize").size;

	int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->cashshopdata_size();
	CreateRubyCell(_size);

	if (m_CellIndex < 0)
		m_CellIndex = 0;

	for (int _i = 0; _i < SHOP_CELL_MAX; _i++)
	{
		if (_i < _size)
		{
			UpdateRubyShopList(_i, m_CellIndex + _i);
		}
	}

	if (_size > 0)
	{
		int _listSize = _size;
		if (_listSize > MAX_LETTER_CELL)
			_listSize = MAX_LETTER_CELL;

		m_pShopListContainer->setContentSize(CCSizeMake(mRubyCellSize.width * _listSize, _contentSize.height));
	}
	else
	{
		m_pShopListContainer->setContentSize(_contentSize);
	}

	m_pShopListView = CCScrollView::create(_contentSize, m_pShopListContainer);
	m_pShopListView->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	m_pShopListView->setBounceable(false);
	//가장 상단으로 올리기.NZ창헌
	m_pShopListView->setContentOffset(ccp(0, 0), false);

	CCPoint _ListPos = m_RubyShopPanel->getDummy("dmy_scrollsize").origin;
	m_pShopListView->setPositionX(_ListPos.x);
	m_pShopListView->setPositionY(DESIGN_HEIGHT - _ListPos.y - _contentSize.height);
	m_RubyShopPanel->addChild(m_pShopListView, 10);
	m_pShopListView->setTouchEnabled(true);
}

void LobbyShopPanel::ClearRubyShopList()
{
	ClearShopList();
}


void LobbyShopPanel::ClearShopList()
{
	if (m_pShopListContainer)
	{
		m_pShopListContainer->cleanup();
		m_pShopListContainer->removeFromParent();
	}
	m_pShopListContainer = nullptr;

	if (m_pShopListView)
	{
		m_pShopListView->cleanup();
		m_pShopListView->removeFromParent();
	}
	m_pShopListView = nullptr;
}


void LobbyShopPanel::CreateClassShopCell()
{
	for (int _i = 0; _i < 2; _i++)
	{
		m_ListCell[_i] = new Panel();
		m_ListCell[_i]->construct(getMxmlPath() + "dmy_membership.mxml");
		CCSize _ButtonPanelSize = m_ListCell[_i]->getDummy("dmy_membership").size;


		if (_i == 0)
		{
			m_ListCell[_i]->getSkel("skel_membership_gold")->playAnimation("membership_silver");			
		}

		else if (_i == 1)
		{
			m_ListCell[_i]->getSkel("skel_membership_gold")->playAnimation("membership_gold");			
		}


		m_ListCell[_i]->setPosition(ccp(20.f + (_ButtonPanelSize.width * _i * 1.05f), _ButtonPanelSize.height - DESIGN_HEIGHT + 30.f));
		Button* _pButton1 = m_ListCell[_i]->getButton("sbtn_middle_button_stay1");
		_pButton1->setListener(this);
		_pButton1->setType(Button::NoPressImg);
		//_pButton1->getButtonSkelObject()->playAnimation("button_rubby");
		_pButton1->setName("BuyRubyButton" + StringConverter::toString(_i));
		//_pButton1->setPaused(true);
		_pButton1->getButtonSkelObject()->playAnimation("middle_iconbutton_stay"); //루비 추가.
		_pButton1->getButtonSkelObject()->setSkin("button_rubby");

		Button* _pButton2 = m_ListCell[_i]->getButton("sbtn_middle_button_stay2");
		_pButton2->setListener(this);
		_pButton2->setName("BuyCashButton" + StringConverter::toString(_i));
		_pButton2->getButtonSkelObject()->setSkin("button_rubby");
		_pButton2->setType(Button::NoPressImg);
		//_pButton2->setPaused(true);

		m_ListCell[_i]->getLabel("txt_membership_spec")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ListCell[_i]->getLabel("txt_iconprice")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ListCell[_i]->getLabel("txt_price2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ListCell[_i]->getLabel("txt_buyguide1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ListCell[_i]->getLabel("txt_buyguide2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		Nx::Label* _pSpec = m_ListCell[_i]->getLabel("txt_membership_spec");
		Nx::Label* _pPrice1 = m_ListCell[_i]->getLabel("txt_iconprice");
		Nx::Label* _pPrice2 = m_ListCell[_i]->getLabel("txt_price2");


		int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata_size();
		if (_i < _size)
		{
			W_MonthlyClassShopData _Data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(_i);
			_pPrice1->setString(StringConverter::toString(_Data.cash()).c_str());
			_pPrice2->setString((StringConverter::toString(_Data.money()) + GameStringDepot::getSingleton().getString("TXT_COUNT_MONEY")).c_str());

			int _line = _Data.desc_size();
			string _desc = "";
			for (int _l = 0; _l < _line; _l++)
			{
				W_MonthlyClassShopData_ShopDesc _ShopDesc = _Data.desc(_l);
				if (_ShopDesc.has_content())
				{
					_desc += _ShopDesc.content();
				}
				if (_l != _line - 1)
				{
					_desc += "\n";
				}
			}

			_pSpec->setString(_desc.c_str());
		}
		else
		{
			_pPrice1->setString("");
			_pPrice2->setString("");
			_pSpec->setString("");
		}

		m_pShopListContainer->addChild(m_ListCell[_i]);
		m_ListCell[_i]->release();
	}

}

bool LobbyShopPanel::cellTouchStart(const CCPoint& tableTouchPoint)
{
	if (m_pShopListContainer == nullptr)
		return false;

	auto& panelNodes = m_pShopListContainer->getChildren();
	for(auto _node : panelNodes)
	{
		Panel* _panel = dynamic_cast<Panel*>(_node);

		if (m_TapIndex == TAB_MEBERSHIP)
		{
			Button* btn1 = _panel->getButton("sbtn_middle_button_stay");
			if (btn1) {
				if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
					if (btn1->isEnabled()){
						btn1->setSkelAnimation("middle_iconbutton_in", false);
						return true;
					}
				}				
			}
		}
		else if (m_TapIndex == TAB_RUBY)
		{

		}
		else if (m_TapIndex == TAB_CHARACTER)
		{
			Button* btn1 = _panel->getButton("sbtn_middle_button_stay");
			if (btn1) {
				if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
					if (btn1->isEnabled()){
						btn1->setSkelAnimation("middle_button_in", false);
						return true;
					}
				}				
			}
		}
		
	}

	return false;
}

bool LobbyShopPanel::cellTouchCancel(const CCPoint& tableTouchPoint)
{
	if (m_pShopListContainer == nullptr)
		return false;

	//CCObject* _node;
	//CCArray* panelNodes = m_pShopListContainer->getChildren();
	//CCARRAY_FOREACH(panelNodes, _node)
	//{
	//	Panel* _panel = dynamic_cast<Panel*>(_node);

	//	if (m_TapIndex == 0)
	//	{
	//		Button* btn1 = _panel->getButton("sbtn_middle_button_stay");
	//		Button* btn2 = _panel->getButton("sbtn_exclamation_mark_stay");
	//		if (btn1 && btn2) {
	//			if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
	//				if (btn1->isEnabled()){
	//					btn1->setSkelAnimation("middle_iconbutton_out", false);
	//					btn1->setSkelAppendAnimation("middle_iconbutton_stay");
	//				}
	//			}
	//			else if (btn2->hasCollided(btn2->convertToNodeSpace(tableTouchPoint))){
	//				if (btn2->isEnabled()){
	//					btn2->setSkelAnimation("exclamation_mark_out", false);
	//					btn2->setSkelAppendAnimation("exclamation_mark_stay");
	//				}
	//			}
	//		}
	//	}
	//	else if (m_TapIndex == 1)
	//	{

	//	}
	//	else if (m_TapIndex == 2)
	//	{
	//		Button* btn1 = _panel->getButton("sbtn_middle_button_stay");
	//		Button* btn2 = _panel->getButton("sbtn_exclamation_mark_stay");
	//		if (btn1 && btn2) {
	//			if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
	//				if (btn1->isEnabled()){
	//					btn1->setSkelAnimation("middle_button_out", false);
	//					btn1->setSkelAppendAnimation("middle_button_stay");
	//				}
	//			}
	//			else if (btn2->hasCollided(btn2->convertToNodeSpace(tableTouchPoint))){
	//				if (btn2->isEnabled()){
	//					btn2->setSkelAnimation("exclamation_mark_out", false);
	//					btn2->setSkelAppendAnimation("exclamation_mark_stay");
	//				}
	//			}
	//		}
	//	}
	//
	//}
	return false;
}

bool LobbyShopPanel::cellTouch(const CCPoint& tableTouchPoint)
{
	if (m_pShopListContainer == nullptr)
		return false;

	auto& panelNodes = m_pShopListContainer->getChildren();
	for (auto _node : panelNodes)
	{
		Panel* _panel = dynamic_cast<Panel*>(_node);
		if (m_TapIndex == TAB_RUBY)
		{
			Button* btn1 = _panel->getButton("sbtn_middle_button_stay");
			if (btn1) {
				if (btn1->hasCollided(btn1->convertToNodeSpace(tableTouchPoint))){
					if (btn1->isEnabled()){
						string _BtnName = "RubyShopButton" + StringConverter::toString(btn1->getTag());
						onClicked(_BtnName);
						btn1->setSkelAnimation("middle_button_out", false);
						btn1->setSkelAppendAnimation("middle_button_stay");
					}
				}				
			}
		}
		
	}
	return false;
}

void LobbyShopPanel::cellTouchEnd(CCNode* node)
{
	Button* btn = dynamic_cast<Button*>(node);
	if (btn){
		btn->setNormalImage();
	}
}

void LobbyShopPanel::ScrollViewOffsetProcess(float _dt)
{
	if (m_bMovingCell == false)
		return;

	if (m_pShopListView == nullptr)
		return;

	if (m_TapIndex == TAB_MEBERSHIP)
		return;

	CCPoint _offSetPoint = m_pShopListView->getContentOffset();
	
	//int _size = 0;
	//if (m_TapIndex == 0)
	//{
	//	_size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata_size();
	//}
	//else if (m_TapIndex == 1)
	//{
	//	_size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->cashshopdata_size();
	//}

	int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->cashshopdata_size();

	if (m_fMoveG < 0)
	{
		m_fMoveG += mRubyCellSize.width * 0.5f * _dt;

		if (m_fMoveG > -5.f)
		{
			m_bMovingCell = false;
			m_fMoveG = 0.f;
			return;
		}

		float _minMove = -mRubyCellSize.width;
		if (_offSetPoint.x >= _minMove && m_CellIndex > 0)
		{
			m_CellIndex--;
			m_pShopListView->setContentOffset(_offSetPoint - ccp(mRubyCellSize.width - m_fMoveG, 0));
			for (int _i = 0; _i < SHOP_CELL_MAX; _i++)
			{
				//if (m_TapIndex == 0)
				//{
				//	UpdateCharacterShopList(_i, m_CellIndex + _i);
				//}
				if (m_TapIndex == TAB_RUBY)
				{
					UpdateRubyShopList(_i, m_CellIndex + _i);
				}
			}
		}
		else
			m_pShopListView->setContentOffset(_offSetPoint - ccp(m_fMoveG, 0));
	}
	else
	{
		m_fMoveG -= mRubyCellSize.width * 0.5f * _dt;

		if (m_fMoveG < 5.f)
		{
			m_bMovingCell = false;
			m_fMoveG = 0.f;
			return;
		}

		float _maxMove = -mRubyCellSize.width * 2.5f;
		if (_offSetPoint.x <= _maxMove && m_CellIndex + SHOP_CELL_MAX < _size)
		{
			m_CellIndex++;
			m_pShopListView->setContentOffset(_offSetPoint + ccp(mRubyCellSize.width - m_fMoveG, 0));
			for (int _i = 0; _i < SHOP_CELL_MAX; _i++)
			{
				//if (m_TapIndex == 0)
				//{
				//	UpdateCharacterShopList(_i, m_CellIndex + _i);
				//}
				if (m_TapIndex == TAB_RUBY)
				{
					UpdateRubyShopList(_i, m_CellIndex + _i);
				}
			}
		}
		else
			m_pShopListView->setContentOffset(_offSetPoint - ccp(m_fMoveG, 0));
	}

	//if (m_TapIndex == 0)
	//{
	//	int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata_size();

	//	if (_size <= SHOP_CELL_MAX)					//셀 수가 SHOP_CELL_SHOW_MAX보다 많고
	//		return;

	//	if (_offSetPoint >= SHOP_CELL_SIZE * 2.f)	//두칸 이상 셀이 이동 했을 때
	//	{
	//		int _toIdx = (_offSetPoint - (SHOP_CELL_SIZE * 2.f)) / SHOP_CELL_SIZE;
	//		int _dstIdx = _toIdx + SHOP_CELL_MAX;
	//		_toIdx = _toIdx % SHOP_CELL_MAX;
	//		UpdateCharacterShopList(_toIdx, _dstIdx);

	//		//지워지는 셀의 위의 셀은 새로 나타난 셀로 판단하고 갱신
	//		_toIdx = (_toIdx + 1) % SHOP_CELL_MAX;
	//		_dstIdx = _dstIdx - (SHOP_CELL_MAX - 1);
	//		UpdateCharacterShopList(_toIdx, _dstIdx);
	//	}
	//	else
	//	{
	//		UpdateCharacterShopList(0, 0);
	//	}
	//}
	//else if (m_TapIndex == 1)
	//{
	//	//2개라서 업데이트 없음.
	//}
	//else if (m_TapIndex == 2)
	//{
	//	int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->charactershopdata_size();

	//	if (_size <= SHOP_CELL_MAX)					//셀 수가 SHOP_CELL_SHOW_MAX보다 많고
	//		return;

	//	if (_offSetPoint >= SHOP_CELL_SIZE * 2.f)	//두칸 이상 셀이 이동 했을 때
	//	{
	//		int _toIdx = (_offSetPoint - (SHOP_CELL_SIZE * 2.f)) / SHOP_CELL_SIZE;
	//		int _dstIdx = _toIdx + SHOP_CELL_MAX;
	//		_toIdx = _toIdx % SHOP_CELL_MAX;
	//		UpdateRubyShopList(_toIdx, _dstIdx);

	//		//지워지는 셀의 위의 셀은 새로 나타난 셀로 판단하고 갱신
	//		_toIdx = (_toIdx + 1) % SHOP_CELL_MAX;
	//		_dstIdx = _dstIdx - (SHOP_CELL_MAX - 1);
	//		UpdateRubyShopList(_toIdx, _dstIdx);
	//	}
	//	else
	//	{
	//		UpdateRubyShopList(0, 0);
	//	}
	//}
}
//
//void LobbyShopPanel::CreateCharacterCell(int _size)
//{
//	int _MakeCellSize = _size;
//	if (_MakeCellSize > SHOP_CELL_MAX)
//		_MakeCellSize = SHOP_CELL_MAX;
//
//	for (int _i = 0; _i < _MakeCellSize; _i++)
//	{
//		m_ListCell[_i] = new Panel();
//		m_ListCell[_i]->construct(getMxmlPath() + "dmy_goods_panel.mxml");
//		m_ListCell[_i]->setTag(-1);
//
//		CCSize _ButtonPanelSize = m_ListCell[_i]->getDummy("dmy_goods_panel").size;
//		m_ListCell[_i]->setPosition(ccp(10.f + (SHOP_CELL_SIZE * _i), _ButtonPanelSize.height - DESIGN_HEIGHT));
//
//		Button* _pButton = m_ListCell[_i]->getButton("sbtn_middle_button_stay");
//		_pButton->getButtonSkelObject()->playAnimation("middle_iconbutton_stay"); //루비 추가.
//		_pButton->getButtonSkelObject()->setSkin("button_rubby");
//		_pButton->setType(Button::NoPressImg);
//		_pButton->setTag(_i);
//		_pButton->setListener(this);
//		_pButton->setPaused(true);
//
//		m_ListCell[_i]->getButton("sbtn_exclamation_mark_stay")->setType(Button::NoPressImg);
//		m_ListCell[_i]->getButton("sbtn_exclamation_mark_stay")->setListener(this);
//		m_ListCell[_i]->getButton("sbtn_exclamation_mark_stay")->setPaused(true);
//
//		m_ListCell[_i]->getLabel("txt_spec")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
//		m_ListCell[_i]->getLabel("txt_gold_goods")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
//		m_ListCell[_i]->getLabel("txt_limit")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
//		m_ListCell[_i]->getLabel("txt_character_name_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
//		m_ListCell[_i]->getLabel("txt_character_name")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
//		m_ListCell[_i]->getLabel("txt_price")->setVisible(false);
//		m_ListCell[_i]->getLabel("txt_iconprice")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
//		m_ListCell[_i]->getLabel("txt_label_shadow")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
//		m_ListCell[_i]->getLabel("txt_label")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
//
//		Label* _pCharacterName = m_ListCell[_i]->getLabel("txt_character_name");
//		Label* _pSpec = m_ListCell[_i]->getLabel("txt_spec");
//		Label* _pPrice = m_ListCell[_i]->getLabel("txt_iconprice");
//		Label* _pEvent = m_ListCell[_i]->getLabel("txt_label");
//		Label* _pEventShadow = m_ListCell[_i]->getLabel("txt_label_shadow");
//
//		_pEvent->setVisible(false);
//		_pEventShadow->setVisible(false);
//
//		m_ListCell[_i]->getSkel("skel_label_red")->setVisible(false);
//
//		m_pShopListContainer->addChild(m_ListCell[_i]);
//		m_ListCell[_i]->release();
//
//	}
//}

void LobbyShopPanel::CreateRubyCell(int _size)
{
	int _MakeCellSize = _size;
	if (_MakeCellSize > SHOP_CELL_MAX)
		_MakeCellSize = SHOP_CELL_MAX;

	for (int _i = 0; _i < _MakeCellSize; _i++)
	{   //NZ창헌 루비 버튼
		m_ListCell[_i] = new Panel();
		m_ListCell[_i]->construct(getMxmlPath() + "dmy_goods_panel.mxml");
		m_ListCell[_i]->setTag(-1);

		mRubyCellSize = m_ListCell[_i]->getDummy("dmy_goods_panel").size;
		m_ListCell[_i]->setPosition(ccp((mRubyCellSize.width * _i), mRubyCellSize.height - DESIGN_HEIGHT));

		CCPoint _posBtn = m_ListCell[_i]->getDummy("dmy_button_shop").origin;
		CCSize buttonSize = m_ListCell[_i]->getDummy("dmy_button_shop").size;
		m_ListBtnCell[_i] = new Panel();
		m_ListBtnCell[_i]->construct(getMxmlPath() + "dmy_button_shop.mxml");
		m_ListBtnCell[_i]->setPositionX(-buttonSize.width * 0.5f);
		m_ListBtnCell[_i]->setPositionY(-DESIGN_HEIGHT + buttonSize.height * 0.5f);
		m_ListCell[_i]->getImage("dmy_button_shop")->addChild(m_ListBtnCell[_i]);
		
		m_ListBtnCell[_i]->release();

		m_ListBtnCell[_i]->getSkel("skel_icon")->setVisible(false);
		m_ListBtnCell[_i]->getLabel("txt_price2_under")->setVisible(false);
		m_ListBtnCell[_i]->getLabel("txt_price2")->setVisible(false);
		m_ListBtnCell[_i]->getLabel("txt_price1_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ListBtnCell[_i]->getLabel("txt_price1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

		//기덕 하드 코딩
		if (_i == 0) {
			mRubyTickerPanel[_i] = new ShopTicketContentPanel();
			m_ListCell[_i]->addChild(mRubyTickerPanel[_i]);
			mRubyTickerPanel[_i]->release();
			mRubyTickerPanel[_i]->setPosition(m_ListCell[_i]->getImage("dmy_sticker")->getPosition());
			mRubyTickerPanel[_i]->setVisible(false);

			mCenterPos = m_ListCell[_i]->getLabel("txt_gold_goods_center")->getPosition();
			mTopPos = m_ListCell[_i]->getImage("dmy_gold_goods_top")->getPosition();
			mBottomPos = m_ListCell[_i]->getImage("dmy_gold_goods_bottom")->getPosition();
			mTopPos.x = mCenterPos.x;
			mBottomPos.x = mCenterPos.x;
		}

		
		//NZ 창헌 패널 추가
		Button* _pButton = m_ListBtnCell[_i]->getButton("sbtn_button");
		_pButton->setTag(_i);
		_pButton->setListener(this);

		m_ListCell[_i]->getSkel("skel_goods_penal_1_stay")->playAnimation("goods_penal_2_stay");
		m_ListCell[_i]->getSkel("skel_cover")->playAnimation("table_shoprubby");
		m_ListCell[_i]->getSkel("skel_label_red")->setVisible(false);

		m_ListCell[_i]->getLabel("txt_spec")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));		
		m_ListCell[_i]->getLabel("txt_limit")->setVisible(false);		
		m_ListCell[_i]->getLabel("txt_label_shadow")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_ListCell[_i]->getLabel("txt_label")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		
		//선택된 캐릭터 표시
		m_ListCell[_i]->getImage("skel_line_choose")->setVisible(false);
		//처음 결제시 홍보문구
		m_ListCell[_i]->getImage("skel_bonus")->setVisible(false);

		m_ListCell[_i]->getImage("skel_cover_gold")->setVisible(false);
		m_ListCell[_i]->getLabel("txt_bonus")->setVisible(false);
		

		m_pShopListContainer->addChild(m_ListCell[_i]);
		m_ListCell[_i]->release();
	}
}

void LobbyShopPanel::SetShopVipXpBar(int _per)
{
	string _sExpPer = StringConverter::toString(_per) + " %";
	m_pVipExp->setString(_sExpPer.c_str());

	//float _width = getSkel("skel_shopexp_bar")->getBounding().size.width - 5.f;
	//float _startPos = m_pExpBarLeft->getPositionX();
	//float _barWidth = m_pExpBarCenter->getBounding().size.width;
	//float _scaleX = _width / _barWidth;

	//m_pExpBarCenter->setPositionX(_startPos + (_width * ((float)_per / 200.f)));
	//m_pExpBarCenter->setScaleX(_scaleX * ((float)_per / 100.f));
	//m_pExpBarRight->setPositionX(_startPos + (_width * ((float)_per / 100.f)));
}

void LobbyShopPanel::SetShopVipInfo()
{	
}


void LobbyShopPanel::InitMemberShipPanel()
{
	CCPoint _shop1Pos = getDummy("dmy_shopin1").origin;
	_shop1Pos.y = -_shop1Pos.y;

	m_MemberShipPanel = new Panel();
	m_MemberShipPanel->construct(getMxmlPath() + "dmy_shopin1.mxml");
	m_MemberShipPanel->setPosition(_shop1Pos);
	addChild(m_MemberShipPanel);
	m_MemberShipPanel->release();
	m_MemberShipPanel->setButtonListener(this);

	//타이틀
	m_MemberShipPanel->getLabel("txt_shipinfo")->setString(GameStringDepot::getSingleton().getString("SHOP_MEMBERSHIP_TAB_TITLE").c_str());
	m_MemberShipPanel->getLabel("txt_regulation")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REGULATION_DESC").c_str());


	mMemberShipLeftTimeLabel = m_MemberShipPanel->getLabel("txt_time1");
	mMemberShipRightTimeLabel = m_MemberShipPanel->getLabel("txt_time2");

	mMemberShipLeftTimeLabel->setVisible(false);
	mMemberShipRightTimeLabel->setVisible(false);

	int _monthlyClass = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_MonthlyClassID;
	for (int _i = 0; _i < 2; _i++)
	{
		m_memberCard[_i] = new Panel();
		m_memberCard[_i]->construct(getMxmlPath() + "dmy_membership.mxml");
		CCPoint _cardPos = m_MemberShipPanel->getDummy("dmy_membership" + StringConverter::toString(_i+1)).origin;
		_cardPos.y = -_cardPos.y;
		m_memberCard[_i]->setPosition(_cardPos);
		m_MemberShipPanel->addChild(m_memberCard[_i]);
		m_memberCard[_i]->release();

		m_memberCard[_i]->getLabel("txt_rightbutton")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_memberCard[_i]->getLabel("txt_rightbutton")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REGULAR_PAY").c_str());
		
		m_memberCard[_i]->getLabel("txt_discount")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_memberCard[_i]->getLabel("txt_discount")->setString(("25%" + GameStringDepot::getSingletonPtr()->getString("TXT_DISCOUNT_UNIT")).c_str());

		m_memberCard[_i]->getLabel("txt_membership_spec")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		
		m_memberCard[_i]->getLabel("txt_detail")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_memberCard[_i]->getLabel("txt_detail")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_DETAIL_UNIT").c_str());

		m_memberCard[_i]->getButton("sbtn_buttoninfo")->setName("BTN_DETAIL" + StringConverter::toString(_i + 1));
		m_memberCard[_i]->getButton("sbtn_buttoninfo")->setListener(this);

		//자세히 글씨 색깔 수정
		//자세히 버튼 수정
		//spec 글씨 색깔 수정
		if (_i == 0) {			
			m_memberCard[_i]->getButton("sbtn_buttoninfo")->setSkelAnimation("button_insilver");
			m_memberCard[_i]->getLabel("txt_detail")->setColor({ 74, 80, 90 });
			m_memberCard[_i]->getLabel("txt_membership_spec")->setColor({ 74, 80, 90 });

			mSilverTicketPanel = new ShopTicketContentPanel();
			m_memberCard[_i]->addChild(mSilverTicketPanel);
			mSilverTicketPanel->release();
			mSilverTicketPanel->setPosition(m_memberCard[_i]->getImage("dmy_sticker")->getPosition());
			W_MonthlyClassShopData _Data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(_i);			
			W_MonthlyClassData _pData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassdata(PokerShopHelper::getMonthlyClassData(_Data.id()));
			if (_monthlyClass == 0) {
				mMemberSilverBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_SHOP_RUBY);
				mMemberSilverBtn->SetBtnText(StringConverter::toString(_Data.cash()));
			}
			else if (_monthlyClass == 1) {
				if (GameDataManager::getSingleton().getPlayerInfo().ismonthlyclassdiscount()) {
					mMemberSilverBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_SHOP_DISCOUNT);
					mMemberSilverBtn->setSaleState(_Data.cash(), _Data.cash() - _pData.discountcash());
				}
				else {
					mMemberSilverBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_SHOP_RUBY);
					mMemberSilverBtn->SetBtnText(StringConverter::toString(_Data.cash()));
				}
			}
			else {
				mMemberSilverBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_IMPOSSIBLE);
			}

			m_memberCard[_i]->addChild(mMemberSilverBtn);
			mMemberSilverBtn->release();
			CCPoint _btnPos = m_memberCard[_i]->getDummy("dmy_button_shop3").origin;
			mMemberSilverBtn->setPositionX(_btnPos.x);
			mMemberSilverBtn->setPositionY(-_btnPos.y);
			mMemberSilverBtn->SetButtonListener(this);
			mMemberSilverBtn->m_Button->setName("BuyRubyButton0");
			if (_monthlyClass == 1) {
			}
			
		}
		else if (_i == 1) {			
			m_memberCard[_i]->getButton("sbtn_buttoninfo")->setSkelAnimation("button_ingold");
			m_memberCard[_i]->getLabel("txt_detail")->setColor({ 103, 57, 13 });
			m_memberCard[_i]->getLabel("txt_membership_spec")->setColor({ 103, 57, 13 });

			mGoldTicketPanel = new ShopTicketContentPanel();
			m_memberCard[_i]->addChild(mGoldTicketPanel);
			mGoldTicketPanel->release();
			mGoldTicketPanel->setPosition(m_memberCard[_i]->getImage("dmy_sticker")->getPosition());

			W_MonthlyClassShopData _Data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(_i);
			W_MonthlyClassData _pData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassdata(PokerShopHelper::getMonthlyClassData(_Data.id()));
			if (_monthlyClass == 0) {
				mMemberGoldBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_SHOP_RUBY);
				mMemberGoldBtn->SetBtnText(StringConverter::toString(_Data.cash()));
			}
			else if (_monthlyClass == 1) {
				mMemberGoldBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_SHOP_RUBY);
				mMemberGoldBtn->SetBtnText(StringConverter::toString(_Data.cash()));				
			}
			else {
				if (GameDataManager::getSingleton().getPlayerInfo().ismonthlyclassdiscount()) {
					mMemberGoldBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_SHOP_DISCOUNT);
					mMemberGoldBtn->setSaleState(_Data.cash(), _Data.cash() -_pData.discountcash());
				}
				else {
					mMemberGoldBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_SHOP_RUBY);
					mMemberGoldBtn->SetBtnText(StringConverter::toString(_Data.cash()));
				}

			}			
			m_memberCard[_i]->addChild(mMemberGoldBtn);
			mMemberGoldBtn->release();
			CCPoint _btnPos = m_memberCard[_i]->getDummy("dmy_button_shop3").origin;
			mMemberGoldBtn->setPositionX(_btnPos.x);
			mMemberGoldBtn->setPositionY(-_btnPos.y);
			mMemberGoldBtn->m_Button->setName("BuyRubyButton1");
			mMemberGoldBtn->SetButtonListener(this);
			mMemberGoldBtn->SetBtnText(StringConverter::toString(_Data.cash()));
		}
		//적용중
		//게이지바
		//left , right 지운다.
		m_memberCard[_i]->getLabel("txt_leftbutton")->setVisible(false);
		m_memberCard[_i]->getLabel("txt_discount")->setVisible(false);
		m_memberCard[_i]->getLabel("txt_rightbutton")->setVisible(false);
		m_memberCard[_i]->getImage("skel_mark_apply")->setVisible(false);		

		Nx::Label* _pSpec = m_memberCard[_i]->getLabel("txt_membership_spec");

		int _size = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata_size();
		if (_i < _size)
		{
			W_MonthlyClassShopData _Data = GameDataManager::getSingletonPtr()->GetGameDataPtr()->monthlyclassshopdata(_i);
			int _line = _Data.desc_size();
			string _desc = "";
			for (int _l = 0; _l < _line; _l++)
			{
				W_MonthlyClassShopData_ShopDesc _ShopDesc = _Data.desc(_l);
				if (_ShopDesc.has_content())
				{
					_desc += _ShopDesc.content();
				}
				if (_l != _line - 1)
				{
					_desc += "\n";
				}
			}
			_pSpec->setString(_desc.c_str());			
		}
		else
		{			
			_pSpec->setString("");
		}
	}

	m_memberCard[0]->getSkel("skel_membership_gold")->playAnimation("membership_silver");
	m_memberCard[1]->getSkel("skel_membership_gold")->playAnimation("membership_gold");
	refreshMemberShip();
}

void LobbyShopPanel::InitRubyShopPanel() //nz
{
	CCPoint _shop2Pos = getDummy("dmy_shopin2").origin;
	_shop2Pos.y = -_shop2Pos.y;

	m_RubyShopPanel = new Panel();
	m_RubyShopPanel->construct(getMxmlPath() + "dmy_shopin2.mxml");
	m_RubyShopPanel->setPosition(_shop2Pos);
	addChild(m_RubyShopPanel);
	m_RubyShopPanel->release();
	m_RubyShopPanel->setButtonListener(this);

	//타이틀
	m_RubyShopPanel->getLabel("txt_shipinfo")->setString(GameStringDepot::getSingleton().getString("SHOP_RUBY_TAB_TITLE").c_str());
	m_RubyShopPanel->getLabel("txt_regulation")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_REGULATION_DESC").c_str());

	SetRubyShopList();
}

void LobbyShopPanel::InitShopPanel()
{
	getButton("sbtn_tab_out")->setSkelAnimation("tab_out");
	getLabel("txt_tab_out")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getLabel("txt_tab_out")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_GO_INVEN").c_str());	
}

void LobbyShopPanel::InitTapButtonPanel()
{
	CCPoint _tap1Pos = getDummy("dmy_button_tab1").origin;
	_tap1Pos.y = -_tap1Pos.y;

	m_TapBtnPanel[0] = new Panel();
	m_TapBtnPanel[0]->construct(getMxmlPath() + "dmy_button_tab.mxml");
	m_TapBtnPanel[0]->setPosition(_tap1Pos);
	addChild(m_TapBtnPanel[0]);
	m_TapBtnPanel[0]->release();

	m_TapBtnPanel[0]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[0]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	string _tap1Txt = GameStringDepot::getSingletonPtr()->getString("TXT_SHOP_MENU_CHARACTER_BTN");
	m_TapBtnPanel[0]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[0]->getLabel("txt_off_tab")->setString(_tap1Txt.c_str());
	m_TapBtnPanel[0]->getLabel("txt_off_tab")->setVisible(false);
	m_TapBtnPanel[0]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[0]->getLabel("txt_on_tab")->setString(_tap1Txt.c_str());

	CCPoint _tap2Pos = getDummy("dmy_button_tab2").origin;
	_tap2Pos.y = -_tap2Pos.y;

	m_TapBtnPanel[1] = new Panel();
	m_TapBtnPanel[1]->construct(getMxmlPath() + "dmy_button_tab.mxml");
	m_TapBtnPanel[1]->setPosition(_tap2Pos);
	addChild(m_TapBtnPanel[1]);
	m_TapBtnPanel[1]->release();

	m_TapBtnPanel[1]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[1]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	string _tap2Txt = GameStringDepot::getSingletonPtr()->getString("TXT_MYHOME_TAP3_UNIT"); 
	m_TapBtnPanel[1]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[1]->getLabel("txt_off_tab")->setString(_tap2Txt.c_str());
	m_TapBtnPanel[1]->getLabel("txt_off_tab")->setVisible(false);
	m_TapBtnPanel[1]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[1]->getLabel("txt_on_tab")->setString(_tap2Txt.c_str());

	CCPoint _tap3Pos = getDummy("dmy_button_tab3").origin;
	_tap3Pos.y = -_tap3Pos.y;
	m_TapBtnPanel[2] = new Panel();
	m_TapBtnPanel[2]->construct(getMxmlPath() + "dmy_button_tab.mxml");
	m_TapBtnPanel[2]->setPosition(_tap3Pos);
	addChild(m_TapBtnPanel[2]);
	m_TapBtnPanel[2]->release();

	m_TapBtnPanel[2]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[2]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	string _tap3Txt = GameStringDepot::getSingletonPtr()->getString("TXT_RUBY_UNIT"); 
	m_TapBtnPanel[2]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[2]->getLabel("txt_off_tab")->setString(_tap3Txt.c_str());
	m_TapBtnPanel[2]->getLabel("txt_off_tab")->setVisible(false);
	m_TapBtnPanel[2]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[2]->getLabel("txt_on_tab")->setString(_tap3Txt.c_str());

#ifdef NO_USE_CHECK
#else
	CCPoint _tap4Pos = getDummy("dmy_button_tab4").origin;
	_tap4Pos.y = -_tap4Pos.y;
	m_TapBtnPanel[3] = new Panel();
	m_TapBtnPanel[3]->construct(getMxmlPath() + "dmy_button_tab.mxml");
	m_TapBtnPanel[3]->setPosition(_tap4Pos);
	addChild(m_TapBtnPanel[3]);
	m_TapBtnPanel[3]->release();

	m_TapBtnPanel[3]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[3]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	string _tap4Txt = GameStringDepot::getSingletonPtr()->getString("TXT_CARD_UNIT");
	m_TapBtnPanel[3]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[3]->getLabel("txt_off_tab")->setString(_tap4Txt.c_str());
	m_TapBtnPanel[3]->getLabel("txt_off_tab")->setVisible(false);
	m_TapBtnPanel[3]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[3]->getLabel("txt_on_tab")->setString(_tap4Txt.c_str());
#endif // NO_USE_CHECK

	// 모델
	CCPoint _tap5Pos = getDummy("dmy_button_tab5").origin;
	_tap5Pos.y = -_tap5Pos.y;
	m_TapBtnPanel[4] = new Panel();
	m_TapBtnPanel[4]->construct(getMxmlPath() + "dmy_button_tab.mxml");
	m_TapBtnPanel[4]->setPosition(_tap5Pos);
	addChild(m_TapBtnPanel[4]);
	m_TapBtnPanel[4]->release();

	m_TapBtnPanel[4]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[4]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	string _tap5Txt = GameStringDepot::getSingletonPtr()->getString("TXT_MODEL_UNIT");
	m_TapBtnPanel[4]->getLabel("txt_off_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[4]->getLabel("txt_off_tab")->setString(_tap5Txt.c_str());
	m_TapBtnPanel[4]->getLabel("txt_off_tab")->setVisible(false);
	m_TapBtnPanel[4]->getLabel("txt_on_tab")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_TapBtnPanel[4]->getLabel("txt_on_tab")->setString(_tap5Txt.c_str());

// 	CCPoint _goldApPos = getDummy("dmy_gold_ad").origin;
// 	_goldApPos.y = -_goldApPos.y;
// 	mGoldAdPanel = new Panel();
// 	mGoldAdPanel->construct(getMxmlPath() + "dmy_gold_ad.mxml");
// 	mGoldAdPanel->setPosition(_goldApPos);	
// 	addChild(mGoldAdPanel);
// 	mGoldAdPanel->release();
}


void LobbyShopPanel::UpdateRubyShopList(int _toIdx, int _dstIdx)
{
	bool isFirstBuy = false;

	CCLog("UpdateRubyShopList _toIdx = %d , _dstIdx = %d", _toIdx,_dstIdx);
	if (_dstIdx >= GameDataManager::getSingletonPtr()->GetGameDataPtr()->cashshopdata_size()) {
		CCLog("_dstIdx = %d , GameDataManager::getSingletonPtr()->GetGameDataPtr()->cashshopdata_size() = %d", _dstIdx, GameDataManager::getSingletonPtr()->GetGameDataPtr()->cashshopdata_size());
		return;
	}

	if (m_ListCell[_toIdx]->getTag() == _dstIdx) {
		CCLog("_dstIdx = %d", _dstIdx);
		return;
	}

	m_ListCell[_toIdx]->setTag(_dstIdx);
	CCSize _ButtonPanelSize = m_ListCell[_toIdx]->getDummy("dmy_goods_panel").size;

	/*m_ListCell[_toIdx]->setPosition(ccp((SHOP_CELL_SIZE * _toIdx), _ButtonPanelSize.height - DESIGN_HEIGHT));*/

	Button* _pButton = m_ListBtnCell[_toIdx]->getButton("sbtn_button");
	_pButton->setTag(_dstIdx);
	_pButton->setName("RubyShopButton" + StringConverter::toString(_dstIdx));
	//_pButton->setPaused(true);

	Nx::Label* middleName = m_ListCell[_toIdx]->getLabel("txt_gold_goods_center");


	Nx::Label* _pSpec = m_ListCell[_toIdx]->getLabel("txt_spec");
	Nx::Label* _pEvent = m_ListCell[_toIdx]->getLabel("txt_label");
	Nx::Label* _pEventShadow = m_ListCell[_toIdx]->getLabel("txt_label_shadow");
	Nx::Label* title = m_ListCell[_toIdx]->getLabel("txt_character_name");	

	W_CashShopData _pData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->cashshopdata(_dstIdx);
	if (_pData.isfirstbonus()) {
		if (PokerRecordHelper::isFirstBonus(_pData.id())) {
			isFirstBuy = true;
		}
	}


	if (_pData.has_title()) {
		title->setString(_pData.title().c_str());
	}

	middleName->setVisible(false);
	if (_pData.has_name())
	{
		middleName->setString(_pData.name().c_str());
	}

	if (_pData.has_desc_1())
	{
		string _text = _pData.desc_1();
		if (isFirstBuy) {
			_text += "\n";
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
			_text += "\n";
#endif // 0

		}
		_pSpec->setString(_text.c_str());
		vector<string> ids;
		nxTokenize(_text, "\n", back_inserter(ids));

		if (_text == " ") {
			//bottomName->setVisible(true);
			middleName->setVisible(true);
			middleName->setPosition(mBottomPos);
		}
		else if (ids.size() > 1) {
			//topName->setVisible(true);
			middleName->setVisible(true);
			middleName->setPosition(mCenterPos);
		}
		else {
			middleName->setVisible(true);
			middleName->setPosition(mTopPos);
			if (isFirstBuy)
				middleName->setPosition(mCenterPos);

		}
	}
	else
	{
		_pSpec->setString("");
		//bottomName->setVisible(true);
		middleName->setVisible(true);
		middleName->setPosition(mBottomPos);
	}

	if (_pData.has_icon())
	{
		m_ListCell[_toIdx]->getImage("img_character_boxer")->setSpriteFrameWithFile("ui/" + _pData.icon()+".png");		
	}

	if (_pData.has_price())
	{
		//NZ창헌
		string _text = StringConverter::toString(_pData.price()) + GameStringDepot::getSingleton().getString("TXT_COUNT_MONEY");//U8(" 원");
		m_ListBtnCell[_toIdx]->getLabel("txt_price1_under")->setString(_text.c_str());
		m_ListBtnCell[_toIdx]->getLabel("txt_price1")->setString(_text.c_str());
	}

	//만약
	SkelObject* eventIconSkel = m_ListCell[_toIdx]->getSkel("skel_label_red2");
	SkelObject* discountSkel = m_ListCell[_toIdx]->getSkel("skel_label_red");
	discountSkel->setVisible(false);
	eventIconSkel->setVisible(false);
	_pEvent->setVisible(false);
	_pEventShadow->setVisible(false);

	
	//만약 첫 결제라면	
	m_ListCell[_toIdx]->getImage("skel_bonus")->setVisible(false);
	m_ListCell[_toIdx]->getLabel("txt_bonus")->setVisible(false);
	
	
	//mRubyTickerPanel[_toIdx]->setVisible(false);
	m_ListCell[_toIdx]->getImage("skel_cover_gold")->setVisible(_pData.functiontype() == W_CashShopData_eFunctionType_Monthly);
	//월정액인데 현재 월 정액인 경우
	if (_pData.functiontype() == W_CashShopData_eFunctionType_Monthly) {
		if (PokerRankHelper::hasRubyPlus()) {
			mRubyTickerPanel[_toIdx]->setVisible(true);		
			mRubyTickerPanel[_toIdx]->setRubyPlusRemain(PokerRankHelper::getRubyPlusDay());
			_pButton->setEnable(false);
			_pButton->setSkelAnimation("button_shop_use");
			m_ListBtnCell[_toIdx]->getLabel("txt_price1_under")->setString(GameStringDepot::getSingleton().getString("MEMBER_CANT_BUY_BTN").c_str());
			m_ListBtnCell[_toIdx]->getLabel("txt_price1")->setString(GameStringDepot::getSingleton().getString("MEMBER_CANT_BUY_BTN").c_str());
			m_ListBtnCell[_toIdx]->getLabel("txt_price1")->setColor(StringConverter::parseColor3B("ffd042"));

		}		
	}

	if (isFirstBuy) {
		eventIconSkel->setVisible(true);
		eventIconSkel->playAnimation("label_yellow2");
		m_ListCell[_toIdx]->getImage("skel_bonus")->setVisible(true);
		m_ListCell[_toIdx]->getLabel("txt_bonus")->setVisible(true);
		m_ListCell[_toIdx]->getLabel("txt_bonus")->setString(_pData.desc_2().c_str());		
	}
	else {
		if (_pData.bandtype() == eBandNew) {
			eventIconSkel->setVisible(true);
			eventIconSkel->playAnimation("label_yellow");
		}
		else if (_pData.bandtype() == eBandHot) {
			eventIconSkel->setVisible(true);
			eventIconSkel->playAnimation("label_red");
		}
	}
	
		if (_pData.has_discount())
		{
			if (_pData.discount() != 0)
			{
				string _text = NxGetFormatString(GameStringDepot::getSingleton().getString("SHOP_SALE_DESC"), _pData.discount());
				_pEvent->setString(_text.c_str());
				_pEventShadow->setString(_text.c_str());
				_pEvent->setVisible(true);
				_pEventShadow->setVisible(true);
				discountSkel->playAnimation("label_blue");
				discountSkel->setVisible(true);
			}			
		}		
}

void LobbyShopPanel::sendW_PayReq(string tID, string txId, string receipt)
{
	CCLog("sendW_PayReq tID = %s , txid = %s, recept = %s", tID.c_str(), txId.c_str(), receipt.c_str());
	W_PayReq req;
	req.set_tid(tID);
	req.set_txid(txId);
	req.set_receipt(receipt);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE) {
		req.set_order_id(txId);
	}
#endif
	HttpMessage msg(req, HttpResponseHandler(LobbyShopPanel::recvW_PayRes), this);
	HttpManager::getSingleton().send(msg);
}

void LobbyShopPanel::recvW_PayRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_PayRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	bool beforeFirstBuy = PokerRecordHelper::isFirstBonus(mBuyCashId);

	for (int i = 0; i < res.payfirstinfo_size(); i++)
	{
		GameDataManager::getSingleton().setPayFirstInfo(res.payfirstinfo(i));
	}

	bool afterFirstBuy = PokerRecordHelper::isFirstBonus(mBuyCashId);

	bool isFirstBuy = false;
	if (beforeFirstBuy == true && afterFirstBuy == false)
		isFirstBuy = true;

	if (res.success()) {
		CCLog("recvW_PayRes sucess");
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

		if (res.has_playerinfo())
		{
			int getRewardRuby = res.playerinfo().cash() - GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
			//상품 이름
			PanelHelper::pushRubyRewardPanel(getRewardRuby, mBuyCashId, isFirstBuy);
			GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());			
		}		
	}
	else {
		CCLog("recvW_PayRes fail");
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
	}

	if (res.has_playerinfo()) {
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
		GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_PLAYER_INFO_RES);
	}
}

void LobbyShopPanel::sendWPayReserveReq(int cashId)
{
	mBuyCashId = cashId;
	W_PayReserveReq req;
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	if (IapManager::getSingleton().getPaymentType() == IapManager::ONE_STORE)
		req.set_markettype(OneStore);
	else
		req.set_markettype(Google);
#else
	req.set_markettype(Local);
#endif
	req.set_paytype(ePayCash);
	req.set_id(cashId);
	HttpMessage msg(req, HttpResponseHandler(LobbyShopPanel::recvWPayReserveRes), this);
	HttpManager::getSingleton().send(msg);
}

void LobbyShopPanel::recvWPayReserveRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_PayReserveRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success()) {
		CCLog("W_PayReserveRes sucess");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
		if (IapManager::getSingleton().getPaymentType() == IapManager::ONE_STORE)
			IapManager::getSingleton().sendPaymentRequest(res.productid(), "", res.tid());
		else {
			mGoogleTid = res.productid();
			IapManager::getSingleton().launchPurchaseFlow(res.productid(), "", res.tid());
		}		
#else
		//WebService::getSingletonPtr()->_sendCashBuyReq(mBuyCashId);
		STCMD_IAP_ONESTORE_REQUEST_RESULT iapRequestResult;
		iapRequestResult.isSucess = true;
		iapRequestResult.errMsg = "";
		iapRequestResult.tid = res.tid();
		iapRequestResult.txid = "win";
		iapRequestResult.receipt = res.productid();
		CCmdQueue::getSingleton().pushQueue(iapRequestResult);

#endif // DEBUG

		
	}
	else {
		CCLog("W_PayReserveRes fail");
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
	}
}

void LobbyShopPanel::onRefresh()
{
	if (m_MemberShipPanel && m_MemberShipPanel->isVisible()) {
		refreshMemberShip();
	}
}

void LobbyShopPanel::refreshMemberShip()
{
	int _monthlyClass = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_MonthlyClassID;
	mSilverTicketPanel->setVisible(false);
	mGoldTicketPanel->setVisible(false);
	if (_monthlyClass == 1) {
		mSilverTicketPanel->setVisible(true);
		m_memberCard[0]->getImage("skel_mark_apply")->setVisible(true);
		//silver 정보  보여준다.
		int remainDay = nxGetTimeDay(GameDataManager::getSingletonPtr()->getPlayerInfo().monthlyclassexpiretime());
		mSilverTicketPanel->setMemberRamain(remainDay);
	}
	else if (_monthlyClass == 2) {		
		//만약 silver 가 있다면 stop 중이라면 보여준다.
		if (GameDataManager::getSingletonPtr()->getPlayerInfo().monthlyclasssilverexpiretime() > 0.f) {
			int remainDay = nxGetTimeDay(GameDataManager::getSingletonPtr()->getPlayerInfo().monthlyclasssilverexpiretime());
			mSilverTicketPanel->setMemberStop(remainDay);
			mSilverTicketPanel->setVisible(true);
			m_memberCard[0]->getImage("skel_mark_apply")->setVisible(true);
		}
		//골드 정보 보여준다.
		int remainDay = nxGetTimeDay(GameDataManager::getSingletonPtr()->getPlayerInfo().monthlyclassexpiretime());
		mGoldTicketPanel->setMemberRamain(remainDay);		
		mGoldTicketPanel->setVisible(true);
		m_memberCard[1]->getImage("skel_mark_apply")->setVisible(true);
	}

	//m_memberCard[_i]->getLabel("txt_leftbutton")->setString(GameStringDepot::getSingletonPtr()->getString("TXT_30DAYS_TICKET").c_str());
	//30일 이용권 관련
	if (_monthlyClass == 0) {
		//둘다 30일 이용권
		m_memberCard[0]->getLabel("txt_memberinfo")->setString(GameStringDepot::getSingletonPtr()->getString("MEMBER_STATE_BASIC").c_str());
		m_memberCard[1]->getLabel("txt_memberinfo")->setString(GameStringDepot::getSingletonPtr()->getString("MEMBER_STATE_BASIC").c_str());
	}
	else if (_monthlyClass == 1) {
		//남은 기간 표시
		//5일 미만
		int remainDay = nxGetTimeDay(GameDataManager::getSingletonPtr()->getPlayerInfo().monthlyclassexpiretime());
		if (remainDay < 6)
			m_memberCard[0]->getLabel("txt_memberinfo")->setString(GameStringDepot::getSingletonPtr()->getString("MEMBER_STATE_LIMIT_5DAY").c_str());
		else
			m_memberCard[0]->getLabel("txt_memberinfo")->setString(GameStringDepot::getSingletonPtr()->getString("MEMBER_STATE_OVER_5DAY").c_str());
	}
	else if (_monthlyClass == 2) {
		//남은 기간 표시
		//5일 미만
		int remainDay = nxGetTimeDay(GameDataManager::getSingletonPtr()->getPlayerInfo().monthlyclassexpiretime());
		if (remainDay < 6)
			m_memberCard[1]->getLabel("txt_memberinfo")->setString(GameStringDepot::getSingletonPtr()->getString("MEMBER_STATE_LIMIT_5DAY").c_str());
		else
			m_memberCard[1]->getLabel("txt_memberinfo")->setString(GameStringDepot::getSingletonPtr()->getString("MEMBER_STATE_OVER_5DAY").c_str());

		m_memberCard[0]->getLabel("txt_memberinfo")->setString(GameStringDepot::getSingletonPtr()->getString("MEMBER_STATE_EXIST_HIGH").c_str());
		
	}

	//버튼 관련
	//구매를 했을 경우만 처리한다.
	if (!GameDataManager::getSingleton().getPlayerInfo().ismonthlyclassdiscount()) {
		if (_monthlyClass == 1) {
			if (mMemberSilverBtn->isDiscountType()) {
				CCPoint pos = mMemberSilverBtn->getPosition();
				mMemberSilverBtn->removeFromParentAndCleanup(true);
				mMemberSilverBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_IMPOSSIBLE);
				m_memberCard[0]->addChild(mMemberSilverBtn);
				mMemberSilverBtn->release();
				mMemberSilverBtn->setPosition(pos);
			}
			else {
				mMemberSilverBtn->setNoUse();
			}
			
		}
		else if (_monthlyClass == 2) {
			if (mMemberGoldBtn->isDiscountType()) {
				CCPoint pos = mMemberGoldBtn->getPosition();
				mMemberGoldBtn->removeFromParentAndCleanup(true);
				mMemberGoldBtn = new SmallButtonPanel(SmallButtonPanel::LOBBY_UI_IMPOSSIBLE);
				m_memberCard[1]->addChild(mMemberGoldBtn);
				mMemberGoldBtn->release();
				mMemberGoldBtn->setPosition(pos);
			}
			else {
				mMemberGoldBtn->setNoUse();
			}

			//실버도 수정해줘야 한다.
			mMemberSilverBtn->setNoUse();
		}
	}
}

void LobbyShopPanel::setCharacterBuy(int characterId)
{
	if (mCharacterShopPanel) {
		string sendStr = BUY_BTN_SEND_MSG + StringConverter::toString(PokerShopHelper::getShopDataIndex(characterId));
		mCharacterShopPanel->onLayerMessage(sendStr);
	}
}

void LobbyShopPanel::onLayerMessage(const string& msg)
{
	if (msg.find("GO_MEMBERSHIP") != string::npos){
		int idx = nxExtractInt(msg, "GO_MEMBERSHIP");
		PanelHelper::pushConfirmMemberShipPanel(idx);
	}
}

void LobbyShopPanel::updateNotiWidget()
{
	for (int i = 0; i < mNotiWidgets.size(); i++)
	{
		mNotiWidgets[i]->refresh();
	}
}

void LobbyShopPanel::initCharacterShopPanel()
{
	CCPoint _shop3Pos = getImage("dmy_shopin3")->getPosition();
	mCharacterShopPanel = new CharacterListPartPanel(CharacterListPartPanel::CHARACTER_SHOP);
	CCSize size = mCharacterShopPanel->getContentSize();
	CCPoint pos = ccpSub(_shop3Pos, ccp(mCharacterShopPanel->getContentSize().width * 0.5, mCharacterShopPanel->getContentSize().height * 0.5));
	mCharacterShopPanel->setPosition(_shop3Pos);
	addChild(mCharacterShopPanel);
	mCharacterShopPanel->release();
}

void LobbyShopPanel::initCardShopPanel()
{
	CCPoint _shop3Pos = getImage("dmy_shopin3")->getPosition();
	mCardListShopPanel = new CardListPartPanel(CardListPartPanel::CARD_SHOP);
	CCSize size = mCardListShopPanel->getContentSize();
	CCPoint pos = ccpSub(_shop3Pos, ccp(mCardListShopPanel->getContentSize().width * 0.5, mCardListShopPanel->getContentSize().height * 0.5));
	mCardListShopPanel->setPosition(_shop3Pos);
	addChild(mCardListShopPanel);
	mCardListShopPanel->release();
}


// 모델 탭 초기화
void LobbyShopPanel::initModelShopPanel()
{
	CCPoint _shop3Pos = getImage("dmy_shopin4")->getPosition();
	mModelTabPanel = new ModelListPartPanel(MODEL_SHOP);
	//CCSize size = mCharacterShopPanel->getContentSize();
	//CCPoint pos = ccpSub(_shop3Pos, ccp(mCharacterShopPanel->getContentSize().width * 0.5, mCharacterShopPanel->getContentSize().height * 0.5));
	mModelTabPanel->setPosition(_shop3Pos);
	addChild(mModelTabPanel);
	mModelTabPanel->release();

	//SetRubyShopList();
}

void LobbyShopPanel::onEnter()
{
	Panel::onEnter();
	setTouchable(true);
}

//// 모델 탭 초기화
//void LobbyShopPanel::initModelShopPanel()
//{
//	CCPoint panelPos = getImage("dmy_record1")->getPosition();
//	mModelTabPanel = new ModelListPartPanel(ModelListPartPanel::MODEL_SHOP);
//	CCSize size = mModelTabPanel->getContentSize();
//	mModelTabPanel->setPosition(panelPos);
//	addChild(mModelTabPanel);
//	mModelTabPanel->release();
//	mModelTabPanel->setActivate(false);
//}
//
//

