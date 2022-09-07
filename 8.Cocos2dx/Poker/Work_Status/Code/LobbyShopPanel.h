/********************************************************************
file name:	LobbyShopPanel.h

purpose:	로비씬에서 상점 버튼 눌렀을때  상점 관련 구조창
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "TockInvtationPanel.h"
#include "CharacterListPartPanel.h"
#include "ShopTicketContentPanel.h"
#include "SmallButtonPanel.h"
#include "NotiWidget.h"
#include "CardListPartPanel.h"
#include "ModelListPartPanel.h"

#define SHOP_MEMEBER_CELL_SIZE 410.f
#define SHOP_CELL_MAX 8

//#define TEST_CELL_SIZE 16
enum TAP_KINDS
{
	TAB_CHARACTER = 0,
	TAB_MEBERSHIP,
	TAB_RUBY,
	TAB_CARD,
	TAB_MODEL,
};



class LobbyShopPanel : public Panel, public Button::Listener , public Nx::Layer::Listener
{
	typedef vector<NotiWidget*> NotiWidgetContainer;
public:
	LobbyShopPanel();
	virtual ~LobbyShopPanel();

	void InitPanel();
	void InitImage();
	void initButton();
// CCTargetedTouchDelegate
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
	virtual void onEnter() override;
	virtual void onRefresh();
	virtual void onLayerMessage(const string& msg);
    void resume();
public:
	void ClickTapButton(int _idx , bool playSound = true);
	virtual bool handling(STCMD &stCmd);
	void update(float dt);
	void ShowShopPanel();
	void HideShopPanel();
	void ShowShopUi();
	void HideShopUi();
	void ShowShopTitie();
	void HideShopTitie();

	//void SetCharacterShopList();
	//void ClearCharacterShopList();
	
	void SetMembershipShop();
	void ClearMembershipShopList();

	void SetRubyShopList();
	void ClearRubyShopList();

	void ClearShopList();

	void SetTapIdx(int idx);
	void SetShopVipInfo();

	void setCharacterBuy(int characterId);

private:
	void ScrollViewOffsetProcess(float _dt);

	bool cellTouchStart(const CCPoint& tableTouchPoint);
	bool cellTouchCancel(const CCPoint& tableTouchPoint);
	bool cellTouch(const CCPoint& tableTouchPoint);
	void cellTouchEnd(CCNode* node);

	
	//void CreateCharacterCell(int _size);
	void CreateClassShopCell();
	void CreateRubyCell(int _size);

	//void UpdateCharacterShopList(int _toIdx, int _dstIdx);
	void UpdateRubyShopList(int _toIdx, int _dstIdx);

	void SetBuyPopup(int _index);
	void SetShopVipXpBar(int _per);

	void InitShopPanel();
	void InitTapButtonPanel();
	void InitRubyShopPanel();
	void InitMemberShipPanel();
	void initCharacterShopPanel();
	void initCardShopPanel();
	void initModelShopPanel();
	void MoveCellUpdate(int _moveV);

private:
	
	void sendWPayReserveReq(int cashId);
	void recvWPayReserveRes(HttpMessage* msg);

	void refreshMemberShip();
	void updateNotiWidget();

public:
	void sendW_PayReq(string tID, string txId, string receipt);
	void recvW_PayRes(HttpMessage* msg);
	bool mLoginProcess;

	int m_ViewDataIndex;
	CCScrollView* m_pShopListView;
	CCLayer* m_pShopListContainer;

	bool m_bTouchCancel;


	Button* m_TapBtn[5];
	Panel* m_TapBtnPanel[5];
	Panel* m_ListCell[SHOP_CELL_MAX];
	Panel* m_ListBtnCell[SHOP_CELL_MAX];
	ShopTicketContentPanel* mRubyTickerPanel[SHOP_CELL_MAX];
	
	Panel* m_MemberShipPanel;
	Panel* m_RubyShopPanel;

	Panel* m_memberCard[2];
	Panel* m_modelShopPanel;
	ShopTicketContentPanel* mSilverTicketPanel;
	ShopTicketContentPanel* mGoldTicketPanel;;


	int m_TapIndex;

	SkelObject* m_ShopTitleLabel;
	SkelObject* m_ShopTitleMark;
	SkelObject* m_ShopTitleBg;
	SkelObject* m_ShadowBg;

	SkelObject* m_pVipMark;
	SkelObject* m_pVipSum;
	SkelObject* m_pExpBarLeft;
	SkelObject* m_pExpBarCenter;
	SkelObject* m_pExpBarRight;
	Nx::Label* m_pVipExp;

	int m_CellIndex;
	bool m_bMovingCell;
	float m_fMoveG;
	Panel* mGoldAdPanel;
	CharacterListPartPanel* mCharacterShopPanel;
	ModelListPartPanel* mModelTabPanel;
	int mBuyCashId;

	Nx::Label* mMemberShipLeftTimeLabel;
	Nx::Label* mMemberShipRightTimeLabel;

	SmallButtonPanel* mMemberSilverBtn;
	SmallButtonPanel* mMemberGoldBtn;

	CCSize mRubyCellSize;

	CCPoint mTopPos;
	CCPoint mBottomPos;
	CCPoint mCenterPos;

	CardListPartPanel* mCardListShopPanel;

	string mGoogleTid;
	NotiWidgetContainer mNotiWidgets;
};