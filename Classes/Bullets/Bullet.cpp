#include "Bullet.h"

Bullet::Bullet(int d, int s, int xp, int yp, int dir, std::string spr):
	damage(d),
	speed(s),
	x(xp),
	y(yp),
	direction(dir)
{
	sprite = Sprite::create(spr);
}

Bullet::~Bullet()
{
	sprite->release();
}

Vec2 tileCoordForPosition(Vec2 position, CCTMXTiledMap* map)
{
	float x = position.x / map->getTileSize().width;

	float y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;

	return Vec2(x, y);
}