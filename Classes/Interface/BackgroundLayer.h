#pragma once

#include "Global.h"
#include "Data/BackgroundData.h"

class BackgroundLayer : public Layer
{
protected:
	Sprite* bG; //����ͼƬ

public:
	CREATE_FUNC(BackgroundLayer);
	bool init();
	float getBGHeight();
};