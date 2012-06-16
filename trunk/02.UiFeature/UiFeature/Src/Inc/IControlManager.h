//////////////////////////////////////////////////////////////////////////
// 在内核管理所有的控件

#pragma once
#include "IControlBase.h"
#include "ICtrlInterface.h"

class IControlManager
{
public:
	// 取得所有支持的控件
	virtual void SetRegControlMap(CONTROL_REG_TLIST *pCtrlMap) = 0;
	// 创建一个控件，参数为步骤1的宏
	virtual ICtrlInterface* CreateCtrl(char *pCtrlType) = 0;
	// 销毁一个控件
	virtual bool ReleaseCtrl(ICtrlInterface **ppCtrl) = 0;
	// 删除一个控件的注册信息
	virtual void DeleteRegControlInfo(CONTROL_REG* pReg) = 0;
};

//////////////////////////////////////////////////////////////////////////
// 控件对【内核】的接口
IControlManager *GetControlManager();
typedef IControlManager* (*GETCONTROLMANAGER)();
