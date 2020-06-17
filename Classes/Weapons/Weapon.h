#pragma once

#include "cocos2d.h"
#include "string"
#include "Data.h"

USING_NS_CC;

class Weapon
{
public:

	Weapon(int ap, int as, int md, int cd, std::string path, int id, std::string bpath);

	~Weapon();

	int getAP();

	int getAS();

	int getMD();

	int getCD();
	void setCD(int dir);

	virtual int getARBS() = 0;

	Sprite* getS();

	std::string getBP();

	int getID();

private:

	const int attackPower;

	const int attackSpeed;

	const int magicDown;

	int curDirect;

	Sprite* sprite;

	std::string bulletPath;

	const int ID;
};