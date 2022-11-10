#include "pch.h"
#include "ModelGoodsPanel.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
//#include "PokerResourceHelper.h"

#include "LobbyScene.h"
#include "ModellsBackPanel.h"
#include "ModelTempTabel.h"
#include "PanelHelper.h"
#include "ModellsBackPopupPanel.h"
#include <time.h>


ModelGoodsPanel::ModelGoodsPanel()
{
	InitPanel();
	InitImage();
	initButton();
	setButtonListener(this);
}

ModelGoodsPanel::~ModelGoodsPanel()
{
	//destruct();
}

void ModelGoodsPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_model_goods_panel.mxml");	
}

void ModelGoodsPanel::InitImage()
{
	m_Cover = getSkel("skel_cover");
	m_Name = getLabel("txt_character_name");

	m_GoodsPanel = getSkel("skel_goods_penal_1_stay");
	
	mCharacter = getImage("img_character_boxer");
	
	mCoverImg = getImage("skel_line_choose");	// 선택 됐다는 외각 라인인데, 인벤에서 사용
	mCoverImg->setVisible(false);

	getImage("img_model_blur_maxim")->setVisible(false);
	getImage("img_model_blur_playpot")->setVisible(false);
	getImage("img_model_blur_comming")->setVisible(false);
}

void ModelGoodsPanel::initButton()
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
}

void ModelGoodsPanel::onClicked(const string& name)
{

}


void ModelGoodsPanel::onLayerMessage(const string& msg)
{
	if (msg == "BUY_MODEL") {
		uint64 money = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
		uint64 need = GameDataManager::getSingletonPtr()->FindShopModel(tIdx,mIdx).gold(); 
		int64 requestId = GameDataManager::getSingletonPtr()->FindShopModel(tIdx, mIdx).id();
		if (money >= need)
		{
			GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney -= need;
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ApplyUserData();
			LayerManager::getSingletonPtr()->getLayerType<ModelGoodsPanel>();
			GameDataManager::getSingletonPtr()->BuyMessageCaller = this;
			m_ButtonPanel->setVisible(false);
			WebService::getSingletonPtr()->SendModelPicBuyReq(requestId);
		}
		else
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice,
			GameStringDepot::getSingletonPtr()->getString("TXT_REFILL_GOLD_TITLE")), DYNAMIC_PUSH_LAYER);
		}
	}
	else if (msg == "BUY_SLOT")
	{
		uint64 money = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
		uint64 need = GameDataManager::getSingletonPtr()->mSlotEXNeedGold;

		if (money >= need)
		{
			GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney -= need;
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ApplyUserData();
			WebService::getSingletonPtr()->SendBuySlotReq(tIdx + 1); //tapId = 1,2,3,4.... tIdx = 0,1,2,3.....
			fireMessage(msg);
		}
		else
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice,
			GameStringDepot::getSingletonPtr()->getString("TXT_REFILL_GOLD_TITLE")), DYNAMIC_PUSH_LAYER);
		}
	}
	else if (msg == "BUY_TAP")
	{
		uint64 money = GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney;
		uint64 need = GameDataManager::getSingletonPtr()->mTapEXNeedGold;

		if (money >= need)
		{
			GameDataManager::getSingletonPtr()->GetPlayerDataPtr()->m_GameMoney -= need;
			LobbyScene* _pScene = dynamic_cast<LobbyScene*>(SceneManager::getSingletonPtr()->getCurrentScene());
			_pScene->ApplyUserData();
			string ablestr = GameStringDepot::getSingleton().getString("TXT_ENABLE_BTN").c_str();
			SetBtnText(StringConverter::toWstring(ablestr));

			WebService::getSingletonPtr()->SendBuyTapReq(mIdx + 1); //디스플레이 모델에서 탭아이디는 모델아이디로 사용...
		}
		else
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice,
				GameStringDepot::getSingletonPtr()->getString("TXT_REFILL_GOLD_TITLE")), DYNAMIC_PUSH_LAYER);
		}

	}
}

