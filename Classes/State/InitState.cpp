#include "StateList.h"

bool InitState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
{
	if (matrixFinishFlag)
		CHANGE_TO_STATE(OperateMatrixState);
	return false;
}

bool InitState::entryState()
{
	matrixFinishFlag = false;
	scene->showInformation();
	return true;
}

void InitState::onUpdate(float dt)
{
	time += dt;
	matrixTime += dt;
	if (matrixTime > FALL_TIME)
	{
		matrixTime = 0;
		matrixFinishFlag = !scene->elementFall();
	}
}

bool InitState::exitState()
{
	return true;
}