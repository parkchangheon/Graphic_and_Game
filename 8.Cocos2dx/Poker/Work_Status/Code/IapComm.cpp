/**********************************
 Java Native Interface library
**********************************/
#include <jni.h>
#include "jni/JniHelper.h"
#include "android/IapManager.h"
#include "../Scene/LobbyScene.h"


extern "C"
{

	/** This is the C implementation of the Java native method.
	@param env Pointer to JVM environment
	@param thiz Reference to Java this object
	*/
	JNIEXPORT void JNICALL Java_com_newzensoft_inApp_IapManager_OnIapResult(JNIEnv* env, jclass thiz, jboolean sucess, jstring errMsg, jstring tid ,jstring receipt)
	{
		CCLog("Java_com_newzensoft_social_OneStoreManager_OnOneStoreLoginResult");
		bool isSucess = sucess;
		IapManager::getSingleton().onOneStorePurchaseRequestResult(isSucess, JniHelper::jstring2string(errMsg), JniHelper::jstring2string(tid), JniHelper::jstring2string(receipt));
	}

	JNIEXPORT void JNICALL Java_com_newzensoft_googleinapp_GoogleIapManager_OnIapResult(JNIEnv* env, jclass thiz, jboolean sucess, jstring errMsg, jstring tid, jstring txid, jstring receipt)
	{
		CCLog("Java_com_newzensoft_googleinApp_GoogleIapManager_OnIapResult");
		bool isSucess = sucess;
		IapManager::getSingleton().onGoogleStorePurchaseRequestResult(isSucess, JniHelper::jstring2string(errMsg), JniHelper::jstring2string(tid), JniHelper::jstring2string(txid), JniHelper::jstring2string(receipt));
	}

JNIEXPORT void JNICALL Java_com_newzensoft_inApp_IapManager_sendPID(JNIEnv *env, jclass clazz,  jstring pid) {
    IapManager::getSingleton().sendPID(JniHelper::jstring2string(pid));

}


/*	JNIEXPORT jstring JNICALL Java_com_newzensoft_inApp_IapManager_CallPurchaseStart(JNIEnv* env, jclass clazz, jstring pid) {
		CCLog("start Purchase Flow");
		return pid;
	}*/
}


