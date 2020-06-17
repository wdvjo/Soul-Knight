#pragma once

#include "Enemy.h"

class EnemyCC : public Enemy
{
public:

	EnemyCC(int mh, int msp, int ap, std::string path, int id, int sx, int sy);

	~EnemyCC();

	void move(CCTMXTiledMap* map);

	void attack(Scene* scene, std::vector<Bullet*> &enemysBullets, int sceneID);

private:

};
