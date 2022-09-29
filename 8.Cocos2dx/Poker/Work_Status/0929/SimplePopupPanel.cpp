#include "pch.h"
#include "SimplePopupPanel.h"
#include "HeroUtil.h"
#include "GameStringDepot.h"
#include "GameDataManager.h"
#include "LobbyUIPanel.h"
#include "SceneUtil.h"
#include "GameService.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/AndroidUtilManager.h"
#endif

SimplePopupPanel::SimplePopupPanel(SimplePopupType type, const string&text, const string&title) : Panel("PopupPanel")
{
	mActivatge = false;
	mType = type;
	mTarget = NULL;
	mGeneralListener = NULL;
	mToastAlign = ToastAlign::TOP;

	mOkEventMsg = PopupOk;
	mCancelEventMsg = PopupCancel;
	mExitEventMsg = PopupCancel;

	if (mType == ToastBankNotice)
	{
		InitBankStatePopup();
		ShowBankStatePopup(title , text);
	}
	else if (mType == ToastSeedNotice)
	{
		InitChangeSeedPopup();
		ShowSeedChangePopup(text);
	}
	else if (mType == ToastStayNotice)
	{
		InitChangeSeedPopup();
		ShowMiddlePopup(text);
	}
	else if (mType == ToastCompleteNotice)
	{
		InitChangeSeedPopup();
		ShowMoveCompletePopup(text);
	}
	else if (mType == ToastVictoryNotice1)
	{
		InitChangeSeedPopup();
		ShowVictoryPopup(text, title, 1);
	}
	else if (mType == ToastVictoryNotice2)
	{
		InitChangeSeedPopup();
		ShowVictoryPopup(text, title, 2);
	}
	else if (mType == ToastVictoryNotice3)
	{
		InitChangeSeedPopup();
		ShowVictoryPopup(text, title, 3);
	}
	else if (mType == ToastVictoryNotice4)
	{
		InitChangeSeedPopup();
		ShowVictoryPopup(text, title, 4);
	}
	else if (mType == ToaseLobbyNoMoneyNotice) {		
		initLobbyBankPopup();
		ShowBankStatePopup(title , text);
	}	
	else if (mType == MAX_MONEY_TYPE) {
		initLobbyBankPopup();
		showMaxMoneyPopup(title, text);
	}
	else if (mType == SAFE_MONEY_TYPE) {
		initBankSafePopup(text, title);
	}
	else
	{
		initPanel();
		initDesc(text);
		SetTitle(title);

		setTextType();
		ShowPanel(true);
	}
	
}

SimplePopupPanel::~SimplePopupPanel()
{
	if(mType == AdminNotice)
		CCLOG("SImplepopup delete");
	//destruct();
}

void SimplePopupPanel::InitChangeSeedPopup()
{
	//addMouseBlockPanel(this, true);
	construct(getMxmlPath() + "dmy_guide_bar.mxml");
	//0708
	//ShowBackPanel(false);
	getLabel("txt_rank_sum")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	

	getLabel("txt_rank_sum")->setVisible(false);
	
	
	getSkel("skel_guidebar_large")->setVisible(false);
	getSkel("skel_guidebar_large")->pauseAnimation();
	getSkel("skel_guidebar_middle")->setVisible(false);
	getSkel("skel_guidebar_middle")->pauseAnimation();	
}

