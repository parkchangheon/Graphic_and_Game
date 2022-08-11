#pragma once
//#include "NxDefine.h"
//#include "pch.h"
//
//#include "NxSingleton.h"
#include "NxFramework.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "jni/JniHelper.h"
#endif
#include "NxHttpManager.h"

#define IAP_JAVA_OBJECT "com/newzensoft/inApp/IapManager"
#define IAP_GOOGLE_JAVA_OBJECT "com/newzensoft/googleinapp/GoogleIapManager"

using google::protobuf::Message;

class IapManager : public Nx::Singleton < IapManager > , public Panel
{
public:
	enum PaymentTypeType
	{
		ONE_STORE = 0,
		GOOGLE_STORE = 1,
	};

public:
	IapManager();
	~IapManager();

public:	
	void exit();	//종료시 exit 해준다.
	void setDevelopMode(bool delvopmode);	//처음 설정 맨 처음 한번만 인정
	void sendPaymentRequest(string productId, string produceName, string tID);		//원스토어 결제
	void launchPurchaseFlow(string productId, string produceName, string tID);		//구글 스토어 결제
	void consumeProduceId(string productId);
	void checkAsyncInventory();

//payment type
	void setPaymentType(PaymentTypeType type) { mPaymentType = type; }
	PaymentTypeType getPaymentType() { return mPaymentType; }

public:
	void onOneStorePurchaseRequestResult(bool isSucess, string errMsg , string tid , string txid , string receipt);
	void onGoogleStorePurchaseRequestResult(bool isSucess, string errMsg, string tid, string orderId, string purchaseToken);
	void onGoogleStoreCheckPurchaseRequestResult(bool isSucess, string inappId, string tid, string orderId, string purchaseToken);

private:
	PaymentTypeType mPaymentType;
};

