
#pragma once
#include "..\..\Inc\IPropertyWindowInWindow.h"

class IPropertyWindowImpl : public IPropertyWindowInWindow
{
public:
	IPropertyWindowImpl(void);
	virtual ~IPropertyWindowImpl(void);

	// 是否支持全窗口点击移动
	virtual void SetDragWindow(bool bDrag);
	virtual bool GetDragWindow();

	// 是否最大化
	virtual void SetCanFullScreen(bool bCanFull);
	virtual bool IsCanFullScreen();
	virtual void SetFullScreen(bool bFull);
	virtual bool IsFullScreen();

	// 窗口名称
	virtual void SetWindowName(char *pszWndName);
	virtual const char * GetWindowName();

private:
	bool m_bDragWindow;
	bool m_bCanFullScreen;
	bool m_bIsFullScreen;
	string m_strWndName;
};