void SimplePopupPanel::ShowVictoryPopup(string _msg, string _gold, int _rank)
{
	//0708
	//getSkel("skel_logeffect2")->setVisible(true);
	//getSkel("skel_logeffect3")->setVisible(true);

	//0708
	//getLabel("txt_victory")->setString(_msg.c_str());
	//getLabel("txt_victory")->setVisible(true);

	setOpacity(0);
	setVisible(true);

	getSkel("skel_guidebar_large")->setVisible(true);
	getSkel("skel_guidebar_large")->playAnimation("guidebar2_start");

	switch (_rank)
	{
	case 1:
		//0708
		//getSkel("skel_victory_mark")->setSkin("victory");
		//getSkel("skel_victory_mark")->playAnimation("victory");
		//getSkel("skel_victory_mark")->setVisible(true);
		//getLabel("txt_victory_gold")->setString(_gold.c_str());
		//getLabel("txt_victory_gold")->setVisible(true);
		break;
	case 2:
		//getSkel("skel_victory2_mark")->playAnimation("victory2");
		//getSkel("skel_victory2_mark")->setVisible(true);
		//getLabel("txt_victory_gold")->setString(_gold.c_str());
		//getLabel("txt_victory_gold")->setVisible(true);
		break;
	case 3:
		//getSkel("skel_victory2_mark")->playAnimation("victory3");
		//getSkel("skel_victory2_mark")->setVisible(true);
		//getLabel("txt_victory_gold")->setString(_gold.c_str());
		//getLabel("txt_victory_gold")->setVisible(true);
		break;
	case 4:
		//0708
		//getSkel("skel_blank")->setVisible(true);
		//getLabel("txt_rank_sum")->setVisible(true);
		//getLabel("txt_rank_sum")->setString(_gold.c_str());
		break;
	}

	stopAllActions();
	mActivatge = true;
	runAction(CCSequence::create(
		CCFadeIn::create(0.1f),
		CCDelayTime::create(3.f),
		CCFadeOut::create(0.1f),
		CCCallFunc::create(this, callfunc_selector(SimplePopupPanel::clearThisPanel)),
		NULL));
}

void SimplePopupPanel::ShowSeedChangePopup(string _msg)
{
	//0708
	//getSkel("skel_logeffect2")->setVisible(true);
	//getSkel("skel_logeffect3")->setVisible(true);

	//0708
	//string msgText = GameStringDepot::getSingleton().getString("TXT_CHANGE_SEED_MONEY1");
	//getLabel("txt_guide")->setString(msgText.c_str());
	//getLabel("txt_guide")->setVisible(true);

	//0708
	//getLabel("txt_guidegold")->setString(_msg.c_str());
	//getLabel("txt_guidegold")->setVisible(true);

	setOpacity(0);
	setVisible(true);

	getSkel("skel_guidebar_large")->setVisible(true);
	getSkel("skel_guidebar_large")->playAnimation("guidebar2_start");
	
	//0708
	//getSkel("skel_guide_mark")->setSkin("bet_up");
	//getSkel("skel_guide_mark")->setVisible(true);

	stopAllActions();
	mActivatge = true;
	runAction(CCSequence::create(
		CCFadeIn::create(0.1f),
		CCDelayTime::create(2.f),
		CCFadeOut::create(0.1f),
		CCCallFunc::create(this, callfunc_selector(SimplePopupPanel::clearThisPanel)),
		NULL));
}

void SimplePopupPanel::ShowMoveCompletePopup(string _msg)
{
	//0708
	//getSkel("skel_logeffect1")->setVisible(true);

	//0708 TODO
	{
// 		getLabel("txt_stay")->setString(_msg.c_str());
// 		getLabel("txt_stay")->setVisible(true);
// 
// 		float _txtPosY = getLabel("txt_stay")->getPositionY();
// 		getLabel("txt_stay")->setPositionY(_txtPosY + 50.f);
	}

	setOpacity(0);
	setVisible(true);

	getSkel("skel_guidebar_middle")->setVisible(true);
	getSkel("skel_guidebar_middle")->playAnimation("guidebar1_start");
	getSkel("skel_guidebar_middle")->appendAnimation("guidebar1_loop");

	stopAllActions();
	mActivatge = true;
	runAction(CCSequence::create(
		CCFadeIn::create(0.1f),
		CCDelayTime::create(1.5f),
		CCFadeOut::create(0.1f),
		CCCallFunc::create(this, callfunc_selector(SimplePopupPanel::clearThisPanel)),
		NULL));
}

void SimplePopupPanel::ShowMiddlePopup(string _msg)
{
	//0708
	//getSkel("skel_logeffect1")->setVisible(true);

	//7006 txt_stay
	//getLabel("txt_stay")->setString(_msg.c_str());
	//getLabel("txt_stay")->setVisible(true);
	
	setOpacity(0);
	setVisible(true);

	getSkel("skel_guidebar_middle")->setVisible(true);
	getSkel("skel_guidebar_middle")->playAnimation("guidebar1_start");
	getSkel("skel_guidebar_middle")->appendAnimation("guidebar1_loop");
	
	//getSkel("skel_stay_mark")->setVisible(true);

	stopAllActions();
	runAction(CCFadeIn::create(0.1f));
	
}

