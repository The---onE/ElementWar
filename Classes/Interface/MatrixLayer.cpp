#include "MatrixLayer.h"

bool MatrixLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		ERGODIC_BLOCK(i, j)
		{
			elements[i][j] = NULL;
		}
		initBlocks();
		clearElements();
		initSign();
		removeCountClear();

		initBrush();

		removeMethod = CHAOS;
		drawGuideLine(getCenterByCoord(0, 0) - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2), getCenterByCoord(9, 9) + Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2));

		responseFlag = false;
		confirmFlag = false;
		ableFalg = false;

		//////////////////////////////////////////////////////////////////////////
		createButton("QuitNormal.png", "QuitSelected.png");

		createWoodButton("wood.png", "wood.png");
		createEarthButton("earth.png", "earth.png");
		createWaterButton("water.png", "water.png");
		createFireButton("fire.png", "fire.png");
		typeSprite = Sprite::create("chaos.png");
		typeSprite->setPosition(Point(WIDTH *0.05, HEIGHT*0.85));
		setSize(typeSprite, 0.2f);
		this->addChild(typeSprite);

		changeFlag = true;
		//////////////////////////////////////////////////////////////////////////

		bRet = true;
	} while (0);
	return bRet;
}


void MatrixLayer::onEnter()
{
	do
	{
		Layer::onEnter();

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(false);
		listener->onTouchBegan = CC_CALLBACK_2(MatrixLayer::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(MatrixLayer::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(MatrixLayer::onTouchEnded, this);
		listener->onTouchCancelled = CC_CALLBACK_2(MatrixLayer::onTouchEnded, this);

		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	} while (0);
}

bool MatrixLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (responseFlag)
	{
		Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());

		ERGODIC_BLOCK(i, j)
		{
			if (blocks[i][j].containsPoint(touchPoint))
			{
				//removeElement(i, j);
				touchLine = i;
				touchRow = j;
				return true;
			}
		}
	}
	
	return false;
}

void MatrixLayer::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void MatrixLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());

	ERGODIC_BLOCK(i, j)
	{
		if (blocks[i][j].containsPoint(touchPoint))
		{
			if (touchLine == i && touchRow == j)
			{
				switch (removeMethod)
				{
				case WOOD:
					ableFalg = woodRemove(i, j);
					break;
				case EARTH:
					ableFalg = earthRemove(i, j);
					break;
				case WATER:
					ableFalg = waterRemove(i, j);
					break;
				case FIRE:
					ableFalg = fireRemove(i, j);
					break;
				default:
					ableFalg = touchRemove(i, j);
					break;
				}
			}
		}
	}
}

void MatrixLayer::initBlocks()
{
	ERGODIC_BLOCK(i, j)
	{
		Point center = getCenterByCoord(i, j);
		Point corner = center - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2);
		blocks[i][j] = Rect(corner.x, corner.y, BLOCK_WIDTH, BLOCK_HEIGHT);
	}
}

void MatrixLayer::clearElements()
{
	ERGODIC_BLOCK(i, j)
	{
		removeElement(i, j);
	}
	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		elementCount[i] = 0;
	}
}

int MatrixLayer::createElement(int step, int line, int row)
{
	ElementUnit* &temp = elements[line][row];
	temp = ElementUnit::create();
	elementCount[step]++;
	temp->createElement(step, getCenterByCoord(line, row));

	return step;
}

int MatrixLayer::removeElement(int line, int row)
{
	ElementUnit* &temp = elements[line][row];
	if (!temp)
		return 0;
	int step = temp->getElementStep();
	elementCount[step]--;
	removeChild(temp);
	temp = NULL;
	signFlag[line][row];
	signSprite[line][row]->setVisible(false);
	return step;
}

int MatrixLayer::removeElement()
{
	int count = 0;
	ERGODIC_BLOCK(i, j)
	{
		if (signFlag[i][j])
		{
			removeCount[removeElement(i, j)]++;
			count++;
		}
	}
	signClear();
	ableFalg = false;
	return count;
}

void MatrixLayer::allowResponse()
{
	responseFlag = true;
}

void MatrixLayer::forbiddenResponse()
{
	responseFlag = false;
}

bool MatrixLayer::checkConfirm()
{
	return confirmFlag;
}

void MatrixLayer::responseConfirm()
{
	confirmFlag = false;
	removeElement();
}

bool MatrixLayer::elementsFall()
{
	bool flag = false;

	for (int j = 0; j < MATRIX_ROW; ++j)
	{
		for (int i = 0; i < MATRIX_LINE; ++i)
		{
			if (elements[i][j] == NULL)
			{
				rowFall(j, i);
				flag = true;
				break;
			}
		}
	}

	return flag;
}

void MatrixLayer::rowFall(int row, int bottom)
{
	for (int i = bottom; i < MATRIX_LINE - 1; ++i)
	{
		elements[i][row] = elements[i + 1][row];
		if (elements[i][row])
		{
			elements[i][row]->moveToPosition(getCenterByCoord(i, row), FALL_TIME);
		}
	}
	appear(row);
}

