#include "Enemy.h"

Enemy::Enemy(int mh, int msp, int ap, std::string path, int id, int sx, int sy):
	maxHealth(mh),
	curHealth(mh),
	moveSpeed(msp),
	attackPower(ap),
	curDirect(4),
	ID(id),
	x(sx),
	y(sy)
{
	sprite = Sprite::create(path);
}

Enemy::~Enemy()
{
	sprite->release();
}

int Enemy::getMH()
{
	return maxHealth;
}
int Enemy::getCH()
{
	return curHealth;
}
void Enemy::setCH(int heal)
{
	curHealth = heal;
}

int Enemy::getMSP()
{
	return moveSpeed;
}

int Enemy::getAP()
{
	return attackPower;
}

int Enemy::getCD()
{
	return curDirect;
}
void Enemy::setCD(int dir)
{
	curDirect = dir;
}

Sprite* Enemy::getS()
{
	return sprite;
}

int Enemy::getID()
{
	return ID;
}

void Enemy::draw(Scene* scene, int SX, int SY)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 position = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) + Vec2(x - SX, y - SY);

	sprite->setPosition(position);

	scene->addChild(sprite, 10);
}