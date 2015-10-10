#include "StateList.h"

bool OperateMatrixState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
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