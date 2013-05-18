
#include "cocos2d.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "GameScreen.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

AppDelegate* GetApp()
{
	return g_pAppDelegate;
}

AppDelegate::AppDelegate()
{
	m_pBaseScene = NULL;
	m_pGameScreen = NULL;
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
    m_pBaseScene = CGameScreen::scene(&m_pGameScreen);
	if (m_pBaseScene == NULL)
		return false;

    // run
    pDirector->runWithScene(m_pBaseScene);
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

CCScene* AppDelegate::GetBaseScene()
{
	return m_pBaseScene;
}

CGameScreen* AppDelegate::GetGameScreen()
{
	return m_pGameScreen;
}