void SimplePopupPanel::InitBankStatePopup()
{
	addMouseBlockPanel(this, true);
	construct(getMxmlPath() + "dmy_up_panel.mxml");
	getLabel("txt_bank_guide")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getSkel("skel_up_panel")->playAnimation("up_panel_start");
	getSkel("skel_up_panel")->appendAnimation("up_panel_stay");
	getLabel("txt_level_gift")->setVisible(false);
	getLabel("txt_level_next")->setVisible(false);	
	getImage("dmy_up_panel")->setVisible(false);
}

void SimplePopupPanel::ShowBankStatePopup(string title , string _msg)
{
	getLabel("txt_bank_guide")->setVisible(true);
	getLabel("txt_gold")->setVisible(true);
	getLabel("txt_bank_guide")->setString(title.c_str());
	getLabel("txt_gold")->setString(_msg.c_str());
	setOpacity(0);	
	stopAllActions();

	setVisible(true);
	mActivatge = true;
	runAction(CCSequence::create(
		CCFadeIn::create(0.1f),
		CCDelayTime::create(3.f),
		CCFadeOut::create(0.1f),
		CCCallFunc::create(this, callfunc_selector(SimplePopupPanel::clearThisPanel)),
		NULL));
}

void SimplePopupPanel::onClicked(const string& name)
{
	//SoundManager::getSingleton().playEffect(BTN_CLICK);

	mEventName = name;
	if (mType == SAFE_MONEY_TYPE) {
		clearThisPanel();
	}
	else {
		ShowPanel(false);

	}
}

void SimplePopupPanel::ShowBackPanel(bool _visible)
{
	getSkel("skel_backcolor")->setVisible(_visible);
}

