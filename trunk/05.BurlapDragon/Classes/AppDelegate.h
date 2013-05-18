
#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"
USING_NS_CC;

class CSceneGameEnter;

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class AppDelegate : private cocos2d::CCApplication
{
public:
	AppDelegate();
	virtual ~AppDelegate();

	/**
	@brief    Implement CCDirector and CCScene init code here.
	@return true    Initialize success, app continue.
	@return false   Initialize failed, app terminate.
	*/
	virtual bool applicationDidFinishLaunching();

	/**
	@brief  The function be called when the application enter background
	@param  the pointer of the application
	*/
	virtual void applicationDidEnterBackground();

	/**
	@brief  The function be called when the application enter foreground
	@param  the pointer of the application
	*/
	virtual void applicationWillEnterForeground();
	
	/**
	@brief  取得游戏入口场景
	@param  
	*/
	CSceneGameEnter* GetGameEnterScene();
	
	/**
	@brief  
	@param  
	*/
	void Android360SdkResult(int nMsgId, const char* pszRet);

private:
	CSceneGameEnter* m_pSceneGameEnter;
};

extern AppDelegate* g_pAppDelegate;
AppDelegate* GetApp();


#endif  // __APP_DELEGATE_H__
