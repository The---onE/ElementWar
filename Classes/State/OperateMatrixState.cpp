#include "StateList.h"

bool OperateMatrixState::checkStateChange() //状态改变返回true，状态未改变返回false，
{
	if (scene->checkMatrixConfirm())
	{
		scene->responseMatrixConfirm();
		CHANGE_TO_STATE(ProcessMatrixState);
	}
	return false;
}

bool OperateMatrixState::entryState()
{
	scene->allowMatrixResponse();

	return true;
}

void OperateMatrixState::onUpdate(float dt)
{
	time += dt;
	scene->changeAttr();
}

bool OperateMatrixState::exitState()
{
	scene->forbiddenMatrixResponse();
	return true;
}