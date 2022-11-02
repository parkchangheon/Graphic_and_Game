package com.newzensoft.admob;

import static com.unity3d.services.core.properties.ClientProperties.getActivity;
import static com.unity3d.services.core.properties.ClientProperties.getApplicationContext;

import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.nfc.Tag;
import android.os.Bundle;
import android.util.Log;

import com.newzensoft.poker.R;
import com.unity3d.ads.IUnityAdsInitializationListener;
import com.unity3d.ads.IUnityAdsLoadListener;
import com.unity3d.ads.IUnityAdsShowListener;
import com.unity3d.ads.UnityAds;
import com.unity3d.ads.UnityAdsShowOptions;

import org.cocos2dx.lib.Cocos2dxHelper;


public class UnityAdsManager{

    private static UnityAdsManager unityadMgr = null;
    private String TAG = "UnityAdsManager";
    private String unityGameID = "5002197"; //5002197   //4997622
    private Boolean testMode = true;
    String adUnitId = "Rewarded_Android";


    public static Object instance() {
        if (unityadMgr == null) {
            unityadMgr = new UnityAdsManager();
            System.out.println("instance has started!!");
        }
        return unityadMgr;
    }


    IUnityAdsInitializationListener mAdsListener = new IUnityAdsInitializationListener() {
        @Override
        public void onInitializationComplete() {
            Log.d(TAG, " onInitializationComplete");
            UnityAds.load(adUnitId, loadListener);
        }

        @Override
        public void onInitializationFailed(UnityAds.UnityAdsInitializationError unityAdsInitializationError, String s) {
            Log.d(TAG, " onInitializationFailed" + s);
            Log.d(TAG, " unityAdsInitializationError: "+ unityAdsInitializationError);

        }
    };

    IUnityAdsLoadListener loadListener = new IUnityAdsLoadListener() {
        @Override
        public void onUnityAdsAdLoaded(String placementId) {
            Log.d(TAG, " onUnityAdsAdLoaded");
            //UnityAds.show(Cocos2dxHelper.getActivity(), adUnitId, new UnityAdsShowOptions(), showListener);

        }

        @Override
        public void onUnityAdsFailedToLoad(String placementId, UnityAds.UnityAdsLoadError unityAdsLoadError, String message) {
            Log.e(TAG, "Unity Ads failed to load ad for " + placementId + " with error: [" + unityAdsLoadError + "] " + message);

        }
    };

    IUnityAdsShowListener showListener = new IUnityAdsShowListener() {

        @Override
        public void onUnityAdsShowFailure(String placementId, UnityAds.UnityAdsShowError error, String message) {
            Log.e("UnityAdsExample", "Unity Ads failed to show ad for " + placementId + " with error: [" + error + "] " + message);
        }

        @Override
        public void onUnityAdsShowStart(String s) {
            Log.d(TAG, "onUnityAdsShowStart");

        }

        @Override
        public void onUnityAdsShowClick(String s) {
            Log.d(TAG, "onUnityAdsShowClick");

        }

        @Override
        public void onUnityAdsShowComplete(String s, UnityAds.UnityAdsShowCompletionState unityAdsShowCompletionState) {
            Log.d(TAG, "onUnityAdsShowComplete");

            //끝나면 여기에다가 ~~~~ 할거다 ~~~~~ 적어주기.

        }
    };

    public UnityAdsManager(){
        Resources PokerRes = Cocos2dxHelper.getActivity().getResources();
        Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
            public void run() {
                Log.d(TAG, " onInitializationStart");
                UnityAds.initialize( Cocos2dxHelper.getActivity(), unityGameID, testMode, mAdsListener);
            }
        });
    }


    public void adsShow(){
        Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
            public void run(){
                Log.d(TAG, "Its On Unity Ads Manager");
                UnityAds.show(Cocos2dxHelper.getActivity(), adUnitId, showListener);

            }
        });
    }


    private static native void CallBackReward();

 /*   @Override
    public void onInitializationComplete() {
        Log.d(TAG, " onInitializationComplete");
        UnityAds.load(adUnitId, loadListener);

    }

    @Override
    public void onInitializationFailed(UnityAds.UnityAdsInitializationError unityAdsInitializationError, String s) {
        Log.d(TAG, " onInitializationFailed");
    }*/
}
