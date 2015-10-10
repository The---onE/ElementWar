#include "PlayerUnit.h"

bool PlayerUnit::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());


		bRet = true;
	} while (0);
	return bRet;
}

void PlayerUnit::setAttribute(int i, int m, int w, int e, int wa, int f)
{
	id = i;

	metal = m;
	wood = w;
	earth = e;
	water = wa;
	fire = f;
}

void PlayerUnit::initHealth(int h)
{
	health = h;
	healthMax = h;
}

int PlayerUnit::changeHealth(int delta)
{
	health += delta;
	if (delta < 0)
	{
		if (health < 0)
		{
			health = 0;
			return DIE;
		}
		else
			return HURT;
	}
	else
	{
		if (health > healthMax)
			health = healthMax;
		return RECOVER;
	}
}

int PlayerUnit::getHealth()
{
	return health;
}

int PlayerUnit::getHealthMax()
{
	return healthMax;
}

int* PlayerUnit::getPlayerAttribute()
{
	int* attr = new int[ELEMENT_COUNT];
	attr[METAL] = metal;
	attr[WOOD] = wood;
	attr[EARTH] = earth;
	attr[WATER] = water;
	attr[FIRE] = fire;

	return attr;
}