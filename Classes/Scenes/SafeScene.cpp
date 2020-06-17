#include "SafeScene.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include <string>
using namespace std;

USING_NS_CC;

Scene* SafeScene::createScene()
{
	return SafeScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SafeScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SafeScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Elecrystal Sound Team.mp3", true);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	map = CCTMXTiledMap::create("map0.tmx");

	auto objects = map->objectGroupNamed("objects");

	auto startPoint = objects->getObject("player");

	startX = startPoint.at("x").asInt();
	startY = startPoint.at("y").asInt();
	
	map->setPosition(Vec2(visibleSize.width / 2 + origin.x - startX, visibleSize.height / 2 + origin.y - startY));

	this->addChild(map, 0);

	hero = new Hero1(startX, startY, 3);

	hero->draw(this);

	auto *dispatcher = Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();

	keyListener->onKeyPressed = CC_CALLBACK_2(SafeScene::onKeyPressed, this);

	keyListener->onKeyReleased = CC_CALLBACK_2(SafeScene::onKeyReleased, this);

	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	this->scheduleUpdate();

	return true;
}


void SafeScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}


void SafeScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_W) {

		hero->setCD(1);

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_A) {

		hero->setCD(4);

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_D) {

		hero->setCD(2);

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_S) {

		hero->setCD(3);

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_F) {

		bool isMusic = CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();

		if (isMusic == true)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}

	}
}
void SafeScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_W && hero->getCD() == 1) {

		hero->setCD(0);

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_A && hero->getCD() == 4) {

		hero->setCD(0);

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_D && hero->getCD() == 2) {

		hero->setCD(0);

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_S && hero->getCD() == 3) {

		hero->setCD(0);

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_P) {

		CCScheduler *defaultScheduler = CCDirector::sharedDirector()->getScheduler();

		defaultScheduler->pauseTarget(this);

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_O) {

		CCScheduler *defaultScheduler = CCDirector::sharedDirector()->getScheduler();

		defaultScheduler->resumeTarget(this);

	}
}

void SafeScene::update(float delta)
{

	hero->move(map);

	next();

	this->adjust();
}

void SafeScene::adjust()
{
	int moveX = hero->getMX();
	int moveY = hero->getMY();

	ActionInterval* moveBy = MoveBy::create(0.01f, Vec2(-moveX, -moveY));

	this->runAction(moveBy);
}

void SafeScene::closeScene()
{
	auto scene = StartScene::create();

	Director::getInstance()->replaceScene(scene);
}

void SafeScene::next()
{
	float curX = hero->curX;
	float curY = hero->curY;

	Vec2 tilePosition = tileCoordForPosition(Vec2(curX, curY), map);

	TMXLayer* next = map->layerNamed("next");

	auto tileGid = next->tileGIDAt(tilePosition);

	if (tileGid != 0)
	{
		auto nextScene = RiskScene1::create(hero->getW1()->getID(), hero->getCH(), hero->getCS(), hero->getCM());

		Director::getInstance()->replaceScene(nextScene);
	}
}

