
#pragma once
#include "..\..\Inc\IPropertyWindowManager.h"
#include "..\..\Inc\IPropertyGroup.h"

class IPropertyWindowManagerImpl : public IPropertyWindowManager
{
public:
	IPropertyWindowManagerImpl(void);
	virtual ~IPropertyWindowManagerImpl(void);

	virtual bool IsInit();

	// 将xml中的属性设置到manager中
	virtual void SetXmlPropetry(IPropertyGroup *pWndPropInXml);

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
	// 创建空的属性队列
	void CreateEmptyWindowPropetry();

private:
	bool m_bIsInit;
	bool m_bDragWindow;
	bool m_bCanFullScreen;
	bool m_bIsFullScreen;
	string m_strWndName;

	// 从xml中读入并需要写入xml中的属性窗口属性列表
	IPropertyGroup *m_pWndPropInXml;
};
