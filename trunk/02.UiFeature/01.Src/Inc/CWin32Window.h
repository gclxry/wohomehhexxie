// 说明：Win32的基本对话框

#pragma once
#include <Windows.h>

#define FEATURE_CLASS_NAME						"Win32Window"

class CWin32Window
{
public:
	CWin32Window();
	virtual ~CWin32Window();

	// 创建一个窗口，参数：
	// HWND hParent：父窗口
	// RECT WndRect：窗口显示位置，坐标为屏幕位置
	// char *pszWndText：窗口标题
	// int nShow：显示模式，如：SW_SHOW、SW_HIDE
	// LPARAM lParam：创建窗口时传入的参数，可以通过 GetCreateWindowParam 函数取得
	virtual bool CreateWindowWithNewThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, LPARAM lParam);
	virtual bool CreateWindowWithoutThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, LPARAM lParam);

	// 本窗口的消息处理函数
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);

	// 取得窗口标题文字
	const char* GetWindowText();
	// 设置窗口标题文字
	void SetWindowText(char* pstrWndText);
	// 取得窗口句柄
	HWND GetSafeHandle();
	// 得到窗口屏幕坐标
	RECT GetWindowRect();
	// 得到客户端坐标，[0,0]坐标系
	RECT GetClientRect();
	// 同API的 IsWindow
	bool IsWindow();
	// 将窗口移到屏幕中央
	void CenterWindow();
	// 设置定时器
	void SetTimer(int nId, UINT uElapse);
	// 取消定时器
	void KillTimer(int nId);
	// 设置对话框位置
	void MoveWindow(RECT MoveRect, BOOL bRepaint = TRUE);
	// 显示/隐藏窗口，参数为SW_SHOW之类
	void ShowWindow(int nShow);
	// 设置重绘区域
	void InvalidateRect(RECT *pInvRect);
	// 更新窗口，立即进行绘制
	void UpdateWindow();
	// 立即重绘窗口
	void RedrawWindow(RECT *pDrawRect = NULL);
	// 发送消息:Send方式
	LRESULT SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// 发送消息:Post方式
	bool PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// 设置窗口支持透明模式
	void SetWindowTransparence(bool bIsTrans);
	// 取得创建对话框的参数
	LPARAM GetCreateWindowParam();
	// 窗口是否被销毁
	bool IsWindowEnd();
	// 窗口线程是否被销毁
	bool IsWindowThreadEnd();
	// 销毁窗口，true：等待销毁完成，false：不等待销毁完成
	// 如果在本窗口的线程中调用，true会引起死锁
	void CloseWindow(bool bIsWaitEnd = true);

	// 取得桌面工作区域大小
	RECT GetWorkAreaRect();

protected:
	// 以下Windows消息函数的重载，都需要调用父类的原函数 /////////////////////////////////////////////////////
	// 如果需要重载的消息函数不在下列函数中，请联系相关开发人员 //////////////////////////////////////////////
	virtual void OnKeyDown(int nVirtKey, int nFlag);
	// 系统消息，返回true说明不需要返回给系统继续调用，直接返回
	virtual bool OnSysCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnCreate();
	// WM_TIMER：定时器	
	virtual void OnTimer(UINT nTimerId);
	// WM_DESTROY：销毁窗口
	virtual void OnDestroy();
	virtual void OnKillFocus();
	virtual void OnSetFocus();
	virtual void OnSize(UINT nType, int cx, int cy);
	// 类似MFC的PreTranslateMessage，如果返回的是true，不再继续往下派发消息
	virtual bool PreTranslateMessage(MSG msg);

	// 设置创建对话框的参数
	void SetCreateWindowParam(LPARAM lParam);

	// Win32 对话框注册创建函数
	ATOM RegisterClass();
	virtual bool InitInstance();

	// 在任务栏上隐藏主窗口按钮
	void HideInTaskbar();
//////////////////////////////////////////////////////////////////////////
	// 以下函数原则上不允许外部程序调用，只提供给内部使用

public:
	// 设置窗口句柄
	void SetSafeHandle(HWND hWnd);
	void _BeginWindowThread();
	void _PostEndThread();
	void WaitWindowThreadEnd();

protected:
	bool m_bIsCreateWithThread;
	// 窗口句柄
	HWND m_hWnd;
	// 窗口标题文字
	string m_strWndText;
	// 父窗口句柄
	HWND m_hParentWnd;
	// 创建对话框的参数，程序可以通过创建函数传入
	LPARAM m_lParam;

	HANDLE m_hCreateWaitEvent;
	HANDLE m_hUiThread;
	DWORD m_dwUiThreadId;
	RECT m_rctCreate;
	int m_nCreateShow;
};
