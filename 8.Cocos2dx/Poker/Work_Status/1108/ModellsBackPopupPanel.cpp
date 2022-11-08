#include "pch.h"
#include "ModellsBackPopupPanel.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "SceneUtil.h"
#include "PanelHelper.h"

#include "ModellsBackPanel.h"
#include "ModelTempTabel.h"


ModellsBackPopupPanel::ModellsBackPopupPanel(int mIdx, MODEL_TYPE modelType, TAB_TYPE tabType)
{
	mListType = modelType;
	m_vModelIdx.clear();
	if (tabType == TAB_TYPE::MAXIM_TAB) {
		for (int x = 0; x < GameDataManager::getSingletonPtr()->getModelList(tabType).size(); x++)
		{
			m_vModelIdx.push_back(GameDataManager::getSingletonPtr()->BuyList_MAXIM[x]);
		}
	}
	else if (tabType == TAB_TYPE::RACING_TAB){
		for (int x = 0; x < GameDataManager::getSingletonPtr()->getModelList(tabType).size(); x++)
		{
			m_vModelIdx.push_back(GameDataManager::getSingletonPtr()->BuyList_RACING[x]);
		}
	}
	
	mModelListIDX = mIdx;
	mtapType = tabType;
	initPanel();
}

ModellsBackPopupPanel::~ModellsBackPopupPanel()
{

}


void ModellsBackPopupPanel::initPanel()
{
	addMouseBlockPanel(this, true);	// 뒷 배경 터치 이벤트 블럭처리
	construct(getMxmlPath() + "dmy_modells_back_popup_panel.mxml");

	// 테이블뷰 생성
	mCellSize = getDummy("dmy_goods_panel").size;
	CCRect tableViewRect = getDummyUI("dmy_scrollsize");
	mTableView = Nx::TableView::create(this, tableViewRect.size);
	addChild(mTableView);
	mTableView->setDirection(ScrollView::Direction::VERTICAL);
	mTableView->setPosition(tableViewRect.origin);
	mTableView->setDelegate(this);
	mTableView->setBounceable(true);
	mTableView->reloadData();
	

	getButton("sbtn_cancel")->setListener(this);
	getButton("sbtn_button_info")->setListener(this);


	// 보관함 모델 '더보기' 팡업창에서는 '청약철회 규정 안내' 버튼과 이미지를 안보이게 한다
	if (mListType == MODEL_TYPE::MODEL_INVEN_SUB)
	{
		getLabel("txt_regulation")->setVisible(false);;
		getImage("sbtn_button_info")->setVisible(false);
	}
}

void ModellsBackPopupPanel::onClicked(const string& name)
{
	if (name == "sbtn_cancel") {
		LayerManager::getSingleton().popLayer(this);
	}
	else if (name == "sbtn_button_info")
	{
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		GameDataManager::getSingletonPtr()->ShowCustomWebview(WEB_REFUND_TYPE);
	}

}


cocos2d::CCSize ModellsBackPopupPanel::cellSizeForTable(CCTableView* table)
{
	return mCellSize;
}


CCTableViewCell* ModellsBackPopupPanel::tableCellAtIndex(CCTableView* table, ssize_t idx)
{
	idx = (maxCount - 1) - idx;
	CCTableViewCell* cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		ModellsBackPanel* pPanel = new ModellsBackPanel();
		cell->addChild(pPanel);
		pPanel->release();
		pPanel->setTag(1);
		
		// 모델 리스트에서 모델별 리스트를 볼 때는 샵 뿐이다.
		pPanel->SetModelType(mListType);
		pPanel->setIndex(idx, getIndices(idx, mtapType) , mModelListIDX, mtapType);
		pPanel->setPosition(ccp(0, -pPanel->getContentSize().height / 2.f + 16.f));
		pPanel->setListener(this);
	}
	else {
		ModellsBackPanel* pPanel = dynamic_cast<ModellsBackPanel*>(cell->getChildByTag(1));
		if (pPanel) {
			pPanel->setIndex(idx, getIndices(idx, mtapType), mModelListIDX, mtapType);
		}
	}

	return cell;
}

ssize_t ModellsBackPopupPanel::numberOfCellsInTableView(CCTableView* table)
{
	uint count = 0;
	count = g_ModelSubTempTableArr[mModelListIDX].size();
	count = GameDataManager::getSingletonPtr()->m_ModelShopList_MAXIM[mModelListIDX].size();
	

#if(TargetingServer == SIMYUI_SERVER)
	if (mModelListIDX == 0)
		maxCount = 3;
	else if (mModelListIDX == 1)
		maxCount = 1;
#else
	maxCount = count % 3 > 0 ? (count / 3) + 1 : (count / 3);
#endif

	return maxCount;
}

void ModellsBackPopupPanel::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	ModellsBackPanel* pPanel = dynamic_cast<ModellsBackPanel*>(cell->getChildByTag(1));
	if (pPanel) {
		pPanel->cellTouch(table->getTouchPoint());
	}
}

void ModellsBackPopupPanel::onLayerMessage(const string& msg)
{
}

void ModellsBackPopupPanel::setIndex(int model_list_idx, TAB_TYPE tapType)
{
	// 모델 이름 설정
	W_DisplayModelData temp = GameDataManager::getSingletonPtr()->FindTitleModel(model_list_idx, tapType);
	mtapType = tapType;
	getLabel("txt_characterinfo")->setString(temp.name().c_str());

}


std::vector<int> ModellsBackPopupPanel::getIndices(int idx, TAB_TYPE taptype)
{
	std::vector<int> outData;
	
	if (mListType == MODEL_TYPE::MODEL_SHOP_SUB)
	{
		for (int i = idx * 3; i < (idx * 3 + 3); ++i)
		{
			if (taptype == TAB_TYPE::MAXIM_TAB) {
				if (i < GameDataManager::getSingletonPtr()->m_ModelShopList_MAXIM[mModelListIDX].size())
					outData.push_back(i);   //여기보다 더 상단. (여기는 모델 사진 없애는 곳)
			}
			else if (taptype == TAB_TYPE::RACING_TAB) {
				if (i < GameDataManager::getSingletonPtr()->m_ModelShopList_RACING[mModelListIDX].size())
					outData.push_back(i);
			}
		}

	}
	else if (mListType == MODEL_TYPE::MODEL_INVEN_SUB)
	{
		for (int i = idx * 3; i < (idx * 3 + 3); ++i)
		{
			if (i < m_vModelIdx[mModelListIDX].size())
				outData.push_back(m_vModelIdx[mModelListIDX][i]);
			else
			{
				// idx는 슬롯으로 보면 된다. 해당 슬롯을 구매 했다면 구매표시를 해제 한다.
				if (GameDataManager::getSingleton().hasSlot(mModelListIDX, i, taptype))
					outData.push_back(-100);
			}
		}
	}
	
	return outData;
}

void ModellsBackPopupPanel::onEnter()
{
	Panel::onEnter();


#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	scheduleUpdate();
#endif
}