void SimplePopupPanel::ShowPanel(bool isVisible)
{
	m_pBtnPanel[0]->setVisible(false);
	mMiddleOkBtn->setEnable(false);
	m_pBtnPanel[1]->setVisible(false);
	mCancelBtn->setEnable(false);
	m_pBtnPanel[2]->setVisible(false);
	mOkBtn->setEnable(false);
	mDesc->setVisible(false);

	mExitBtn->setVisible(true);
	mExitBtn->setEnable(true);
	mExitBtn->setListener(this);

	if (mAdminText != nullptr)
		mAdminText->setVisible(false);

	if (isVisible)
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_POPUPOPEN);

	if (mType == OKNotice)
	{
		getSkel("skel_toastbar")->setVisible(false);

		mExitBtn->setVisible(false);
		mExitBtn->setEnable(false);

		if (isVisible)
		{
			//mBoard->playAnimation("notice_small1_start");
			//mBoard->appendAnimation("notice_small1_loop");
			m_pBtnPanel[0]->setVisible(true);
			mMiddleOkBtn->setEnable(true);
			mMiddleOkBtn->setListener(this);
			mDesc->setVisible(true);
			GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SIMPLE_POPUP);
		}
		else
		{
			//mBoard->playAnimation("notice_small1_end");
			GameDataManager::getSingletonPtr()->PopUiState();
			ExeEvent();
		}
			
	}
	else if (mType == VERSION_NOTICE)
	{
		getSkel("skel_toastbar")->setVisible(false);
		if (isVisible)
		{
			//mBoard->playAnimation("notice_small1_start");
			//mBoard->appendAnimation("notice_small1_loop");
			m_pBtnPanel[0]->setVisible(true);
			mMiddleOkBtn->setEnable(true);
			mMiddleOkBtn->setListener(this);
			mDesc->setVisible(true);
			GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SIMPLE_POPUP);
		}
		else
		{
			//mBoard->playAnimation("notice_small1_end");
			GameDataManager::getSingletonPtr()->PopUiState();
			ExeEvent();
		}

	}
	else if (mType == GAME_END || mType == FRIEND_REMOVE || mType == LOG_OUT)
	{
		getSkel("skel_toastbar")->setVisible(false);
		if (isVisible)
		{
			m_pBtnPanel[1]->setVisible(true);
			string buttonStr = "";
			mOkBtn->setSkelAnimation("button_small_r");
			switch (mType)
			{
			case SimplePopupPanel::FRIEND_REMOVE:
				buttonStr = GameStringDepot::getSingleton().getString("TXT_LETTER_DELETE_UNIT");
				//버튼 이름 수정
				break;
			case SimplePopupPanel::GAME_END:
				buttonStr = GameStringDepot::getSingleton().getString("TXT_GAME_END_LABEL");
				//버튼 이름 수정
				break;
			case SimplePopupPanel::LOG_OUT:
				buttonStr = GameStringDepot::getSingleton().getString("TXT_LOGOUT_UNIT");
				//버튼 이름 수정
				break;
			default:
				break;
			}
			m_pBtnPanel[2]->getLabel("txt_button_under")->setString(buttonStr.c_str());
			m_pBtnPanel[2]->getLabel("txt_button")->setString(buttonStr.c_str());

			mExitBtn->setVisible(false);
			mExitBtn->setEnable(false);

			mCancelBtn->setEnable(true);
			mCancelBtn->setListener(this);

			m_pBtnPanel[2]->setVisible(true);
			mOkBtn->setEnable(true);
			mOkBtn->setListener(this);
			
			mDesc->setVisible(true);

			GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SIMPLE_POPUP);
		}
		else
		{
			//mBoard->playAnimation("notice_small2_end");
			GameDataManager::getSingletonPtr()->PopUiState();
			ExeEvent();
		}
	}
	else if (mType == YESNONotice)
	{
		getSkel("skel_toastbar")->setVisible(false);
		if (isVisible)
		{
			//mBoard->playAnimation("notice_small1_start");
			//mBoard->appendAnimation("notice_small1_loop");
			m_pBtnPanel[0]->setVisible(true);
			mMiddleOkBtn->setEnable(true);
			mMiddleOkBtn->setListener(this);
			mDesc->setVisible(true);
			GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SIMPLE_POPUP);
		}
		else
		{
			//mBoard->playAnimation("notice_small1_end");
			GameDataManager::getSingletonPtr()->PopUiState();
			ExeEvent();
		}
	}
	else if (mType == BUY_AT_ONESTORE)  //NZ창헌
	{
		getSkel("skel_toastbar")->setVisible(false);
		if (isVisible)
		{
			//mBoard->playAnimation("notice_small1_start");
			//mBoard->appendAnimation("notice_small1_loop");
			m_pBtnPanel[0]->setVisible(true);
			mMiddleOkBtn->setEnable(true);
			mMiddleOkBtn->setListener(this);
			mDesc->setVisible(true);
			GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SIMPLE_POPUP);
		}
		else
		{
			//mBoard->playAnimation("notice_small1_end");
			GameDataManager::getSingletonPtr()->PopUiState();
			ExeEvent();
		}
	}
	else if (mType == ToastBankNotice)
	{
		ShowBackPanel(false);

	}
	else if (mType == ToastNotice || mType == BigToastNotice || mType == AdminNotice )
	{
		getSkel("skel_backcolor")->setVisible(false);
		getSkel("skel_panel")->setVisible(false);
		getSkel("skel_titlelight")->setVisible(false);
		
		getLabel("txt_title")->setVisible(false);
		if (hasElement("txt_title_under"))
			getLabel("txt_title_under")->setVisible(false);

		getButton("sbtn_cancel")->setVisible(false);
		getButton("sbtn_cancel")->setEnable(false);

		mBoard = getSkel("skel_toastbar");
		mBoard->setListener(this);
		
		if (mAdminText != nullptr)
		{
			mAdminText->setPositionX(getSkel("skel_toastbar")->getPositionX());
			mAdminText->setPositionY(getSkel("skel_toastbar")->getPositionY());
		}

		if (mType == ToastNotice)
		{
			mBoard->playAnimation("toastbar1_start");
			mBoard->appendAnimation("toastbar1_loop");
		}
		else
		{
			mBoard->playAnimation("toastbar2_start",true);
			mBoard->appendAnimation("toastbar2_loop",true);
		}

		if (mType != AdminNotice)
		{
			mDesc->setHorizontalAlignment(kCCTextAlignmentCenter);
			ccColor3B fontcolor;
			fontcolor.r = 255;
			fontcolor.g = 228;
			fontcolor.b = 176;
			mDesc->setColor(fontcolor);
		}
	}
	else if(mType == LetterNotice)
	{
		getSkel("skel_toastbar")->setVisible(false);
		if (isVisible)
		{
			m_pBtnPanel[0]->setVisible(true);
			mMiddleOkBtn->setEnable(true);
			mMiddleOkBtn->setListener(this);
			mDesc->setVisible(true);
			GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SIMPLE_POPUP);
		}
		else
		{
			GameDataManager::getSingletonPtr()->PopUiState();
			//mBoard->playAnimation("notice_small1_end");
			ExeEvent();
		}
	}	
	else if (mType == ShopYESNONotice)
	{
		getSkel("skel_toastbar")->setVisible(false);		
		if (isVisible)
		{
			m_pBtnPanel[1]->setVisible(true);
			mCancelBtn->setEnable(true);
			mCancelBtn->setListener(this);

			m_pBtnPanel[2]->setVisible(true);
			mOkBtn->setEnable(true);
			mOkBtn->setListener(this);

			mDesc->setVisible(true);
			mDesc->setHorizontalAlignment(CCTextAlignment::CENTER);
			mDesc->setVerticalAlignment(CCVerticalTextAlignment::TOP);

			GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SIMPLE_POPUP);
		}
		else
		{
			GameDataManager::getSingletonPtr()->PopUiState();
			//mBoard->playAnimation("notice_small2_end");
			ExeEvent();
		}
	}
	else if (mType == MonthlyBuyNotice)
	{
		getSkel("skel_toastbar")->setVisible(false);
		if (isVisible)
		{
			//mBoard->playAnimation("notice_small2_start");
			//mBoard->appendAnimation("notice_small2_loop");
			m_pBtnPanel[1]->setVisible(true);
			mCancelBtn->setEnable(true);
			mCancelBtn->setListener(this);
			
			m_pBtnPanel[2]->setVisible(true);
			mOkBtn->setEnable(true);
			mOkBtn->setListener(this);
			//m_pBtnPanel[2]->getLabel("")->getButtonSkelObject()->setSkin("txt_check");
			mDesc->setVisible(true);
			
			mDesc->setHorizontalAlignment(CCTextAlignment::CENTER);
			mDesc->setVerticalAlignment(CCVerticalTextAlignment::TOP);

			GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SIMPLE_POPUP);
		}
		else
		{
			GameDataManager::getSingletonPtr()->PopUiState();
			//mBoard->playAnimation("notice_small2_end");
			ExeEvent();
		}
	}
	else if (mType == OK_CERTIFICATION)
	{
		getSkel("skel_toastbar")->setVisible(false);

		if (isVisible)
		{
			m_pBtnPanel[0]->setVisible(isVisible);
			mMiddleOkBtn->setEnable(isVisible);
			mMiddleOkBtn->setListener(this);
			mDesc->setVisible(isVisible);
			//mBoard->playAnimation("notice_small1_start");
			//mBoard->appendAnimation("notice_small1_loop");
			GameDataManager::getSingletonPtr()->SetUiState(LOBBY_UI_SIMPLE_POPUP);
		}
		else
		{
			this->setVisible(false);
			//mBoard->playAnimation("notice_small1_end");
			//GameDataManager::getSingletonPtr()->PopUiState();
			//ExeEvent();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			AndroidUtilManager::getSingletonPtr()->ReleaseWebView();
			AndroidUtilManager::getSingletonPtr()->OpenAdultURL(GAMBLE_DEFAULT_URL, GameDataManager::getSingletonPtr()->m_pPlayerData->m_UID, GAMBLE_GAME_IP);
#else
			WebService::getSingletonPtr()->_sendGameDataReq();
#endif
		}
		
	}


}

