#pragma once

#include "cocos2d.h"
#include "Data.h"

USING_NS_CC;

class AddM
{
public:

	AddM(Scene* scene, int x, int y);

	~AddM();

	int getNumber();

	Sprite* getS();

private:

	int addNumber;

	Sprite* sprite;
};