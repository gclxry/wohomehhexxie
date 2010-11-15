
#pragma once
#include "FetionSFDefs.h"

// 子类化窗口类型
enum PWND_TYPE
{
	// 对话框
	PWT_WND		= 1,
	// 菜单
	PWT_MENU,
	// 下拉列表框的显示选项窗口
	PWT_DROP_WND,
};

class CWindowBase
{
public:
	CWindowBase(void);
	virtual ~CWindowBase(void);

	// 窗口消息处理
	virtual LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam) = 0;

	// 设置窗口句柄
	void SetSafeHandle(HWND hWnd);
	// 取得窗口句柄
	HWND GetSafeHandle();

	// 得到窗口屏幕坐标
	CRect GetWindowRect();
	// 得到客户端坐标，[0,0]坐标系
	CRect GetClientRect();
	// 根据窗口的长度和宽度，将窗口移到屏幕中央
	void CenterWindow(int cx = 0, int cy = 0);

	// 设置窗口标题文字
	void SetWindowText(CString strText);

	// 设置定时器
	int SetTimer(UINT uElapse);
	// 取消定时器
	void KillTimer(int nId);

public:
	static HINSTANCE ms_hInstance;

protected:

	// 父窗口句柄
	HWND m_hParent;
	// 窗口属性
	DWORD m_dwWndStyle;
	// 窗口句柄
	HWND m_hWnd;
	// 窗口类型
	PWND_TYPE m_PuppetWndType;
	// 窗口类名
	CString m_strWindowClass;
	// 窗口标题文字
	CString m_strWindowText;
	// 定时器ID号
	int m_nTimerId;
};
