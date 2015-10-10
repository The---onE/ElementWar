#include "StateMachine.h"
#include "State.h"
#include "GameScene.h"

bool StateMachine::initWithGameScene(GameScene* scene)
{
	this->state = NULL;
	this->scene = scene;
	CC_SAFE_RETAIN(scene);

	return true;
}

StateMachine* StateMachine::createWithGameScene(GameScene* scene)
{
	StateMachine *pRet = new StateMachine();
	if (pRet && pRet->initWithGameScene(scene))
	{
		pRet->autorelease();
		CC_SAFE_RETAIN(pRet);
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

State* StateMachine::getState()
{
	return state;
}

void StateMachine::changeState(State* state)
{
	CC_SAFE_RELEASE(this->state);
	this->state = state;
}

void StateMachine::update(float delta)
{
	if (state)
	{
		if (!state->checkStateChange())
			state->onUpdate(delta);
	}
}