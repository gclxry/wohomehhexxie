
#pragma once
#include "IControlBase.h"

class IKernelBuilder
{
public:
	// 取得所有支持的控件
	virtual CONTROL_REG_MAP *GetRegControlMap() = 0;
};
