#include "pch.h"
#include "TicketContentPanel.h"
#include "LobbyShopPanel.h"
#include "LobbyUIPanel.h"
#include "LobbyTopUiPanel.h"
#include "PanelHelper.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"


TicketContentPanel::TicketContentPanel(int idx)
{
	mIdx = idx;
	initPanel();	
	initButtonPanel();
	setData();
}

TicketContentPanel::~TicketContentPanel()
{ 

}

void TicketContentPanel::initPanel()
{
	mMainPanel = new Panel();
	 
	addChild(mMainPanel);
	mMainPanel->release();
	mMainPanel->construct(getMxmlPath() + "dmy_pannel_ticket.mxml");
	mContentSize = mMainPanel->getContentSize();
	mMainPanel->setPositionY(mContentSize.height - DESIGN_HEIGHT - mContentSize.height / 2.f);
	mMainPanel->setPositionX(-mContentSize.width / 2.f);
	mMainPanel->setContentSize(mContentSize);
	this->setContentSize(mContentSize);
	
	mTourName = mMainPanel->getLabel("txt_title");
	mTourNameUnder = mMainPanel->getLabel("txt_title_under");
	mTicketAmount = mMainPanel->getLabel("txt_have2");	
	mTicketImg = mMainPanel->getImage("dmy_ticket"); 

	mStepLabel = mMainPanel->getLabel("txt_number");  

	mButtonPanel0 = nullptr;

	//보유갯수
	mMainPanel->getLabel("txt_have")->setString(GameStringDepot::getSingletonPtr()->getString("TicketContentPanel_GETCOUNT_TITLE").c_str());
}

void TicketContentPanel::initButtonPanel()
{
	CCPoint _btnPos = mMainPanel->getDummy("dmy_button_small").origin;
	mButtonPanel0 = new Panel();
	mButtonPanel0->construct(getMxmlPath() + "dmy_button_small.mxml");
	mButtonPanel0->setPositionX(_btnPos.x);
	mButtonPanel0->setPositionY(-_btnPos.y + 20);
	mMainPanel->addChild(mButtonPanel0);
	mButtonPanel0->release();

	mSelectBtn = mButtonPanel0->getButton("sbtn_button");
	mSelectBtn->setListener(this);

	mSelectBtnLabel = mButtonPanel0->getLabel("txt_button");
	mSelectBtnUnderLabel = mButtonPanel0->getLabel("txt_button_under");

	if (mIdx == 0) //칩
	{
		mSelectBtn->setName("goChipshop");
		mSelectBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_BUY_UNIT").c_str());
		mSelectBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("TXT_BUY_UNIT").c_str());
	}

	if (mIdx == 1) //루비
	{
		mSelectBtn->setName("goshop");

		mSelectBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_BUY_UNIT").c_str());
		mSelectBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("TXT_BUY_UNIT").c_str());

	}

	if (mIdx == 2) //모델
	{
		//go model
		mSelectBtn->setName("gomodel");
		mSelectBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_BUY_MODEL_US").c_str());
		mSelectBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("TXT_BUY_MODEL_US").c_str());
	}


	if (mIdx == 3) //토큰
	{
		//go exchange
		mSelectBtn->setName("goexchange");
		mSelectBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_EXCHANGE_TOKEN").c_str());
		mSelectBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("TXT_EXCHANGE_TOKEN").c_str());
	}
	

}


