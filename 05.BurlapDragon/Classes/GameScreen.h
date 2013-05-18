#ifndef __GAME_SCREEN_H__
#define __GAME_SCREEN_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "chipmunk.h"
#include "SimpleAudioEngine.h"
#include "ExtensionMacros.h"
#include "GUI\CCControlExtension\CCControlExtensions.h"
#include "Android360Sdk.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CGameScreen : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static CCScene* scene(CGameScreen** ppGameScreen);
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(CGameScreen);

	// ���ܵ����ؼ�
    virtual void keyBackClicked(void);
    virtual void keyMenuClicked(void);
	
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	
	void ReadMapInfo(void);

	// 360SDK �Ļص�
	void Android360SdkResult(int nMsgId, const char* pszRet);

private:
	static CCScene* ms_BaseScene;
	static CGameScreen* ms_GameScreen;
};

#endif  // __GAME_SCREEN_H__