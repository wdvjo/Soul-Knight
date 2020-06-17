#pragma once

#include "WL1.h"
#include "WL2.h"
#include "WC1.h"
#include "WC2.h"
#include "EC1.h"
#include "EC2.h"
#include "EL1.h"
#include "EL2.h"
#include "Boss.h"
#include "Data.h"
#include "Bullet.h"
#include "cocos2d.h"
USING_NS_CC;

class Hero
{
public:

	Hero(int mh, int ms, int mm, int msp, int cx, int cy, int wID);
	
	~Hero();

	friend class RiskScene1;

	int getMH();
	int getCH();
	void setCH(int ch);

	int getMS();
	int getCS();
	void setCS(int cs);

	int getMM();
	int getCM();
	void setCM(int cm);

	int getMSP();

	int getMX();
	int getMY();

	Weapon* getW1();
	void setW1(Weapon* weap);

	Weapon* getW2();
	void setW2(Weapon* weap);

	int getCD();
	void setCD(int cd);

	Sprite* getS();
	void setS(Sprite* spr);

	Animate* getA();
	void setA(Animate* ani);

	void draw(Scene* scene);

	void move(CCTMXTiledMap* map);

	void attack(Scene* scene, std::vector<Bullet*> &playerBullets,std::vector<Enemy*> &enemysList, int sceneID);

	int curX;
	int curY;

private:

	const int maxHealth;
	int curHealth;

	const int maxShield;
	int curShield;

	const int maxMagic;
	int curMagic;

	const int moveSpeed;

	int moveX;
	int moveY;

	int curDirect;

	Weapon* weapon1;
	Weapon* weapon2;

	Sprite* sprite;

	Animate* animate;
};
