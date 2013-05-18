
#include "Android360Sdk.h"
#include "AppDelegate.h"
#include "GameScreen.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform\android\jni\JniHelper.h"

extern "C" {
	void Java_game_burlapdragon_BurlapDragonGameActivity_nativeAndroid360SdkResult(JNIEnv* env, jobject thiz, jint nRet, jstring strResult)
	{
		if (env == NULL)
			return;

		CCLog("Java_game_burlapdragon_BurlapDragonGameActivity_Android360SdkResult");

		CGameScreen *pGame = GetApp()->GetGameScreen();
		if (pGame == NULL)
			return;

		const char *pRst = env->GetStringUTFChars(strResult, NULL);
		pGame->Android360SdkResult(nRet, pRst);
		env->ReleaseStringUTFChars(strResult, pRst);
	}
}
#endif

CAndroid360Sdk::CAndroid360Sdk()
{

}

CAndroid360Sdk::~CAndroid360Sdk()
{

}