void MatrixLayer::appear(int row)
{
	int top = MATRIX_LINE - 1;

	int step = randStep();
	createElement(step, top, row);
	this->addChild(elements[top][row]);
	elements[top][row]->appear(FALL_TIME);
}

int MatrixLayer::randStep()
{
	int num[ELEMENT_COUNT];
	int max = 0;
	int min = 0x7FFFFFFF;
	for (int i = 1; i < ELEMENT_COUNT; ++i)
	{
		int temp = elementCount[i];
		if (temp > max)
			max = temp;
		if (temp < min)
			min = temp;
	}
	if (max-1 <= min)
		max++;
	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		num[i] = max - elementCount[i];
	}

	return randNum(ELEMENT_COUNT - 1, num + 1) + 1;
}

void MatrixLayer::initBrush()
{
	brush = DrawNode::create();
	this->addChild(brush);
}

void MatrixLayer::drawGuideLine(Point leftBottom, Point rightTop)
{
	brush->clear();
	Point leftTop = Point(leftBottom.x, rightTop.y);
	Point rightBottom = Point(rightTop.x, leftBottom.y);
	brush->drawSegment(leftBottom, leftTop, GUIDELINE_WIDTH, GUIDELINE_COLOR);
	brush->drawSegment(rightBottom, rightTop, GUIDELINE_WIDTH, GUIDELINE_COLOR);
	brush->drawSegment(leftBottom, rightBottom, GUIDELINE_WIDTH, GUIDELINE_COLOR);
	brush->drawSegment(leftTop, rightTop, GUIDELINE_WIDTH, GUIDELINE_COLOR);
}

int MatrixLayer::signElement(int line, int row)
{
	if (!elements[line][row])
		return -1;
	signFlag[line][row] = true;
	signSprite[line][row]->setVisible(true);

	return 0;
}

void MatrixLayer::initSign()
{
	ERGODIC_BLOCK(i, j)
	{
		signSprite[i][j] = Sprite::create(SIGN_IMG);
		signSprite[i][j]->setPosition(getCenterByCoord(i, j));
		setSize(signSprite[i][j], SIGN_SIZE);
		this->addChild(signSprite[i][j]);
	}

	signClear();
}

void MatrixLayer::signClear()
{
	ERGODIC_BLOCK(i, j)
	{
		signFlag[i][j] = false;
		signSprite[i][j]->setVisible(false);
	}
	ableFalg = false;
}

void MatrixLayer::removeCountClear()
{
	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		removeCount[i] = 0;
	}
}

bool MatrixLayer::touchRemove(int line, int row)
{
	signClear();
	removeCountClear();
	signElement(line, row);
	return true;
}

bool MatrixLayer::woodRemove(int line, int row)
{
	signClear();
	removeCountClear();
	if (line <= 0 || line >= MATRIX_LINE - 1)
		return false;
	if (row <= 0 || row >= MATRIX_ROW - 1)
		return false;

	for (int i = 0; i < MATRIX_LINE; ++i)
		signElement(i, row);
	for (int j = 0; j < MATRIX_ROW; ++j)
		signElement(line, j);

	signElement(line - 1, row - 1);
	signElement(line - 1, row + 1);
	signElement(line + 1, row - 1);
	signElement(line + 1, row + 1);

	return true;
}

bool MatrixLayer::earthRemove(int line, int row)
{
	signClear();
	removeCountClear();
	if (line <= 2 || line >= MATRIX_LINE - 3)
		return false;
	if (row <= 2 || row >= MATRIX_ROW - 3)
		return false;

	int count = 0;
	for (int i = line - 3; i < line; ++i)
	{
		for (int j = row - count; j <= row + count; ++j)
		{
			signElement(i, j);
		}
		count++;
	}
	count = 0;
	for (int i = line + 3; i >= line; --i)
	{
		for (int j = row - count; j <= row + count; ++j)
		{
			signElement(i, j);
		}
		count++;
	}

	return true;
}

bool MatrixLayer::waterRemove(int line, int row)
{
	signClear();
	removeCountClear();
	if (line <= 1 || line >= MATRIX_LINE - 2)
		return false;
	if (row <= 1 || row >= MATRIX_ROW - 2)
		return false;

	for (int i = line - 2; i <= line + 2; ++i)
	{
		for (int j = row - 2; j <= row + 2; ++j)
		{
			signElement(i, j);
		}
	}

	return true;
}

bool MatrixLayer::fireRemove(int line, int row)
{
	signClear();
	removeCountClear();
	if (line <= 2 || line >= MATRIX_LINE - 3)
		return false;
	if (row <= 2 || row >= MATRIX_ROW - 3)
		return false;

	for (int i = line - 3; i <= line + 3; ++i)
		signElement(i, row);
	for (int j = row - 3; j <= row + 3; ++j)
		signElement(line, j);

	for (int i = line - 3, j = 0; i <= line + 3; ++i, ++j)
		signElement(i, row + j - 3);
	for (int i = line - 3, j = 0; i <= line + 3; ++i, ++j)
		signElement(i, row - j + 3);

	return true;
}

