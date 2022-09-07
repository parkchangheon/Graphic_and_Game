#include "android/IapManager.h"
#include "jni/JniHelper.h"
#include "CmdList.h"
#include "CmdQueue.h"
#include "TypeDefine.pb.h"
#include "SimplePopupPanel.h"
#include "W_PayReserveReq.pb.h"
#include "W_PayReserveRes.pb.h"
#include "../../protocpp/W_RestorePayReq.pb.h"
#include "../../protocpp/W_RestorePayRes.pb.h"
#include "base/CCScheduler.h"
#include "../Game/PlayerData.h"
#include "../Game/GameDataManager.h"
#include "../Scene/LobbyScene.h"

template<> IapManager* Nx::Singleton<IapManager>::msSingleton = 0;

struct IapManagerObject //왜쓰는지 모름 
{
	JNIEnv* env;
	jobject object;

	IapManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, IAP_JAVA_OBJECT, "instance", "()Ljava/lang/Object;"))    //instance인데 IapManager로 바꿔줌
		{
			env = t.env;
			object = env->CallStaticObjectMethod(t.classID, t.methodID);
			env->DeleteLocalRef(t.classID);
		}
		else {
			object = nullptr;
		}
#else
		object = nullptr;
#endif
	}

	~IapManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};


struct GoogleIapManagerObject
{
	JNIEnv* env;
	jobject object;

	GoogleIapManagerObject() {
		JniMethodInfo t;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (JniHelper::getStaticMethodInfo(t, IAP_GOOGLE_JAVA_OBJECT, "instance", "()Ljava/lang/Object;"))
		{
			env = t.env;
			object = env->CallStaticObjectMethod(t.classID, t.methodID);
			env->DeleteLocalRef(t.classID);
		}
		else {
			object = nullptr;
		}
#else
		object = nullptr;
#endif
	}

	~GoogleIapManagerObject() {
		if (object)
			env->DeleteLocalRef(object);
	}

	jobject getObject() { return object; }
};

IapManager::IapManager()
{	
#ifdef PAY_GOOGLE
	setPaymentType(GOOGLE_STORE);
#else
	setPaymentType(ONE_STORE);
#endif // PAY_GOOGLE	
}

IapManager::~IapManager()
{
	exit();
}

void IapManager::exit()
{
	IapManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, IAP_JAVA_OBJECT, "exit", "()V")) {
		t.env->CallVoidMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void IapManager::setDevelopMode(bool delvopmode)
{
	CCLog("IapManager::setDevelopMode 1");
	IapManagerObject obj;
	if (!obj.getObject())
		return;

	CCLog("IapManager::setDevelopMode 2");
	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, IAP_JAVA_OBJECT, "setDevelopMode", "(Z)V")) {
		t.env->CallVoidMethod(obj.getObject(), t.methodID , delvopmode);
		t.env->DeleteLocalRef(t.classID);
	}
	CCLog("IapManager::setDevelopMode 3");
}

//원스토어로 보내는 결제 요청
void IapManager::sendPaymentRequest(std::string productId, std::string produceName , std::string tID)
{
	CCLog("IapManager::sendPaymentRequest productId = %s , tid = %s" , productId.c_str() , tID.c_str());
	IapManagerObject obj;
	if (!obj.getObject())
		return;

	
	CCLog("IapManager::sendPaymentRequest 1");

	//딜레이 값을 주려고 하는것인데 위험하다
	//int a = 0;
	//for (int i = 0; i < 25000; i++) { //1중첩 for문
	//	for (int j = 0; j < 25000; j++) { //2중첩 for문
	//		a++;
	//	}
	//}

	CCLog("IapManager::sendPaymentRequest 2");
	JniMethodInfo t;
	
	//NZ창헌 - sendpaymentrequest 변경 -> buyProduct
	if (JniHelper::getMethodInfo(t, IAP_JAVA_OBJECT, "buyProduct", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
		CCLog("IapManager::sendPaymentRequest 3");
		jstring jproductId = t.env->NewStringUTF(productId.c_str());
		jstring jproduceName = t.env->NewStringUTF(produceName.c_str());
		jstring jproductTid = t.env->NewStringUTF(tID.c_str());
		t.env->CallVoidMethod(obj.getObject(), t.methodID, jproductId, jproduceName, jproductTid);

		//t.env->CallVoidMethod(obj.getObject(), t.methodID, true, jproductId, jproduceName, jproductTid);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jproductId);
		t.env->DeleteLocalRef(jproduceName);
		t.env->DeleteLocalRef(jproductTid);
	}
}

void IapManager::onOneStorePurchaseRequestResult(bool isSucess, string errMsg, string tid , string receipt)
{
	CCLog("onOneStorePurchaseRequestResultonOneStorePurchaseRequestResultonOneStorePurchaseRequestResultonOneStorePurchaseRequestResult");
	CCLog("the tid is = %s and receipt is a %s", tid.c_str(), receipt.c_str());
	
	STCMD_IAP_ONESTORE_REQUEST_RESULT iapRequestResult;
	iapRequestResult.isSucess = isSucess;
	iapRequestResult.errMsg = errMsg;
	iapRequestResult.tid = tid;
	iapRequestResult.txid = "";
	iapRequestResult.receipt = receipt;
	

	CCLog("IapManager::onRequestResult isSucess = %d , tid = %s , receipt = %s", isSucess , tid.c_str(), receipt.c_str());
	CCmdQueue::getSingleton().pushQueue(iapRequestResult);
}

void IapManager::launchPurchaseFlow(string productId, string produceName, string tID)
{
	GoogleIapManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, IAP_GOOGLE_JAVA_OBJECT, "launchPurchaseFlow", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
		CCLog("IapManager::launchPurchaseFlow 3");
		jstring jproductId = t.env->NewStringUTF(productId.c_str());
		jstring jproduceName = t.env->NewStringUTF(produceName.c_str());
		jstring jproductTid = t.env->NewStringUTF(tID.c_str());
		t.env->CallVoidMethod(obj.getObject(), t.methodID,jproductId, jproduceName, jproductTid);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jproductId);
		t.env->DeleteLocalRef(jproduceName);
		t.env->DeleteLocalRef(jproductTid);
	}
	CCLog("IapManager::launchPurchaseFlow 4");
}

