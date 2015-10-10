#include "StateList.h"

bool ProcessInjureState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
{
	if (time > 0)
		CHANGE_TO_STATE(OperateMatrixState);
	return false;
}

bool ProcessInjureState::entryState()
{
	scene->processInjure();
	scene->showInformation();

	return true;
}

void ProcessInjureState::onUpdate(float dt)
{
	time += dt;
}

bool ProcessInjureState::exitState()
{
	return true;
}