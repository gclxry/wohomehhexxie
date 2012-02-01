// 说明：UiFeature的高性能基本对话框

#pragma once
#include <Windows.h>
#include "IWindowBase.h"
#include "IControlBase.h"
#include "IUiFeatureKernel.h"

class CUiFeatureWindow : public IControlMessage
{
public:
	CUiFeatureWindow();
	virtual ~CUiFeatureWindow();

	// 创建一个窗口，参数：
	// char* pszDllDir：UiFeatureKernel.dll的全路径
	// char* pszSkinPath：*.ufd皮肤文件的全路径
	// char *pszWndName：*.ufd皮肤文件中对话框的名字
	// HWND hParent：父窗口
	// RECT WndRect：窗口显示位置，坐标为屏幕位置
	// int nShow：显示模式，如：SW_SHOW、SW_HIDE
	// LPARAM lParam：创建窗口时传入的参数，可以通过 GetCreateWindowParam 函数取得
	bool CreateFeatureWindow(char* pszKernelDllPath, char* pszSkinPath, char *pszSkinWndName, HWND hParent, RECT WndRect, int nShow, LPARAM lParam);

	// 控件发送给窗口的消息接口
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, WPARAM wParam, LPARAM lParam);
	// 本窗口的消息处理函数
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);

	// 取得窗口句柄
	HWND GetSafeHandle();
	// 得到窗口屏幕坐标
	RECT GetWindowRect();
	// 得到客户端坐标，[0,0]坐标系
	RECT GetClientRect();
	// 取得
	IWindowBase* GetUiFeatureWindow();
	// 取得窗口标题文字
	const char* GetWindowText();
	// 设置窗口标题文字
	void SetWindowText(char* pstrWndText);
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
	// 销毁窗口，同时销毁窗口线程，这个函数必须在此窗口外的线程调用
	// 如果在本窗口的线程中调用，会引起死锁
	void CloseWindow();
	// 窗口内部需要关闭窗口，调用此函数
	void CloseSelf();
	// 设置窗口支持透明模式
	void SetWindowTransparence(bool bIsTrans);
	// 取得创建对话框的参数
	LPARAM GetCreateWindowParam();
	// 取得窗口中指定名称的控件
	IControlBase* GetCtrlObject(char* pstrCtrlName);
	// 窗口是否被销毁
	bool IsWindowEnd();
	// 窗口线程是否被销毁
	bool IsWindowThreadEnd();
	// 初始化对话框错误
	virtual void OnInitWindowError(int nErrorCode);
	// 初始化对话框成功
	virtual void OnInitWindowSuccess();

protected:
	// 以下Windows消息函数的重载，都需要调用父类的原函数 /////////////////////////////////////////////////////
	// 如果需要重载的消息函数不在下列函数中，请联系相关开发人员 //////////////////////////////////////////////
	virtual void OnKeyDown(int nVirtKey, int nFlag);
	// 系统消息，返回true说明不需要返回给系统继续调用，直接返回
	virtual bool OnSysCommand(WPARAM wParam, LPARAM lParam);
	// WM_CREATE：对话框初始化	
	virtual void OnCreate();
	// 对话框初始化完毕调用
	virtual void OnCreateEnd();
	// WM_TIMER：定时器	
	virtual void OnTimer(UINT nTimerId);
	// WM_DESTROY：销毁窗口
	virtual void OnDestroy();
	virtual void OnKillFocus();
	virtual void OnSetFocus();
	// 类似MFC的PreTranslateMessage，如果返回的是true，不再继续往下派发消息
	virtual bool PreTranslateMessage(MSG msg);

private:
	// 设置创建对话框的参数
	void SetCreateWindowParam(LPARAM lParam);
	// 创建一个普通窗口，没有经过内核过滤
	bool CreateWin32Window(HWND hParent, RECT WndRect, char *pszWndText, int nShow, LPARAM lParam);
	// Win32 对话框注册创建函数
	ATOM RegisterClass();
	bool InitInstance();

//////////////////////////////////////////////////////////////////////////
	// 以下函数原则上不允许外部程序调用，只提供给内部使用
public:
	// 设置窗口句柄
	void SetSafeHandle(HWND hWnd);
	void _BeginWindowThread();
	void _PostEndThread();
	void WaitWindowThreadEnd();

protected:
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

//////////////////////////////////////////////////////////////////////////
	HMODULE m_hKernelDll;
	IUiFeatureKernel *m_pUiFeatureKernel;
	// UiFeature界面的对话框资源指针
	IWindowBase* m_pWindowBase;
	string m_strKernelDllPath;
	string m_strSkinPath;
	string m_strSkinWndName;
};
