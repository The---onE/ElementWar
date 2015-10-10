#pragma once
#include "Global.h"

class State;
class GameScene;

class StateMachine : public Node //״̬���࣬�޸�scene����Ϊ��Ϸ�����������ȸ�״̬
{
protected:
	GameScene* scene; //�޸�����Ϊ��Ϸ������
	State* state; //����״̬��Ϣ
public:
	bool initWithGameScene(GameScene* scene); //��ʼ��״̬��������ʱ�Զ�����
	static StateMachine* createWithGameScene(GameScene* scene); //���øú�������״̬��
	State* getState(); //���ص�ǰ״̬
	void changeState(State* state); //����״̬
	void update(float delta); //ÿ֡�Զ�������״̬��Ӧ����
};