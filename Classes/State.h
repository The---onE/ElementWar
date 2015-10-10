#pragma once
#include "Global.h"

#include "GameScene.h"

//定义create方法
#define CREATE_STATE(__TYPE__) \
static __TYPE__* create(GameScene* scene) \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && (pRet->scene=scene) && pRet->entryState()) \
	{ \
        pRet->autorelease(); \
        CC_SAFE_RETAIN(pRet); \
		pRet->time = 0; \
        return pRet; \
	} \
	else \
	{ \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
	} \
}

//通过DEFINE_STATE和END_DEFINE_STATE自动定义状态
#define DEFINE_STATE(STATE) class STATE : public State \
{ \
public: \
	CREATE_STATE(STATE); \
	bool checkStateChange(); \
	bool entryState(); \
	void onUpdate(float dt); \
	bool exitState(); \

#define END_DEFINE_STATE };

#define CHANGE_TO_STATE(STATE) {exitState(); scene->getStateMachine()->changeState(STATE::create(scene)); return true;} //更改状态

class GameScene;

class State : public Node
{
protected:
	GameScene* scene; //修改为游戏主场景
	float time; //在onUpdate中加入time += dt;记录从进入状态到当前经历的之间

public:
	virtual bool checkStateChange() = 0; //状态改变返回true，状态未改变返回false，使用CHANGE_TO_STATE(STATE)更改状态
	virtual bool entryState() = 0; //进入状态时调用一次
	virtual void onUpdate(float dt) = 0; //每帧调用一次
	virtual bool exitState() = 0; //退出状态调用一次
};

