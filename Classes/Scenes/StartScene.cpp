#include "StartScene.h"
#include <vector>
#include <string>
USING_NS_CC;

Scene* StartScene::createScene()
{
	return StartScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Elecrystal Sound Team - Count.mp3", true);

	srand((unsigned)time(nullptr));

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto bgSprite = Sprite::create("s0.png");
	if (bgSprite == nullptr)
	{
		problemLoading("'s0.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		bgSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(bgSprite, 0);
	}


	auto startGameItem = MenuItemImage::create(
		"s2.png",
		"s21.png",
		CC_CALLBACK_1(StartScene::menuStartGameCallback, this));

	if (startGameItem == nullptr ||
		startGameItem->getContentSize().width <= 0 ||
		startGameItem->getContentSize().height <= 0)
	{
		problemLoading("'s2.png' and 's21.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + 100;
		startGameItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto startMenu = Menu::create(startGameItem, NULL);
	startMenu->setPosition(Vec2::ZERO);
	this->addChild(startMenu, 1);


	auto closeItem = MenuItemImage::create(
		"s1.png",
		"s11.png",
		CC_CALLBACK_1(StartScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'s1.png' and 's11.png'");
	}
	else
	{
		float x = origin.x + closeItem->getContentSize().width / 2 + 20;
		float y = origin.y + closeItem->getContentSize().height / 2 + 20;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto closeMenu = Menu::create(closeItem, NULL);
	closeMenu->setPosition(Vec2::ZERO);
	this->addChild(closeMenu, 1);


	auto _openMusicItem = MenuItemImage::create(
		"s3.jpg",
		"s31.jpg"
	);
	auto _closeMusicItem = MenuItemImage::create(
		"s31.jpg",
		"s3.jpg"
	);

	auto musicItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(StartScene::menuMusicCallback, this),
		_openMusicItem,
		_closeMusicItem,
		NULL);

	if (musicItem == nullptr ||
		musicItem->getContentSize().width <= 0 ||
		musicItem->getContentSize().height <= 0)
	{
		problemLoading("'s3.jpg' and 's31.jpg'");
	}
	else
	{
		float x = origin.x + closeItem->getContentSize().width / 2 + 20;
		float y = origin.y + closeItem->getContentSize().height / 2 + 280;
		musicItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto musicMenu = Menu::create(musicItem, NULL);
	musicMenu->setPosition(Vec2::ZERO);
	this->addChild(musicMenu, 1);

	auto label0 = Label::createWithTTF("Help :", "fonts/Marker Felt.ttf", 30);
	auto label1 = Label::createWithTTF("Direction control : WASD", "fonts/Marker Felt.ttf", 30);
	auto label2 = Label::createWithTTF("Attack : SPACE", "fonts/Marker Felt.ttf", 30);
	auto label3 = Label::createWithTTF("Take out the box weapon : Q", "fonts/Marker Felt.ttf", 30);
	auto label4 = Label::createWithTTF("Return to the safe scene : ESC", "fonts/Marker Felt.ttf", 30);
	auto label5 = Label::createWithTTF("Background music control : F", "fonts/Marker Felt.ttf", 30);
	auto label6 = Label::createWithTTF("Pause : P", "fonts/Marker Felt.ttf", 30);
	auto label7 = Label::createWithTTF("Continue : O", "fonts/Marker Felt.ttf", 30);

	label0->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 100 + 30));
	label1->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 100));
	label2->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 100 - 30));
	label3->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 100 - 60));
	label4->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 100 - 90));
	label5->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 100 - 120));
	label6->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 100 - 150));
	label7->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 100 - 180));

	this->addChild(label0, 2);
	this->addChild(label1, 2);
	this->addChild(label2, 2);
	this->addChild(label3, 2);
	this->addChild(label4, 2);
	this->addChild(label5, 2);
	this->addChild(label6, 2);
	this->addChild(label7, 2);

	return true;
}


void StartScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}

void StartScene::menuStartGameCallback(cocos2d::Ref* pSender)
{
	auto scene = SafeScene::create();

	Director::getInstance()->replaceScene(scene);
}

void StartScene::menuMusicCallback(cocos2d::Ref* pSender)
{
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

