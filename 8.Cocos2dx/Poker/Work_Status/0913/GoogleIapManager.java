package com.newzensoft.inApp;


import static org.cocos2dx.lib.Cocos2dxHelper.getActivity;

import org.cocos2dx.cpp.AppActivity;
import org.json.JSONException;
import org.json.JSONObject;

/*import com.android.billingclient.api.ProductDetailsResponseListener;
import com.android.billingclient.api.QueryProductDetailsParams;*/
import com.google.android.gms.ads.rewarded.RewardedAd;
import com.google.common.collect.ImmutableList;
import com.newzensoft.poker.R;
import com.numixent.inApp.helper.ConverterFactory;
import com.numixent.inApp.helper.ParamsBuilder;
import com.numixent.inApp.pdu.Response;
/*import com.skplanet.dodo.IapPlugin;
import com.skplanet.dodo.IapResponse;
import com.skplanet.dodo.helper.PaymentParams;
import com.skplanet.dodo.helper.PaymentParams.Builder;*/

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.nfc.Tag;
import android.os.Bundle;
import android.os.Handler;
import android.os.StrictMode;
import android.text.Html;
import android.text.Spanned;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Random;
import java.util.Set;


import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import javax.net.ssl.HttpsURLConnection;

import com.android.billingclient.api.BillingClient;
import com.android.billingclient.api.BillingClientStateListener;
import com.android.billingclient.api.BillingFlowParams;
import com.android.billingclient.api.BillingResult;
import com.android.billingclient.api.ConsumeParams;
import com.android.billingclient.api.ConsumeResponseListener;
import com.android.billingclient.api.Purchase;
import com.android.billingclient.api.PurchasesUpdatedListener;
import com.android.billingclient.api.SkuDetails;
import com.android.billingclient.api.SkuDetailsParams;
import com.android.billingclient.api.SkuDetailsResponseListener;
import com.google.gson.JsonObject;



public class GoogleIapManager implements PurchasesUpdatedListener{

    public static native void OnIapResult(boolean sucess , String errMsg , String tid , String ToServToken, String pid);

    private static final String TAG = "GoogleIAPManager : ";
    //각 주요 결재 변수들을 선언해 줍니다.
    private BillingClient billingClient;
    private List<SkuDetails> skuDetails_list;
    private ConsumeResponseListener consumeResponseListener;
    private Context context;
    
    public GoogleIapManager(Context context) {
        this.context = context;
        billingClient = BillingClient.newBuilder(context)
                .setListener(this::onPurchasesUpdated)//이부분은 밑에 선언된 구매시 구매완료 및 실패에 대한 콜백을 해주는 부분입니다.
                .enablePendingPurchases()
                .build();

//billingClient.startConnection 은 결제 이벤트를 실행했을때, 결제사이트에 들어가는 부분
        billingClient.startConnection(new BillingClientStateListener() {

            @Override
            public void onBillingSetupFinished(BillingResult billingResult) {
                if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK) {
                    Log.d(TAG, "biilingcount2");
                    //접속이 됫을때 구매목록을 보여달라는 이벤트를 넣자
                    getSkuDetailList(); // 이 함수도 밑에 있습니다.
                    //안드로이드 개발자 가이드에는 이걸 이렇게 넣어서 쓰라는 정보가 없습니다.
                    //한동안 어떻게  쓰는지 찾느라 로그 노가다를 했습니다.
                }
            }

            @Override
            public void onBillingServiceDisconnected() {
                Log.d(TAG, " onBillingServiceDisconnect!!!!");
            }
        });


        // 상품 소모결과 리스너
        //이부분은 상품을 구매하거나 했을때 실행되는 함수 입니다.
        //상품을 구매하거나 하면 purchaseToken에 값이 저장이 되는데 그것을 보여줍니다.
        consumeResponseListener = new ConsumeResponseListener() {
            @Override
            public void onConsumeResponse(BillingResult billingResult, String purchaseToken) {
                if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK) {
                    Log.d(TAG, "상품을 성공적으로 소모하였습니다. 소모된 상품 => " + purchaseToken);
                    return;
                } else {
                    Log.d(TAG, "상품 소모에 실패하였습니다. 오류코드 (" + billingResult.getResponseCode() + "), 대상 상품 코드: " + purchaseToken);
                    return;
                }
            }
        };
    }
// 즉, 처음 BillingService를 초기화 하면, 구글창에 연결을 하고 구매리스트를 변수에저장합니다.
// 그리고 현재 무언가 구매한 상태라면 그 마지막 구매 목록을 불러와 보여줍니다
// 안드로이드 개발자 가이드에 정보를 보면서 같이 보면 이해가 빠를거에요.


    //결제과 완료 됐을때 나오는 문구 입니다. 함수멸을 보시다 시피 결제 업데이트 입니다.
