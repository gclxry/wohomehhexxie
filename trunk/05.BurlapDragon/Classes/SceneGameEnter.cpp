
#include "SceneGameEnter.h"

CSceneGameEnter::CSceneGameEnter()
{

}

CSceneGameEnter::~CSceneGameEnter()
{

}

CSceneGameEnter* CSceneGameEnter::GetScene()
{
	static CSceneGameEnter* sGameEnter = NULL;
	if (sGameEnter == NULL)
	{
		sGameEnter = CSceneGameEnter::create();
	}

	return sGameEnter;
}

// on "init" you need to initialize your instance
bool CSceneGameEnter::init()
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
