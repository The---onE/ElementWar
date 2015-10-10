#include "GameScene.h"
#include "State/StateList.h"

bool GameScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::init());

		createQuitButton("QuitNormal.png", "QuitSelected.png");
		
		stateMachine = StateMachine::createWithGameScene(this);
		stateMachine->changeState(StartState::create(this));

		this->scheduleUpdate();

		initBackground();
		initMatrix();
		initInformation();

		initPlayers();

		//////////////////////////////////////////////////////////////////////////
		players->createAlly(LEAD, 1, 1, 1, 1, 1, 500);
		players->setLead(LEAD);
		players->createEnemy(AIM, 80, 80, 80, 80, 80, 500);
		players->setAim(AIM);
		//////////////////////////////////////////////////////////////////////////

		//auto rootNode = CSLoader::createNode("MainScene.csb");
		//addChild(rootNode);

		bRet = true;
	} while (0);
	return bRet;
}

StateMachine* GameScene::getStateMachine()
{
	return stateMachine;
}

void GameScene::update(float dt)
{
	stateMachine->update(dt);
}

void GameScene::initBackground()
{
	bg = BackgroundLayer::create();
	this->addChild(bg);
}

void GameScene::initMatrix()
{
	matrix = MatrixLayer::create();
	this->addChild(matrix);
}

void GameScene::initInformation()
{
	information = InformationLayer::create();
	this->addChild(information);
}

void GameScene::initPlayers()
{
	players = Players::create();
	this->addChild(players);
}

int GameScene::attack(int att, int def, int aim)
{
	int delta = att - def;
	if (delta < 0)
		delta = 0;
	return players->changeHealth(-delta, aim);
}

int GameScene::cure(int cur, int aim)
{
	return players->changeHealth(cur, aim);
}

//////////////////////////////////////////////////////////////////////////
int GameScene::processInjure()
{
	int* l = players->getAttribute(LEAD);
	int* r = matrix->getRemoveCount();
	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		l[i] *= r[i];
	}
	int* e = players->getAttribute(AIM);

	if (attack(l[FIRE], e[WATER], AIM) == DIE)
		return WIN;
	if (attack(e[FIRE], e[WATER], LEAD) == DIE)
		return LOSE;

	if (attack(l[METAL], e[EARTH], AIM) == DIE)
		return WIN;
	if (attack(e[METAL], l[EARTH], LEAD) == DIE)
		return LOSE;

	if (attack(l[WOOD] / 3, 0, AIM) == DIE)
		return WIN;
	cure(l[WOOD] / 3, LEAD);

	if (attack(e[WOOD] / 3, 0, LEAD) == DIE)
		return LOSE;
	cure(e[WOOD] / 3, AIM);

	information->changeHealth(players->getHealth(LEAD), players->getHealthMax(LEAD));
	information->changeEnemyHealth(players->getHealth(AIM), players->getHealthMax(AIM));

	delete[] l;
	delete[] e;

	return 0;
}

void GameScene::showInformation()
{
	showRemoveCount();
	showHealth();
	showAimHealth();
}

void GameScene::showRemoveCount()
{
	information->createLabel(matrix->getRemoveCount(), players->getAttribute(LEAD));
	information->createAimLabel(players->getAttribute(AIM));
}

void GameScene::showHealth()
{
	information->changeHealth(players->getHealth(LEAD), players->getHealthMax(LEAD));
}

void GameScene::showAimHealth()
{
	information->changeEnemyHealth(players->getHealth(AIM), players->getHealthMax(AIM));
}

bool GameScene::changeAttr()
{
	if (matrix->isChanged())
	{
		int s;
		s = matrix->getRemoveMethod();
		switch (s)
		{
		case CHAOS:
			players->changeAttribute(1, 1, 1, 1, 1, 1);
			break;
		case METAL:
			players->changeAttribute(1, 20, 10, 14, 16, 12);
			break;
		case WOOD:
			players->changeAttribute(1, 12, 20, 10, 14, 16);
			break;
		case EARTH:
			players->changeAttribute(1, 16, 12, 20, 10, 14);
			break;
		case WATER:
			players->changeAttribute(1, 14, 16, 12, 20, 10);
			break;
		case FIRE:
			players->changeAttribute(1, 10, 14, 16, 12, 20);
			break;
		default:
			break;
		}
		matrix->removeCountClear();
		matrix->change();
		matrix->signClear();
		showRemoveCount();

		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////

void GameScene::createQuitButton(string normal, string selected)
{
	auto closeItem = MenuItemImage::create(normal, selected, CC_CALLBACK_1(GameScene::quitGame, this));
	closeItem->setPosition(Point(visibleSize.width / 2, 0));
	closeItem->setAnchorPoint(Point(0.5f, 0));
	setSize(closeItem, 0.08f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}

void GameScene::quitGame(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
