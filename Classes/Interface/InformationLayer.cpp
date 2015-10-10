#include "InformationLayer.h"

bool InformationLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		createSprite();
		createAimSprite();

		int* initCount = new int[ELEMENT_COUNT];
		int* initAttr = new int[ELEMENT_COUNT];
		for (int i = 0; i < ELEMENT_COUNT; ++i)
		{
			initCount[i] = 0;
			initAttr[i] = 0;
		}
		createLabel(initCount, initAttr);

		int* initAttrA = new int[ELEMENT_COUNT];
		for (int i = 0; i < ELEMENT_COUNT; ++i)
		{
			initAttrA[i] = 0;
		}
		createAimLabel(initAttrA);

		createHealth(1, 1);
		createEnemyHealth(1, 1);

		bRet = true;
	} while (0);
	return bRet;
}

void InformationLayer::createSprite()
{
	createSprite(metalSprite, METAL_SPRITE_IMG, METAL_SPRITE_POSITION);
	createSprite(woodSprite, WOOD_SPRITE_IMG, WOOD_SPRITE_POSITION);
	createSprite(earthSprite, EARTH_SPRITE_IMG, EARTH_SPRITE_POSITION);
	createSprite(waterSprite, WATER_SPRITE_IMG, WATER_SPRITE_POSITION);
	createSprite(fireSprite, FIRE_SPRITE_IMG, FIRE_SPRITE_POSITION);
}

void InformationLayer::createSprite(Sprite* &sprite, string img, Point pos)
{
	sprite = Sprite::create(img);
	sprite->setPosition(pos);
	setSize(sprite, SPRITE_SIZE);
	this->addChild(sprite);
}

void InformationLayer::createLabel(int* count, int* attr)
{
	this->removeChild(metalLabel);
	this->removeChild(woodLabel);
	this->removeChild(earthLabel);
	this->removeChild(waterLabel);
	this->removeChild(fireLabel);

	createLabel(metalLabel, count[METAL], attr[METAL], METAL_COLOR, METAL_INFORMATION_POSITION);
	createLabel(woodLabel, count[WOOD], attr[WOOD], WOOD_COLOR, WOOD_INFORMATION_POSITION);
	createLabel(earthLabel, count[EARTH], attr[EARTH], EARTH_COLOR, EARTH_INFORMATION_POSITION);
	createLabel(waterLabel, count[WATER], attr[WATER], WATER_COLOR, WATER_INFORMATION_POSITION);
	createLabel(fireLabel, count[FIRE], attr[FIRE], FIRE_COLOR, FIRE_INFORMATION_POSITION);

	delete[] count;
	delete[] attr;
}

void InformationLayer::createLabel(Label* &label, int count, int attr, Color3B color, Point pos)
{
	char text[32];
	sprintf(text, "%d * %d = %d", attr, count, count * attr);
	label = Label::createWithTTF(text, INFORMATION_FONT, INFORMATION_FONTSIZE);
	label->setColor(color);
	label->setAnchorPoint(Point(0, 0.5));
	label->setPosition(pos);
	setSize(label, INFORMATION_SIZE);
	this->addChild(label);
}


void InformationLayer::createAimSprite()
{
	createSprite(metalAimSprite, METAL_SPRITE_IMG, METAL_SPRITE_POSITION + Point(0.7*WIDTH, 0));
	createSprite(woodAimSprite, WOOD_SPRITE_IMG, WOOD_SPRITE_POSITION + Point(0.7*WIDTH, 0));
	createSprite(earthAimSprite, EARTH_SPRITE_IMG, EARTH_SPRITE_POSITION + Point(0.7*WIDTH, 0));
	createSprite(waterAimSprite, WATER_SPRITE_IMG, WATER_SPRITE_POSITION + Point(0.7*WIDTH, 0));
	createSprite(fireAimSprite, FIRE_SPRITE_IMG, FIRE_SPRITE_POSITION + Point(0.7*WIDTH, 0));
}

void InformationLayer::createAimLabel(int* attr)
{
	this->removeChild(metalAimLabel);
	this->removeChild(woodAimLabel);
	this->removeChild(earthAimLabel);
	this->removeChild(waterAimLabel);
	this->removeChild(fireAimLabel);

	createAimLabel(metalAimLabel, attr[METAL], METAL_COLOR, METAL_INFORMATION_POSITION + Point(0.7*WIDTH, 0));
	createAimLabel(woodAimLabel, attr[WOOD], WOOD_COLOR, WOOD_INFORMATION_POSITION + Point(0.7*WIDTH, 0));
	createAimLabel(earthAimLabel, attr[EARTH], EARTH_COLOR, EARTH_INFORMATION_POSITION + Point(0.7*WIDTH, 0));
	createAimLabel(waterAimLabel, attr[WATER], WATER_COLOR, WATER_INFORMATION_POSITION + Point(0.7*WIDTH, 0));
	createAimLabel(fireAimLabel, attr[FIRE], FIRE_COLOR, FIRE_INFORMATION_POSITION + Point(0.7*WIDTH, 0));

	delete[] attr;
}

