//////////////////////////////////////////////////////////////////////////
// 在内核管理所有的控件

#pragma once
#include "IControlBase.h"
#include "ICtrlInterface.h"

// 添加控件，步骤1：编写一个控件名称宏。注意，控件名称不能相同
#define CTRL_NAME_BASE_PANEL					("Panel")

class IControlManager
{
public:
	// 取得所有支持的控件
	virtual void SetRegControlMap(CONTROL_REG_MAP *pCtrlMap) = 0;
	// 创建一个控件，参数为步骤1的宏
	virtual ICtrlInterface* CreateCtrl(char *pCtrlType, char *pszObjectId) = 0;
	// 销毁一个控件
	virtual bool ReleaseCtrl(ICtrlInterface **ppCtrl) = 0;
};
