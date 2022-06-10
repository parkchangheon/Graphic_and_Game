#include "FaceBookMgr.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include 
#endif

USING_NS_CC;

void FaceBookMgr::LoginSession()
{
	log("I have Passed the Session!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	connectFaceBook();
#endif
}


void FaceBookMgr::SetFacebookUserData()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookManagerObject facebookObject;

	if (!facebookObject.getObject())
		return;

	JniMethodInfo t;

	if (JniHelper::getMethodInfo(t, FACEBOOK_OBJECT, "GetFacebookUserData", "()V"))
	{
		t.env->CallVoidMethod(facebookObject.getObject(), t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}