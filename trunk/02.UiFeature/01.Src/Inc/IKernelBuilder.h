
#pragma once
#include "IControlBase.h"

class IKernelBuilder
{
public:
	// ȡ������֧�ֵĿؼ�
	virtual CONTROL_REG_MAP *GetRegControlMap() = 0;
};
