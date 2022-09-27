#include "pch.h"
#include "CardPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "PokerResourceHelper.h"

CardPanel::CardPanel()
{
	InitPanel();
	InitImage();
	initButton();
	SetGoodsType(CARD_SHOP_TYPE);
	setButtonListener(this);
}

CardPanel::~CardPanel()
{
	//destruct();
}

void CardPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_goods_panel.mxml");	
}

void CardPanel::InitImage()
{
	m_Spec = getLabel("txt_spec");
	
	mCenteTitle = getLabel("txt_gold_goods_center");	
	mCenterPos = mCenteTitle->getPosition();
	mTopPos = getImage("dmy_gold_goods_top")->getPosition();
	mBottomPos = getImage("dmy_gold_goods_bottom")->getPosition(); 
	mTopPos.x = mCenterPos.x;
	mBottomPos.x = mCenterPos.x;

	m_OverlapNotice = getLabel("txt_overlap_notice");
	
	m_DayLimit = getLabel("txt_limit");
	m_Name = getLabel("txt_character_name");
	m_DiscountUnder = getLabel("txt_label_shadow");
	m_Discount = getLabel("txt_label");

	m_GoodsPanel = getSkel("skel_goods_penal_1_stay");
	m_Cover = getSkel("skel_cover");
	m_HotMark = getSkel("skel_label_red2");
	mDisCount = getSkel("skel_label_red");
	mCharacter = getImage("img_character_boxer");
	
	mCoverImg = getImage("skel_line_choose");
	mCoverImg->setVisible(false);

	getImage("skel_cover_gold")->setVisible(false);
	getImage("skel_bonus")->setVisible(false);
	getLabel("txt_bonus")->setVisible(false);
	getLabel("txt_overlap_notice")->setVisible(false);
}

void CardPanel::initButton()
{
	CCPoint _btnPos = getDummy("dmy_button_shop").origin;
	m_ButtonPanel = new Panel();
	m_ButtonPanel->construct(getMxmlPath() + "dmy_button_shop.mxml");
	m_ButtonPanel->setPositionX(_btnPos.x);
	m_ButtonPanel->setPositionY(-_btnPos.y);
	addChild(m_ButtonPanel);
	m_ButtonPanel->release();

	m_ButtonPanel->getLabel("txt_price2_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_ButtonPanel->getLabel("txt_price2")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_ButtonPanel->getLabel("txt_price1_under")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_ButtonPanel->getLabel("txt_price1")->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	
	m_OkBtn = m_ButtonPanel->getButton("sbtn_button");
	m_OkBtn->setPaused(true); 
	mButtons.push_back(m_OkBtn);	
}

void CardPanel::onClicked(const string& name)
{
	if (name == m_OkBtn->getName()) {
		fireMessage(BUY_CARD_BTN_SEND_MSG + StringConverter::toString(mIdx));
	}	
}

void CardPanel::SetGoodsType(CardPanelType _type)
{
	m_panelType = _type;

	switch (_type)
	{
	case CARD_INVEN_TYPE:
		m_ButtonPanel->getSkel("skel_icon")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price1_under")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price1")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price2_under")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price2")->setVisible(false);
		m_Discount->setVisible(false);
		m_DiscountUnder->setVisible(false);
		m_HotMark->setVisible(false);		
		mDisCount->setVisible(false);
		getLabel("txt_overlap_notice")->setVisible(false);
		break;
	case CARD_SHOP_TYPE:
		m_ButtonPanel->getSkel("skel_icon")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price1_under")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price1")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price2_under")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price2")->setVisible(true);
		m_Discount->setVisible(false);
		m_DiscountUnder->setVisible(false);
		m_HotMark->setVisible(false);
		mDisCount->setVisible(false);
		getLabel("txt_overlap_notice")->setVisible(true);
		break;
	}
}

