package com.newzensoft.inApp;


import static org.cocos2dx.lib.Cocos2dxHelper.getActivity;

import org.json.JSONException;
import org.json.JSONObject;

import com.gaa.sdk.iap.AcknowledgeListener;
import com.gaa.sdk.iap.AcknowledgeParams;
import com.gaa.sdk.iap.ConsumeListener;
import com.gaa.sdk.iap.ConsumeParams;
import com.gaa.sdk.iap.IapResult;
import com.gaa.sdk.iap.IapResultListener;
import com.gaa.sdk.iap.ProductDetail;
import com.gaa.sdk.iap.ProductDetailsListener;
import com.gaa.sdk.iap.ProductDetailsParams;
import com.gaa.sdk.iap.PurchaseClient;
import com.gaa.sdk.iap.PurchaseClientStateListener;
import com.gaa.sdk.iap.PurchaseData;
import com.gaa.sdk.iap.PurchaseFlowParams;
import com.gaa.sdk.iap.PurchasesListener;
import com.gaa.sdk.iap.PurchasesUpdatedListener;
import com.gaa.sdk.iap.RecurringProductListener;
import com.gaa.sdk.iap.RecurringProductParams;
import com.gaa.sdk.iap.StoreInfoListener;


import com.google.android.gms.ads.rewarded.RewardedAd;
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
import android.text.Html;
import android.text.Spanned;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Random;
import java.util.Set;


public final class IapManager extends AppCompatActivity implements PurchasesUpdatedListener {

	private final String TAG = IapManager.class.getSimpleName();
	private List<ProductDetail> skuDetailsList = new ArrayList<>();

	private Activity mActivity;
	private PurchaseClient mPurchaseClient;
	private ProgressDialog mProgressDialog;
	private static IapManager iapMgr = null;

	private Set<String> mTokenToBe;
	private boolean isServiceConnected;

	public static Object instance() {
		System.out.println("instance 1");
		getActivity().runOnUiThread(new Runnable() {
			public void run() {
				if (iapMgr == null) {
					System.out.println("instance 2");
					iapMgr = new IapManager(getActivity());
				}
				System.out.println("instance 3");

			}
		});
		return iapMgr;
	}

	public IapManager(@NonNull Activity activity) {
		mActivity = activity;

		mPurchaseClient = PurchaseClient.newBuilder(activity)
				.setBase64PublicKey(null)
				.setListener(this)
				.build();
		Log.d(TAG, "before setup");
		startConnection(new Runnable() {  //여기가 원스토어 서비스와 연결을 하는 부분
			@Override
			public void run() {
				onPurchaseClientSetupFinished();
				Log.d(TAG, "Setup successful. Querying inventory.");
				queryPurchasesAsync();
			}
		});
	}

