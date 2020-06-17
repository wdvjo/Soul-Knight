#pragma once

#include "cocos2d.h"
#include "Bullet.h"
#include "Data.h"

USING_NS_CC;

class Enemy
{
public:

	Enemy(int mh, int msp, int ap, std::string path, int id, int sx, int sy);

	~Enemy();

	int getMH();
	int getCH();
	void setCH(int heal);

	int getMSP();

	int getAP();

	int getCD();
	void setCD(int dir);

	Sprite* getS();

	int getID();

	virtual void move(CCTMXTiledMap* map) = 0;
	virtual void attack(Scene* scene, std::vector<Bullet*> &enemysBullets, int sceneID) = 0;

	void draw(Scene* scene, int SX, int SY);

	int x;
	int y;

private:

	const int maxHealth;
	int curHealth;

	const int moveSpeed;

	const int attackPower;

	int curDirect;

	Sprite* sprite;

	const int ID;
};
