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
	mStepLabel = mMainPanel->getLabel("txt_number");  
	 
	CCPoint _btnPos = mMainPanel->getDummy("dmy_button_small").origin;
	//mButtonPanel = new Panel();
	//mButtonPanel->construct(getMxmlPath() + "dmy_button_small.mxml");
	//mButtonPanel->setPositionX(_btnPos.x);
	//mButtonPanel->setPositionY(-_btnPos.y);
	//mMainPanel->addChild(mButtonPanel);
	//mButtonPanel->release();

	//mSelectBtn = mButtonPanel->getButton("sbtn_button");
	//mSelectBtnLabel = mButtonPanel->getLabel("txt_button");
	//mSelectBtnUnderLabel = mButtonPanel->getLabel("txt_button_under");
	//mSelectBtn->setListener(this);
	//mSelectBtn->setName("select");

	//mButtonPanel2 = new Panel();
	//mButtonPanel2->construct(getMxmlPath() + "dmy_button_small.mxml");
	//mButtonPanel2->setPositionX(_btnPos.x);
	//mButtonPanel2->setPositionY(-_btnPos.y + 50);
	//mMainPanel->addChild(mButtonPanel2);
	//mButtonPanel2->release();

	//mSummaryBtn = mButtonPanel2->getButton("sbtn_button");
	//mSummaryBtnLabel = mButtonPanel2->getLabel("txt_button");
	//mSummaryBtnUnderLabel = mButtonPanel2->getLabel("txt_button_under");
	//mSummaryBtn->setListener(this);
	//mSummaryBtn->setName("sum");

	//보유갯수
	mMainPanel->getLabel("txt_have")->setString(GameStringDepot::getSingletonPtr()->getString("TicketContentPanel_GETCOUNT_TITLE").c_str());
}

void TicketContentPanel::onClicked(const string& buttonName)
{
	if (buttonName == getButtonName(mSelectBtn)) {
		fireMessage("SELECT_TICKET" + StringConverter::toString(mIdx));
	}
	else if (buttonName == getButtonName(mSummaryBtn)) {
		fireMessage("SUM_TICKET" + StringConverter::toString(mIdx));
	}
}

void TicketContentPanel::setData()
{
	//사진 뿌리고
	string ticketImgStr = "ui/" + mTicketData.image() + ".png";
	mTicketImg->setSpriteFrameWithFile(ticketImgStr);
	mTicketImg->fit(mMainPanel->getDummy("dmy_ticket").size);
	//step 뿌린다
	string stepStr = NxGetFormatString(GameStringDepot::getSingleton().getString("TICKET_STEP_DESC"), mTicketData.step());
	mStepLabel->setString(stepStr.c_str());
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