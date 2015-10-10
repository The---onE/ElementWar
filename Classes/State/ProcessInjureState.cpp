#include "StateList.h"

bool ProcessInjureState::checkStateChange() //状态改变返回true，状态未改变返回false，
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