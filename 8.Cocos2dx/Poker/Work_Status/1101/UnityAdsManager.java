package com.newzensoft.admob;

import static com.unity3d.services.core.properties.ClientProperties.getActivity;
import static com.unity3d.services.core.properties.ClientProperties.getApplicationContext;

import android.app.Activity;
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


public class UnityAdsManager implements IUnityAdsInitializationListener {
    private static UnityAdsManager unityadMgr = null;
    private String TAG = "UnityAdsManager";

    private Activity activity;
    private String unityGameID = "4997097";
    private Boolean testMode = true;
    private String adUnitId = "rewardedVideo";




    public static Object instance() {
        if (unityadMgr == null) {
            unityadMgr = new UnityAdsManager();
        }
        return unityadMgr;
    }


    private IUnityAdsLoadListener loadListener = new IUnityAdsLoadListener() {
        @Override
        public void onUnityAdsAdLoaded(String placementId) {
            UnityAds.show((Activity)getApplicationContext(), adUnitId, new UnityAdsShowOptions(), showListener);
        }

        @Override
        public void onUnityAdsFailedToLoad(String placementId, UnityAds.UnityAdsLoadError error, String message) {
            Log.e("UnityAdsExample", "Unity Ads failed to load ad for " + placementId + " with error: [" + error + "] " + message);
        }
    };


    private IUnityAdsShowListener showListener = new IUnityAdsShowListener() {
        @Override
        public void onUnityAdsShowFailure(String placementId, UnityAds.UnityAdsShowError error, String message) {
            Log.e("UnityAdsExample", "Unity Ads failed to show ad for " + placementId + " with error: [" + error + "] " + message);
        }

        @Override
        public void onUnityAdsShowStart(String placementId) {
            Log.v("UnityAdsExample", "onUnityAdsShowStart: " + placementId);
        }

        @Override
        public void onUnityAdsShowClick(String placementId) {
            Log.v("UnityAdsExample", "onUnityAdsShowClick: " + placementId);
        }


        @Override
        public void onUnityAdsShowComplete(String placementId, UnityAds.UnityAdsShowCompletionState state) {
            Log.v("UnityAdsExample", "onUnityAdsShowComplete: " + placementId);
            if (state.equals(UnityAds.UnityAdsShowCompletionState.COMPLETED)) {
                // Reward the user for watching the ad to completion
                Log.e(TAG,"onUnityAdsShowComplete");
                //리워드 주고
                CallBackReward();
                //새로 광고 로드해주라.
                LoadAd();

            } else {
                // Do not reward the user for skipping the ad


            }
        }
    };


    public UnityAdsManager(){
        Resources PokerRes = Cocos2dxHelper.getActivity().getResources();
        Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
            public void run() {
                UnityAds.initialize(getApplicationContext(), unityGameID, testMode, unityadMgr);
                Log.e(TAG, "Unity ads has Initialize");

            }
        });
    }

    @Override
    public void onInitializationComplete() {
        Log.e(TAG, "onInitializationComplete");
        LoadAd();
    }

    public void LoadAd()
    {
        UnityAds.load(adUnitId, loadListener);
    }

    @Override
    public void onInitializationFailed(UnityAds.UnityAdsInitializationError error, String message) {
        Log.e("UnityAdsExample", "Unity Ads initialization failed with error: [" + error + "] " + message);
    }

    public void adsShow(){
        Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
            public void run(){
                Log.d(TAG, "Its On Unity Ads Manager");


            }
        });
    }


    private static native void CallBackReward();

}
