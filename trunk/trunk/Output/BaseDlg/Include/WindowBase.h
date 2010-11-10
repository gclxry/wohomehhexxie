
#pragma once

// ���໯��������
enum PWND_TYPE
{
	// �Ի���
	PWT_WND		= 1,
	// �˵�
	PWT_MENU,
};


class CWindowBase
{
public:
	CWindowBase(void) { m_hWnd = NULL; };
	virtual ~CWindowBase(void) {};

	void SetSafeHandle(HWND hWnd) { m_hWnd = hWnd; };
	HWND GetSafeHandle() { return m_hWnd; };
	virtual LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam) = 0;

protected:
	static HINSTANCE m_hInstance;
	HWND m_hWnd;
	PWND_TYPE m_PuppetWndType;
};
