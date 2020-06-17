#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "SafeScene.h"
#include "RiskScene1.h"
#include "RiskScene2.h"
#include "RiskScene3.h"
#include "SimpleAudioEngine.h"
#include "Hero1.h"

class StartScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuStartGameCallback(cocos2d::Ref* pSender);

	void menuMusicCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(StartScene);
};

#endif // __HELLOWORLD_SCENE_H__
