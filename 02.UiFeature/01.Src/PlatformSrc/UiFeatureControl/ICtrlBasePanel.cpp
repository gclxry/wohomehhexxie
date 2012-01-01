
#include "StdAfx.h"
#include "..\..\Inc\ICtrlBasePanel.h"
#include "..\..\Inc\IControlManager.h"

ICtrlBasePanel::ICtrlBasePanel(void)
{
	// 添加控件，步骤3：向内核系统注册控件
	SetObjectType(CTRL_NAME_BASE_PANEL);
}

ICtrlBasePanel::~ICtrlBasePanel(void)
{
}
