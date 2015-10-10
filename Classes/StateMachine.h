#pragma once
#include "Global.h"

class State;
class GameScene;

class StateMachine : public Node //状态机类，修改scene类型为游戏主场景，调度各状态
{
protected:
	GameScene* scene; //修改类型为游戏主场景
	State* state; //保存状态信息
public:
	bool initWithGameScene(GameScene* scene); //初始化状态机，创建时自动调用
	static StateMachine* createWithGameScene(GameScene* scene); //调用该函数创建状态机
	State* getState(); //返回当前状态
	void changeState(State* state); //更改状态
	void update(float delta); //每帧自动检查调用状态相应方法
};