void ModelGoodsPanel::SetGoodsType(MODEL_TYPE _type)
{
	m_panelType = _type; 
	
	switch (_type)
	{
	case MODEL_TYPE::MODEL_SHOP:
	case MODEL_TYPE::MODEL_INVEN:
		m_ButtonPanel->getSkel("skel_icon")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price1_under")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price1")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price2_under")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price2")->setVisible(false);
		break;
	case MODEL_TYPE::MODEL_SHOP_SUB:
	case MODEL_TYPE::MODEL_INVEN_SUB:
		m_ButtonPanel->getSkel("skel_icon")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price1_under")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price1")->setVisible(true);
		m_ButtonPanel->getLabel("txt_price2_under")->setVisible(false);
		m_ButtonPanel->getLabel("txt_price2")->setVisible(false);
		break;
	}
}

void ModelGoodsPanel::SetBtnText(const std::wstring& _text)
{
	m_ButtonPanel->getLabel("txt_price1_under")->setString(_text.c_str());
	m_ButtonPanel->getLabel("txt_price1")->setString(_text.c_str());
	m_ButtonPanel->getLabel("txt_price2_under")->setString(_text.c_str());
	m_ButtonPanel->getLabel("txt_price2")->setString(_text.c_str());
}

void ModelGoodsPanel::setIndex(int tIdx,int idx , TAB_TYPE tabType)
{
	this->tIdx = tIdx;
	//this->mIdx = idx;
	if(m_panelType == MODEL_TYPE::MODEL_INVEN || m_panelType == MODEL_TYPE::MODEL_SHOP || m_panelType == MODEL_TYPE::MODEL_SHOP_SUB)
		this->mIdx = idx;
	else if(m_panelType == MODEL_TYPE::MODEL_INVEN_SUB )
		this->mIdx = GameDataManager::getSingletonPtr()->getModelInfo(idx, MODEL_INDEX);
	
	m_ButtonPanel->getLabel("txt_price1")->setColor(StringConverter::parseColor3B("ffffff"));
	getImage("img_model_blur_maxim")->setVisible(false);
	getImage("img_model_blur_playpot")->setVisible(false);
	getImage("img_model_blur_comming")->setVisible(false);

	// -1은 구매하지 않은 값인데 이 값은 빈슬롯 표시에 활용 된다
	m_ButtonPanel->setVisible(idx >= 0);
	mCharacter->setVisible(idx >= 0);
	m_OkBtn->setVisible(idx >= 0);
	m_Cover->setVisible(idx >= 0);
	m_Name->setVisible(idx >= 0);
	
	if (m_panelType == MODEL_TYPE::MODEL_SHOP) {
		m_Cover->setVisible(true);
		m_Name->setVisible(true);
		//titlemodel list에서는 tid를 쓰지 않기에 -1값만 반환한다
		W_DisplayModelData temp = GameDataManager::getSingletonPtr()->FindTitleModel(idx, tabType);
		std::string goldDesc = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(GameDataManager::getSingletonPtr()->mTapEXNeedGold), 2);
		SetBtnText(StringConverter::toWstring(goldDesc));	// 가격
		m_Name->setString(temp.name().c_str());
		mCharacter->setVisible(idx >= 0);
		
		if (mCharacter->isVisible())
		{
			mCharacter->setSpriteFrameWithFile("model/" + temp.filename());
			PanelHelper::setCompactImage(mCharacter, getDummy("img_character_boxer"));
		}
		if (idx >= 0) {
#if(TargetingServer == SIMYUI_SERVER) //NZ창헌
			if (GameDataManager::getSingletonPtr()->CanDisplay(temp.startdt(), temp.enddt()) || idx == 1)	// 시작날자와 판매종료날자 사이에 있으면
#else
			if (GameDataManager::getSingletonPtr()->CanDisplay(temp.startdt(), temp.enddt()))	// 시작날자와 판매종료날자 사이에 있으면
#endif
			{
				m_OkBtn->setSkelAnimation("button_shop_on");
				int tapid = GameDataManager::getSingletonPtr()->getModelInfo(temp.id(), TAP_ID);
				string ablestr = GameStringDepot::getSingleton().getString("TXT_ENABLE_BTN").c_str();
				SetBtnText(StringConverter::toWstring(ablestr));
			}

			else {
				string unablestr = GameStringDepot::getSingleton().getString("TXT_COMMING_SOON").c_str();
				m_OkBtn->setSkelAnimation("button_shop_use");	// 투명 버튼
				SetBtnText(StringConverter::toWstring(unablestr));
			}
		}
	}
	else if (m_panelType == MODEL_TYPE::MODEL_SHOP_SUB)
	{
		getImage("img_model_blur_maxim")->setVisible(false);
		
		W_ModelData temp = GameDataManager::getSingletonPtr()->FindShopModel(tIdx, mIdx, tabType);
		std::string goldDesc = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(temp.gold()), 2);
		SetBtnText(StringConverter::toWstring(goldDesc));	// 가격
		m_Name->setString(temp.name().c_str());
		mCharacter->setVisible(idx >= 0);
		if (mCharacter->isVisible())
		{
			mCharacter->setSpriteFrameWithFile("model/" + temp.filename()); //이미지를 불러오고
			PanelHelper::setCompactImage(mCharacter, getDummy("img_character_boxer")); //이미지를 박스에 알맞게 삽입
		}
		m_ButtonPanel->setVisible(idx >= 0 && !GameDataManager::getSingletonPtr()->hasModel(tIdx,idx, tabType));
		// 구매한 모델이 아니라면 블러이미지
		getImage("img_model_blur_maxim")->setVisible(!GameDataManager::getSingletonPtr()->hasModel(tIdx,idx, tabType));
	}
	else if (m_panelType == MODEL_TYPE::MODEL_INVEN)
	{
		m_Cover->setVisible(true);
		m_Name->setVisible(true);

		W_DisplayModelData temp = GameDataManager::getSingletonPtr()->FindTitleModel(idx, tabType);
		m_Name->setString(temp.name().c_str());
		mCharacter->setVisible(idx >= 0);
		if (mCharacter->isVisible())
		{
			mCharacter->setSpriteFrameWithFile("model/" + temp.filename());
			PanelHelper::setCompactImage(mCharacter, getDummy("img_character_boxer"));
		}

		if (idx >= 0) {
#if(TargetingServer == SIMYUI_SERVER) //NZ창헌
			if (GameDataManager::getSingletonPtr()->CanDisplay(temp.startdt(), temp.enddt()) || idx == 1)	// 시작날자와 판매종료날자 사이에 있으면
#else
			if (GameDataManager::getSingletonPtr()->CanDisplay(temp.startdt(), temp.enddt()))	// 시작날자와 판매종료날자 사이에 있으면
#endif
			{
				m_OkBtn->setSkelAnimation("button_shop_on");
				int tapid = GameDataManager::getSingletonPtr()->getModelInfo(temp.id(), TAP_ID);
				if (GameDataManager::getSingletonPtr()->hasTap(tapid, tabType)) {
					string ablestr = GameStringDepot::getSingleton().getString("TXT_ENABLE_BTN").c_str();
					SetBtnText(StringConverter::toWstring(ablestr));
				}
				
			}
			else {
				string unablestr = GameStringDepot::getSingleton().getString("TXT_COMMING_SOON").c_str();
				m_OkBtn->setSkelAnimation("button_shop_use");	// 투명 버튼
				SetBtnText(StringConverter::toWstring(unablestr));
			}
		}
	}
	else if (m_panelType == MODEL_TYPE::MODEL_INVEN_SUB)
	{
		// 구매한 이미지만 출력한다.
		if (GameDataManager::getSingletonPtr()->hasModel(tIdx, mIdx,tabType))
		{
			getImage("img_model_blur_maxim")->setVisible(false);

			W_ModelData temp = GameDataManager::getSingletonPtr()->FindShopModel(tIdx, mIdx, tabType);
			std::string goldDesc = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(temp.gold()), 2);
			SetBtnText(StringConverter::toWstring(goldDesc));	// 가격
			m_Name->setString(temp.name().c_str());
			mCharacter->setVisible(idx >= 0);
			if (mCharacter->isVisible())
			{
				mCharacter->setSpriteFrameWithFile("model/" + temp.filename());
				PanelHelper::setCompactImage(mCharacter, getDummy("img_character_boxer"));
			}
			m_ButtonPanel->setVisible(false);
		}
	}
}

