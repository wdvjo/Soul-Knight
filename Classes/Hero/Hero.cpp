#include "Hero.h"

USING_NS_CC;

Hero::Hero(int mh, int ms, int mm, int msp, int cx, int cy, int wID) :
	maxHealth(mh),
	curHealth(mh),
	maxShield(ms),
	curShield(ms),
	maxMagic(mm),
	curMagic(mm),
	moveSpeed(msp),
	moveX(0),
	moveY(0),
	curX(cx),
	curY(cy)
{
	curDirect = 0;

	if (wID == 1)
	{
		weapon1 = new WC1(1);
	}
	else if (wID == 2)
	{
		weapon1 = new WC2(1);
	}
	else if (wID == 3)
	{
		weapon1 = new WL1(1);
	}
	else if (wID == 4)
	{
		weapon1 = new WL2(1);
	}
	
	weapon2 = NULL;
}


Hero::~Hero()
{
	delete weapon1;
	delete weapon2;

	sprite->release();

	animate->release();
}

int Hero::getMH()
{
	return maxHealth;
}
int Hero::getCH()
{
	return curHealth;
}
void Hero::setCH(int ch)
{
	curHealth = ch;
}

int Hero::getMS()
{
	return maxShield;
}
int Hero::getCS()
{
	return curShield;
}
void Hero::setCS(int cs)
{
	curShield = cs;
}

int Hero::getMM()
{
	return maxMagic;
}
int Hero::getCM()
{
	return curMagic;
}
void Hero::setCM(int cm)
{
	curMagic = cm;
}

int Hero::getMSP()
{
	return moveSpeed;
}

int Hero::getMX()
{
	return moveX;
}
int Hero::getMY()
{
	return moveY;
}

Weapon* Hero::getW1()
{
	return weapon1;
}
void Hero::setW1(Weapon* weap)
{
	weapon1 = weap;
}

Weapon* Hero::getW2()
{
	return weapon2;
}
void Hero::setW2(Weapon* weap)
{
	weapon2 = weap;
}

int Hero::getCD()
{
	return curDirect;
}
void Hero::setCD(int cd)
{
	curDirect = cd;
}

Sprite* Hero::getS()
{
	return sprite;
}
void Hero::setS(Sprite* spr)
{
	sprite = spr;
}

Animate* Hero::getA()
{
	return animate;
}
void Hero::setA(Animate* ani)
{
	animate = ani;
}

void Hero::draw(Scene* scene)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	sprite->runAction(animate);

	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x + 80, visibleSize.height / 2 + origin.y - 46));
	scene->addChild(sprite, 10);
	
	Sprite* weaponSprite = weapon1->getS();

	weaponSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 10));
	scene->addChild(weaponSprite, 11);
}

void Hero::move(CCTMXTiledMap* map)
{
	moveX = 0;
	moveY = 0;

	int dx = 0;
	int dy = 0;

	if (curDirect == 1)
	{
		dy = 1;
		weapon1->setCD(1);
	}
	else if (curDirect == 2)
	{
		dx = 1;
		weapon1->setCD(2);
	}
	else if (curDirect == 3)
	{
		dy = -1;
		weapon1->setCD(3);
	}
	else if (curDirect == 4)
	{
		dx = -1;
		weapon1->setCD(4);
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int realMX = (moveSpeed / 60) * dx;
	int realMY = (moveSpeed / 60) * dy;

	Vec2 tilePosition = tileCoordForPosition(Vec2(curX + realMX, curY + realMY), map);

	auto wall = map->layerNamed("wall");

	auto tileGid = wall->tileGIDAt(tilePosition);

	if (tileGid)
	{
		return;
	}

	auto moveBy1 = MoveBy::create(0.01f, Vec2(realMX, realMY));

	sprite->runAction(moveBy1);

	Sprite* weaponSprite = weapon1->getS();

	auto moveBy2 = MoveBy::create(0.01f, Vec2(realMX, realMY));
	weaponSprite->runAction(moveBy2);
	weaponSprite->setRotation(90.0f * (weapon1->getCD() - 1));

	moveX = realMX;
	moveY = realMY;

	curX += moveX;
	curY += moveY;
}

void Hero::attack(Scene* scene, std::vector<Bullet*> &playerBullets, std::vector<Enemy*> &enemysList, int sceneID)
{
	int offestX;
	int offestY;

	if (sceneID == 1)
	{
		offestX = RS1OX;
		offestY = RS1OY;
	}
	else if (sceneID == 2)
	{
		offestX = RS2OX;
		offestY = RS2OY;
	}
	else if (sceneID == 3)
	{
		offestX = RS3OX;
		offestY = RS3OY;
	}

	int downMagic = weapon1->getMD();
	
	if (curMagic - downMagic < 0)
	{
		return;
	}

	curMagic -= downMagic;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int cD = weapon1->getCD();

	Bullet* bullet = new Bullet(weapon1->getAP(), weapon1->getARBS(), curX, curY, cD, weapon1->getBP());

	int weaponID = weapon1->getID();

	if (weaponID <= 2)
	{
		auto action = Blink::create(0.1f, 1);

		bullet->sprite->runAction(Sequence::create(action, CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet->sprite)), NULL));

		bullet->sprite->setRotation(90.0f * (cD - 1));

		if (cD == 1)
		{
			bullet->sprite->setPosition(Vec2(curX + offestX, curY + offestY + 50));
		}
		else if (cD == 2)
		{
			bullet->sprite->setPosition(Vec2(curX + offestX + 50, curY + offestY));
		}
		else if (cD == 3)
		{
			bullet->sprite->setPosition(Vec2(curX + offestX, curY + offestY - 50));
		}
		else if (cD == 4)
		{
			bullet->sprite->setPosition(Vec2(curX + offestX - 50, curY + offestY));
		}

		int enemysLen = enemysList.size();

		for (int i = 0; i < enemysLen; i++)
		{
			Enemy* eP = enemysList[i];

			if (eP == NULL)
			{
				continue;
			}

			Rect cr1 = eP->getS()->boundingBox();
			Rect cr2 = bullet->sprite->boundingBox();

			if (cr1.intersectsRect(cr2))
			{
				int damage = weapon1->getAP();

				eP->setCH(eP->getCH() - damage);
			}
		}
	}
	else
	{
		bullet->sprite->setPosition(Vec2(curX + offestX, curY + offestY));

		playerBullets.push_back(bullet);
	}

	scene->addChild(bullet->sprite, 11);
}
