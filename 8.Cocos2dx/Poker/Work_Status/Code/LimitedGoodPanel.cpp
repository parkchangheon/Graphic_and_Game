#include "pch.h"
#include "LimitedGoodPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "CmdQueue.h"
#include "W_PayRes.pb.h"
#include "PanelHelper.h"
#include "W_PayReserveReq.pb.h"
#include "W_PayReserveRes.pb.h"
#include "W_PayReq.pb.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	#include "android/IapManager.h"
#endif

LimitedGoodPanel::LimitedGoodPanel(LIMITED_TYPE type)
{
	mLimitedType = type;
	initShopData();
	initPanel();	
	refreshTitle();
}

LimitedGoodPanel::~LimitedGoodPanel()
{

}

void LimitedGoodPanel::initPanel()
{
	addMouseBlockPanel(this,true);
	construct(getMxmlPath() + "dmy_limited_goods.mxml");	
	mLimitedTimeLabel = getLabel("txt_info1");
	mLimitedTitleLabel = getLabel("txt_title");
	mLimitedTitleUnderLabel = getLabel("txt_title_under");
	mLimitedDescLabel = getLabel("txt_info2");

	if (mShopDatas.size() > 0) {
		if (mLimitedType == LIMITED_JACKPOT)
			mLeftPanel = new LimitedGoodContentPanel(LimitedGoodContentPanel::LIMITED_JACKPOT_1);
		else if (mLimitedType == LIMITED_MADE)
			mLeftPanel = new LimitedGoodContentPanel(LimitedGoodContentPanel::LIMITED_MADE_1);
		else if (mLimitedType == ALLIN)
			mLeftPanel = new LimitedGoodContentPanel(LimitedGoodContentPanel::LIMITED_ALLIN_1);

		addChild(mLeftPanel);
		mLeftPanel->release();
		mLeftPanel->setPosition(getImage("dmy_limited_goods_slot1")->getPosition());
		mLeftPanel->setLimitShopData(mShopDatas[0]);
		mLeftPanel->setListener(this);
	}

	if (mShopDatas.size() > 1) {
		if (mLimitedType == LIMITED_JACKPOT)
			mRightPanel = new LimitedGoodContentPanel(LimitedGoodContentPanel::LIMITED_JACKPOT_2);
		else if (mLimitedType == LIMITED_MADE)
			mRightPanel = new LimitedGoodContentPanel(LimitedGoodContentPanel::LIMITED_MADE_2);
		else if (mLimitedType == ALLIN)
			mRightPanel = new LimitedGoodContentPanel(LimitedGoodContentPanel::LIMITED_ALLIN_2);		

		addChild(mRightPanel);
		mRightPanel->release();
		mRightPanel->setPosition(getImage("dmy_limited_goods_slot2")->getPosition());
		mRightPanel->setLimitShopData(mShopDatas[1]);
		mRightPanel->setListener(this);
	}

	mCloseBtn = getButton("sbtn_cancel");
	mLimitedDescLabel->setString(GameStringDepot::getSingleton().getString("LIMITED_DESC").c_str());
	setButtonListener(this);
}

void LimitedGoodPanel::onClicked(const string& name)
{
	if (name == getButtonName(mCloseBtn)) {
		LayerManager::getSingleton().popLayer(this);
	}
}

void LimitedGoodPanel::update(float delta)
{
	refreshTImeDesc();
}

void LimitedGoodPanel::refreshTitle()
{
	if (mLimitedType == LIMITED_JACKPOT) {
		mLimitedTitleLabel->setString(GameStringDepot::getSingleton().getString("LIMITED_JACKPOT_TITLE").c_str());
		mLimitedTitleUnderLabel->setString(GameStringDepot::getSingleton().getString("LIMITED_JACKPOT_TITLE").c_str());
	}
	else if (mLimitedType == LIMITED_MADE) {
		mLimitedTitleUnderLabel->setString(GameStringDepot::getSingleton().getString("LIMITED_MADE_TITLE").c_str());
		mLimitedTitleLabel->setString(GameStringDepot::getSingleton().getString("LIMITED_MADE_TITLE").c_str());
	}
	else if (mLimitedType == ALLIN) {
		mLimitedTitleUnderLabel->setString(GameStringDepot::getSingleton().getString("LIMITED_ALLIN_TITLE").c_str());
		mLimitedTitleLabel->setString(GameStringDepot::getSingleton().getString("LIMITED_ALLIN_TITLE").c_str());
	}
}

