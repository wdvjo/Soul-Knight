#include "AddM.h"

AddM::AddM(Scene* scene, int x, int y)
{
	sprite = Sprite::create("addmagic.jpg");

	sprite->setPosition(Vec2(x, y));

	scene->addChild(sprite, 9);

	addNumber = AMN;
}

AddM::~AddM()
{
	sprite->release();
}

int AddM::getNumber()
{
	return addNumber;
}

Sprite* AddM::getS()
{
	return sprite;
}