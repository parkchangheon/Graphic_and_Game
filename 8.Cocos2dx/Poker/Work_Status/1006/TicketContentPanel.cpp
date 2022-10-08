#include "pch.h"
#include "TicketContentPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"


TicketContentPanel::TicketContentPanel(int idx)
{
	mIdx = idx;
	mTicketData.CopyFrom(GameDataManager::getSingleton().GetGameDataPtr()->ticketdata(idx));
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
	
	//mTourName = mMainPanel->getLabel("txt_title");
	//mTourNameUnder = mMainPanel->getLabel("txt_title_under");
	mTicketAmount = mMainPanel->getLabel("txt_have2");	
	mTicketImg = mMainPanel->getImage("dmy_ticket"); 

	mChipImg = mMainPanel->getImage("dmy_chip");
	mGoldImg = mMainPanel->getImage("dmy_gold");
	mTokenImg = mMainPanel->getImage("dmy_token"); 
	mRubbyImg = mMainPanel->getImage("dmy_ruby");
	mStepLabel = mMainPanel->getLabel("txt_number");  

	mButtonPanel = nullptr;
	mButtonPanel2 = nullptr;
	mButtonPanel3 = nullptr;

	mGoShopBtn = nullptr;
	mGoModelBtn = nullptr;
	mGoExchangeBtn = nullptr;
	//보유갯수
	mMainPanel->getLabel("txt_have")->setString(GameStringDepot::getSingletonPtr()->getString("TicketContentPanel_GETCOUNT_TITLE").c_str());
}

void TicketContentPanel::initButtonPanel()
{
	CCPoint _btnPos = mMainPanel->getDummy("dmy_button_small").origin;

	if (mTicketData.movetype() == 1 || mTicketData.movetype() == 2) //칩
	{
		mButtonPanel = new Panel();
		mButtonPanel->construct(getMxmlPath() + "dmy_button_small.mxml");
		mButtonPanel->setPositionX(_btnPos.x);
		mButtonPanel->setPositionY(-_btnPos.y + 20);
		mMainPanel->addChild(mButtonPanel);
		mButtonPanel->release();

		mGoShopBtn = mButtonPanel->getButton("sbtn_button");
		mGoShopBtnLabel = mButtonPanel->getLabel("txt_goshop_button");
		mGoShopBtnUnderLabel = mButtonPanel->getLabel("txt_goshop_under");
		mGoShopBtn->setListener(this);
		mGoShopBtn->setName("goshop");

		mGoShopBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_BUY_UNIT").c_str());
		mGoShopBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("TXT_BUY_UNIT").c_str());
		
		mTourName = mMainPanel->getLabel("txt_chip_title");
		mTourName->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_CHIP").c_str());
	}

	if (mTicketData.movetype() == 3) //칩
	{
		//go model
		mButtonPanel2 = new Panel();
		mButtonPanel2->construct(getMxmlPath() + "dmy_button_small.mxml");
		mButtonPanel2->setPositionX(_btnPos.x);
		mButtonPanel2->setPositionY(-_btnPos.y + 10);
		mMainPanel->addChild(mButtonPanel2);
		mButtonPanel2->release();

		mGoModelBtn = mButtonPanel2->getButton("sbtn_button");
		mGoModelBtnLabel = mButtonPanel2->getLabel("txt_gomodel_button");
		mGoModelBtnUnderLabel = mButtonPanel2->getLabel("txt_gomodel_under");
		mGoModelBtn->setListener(this);
		mGoModelBtn->setName("gomodel");

		mGoModelBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_BUY_MODEL").c_str());
		mGoModelBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("TXT_BUY_MODEL").c_str());
	}


	if (mTicketData.movetype() == 4) //칩
	{
		//go exchange
		mButtonPanel3 = new Panel();
		mButtonPanel3->construct(getMxmlPath() + "dmy_button_small.mxml");
		mButtonPanel3->setPositionX(_btnPos.x);
		mButtonPanel3->setPositionY(-_btnPos.y + 40);
		mMainPanel->addChild(mButtonPanel3);
		mButtonPanel3->release();

		mGoExchangeBtn = mButtonPanel3->getButton("sbtn_button");
		mGoExchangeBtnLabel = mButtonPanel3->getLabel("txt_goexchange_button");
		mGoExchangeBtnUnderLabel = mButtonPanel3->getLabel("txt_goexchange_under");
		mGoExchangeBtn->setListener(this);
		mGoExchangeBtn->setName("goexchange");

		mGoExchangeBtnLabel->setString(GameStringDepot::getSingleton().getString("TXT_EXCHANGE_TOKEN").c_str());
		mGoExchangeBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("TXT_EXCHANGE_TOKEN").c_str());
	}
}


void TicketContentPanel::onClicked(const string& buttonName)
{
	if (buttonName == getButtonName(mGoShopBtn)) {
		fireMessage("Click go shop btn");
	}
	if (buttonName == getButtonName(mGoModelBtn)) {
		//fireMessage("Click go model btn");
		CCLOG("I Click GoModel");
	}
	if (buttonName == getButtonName(mGoExchangeBtn)) {
		fireMessage("Click go exchange btn");
	}
}

void TicketContentPanel::setData()
{
	//사진 뿌리고   
	//string ticketImgStr = "ui/" + mTicketData.image() + ".png";  
	//mTicketImg->setSpriteFrameWithFile(ticketImgStr);  
	//mTicketImg->fit(mMainPanel->getDummy("dmy_ticket").size);
	//step 뿌린다
	//string stepStr = NxGetFormatString(GameStringDepot::getSingleton().getString("TICKET_STEP_DESC"), mTicketData.step());
	//mStepLabel->setString(stepStr.c_str());
	//지역 이름 뿌린다.
	//mTourName->setString(mTicketData.name().c_str());
	//mTourNameUnder->setString(mTicketData.name().c_str());
	refreshData();	
}

