#pragma once

#include "NxFramework.h"

enum CardPanelType
{
	CARD_SHOP_TYPE,
	CARD_INVEN_TYPE
};

static const string BUY_CARD_BTN_SEND_MSG = "BUY_CARD_BTN";

typedef vector<Button*> ButtonContainer;

class CardPanel : public Panel, public Button::Listener
{
public:
	CardPanel();
	virtual ~CardPanel();

	void InitPanel();
	void InitImage();
	void initButton();

	virtual void onClicked(const string& name);

	void SetGoodsType(CardPanelType _type);
	void SetBtnText(string _text);

	void setIndex(int idx);
	void cellTouch(const CCPoint& touchPoint);

private:
	void _cellTouchEnd(CCNode* node);
	bool isCardMoneyType();	//이 캐릭터는 돈으로 사는 캐릭이다.
public:
	Nx::Label* m_Spec;	
	Nx::Label* mCenteTitle;
	CCPoint mTopPos;
	CCPoint mBottomPos;
	CCPoint mCenterPos;

	Nx::Label* m_DayLimit;
	Nx::Label* m_Name;
	Nx::Label* m_DiscountUnder;
	Nx::Label* m_Discount;
	Nx::Label* m_OverlapNotice;

	Panel* m_ButtonPanel;	
	Button* m_OkBtn;

	SkelObject* m_GoodsPanel;
	SkelObject* m_Cover;
	SkelObject* m_HotMark;
	SkelObject* mDisCount;
	Widget* mCharacter;

	Widget* mCharacterChoice;
	Nx::Label* mFirstBuyDesc;
	Nx::Label* mFirstBuyDescUnder;

private:
	CardPanelType m_panelType;
	ButtonContainer mButtons;
	int mIdx;
	Widget* mCoverImg;
};
