#pragma once

#include "Global.h"
#include "Data/ElementData.h"
#include "Data/PlayerData.h"

class PlayerUnit : public Node
{
protected:
	int id;

	int metal;
	int wood;
	int earth;
	int water;
	int fire;
	int health;
	int healthMax;

public:
	CREATE_FUNC(PlayerUnit);
	bool init();

	void setAttribute(int i, int m, int w, int e, int wa, int f);
	void initHealth(int h);
	int changeHealth(int delta);
	int getHealth();
	int getHealthMax();
	int* getPlayerAttribute();
};