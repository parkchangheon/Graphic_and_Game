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
	void setData();
	bool getCanSum();
private:	
	int mIdx;
	int mTicketId;
	W_TourTicketInfo mTicketInfo;
	Panel* mMainPanel;
	CCSize mContentSize;		
	
	//Panel* mButtonPanel;
	//Panel* mButtonPanel2;
	
	//갈수있는 지역 이름
	Nx::Label* mTourName;
	Nx::Label* mTourNameUnder;
	//보유 갯수
	Nx::Label* mTicketAmount;
	
	Widget* mTicketImg;	

	Widget* mRubbyImg;
	Widget* mGoldImg;
	Widget* mChipImg; 
	Widget* mTokenImg;

	Nx::Label* mStepLabel;

	Button* mSelectBtn;
	Button* mSummaryBtn;
	Nx::Label* mSelectBtnLabel;
	Nx::Label* mSelectBtnUnderLabel;
	Nx::Label* mSummaryBtnLabel;
	Nx::Label* mSummaryBtnUnderLabel;
	W_TicketData mTicketData;
};
