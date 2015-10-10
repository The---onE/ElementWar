#pragma once

#include "Global.h"
#include "StateMachine.h"

#include "Interface/Interface.h"
#include "User/User.h"

class GameScene : public Scene
{
protected:
	StateMachine* stateMachine; //状态机

	BackgroundLayer* bg;
	MatrixLayer* matrix;
	InformationLayer* information;

	Players* players;

public:
	CREATE_FUNC(GameScene);
	bool init();
	StateMachine* getStateMachine(); //返回状态机指针
	void update(float dt);

	void initBackground();
	void initMatrix();
	void initInformation();

	void initPlayers();

	bool elementFall() { return matrix->elementsFall(); }
	void allowMatrixResponse() { matrix->allowResponse(); }
	void forbiddenMatrixResponse() { matrix->forbiddenResponse(); }
	bool checkMatrixConfirm() { return matrix->checkConfirm(); }
	void responseMatrixConfirm() { matrix->responseConfirm(); }

	int attack(int att, int def, int aim);
	int cure(int cur, int aim);

	//////////////////////////////////////////////////////////////////////////
	int processInjure();

	void showInformation();
	void showRemoveCount();
	void showHealth();
	void showAimHealth();
	bool changeAttr();
	//////////////////////////////////////////////////////////////////////////

	void createQuitButton(string normal, string selected);
	void quitGame(Ref* pSender); //退出游戏
};