void LimitedGoodPanel::refreshTImeDesc()
{
	if (mLimitedType == LIMITED_JACKPOT) {
		string timeFormatStr = nxGetTimeFormatLong(GameDataManager::getSingleton().getJackPotLimitedTime());
		string timeStr = NxGetFormatString(GameStringDepot::getSingleton().getString("LIMITED_REMAIN_TIME"), timeFormatStr);
		mLimitedTimeLabel->setString(timeStr.c_str());
	}
	else if (mLimitedType == LIMITED_MADE) {
		string timeFormatStr = nxGetTimeFormatLong(GameDataManager::getSingleton().getMadeLimitedTime());
		string timeStr = NxGetFormatString(GameStringDepot::getSingleton().getString("LIMITED_REMAIN_TIME"), timeFormatStr);
		mLimitedTimeLabel->setString(timeStr.c_str());
	}
	else if (mLimitedType == ALLIN) {
		mLimitedTimeLabel->setVisible(false);
	}

}

void LimitedGoodPanel::sendPayReserveReq(int cashId)
{
	mBuyCashId = cashId;
	W_PayReserveReq req;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	if (IapManager::getSingleton().getPaymentType() == IapManager::ONE_STORE)
		req.set_markettype(OneStore);
	else
		req.set_markettype(Google);
#else
	req.set_markettype(Local);
#endif

	req.set_paytype(ePayLimitShop);
	req.set_id(cashId);
	HttpMessage msg(req, HttpResponseHandler(LimitedGoodPanel::recvWPayReserveRes), this);
	HttpManager::getSingleton().send(msg);
}

void LimitedGoodPanel::recvWPayReserveRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}

	W_PayReserveRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success()) {
		CCLog("W_PayReserveRes sucess");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
		if (IapManager::getSingleton().getPaymentType() == IapManager::ONE_STORE) {
			CCLog("W_PayReserveRes onestore");
			IapManager::getSingleton().sendPaymentRequest(res.productid(), StringConverter::toString(res.uid()), res.tid());
		}
		else {
			mGoogleTid = res.productid();
			IapManager::getSingleton().launchPurchaseFlow(res.productid(), "", res.tid());
		}
#else
		//WebService::getSingletonPtr()->_sendCashBuyReq(mBuyCashId);
		CCLog("W_PayReserveRes win2");
		STCMD_IAP_ONESTORE_REQUEST_RESULT iapRequestResult;
		iapRequestResult.isSucess = true;
		iapRequestResult.errMsg = "";
		iapRequestResult.tid = res.tid();
		iapRequestResult.txid = "win";
		iapRequestResult.receipt = res.productid();
		CCmdQueue::getSingleton().pushQueue(iapRequestResult);

#endif // DEBUG


	}
	else {
		CCLog("W_PayReserveRes fail");
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
	}
}

bool LimitedGoodPanel::handling(STCMD &stCmd)
{
	if (!isVisible()) {
		CCLog("NO vislble false");
		return false;
	}


	if (auto *pstIt = castCMD<STCMD_IAP_ONESTORE_REQUEST_RESULT>(&stCmd))
	{
		STCMD_IAP_ONESTORE_REQUEST_RESULT res = *pstIt;
		if (res.isSucess) {
			CCLog("STCMD_IAP_REQUEST_RESULT sucess res.tid = %s , res.txid = %s , res.receipt = %s", res.tid.c_str(), res.txid.c_str(), res.receipt.c_str());
			sendW_PayReq(res.tid, res.txid, res.receipt);
		}
		else {
			CCLog("STCMD_IAP_REQUEST_RESULT false");
			SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errMsg, "IAP Request");
			LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
		}
		return true;
	}
	else if (auto *pstIt = castCMD<STCMD_IAP_GOOGLESTORE_REQUEST_RESULT>(&stCmd))
	{
		STCMD_IAP_GOOGLESTORE_REQUEST_RESULT res = *pstIt;
		if (res.isSucess) {
			CCLog("STCMD_IAP_REQUEST_RESULT sucess res.tid = %s , res.txid = %s , res.receipt = %s", res.tid.c_str(), res.orderId.c_str(), res.purchaseToken.c_str());
			sendW_PayReq(res.tid, res.orderId, res.purchaseToken);
		}
		else {
			CCLog("STCMD_IAP_REQUEST_RESULT false");
			SimplePopupPanel* panel = new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errMsg, "IAP Request");
			LayerManager::getSingleton().pushDynamicLayer(panel, DYNAMIC_PUSH_LAYER);
		}
		return true;
	}
	return false;
}

