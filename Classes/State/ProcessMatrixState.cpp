#include "StateList.h"

bool ProcessMatrixState::checkStateChange() //状态改变返回true，状态未改变返回false，
{
	if (matrixFinishFlag)
		CHANGE_TO_STATE(ProcessInjureState);
	return false;
}

bool ProcessMatrixState::entryState()
{
	matrixFinishFlag = false;
	scene->showRemoveCount();
	return true;
}

void ProcessMatrixState::onUpdate(float dt)
{
	time += dt;
	matrixTime += dt;
	if (matrixTime > FALL_TIME)
	{
		matrixTime = 0;
		matrixFinishFlag = !scene->elementFall();
	}
}

bool ProcessMatrixState::exitState()
{
	return true;
}