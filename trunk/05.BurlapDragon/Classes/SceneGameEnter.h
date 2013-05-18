#ifndef __SCENE_GAME_ENTER_H__
#define __SCENE_GAME_ENTER_H__

#include "cocos2d.h"

USING_NS_CC;

class CSceneGameEnter : public CCScene
{
public:
	CSceneGameEnter();
	~CSceneGameEnter();

	static CSceneGameEnter* GetScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

    // implement the "static node()" method manually
    CREATE_FUNC(CSceneGameEnter);


};

#endif  // __SCENE_GAME_ENTER_H__
