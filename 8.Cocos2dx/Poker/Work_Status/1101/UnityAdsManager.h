#pragma once
#include "NxSingleton.h"
#include "NxFramework.h"
#include "HeroUtil.h"


#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include "jni/JniHelper.h"
#endif

#define UNITYADS_OBJECT "com/newzensoft/admob/UnityAdsManager"

//using google::protobuf::Message;

class UnityAdsManager : public Singleton < UnityAdsManager >
{

public:
	UnityAdsManager();
	~UnityAdsManager();

public:	
	bool isReadyShowAds();
	void showAds();
	void unityAdsFinish(string zoneId);
	void unityAdsError(string error);
	void setUseFlag(bool flag);
	void SetReward(bool val);
	void SetLoaded(bool val);
	void HandleReward();
public:
	bool mUseFlag;
	bool CanReward = false;
	bool mIsLoaded = false;
	bool ShowIntend = false;
};