int* MatrixLayer::getRemoveCount()
{
	int* count = new int[ELEMENT_COUNT];
	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		count[i] = removeCount[i];
	}
	return count;
}

//////////////////////////////////////////////////////////////////////////
void MatrixLayer::createButton(string normal, string selected)
{
	auto closeItem = MenuItemImage::create(normal, selected, CC_CALLBACK_1(MatrixLayer::fall, this));
	closeItem->setPosition(Point(visibleSize.width *0.8, 0));
	closeItem->setAnchorPoint(Point(0.5f, 0));
	setSize(closeItem, 0.15f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}

void MatrixLayer::fall(Ref* pSender)
{
	if (!ableFalg)
		return;
	confirmFlag = true;
}

void MatrixLayer::createWoodButton(string normal, string selected)
{
	auto closeItem = MenuItemImage::create(normal, selected, CC_CALLBACK_1(MatrixLayer::wood, this));
	closeItem->setPosition(Point(visibleSize.width *0.15, 0));
	closeItem->setAnchorPoint(Point(0.5f, 0));
	setSize(closeItem, 0.15f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}

void MatrixLayer::wood(Ref* pSender)
{
	if (removeMethod != WOOD)
	{
		removeMethod = WOOD;
		typeSprite->initWithFile(WOOD_IMG);
		changeFlag = true;
		drawGuideLine(getCenterByCoord(1, 1) - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2), getCenterByCoord(8, 8) + Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2));
	}
	else
	{
		removeMethod = CHAOS;
		typeSprite->initWithFile(CHAOS_IMG);
		changeFlag = true;
		drawGuideLine(getCenterByCoord(0, 0) - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2), getCenterByCoord(9, 9) + Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2));
	}
}

void MatrixLayer::createEarthButton(string normal, string selected)
{
	auto closeItem = MenuItemImage::create(normal, selected, CC_CALLBACK_1(MatrixLayer::earth, this));
	closeItem->setPosition(Point(visibleSize.width *0.25, 0));
	closeItem->setAnchorPoint(Point(0.5f, 0));
	setSize(closeItem, 0.15f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}

void MatrixLayer::earth(Ref* pSender)
{
	if (removeMethod != EARTH)
	{
		removeMethod = EARTH;
		typeSprite->initWithFile(EARTH_IMG);
		changeFlag = true;
		drawGuideLine(getCenterByCoord(3, 3) - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2), getCenterByCoord(6, 6) + Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2));
	}
	else
	{
		removeMethod = CHAOS;
		typeSprite->initWithFile(CHAOS_IMG);
		changeFlag = true;
		drawGuideLine(getCenterByCoord(0, 0) - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2), getCenterByCoord(9, 9) + Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2));
	}
}

void MatrixLayer::createWaterButton(string normal, string selected)
{
	auto closeItem = MenuItemImage::create(normal, selected, CC_CALLBACK_1(MatrixLayer::water, this));
	closeItem->setPosition(Point(visibleSize.width *0.35, 0));
	closeItem->setAnchorPoint(Point(0.5f, 0));
	setSize(closeItem, 0.15f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}

void MatrixLayer::water(Ref* pSender)
{
	if (removeMethod != WATER)
	{
		removeMethod = WATER;
		typeSprite->initWithFile(WATER_IMG);
		changeFlag = true;
		drawGuideLine(getCenterByCoord(2, 2) - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2), getCenterByCoord(7, 7) + Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2));
	}
	else
	{
		removeMethod = CHAOS;
		typeSprite->initWithFile(CHAOS_IMG);
		changeFlag = true;
		drawGuideLine(getCenterByCoord(0, 0) - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2), getCenterByCoord(9, 9) + Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2));
	}
}

void MatrixLayer::createFireButton(string normal, string selected)
{
	auto closeItem = MenuItemImage::create(normal, selected, CC_CALLBACK_1(MatrixLayer::fire, this));
	closeItem->setPosition(Point(visibleSize.width *0.45, 0));
	closeItem->setAnchorPoint(Point(0.5f, 0));
	setSize(closeItem, 0.15f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}

void MatrixLayer::fire(Ref* pSender)
{
	if (removeMethod != FIRE)
	{
		removeMethod = FIRE;
		typeSprite->initWithFile(FIRE_IMG);
		changeFlag = true;
		drawGuideLine(getCenterByCoord(3, 3) - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2), getCenterByCoord(6, 6) + Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2));
	}
	else
	{
		removeMethod = CHAOS;
		typeSprite->initWithFile(CHAOS_IMG);
		changeFlag = true;
		drawGuideLine(getCenterByCoord(0, 0) - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2), getCenterByCoord(9, 9) + Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2));
	}
}

//////////////////////////////////////////////////////////////////////////