	public void startConnection(final Runnable executeOnSuccess) {
		mPurchaseClient.startConnection(new PurchaseClientStateListener() {

			@Override
			public void onSetupFinished(IapResult iapResult) {
				Log.e(TAG, " setup END!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ");

				if (iapResult.isSuccess()) {  //the purchasesclient is ready   , you can query purchases here
					Log.e(TAG, " @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@iapResult isSUccess @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		
					isServiceConnected = true;
					//여기에 결제 요청 붙여보자
					/*showBuyProductDialog();*/
					queryProductDetailsAsync();


					if (executeOnSuccess != null) {
						executeOnSuccess.run();
					}

					return;
				}

				new Handler().postDelayed(new Runnable() {
					@Override
					public void run() {
						handleErrorCode(iapResult);
					}
				}, 300);
			}

			@Override
			public void onServiceDisconnected() {    // 서비스가 끊겼을때
				Log.e(TAG,"Log Has Disconnect");
				isServiceConnected = false;
			}
		});
	}

	//여기까지 진행이 완료됨
	public void onPurchaseClientSetupFinished() {
		iapMgr.getStoreCode(new StoreInfoListener() {
			@Override
			public void onStoreInfoResponse(IapResult iapResult, String storeCode) {
				if (iapResult.isSuccess()) {
					Log.d(TAG, "onPurchaseClientSetupFinished: storeCode: " + storeCode);
					saveStoreCode(storeCode);
				}
			}
		});
	}
	@Override
	protected void onDestroy() {
		Log.d(TAG, " onDestroy has Activate! ");
		super.onDestroy();
		if (mPurchaseClient != null) {
			mPurchaseClient.endConnection();
			mPurchaseClient = null;
		}
	}



	private void queryProductDetailsAsync()
	{
		Log.d(TAG, "I am Setting query_ProductDetailsAsync");

		List<String> strList = new ArrayList<>();
		strList.add("m_ruby_01");
		strList.add("ruby_01");

		ProductDetailsParams params = ProductDetailsParams.newBuilder()
				.setProductIdList(strList).setProductType(PurchaseClient.ProductType.ALL).build();
		Log.d(TAG, "I am Setting query_ProductDetailsAsync2222222");


		//여기가문제  저기서 받아와야하는데 못받아온다.
		mPurchaseClient.queryProductDetailsAsync(params, new ProductDetailsListener(){
			@Override
			public void onProductDetailsResponse(IapResult iapResult, @Nullable List<ProductDetail> list) {
				Log.e(TAG, "I am Setting query_ProductDetailsAsync333333333");

				if(iapResult.isSuccess() && list != null){
					for(ProductDetail skuDetail : list){
						Log.d(TAG, "ProductDetail = " + skuDetail.toString());
					}
				}else{
					Log.d(TAG, iapResult.toJsonString());
				}
			}
		});
	}


	private void buyProduct(final String productId, @PurchaseClient.ProductType String productType) {
		Log.d(TAG, "buyProduct() - productId:" + productId + " productType: " + productType);

		String devPayload = AppSecurity.generatePayload();
		ProductDetail sku = getSkuDetail(productId);


		savePayloadString(devPayload);
		showProgressDialog();

		PurchaseFlowParams params = PurchaseFlowParams.newBuilder()
				.setProductId(productId)
				.setProductType(productType)
				.setDeveloperPayload(devPayload)
				.setPromotionApplicable(false)
				.build();

		launchPurchaseFlow(params);
	}

	private ProductDetail getSkuDetail(String pid) {
		for(ProductDetail item : skuDetailsList) {
			if(item.getProductId().equals(pid)) {
				return item;
			}
		}
		return null;
	}


	private void executeServiceRequest(Runnable runnable) {
		if (isServiceConnected) {
			runnable.run();
		} else {
			startConnection(runnable);
		}
	}

	private void handleErrorCode(IapResult iapResult) {
		if(iapResult.isSuccess()){
			Log.w(TAG, "the purchase is ready. we can query at here");
		}

		else if (iapResult.getResponseCode() == PurchaseClient.ResponseCode.RESULT_NEED_LOGIN) {
			Log.w(TAG, "handleErrorCode() RESULT_NEED_LOGIN");
			onNeedLogin();
		} else if (iapResult.getResponseCode() == PurchaseClient.ResponseCode.RESULT_NEED_UPDATE) {
			Log.w(TAG, "handleErrorCode() RESULT_NEED_UPDATE");
			onNeedUpdate();
		} else {
			String message = iapResult.getMessage() + "(" + iapResult.getResponseCode() + ")";
			Log.d(TAG, "handleErrorCode() error: " + message);
			onError(message);
		}
	}

	// =================================================================================================================
	// implements PurchasesUpdatedListener
	// =================================================================================================================
	@Override
	public void onPurchasesUpdated(IapResult iapResult, List<PurchaseData> purchaseData) {
		if (iapResult.isSuccess()) {
			Log.e(TAG, "onpurchasesupdated");
/*
			onPurchaseUpdated(purchaseData);
*/
			return;
		}

		handleErrorCode(iapResult);
	}

	public void launchLoginFlow(IapResultListener listener) {
		mPurchaseClient.launchLoginFlowAsync(mActivity, listener);
	}

	public void launchUpdateOrInstall(IapResultListener listener) {
		mPurchaseClient.launchUpdateOrInstallFlow(mActivity, listener);
	}


	public void launchPurchaseFlow(final PurchaseFlowParams params) {
		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				mPurchaseClient.launchPurchaseFlow(mActivity, params);
			}
		});
	}



	public void onNeedLogin() {
		launchLoginFlow(null);
	}

	public void onNeedUpdate() {
		Log.e(TAG, "Before updateOrInstallPaymentModule");
		updateOrInstallPaymentModule();
	}

	private void updateOrInstallPaymentModule() {
		Log.e(TAG, "Inside updateOrInstallPaymentModule");
		launchUpdateOrInstall(new IapResultListener() {
			@Override
			public void onResponse(IapResult iapResult) {
				if (iapResult.isSuccess()) {
					startConnection(new Runnable() {
						@Override
						public void run() {
							onPurchaseClientSetupFinished();
							queryPurchasesAsync();
						}
					});
				} else {
					Log.w(TAG, "launchUpdateOrInstall() got an error response code: " + iapResult.getResponseCode());
				}
			}
		});
	}

	public void onError(String message) {
		showDialog(message);
	}

	private void savePayloadString(String payload) {
		SharedPreferences.Editor spe = getPreferences(MODE_PRIVATE).edit();
		spe.putString("PAYLOAD", payload);
		spe.apply();
	}

	public static String generatePayload() {
		char[] payload;
		final char[] specials = {'~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '-', '{', '}', '|', '\\', '/', '.',
				'.', '=', '[', ']', '?', '<', '>'};
		StringBuilder buffer = new StringBuilder();
		for (char ch = '0'; ch <= '9'; ++ch) {
			buffer.append(ch);
		}
		for (char ch = 'a'; ch <= 'z'; ++ch) {
			buffer.append(ch);
		}
		for (char ch = 'A'; ch <= 'Z'; ++ch) {
			buffer.append(ch);
		}

		for (char ch : specials) {
			buffer.append(ch);
		}

		payload = buffer.toString().toCharArray();

		StringBuilder randomString = new StringBuilder();
		Random random = new Random();

		//length : 20자
		for (int i = 0; i < 20; i++) {
			randomString.append(payload[random.nextInt(payload.length)]);
		}

		return randomString.toString();
	}

	public void consumeAsync(final PurchaseData data) {
		if (mTokenToBe == null) {
			mTokenToBe = new HashSet<>();
		} else if (mTokenToBe.contains(data.getPurchaseToken())) {
			Log.i(TAG, "Token was already scheduled to be consumed - skipping...");
			return;
		}

		mTokenToBe.add(data.getPurchaseToken());

		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				ConsumeParams params = ConsumeParams.newBuilder().setPurchaseData(data).build();
				mPurchaseClient.consumeAsync(params, new ConsumeListener() {
					@Override
					public void onConsumeResponse(IapResult iapResult, PurchaseData purchaseData) {
						if (iapResult.isSuccess()) {
							if (purchaseData.getPurchaseToken().equals(data.getPurchaseToken())) {
								mTokenToBe.remove(data.getPurchaseToken());
								onConsumeFinished(purchaseData, iapResult);
							} else {
								onError("purchaseToken not equal");
							}
						} else {
							handleErrorCode(iapResult);
						}
					}
				});
			}
		});
	}

	public void acknowledgeAsync(final PurchaseData data) {
		if (mTokenToBe == null) {
			mTokenToBe = new HashSet<>();
		} else if (mTokenToBe.contains(data.getPurchaseToken())) {
			Log.i(TAG, "Token was already scheduled to be acknowledged - skipping...");
			return;
		}

		mTokenToBe.add(data.getPurchaseToken());

		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				AcknowledgeParams params = AcknowledgeParams.newBuilder().setPurchaseData(data).build();
				mPurchaseClient.acknowledgeAsync(params, new AcknowledgeListener() {
					@Override
					public void onAcknowledgeResponse(IapResult iapResult, PurchaseData purchaseData) {
						if (iapResult.isSuccess()) {
							if (data.getPurchaseToken().equals(purchaseData.getPurchaseToken())) {
								mTokenToBe.remove(data.getPurchaseToken());
								onAcknowledgeFinished(purchaseData, iapResult);
							} else {
								onError("purchaseToken not equal");
							}
						} else {
							handleErrorCode(iapResult);
						}
					}
				});
			}
		});
	}
	public void onAcknowledgeFinished(PurchaseData purchase, IapResult iapResult) {
		Log.e(TAG, "onAcknowledgeFinished in come");
	}

	public void onConsumeFinished(PurchaseData purchaseData, IapResult iapResult) {


		if (iapResult.isSuccess()) {
			updateCoinsPurchased(purchaseData.getProductId());
			Spanned message = Html.fromHtml(
					String.format("asd", getPurchasedCoins(purchaseData.getProductId()))
			);
			showDialog(message);
		} else {
			showDialog(iapResult.getMessage());
		}
	}

	/**
	 * TODO: 개발사에서는 소비되지 않는 관리형상품(inapp)에 대해, 애플리케이션의 적절한 life cycle 에 맞춰 구매내역조회를 진행 후 소비를 진행해야합니다.
	 * <p>
	 * 구매내역조회 API를 이용하여 소비되지 않는 관리형상품(inapp)과 자동결제중인 월정액상품(auto) 목록을 받아옵니다.
	 * 관리형상품(inapp)의 경우 소비를 하지 않을 경우 재구매요청을 하여도 구매가 되지 않습니다. 꼭, 소비 과정을 통하여 소모성상품 소비를 진행하여야합니다.
	 * 월정액상품(auto)의 경우 구매내역조회 시 recurringState 정보를 통하여 현재상태정보를 확인할 수 있습니다. -> recurringState 0(자동 결제중), 1(해지 예약중)
	 * manageRecurringProduct API를 통해 해지예약요청을 할 경우 recurringState는 0 -> 1로 변경됩니다. 해지예약 취소요청을 할경우 recurringState는 1 -> 0로 변경됩니다.
	 * <p>
	 * 월정액상품(auto)을 11월 10일에 구매를 할 경우 구매내역조회에서 월정액상품의 recurringState는 0(자동 결제중)으로 내려옵니다.
	 * 월정액상품은 매달 구매일(12월 10일)에 자동결제가 발생하므로 11월 10일 ~ 12월 9일까지 현재 상태를 유지합니다.
	 * 11월 15일에 월정액상태변경API를 이용하여 해지예약(cancel)을 진행할 경우, 12월 9일까지 월정액상품 상태(recurringState)는 1(해지 예약중)이 됩니다.
	 * 12월 9일 이전에 월정액상태변경API를 이용하여 해지예약 취소(reactivate)를 진행할 경우, 해당 상품의 상태(recurringState)는 0(자동 결제중)이 됩니다.
	 */



	public void queryPurchasesAsync() {
		final List<PurchaseData> result = new ArrayList<>();
		final long time = System.currentTimeMillis();
		Log.d(TAG, "Finally we enter queryPurchasesAsync and before new runnable");
		final Runnable auto = new Runnable() {
			@Override
			public void run() {
				Log.d(TAG, "============queryPurchasesAsync inside============");

				mPurchaseClient.queryPurchasesAsync(PurchaseClient.ProductType.AUTO, new PurchasesListener() {
					@Override
					public void onPurchasesResponse(IapResult iapResult, List<PurchaseData> purchaseData) {
						Log.i(TAG, "AUTO - Querying purchases elapsed time: " + (System.currentTimeMillis() - time + "ms"));
						if (iapResult.isSuccess()) {
							result.addAll(purchaseData);
						} else {
							Log.w(TAG, "AUTO - queryPurchasesAsync() got an error response code: " + iapResult.getResponseCode());
						}

						onPurchasesUpdated(iapResult, result);
					}
				});
			}
		};

		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				mPurchaseClient.queryPurchasesAsync(PurchaseClient.ProductType.INAPP, new PurchasesListener() {
					@Override
					public void onPurchasesResponse(IapResult iapResult, List<PurchaseData> purchaseData) {
						Log.i(TAG, "INAPP - Querying purchases elapsed time: " + (System.currentTimeMillis() - time + "ms"));
						if (iapResult.isSuccess()) {
							result.addAll(purchaseData);
						} else {
							Log.w(TAG, "INAPP - queryPurchasesAsync() got an error response code: " + iapResult.getResponseCode());
						}
						auto.run();
					}
				});
			}
		});
	}

	public void queryPurchasesAsync(@PurchaseClient.ProductType String productType) {
		final long time = System.currentTimeMillis();
		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				mPurchaseClient.queryPurchasesAsync(productType, new PurchasesListener() {
					@Override
					public void onPurchasesResponse(IapResult iapResult, List<PurchaseData> purchaseData) {
						Log.i(TAG, productType + " - Querying purchases elapsed time: " + (System.currentTimeMillis() - time + "ms"));
						if (iapResult.isSuccess()) {
							//onPurchaseUpdated(purchaseData);
							Log.e(TAG,"onpurchase res");
						} else {
							Log.w(TAG, productType + " - queryPurchasesAsync() got an error response code: " + iapResult.getResponseCode());
							handleErrorCode(iapResult);
						}
					}
				});
			}
		});
	}

	public void manageRecurringProductAsync(final PurchaseData purchaseData, final String recurringAction, final RecurringProductListener listener) {
		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				RecurringProductParams params = RecurringProductParams.newBuilder()
						.setPurchaseData(purchaseData)
						.setRecurringAction(recurringAction)
						.build();
				mPurchaseClient.manageRecurringProductAsync(params, listener);
			}
		});
	}

	public void getStoreCode(final StoreInfoListener listener) {
		executeServiceRequest(new Runnable() {
			@Override
			public void run() {
				mPurchaseClient.getStoreInfoAsync(listener);
			}
		});
	}


	private void saveStoreCode(String storeCode) {
		SharedPreferences.Editor spe = getPreferences(MODE_PRIVATE).edit();
		spe.putString(null, storeCode);
		spe.apply();
	}
	
	//======================== 여기서부터는 MainActivity 그냥 때려받은 코드 ====================================

	private void showProgressDialog() {
		Log.e(TAG,"ShowProgressDialog");
		if (!isFinishing() && !isShowingProgressDialog()) {
			/*if (mProgressDialog == null) {
				Log.e(TAG,"ShowProgressDialog NULL");
				mProgressDialog = new ProgressDialog(this);
			}*/
			mProgressDialog.setMessage("Service connection...");
			mProgressDialog.show();
		}
	}

	private boolean isShowingProgressDialog() {
		return mProgressDialog != null && mProgressDialog.isShowing();
	}

	private void showDialog(CharSequence message) {
		new AlertDialog.Builder(this)
				.setMessage(message)
				.setPositiveButton(android.R.string.ok, null)
				.create().show();
	}

	private void showDialog(CharSequence message, DialogInterface.OnClickListener listener) {
		new AlertDialog.Builder(this)
				.setMessage(message)
				.setPositiveButton(android.R.string.ok, listener)
				.setNegativeButton(android.R.string.cancel, null)
				.create().show();
	}


	private void updateCoinsPurchased(String productId) {
		int coins = getPurchasedCoins(productId);
		updateCoin(coins);
	}

	private int getPurchasedCoins(String productId) {
		switch (productId) {
			case "ruby_01":
				return 55;
			case "m_ruby_01":
				return 30;
			case "ruby_02":
				return 110;
			default:
				return 0;
		}
	}


	private void updateCoin(int coin) {
/*		SharedPreferences sp = getPreferences(MODE_PRIVATE);
		SharedPreferences.Editor spe = getPreferences(MODE_PRIVATE).edit();

		int savedCoins = sp.getInt(AppConstants.KEY_TOTAL_COIN, 0);
		savedCoins += coin;
		spe.putInt(AppConstants.KEY_TOTAL_COIN, savedCoins);
		spe.apply();

		mCoinView.setText(String.valueOf(savedCoins));*/
	}


}
