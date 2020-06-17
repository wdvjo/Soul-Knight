#include "Blood.h"

Blood::Blood(Scene* scene, Hero* hero)
{
	addMoveX = addMoveY = 0;

	lastMX = lastMY = 0;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int maxH = hero->getMH();
	int curH = hero->getCH();

	int maxS = hero->getMS();
	int curS = hero->getCS();

	int maxM = hero->getMM();
	int curM = hero->getCM();

	mainBlood = Sprite::create("xuetiao.jpg");
	healthImage = Sprite::create("health.jpg");
	shieldImage = Sprite::create("shield.jpg");
	magicImage = Sprite::create("magic.jpg");

	std::string hT = String::createWithFormat("%d / %d", curH, maxH)->getCString();
	healthText = Label::createWithTTF(hT, "fonts/Marker Felt.ttf", 24);

	std::string sT = String::createWithFormat("%d / %d", curS, maxS)->getCString();
	shieldText = Label::createWithTTF(sT, "fonts/Marker Felt.ttf", 24);

	std::string mT = String::createWithFormat("%d / %d", curM, maxM)->getCString();
	magicText = Label::createWithTTF(mT, "fonts/Marker Felt.ttf", 24);

	mainBlood->setPosition(Vec2(origin.x + 200, visibleSize.height + origin.y - 100));

	healthImage->setPosition(Vec2(origin.x + 226 - 136, visibleSize.height + origin.y - 50 - 19));
	shieldImage->setPosition(Vec2(origin.x + 226 - 136, visibleSize.height + origin.y - 96 - 20));
	magicImage->setPosition(Vec2(origin.x + 226 - 138, visibleSize.height + origin.y - 141 - 22));

	healthImage->setAnchorPoint(Vec2(0, 0));
	shieldImage->setAnchorPoint(Vec2(0, 0));
	magicImage->setAnchorPoint(Vec2(0, 0));

	healthText->setPosition(Vec2(origin.x + 226, visibleSize.height + origin.y - 50));
	shieldText->setPosition(Vec2(origin.x + 226, visibleSize.height + origin.y - 96));
	magicText->setPosition(Vec2(origin.x + 226, visibleSize.height + origin.y - 141));

	scene->addChild(mainBlood, 20);

	scene->addChild(healthImage, 21);
	scene->addChild(shieldImage, 21);
	scene->addChild(magicImage, 21);

	scene->addChild(healthText, 22);
	scene->addChild(shieldText, 22);
	scene->addChild(magicText, 22);
}

Blood::~Blood()
{
	mainBlood->release();
	healthImage->release();
	healthText->release();
	shieldImage->release();
	shieldText->release();
	magicImage->release();
	magicText->release();
}

void Blood::draw(Scene* scene, Hero* hero)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int maxH = hero->getMH();
	int curH = hero->getCH();

	int maxS = hero->getMS();
	int curS = hero->getCS();

	int maxM = hero->getMM();
	int curM = hero->getCM();

	double scaleH = static_cast<double>(curH) / maxH;
	double scaleS = static_cast<double>(curS) / maxS;
	double scaleM = static_cast<double>(curM) / maxM;

	scene->removeChild(healthText);
	scene->removeChild(shieldText);
	scene->removeChild(magicText);

	healthText->release();
	shieldText->release();
	magicText->release();

	std::string hT = String::createWithFormat("%d / %d", curH, maxH)->getCString();
	healthText = Label::createWithTTF(hT, "fonts/Marker Felt.ttf", 24);

	std::string sT = String::createWithFormat("%d / %d", curS, maxS)->getCString();
	shieldText = Label::createWithTTF(sT, "fonts/Marker Felt.ttf", 24);

	std::string mT = String::createWithFormat("%d / %d", curM, maxM)->getCString();
	magicText = Label::createWithTTF(mT, "fonts/Marker Felt.ttf", 24);

	healthImage->setScaleX(scaleH);
	shieldImage->setScaleX(scaleS);
	magicImage->setScaleX(scaleM);

	int moveX = hero->getMX();
	int moveY = hero->getMY();

	int iMX = moveX;
	int iMY = moveY;

	if (moveX != lastMX)
	{
		iMX = lastMX;
	}
	if (moveY != lastMY)
	{
		iMY = lastMY;
	}


	healthText->setPosition(Vec2(origin.x + 226 + addMoveX - iMX, visibleSize.height + origin.y - 50 + addMoveY - iMY));
	shieldText->setPosition(Vec2(origin.x + 226 + addMoveX - iMX, visibleSize.height + origin.y - 96 + addMoveY - iMY));
	magicText->setPosition(Vec2(origin.x + 226 + addMoveX - iMX, visibleSize.height + origin.y - 141 + addMoveY - iMY));

	addMoveX += moveX;
	addMoveY += moveY;

	lastMX = moveX;
	lastMY = moveY;

	ActionInterval* moveBy1 = MoveBy::create(0.01f, Vec2(moveX, moveY));
	ActionInterval* moveBy2 = MoveBy::create(0.01f, Vec2(moveX, moveY));
	ActionInterval* moveBy3 = MoveBy::create(0.01f, Vec2(moveX, moveY));
	ActionInterval* moveBy4 = MoveBy::create(0.01f, Vec2(moveX, moveY));
	
	mainBlood->runAction(moveBy1);
	healthImage->runAction(moveBy2);
	shieldImage->runAction(moveBy3);
	magicImage->runAction(moveBy4);

	scene->addChild(healthText, 22);
	scene->addChild(shieldText, 22);
	scene->addChild(magicText, 22);

}