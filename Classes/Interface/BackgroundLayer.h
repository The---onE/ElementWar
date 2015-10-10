#pragma once

#include "Global.h"
#include "Data/BackgroundData.h"

class BackgroundLayer : public Layer
{
protected:
	Sprite* bG; //±³¾°Í¼Æ¬

public:
	CREATE_FUNC(BackgroundLayer);
	bool init();
	float getBGHeight();
};