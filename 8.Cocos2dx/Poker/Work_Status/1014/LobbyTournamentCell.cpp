#include "pch.h"
#include "LobbyTournamentCell.h"
#include "HeroUtil.h"
#include "socket/TCPService.h"
#include "GameDataManager.h"
#include "SceneUtil.h"
#include "Web/WebService.h"
#include "GameStringDepot.h"
#include "LobbyUIPanel.h"
#include "PanelHelper.h"

LobbyTournamentCell::LobbyTournamentCell()
{
	m_CellInfo = nullptr;

	InitPanel();
	InitImage();
	InitButton();

	setTouchable(false);
	setButtonListener(this);
}

LobbyTournamentCell::~LobbyTournamentCell()
{
	if (m_CellInfo)
	{
		NX_SAFE_DELETE(m_CellInfo);
		m_CellInfo = nullptr;
	}
}

void LobbyTournamentCell::InitPanel()
{
	construct(getMxmlPath() + "dmy_tournament_button.mxml");
}

void LobbyTournamentCell::InitImage()
{
	m_labelTitle = getLabel("txt_tournament_title");
	m_labelTicket = getLabel("txt_myticket");
	m_labelTicketSum = getLabel("txt_ticket1_sum");
	m_labelGift = getLabel("txt_gift");
	m_labelGift1 = getLabel("txt_fame_sum");
	m_labelGift2 = getLabel("txt_gold1_sum");

	m_labelTitle->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_labelTicket->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));
	m_labelTicketSum->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));  
	m_labelGift1->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET)); 
	m_labelGift2->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));     
	m_labelGift->setAnchorPoint(ccp(0, LABEL_ANCHOR_OFFSET));    
	  
	getSkel("skel_lock")->setVisible(false);  


}


void LobbyTournamentCell::InitButton()
{ 
	m_btnChannel = getButton("sbtn_tournament_button"); 
	m_btnChannel->setType(Button::NoPressImg);
	m_btnChannel->setPaused(true);
}

void LobbyTournamentCell::OnMessage(int type, void* _msg, int parm1, int parm2)
{
	
}

void LobbyTournamentCell::onClicked(const string& name)
{
	if (name == "sbtn_tournament_button")
	{
		//int _dst = getButton("sbtn_tournament_button")->getTag();
		//SendTournamentReady(_dst);
	}
}

void LobbyTournamentCell::SelectTournamentCell(int _dst)
{
	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	W_TourInfo _tourInfo = _pInfoData->tourinfo(_dst);

	if (_tourInfo.isopen()) {
		GameDataManager::getSingletonPtr()->m_seasonId = _pInfoData->seasonid();
		GameDataManager::getSingletonPtr()->m_TournamentId = _tourInfo.tourid();
		WebService::getSingletonPtr()->TournamentIdReq(GameDataManager::getSingletonPtr()->m_TournamentId);
	}
	else {
		//PanelHelper::pushAnnounceNotiPanel(GameStringDepot::getSingleton().getString("TOURMENT_UPDATE_DESC"));
		PanelHelper::pushSimpleConfirmPopupPanel(GameStringDepot::getSingleton().getString("TOURMENT_UPDATE_DESC") , GameStringDepot::getSingleton().getString("TXT_INFORMATION"));		
	}
}

void LobbyTournamentCell::update(float dt)
{

}

bool LobbyTournamentCell::handling(STCMD &stCmd)
{
	return false;
}

