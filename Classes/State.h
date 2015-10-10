#pragma once
#include "Global.h"

#include "GameScene.h"

//����create����
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

//ͨ��DEFINE_STATE��END_DEFINE_STATE�Զ�����״̬
#define DEFINE_STATE(STATE) class STATE : public State \
{ \
public: \
	CREATE_STATE(STATE); \
	bool checkStateChange(); \
	bool entryState(); \
	void onUpdate(float dt); \
	bool exitState(); \

#define END_DEFINE_STATE };

#define CHANGE_TO_STATE(STATE) {exitState(); scene->getStateMachine()->changeState(STATE::create(scene)); return true;} //����״̬

class GameScene;

class State : public Node
{
protected:
	GameScene* scene; //�޸�Ϊ��Ϸ������
	float time; //��onUpdate�м���time += dt;��¼�ӽ���״̬����ǰ������֮��

public:
	virtual bool checkStateChange() = 0; //״̬�ı䷵��true��״̬δ�ı䷵��false��ʹ��CHANGE_TO_STATE(STATE)����״̬
	virtual bool entryState() = 0; //����״̬ʱ����һ��
	virtual void onUpdate(float dt) = 0; //ÿ֡����һ��
	virtual bool exitState() = 0; //�˳�״̬����һ��
};

