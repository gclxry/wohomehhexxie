
#pragma once
#include "IControlManager.h"

//////////////////////////////////////////////////////////////////////////
// �ؼ��ԡ��ںˡ��Ľӿ�
IControlManager *GetControlManager();
typedef IControlManager* (*GETCONTROLMANAGER)();
