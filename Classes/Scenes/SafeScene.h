#ifndef __SAFE_SCENE_H__
#define __SAFE_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include "Hero1.h"
#include "RiskScene1.h"
#include "StartScene.h"

USING_NS_CC;


class SafeScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SafeScene);

	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);

	virtual void update(float delta);

	void adjust();

	void closeScene();

	void next();

private:

	int startX;
	int startY;

	Hero* hero;

	CCTMXTiledMap* map;
};

#endif // __HELLOWORLD_SCENE_H__

