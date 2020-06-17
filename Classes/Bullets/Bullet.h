#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Bullet
{
public:

	int damage;

	int speed;

	int x;

	int y;

	int direction;

	Sprite* sprite;

	Bullet(int d, int s, int xp, int yp, int dir, std::string spr);

	~Bullet();

private:

};

Vec2 tileCoordForPosition(Vec2 position, CCTMXTiledMap* map);