void TicketContentPanel::onClicked(const string& buttonName)
{
	CCLOG("Button Clicked");

	if (buttonName == "goChipshop")
	{
		 
	}
	else if (buttonName == "goshop") {
		CCLOG("BTN goshop Clicked");
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//현재창이 샵창이라면 바꾸고 아니라면 push 한다.
		LobbyShopPanel* lobbyShopPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingleton().getCurrentLayer());
		if (lobbyShopPanel) {
			//바꾸고
			lobbyShopPanel->ShowShopPanel();
			lobbyShopPanel->SetTapIdx(TAB_RUBY);
		}
		else {
			PanelHelper::pushRubyShopPanel();
		}
		//pushUiPanel(LOBBY_UI_SHOP);
	}
	else if (buttonName == "gomodel") {
		CCLOG("BTN goshop Clicked");
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		//현재창이 샵창이라면 바꾸고 아니라면 push 한다.
		LobbyShopPanel* lobbyShopPanel = dynamic_cast<LobbyShopPanel*>(LayerManager::getSingleton().getCurrentLayer());
		if (lobbyShopPanel) {
			//바꾸고
			lobbyShopPanel->ShowShopPanel();
			lobbyShopPanel->SetTapIdx(TAB_MODEL);
		}
		else {
			PanelHelper::pushModelShopPanel();
		}
		//pushUiPanel(LOBBY_UI_SHOP);
	}
	else if (buttonName == "goexchange") {
		
	}
}

void TicketContentPanel::setData()
{
	refreshData();	
}

void TicketContentPanel::refreshData() 
{
	mTourName = mMainPanel->getLabel("txt_title");
	mTourName->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_CHIP").c_str());
	mTourName->setZOrder(5);
	mTourNameUnder = mMainPanel->getLabel("txt_title_under"); //Under는 텍스트가 좀 더 잘보이게끔 그림자를 넣어준것이라고 이해하면된다.
	mTourNameUnder->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_CHIP").c_str());
	mTourNameUnder->setZOrder(4);
	if (mIdx==0) //칩
	{
		//뚜껑에 이름 설정해주는 부분 텍스트 처리 -> dmy_pannel_ticket에 각각 정리해놓았다.
		//아래 보여지는 이미지 처리하는 부분  
		mTicketImg->setSpriteFrameWithFile("ui/chip.png");
		mTicketImg->fit(mMainPanel->getDummy("dmy_ticket").size);
		ownedChip = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Chip;
		string _tmpChip = commaInsert(ownedChip);
		mTicketAmount->setString(StringConverter::toString(_tmpChip).c_str());

	}

	else if (mIdx == 1) //루비
	{   
		mTicketImg->setSpriteFrameWithFile("ui/ruby.png");
		mTicketImg->fit(mMainPanel->getDummy("dmy_ticket").size);

		mTourName->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_RUBY").c_str());
		mTourNameUnder->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_RUBY").c_str());

		ownedRubby = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_Cash;
		string _tmpRubby = commaInsert(ownedRubby);
		mTicketAmount->setString(StringConverter::toString(_tmpRubby).c_str());

	}

	else if (mIdx == 2) //골드
	{
		mTicketImg->setSpriteFrameWithFile("ui/gold.png");
		mTicketImg->fit(mMainPanel->getDummy("dmy_ticket").size);

		mTourName->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_GOLD").c_str());
		mTourNameUnder->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_GOLD").c_str());
		
		ownedGold = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
		string _tmpGold = commaInsert(ownedGold);
		mTicketAmount->setString(StringConverter::toString(_tmpGold).c_str());

	}

	else if (mIdx == 3) //토큰  
	{
		mTicketImg->setSpriteFrameWithFile("ui/Token_Icon.png");
		mTicketImg->fit(mMainPanel->getDummy("dmy_ticket").size);

		mTourName->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_TOKEN").c_str());
		mTourNameUnder->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_TOKEN").c_str());

		ownedToken = 0;
		mTicketAmount->setString(StringConverter::toString(ownedToken).c_str());

	}

}


string TicketContentPanel::commaInsert(int64 goods)
{
	string _tmpGoods = StringConverter::toString(goods).c_str();
	for (int i = _tmpGoods.size() - 3; i > -1; i -= 3) {
		if (i > 0)
			_tmpGoods.insert(i, ",");
		else
			break;
	}
	return _tmpGoods;
}
