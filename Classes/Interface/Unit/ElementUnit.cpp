#include "ElementUnit.h"

bool ElementUnit::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());


		bRet = true;
	} while (0);
	return bRet;
}

void ElementUnit::createElement(int ele, Point pos)
{
	elementStep = ele;
	switch (ele)
	{
	case METAL:
		elementSprite = Sprite::create(METAL_IMG);
		break;
	case WOOD:
		elementSprite = Sprite::create(WOOD_IMG);
		break;
	case EARTH:
		elementSprite = Sprite::create(EARTH_IMG);
		break;
	case WATER:
		elementSprite = Sprite::create(WATER_IMG);
		break;
	case FIRE:
		elementSprite = Sprite::create(FIRE_IMG);
		break;
	default:
		elementSprite = Sprite::create(CHAOS_IMG);
		elementStep = CHAOS;
		break;
	}
	elementSprite->setPosition(Point::ZERO);
	this->setPosition(pos);
	setSize(elementSprite, BALL_SIZE);
	this->addChild(elementSprite);
}

void ElementUnit::moveToPosition(Point pos)
{
	this->setPosition(pos);
}

void ElementUnit::moveToPosition(Point pos, float time)
{
	this->stopAllActions();
	Action* move = MoveTo::create(time, pos);
	this->runAction(move);
}

void ElementUnit::appear(float time)
{
	elementSprite->setScale(0);
	float sc = DATUM* BALL_SIZE / elementSprite->getContentSize().height;
	Action* scale = ScaleTo::create(time, sc);
	elementSprite->runAction(scale);
}

int ElementUnit::getElementStep()
{
	return elementStep;
}