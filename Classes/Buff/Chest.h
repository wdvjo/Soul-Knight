#pragma once

#include "cocos2d.h"
#include "WL1.h"
#include "WL2.h"
#include "WC1.h"
#include "WC2.h"

USING_NS_CC;

class Chest
{
public:

	Chest();

	Weapon* change(Scene* scene, int wID, int x, int y);

private:

	int weaponID;
};