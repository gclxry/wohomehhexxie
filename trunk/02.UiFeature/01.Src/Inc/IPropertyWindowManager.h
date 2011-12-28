//////////////////////////////////////////////////////////////////////////
// 一个窗口的属性

#pragma once
#include "IPropertyGroup.h"

class IPropertyWindowManager
{
public:
	// 是否已经初始化
	virtual bool IsInit() = 0;

	// 将xml中的属性设置到manager中
	virtual void SetWindowPropetry(IPropertyGroup *pWndPropInXml) = 0;

	// 是否支持全窗口点击移动
	virtual void SetDragWindow(bool bDrag) = 0;
	virtual bool GetDragWindow() = 0;

	// 是否最大化
	virtual void SetCanFullScreen(bool bCanFull) = 0;
	virtual bool IsCanFullScreen() = 0;
	virtual void SetFullScreen(bool bFull) = 0;
	virtual bool IsFullScreen() = 0;

	// 窗口名称
	virtual void SetWindowName(char *pszWndName) = 0;
	virtual const char * GetWindowName() = 0;

	virtual IPropertyGroup *GetWindowPropetryBaseGroup() = 0;

};
