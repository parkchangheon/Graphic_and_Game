/********************************************************************
file name:	TicketContentPanel.h

purpose:	ticket 정보창 -> 이걸 해외 버전으로 바꾼다리.
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "W_TourTicketInfo.pb.h"
#include "W_TicketData.pb.h"

class TicketContentPanel : public Panel, public Button::Listener
{	
public:	
	TicketContentPanel(int idx);
	virtual ~TicketContentPanel();

public:
	virtual void onClicked(const string& buttonName);

	void refreshData();

private:
	void initPanel();			
	void initButtonPanel();
	void setData();
private:	
	int mIdx;
	int mTicketId;
	W_TourTicketInfo mTicketInfo;
	Panel* mMainPanel;
	CCSize mContentSize;		
	
	Panel* mButtonPanel;  //샵으로 가라는 패널
	Panel* mButtonPanel2; //모델로 가라는 패널 
	Panel* mButtonPanel3; //토큰 교환하라는 패널
	
	//갈수있는 지역 이름
	Nx::Label* mTourName;
	Nx::Label* mTourNameUnder;
	//보유 갯수
	Nx::Label* mTicketAmount; //웬지 보유 티켓 같은데 비슷하게 만들어보자
	
	Nx::Label* mChipAmount;
	Nx::Label* mRubbyAmount;
	Nx::Label* mGoldAmount;
	Nx::Label* mTokenAmount;

	Widget* mTicketImg;	

	Widget* mRubbyImg;
	Widget* mGoldImg;
	Widget* mChipImg; 
	Widget* mTokenImg;

	Nx::Label* mStepLabel;

	Button* mSelectBtn;
	Button* mSummaryBtn;

	Button* mGoShopBtn;
	Button* mGoModelBtn;
	Button* mGoExchangeBtn;

	Nx::Label* mSelectBtnLabel;
	Nx::Label* mSelectBtnUnderLabel;
	Nx::Label* mSummaryBtnLabel;
	Nx::Label* mSummaryBtnUnderLabel;

	Nx::Label* mGoShopBtnLabel;
	Nx::Label* mGoShopBtnUnderLabel;
	Nx::Label* mGoModelBtnLabel;
	Nx::Label* mGoModelBtnUnderLabel;
	Nx::Label* mGoExchangeBtnLabel;
	Nx::Label* mGoExchangeBtnUnderLabel;


	W_TicketData mTicketData;
};
