#pragma once

#include "cocos2d.h"
#include "Data.h"

USING_NS_CC;

class AddH
{
public:

	AddH(Scene* scene, int x, int y);

	~AddH();

	int getNumber();

	Sprite* getS();

private:

	int addNumber;

	Sprite* sprite;
};