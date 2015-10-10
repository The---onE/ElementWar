#pragma once

#include "Global.h"
#include "Data/ElementData.h"

class ElementUnit : public Node
{
protected:
	Sprite* elementSprite;
	int elementStep;
public:
	CREATE_FUNC(ElementUnit);
	bool init();

	void createElement(int ele, Point pos);
	void moveToPosition(Point pos);
	void moveToPosition(Point pos, float time);
	void appear(float time);

	int getElementStep();
};