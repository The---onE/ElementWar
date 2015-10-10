#pragma once

#include "Global.h"
#include "Data/InformationData.h"
#include "Data/ElementData.h"

class InformationLayer : public Layer
{
protected:
	Sprite* metalSprite;
	Sprite* woodSprite;
	Sprite* earthSprite;
	Sprite* waterSprite;
	Sprite* fireSprite;

	Label* metalLabel;
	Label* woodLabel;
	Label* earthLabel;
	Label* waterLabel;
	Label* fireLabel;

	Sprite* metalAimSprite;
	Sprite* woodAimSprite;
	Sprite* earthAimSprite;
	Sprite* waterAimSprite;
	Sprite* fireAimSprite;

	Label* metalAimLabel;
	Label* woodAimLabel;
	Label* earthAimLabel;
	Label* waterAimLabel;
	Label* fireAimLabel;

	Sprite* healthSprite;
	Sprite* enemyHealthSprite;
	Label* healthLabel;
	Label* enemyHealthLabel;
	float healthScaleBase;
	float enemyHealthScaleBase;

	void createHealth(int health, int healthMax);
	void createEnemyHealth(int health, int healthMax);

public:
	CREATE_FUNC(InformationLayer);
	bool init();

	void createSprite();
	void createSprite(Sprite* &sprite, string img, Point pos);
	void createLabel(int* count, int* attr);
	void createLabel(Label* &label, int count, int attr, Color3B color, Point pos);

	void createAimSprite();
	void createAimLabel(int* attr);
	void createAimLabel(Label* &label, int attr, Color3B color, Point pos);

	void changeHealth(int health, int healthMax);
	void changeEnemyHealth(int health, int healthMax);
};