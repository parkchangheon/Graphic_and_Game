#include "pch.h"
#include "FirstBuyPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"
#include "W_PayReserveReq.pb.h"
#include "W_PayReserveRes.pb.h"
#include "W_PayReq.pb.h"
#include "W_PayRes.pb.h"
#include "CmdQueue.h"
#include "PanelHelper.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include "android/IapManager.h"
#endif

FirstBuyPanel::FirstBuyPanel()
{
	initPanel();	
}

FirstBuyPanel::~FirstBuyPanel()
{
	//destruct();
}

void FirstBuyPanel::onClicked(const string& name)
{
	if (name == getButtonName(mCloseBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		LayerManager::getSingleton().popLayer(this);
	}
	else if (name == getButtonName(mSelectBtn)) {
		GameDataManager::getSingletonPtr()->PlayGameSound(EFX_GAME_BTN);
		sendPayReserveReq(mLimitShopData.id());
	}
}

void FirstBuyPanel::initPanel()
{
	addMouseBlockPanel(this, true);
	construct(getMxmlPath() + "dmy_first_payment.mxml");
	setButtonListener(this);
	mCloseBtn = getButton("sbtn_cancel");

	CCPoint _btnPos = getDummy("dmy_button_shop").origin;
	mButtonPanel = new Panel();
	mButtonPanel->construct(getMxmlPath() + "dmy_button_shop.mxml");
	mButtonPanel->setPositionX(_btnPos.x);
	mButtonPanel->setPositionY(-_btnPos.y);
	addChild(mButtonPanel);
	mButtonPanel->release();

	mSelectBtn = mButtonPanel->getButton("sbtn_button");
	mSelectBtnLabel = mButtonPanel->getLabel("txt_price1");
	mSelectBtnUnderLabel = mButtonPanel->getLabel("txt_price1_under");
	mSelectBtn->setListener(this);
	mButtonPanel->getImage("skel_icon")->setVisible(false);
	mButtonPanel->getLabel("txt_price2_under")->setVisible(false);
	mButtonPanel->getLabel("txt_price2")->setVisible(false);
	mSelectBtn->setName("select");

	W_GameData * gameData = GameDataManager::getSingletonPtr()->GetGameDataPtr();
	for (int i = 0; i < gameData->limitshopdata_size(); i++)
	{
		W_LimitShopData shopData = gameData->limitshopdata(i);
		if (int(shopData.limittype() == W_LimitShopData_eLimitType_l_oneTime)) {
			mLimitShopData.CopyFrom(shopData);
		}
	}
	int price = mLimitShopData.price();
	string txtPrice = StringConverter::toString(price) + GameStringDepot::getSingleton().getString("TXT_COUNT_MONEY");
	mSelectBtnLabel->setString(txtPrice.c_str());
	mSelectBtnUnderLabel->setString(txtPrice.c_str());	
}

void FirstBuyPanel::sendPayReserveReq(int cashId)
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
	HttpMessage msg(req, HttpResponseHandler(FirstBuyPanel::recvWPayReserveRes), this);
	HttpManager::getSingleton().send(msg);
}

void FirstBuyPanel::recvWPayReserveRes(HttpMessage* msg)
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

bool FirstBuyPanel::handling(STCMD &stCmd)
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

void FirstBuyPanel::sendW_PayReq(string tID, string txId, string receipt)
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
	HttpMessage msg(req, HttpResponseHandler(FirstBuyPanel::recvW_PayRes), this);
	HttpManager::getSingleton().send(msg);
}

void FirstBuyPanel::recvW_PayRes(HttpMessage* msg)
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
			PanelHelper::pushFirstBuyRewardPanel(res.rewardinfo());

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