void SimplePopupPanel::initPanel()
{
	if (!(mType == ToastNotice || mType == BigToastNotice || mType == AdminNotice)) {
		addMouseBlockPanel(this, true);
	}
	else {
		this->setName("PopupPanel_Toast");
		this->makeDynamic();
	}
		
		
	construct(getMxmlPath() + "dmy_checkboard_1.mxml");
	CCSize contentsSize = getDummy("dmy_checkboard_1").size;
	getLabel("txt_title")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));

	//getLabel("txt_shop_colon")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//getLabel("txt_postcount1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//getLabel("txt_postcount2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	//getLabel("txt_postcount3")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	
	for (int _i = 0; _i < 3; _i++)
	{
		m_pBtnPanel[_i] = new Panel();
		m_pBtnPanel[_i]->construct(getMxmlPath() + "dmy_button_small.mxml");
		
		string dmyName = "dmy_button_small" + StringConverter::toString(_i + 1);
		CCPoint _btnPos = getDummy(dmyName).origin;
		_btnPos.y = -_btnPos.y;
		m_pBtnPanel[_i]->setPosition(_btnPos);
		addChild(m_pBtnPanel[_i]);
		m_pBtnPanel[_i]->getLabel("txt_button_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pBtnPanel[_i]->getLabel("txt_button")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		m_pBtnPanel[_i]->release();
	}

	string _okTxt = GameStringDepot::getSingletonPtr()->getString("TXT_OK_LABEL");

	if (mType == VERSION_NOTICE) {
		_okTxt = GameStringDepot::getSingletonPtr()->getString("TXT_MOVE_LABEL");
	}

	string _cancelTxt = GameStringDepot::getSingletonPtr()->getString("TXT_CANCEL_LABEL");

	m_pBtnPanel[0]->getLabel("txt_button_under")->setString(_okTxt.c_str());
	m_pBtnPanel[0]->getLabel("txt_button")->setString(_okTxt.c_str());

	m_pBtnPanel[1]->getLabel("txt_button_under")->setString(_cancelTxt.c_str());
	m_pBtnPanel[1]->getLabel("txt_button")->setString(_cancelTxt.c_str());

	m_pBtnPanel[2]->getLabel("txt_button_under")->setString(_okTxt.c_str());
	m_pBtnPanel[2]->getLabel("txt_button")->setString(_okTxt.c_str());

	mMiddleOkBtn = m_pBtnPanel[0]->getButton("sbtn_button");
	mCancelBtn = m_pBtnPanel[1]->getButton("sbtn_button");
	mOkBtn = m_pBtnPanel[2]->getButton("sbtn_button");
	mExitBtn = getButton("sbtn_cancel");

	mMiddleOkBtn->setName("sbtn_small_single_button");
	mCancelBtn->setName("sbtn_small_button_2_stay1");
	mOkBtn->setName("sbtn_small_button_2_stay2");


	if (mType != ToastNotice && mType != AdminNotice && mType != BigToastNotice)
	{
		mDesc = getLabel("txt_checktext");
		mDesc->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		getLabel("txt_toastext")->setVisible(false);
	}
	else
	{
		mDesc = getLabel("txt_toastext");
		mDesc->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
		getLabel("txt_checktext")->setVisible(false);
	}

	if (mType == OKNotice) {
		mExitBtn->setEnable(false);
		mExitBtn->setVisible(false);
	}
}

