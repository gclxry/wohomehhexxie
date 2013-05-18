
#include "cocos2d.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "SceneGameEnter.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform\android\jni\JniHelper.h"

extern "C" {
	void Java_game_burlapdragon_BurlapDragonGameActivity_nativeAndroid360SdkResult(JNIEnv* env, jobject thiz, jint nRet, jstring strResult)
	{
		if (env == NULL)
			return;

		CCLog("Java_game_burlapdragon_BurlapDragonGameActivity_nativeAndroid360SdkResult");

		const char *pRst = env->GetStringUTFChars(strResult, NULL);
		GetApp()->Android360SdkResult(nRet, pRst);
		env->ReleaseStringUTFChars(strResult, pRst);
	}
}
#endif

AppDelegate* GetApp()
{
	return g_pAppDelegate;
}

AppDelegate::AppDelegate()
{
	m_pSceneGameEnter = NULL;
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	if (pDirector == NULL)
		return false;

    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	m_pSceneGameEnter = CSceneGameEnter::GetScene();
	if (m_pSceneGameEnter == NULL)
		return false;

    // run
    pDirector->runWithScene(m_pSceneGameEnter);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

CSceneGameEnter* AppDelegate::GetGameEnterScene()
{
	return m_pSceneGameEnter;
}

void AppDelegate::Android360SdkResult(int nMsgId, const char* pszRet)
{
	CCLog(pszRet);
}
