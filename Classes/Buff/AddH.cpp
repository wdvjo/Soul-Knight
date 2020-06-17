#include "AddH.h"

AddH::AddH(Scene* scene, int x, int y)
{
	sprite = Sprite::create("addhealth.jpg");

	sprite->setPosition(Vec2(x, y));

	scene->addChild(sprite, 9);

	addNumber = AHN;
}

AddH::~AddH()
{
	sprite->release();
}

int AddH::getNumber()
{
	return addNumber;
}

Sprite* AddH::getS()
{
	return sprite;
}