void SimplePopupPanel::setTextType()
{
	if (mType != AdminNotice)
		mDesc->setVisible(true);
}

void SimplePopupPanel::initDesc(const string& text)
{
	if (mType == AdminNotice)
	{
		mAdminText = Script::create(text.c_str(), mDesc->getContentSize(), 18);

		addChild(mAdminText);
		
		mAdminText->setPositionX(getSkel("skel_toastbar")->getPositionX());
		mAdminText->setPositionY(getSkel("skel_toastbar")->getPositionY());
		GameDataManager::getSingletonPtr()->NoticePanelDesc = text;

		//mAdminText->setPositionY(this->getPositionY() + getPositionY() + mDesc->getPositionY() - 100);
		mDesc->setVisible(false);
	}
	else
	{
		mAdminText = nullptr;
		mDesc->setString(nxReplaceNewl(text).c_str());
	}
}

void SimplePopupPanel::clearThisPanel()
{
	if(this->isDynamic())
		LayerManager::getSingleton().popLayer(this);
}

void SimplePopupPanel::onRefresh()
{
	setVisible( true );
	if(mActivatge)
		setLayerActivate(true);
}

void SimplePopupPanel::TurnOffAdminMessage(float t)
{
	mBoard->playAnimation("toastbar2_end");
	GameDataManager::getSingletonPtr()->NoticePanelDesc = "";
	//GameDataManager::getSingletonPtr()->isNoticePanelExist = false;
}

void SimplePopupPanel::TurnOnAdminMessage()
{
	CCLOG("asdasdasdas");
	LayerManager::getSingleton().pushDynamicLayer(this, DYNAMIC_PUSH_LAYER);
}


