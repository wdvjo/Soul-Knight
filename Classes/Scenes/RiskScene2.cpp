#include "RiskScene2.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include <string>

USING_NS_CC;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in RiskScene2.cpp\n");
}

// on "init" you need to initialize your instance
bool RiskScene2::init(int weaponID, int curH, int curS, int curM)
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Strength and Discipline.mp3", true);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	map = CCTMXTiledMap::create("map2.tmx");

	auto wall = map->layerNamed("wall");
	auto objects = map->objectGroupNamed("objects");

	wall->setVisible(false);

	auto startPoint = objects->getObject("player");

	startX = startPoint.at("x").asInt();
	startY = startPoint.at("y").asInt();

	getEnemysPoint(startX, startY);

	map->setPosition(Vec2(visibleSize.width / 2 + origin.x - startX, visibleSize.height / 2 + origin.y - startY));

	this->addChild(map, 0);

	hero = new Hero1(startX, startY, weaponID);

	hero->setCH(curH);
	hero->setCS(curS);
	hero->setCM(curM);

	hero->draw(this);

	blood = new Blood(this, hero);

	chest = new Chest();

	auto *dispatcher = Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();

	keyListener->onKeyPressed = CC_CALLBACK_2(RiskScene2::onKeyPressed, this);

	keyListener->onKeyReleased = CC_CALLBACK_2(RiskScene2::onKeyReleased, this);

	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	nowTime = 9999;

	addShieldTime = 300;

	this->scheduleUpdate();

	return true;
}

void RiskScene2::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event)
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
	else if (keycode == EventKeyboard::KeyCode::KEY_P) {

		CCScheduler *defaultScheduler = CCDirector::sharedDirector()->getScheduler();

		defaultScheduler->pauseTarget(this);

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_O) {

		CCScheduler *defaultScheduler = CCDirector::sharedDirector()->getScheduler();

		defaultScheduler->resumeTarget(this);

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE) {

		closeScene();

	}
	else if (keycode == EventKeyboard::KeyCode::KEY_SPACE && (nowTime > hero->getW1()->getAS())) {

		hero->attack(this, playerBullets, enemysList, 2);

		nowTime = 0;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_Q) {

		float curX = hero->curX;
		float curY = hero->curY;

		Vec2 tilePosition = tileCoordForPosition(Vec2(curX, curY), map);

		auto box = map->layerNamed("box");

		auto tileGid = box->tileGIDAt(tilePosition);

		if (tileGid == 0)
		{
			return;
		}

		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		Vec2 position = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) + Vec2(curX - startX, curY - startY);

		Weapon* weap1 = hero->getW1();
		int curWID = hero->getW1()->getID();
		Sprite* curWS = hero->getW1()->getS();

		hero->setW1(chest->change(this, curWID, position.x, position.y));

		this->removeChild(curWS);
		delete weap1;
	}
}
void RiskScene2::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event)
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
}

void RiskScene2::update(float delta)
{
	nowTime++;

	hero->move(map);

	addShield();

	moveBullets();

	moveEnemys();

	attackEnemys();

	check();

	blood->draw(this, hero);

	this->adjust();

	next();
}

void RiskScene2::adjust()
{
	int moveX = hero->getMX();
	int moveY = hero->getMY();

	auto moveBy = MoveBy::create(0.01f, Vec2(-moveX, -moveY));

	this->runAction(moveBy);
}

void RiskScene2::getEnemysPoint(int SX, int SY)
{
	if (map == NULL)
	{
		return;
	}

	auto objects = map->objectGroupNamed("objects");

	for (int i = 1; i <= 12; i++)
	{
		auto Point = objects->getObject(String::createWithFormat("e%d", i)->getCString());

		int X = Point.at("x").asInt();

		int Y = Point.at("y").asInt();

		Enemy* p;

		if (i % 4 == 0)
		{
			p = new EC1(X, Y);
		}
		else if (i % 4 == 1)
		{
			p = new EC2(X, Y);
		}
		else if (i % 4 == 2)
		{
			p = new EL1(X, Y);
		}
		else if (i % 4 == 3)
		{
			p = new EL2(X, Y);
		}

		p->draw(this, SX, SY);

		enemysList.push_back(p);
	}
}