void LobbyTournamentCell::SetCellData(int _index)
{
	int _size = GameDataManager::getSingletonPtr()->m_TourOfInfo->tourinfo_size();

	if (_size <= _index)
		return;

	W_TourOfInfo* _pInfoData = GameDataManager::getSingletonPtr()->m_TourOfInfo;
	W_TourInfo _tourInfo = _pInfoData->tourinfo(_index);
	W_TourStepInfo _stepInfo = _tourInfo.stepinfo(0);

	m_btnChannel->setEnable(_tourInfo.isopen());

	if (m_CellInfo)
	{
		NX_SAFE_DELETE(m_CellInfo);
		m_CellInfo = nullptr;
	}
	m_CellInfo = new W_ChannelInfo(_stepInfo.channelinfo());

	W_TourInfo_W_TourWinner _tWinnerInfo = _tourInfo.twinner();
	W_TourInfo_W_TourCharge _tChargeInfo = _tourInfo.tcharge();

	m_labelTitle->setString(_tourInfo.name().c_str());

	string _ticketLabel = GameStringDepot::getSingletonPtr()->getString("TXT_TICKET_UNIT");	//티켓 보유량 
	m_labelTicket->setString(_ticketLabel.c_str());

	int _haveticketCount = GameDataManager::getSingletonPtr()->getTicketCount(_tourInfo.ticketid());
	string _haveTicket = GameStringDepot::getSingletonPtr()->getString("TXT_NORMAL_CLASS_UNIT") + " ";
	_haveTicket += StringConverter::toString(_haveticketCount) + GameStringDepot::getSingletonPtr()->getString("TXT_TICKET_COUNT");
	m_labelTicketSum->setString(_haveTicket.c_str());

	string _winHonor = GameStringDepot::getSingletonPtr()->getString("TXT_GET_FAME_LABEL");	//획득 명성
	_winHonor += StringConverter::toString(_tWinnerInfo.repute());
	m_labelGift1->setString(_winHonor.c_str());
	
	string _winMoney = GameStringDepot::getSingletonPtr()->getString("TXT_GET_GOLD_LABEL");	//획득 골드
	_winMoney += GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_tWinnerInfo.money()), 1);
	m_labelGift2->setString(_winMoney.c_str());


	string _giftTxt = GameStringDepot::getSingletonPtr()->getString("TXT_WINNER_GIFT");	//최종우승보상
	m_labelGift->setString(_giftTxt.c_str());

	string _frameName1 = "";
	string _frameName2 = "";

	ccColor3B lockTabColor = { 109, 109, 109 };	//잠겨있는거 선택시
	ccColor3B unlockTabColor;
	ccColor3B unlockTitleColor;	//오픈될을때 타이틀 색깔 마카오 라스베가스등
	ccColor3B lockTitleColor = { 151, 151, 151 };	//잠겨있는거 선택시
	ccColor3B lockDescColor = { 105,105,105 };
	ccColor3B unlockDescColor;
	switch (m_CellInfo->gamekind())
	{
	case GameKind::GAMEKIND_7POKER:
		unlockTabColor = { 235, 122, 122 };
		unlockTitleColor = { 255, 241, 233 };
		unlockDescColor = { 186,80,86 };	

		_frameName1 = "seven_";
		_frameName2 = "lock_saven";
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		unlockTabColor = { 111, 151, 224 };
		unlockTitleColor = { 233, 246, 255 };
		unlockDescColor = { 73, 105, 173 };		
		_frameName1 = "highlow_";
		_frameName2 = "lock_highlow";
		break;
	case GameKind::GAMEKIND_BADUKI:
		unlockTabColor = { 128, 228, 114 };
		unlockTitleColor = { 243, 255, 233 };
		unlockDescColor = { 79, 163, 80 };		
		_frameName1 = "badugi_";
		_frameName2 = "lock_badugi";
		break;
	case GameKind::GAMEKIND_HOLDEM:
		unlockTabColor = { 105, 228, 212 };
		unlockTitleColor = { 233, 255, 255 };
		unlockDescColor = { 65, 165, 153 };			
		_frameName1 = "texas_";
		_frameName2 = "lock_texas";
		break;
	}

	if (m_btnChannel->isEnabled())
	{
		getSkel("skel_lock")->setVisible(false);
		_frameName1 += "stay";
		m_labelGift->setColor(unlockTabColor);
		m_labelTicket->setColor(unlockTabColor);

		m_labelTicketSum->setColor(unlockDescColor);
		m_labelGift1->setColor(unlockDescColor);
		m_labelGift2->setColor(unlockDescColor);

		m_labelTitle->setColor(unlockTitleColor);
	}
	else
	{
		getSkel("skel_lock")->setVisible(true);
		_frameName1 += "stayoff";
		m_labelGift->setColor(lockTabColor);
		m_labelTicket->setColor(lockTabColor);

		m_labelTicketSum->setColor(lockDescColor);
		m_labelGift1->setColor(lockDescColor);
		m_labelGift2->setColor(lockDescColor);

		m_labelTitle->setColor(lockTitleColor);
	}

	//nz창헌
	//m_btnChannel->getButtonSkelObject()->playAnimation(_frameName1, true);
	//getSkel("skel_lock")->playAnimation(_frameName2);

	getButton("sbtn_tournament_button")->setTag(_index);

	////GameDataManager::getSingletonPtr()->m_TournamentId = _tourInfo.tourid();
	//string _roundTxt = GameStringDepot::getSingletonPtr()->getString("TXT_ROUND_LABEL") + StringConverter::toString(_tourInfo.roundcnt());

	//string _winMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_tWinnerInfo.money()), 1);
	//string _winHonor = "x" + StringConverter::toString(_tWinnerInfo.repute());
	//
	//int _ticketId = _tourInfo.ticketid() / 100;
	//getSkel("skel_ticket1")->playAnimation("icon_ticket" + StringConverter::toString(_ticketId));
	
	
	//
	//string _chargeMoney = GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(_tChargeInfo.money()), 1);
	//string _chargeTicket = "x" + StringConverter::toString(_tChargeInfo.ticketcnt());
	//int _chargeTicketId = _tChargeInfo.ticketid()/100;
	//getSkel("skel_ticket3")->playAnimation("icon_ticket" + StringConverter::toString(_chargeTicketId));

	////_tourInfo.stepinfo_size();

	//getLabel("txt_tournament_title")->setString(_tourInfo.name().c_str());

	//getLabel("txt_gold1_sum")->setString(_winMoney.c_str());
	//getLabel("txt_gold2_sum")->setString(_chargeMoney.c_str());
	//getLabel("txt_trophy_sum")->setString(_winHonor.c_str());
	//getLabel("txt_ticket1_sum")->setString(_haveTicket.c_str());	//보유수
	////getLabel("txt_ticket2_sum")->setString(_winTicket.c_str());
	//getLabel("txt_ticket3_sum")->setString(_chargeTicket.c_str());
	//getLabel("txt_round_sum")->setString(_roundTxt.c_str());

	//getButton("sbtn_tournament_button")->setTag(_index);

	//if (m_CellInfo->gamekind() == GAMEKIND_7POKER)
	//{
	//	getButton("sbtn_tournament_button")->getButtonSkelObject()->setSkin("seven_poker");
	//}
	//else if (m_CellInfo->gamekind() == GAMEKIND_HIGH_LOW)
	//{
	//	getButton("sbtn_tournament_button")->getButtonSkelObject()->setSkin("highlow");
	//}
	//else if (m_CellInfo->gamekind() == GAMEKIND_BADUKI)
	//{
	//	getButton("sbtn_tournament_button")->getButtonSkelObject()->setSkin("badugi");
	//}
	//else if (m_CellInfo->gamekind() == GAMEKIND_HOLDEM)
	//{
	//	getButton("sbtn_tournament_button")->getButtonSkelObject()->setSkin("texasholdem");
	//}
}

