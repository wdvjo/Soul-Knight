#pragma once

#include "cocos2d.h"
#include "Hero1.h"

USING_NS_CC;

class Blood
{
public:

	Blood(Scene* scene, Hero* hero);

	~Blood();

	void draw(Scene* scene, Hero* hero);

private:

	int addMoveX;
	int addMoveY;

	int lastMX;
	int lastMY;

	Sprite* mainBlood;

	Sprite* healthImage;
	Label* healthText;

	Sprite* shieldImage;
	Label* shieldText;

	Sprite* magicImage;
	Label* magicText;
};