void TicketContentPanel::refreshData() 
{
	//보유 갯수
	int ticketCount = GameDataManager::getSingleton().getTicketCount(mTicketData.id());
	mTicketAmount->setString(StringConverter::toString(ticketCount).c_str());

	bool isOpenFlag = ticketCount > 0;

	if (mTicketData.movetype()==1) //칩
	{
		//뚜껑에 이름 설정해주는 부분 텍스트 처리 -> dmy_pannel_ticket에 각각 정리해놓았다.
		mTourName = mMainPanel->getLabel("txt_chip_title");
		mTourName->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_CHIP").c_str());
		mTourName->setZOrder(5);
		mTourNameUnder = mMainPanel->getLabel("txt_chip_under"); //Under는 텍스트가 좀 더 잘보이게끔 그림자를 넣어준것이라고 이해하면된다.
		mTourNameUnder->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_CHIP").c_str());
		mTourNameUnder->setZOrder(4);


		//아래 보여지는 이미지 처리하는 부분
		string _chipImgStr = "ui/chip.png";  
		mChipImg->setSpriteFrameWithFile(_chipImgStr);
		mChipImg->fit(mMainPanel->getDummy("dmy_chip").size);

	}

	else if (mTicketData.movetype() == 2) //루비
	{   
		mTourName = mMainPanel->getLabel("txt_ruby_title");
		mTourName->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_RUBY").c_str());
		mTourName->setZOrder(5);
		mTourNameUnder = mMainPanel->getLabel("txt_ruby_under");
		mTourNameUnder->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_RUBY").c_str());
		mTourNameUnder->setZOrder(4);

		string _rubbyImgStr = "ui/ruby.png"; 
		mRubbyImg->setSpriteFrameWithFile(_rubbyImgStr); 
		mRubbyImg->fit(mMainPanel->getDummy("dmy_ruby").size);  

	}

	else if (mTicketData.movetype() == 3) //골드
	{
		mTourName = mMainPanel->getLabel("txt_gold_title");
		mTourName->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_GOLD").c_str());
		mTourName->setZOrder(5);
		mTourNameUnder = mMainPanel->getLabel("txt_gold_under");
		mTourNameUnder->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_GOLD").c_str());
		mTourNameUnder->setZOrder(4);

		string _goldImgStr = "ui/gold.png";
		mGoldImg->setSpriteFrameWithFile(_goldImgStr);
		mGoldImg->fit(mMainPanel->getDummy("dmy_gold").size);  

	}

	else if (mTicketData.movetype() == 4) //토큰  
	{
		mTourName = mMainPanel->getLabel("txt_token_title");
		mTourName->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_TOKEN").c_str());
		mTourNameUnder = mMainPanel->getLabel("txt_token_under");
		mTourName->setZOrder(5);
		mTourNameUnder->setString(GameStringDepot::getSingletonPtr()->getString("OWNED_GOODS_TOKEN").c_str());
		mTourNameUnder->setZOrder(4);

		string _tokenImgStr = "ui/" + mTicketData.image() + ".png";
		mTokenImg->setSpriteFrameWithFile(_tokenImgStr);
		mTokenImg->fit(mMainPanel->getDummy("dmy_token").size);  

	}


	/*bool canSum = getCanSum();*/
	//bool canDisplaySum = mTicketData.movetype() < 4;
	//if (isOpenFlag) {
	//	mSelectBtnLabel->setString(GameStringDepot::getSingleton().getString("TICKET_MOVE").c_str());
	//	mSelectBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("TICKET_MOVE").c_str());
	//}
	//else {
	//	mSelectBtnLabel->setString(GameStringDepot::getSingleton().getString("TICKET_NO_MOVE").c_str());
	//	mSelectBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("TICKET_NO_MOVE").c_str());
	//}
	//mSelectBtn->setEnable(isOpenFlag);
	//mSelectBtn->setGrayscale(!isOpenFlag);
	////canSum = true;
	//if (canSum) {
	//	mSummaryBtnLabel->setString(GameStringDepot::getSingleton().getString("TICKET_SUM").c_str());
	//	mSummaryBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("TICKET_SUM").c_str());
	//}
	//else {
	//	mSummaryBtnLabel->setString(GameStringDepot::getSingleton().getString("TICKET_NO_SUM").c_str());
	//	mSummaryBtnUnderLabel->setString(GameStringDepot::getSingleton().getString("TICKET_NO_SUM").c_str());
	//}

	//mSummaryBtnUnderLabel->setVisible(canDisplaySum);
	//mSummaryBtnLabel->setVisible(canDisplaySum);

	//mSummaryBtn->setVisible(canDisplaySum);
	//mSummaryBtn->setEnable(canSum && canDisplaySum);
	//mSummaryBtn->setGrayscale(!canSum);
}

//bool TicketContentPanel::getCanSum()
//{
//	int ticketCount = GameDataManager::getSingleton().getTicketCount(mTicketData.id());
//	bool result = false;
//	//추후 확장성을 위한 스위치문
//	switch (mTicketData.movetype())
//	{
//	case 1: //프로페셔널 1R 티켓
//		result = ticketCount >= 10;
//		break;
//	case 2://마스터즈 1R 티켓
//		result = ticketCount >= 10;
//		break;
//	case 3://마스터즈 2R 티켓
//		result = ticketCount >= 5;
//		break;
//	default:
//		break;
//	}
//
//	return result;
//}