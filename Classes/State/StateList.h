#pragma once
#include "Global.h"
#include "State.h"

//DEFINE_STATE(XXState)��END_DEFINE_STATE����XXState��֮�䶨����Ի�����

DEFINE_STATE(StartState)
END_DEFINE_STATE

DEFINE_STATE(InitState)
bool matrixFinishFlag;
float matrixTime;
END_DEFINE_STATE

DEFINE_STATE(OperateMatrixState)
END_DEFINE_STATE

DEFINE_STATE(ProcessMatrixState)
bool matrixFinishFlag;
float matrixTime;
END_DEFINE_STATE

DEFINE_STATE(ProcessInjureState)
END_DEFINE_STATE