void InformationLayer::createAimLabel(Label* &label, int attr, Color3B color, Point pos)
{
	char text[32];
	sprintf(text, "%d", attr);
	label = Label::createWithTTF(text, INFORMATION_FONT, INFORMATION_FONTSIZE);
	label->setColor(color);
	label->setAnchorPoint(Point(0, 0.5));
	label->setPosition(pos);
	setSize(label, INFORMATION_SIZE);
	this->addChild(label);
}


void InformationLayer::createHealth(int health, int healthMax)
{
	char text[32];
	sprintf(text, "%d/%d", health, healthMax);
	healthLabel = Label::createWithTTF(text, INFORMATION_FONT, INFORMATION_FONTSIZE);
	healthLabel->setColor(HEALTH_COLOR);
	healthLabel->setAnchorPoint(Point(0.5, 1));
	healthLabel->setPosition(HEALTH_POSITION);
	setSize(healthLabel, INFORMATION_SIZE);
	this->addChild(healthLabel);

	healthSprite = Sprite::create(HEALTH_IMG);
	healthSprite->setAnchorPoint(Point(0, 1));
	healthSprite->setPosition(Point(0, HEIGHT));
	setSize(healthSprite, HEALTH_SIZE);
	healthScaleBase = WIDTH*0.5 / healthSprite->getContentSize().width;
	healthSprite->setScaleX(healthScaleBase*health / healthMax);
	this->addChild(healthSprite, -1);
}

void InformationLayer::createEnemyHealth(int health, int healthMax)
{
	char text[32];
	sprintf(text, "%d/%d", health, healthMax);
	enemyHealthLabel = Label::createWithTTF(text, INFORMATION_FONT, INFORMATION_FONTSIZE);
	enemyHealthLabel->setColor(ENELM_HEALTH_COLOR);
	enemyHealthLabel->setAnchorPoint(Point(0.5, 1));
	enemyHealthLabel->setPosition(ENEMY_HEALTH_POSITION);
	setSize(enemyHealthLabel, INFORMATION_SIZE);
	this->addChild(enemyHealthLabel);

	enemyHealthSprite = Sprite::create(ENEMY_HEALTH_IMG);
	enemyHealthSprite->setAnchorPoint(Point(1, 1));
	enemyHealthSprite->setPosition(Point(WIDTH, HEIGHT));
	setSize(enemyHealthSprite, HEALTH_SIZE);
	enemyHealthScaleBase = WIDTH*0.5 / enemyHealthSprite->getContentSize().width;
	enemyHealthSprite->setScaleX(enemyHealthScaleBase*health / healthMax);
	this->addChild(enemyHealthSprite, -1);
}

void InformationLayer::changeHealth(int health, int healthMax)
{
	this->removeChild(healthLabel);
	char text[32];
	sprintf(text, "%d/%d", health, healthMax);
	healthLabel = Label::createWithTTF(text, INFORMATION_FONT, INFORMATION_FONTSIZE);
	healthLabel->setColor(HEALTH_COLOR);
	healthLabel->setAnchorPoint(Point(0.5, 1));
	healthLabel->setPosition(HEALTH_POSITION);
	setSize(healthLabel, INFORMATION_SIZE);
	this->addChild(healthLabel);

	healthSprite->setScaleX(healthScaleBase*health / healthMax);
}

void InformationLayer::changeEnemyHealth(int health, int healthMax)
{
	this->removeChild(enemyHealthLabel);
	char text[32];
	sprintf(text, "%d/%d", health, healthMax);
	enemyHealthLabel = Label::createWithTTF(text, INFORMATION_FONT, INFORMATION_FONTSIZE);
	enemyHealthLabel->setColor(ENELM_HEALTH_COLOR);
	enemyHealthLabel->setAnchorPoint(Point(0.5, 1));
	enemyHealthLabel->setPosition(ENEMY_HEALTH_POSITION);
	setSize(enemyHealthLabel, INFORMATION_SIZE);
	this->addChild(enemyHealthLabel);

	enemyHealthSprite->setScaleX(enemyHealthScaleBase*health / healthMax);
}