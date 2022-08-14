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
import com.gaa.sdk.iap.ProductDetailsListener;

import com.google.android.gms.ads.rewarded.RewardedAd;
import com.newzensoft.poker.R;
import com.numixent.inApp.helper.ConverterFactory;
import com.numixent.inApp.helper.ParamsBuilder;
import com.numixent.inApp.pdu.Response;
import com.skplanet.dodo.IapPlugin;
import com.skplanet.dodo.IapResponse;
import com.skplanet.dodo.helper.PaymentParams;
import com.skplanet.dodo.helper.PaymentParams.Builder;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
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
	private Callback mCallback;
	private ProgressDialog mProgressDialog;
	private static IapManager iapMgr = null;

	public interface Callback {
		void onPurchaseClientSetupFinished();
		void onConsumeFinished(PurchaseData purchaseData, IapResult iapResult);
		void onAcknowledgeFinished(PurchaseData purchaseData, IapResult iapResult);
		void onPurchaseUpdated(List<PurchaseData> purchases);
		void onNeedLogin();
		void onNeedUpdate();
		void onError(String message);
	}


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
		mCallback = new Callback() {
			@Override
			public void onPurchaseClientSetupFinished() {
				System.out.print("Yeah");

				dismissProgressDialog();
				IapManager.getStoreCode(new StoreInfoListener() {
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
			public void onConsumeFinished(PurchaseData purchaseData, IapResult iapResult) {
				System.out.print("Yeah");
			}

			@Override
			public void onAcknowledgeFinished(PurchaseData purchaseData, IapResult iapResult) {
				System.out.print("Yeah");
			}

			@Override
			public void onPurchaseUpdated(List<PurchaseData> purchases) {
				System.out.print("Yeah");
			}

			@Override
			public void onNeedLogin() {
				System.out.print("Yeah");
			}

			@Override
			public void onNeedUpdate() {
				System.out.print("Yeah");
			}

			@Override
			public void onError(String message) {
				System.out.print("Yeah" + message);
			}
		};

		mPurchaseClient = PurchaseClient.newBuilder(activity)
				.setBase64PublicKey(null)  //AppSecurity.getPublicKey()
				.setListener(this)
				.build();
		Log.d(TAG, "before start connection - 0 ");

		startConnection(new Runnable() {  //이 runnable은 멀티스레드로 서버에서 값을 검사하거나 실시간으로 상황을 판단해야 하며, 다른 일을 해야하는 상황에 쓰인다.
			@Override
			public void run() {
				Log.d(TAG, "Start Connection _ tag1");
				mCallback.onPurchaseClientSetupFinished();
				Log.d(TAG, "Setup successful. Querying inventory.");
				queryPurchasesAsync();
			}
		});
	}

/*	public IapManager(@NonNull Activity activity) {
		mActivity = activity;

		mCallback = new Callback() {
			@Override
			public void onPurchaseClientSetupFinished() {
				System.out.print("Yeah");
			}

			@Override
			public void onConsumeFinished(PurchaseData purchaseData, IapResult iapResult) {
				System.out.print("Yeah");
			}

			@Override
			public void onAcknowledgeFinished(PurchaseData purchaseData, IapResult iapResult) {
				System.out.print("Yeah");
			}

			@Override
			public void onPurchaseUpdated(List<PurchaseData> purchases) {
				System.out.print("Yeah");
			}

			@Override
			public void onNeedLogin() {
				System.out.print("Yeah");
			}

			@Override
			public void onNeedUpdate() {
				System.out.print("Yeah");
			}

			@Override
			public void onError(String message) {
				System.out.print("Yeah" + message);
			}
		};
		mPurchaseClient = PurchaseClient.newBuilder(activity)
				.setBase64PublicKey(null)
				.setListener(this)
				.build();

		startConnection(new Runnable() {  //여기가 원스토어 서비스와 연결을 하는 부분
			@Override
			public void run() {
				mCallback.onPurchaseClientSetupFinished();
				Log.d(TAG, "Setup successful. Querying inventory.");
				queryPurchasesAsync();
			}
		});
	}*/

	public void destroy() {
		if (mPurchaseClient != null) {
			mPurchaseClient.endConnection();
			mPurchaseClient = null;
		}
	}

	public void startConnection(final Runnable executeOnSuccess) {
		mPurchaseClient.startConnection(new PurchaseClientStateListener() {

			@Override
			public void onSetupFinished(IapResult iapResult) {
				if (iapResult.isSuccess()) {  //the purchasesclient is ready   , you can query purchases here
					isServiceConnected = true;
					queryProductDetailAsync();
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
				isServiceConnected = false;
			}
		});
	}



	public void onPurchaseClientSetupFinished() {
		dismissProgressDialog();
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


	private void executeServiceRequest(Runnable runnable) {
		if (isServiceConnected) {
			runnable.run();
		} else {
			startConnection(runnable);
		}
	}

	private void handleErrorCode(IapResult iapResult) {
		if(iapResult.isSuccess()){
			Log.d(TAG, "the purchase is ready. we can query at here");
		}

		else if (iapResult.getResponseCode() == PurchaseClient.ResponseCode.RESULT_NEED_LOGIN) {
			Log.w(TAG, "handleErrorCode() RESULT_NEED_LOGIN");
			mCallback.onNeedLogin();
		} else if (iapResult.getResponseCode() == PurchaseClient.ResponseCode.RESULT_NEED_UPDATE) {
			Log.w(TAG, "handleErrorCode() RESULT_NEED_UPDATE");
			mCallback.onNeedUpdate();
		} else {
			String message = iapResult.getMessage() + "(" + iapResult.getResponseCode() + ")";
			Log.d(TAG, "handleErrorCode() error: " + message);
			mCallback.onError(message);
		}
	}

	// =================================================================================================================
	// implements PurchasesUpdatedListener
	// =================================================================================================================
	@Override
	public void onPurchasesUpdated(IapResult iapResult, List<PurchaseData> purchaseData) {
		if (iapResult.isSuccess()) {
			mCallback.onPurchaseUpdated(purchaseData);
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


	private void buyProduct(final String productId, @PurchaseClient.ProductType String productType) {
		Log.d(TAG, "buyProduct() - productId:" + productId + " productType: " + productType);
		/*
		 * TODO: AppSecurity.generatePayload() 는 예제일 뿐, 각 개발사의 규칙에 맞는 payload를 생성하여야 한다.
		 *
		 * 구매요청을 위한 Developer payload를 생성합니다.
		 * Developer Payload 는 상품의 구매 요청 시에 개발자가 임의로 지정 할 수 있는 문자열입니다.
		 * 이 Payload 값은 결제 완료 이후에 응답 값에 다시 전달 받게 되며 결제 요청 시의 값과 차이가 있다면 구매 요청에 변조가 있다고 판단 하면 됩니다.
		 * Payload 검증을 통해 Freedom 과 같은 변조 된 요청을 차단 할 수 있으며, Payload 의 발급 및 검증 프로세스를 자체 서버를 통해 이루어 지도록합니다.
		 * 입력 가능한 Developer Payload는 최대 200byte까지 입니다.
		 */
		String devPayload = generatePayload();

		// 구매 후 dev payload를 검증하기 위하여 프리퍼런스에 임시로 저장합니다.
		savePayloadString(devPayload);
		//showProgressDialog();

		/*
		 * PurchaseClient의 launchPurchaseFlowAsync API를 이용하여 구매요청을 진행합니다.
		 * 상품명을 공백("")으로 요청할 경우 개발자센터에 등록된 상품명을 결제화면에 노출됩니다. 구매시 지정할 경우 해당 문자열이 결제화면에 노출됩니다.
		 */
		PurchaseFlowParams params = PurchaseFlowParams.newBuilder()
				.setProductId(productId)
				.setProductType(productType)
				.setDeveloperPayload(devPayload)
				.setProductName("")
				.setGameUserId("")
				.setPromotionApplicable(false)
				.build();

		Log.d(TAG, "Before the launchPurchaseFlow");
		launchPurchaseFlow(params);
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



	public void queryProductDetailAsync() {
		/*final List<String> productIdList, @PurchaseClient.ProductType final String productType, final ProductDetailsListener listener*/

		List<String> productIdList = new ArrayList<>();
		List<String> productIdList2 = new ArrayList<>();

		productIdList.add("ruby_01");
		productIdList2.add("m_ruby_01");  //맞는지 모르겠지만 일단 상품 PID 하드코딩으로 떄려넣음

		ProductDetailsParams params = ProductDetailsParams.newBuilder()
				.setProductIdList(productIdList2)
				.setProductType(PurchaseClient.ProductType.INAPP)
				.build();
		mPurchaseClient.queryProductDetailsAsync(params, new ProductDetailsListener() {
			@Override
			public void onProductDetailsResponse(IapResult iapResult, @Nullable List<ProductDetail> list)
			{
				if(iapResult.isSuccess() && list != null){
					for(ProductDetail skuDetail : list){
						Log.d(TAG, "ProductDetail = " + skuDetail.toString());
					}
				}
				else{
					Log.d(TAG, iapResult.toJsonString());
				}
			}
		});
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
								mCallback.onConsumeFinished(purchaseData, iapResult);
							} else {
								mCallback.onError("purchaseToken not equal");
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
								mCallback.onAcknowledgeFinished(purchaseData, iapResult);
							} else {
								mCallback.onError("purchaseToken not equal");
							}
						} else {
							handleErrorCode(iapResult);
						}
					}
				});
			}
		});
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



	private void dismissProgressDialog() {
		if (isShowingProgressDialog()) mProgressDialog.dismiss();
	}

	private boolean isShowingProgressDialog() {
		return mProgressDialog != null && mProgressDialog.isShowing();
	}


	public void queryPurchasesAsync() {
		final List<PurchaseData> result = new ArrayList<>();
		final long time = System.currentTimeMillis();

		final Runnable auto = new Runnable() {
			@Override
			public void run() {
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
							mCallback.onPurchaseUpdated(purchaseData);
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
	
	//======================== MainActivity 그냥 때려받은 코드 ====================================

	@Override
	public void onPurchaseUpdated(List<PurchaseData> purchases) {
		dismissProgressDialog();

		for (PurchaseData purchase: purchases) {
//            if (!isValidPayload(purchase.getDeveloperPayload())) {
//                Log.d(TAG, "onPurchaseUpdated() - OK :: invalid dev payload: " + purchase.getDeveloperPayload());
//                showDialog(getString(R.string.msg_alert_dev_payload_invalid));
//                return;
//            }

			if (AppSecurity.verifyPurchase(purchase.getOriginalJson(), purchase.getSignature())) {
				final String productId = purchase.getProductId();
				if (AppConstants.AutoType.PRODUCT_AUTO_100000.equals(productId)) {
					// 월정액상품이면 소비를 수행하지 않는다.
					if (purchase.isAcknowledged()) {
						saveMonthlyItem(purchase);
					} else {
						mPurchaseManager.acknowledgeAsync(purchase);
					}
				} else if (AppConstants.InappType.PRODUCT_INAPP_50000.equals(productId)) {
					// 프리미엄 인앱 상품도 소비를 수행하지 않는다.
					if (purchase.isAcknowledged()) {
						updateOneMore(true);
					} else {
						mPurchaseManager.acknowledgeAsync(purchase);
					}
				} else {
					// 관리형상품(inapp)의 구매완료 이후 또는 구매내역조회 이후 소비되지 않는 관리형상품에 대해서 소비를 진행합니다.
					mPurchaseManager.consumeAsync(purchase);
				}
			} else {
				showDialog(getString(R.string.msg_alert_signature_invalid));
			}
		}
	}


}
































	/*
	private static IapManager iapMgr = null;
    private IapPlugin mPlugin = null;
    private Activity activity;
    private String IAP_APP_ID = "";
    private String mRequestId;
    private boolean isPrint = true;
    private String mTxid;
    private String mReceipt;
    private String mTid;

	private Set<String> mTokenToBe;
	private boolean isServiceConnected;

	private final String TAG = IapManager.class.getSimpleName();
	private IapManager mPurchaseClient;
	private Callback mCallback;

	public interface Callback {
		void onPurchaseClientSetupFinished();
		void onConsumeFinished(PurchaseData purchaseData, IapResult iapResult);
		void onAcknowledgeFinished(PurchaseData purchaseData, IapResult iapResult);
		void onPurchaseUpdated(List<PurchaseData> purchases);
		void onNeedLogin();
		void onNeedUpdate();
		void onError(String message);
	}


    public static native void OnIapResult(boolean sucess , String errMsg , String tid , String txid , String receipt);

	private IapManager() {

	}

	public static Object instance() {
		System.out.println("instance 1");
		if (iapMgr == null) {
			System.out.println("instance 2");
			iapMgr = new IapManager();
		}
		System.out.println("instance 3");
		return iapMgr;
	}

	public void init(Object obj) {
		activity = (Activity) obj;
		ApplicationInfo ai;
        try
        {
            //System.out.println(context.getPackageName());
            ai = activity.getPackageManager().getApplicationInfo(activity.getPackageName(), PackageManager.GET_META_DATA);
        }
        catch(android.content.pm.PackageManager.NameNotFoundException e)
        {
            return;
        }
        Bundle aBundle = ai.metaData;
		IAP_APP_ID = aBundle.getString("t_app_id");
		setDevelopMode(true);
	}

	public void exit() {
		if(mPlugin != null) {
			mPlugin.exit();
		}
	}

	public void setDevelopMode(boolean delvopmode) {
		println("setDevelopMode1");
		if(mPlugin == null) {
			println("setDevelopMode2");
			if(delvopmode == true)
				mPlugin = IapPlugin.getPlugin(activity, IapPlugin.DEVELOPMENT_MODE);		//���� ����
			else
				mPlugin = IapPlugin.getPlugin(activity, IapPlugin.RELEASE_MODE);			//��뼭��
		}
	}





	private void handleErrorCode(IapResult iapResult) {
		if (iapResult.getResponseCode() == PurchaseClient.ResponseCode.RESULT_NEED_LOGIN) {
			Log.w(TAG, "handleErrorCode() RESULT_NEED_LOGIN");
			mCallback.onNeedLogin();
		} else if (iapResult.getResponseCode() == PurchaseClient.ResponseCode.RESULT_NEED_UPDATE) {
			Log.w(TAG, "handleErrorCode() RESULT_NEED_UPDATE");
			mCallback.onNeedUpdate();
		} else {
			String message = iapResult.getMessage() + "(" + iapResult.getResponseCode() + ")";
			Log.d(TAG, "handleErrorCode() error: " + message);
			mCallback.onError(message);
		}
	}

	@Override
	public void onPurchasesUpdated(IapResult iapResult, List<PurchaseData> purchaseData) {
		if (iapResult.isSuccess()) {
			mCallback.onPurchaseUpdated(purchaseData);
			return;
		}

		handleErrorCode(iapResult);
	}


























	//ORIGIN CODE


	//application id �� �˰� �ְ� , in-app productid , productName , tid	//������ ������
	public void sendPaymentRequest(boolean delvopmode , String productid , String productName , String productTid) {
		mTid = productTid;
		println("sendPaymentRequest productid = " + productid + "productName = " + productName + "productTid" + productTid );
		//String parameter = makeRequest(productid , productName , productTid);
		Builder payBuilder = new PaymentParams.Builder(IAP_APP_ID, productid);
		payBuilder.addTid(productTid);
		PaymentParams params = payBuilder.build();
		final String fProductId = productid;
	    String requestId = mPlugin.sendPaymentRequest(
	                new IapPlugin.RequestCallback() {
	                    @Override
	                    public void onResponse(IapResponse data) {
	                    	println("onrespoinse");
	                        if (data == null || data.getContentLength() <= 0) {
	                            // TODO Unusual error
	                        	println("onResponse() response data is null");
	                        	OnIapResult(false , "response data is null", "" , "" , "");
	                            return;
	                        }
	                        // 1. JSON �����͸� ���� ��ü ��ȯ ��� ��
	                        Response response = ConverterFactory.getConverter().fromJson(data.getContentToString());

	                        if (response == null) {
	                            // TODO invalid response data
				 				println("onResponse() invalid response data");
				 				OnIapResult(false , "invalid response data" , "" , "" , "");
	                            return;
	                        }

	                        println("onrespoinse 1");
	                        // TODO for logging
	                        StringBuffer sb = new StringBuffer("onResponse() \n");
	                        sb.append("From:" + data.getContentToString())
	                                .append("\n")
	                                .append("To:" + response.toString());

	                        // TODO ���� �Ϸ� �� ó�� �� - ����
	                        // C1. ��� �ڵ� üũ
	                        // response.result.code
	                        println("onrespoinse 2");
	                        if (!response.result.code.equals("0000")) {
	                        	println("Failed to request to purchase a item");
	                        	OnIapResult(false , response.result.message , "" , "" , "");
	                            return;
	                        }
	                        // S1. ���� �Ϸ��� ��� �߱޵� ���� �������� ���� ���� Ȯ�� üũ (���� �ǰ�)
	                        // response.result.txid
	                        // response.result.receipt
	                        println("onrespoinse 3");
	                        println("response.result.txid" + response.result.txid + "response.result.receipt" + response.result.receipt);

	                        // S2. ���� ��ǰ Ÿ�Կ� ���� ��ǰ �߱� ó��
	                        // ������ �߱� / ������ ��ȯ

	                        // TODO ���� �Ϸ� �� ó�� ��- ����
	                        // C1. ��� �ڵ� üũ
	                        // response.result.code

	                        // F1. ��� �ڵ尡 ��� ������ ��� ����ڰ� ������ �� �ִ� ������� �˸� (�˾� â ��)

	                        // 2. JSON ������ �״�� ��� ��

	                        // TODO ���� �Ϸ� �� ó�� �� - ���� / ����

	                         // C1. ��� �ڵ� üũ

	                        try {
	                            JSONObject jsonMain = new JSONObject(data
	                                    .getContentToString());
	                            JSONObject jsonResult = jsonMain.getJSONObject("result");
	                            String code = jsonResult.getString("code");
	                            println("code = " + code);
	                            if (code.equals("0000")) {
	                                // S1. ���� �Ϸ��� ��� �߱޵� ���� �������� ���� ���� Ȯ�� üũ (���� �ǰ�)
	                            	println("OnIapResult sucess");
	                            	mReceipt = jsonResult.getString("receipt");
	                                mTxid = jsonResult.getString("txid");
	                                // S2. ���� ��ǰ Ÿ�Կ� ���� ��ǰ �߱� ó�� // ������ �߱� / ������ ��ȯ
	                                println("OnIapResult sucess mTid" + mTid);
	                    	        OnIapResult(true , "Sucess" , mTid ,  mTxid , mReceipt);

	                            } else {
	                                // F1. ��� �ڵ尡 ��� ������ ��� ����ڰ� ������ �� �ִ� ������� �˸�
	                                // (�˾� â ��)
	                            	println("OnIapResult not 0000");
	                            	OnIapResult(false , code , mTid ,  mTxid , mReceipt);
	                            }
	                        } catch (JSONException e) {
	                            e.printStackTrace();
	                        }
	                    }

	                    @Override
	                    public void onError(String reqid, String errcode,
	                            String errmsg) {
	                        // TODO Error occurred
	                        println("onError() identifier:" + reqid + " code:" + errcode + " msg:" + errmsg);
	                        OnIapResult(false , errmsg , "" , "" ,  "");
	                    }
	                } , params);

	        if (requestId == null || requestId.length() == 0) {
	            // TODO request failure
	        	println("requestId is null error");
	        	OnIapResult(false , "requestId error" ,"" , "" , "");
	            return;
	        }
	}

	 private String makeRequest(String productid , String productName , String productTid) {
		    ParamsBuilder pb = new ParamsBuilder();
	        pb.put(ParamsBuilder.KEY_APPID,  IAP_APP_ID);
	        pb.put(ParamsBuilder.KEY_PID, productTid);
	        pb.put(ParamsBuilder.KEY_PNAME, productName);
	        pb.put(ParamsBuilder.KEY_TID, productTid);
	        return pb.build();
	 }

	 private void println(String string) {
			// TODO Auto-generated method stub
			if (isPrint)
				System.out.println(string);
	 }
}

*/