void ModelGoodsPanel::OnPopupOpen(MODEL_TYPE modelType, TAB_TYPE tapType)
{
	W_DisplayModelData temp = GameDataManager::getSingletonPtr()->FindTitleModel(mIdx, tapType);

	if (!GameDataManager::getSingletonPtr()->CanDisplay(temp.startdt(), temp.enddt()))	// '곧 만나요' 는 버튼 작동하지 않음
	{
#if(TargetingServer == SIMYUI_SERVER) //NZ창헌
		if(mIdx!=1)
			return;
#else
		return;
#endif
	}
		
	else if (modelType == MODEL_TYPE::MODEL_SHOP_SUB && !GameDataManager::getSingletonPtr()->hasTap(mIdx + 1, tapType)) {
		BuyTap();
		return;
	}
	PanelHelper::pushModellsBackPopupPanel(mIdx, modelType, tapType); // 모델 리스트의 모델별 인덱스
}

// 전체 화면 보기
void ModelGoodsPanel::ModelShot()
{
	PanelHelper::pushModelShotPanel(tIdx,mIdx);
}

void ModelGoodsPanel::BuyModel() //NZ창헌
{
	string _title = GameStringDepot::getSingleton().getString("TXT_INFORMATION"); //팝업 이미지의 제목
	string _content = GameStringDepot::getSingleton().getString("TXT_BUY_MODEL"); //팝업 이미지의 내용 텍스트
	SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ShopYESNONotice, _content, _title);   // simeplepopup만들어주자
	if (_popupPanel)
	{
		_popupPanel->SetOkEventMsg("BUY_MODEL");
		_popupPanel->setListener(this);
		LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
	}
}

