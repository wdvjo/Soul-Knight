#ifndef __RISK_SCENE3_H__
#define __RISK_SCENE3_H__

#include "cocos2d.h"
#include <vector>
#include "Hero1.h"
#include "Bullet.h"
#include "Blood.h"
#include "AddH.h"
#include "AddM.h"
#include "Chest.h"
#include "SafeScene.h"

USING_NS_CC;


class RiskScene3 : public cocos2d::Scene
{
public:

	virtual bool init(int weaponID, int curH, int curS, int curM);

	void closeScene();

	static RiskScene3* create(int weaponID, int curH, int curS, int curM);

	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);

	virtual void update(float delta);

	void adjust();

	void getEnemysPoint(int SX, int SY);

	void moveBullets();

	void moveEnemys();

	void attackEnemys();

	void check();

	int nowTime;

	int addShieldTime;

	void addShield();

	Hero* getHero();

	void setHero(Hero* h);

	void next();

	int getID();

private:

	int startX;
	int startY;

	Hero* hero;

	CCTMXTiledMap* map;

	Blood* blood;

	Chest* chest;

	std::vector<Enemy*> enemysList;

	std::vector<Bullet*> enemyBullets;

	std::vector<Bullet*> playerBullets;

	std::vector<AddH*> AHList;

	std::vector<AddM*> AMList;
};

#endif // __HELLOWORLD_SCENE_H__
