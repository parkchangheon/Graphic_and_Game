/********************************************************************
filename: 	LobbySurvivalWindowMain.h

purpose:	서바이벌 매치 기본창
*********************************************************************/
#pragma once

#include "NxFramework.h"
#include "W_DeathMatchInfo.pb.h"
#include "LobbySurvivalCell.h"

#define SURVIVAL_RANK_CELL_HIGHT 46.f
#define SURVIVAL_RANK_CELL_MAX 7

class LobbySurvivalWindowMain : public Panel, public Button::Listener
{
public:
	LobbySurvivalWindowMain();
	virtual ~LobbySurvivalWindowMain();
	void InitPanel();
	void InitImage();
	void InitButton();

	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
// Button::Listener
	virtual void onClicked(const string& name);
	virtual bool handling(STCMD &stCmd);
	virtual void onEnter() override;

	void update(float dt);

	void CreateCell();
	void RemoveRankinfoList();
	void RemoveRankView();
	Panel* CreateSurvivalInfoPanel();
	void UpdateCell(int _to, int _dst);
	void ScrollViewOffsetProcess(float _dt);

	void SetResistTxt(int64 _money, bool _enable = true);
	//void SetResistEndTxt(std::string _txt, bool _enable = true);
	void SetResistEndTxt(std::string _txt, SURVIVAL_BUTTON_KIND btnKind);
	void SetTotalRewardGold(int64 _gold);

	void ApplyData();
	void ApplyBtnSetting();
	void ApplyMyInfo();
	void ApplyGameInfo();
	void ApplyGameTitle();
	void ReadyToSurvival(W_DeathMatchInfo *_matchInfo);
	void ApplyRankGamePopup();
public:
	Panel* m_MatchButton;
	Panel* m_ReplayButton;
	Panel* m_OkButton;

	Panel* m_SurvivalInfoCell[SURVIVAL_RANK_CELL_MAX];
	vector<W_DeathMatchInfo_W_DeathMatchRankInfo*> m_RankerInfoList;

	int m_CellIndex;
	bool m_bMovingCell;
	bool m_bTouchCancel;
	float m_fMoveG;

	CCScrollView* m_pSurvivalListView;
	CCLayer* m_pSurvivalListContainer;

	CCLabelBMFont* m_pTotalRewardGold;

	int m_SeletctedCellIndex;
};
