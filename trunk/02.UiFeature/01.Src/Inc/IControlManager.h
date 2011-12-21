//////////////////////////////////////////////////////////////////////////
// 在内核管理所有的控件

#pragma once
#include "IControlBase.h"

class IControlManager
{
public:
	// 取得所有支持的控件
	virtual void SetRegControlMap(CONTROL_REG_MAP *pCtrlMap) = 0;
};
