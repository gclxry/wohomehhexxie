#include "GameScreen.h"
#include "AES.h"



CCScene* CGameScreen::scene(CGameScreen** ppGameScreen)
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        CGameScreen *layer = CGameScreen::create();
        CC_BREAK_IF(! layer);
		if (ppGameScreen != NULL)
			*ppGameScreen = layer;

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CGameScreen::init()
{
    bool bRet = false;
    do 
    {
		// 打开对返回键的支持
		this->setKeypadEnabled(true);

		// 读取xml信息
		ReadMapInfo();

        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(CGameScreen::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to CGameScreen layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to CGameScreen layer as a child layer.
        this->addChild(pLabel, 1);

		// 取得屏幕大小
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        // 3. Add add a splash screen, show the cocos2d splash image.
		CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        CC_BREAK_IF(!pSprite);
        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));
        // Add the sprite to CGameScreen layer as a child layer.
        this->addChild(pSprite, 1);

		CCSprite *pPlayer = CCSprite::create("fairy.png");
		if (pPlayer != NULL)
		{
			pPlayer->setPosition(ccp(100, 100));
			//pPlayer->setPosition(ccp(size.width/2, size.height/2));
			this->addChild(pPlayer, 2);
		}


        bRet = true;
    } while (0);

    return bRet;
}

void CGameScreen::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}


bool CGameScreen::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void CGameScreen::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CGameScreen::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void CGameScreen::keyBackClicked(void) 
{
	CCLayer::keyBackClicked();

	CCDirector::sharedDirector()->popToRootScene();
	//CCDirector::sharedDirector()->end();
	//CCDirector::sharedDirector()->resume();
	//CCDirector::sharedDirector()->pause();
}

void CGameScreen::keyMenuClicked(void) 
{
	CCLayer::keyMenuClicked();
}

void CGameScreen::ReadMapInfo(void) 
{
	CCFileUtils *pPathUtil = CCFileUtils::sharedFileUtils();
	if (pPathUtil == NULL)
		return;

	const char* pcszPath = pPathUtil->fullPathFromRelativePath("big_map.xml");
	if (pcszPath == NULL || strlen(pcszPath) <= 0)
		return;
	
	//NSLog("CGameScreen::ReadMapInfo xmlPath=%s", pcszPath);
	CCLog("CGameScreen::ReadMapInfo xmlPath=%s", pcszPath);


//	CCSAXParser saxXml;
//	if (!saxXml.parse(pcszPath))
//		return;
	

}
