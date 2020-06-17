
#include "EnemyCC.h"

EnemyCC::EnemyCC(int mh, int msp, int ap, std::string path, int id, int sx, int sy):
	Enemy(mh, msp, ap, path, id, sx, sy)
{}

EnemyCC::~EnemyCC()
{}

void EnemyCC::move(CCTMXTiledMap* map)
{
	int is_change = rand() % 10;

	if (is_change > 8)
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

void EnemyCC::attack(Scene* scene, std::vector<Bullet*> &enemysBullets, int sceneID)
{}