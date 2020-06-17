#include "Chest.h"

Chest::Chest()
{
	int luck = random() % 10;

	if (luck == 0)
	{
		weaponID = 2;
	}
	else if (luck == 1 || luck == 2)
	{
		weaponID = 3;
	}
	else if (luck == 3 || luck == 4 || luck == 5)
	{
		weaponID = 4;
	}
	else if (luck == 6 || luck == 7 || luck == 8 || luck == 9)
	{
		weaponID = 1;
	}
}

Weapon* Chest::change(Scene* scene, int wID, int x, int y)
{
	Weapon* p;

	if (weaponID == 1)
	{
		p = new WC1(1);
	}
	else if (weaponID == 2)
	{
		p = new WC2(1);
	}
	else if (weaponID == 3)
	{
		p = new WL1(1);
	}
	else if (weaponID == 4)
	{
		p = new WL2(1);
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	p->getS()->setPosition(Vec2(x, y + 10));

	scene->addChild(p->getS(), 15);

	weaponID = wID;

	return p;
}