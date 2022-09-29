#pragma once

#include "NxFramework.h"
#include "ModelListPartPanel.h"

class ModelGoodsPanel : public Panel, public Button::Listener, public Panel::Listener
{
public:
	ModelGoodsPanel();
	virtual ~ModelGoodsPanel();

	void InitPanel();
	void InitImage();
	void initButton();

	virtual void onClicked(const string& name);
	virtual void onLayerMessage(const string& msg);

	void SetGoodsType(MODEL_TYPE _type);
	void SetBtnText(const std::wstring& _text);

	void setIndex(int tIdx ,int idx, TAB_TYPE tabType);
	bool isValidIndex() { return mIdx >= 0; }

private:

	CCPoint mTopPos;
	CCPoint mBottomPos;
	CCPoint mCenterPos;

	Nx::Label* m_Name;

	Button* m_OkBtn;

	SkelObject* m_GoodsPanel;
	SkelObject* m_Cover;
	Widget* mCharacter;

public:
	Panel* m_ButtonPanel;

	void OnPopupOpen(MODEL_TYPE modelType, TAB_TYPE tabType);

	void ModelShot();
	void BuyModel();
	void OneStoreNotice();
	void UnlockModel();
	void BuyTap();
	int getMidx() { return mIdx; }
	int getTidx() { return tIdx; }
private:
	MODEL_TYPE m_panelType;
	int mIdx; //리스트 인덱스 밑에 서브 인덱스
	int tIdx; //리스트 인덱스
	Widget* mCoverImg;

	Widget* m_wCharacterBlurCover;
};