void CardPanel::SetBtnText(string _text)
{
	switch (m_panelType)
	{
	case CARD_INVEN_TYPE:
		m_ButtonPanel->getLabel("txt_price1_under")->setString(_text.c_str());
		m_ButtonPanel->getLabel("txt_price1")->setString(_text.c_str());
		break;
	case CARD_SHOP_TYPE:
		m_ButtonPanel->getLabel("txt_price1_under")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price1")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price2_under")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price2")->setVisible(false);
		if (isCardMoneyType()) {
			m_ButtonPanel->getSkel("skel_icon")->setVisible(false);
			m_ButtonPanel->getLabel("txt_price1_under")->setString(_text.c_str());
			m_ButtonPanel->getLabel("txt_price1")->setString(_text.c_str());
			m_ButtonPanel->getLabel("txt_price1_under")->setVisible(true);
			m_ButtonPanel->getLabel("txt_price1")->setVisible(true);
		}
		else {
			m_ButtonPanel->getSkel("skel_icon")->setVisible(true);
			m_ButtonPanel->getLabel("txt_price2_under")->setString(_text.c_str());
			m_ButtonPanel->getLabel("txt_price2")->setString(_text.c_str());
			m_ButtonPanel->getLabel("txt_price2_under")->setVisible(true);
			m_ButtonPanel->getLabel("txt_price2")->setVisible(true);
		}
		
		break;
	}
}

