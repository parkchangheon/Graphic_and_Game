#include "FaceBookManager.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include <jni.h>
#include<string>

USING_NS_CC;


void FaceBookManager::login()
{
	log("ITITITITIIIITITIITITITIITITITIITIIT");
}

extern "C"
{
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_facebookLogin_LoginStart(JNIEnv* env, jclass clazz) {
		log("lollollollollollollollollollollollollollollollollollollollollollollollollollollollollollol")
	}
};