void RiskScene2::moveBullets()
{
	for (auto iter = enemyBullets.begin(); iter != enemyBullets.end(); iter++)
	{
		Bullet* pB = *iter;

		if (pB != NULL)
		{
			int cD = pB->direction;

			int speed = pB->speed;

			Vec2 move;

			if (cD == 1)
			{
				move = Vec2(0, speed / 60);
			}
			else if (cD == 2)
			{
				move = Vec2(speed / 60, 0);
			}
			else if (cD == 3)
			{
				move = Vec2(0, -(speed / 60));
			}
			else if (cD == 4)
			{
				move = Vec2(-(speed / 60), 0);
			}

			Vec2 curPos = Vec2(pB->x, pB->y);

			Vec2 tilePosition = tileCoordForPosition(curPos, map);

			auto wall = map->layerNamed("wall");

			auto tileGid = wall->tileGIDAt(tilePosition);

			if (tileGid)
			{
				this->removeChild(pB->sprite);

				delete pB;

				*iter = NULL;

				continue;
			}

			ActionInterval* moveBy = MoveBy::create(0.01f, move);
			pB->sprite->runAction(moveBy);

			pB->x += move.x;
			pB->y += move.y;
		}
	}

	for (auto iter = playerBullets.begin(); iter != playerBullets.end(); iter++)
	{
		Bullet* pB = *iter;

		if (pB != NULL)
		{
			int cD = pB->direction;

			int speed = pB->speed;

			Vec2 move;

			if (cD == 1)
			{
				move = Vec2(0, speed / 60);
			}
			else if (cD == 2)
			{
				move = Vec2(speed / 60, 0);
			}
			else if (cD == 3)
			{
				move = Vec2(0, -(speed / 60));
			}
			else if (cD == 4)
			{
				move = Vec2(-(speed / 60), 0);
			}

			Vec2 curPos = Vec2(pB->x, pB->y);

			Vec2 tilePosition = tileCoordForPosition(curPos, map);

			auto wall = map->layerNamed("wall");

			auto tileGid = wall->tileGIDAt(tilePosition);

			if (tileGid)
			{
				this->removeChild(pB->sprite);

				delete pB;

				*iter = NULL;

				continue;
			}

			auto moveBy = MoveBy::create(0.01f, move);
			pB->sprite->runAction(moveBy);

			pB->x += move.x;
			pB->y += move.y;
		}
	}
}

void RiskScene2::moveEnemys()
{
	for (auto iter = enemysList.begin(); iter != enemysList.end(); iter++)
	{
		Enemy* eP = *iter;

		if (eP == NULL)
		{
			continue;
		}

		eP->move(map);
	}
}

void RiskScene2::attackEnemys()
{
	for (auto iter = enemysList.begin(); iter != enemysList.end(); iter++)
	{
		Enemy* eP = *iter;

		if (eP == NULL)
		{
			continue;
		}

		int is_attack = rand() % 60;

		if (is_attack == 0)
		{
			eP->attack(this, enemyBullets, 2);
		}

	}
}

