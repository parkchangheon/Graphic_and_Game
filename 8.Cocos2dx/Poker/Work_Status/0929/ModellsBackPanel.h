#pragma once

#include "NxFramework.h"
#include "ModelListPartPanel.h"

typedef std::vector<class ModelGoodsPanel*> ModelButtonContainer;

class ModellsBackPanel : public Panel, public Nx::Layer::Listener
{
public:
	ModellsBackPanel();
	virtual ~ModellsBackPanel();

	void InitPanel();
	void SetModelType(MODEL_TYPE _type);
	void setIndex(int idx, std::vector<int> ids, int tIdx= -1, TAB_TYPE tabType = MAXIM_TAB);

	void cellTouch(const CCPoint& touchPoint);
	virtual void onLayerMessage(const string& msg);

	void CanGoogleBuy(ModelGoodsPanel* _pPanel);

private:
	void setLock(bool lock);
	TAB_TYPE mtabType;
	MODEL_TYPE m_panelType;
	int mIdx;
    CCSize mCellSize;
    CCSize mContentsSize;
    Nx::TableView* mTableView;
	Panel* mMainPanel;
	Widget* mLock;
	Widget* mLockBg;
	ModelButtonContainer mGoodsPanels;
};