//윗부분 billingClient.setListner(this::onPurchaseUpdated) 에 사용되는 함수입니다.
//콜백과 비슷한 기능입니다. 42번쨰 줄
    @Override
    public void onPurchasesUpdated(@NonNull BillingResult billingResult, @Nullable @org.jetbrains.annotations.Nullable List<Purchase> purchases) {

        Log.d(TAG,"biilingcount1");
        // To be implemented in a later section.
        if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK
                && purchases != null) {
            Log.d(TAG, "결제에 성공했으며, 아래에 구매한 상품들이 나열됨");
            for (Purchase purchase : purchases) {
                Log.e(TAG, "결제 구매완료상품: " + purchases);
                handlePurchase(purchase);
            }
        } else if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.USER_CANCELED) {
            // Handle an error caused by a user cancelling the purchase flow.
        } else {
            // Handle any other error codes.
        }
    }



//이때 skuList.add 에는 플레이스토어 콘설에서 등록한 결제 상품의 id를 입력해주시면 됩니다.
//이 함수도 위쪽에 구글결제에 연결이 완료 됐을때, 선언된 함수입니다.
    public void getSkuDetailList() {
        Log.d(TAG, "biilingcount3");
        List<String> skuList = new ArrayList<>();

        skuList.add("m_ruby_01");
        skuList.add("ruby_01");
        skuList.add("ruby_02");
        skuList.add("ruby_03");
        skuList.add("ruby_04");
        skuList.add("ruby_05");
        skuList.add("jackpot_01");
        skuList.add("jackpot_02");
        skuList.add("made_01");
        skuList.add("made_02");
        skuList.add("allin_01");
        skuList.add("allin_02");
        skuList.add("onetime01");

        SkuDetailsParams.Builder params = SkuDetailsParams.newBuilder();
        params.setSkusList(skuList).setType(BillingClient.SkuType.INAPP);//.INAPP은 일회용 결제, SUBS는 구독형

        billingClient.querySkuDetailsAsync(params.build(),
                new SkuDetailsResponseListener() {
                    @Override
                    public void onSkuDetailsResponse(BillingResult billingResult,
                                                     List<SkuDetails> skuDetailsList) {
                        Log.d(TAG, "biilingcount3.1");
                        if (billingResult.getResponseCode() != BillingClient.BillingResponseCode.OK) {
                            Log.d(TAG, "biilingcount3.2");
                            return;
                        }
                        Log.d(TAG, "biilingcount3.3");
                        //상품정보를 가저오지 못함 면 동작 이벤트
                        if (skuDetailsList == null) {
                            Log.d(TAG,"결제 상품 리스트에 없음 ");
                            return;
                        }

                        //상품사이즈 체크
                        Log.d(TAG, "결제 상품 리스트 크기 : " + skuDetailsList.size());

                        try {
                            for (SkuDetails skuDetails : skuDetailsList) {
                                String title = skuDetails.getTitle();
                                String sku = skuDetails.getSku();
                                String price = skuDetails.getPrice();

                            }
                        } catch (Exception e) {
                            Log.d(TAG, "itemerror" + e.toString());
                        }

                        skuDetails_list = skuDetailsList;
                    }

                });
    }


//인자중 itemid 는 구매 품목 id를 문자열로, Activity 는 현재 액티비티를 넣어주면 됩니다.
//이 Activity인자는 구매를 성공했는지 아닌지를 값을 반환해 주기 위해 있는 인자이므로 그게
//신경을 안써도 됩니다.
    public void purchase(String itemid, Activity activity) {
        SkuDetails skuDetails = null;
        if(null != skuDetails_list){
            for(int i=0; i<skuDetails_list.size(); i++){
                SkuDetails skuinfo = skuDetails_list.get(i);
                if(skuinfo.getSku().equals(itemid)){//해당 상품을 상품목록에 있는지 비교하고 있으면 다음으로 넘어갑니다.
                    skuDetails = skuinfo;
                    break;
                }
            }
            Log.d(TAG,"biilingcount4");
            // Retrieve a value for "skuDetails" by calling querySkuDetailsAsync().
            BillingFlowParams flowParams = BillingFlowParams.newBuilder()
                    .setSkuDetails(skuDetails) //구매 flow에 해당 목록id가 저장된 변수를 넣습니다.
                    .build();
            Log.d(TAG,"purchase state : "+billingClient.launchBillingFlow(activity,flowParams).getResponseCode());
            // 아까 말했다시피 단지 성공여부를 알려주는 값입니다.  Activity는 그냥 현재, 결제하고 있는 Activity를 입력하시면 됩니다.
        }

    }



