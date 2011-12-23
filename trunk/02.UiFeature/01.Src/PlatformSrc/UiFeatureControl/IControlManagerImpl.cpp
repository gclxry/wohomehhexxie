
#include "StdAfx.h"
#include "IControlManagerImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"


IControlManager *GetControlManager()
{
	return IControlManagerImpl::GetInstance();
}

IControlManagerImpl::IControlManagerImpl(void)
{
}

IControlManagerImpl::~IControlManagerImpl(void)
{
	int i = 0;
	i++;
}

IControlManager* IControlManagerImpl::GetInstance()
{
	static IControlManagerImpl _ControlManagerInstance;
	return &_ControlManagerInstance;
}

// 设置一个支持的控件的节点
void IControlManagerImpl::SetRegControl(CONTROL_REG_MAP *pCtrlMap, string strCtrlGroupName, string strCtrlName, string strControlImg)
{
	if (pCtrlMap == NULL)
		return;

	CONTROL_REG RegInfo;

	RegInfo.strControlImg = strControlImg;
	RegInfo.strCtrlGroupName = strCtrlGroupName;
	RegInfo.strCtrlName = strCtrlName;
	RegInfo.strDllName = NAME_CONTROL_DLL;

	pCtrlMap->insert(pair<string, CONTROL_REG>(RegInfo.strCtrlName, RegInfo));
}

//////////////////////////////////////////////////////////////////////////
// 需要修改和扩展的函数
// 取得所有支持的控件
void IControlManagerImpl::SetRegControlMap(CONTROL_REG_MAP *pCtrlMap)
{
	if (pCtrlMap == NULL)
		return;

	pCtrlMap->clear();

	// 注册一个控件
	SetRegControl(pCtrlMap, "基本控件", "Button", "Ctrl (1).png");
	SetRegControl(pCtrlMap, "基本控件", "CheckBox", "Ctrl (2).png");
	SetRegControl(pCtrlMap, "项目组控件", "StaticBox", "Ctrl (3).png");
	SetRegControl(pCtrlMap, "项目组控件", "Link", "Ctrl (4).png");
	// 注册一个控件
}
