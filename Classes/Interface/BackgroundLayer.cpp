#include "BackgroundLayer.h"

bool BackgroundLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		bG = Sprite::create(BACKGROUND_IMG);
		bG->setPosition(BACKGROUND_POSITION);
		setSize(bG, BACKGROUND_SIZE);
		this->addChild(bG);

		bRet = true;
	} while (0);
	return bRet;
}

float BackgroundLayer::getBGHeight()
{
	return bG->getContentSize().height;
}