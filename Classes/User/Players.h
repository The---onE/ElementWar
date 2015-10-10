#pragma once

#include "Global.h"
#include "Unit/PlayerUnit.h"

class Players : public Node
{
protected:
	Map<int, PlayerUnit*> allies;
	Map<int, PlayerUnit*> enemies;
	PlayerUnit* lead;
	PlayerUnit* aim;
	int leadIndex;
	int aimIndex;

public:
	CREATE_FUNC(Players);
	bool init();

	PlayerUnit* createPlayer(int i, int m, int w, int e, int wa, int f, int h);
	PlayerUnit* createAlly(int i, int m, int w, int e, int wa, int f, int h);
	PlayerUnit* createEnemy(int i, int m, int w, int e, int wa, int f, int h);

	PlayerUnit* findPlayer(int i);

	bool setLead(int i);
	bool setAim(int i);

	bool changeAttribute(int i, int m, int w, int e, int wa, int f);
	int getHealth(int i = DEFAULT);
	int getHealthMax(int i = DEFAULT);
	int changeHealth(int delta, int i = DEFAULT);

	int* getAttribute(int i = DEFAULT);
};