#include "Hero1.h"
#include <vector>
USING_NS_CC;

Hero1::Hero1(int cx, int cy, int wID) :
	Hero(H1MH, H1MS, H1MM, H1MSP, cx, cy, wID)
{
	Sprite* tempSprite = Sprite::create("h10.png");

	SpriteFrame* frame = NULL;

	Vector<SpriteFrame*> array;

	for (int i = 0; i < H1AL; i++)
	{
		frame = SpriteFrame::create(String::createWithFormat("h1%d.png", i)->getCString(), CCRectMake(0, 0, 256, 256));

		array.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(array, 0.2f);
	animation->setLoops(-1);

	Animate* tempAnimate = Animate::create(animation);

	setS(tempSprite);
	setA(tempAnimate);

}

Hero1::~Hero1()
{
	Sprite* tempSprite = getS();

	Animate* tempAnimate = getA();

	tempSprite->release();
	tempAnimate->release();
}