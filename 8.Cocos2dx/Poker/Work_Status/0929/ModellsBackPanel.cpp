#include "pch.h"
#include "ModellsBackPanel.h"
#include "GameDataManager.h"
#include "ModelTempTabel.h"
#include "GameStringDepot.h"
#include "ModelGoodsPanel.h"
#include "ModelListPartPanel.h"

#define KIMSOHEE_BLOCK 8
#define KIMNAJEONG_BLOCK 2

ModellsBackPanel::ModellsBackPanel()
{
	InitPanel();
	SetModelType(MODEL_SHOP);
}

ModellsBackPanel::~ModellsBackPanel()
{
	//destruct();
}

void ModellsBackPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_modells_back_panel.mxml");
	mLock = getImage("img_lock");
	mLockBg = getImage("img_lock_bg");
}

void ModellsBackPanel::SetModelType(MODEL_TYPE _type)
{
	m_panelType = _type;
}

void ModellsBackPanel::setIndex(int idx, std::vector<int> ids, int tIdx, TAB_TYPE tabType)
{
	mIdx = tIdx;
	mtabType = tabType;
	for (uint i = 0; i < 3; ++i)
	{
		int realIdx = ids.size() > i ? ids[i] : -1;
		ModelGoodsPanel* pPanel = nullptr;
		if (mGoodsPanels.size() > i)
		{
			pPanel = mGoodsPanels[i];
		}
		else
		{
			if (realIdx >= 0 || (m_panelType == MODEL_SHOP_SUB || m_panelType == MODEL_INVEN_SUB)) {
				pPanel = new ModelGoodsPanel();
				mGoodsPanels.push_back(pPanel);
				addChild(pPanel);
				pPanel->release();
			}
			else {
				continue;
			}
		}
		pPanel->SetGoodsType(m_panelType);
		pPanel->setIndex(tIdx,realIdx, tabType);
		pPanel->setListener(this);
		pPanel->setPosition(ccp(pPanel->getContentSize().width * i + 2 * i, 0));
        //pPanel->m_ButtonPanel->getButton("sbtn_button")->setPaused(true);
		//pPanel->setVisible(ids.size() <= 0 || realIdx != -1);
		pPanel->setVisible(realIdx >= 0 || (m_panelType == MODEL_SHOP_SUB || m_panelType == MODEL_INVEN_SUB));
	}
	setLock(ids.size() <= 0);
}

void ModellsBackPanel::cellTouch(const CCPoint& touchPoint)
{
    for (ModelGoodsPanel* pPanel : mGoodsPanels)
    {
		if (!pPanel->isVisible())
			continue;

		switch (m_panelType)
		{
		case MODEL_TYPE::MODEL_SHOP:
		{
			Button* btn = pPanel->m_ButtonPanel->getButton("sbtn_button");
			if (btn->hasCollided(btn->convertToNodeSpace(touchPoint))) {
				if (pPanel->m_ButtonPanel->isVisible()) {
					pPanel->OnPopupOpen(MODEL_TYPE::MODEL_SHOP_SUB, mtabType);	// 여긴 모델들을 표시 하는 곳이니, 모델별 사진으로 이동
					return;
				}
			}
			
		}
		break;
		case MODEL_TYPE::MODEL_SHOP_SUB: 
		{
			Button* btn = pPanel->m_ButtonPanel->getButton("sbtn_button");
			if (btn->hasCollided(btn->convertToNodeSpace(touchPoint))) {
				if (pPanel->m_ButtonPanel->isVisible()) {
					if (GameDataManager::getSingleton().hasSlot(mIdx, -1, mtabType)) { //슬롯 구매되었나
						
						CanGoogleBuy(pPanel);
						//pPanel->OneStoreNotice();  // 이부분에서 구글 모델, 원스토어 모델 처리를 해주자.
						//pPanel->BuyModel(); //nz창헌 onestore 쪽으로 수정 할 것  0929 아직 진행 x
					}
						
					else
						pPanel->UnlockModel();
					return;
				}
			}
		}
		break;
		case MODEL_TYPE::MODEL_INVEN:
		{
			Button* btn = pPanel->m_ButtonPanel->getButton("sbtn_button");
			if (btn->hasCollided(btn->convertToNodeSpace(touchPoint))) {
				if (pPanel->m_ButtonPanel->isVisible()) {
					pPanel->OnPopupOpen(MODEL_TYPE::MODEL_INVEN_SUB, mtabType);	// 여긴 모델들을 표시 하는 곳이니, 모델별 사진으로 이동
					return;
				}
			}
		}
		break;
		case MODEL_TYPE::MODEL_INVEN_SUB:
		{
			Widget* btn = pPanel->getImage("img_character_boxer");
			if (btn->hasCollided(btn->convertToNodeSpace(touchPoint))) {
				if (mLock->isVisible())
				{
					if (mLock->hasCollided(mLock->convertToNodeSpace(touchPoint)))
						pPanel->UnlockModel();
				}
				else if (pPanel->isValidIndex())
					pPanel->ModelShot();
				return;
			}
		}
		break;
		}
    }
}

void ModellsBackPanel::onLayerMessage(const string& msg)
{
	fireMessage(msg);
	if (msg == "BUY_SLOT")
	{
		setLock(false);
	}
}

void ModellsBackPanel::setLock(bool lock)
{
	mLock->setVisible(lock);
	mLockBg->setVisible(lock);
	mLock->setZOrder(lock ? 101 : 0);
	mLockBg->setZOrder(lock ? 100 : 0);
}



void ModellsBackPanel::CanGoogleBuy(ModelGoodsPanel* _pPanel)
{
	if (_pPanel->getTidx() == 0)  //김소희 일때 
	{
		if (_pPanel->getMidx() <= KIMSOHEE_BLOCK)
			_pPanel->BuyModel();
		else
			_pPanel->OneStoreNotice();
	}


	else if (_pPanel->getTidx() == 1) //김나정 일때
	{
		if (_pPanel->getMidx() <= KIMNAJEONG_BLOCK)
			_pPanel->BuyModel();
		else
			_pPanel->OneStoreNotice();
	}
}