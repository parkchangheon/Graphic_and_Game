/****************************************************************************
Copyright (c) 2015-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.os.Bundle;
//admob 광고 적용

import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.initialization.InitializationStatus;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.rewarded.RewardedAd;
import com.google.android.gms.ads.rewarded.RewardedAdLoadCallback;
import com.google.android.gms.ads.rewarded.RewardItem;
import com.newzensoft.poker.R;
//import com.google.android.gms.ads.rewarded.RewardedAdCallback; 최신버전에서는 필요가 없는듯???

import org.cocos2dx.lib.Cocos2dxActivity;
import android.os.Build;
import android.util.Log;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import androidx.annotation.NonNull;

public class AppActivity extends Cocos2dxActivity {

    private static final String AD_UNIT_ID = "ca-app-pub-3940256099942544/5224354917";
    private static final long COUNTER_TIME = 10;
    private static final int GAME_OVER_REWARD = 1;

    private boolean gameOver;
    private boolean gamePaused;

    private static final String TAG = "AppActivity";
    private AdView mAdView;
    private AdView m_cBannerAdView;

    private RewardedAd rewardedAd;
    private long timeRemaining;
    boolean isLoading;


    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.setEnableVirtualButton(false);
        super.onCreate(savedInstanceState);

        MobileAds.initialize(this, new OnInitializationCompleteListener() {
            @Override
            public void onInitializationComplete(@NonNull InitializationStatus initializationStatus) {
                Log.d(TAG, "admob, onInitializationComplete");
            }
        });

        //배너 광고 처리
        m_cBannerAdView = new AdView(this);
        m_cBannerAdView.setAdSize(AdSize.BANNER);
        m_cBannerAdView.setAdUnitId("ca-app-pub-3940256099942544/6300978111");

        
        //보상형 광고 처리


        
        
        //======================배너 광고 함수 구현======================
        AdRequest l_cAdRequest = new AdRequest.Builder().build();
        m_cBannerAdView.loadAd(l_cAdRequest);

        ViewGroup.LayoutParams l_cAdParam = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        this.addContentView(m_cBannerAdView, l_cAdParam);

        m_cBannerAdView.setAdListener(new AdListener() {
            @Override
            public void onAdClicked() {
                super.onAdClicked();
                Log.d(TAG,"admob, onClicked");
            }

            @Override
            public void onAdClosed() {
                super.onAdClosed();
                Log.d(TAG,"admob, onAdClosed");
            }

            @Override
            public void onAdFailedToLoad(@NonNull LoadAdError loadAdError) {
                super.onAdFailedToLoad(loadAdError);
                Log.d(TAG,"admob, onAdFailedToLoad");
            }

            @Override
            public void onAdImpression() {
                super.onAdImpression();
                Log.d(TAG,"admob, onAdImpression");
            }

            @Override
            public void onAdLoaded() {
                super.onAdLoaded();
                Log.d(TAG,"admob, onAdLoaded");
            }

            @Override
            public void onAdOpened() {
                super.onAdOpened();
                Log.d(TAG,"admob, onAdOpened");
            }
        });
        m_cBannerAdView.destroy();

        //======================배너 광고 종료======================




        // Workaround in https://stackoverflow.com/questions/16283079/re-launch-of-activity-on-home-button-but-only-the-first-time/16447508
        if (!isTaskRoot()) {
            // Android launched another instance of the root activity into an existing task
            //  so just quietly finish and go away, dropping the user back into the activity
            //  at the top of the stack (ie: the last state of this task)
            // Don't need to finish it again since it's finished in super.onCreate .
            return;
        }
        // Make sure we're running on Pie or higher to change cutout mode
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            // Enable rendering into the cutout area
            WindowManager.LayoutParams lp = getWindow().getAttributes();
            lp.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            getWindow().setAttributes(lp);
        }
        // DO OTHER INITIALIZATION BELOW



    }


    //=======================보상형 광고 구현부==============================
    @Override
    public void onPause(){
        super.onPause();
        pauseGame();
    }
    @Override
    public void onResume() {
        super.onResume();
        if (!gameOver && gamePaused) {
            resumeGame();
        }
    }

    private void pauseGame() {
        countDownTimer.cancel();
        gamePaused = true;
    }

    private void resumeGame() {
        createTimer(timeRemaining);
        gamePaused = false;
    }

}