void IapManager::onGoogleStorePurchaseRequestResult(bool isSucess, string errMsg, string tid, string orderId, string purchaseToken)
{
	STCMD_IAP_GOOGLESTORE_REQUEST_RESULT iapRequestResult;
	iapRequestResult.isSucess = isSucess;
	iapRequestResult.errMsg = errMsg;
	iapRequestResult.tid = tid;
	iapRequestResult.orderId = orderId;
	iapRequestResult.purchaseToken = purchaseToken;
	CCLog("IapManager::onRequestResult tid = %s , txid = %s , receipt = %s", tid.c_str(), orderId.c_str(), purchaseToken.c_str());
	CCmdQueue::getSingleton().pushQueue(iapRequestResult);
}

void IapManager::consumeProduceId(string productId)
{
	CCLog("IapManager::productId = %s", productId.c_str());
	GoogleIapManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;
	if (JniHelper::getMethodInfo(t, IAP_GOOGLE_JAVA_OBJECT, "consumeProductId", "(Ljava/lang/String;)V")) {
		jstring jproductId = t.env->NewStringUTF(productId.c_str());
		t.env->CallVoidMethod(obj.getObject(), t.methodID, jproductId);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jproductId);		
	}
	CCLog("IapManager::consumeProduceId 4");
}

void IapManager::checkAsyncInventory()
{
	GoogleIapManagerObject obj;
	if (!obj.getObject())
		return;

	JniMethodInfo t;

	CCLog("checkAsyncInventory");

	if (JniHelper::getMethodInfo(t, IAP_GOOGLE_JAVA_OBJECT, "checkAsyncInventory", "()V")) {
		t.env->CallVoidMethod(obj.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void IapManager::onGoogleStoreCheckPurchaseRequestResult(bool isSucess, string inappId, string tid, string orderId, string purchaseToken)
{
	CCLog("onGoogleStoreCheckPurchaseRequestResult");
	STCMD_IAP_GOOGLESTORE_CHECK_REQUEST_RESULT iapRequestResult;
	iapRequestResult.isSucess = isSucess;
	iapRequestResult.inappId = inappId;
	iapRequestResult.tid = tid;
	iapRequestResult.orderId = orderId;
	iapRequestResult.purchaseToken = purchaseToken;
	CCLog("IapManager::onRequestResult tid = %s , txid = %s , receipt = %s", tid.c_str(), orderId.c_str(), purchaseToken.c_str());
	CCmdQueue::getSingleton().pushQueue(iapRequestResult);
}


int t = 0;
void IapManager::checkUnpaid(std::string tid, std::string pid, std::string uid)
{

	CCLog("itsalamaicoom");
	IapManagerObject obj;

	if (!obj.getObject())
		return;
	
	
	if (t < 5) {
		int a = 0;
		for (int i = 0; i < 25000; i++) { //1중첩 for문
			for (int j = 0; j < 25000; j++) { //2중첩 for문
				a++;
			}
		}
		t++;
	}
	

	JniMethodInfo t;

	
	if (JniHelper::getMethodInfo(t, IAP_JAVA_OBJECT, "restorePurchases", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
		jstring jproductId = t.env->NewStringUTF(pid.c_str());
		jstring jproduceName = t.env->NewStringUTF(uid.c_str());
		jstring jproductTid = t.env->NewStringUTF(tid.c_str());
		t.env->CallVoidMethod(obj.getObject(), t.methodID, jproductId, jproductTid, jproduceName);
		//t.env->CallVoidMethod(obj.getObject(), t.methodID, jproductId, jproductTid);


		//t.env->CallVoidMethod(obj.getObject(), t.methodID, true, jproductId, jproduceName, jproductTid);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jproductId);
		t.env->DeleteLocalRef(jproductTid);
		t.env->DeleteLocalRef(jproduceName);
	}
}