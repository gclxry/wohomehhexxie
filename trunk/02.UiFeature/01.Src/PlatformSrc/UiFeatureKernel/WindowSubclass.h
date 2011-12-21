
#pragma once
#include "..\..\Inc\IWindowBase.h"

// 被子类化的窗口map
struct SUBCLASS_FUNCTION 
{
	IWindowBase* pWndBase;
	WNDPROC pOldWndProc;
};
typedef map<HWND, SUBCLASS_FUNCTION>		SUB_CLASS_WINDOW_MAP;

class CWindowSubclass
{
public:
	CWindowSubclass();
	virtual ~CWindowSubclass();

	static CWindowSubclass* GetInstance();

	IWindowBase* FindSubWindow(HWND hWnd);
	bool SubWindow(HWND hWnd, IWindowBase* pWndBase);

	SUB_CLASS_WINDOW_MAP* GetSubclassWindowMap();

private:
	// 窗口队列
	SUB_CLASS_WINDOW_MAP m_SubClsWndMap;
};
