/********************************************************************
	file name:	PopupPanel.h
	
	purpose:	공통 팝업창 Push 레이어가 아닌 부치는 panel
*********************************************************************/
#pragma once
#include "NxFramework.h"
#include "W_LetterInfo.pb.h"
//#include "TypeDefine.pb.h"

#define PopupOk "PopupOk"
#define PopupCancel "PopupCancel"

class SimplePopupPanel : public Panel, public Button::Listener, public SkelObject::Listener
{
public:
	
	enum SimplePopupType{
		OKNotice,		// OK 버튼 하나만 있는것
		YESNONotice,	// YES, NO 버튼  있는거 ( NO USE 빨간버튼)
		ToastNotice,	// 토스트 있는거
		BigToastNotice,	// 큰 토스트
		AdminNotice,	// admin gongji
		LetterNotice,	// 편지
		ShopYESNONotice,		// SHOP
		MonthlyBuyNotice,		// 맴버쉽권 구입
		ToastBankNotice,	//금과 관련 메세지.
		ToastSeedNotice,									//토너먼트 씨드 메세지
		ToastStayNotice,									//토너먼트 대기 메세지
		ToastCompleteNotice,								//토너먼트 대기 메세지
		ToastVictoryNotice1,	//토너먼트 우승 메세지
		ToastVictoryNotice2,	//토너먼트 준우승 메세지
		ToastVictoryNotice3,	//토너먼트 3등  메세지
		ToastVictoryNotice4,		//토너먼트 4등 이하 메세지
		ToaseLobbyNoMoneyNotice,	//lobby 왔을때 돈이 없을때 나오는 창
		VERSION_NOTICE,				//버전 노티스
		SAFE_MONEY_TYPE,			//보험금 관련창
		MAX_MONEY_TYPE,				//
		//________________________________________ 빨간버튼용
		FRIEND_REMOVE,			//친구삭제(빨간버튼)	
		GAME_END,				//게임엔드(빨간버튼)
		LOG_OUT,				//로그아웃(빨간버튼)
		OK_CERTIFICATION,		// 성인인증
		//________________________________________원스토어 띄우는 창 version
		BUY_AT_ONESTORE,
	};
	
	
	enum PopupBtnType {
		Confirm,
		CancelOk,
	};

	enum ToastAlign {
		TOP,
		VCENTER,
		BOTTOM,
	};

public:
	SimplePopupPanel(SimplePopupType type, const string&text, const string&title = "");
	~SimplePopupPanel();

public: // Button::Listener
	virtual void onClicked(const string& name);
	virtual void onAnimationEnded(const string& ani);

public:
	virtual void onRefresh();
	void TurnOffAdminMessage(float t);
	void TurnOnAdminMessage();
	void RegistTurnOffAdminMessage(float remainDt);
	void RegistTurnOnAdminMessage(float remainDt);
public:
	void setGeneralListener(CCObject* target, ObjectListener listener) { mTarget = target; mGeneralListener = listener; }
public:
	void SetOkEventMsg(string msg);
	void SetCancelEventMsg(string msg);
	void SetExitEventMsg(string msg);
	void SetToastAlign(ToastAlign align);
	
	void ShowPanel(bool isVisible);
	void OnExitEvent();
	void ShowBankStatePopup(string title , string _msg);	//현재 금고에는 얼마가 있습니다.
	void showMaxMoneyPopup(string title, string _msg);

	void UpdateStayTimeLabel(std::string _time);
	void GuideboxCloseEvent();
	bool isGameEndType();
	bool isGuideType();			//팝업이지만 실직적으론 addchild 같은 거라 lobbyui 엥서 onclick 안 눌러ㅈ져도 된다.
	void setLayerActivate(bool activate);	//vislble false 될때 action 도 같이 멈추고 재생시킨다.

private:
	void InitChangeSeedPopup();
	void InitBankStatePopup();
	void initLobbyBankPopup();
	void initBankSafePopup(string text , string title);
	void initPanel();
	void initDesc(const string& text);	//각 string data 및 visible init
	void setTextType();
	void setUseNotice(bool flag);
	void clearThisPanel();
	void ExeEvent();
	void SetTitle(string _title);
	void SetContents(string _content);
	void ShowBackPanel(bool _visible);
	void ShowVictoryPopup(string _msg, string _gold, int _rank);
	void ShowMiddlePopup(string _msg);
	void ShowSeedChangePopup(string _msg);
	void ShowMoveCompletePopup(string _msg);

private:
	CCObject* mTarget;
	ObjectListener mGeneralListener;

	std::string mContentsStr;
	SimplePopupType mType;
	Nx::Label* mDesc;			// 내용

	Button* mMiddleOkBtn;
	Button* mOkBtn;
	Button* mCancelBtn;
	Panel* m_pBtnPanel[3];
	Button* mExitBtn;

	string	mOkEventMsg;
	string	mCancelEventMsg;
	string	mExitEventMsg;

	SkelObject * mBoard;
	string	mEventName;

	ToastAlign mToastAlign;

	Script * mAdminText;

	bool mActivatge;
public:
	int RemainFromStart;
	int RemainFromEnd;
};
