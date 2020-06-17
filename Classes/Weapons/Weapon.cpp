#include "Weapon.h"

Weapon::Weapon(int ap, int as, int md, int cd, std::string path, int id, std::string bpath) :
	attackPower(ap),
	attackSpeed(as),
	magicDown(md),
	curDirect(cd),
	bulletPath(bpath),
	ID(id)
{
	sprite = Sprite::create(path);
}

Weapon::~Weapon()
{
	sprite->release();
}

int Weapon::getAP()
{
	return attackPower;
}

int Weapon::getAS()
{
	return attackSpeed;
}

int Weapon::getMD()
{
	return magicDown;
}

int Weapon::getCD()
{
	return curDirect;
}

void Weapon::setCD(int dir)
{
	curDirect = dir;
}

Sprite* Weapon::getS()
{
	return sprite;
}

std::string Weapon::getBP()
{
	return bulletPath;
}

int Weapon::getID()
{
	return ID;
}