//////////////////////////////////////////////////////////////////////////
// 

#pragma once
#include "BaseCtrlDefs.h"

class CBfWindowsWnd
{
public:
	CBfWindowsWnd(HINSTANCE hInstance);
	virtual ~CBfWindowsWnd(void);

	HWND CreateWindowsWnd(HWND hwndParent, LPCTSTR pstrName = NULL, DWORD dwStyle = WS_CHILD | WS_TABSTOP | WS_VISIBLE, DWORD dwExStyle = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);

protected:
	bool RegisterSuperClass();
	bool RegisterWindowClass();
	UINT GetClassStyle() const;

protected:
	virtual LPCTSTR GetSuperClassName() const = 0;
	virtual LPCTSTR GetWindowClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnFinalMessage(HWND hWnd);

protected:
	static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	HWND m_hWindowsWnd;
	WNDPROC m_OldWndProc;
	HINSTANCE m_hInstance;
};
