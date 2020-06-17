#pragma once

#include <string>
#include "Enemy.h"
#include "Bullet.h"

class EnemyLR : public Enemy
{
public:

	EnemyLR(int mh, int msp, int ap, std::string path, int id, int sx, int sy, std::string bpath);

	~EnemyLR();

	void move(CCTMXTiledMap* map);

	void attack(Scene* scene, std::vector<Bullet*> &enemysBullets, int sceneID);

private:

	std::string bulletPath;

};