void SimplePopupPanel::RegistTurnOnAdminMessage(float remainDt)
{
	runAction(CCSequence::create(
		CCDelayTime::create(remainDt),
		CCCallFunc::create(this, callfunc_selector(SimplePopupPanel::TurnOnAdminMessage)),
		NULL));
}

void SimplePopupPanel::RegistTurnOffAdminMessage(float remainDt)
{
	this->scheduleOnce(schedule_selector(SimplePopupPanel::TurnOffAdminMessage), remainDt);
}


void SimplePopupPanel::onAnimationEnded(const string& ani)
{
	if (!isVisible())
		return;

	if (ani.find("notice_small1_start") != string::npos)
	{
		//if (mType != ToastNotice)
		//{
		//	mMiddleOkBtn->setVisible(true);
		//	mMiddleOkBtn->setEnable(true);
		//	mMiddleOkBtn->setListener(this);
		//}
		//else
		//	clearThisPanel();

		//if (mType != AdminNotice)
		//	mDesc->setVisible(true);
	}
	else if (ani.find("notice_small2_start") != string::npos)
	{
		//mCancelBtn->setVisible(true);
		//mCancelBtn->setEnable(true);
		//mCancelBtn->setListener(this);

		//mOkBtn->setVisible(true);
		//mOkBtn->setEnable(true);
		//mOkBtn->setListener(this);

		//if (mType != AdminNotice)
		//	mDesc->setVisible(true);
	}
	else if (ani.find("toastbar1_start") != string::npos)
	{
		if (mType != AdminNotice)
			mDesc->setVisible(true);
		else
			mAdminText->setVisible(true);
	}
	else if (ani.find("toastbar2_start") != string::npos)
	{
		if (mType != AdminNotice)
			mDesc->setVisible(true);
		else
			mAdminText->setVisible(true);
	}
	else if (ani.find("toastbar1_loop") != string::npos)
	{
		if (mType != AdminNotice)
			mDesc->setVisible(false);
		else
			mAdminText->setVisible(true);
		mBoard->playAnimation("toastbar1_end");
	}
	else if (ani.find("toastbar2_loop") != string::npos)
	{
		if (mType != AdminNotice)
			mDesc->setVisible(false);
		else
			mAdminText->setVisible(true);

		//mBoard->playAnimation("toastbar2_end");
	}
	else if (ani.find("toastbar1_end") != string::npos)
	{
		clearThisPanel();
	}
	else if (ani.find("toastbar2_end") != string::npos)
	{
		clearThisPanel();
	}
	else if (ani.find("notice_small1_end") != string::npos)
	{
		/*ExeEvent();*/
	}
	else if (ani.find("notice_small2_end") != string::npos)
	{
		//ExeEvent();
	}
}

void SimplePopupPanel::ExeEvent()
{
	GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
	if (mEventName == mMiddleOkBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mOkEventMsg);
		else
			fireMessage(mOkEventMsg);
	}
	else if (mEventName == mOkBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mOkEventMsg);
		else
			fireMessage(mOkEventMsg);
	}
	else if (mEventName == mCancelBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mCancelEventMsg);
		else
			fireMessage(mCancelEventMsg);
	}
	else if (mEventName == mExitBtn->getName())
	{
		clearThisPanel();
		if (mGeneralListener)
			(mTarget->*mGeneralListener)(mExitEventMsg);
		else
			fireMessage(mExitEventMsg);
	}
}

void SimplePopupPanel::OnExitEvent()
{
	clearThisPanel();
	if (mGeneralListener)
		(mTarget->*mGeneralListener)(mExitEventMsg);
	else
		fireMessage(mExitEventMsg);
}

void SimplePopupPanel::GuideboxCloseEvent()
{
	getSkel("skel_guidebar_middle")->appendAnimation("guidebar1_end");
	mActivatge = true;
	runAction(CCSequence::create(
		CCDelayTime::create(1.f),
		CCCallFunc::create(this, callfunc_selector(SimplePopupPanel::OnExitEvent)),
		NULL));
}

void SimplePopupPanel::SetOkEventMsg(string msg)
{
	mOkEventMsg = msg;
}

void SimplePopupPanel::SetCancelEventMsg(string msg)
{
	mCancelEventMsg = msg;
}

void SimplePopupPanel::SetToastAlign(ToastAlign align)
{
	mToastAlign = align;
}