void CardPanel::setIndex(int idx)
{
	mIdx = idx;
	mCenteTitle->setVisible(false);
	int skinId = -1;
	int _day = 0;
	string _sLimitDay = "";
	string _overlapNotice = "";

	m_ButtonPanel->getLabel("txt_price1")->setColor(StringConverter::parseColor3B("ffffff"));

	if (m_panelType == CARD_INVEN_TYPE){
		const W_SkinInfo& skinInfo = GameDataManager::getSingletonPtr()->getUserInfo()->skininfo(idx);
		skinId = skinInfo.id();
		mCoverImg->setVisible(false);
		if (skinInfo.isbase())
		{
			_sLimitDay = GameStringDepot::getSingletonPtr()->getString("TXT_UNLIMIT");
			_overlapNotice = GameStringDepot::getSingletonPtr()->getString("TXT_OVERLAP_NOTICE");
		}
		else
		{
			_sLimitDay = GameDataManager::getSingletonPtr()->GetTimeString(skinInfo.expirelefttime()) + GameStringDepot::getSingletonPtr()->getString("TXT_TIMELEFT");
			_overlapNotice = GameStringDepot::getSingletonPtr()->getString("TXT_OVERLAP_NOTICE");
		}
		m_OkBtn->setSkelAnimation("button_shop_on");

		string _btnTxt = "";
		if (GameDataManager::getSingletonPtr()->getPlayerInfo().useskin() == skinId)
		{
			_btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_SELECTED_UNIT");
			m_OkBtn->setEnable(false);
			m_OkBtn->setSkelAnimation("button_shop_use");
			mCoverImg->setVisible(true);			
			m_ButtonPanel->getLabel("txt_price1")->setColor(StringConverter::parseColor3B("ffd042"));
		}
		else
		{
			if (skinInfo.expirelefttime() == 0 && skinInfo.isbase() == false)
			{
				_btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_CHARACTER_BUY_UNIT");
			}
			else
			{
				_btnTxt = GameStringDepot::getSingletonPtr()->getString("TXT_CHANGEING_UNIT");
			}
			m_OkBtn->setEnable(true);
			m_OkBtn->setGrayscale(false);
		}
		SetBtnText(_btnTxt.c_str());
		const W_SkinData* skinData = GameDataManager::getSingleton().getSkinData(skinId);
		m_Name->setString(skinData->name().c_str());
	}
	else if (m_panelType == CARD_SHOP_TYPE) {
		//index 를 가지고 글 표시
		W_SkinShopData _infoData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->skinshopdata(idx);
		skinId = _infoData.skinid();
		m_HotMark->setVisible(false);
		mDisCount->setVisible(false);
		m_Discount->setVisible(false);
		m_DiscountUnder->setVisible(false);

		if (_infoData.bandtype() == eBandNew) {
			m_HotMark->setVisible(true);
			m_HotMark->playAnimation("label_yellow");
		}
		else if (_infoData.bandtype() == eBandHot) {
			m_HotMark->setVisible(true);
			m_HotMark->playAnimation("label_red");
		}
		string _rewardText = "";
		if (_infoData.has_rewardinfo())
		{
			int _rewardSize = _infoData.rewardinfo().rewardset_size();

			for (int _j = 0; _j < _rewardSize; _j++)
			{
				W_RewardInfo_RewardSet _set = _infoData.rewardinfo().rewardset(_j);


				//if (_set.has_id());

				if (_set.has_amount())
				{
					_rewardText += GameStringDepot::getSingleton().getString("TXT_IMMEDIATELY");
					_rewardText += " " + GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_set.amount()));
					_rewardText += " " + GameStringDepot::getSingleton().getString("TXT_GET_UNIT");
				}
			}
		}
		mCenteTitle->setString((_rewardText).c_str());
		_day = _infoData.periodday();
		_sLimitDay = GameStringDepot::getSingletonPtr()->getString("TXT_LIMITTIME") + ":" + StringConverter::toString(_day) + GameStringDepot::getSingletonPtr()->getString("TXT_DAY");
		_overlapNotice = GameStringDepot::getSingletonPtr()->getString("TXT_OVERLAP_NOTICE");

		if (isCardMoneyType()) {
			string txtPrice = StringConverter::toString(_infoData.money()) + GameStringDepot::getSingleton().getString("TXT_COUNT_MONEY");
			SetBtnText(txtPrice.c_str());
		}
		else {
			SetBtnText(StringConverter::toString(_infoData.cash()).c_str());
		}
		
		m_Name->setString(_infoData.name().c_str());
	}

	const W_SkinData* skinData = GameDataManager::getSingleton().getSkinData(skinId);

	//공통표시
	m_DayLimit->setString(_sLimitDay.c_str());
	m_OverlapNotice->setString(_overlapNotice.c_str());
	m_OverlapNotice->setColor(StringConverter::parseColor3B("bc9e62"));
	m_OverlapNotice->setVisible(true);
	string _sDesc = "";
	int _size = skinData->effect_size();
	int realEffectSize = 0;
	for (int _i = 0; _i < _size; _i++)
	{
		W_CharacterData_CharacterEffect _dataEff = skinData->effect(_i);
		if (_dataEff.type() != W_CharacterData_eEffectType_None) {
			if (realEffectSize != 0)
				_sDesc += "\n";
			_sDesc += _dataEff.desc();			
			realEffectSize++;
		}
	}

	//캐릭터 상품일때만 뿌린다.
	if (m_panelType == CARD_SHOP_TYPE) {
		if (realEffectSize == 2) {
			mCenteTitle->setVisible(true);
			mCenteTitle->setPosition(mCenterPos); 
		}
		else if (realEffectSize == 1) {
			mCenteTitle->setVisible(true);			
			mCenteTitle->setPosition(mTopPos);
		}
		else if (realEffectSize == 0) {
			mCenteTitle->setVisible(true);
			mCenteTitle->setPosition(mBottomPos);
		}
	}
	m_Spec->setString(_sDesc.c_str());
	
	//캐릭터 표시		
	
	if (m_panelType == CARD_INVEN_TYPE) {
		mCharacter->setSpriteFrameWithFile(PokerResourceHelper::getSkinImgName(skinId));
	}
	else {
		mCharacter->setSpriteFrameWithFile(PokerResourceHelper::getSkinShopWithMoneyImgName(skinId));
	}
}

void CardPanel::cellTouch(const CCPoint& touchPoint)
{
	for (Button* btn : mButtons)
	{
		if (btn->hasCollided(btn->convertToNodeSpace(touchPoint))){
			if (btn->isEnabled()){
				onClicked(btn->getName());
				CCDelayTime* delay = CCDelayTime::create(CELL_TOUCH_TIME * 2);
				CCActionInstant* func = CCCallFuncN::create(this, callfuncN_selector(CardPanel::_cellTouchEnd));
				btn->runAction(CCSequence::create(delay, func, nullptr));
				return;
			}
		}
	}	
}

void CardPanel::_cellTouchEnd(CCNode* node)
{
	Button* btn = dynamic_cast<Button*>(node);
	if (btn){
		btn->setNormalImage();
	}
}

bool CardPanel::isCardMoneyType()
{
	bool isMoneyType = false;
	if (m_panelType == CARD_SHOP_TYPE){
		W_SkinShopData _infoData = GameDataManager::getSingletonPtr()->GetGameDataPtr()->skinshopdata(mIdx);
		if (_infoData.cash() == 0) {
			isMoneyType = true;
		}
	}
	return isMoneyType;
}
