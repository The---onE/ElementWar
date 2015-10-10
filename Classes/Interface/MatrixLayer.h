#pragma once

#include "Global.h"
#include "Unit/ElementUnit.h"
#include "Data/MatrixData.h"

class MatrixLayer : public Layer
{
protected:
	ElementUnit* elements[MATRIX_LINE][MATRIX_ROW];
	Rect blocks[MATRIX_LINE][MATRIX_ROW];
	bool signFlag[MATRIX_LINE][MATRIX_ROW];
	Sprite* signSprite[MATRIX_LINE][MATRIX_ROW];

	DrawNode* brush;

	int elementCount[ELEMENT_COUNT];
	int removeCount[ELEMENT_COUNT];

	int touchLine, touchRow;

	int removeMethod;

	bool responseFlag;
	bool confirmFlag;
	bool ableFalg;

	//////////////////////////////////////////////////////////////////////////
	Sprite* typeSprite;
	bool changeFlag;
	//////////////////////////////////////////////////////////////////////////

public:
	CREATE_FUNC(MatrixLayer);
	bool init();
	void onEnter();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	void initBlocks();
	void clearElements();
	int createElement(int step, int line, int row);
	int removeElement(int line, int row);
	int removeElement();

	void allowResponse();
	void forbiddenResponse();
	bool checkConfirm();
	void responseConfirm();

	bool elementsFall();
	void rowFall(int row, int bottom);
	void appear(int row);
	int randStep();

	void initBrush();
	void drawGuideLine(Point leftBottom, Point rightTop);

	int signElement(int line, int row);

	void initSign();
	void signClear();
	void removeCountClear();
	bool touchRemove(int line, int row);
	bool metalRemove(int line, int row);
	bool woodRemove(int line, int row);
	bool earthRemove(int line, int row);
	bool waterRemove(int line, int row);
	bool fireRemove(int line, int row);

	int getRemoveMethod() { return removeMethod; }

	int* getRemoveCount();

	//////////////////////////////////////////////////////////////////////////
	void createButton(string normal, string selected);
	void fall(Ref* pSender); //退出游戏

	void createWoodButton(string normal, string selected);
	void wood(Ref* pSender); //退出游戏
	void createEarthButton(string normal, string selected);
	void earth(Ref* pSender); //退出游戏
	void createWaterButton(string normal, string selected);
	void water(Ref* pSender); //退出游戏
	void createFireButton(string normal, string selected);
	void fire(Ref* pSender); //退出游戏

	void change() { changeFlag = false; }
	bool isChanged() { return changeFlag; }
	//////////////////////////////////////////////////////////////////////////
};