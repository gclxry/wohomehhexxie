
#pragma once
#include "..\..\Inc\IWindowBase.h"

// �����໯�Ĵ���map
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
	// ���ڶ���
	SUB_CLASS_WINDOW_MAP m_SubClsWndMap;
};
