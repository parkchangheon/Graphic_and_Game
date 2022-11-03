/**********************************
 Java Native Interface library
**********************************/
#include <jni.h>
#include "jni/JniHelper.h"
#include "android/UnityAdsManager.h"
#include "CmdList.h"
#include "SimplePopupPanel.h"
#include "HeroApp.h"
#include "GameStringDepot.h"
#include "CmdQueue.h"
#include <jni.h>


extern "C"
{
	JNIEXPORT void JNICALL
		Java_com_newzensoft_admob_UnityAdsManager_CallBackReward(JNIEnv* env, jclass clazz) {
        // TODO: implement CallBackReward()
        CCLog("Reward Earned!!!!!!!!!");
        UnityAdsManager::getSingleton().SetReward(true);
        UnityAdsManager::getSingleton().HandleReward();

	}


    JNIEXPORT void JNICALL Java_com_newzensoft_admob_UnityAdsManager_CallBackFailRewardedVideoAd(JNIEnv * env, jclass clazz) {
        CCLog("Unity CallBack Fail");

    }



    JNIEXPORT void JNICALL Java_com_newzensoft_admob_UnityAdsManager_CallBackOnRewardAdClosed(JNIEnv * env, jclass clazz) {
        CCLog("CallBackOnRewardAdClosed !!!!!!!!!");
        UnityAdsManager::getSingleton().HandleReward();
    }


    JNIEXPORT void JNICALL Java_com_newzensoft_admob_UnityAdsManager_CallBackOnRewardAdLoaded(JNIEnv * env, jclass clazz) {
        CCLog("CallBackOnRewardAdLoaded !!!!!!!!!");

    }
    JNIEXPORT void JNICALL Java_com_newzensoft_admob_UnityAdsManager_CallbackOnRewardAdFailToLoaded(JNIEnv * env, jclass clazz) {
        CCLog("CallbackOnRewardAdFailToLoaded !!!!!!!!");
        UnityAdsManager::getSingleton().SetLoaded(false);
        UnityAdsManager::getSingleton().SetReward(false);
        STCMD_UNITADS_FINISH result;
        UnityAdsManager::getSingleton().HandleReward();
    }


}