void SimplePopupPanel::SetTitle(string _title)
{
	if (_title.length() == 0)
	{
		_title = GameStringDepot::getSingletonPtr()->getString("TXT_INFORMATION");
	}
	//getLabel("txt_checktitle")->setString(_title.c_str());
	//getLabel("txt_checktitle2")->setString(_title.c_str());
	getLabel("txt_title")->setString(_title.c_str());
	if (hasElement("txt_title_under"))
		getLabel("txt_title_under")->setString(_title.c_str());
}

void SimplePopupPanel::SetContents(string _content)
{
	getLabel("txt_checktext")->setString(_content.c_str());
}

void SimplePopupPanel::UpdateStayTimeLabel(std::string _time)
{
	//0708
// 	if (hasElement("txt_stay") == false)
// 		return;
// 
// 	getLabel("txt_stay")->setString(_time.c_str());
}

void SimplePopupPanel::initLobbyBankPopup()
{
	construct(getMxmlPath() + "dmy_up_panel2.mxml");
	getLabel("txt_bank_guide")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	getSkel("skel_up_panel")->playAnimation("up_panel_start");
	getSkel("skel_up_panel")->appendAnimation("up_panel_stay");
	getLabel("txt_gold")->setVisible(false);
	getLabel("txt_red")->setVisible(false);	
	getLabel("txt_bank_guide")->setVisible(false);
	ShowBackPanel(false);
}

bool SimplePopupPanel::isGameEndType()
{
	return mType == GAME_END;
}

bool SimplePopupPanel::isGuideType()
{
	return mType == ToastBankNotice;
}

void SimplePopupPanel::setLayerActivate(bool activate)
{
	if (activate) {
		setVisible(true);
		if (mActivatge) {
			runAction(CCSequence::create(
				CCFadeIn::create(0.1f),
				CCDelayTime::create(3.f),
				CCFadeOut::create(0.1f),
				CCCallFunc::create(this, callfunc_selector(SimplePopupPanel::clearThisPanel)),
				NULL));
		}
	}
	else {
		setVisible(false);
		stopAllActions();
	}
}

void SimplePopupPanel::SetExitEventMsg(string msg)
{
	mExitEventMsg = msg;
}

void SimplePopupPanel::initBankSafePopup(string text, string title)
{
	construct(getMxmlPath() + "dmy_bank_board.mxml");
	getLabel("txt_info")->setString(GameStringDepot::getSingleton().getString("BankInOutPanel_PROCESS").c_str());
	
	//title
	getLabel("txt_title_under")->setString(title.c_str());
	getLabel("txt_title")->setString(title.c_str());
	//내용
	getLabel("txt_item_name")->setString(text.c_str());

	m_pBtnPanel[0] = new Panel();
	m_pBtnPanel[0]->construct(getMxmlPath() + "dmy_button_small.mxml");
	string dmyName = "dmy_button_small";
	CCPoint _btnPos = getDummy(dmyName).origin;
	_btnPos.y = -_btnPos.y;
	m_pBtnPanel[0]->setPosition(_btnPos);
	addChild(m_pBtnPanel[0]);
	m_pBtnPanel[0]->release();
	
	string _okTxt = GameStringDepot::getSingletonPtr()->getString("TXT_OK_LABEL");
	m_pBtnPanel[0]->getLabel("txt_button_under")->setString(_okTxt.c_str());
	m_pBtnPanel[0]->getLabel("txt_button")->setString(_okTxt.c_str());
	mMiddleOkBtn = m_pBtnPanel[0]->getButton("sbtn_button");
	mMiddleOkBtn->setListener(this);
}

void SimplePopupPanel::showMaxMoneyPopup(string title, string _msg)
{
	getLabel("txt_bank_guide")->setVisible(true);
	getLabel("txt_red")->setVisible(true);
	getLabel("txt_bank_guide")->setString(title.c_str());
	getLabel("txt_red")->setString(_msg.c_str());
	setOpacity(0);
	stopAllActions();

	setVisible(true);
	mActivatge = true;
	runAction(CCSequence::create(
		CCFadeIn::create(0.1f),
		CCDelayTime::create(3.f),
		CCFadeOut::create(0.1f),
		CCCallFunc::create(this, callfunc_selector(SimplePopupPanel::clearThisPanel)),
		NULL));
}