//이부분은 구매를 하는 함수입니다.
// 버튼클릭하면 구매를 원할시 버튼이벤트에 이 함수를 넣어주면 됩니다.
//위에 선언된 purchase를 이 함수의 인자에 넣어주고 함수를 실행하면 됩니다.
    public void handlePurchase(Purchase purchase) {
        Log.d(TAG,"biilingcount5");
        // Purchase retrieved from BillingClient#queryPurchasesAsync or your PurchasesUpdatedListener.

        ConsumeParams consumeParams =
                ConsumeParams.newBuilder()
                        .setPurchaseToken(purchase.getPurchaseToken())
                        .build();

//구매가 되면 위에서 처럼 ComsumeResponesListner을 가진 변수로 결제 성공 후 이벤트를 등록합니다.
//결제상태를 계속 체크하면서, 장애, 정보등을 전당해 줍니다.
        ConsumeResponseListener listener = new ConsumeResponseListener() {
            @Override
            public void onConsumeResponse(BillingResult billingResult, String purchaseToken) {
                if (billingResult.getResponseCode() == BillingClient.BillingResponseCode.OK) {
                    // Handle the success of the consume operation.
                }
            }
        };

        billingClient.consumeAsync(consumeParams, listener);
    }


    //purchase 원래 purchase data였음
    public static void httpGetConnection(String UrlData, String ParamData, Purchase purchaseData, String ppid) {
        System.out.println("111111111");

        //http 요청 시 url 주소와 파라미터 데이터를 결합하기 위한 변수 선언
        String totalUrl = "";
        if(ParamData != null && ParamData.length() > 0 &&
                !ParamData.equals("") && !ParamData.contains("null")) { //파라미터 값이 널값이 아닌지 확인
            totalUrl = UrlData.trim().toString() + "?" + ParamData.trim().toString();
        }
        else {
            totalUrl = UrlData.trim().toString();
        }
        System.out.println("2222222222222222222222222222");
        //http 통신을 하기위한 객체 선언 실시
        URL url = null;
        HttpURLConnection conn = null;
        System.out.println("333333333333333333333333333333");
        //http 통신 요청 후 응답 받은 데이터를 담기 위한 변수
        String responseData = "";
        BufferedReader br = null;
        StringBuffer sb = null;
        System.out.println("44444444444444444444444444444444");
        //메소드 호출 결과값을 반환하기 위한 변수
        String returnData = "";
        System.out.println("555555555555555555555555555555555");
        try {
            System.out.println("6666666666666666666666666666666666");
            //파라미터로 들어온 url을 사용해 connection 실시
            url = new URL(totalUrl);
            conn = (HttpURLConnection) url.openConnection();
            System.out.println("7777777777777777777777777777777");
            //http 요청에 필요한 타입 정의 실시
            conn.setRequestProperty("Accept", "application/json");
            conn.setRequestMethod("GET");

            //http 요청 실시
            conn.connect();
            System.out.println("http 요청 방식 : "+"GET");
            System.out.println("http 요청 타입 : "+"application/json");
            System.out.println("http 요청 주소 : "+UrlData);
            System.out.println("http 요청 데이터 : "+ParamData);
            System.out.println("");
            System.out.println("888888888888888888888888888888888888");
            //http 요청 후 응답 받은 데이터를 버퍼에 쌓는다
            br = new BufferedReader(new InputStreamReader(conn.getInputStream(), "UTF-8"));
            sb = new StringBuffer();
            while ((responseData = br.readLine()) != null) {
                sb.append(responseData); //StringBuffer에 응답받은 데이터 순차적으로 저장 실시
            }
            System.out.println("999999999999999999999999999999999999999");
            //메소드 호출 완료 시 반환하는 변수에 버퍼 데이터 삽입 실시
            returnData = sb.toString();



            //http 요청 응답 코드 확인 실시
            String responseCode = String.valueOf(conn.getResponseCode());
            System.out.println("http 응답 코드 : "+responseCode);
            System.out.println("http 응답 데이터 : "+returnData); //0이면성공으로 처리


            OnIapResult(returnData.equals("0") , null , ToServTID , PdToken, purchaseData.getProductId());



        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            //http 요청 및 응답 완료 후 BufferedReader를 닫아줍니다
            try {
                if (br != null) {
                    br.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }


}