void RiskScene2::check()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (auto iter1 = enemysList.begin(); iter1 != enemysList.end(); iter1++)
	{
		Enemy* eP = *iter1;

		if (eP == NULL)
		{
			continue;
		}

		Rect cr1 = eP->getS()->boundingBox();
		Rect cr2 = hero->getS()->boundingBox();

		float LTX = cr2.getMinX();
		float LTY = cr2.getMaxY();

		float LBX = LTX;
		float LBY = LTY - 96;

		cr2.setRect(LBX, LBY, 96.0f, 96.0f);

		if (cr1.intersectsRect(cr2))
		{
			int damage = eP->getAP();

			this->removeChild(eP->getS());

			*iter1 = NULL;

			delete eP;

			int curH = hero->getCH();
			int curS = hero->getCS();


			if (curS >= damage)
			{
				hero->setCS(curS - damage);
			}
			else
			{
				damage -= curS;

				hero->setCS(0);
				hero->setCH(curH - damage);
			}

			continue;
		}

		for (auto iter2 = playerBullets.begin(); iter2 != playerBullets.end(); iter2++)
		{
			Bullet* eB = *iter2;

			if (eB == NULL)
			{
				continue;
			}

			Rect cr3 = eB->sprite->boundingBox();

			if (cr1.intersectsRect(cr3))
			{
				int damage = eB->damage;

				eP->setCH(eP->getCH() - damage);

				this->removeChild(eB->sprite);

				*iter2 = NULL;

				delete eB;
			}
		}
	}

	for (auto iter = enemyBullets.begin(); iter != enemyBullets.end(); iter++)
	{
		Bullet* eB = *iter;

		if (eB == NULL)
		{
			continue;
		}

		Rect cr1 = eB->sprite->boundingBox();
		Rect cr2 = hero->getS()->boundingBox();

		float LTX = cr2.getMinX();
		float LTY = cr2.getMaxY();

		float LBX = LTX;
		float LBY = LTY - 96;

		cr2.setRect(LBX, LBY, 96.0f, 96.0f);

		if (cr1.intersectsRect(cr2))
		{
			int damage = eB->damage;

			int curH = hero->getCH();
			int curS = hero->getCS();


			if (curS >= damage)
			{
				hero->setCS(curS - damage);
			}
			else
			{
				damage -= curS;

				hero->setCS(0);
				hero->setCH(curH - damage);
			}

			this->removeChild(eB->sprite);

			*iter = NULL;

			delete eB;
		}
	}

	for (auto iter = enemysList.begin(); iter != enemysList.end(); iter++)
	{
		Enemy* eP = *iter;

		if (eP != NULL)
		{
			if (eP->getCH() <= 0)
			{
				int luck = random() % 10;
				int x = eP->x;
				int y = eP->y;

				Vec2 position = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) + Vec2(x - startX, y - startY);

				if (luck == 0)
				{
					AddH* ah = new AddH(this, position.x, position.y);

					AHList.push_back(ah);
				}
				else if (luck == 1 || luck == 2)
				{
					AddM* am = new AddM(this, position.x, position.y);

					AMList.push_back(am);
				}

				this->removeChild(eP->getS());

				*iter = NULL;

				delete eP;
			}
		}
	}

	for (auto iter = AHList.begin(); iter != AHList.end(); iter++)
	{
		AddH* eAH = *iter;

		if (eAH == NULL)
		{
			continue;
		}

		Rect cr1 = eAH->getS()->boundingBox();
		Rect cr2 = hero->getS()->boundingBox();

		float LTX = cr2.getMinX();
		float LTY = cr2.getMaxY();

		float LBX = LTX;
		float LBY = LTY - 96;

		cr2.setRect(LBX, LBY, 96.0f, 96.0f);

		if (cr1.intersectsRect(cr2))
		{
			int add = eAH->getNumber();

			int curH = hero->getCH();
			int maxH = hero->getMH();

			if (curH + add <= maxH)
			{
				hero->setCH(curH + add);
			}
			else
			{
				hero->setCH(maxH);
			}

			this->removeChild(eAH->getS());

			*iter = NULL;

			delete eAH;
		}
	}

	for (auto iter = AMList.begin(); iter != AMList.end(); iter++)
	{
		AddM* eAM = *iter;

		if (eAM == NULL)
		{
			continue;
		}

		Rect cr1 = eAM->getS()->boundingBox();
		Rect cr2 = hero->getS()->boundingBox();

		float LTX = cr2.getMinX();
		float LTY = cr2.getMaxY();

		float LBX = LTX;
		float LBY = LTY - 96;

		cr2.setRect(LBX, LBY, 96.0f, 96.0f);

		if (cr1.intersectsRect(cr2))
		{
			int add = eAM->getNumber();

			int curM = hero->getCM();
			int maxM = hero->getMM();

			if (curM + add <= maxM)
			{
				hero->setCM(curM + add);
			}
			else
			{
				hero->setCM(maxM);
			}

			this->removeChild(eAM->getS());

			*iter = NULL;

			delete eAM;
		}
	}

	if (hero->getCH() <= 0)
	{
		closeScene();
	}

}

void RiskScene2::addShield()
{
	int curS = hero->getCS();
	int maxS = hero->getMS();

	if (curS < maxS)
	{
		addShieldTime--;

		if (addShieldTime == 0)
		{
			hero->setCS(curS + 1);

			addShieldTime = 300;
		}
	}
}

Hero* RiskScene2::getHero()
{
	return hero;
}

void RiskScene2::setHero(Hero* h)
{
	hero = h;
}

void RiskScene2::next()
{
	float curX = hero->curX;
	float curY = hero->curY;

	Vec2 tilePosition = tileCoordForPosition(Vec2(curX, curY), map);

	TMXLayer* next = map->layerNamed("next");

	auto tileGid = next->tileGIDAt(tilePosition);

	if (tileGid != 0)
	{
		auto nextScene = RiskScene3::create(hero->getW1()->getID(), hero->getCH(), hero->getCS(), hero->getCM());

		Director::getInstance()->replaceScene(nextScene);
	}
}

void RiskScene2::closeScene()
{
	auto scene = SafeScene::create();

	Director::getInstance()->replaceScene(scene);
}

RiskScene2* RiskScene2::create(int weaponID, int curH, int curS, int curM)
{
	RiskScene2 *pScene = new RiskScene2;

	if (pScene && pScene->init(weaponID, curH, curS, curM))
	{
		pScene->autorelease();

		return pScene;
	}
	else
	{
		delete pScene;
		pScene = nullptr;
		return nullptr;
	}
}

int RiskScene2::getID()
{
	return 2;
}