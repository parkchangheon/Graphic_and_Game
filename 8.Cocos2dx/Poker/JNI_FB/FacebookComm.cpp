#include <jni.h>
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper2.h"
#endif
//#include "platform/android/jni/JniHelper2.h"
#include "FaceBookMgr.h"


//기존 방식
//extern "C"
//{
//
//	/** This is the C implementation of the Java native method.
//	@param env Pointer to JVM environment
//	@param thiz Reference to Java this object
//	*/
//	JNIEXPORT void JNICALL Java_com_numixent_social_FacebookMgr_OnFacebookEvent(JNIEnv* env, jobject thiz, int _envId, jstring _data)
//	{
//		std::string friendData = JniHelper::jstring2string(_data);
//		FaceBookMgr::getSingletonPtr()->OnFacebookEvent(_envId, friendData);
//	}
//
//	JNIEXPORT void JNICALL Java_com_numixent_social_FacebookMgr_FacebookUserData(JNIEnv* env, jobject thiz, jstring _id, jstring _name, jstring _email, jstring _photourl)
//	{
//		FaceBookMgr::getSingletonPtr()->m_Userata.fb_id = JniHelper::jstring2string(_id);
//		FaceBookMgr::getSingletonPtr()->m_UserData.fb_name = JniHelper::jstring2string(_name);
//		FaceBookMgr::getSingletonPtr()->m_UserData.fb_email = JniHelper::jstring2string(_email);
//		FaceBookMgr::getSingletonPtr()->m_UserData.fb_photoUrl = JniHelper::jstring2string(_photourl);
//	}
//}



// PCH Code Similar to Origin


//extern "C"
//JNIEXPORT void JNICALL
//Java_org_cocos2dx_cpp_FacebookMgr_OnFacebookEvent(JNIEnv *env, jclass clazz, jint param_int,
//                                                  jstring param_string) {
//    
//}
//extern "C"
//JNIEXPORT void JNICALL
//Java_org_cocos2dx_cpp_FacebookMgr_FacebookUserData(JNIEnv *env, jclass clazz, jstring param_string1,
//                                                   jstring param_string2, jstring param_string3,
//                                                   jstring param_string4) {
//    // parameter 순서는 id, name, email, photourl 이다
//
//    //들어오는지만 확인
//    FaceBookMgr::getSingletonPtr()->m_UserData.fb_id = JniHelper::jstring2string(param_string1);
//
//}



//PCH CODE New with My algorithm