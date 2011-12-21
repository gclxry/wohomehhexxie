
#pragma once
#include "IControlManager.h"

//////////////////////////////////////////////////////////////////////////
// 控件对【内核】的接口
IControlManager *GetControlManager();
typedef IControlManager* (*GETCONTROLMANAGER)();