void ModelGoodsPanel::OneStoreNotice() //NZ창헌 
{
	string _title = GameStringDepot::getSingleton().getString("TXT_INFORMATION"); //팝업 이미지의 제목
#if(TargetingServer == SIMYUI_SERVER)
	string _content = GameStringDepot::getSingleton().getString("TXT_CANT_BUY_NOW"); //팝업 이미지의 내용 텍스트 ( 심의 서버에서 보여줄 것 )
#else
	string _content = GameStringDepot::getSingleton().getString("TXT_GOTO_ONESTORE"); //팝업 이미지의 내용 텍스트 (외부 서버에서 보여줄 것 ) 
#endif
	SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::BUY_AT_ONESTORE, _content, _title);   // simeplepopup만들어주자
	if (_popupPanel)
	{
#if(TargetingServer == SIMYUI_SERVER)
		_popupPanel->SetOkEventMsg("TXT_CANT_BUY_NOW");
#else
		_popupPanel->SetOkEventMsg("TXT_GOTO_ONESTORE");
#endif
		_popupPanel->setListener(this);
		LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
	}
}

void ModelGoodsPanel::UnlockModel()
{
	string _title = GameStringDepot::getSingleton().getString("TXT_INFORMATION");
	string _content = GameStringDepot::getSingleton().getString("TXT_POPUP_MODEL_SLOT");
	SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ShopYESNONotice, _content, _title);
	if (_popupPanel)
	{
		_popupPanel->SetOkEventMsg("BUY_SLOT");
		_popupPanel->setListener(this);
		LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
	}
}

void ModelGoodsPanel::BuyTap()
{
	string _title = GameStringDepot::getSingleton().getString("TXT_INFORMATION"); //팝업 이미지의 제목
	string _content = GameStringDepot::getSingleton().getString("TXT_POPUP_MODEL_TAP"); //팝업 이미지의 내용 텍스트
	SimplePopupPanel* _popupPanel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::ShopYESNONotice, _content, _title);
	if (_popupPanel)
	{
		_popupPanel->SetOkEventMsg("BUY_TAP");
		_popupPanel->setListener(this);
		LayerManager::getSingleton().pushDynamicLayer(_popupPanel, DYNAMIC_PUSH_LAYER);
		return;
	}
}
