#include "EnemyLR.h"

EnemyLR::EnemyLR(int mh, int msp, int ap, std::string path, int id, int sx, int sy, std::string bpath) :
	Enemy(mh, msp, ap, path, id, sx, sy),
	bulletPath(bpath)
{}

EnemyLR::~EnemyLR()
{}

void EnemyLR::move(CCTMXTiledMap* map)
{
	int is_change = rand() % 20;
	
	if (is_change < 1)
	{
		setCD(rand() % 4 + 1);
	}

	int dx = 0;
	int dy = 0;

	if (getCD() == 1)
	{
		dy = 1;
	}
	else if (getCD() == 2)
	{
		dx = 1;
	}
	else if (getCD() == 3)
	{
		dy = -1;
	}
	else if (getCD() == 4)
	{
		dx = -1;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int realMX = (getMSP() / 60) * dx;
	int realMY = (getMSP() / 60) * dy;

	Vec2 tilePosition = tileCoordForPosition(Vec2(x + realMX, y + realMY), map);

	TMXLayer* wall = map->layerNamed("wall");

	auto tileGid = wall->tileGIDAt(tilePosition);

	if (tileGid)
	{
		return;
	}

	ActionInterval* moveBy = MoveBy::create(0.01f, Vec2(realMX, realMY));

	getS()->runAction(moveBy);

	x += realMX;
	y += realMY;
}


void EnemyLR::attack(Scene* scene, std::vector<Bullet*> &enemysBullets, int sceneID)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int cD = getCD();

	Bullet* bullet = new Bullet(getAP(), 500, x, y, cD, bulletPath);

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

	bullet->sprite->setPosition(Vec2(x + offestX, y + offestY));

	enemysBullets.push_back(bullet);

	scene->addChild(bullet->sprite, 11);
}