void LimitedGoodPanel::sendW_PayReq(string tID, string txId, string receipt)
{
	W_PayReq req;
	req.set_tid(tID);
	req.set_txid(txId);
	req.set_receipt(receipt);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE) {
		req.set_order_id(txId);
	}
#endif
	HttpMessage msg(req, HttpResponseHandler(LimitedGoodPanel::recvW_PayRes), this);
	HttpManager::getSingleton().send(msg);
}

void LimitedGoodPanel::recvW_PayRes(HttpMessage* msg)
{
	if (msg->hasCode()) {
		return;
	}


	W_PayRes res;
	res.ParseFromArray(msg->getData(), msg->getSize());
	NXASSERT(res.IsInitialized());

	if (res.success()) {
		CCLog("recvW_PayRes sucess");

		if (res.has_rewardinfo())
			PanelHelper::pushLimitedAllRewardPanel(res.rewardinfo());

		if (res.has_playerinfo())
		{
			GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
			//창을 끈다
			LayerManager::getSingleton().popLayer(this);
		}

		//똑같은 걸 두번 보낼수도 있어서...
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE && !mGoogleTid.empty()) {
			IapManager::getSingleton().consumeProduceId(mGoogleTid);
			mGoogleTid = "";
		}

		if (IapManager::getSingleton().getPaymentType() == IapManager::GOOGLE_STORE) {
			CCLog("W_PayRes checkAsyncInventory");
			IapManager::getSingleton().checkAsyncInventory();
		}
#endif
	}
	else {
		CCLog("recvW_PayRes fail");
		if (res.has_errorstring())
		{
			LayerManager::getSingleton().pushDynamicLayer(new SimplePopupPanel(SimplePopupPanel::SimplePopupType::OKNotice, res.errorstring()), DYNAMIC_PUSH_LAYER);
		}
	}

	for (int i = 0; i < res.limitshopinfo_size(); i++)
	{
		GameDataManager::getSingleton().setLimitShopInfo(res.limitshopinfo(i));
	}

	if (res.has_playerinfo()) {
		GameDataManager::getSingleton().setPlayerInfo(res.playerinfo());
		GameDataManager::getSingletonPtr()->OnWebserviceMassage(W_S2C_UPDATE_PLAYER_INFO_RES);
	}
}

void LimitedGoodPanel::initShopData()
{
	mShopDatas.clear();
	W_GameData * gameData = GameDataManager::getSingletonPtr()->GetGameDataPtr();
	for (int i = 0; i < gameData->limitshopdata_size(); i++)
	{
		W_LimitShopData shopData = gameData->limitshopdata(i);
		if (int(shopData.limittype()) == int(mLimitedType)) {
			mShopDatas.push_back(shopData);
		}
	}
}

void LimitedGoodPanel::onLayerMessage(const string& msg)
{
	if (msg.find("LIMITED_SHOP_ID_") != string::npos){
		int shopId = nxExtractInt(msg, "LIMITED_SHOP_ID_");
		sendPayReserveReq(shopId);
	}
}

void LimitedGoodPanel::onRefresh()
{
	setVisible(true);
}

void LimitedGoodPanel::onEnter()
{
	Panel::onEnter();

	scheduleUpdate();
}