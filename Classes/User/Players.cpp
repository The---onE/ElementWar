#include "Players.h"

bool Players::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		lead = NULL;

		bRet = true;
	} while (0);
	return bRet;
}

PlayerUnit* Players::createPlayer(int i, int m, int w, int e, int wa, int f, int h)
{
	PlayerUnit* p = PlayerUnit::create();
	p->setAttribute(i, m, w, e , wa, f);
	p->initHealth(h);
	this->addChild(p);

	return p;
}

PlayerUnit* Players::createAlly(int i, int m, int w, int e, int wa, int f, int h)
{
	PlayerUnit* p = createPlayer(i, m, w, e, wa, f, h);
	allies.insert(i, p);

	return p;
}

PlayerUnit* Players::createEnemy(int i, int m, int w, int e, int wa, int f, int h)
{
	PlayerUnit* p = createPlayer(i, m, w, e, wa, f, h);
	enemies.insert(i, p);

	return p;
}

PlayerUnit* Players::findPlayer(int i)
{
	PlayerUnit* p = allies.at(i);

	if (!p)
		p = enemies.at(i);

	if (!p)
		return NULL;

	return p;
}

bool Players::setLead(int i)
{
	PlayerUnit* p = findPlayer(i);
	if (!p)
		return false;

	lead = p;
	leadIndex = i;
	return true;
}

bool Players::setAim(int i)
{
	PlayerUnit* p = findPlayer(i);
	if (!p)
		return false;

	aim = p;
	aimIndex = i;
	return false;
}

bool Players::changeAttribute(int i, int m, int w, int e, int wa, int f)
{
	PlayerUnit* p = findPlayer(i);
	if (!p)
		return false;

	p->setAttribute(i, m, w, e, wa, f);
	return true;
}

int Players::getHealth(int i /* = DEFAULT */)
{
	PlayerUnit* p = findPlayer(i);
	if (i == DEFAULT)
		p = lead;
	if (!p)
		return -1;

	return p->getHealth();
}

int Players::getHealthMax(int i /* = DEFAULT */)
{
	PlayerUnit* p = findPlayer(i);
	if (i == DEFAULT)
		p = lead;
	if (!p)
		return -1;

	return p->getHealthMax();
}

int Players::changeHealth(int delta, int i /* = DEFAULT */)
{
	PlayerUnit* p = findPlayer(i);
	if (i == DEFAULT)
		p = lead;
	if (!p)
		return -1;

	return p->changeHealth(delta);
}

int* Players::getAttribute(int i /* = DEFAULT */)
{
	PlayerUnit* p = findPlayer(i);
	if (i == DEFAULT)
		p = lead;
	if (!p)
		return NULL;

	return p->getPlayerAttribute();
}