
#pragma once
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\CMemoryDC.h"
#include "..\..\Inc\IPropertyWindow.h"

class IWindowBaseImpl : public IWindowBase
{
public:
	IWindowBaseImpl();
	virtual ~IWindowBaseImpl();

	// 初始化
	virtual void InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName);
	// 窗口居中显示
	virtual void CenterWindow();
	// 取得窗口句柄
	virtual HWND GetSafeHandle();
	// 得到窗口屏幕坐标
	virtual RECT GetWindowRect();
	// 得到客户端坐标，[0,0]坐标系
	virtual RECT GetClientRect();
	// 重绘控件
	virtual void RedrawControl(IControlBase* pCtrl, bool bDrawImmediately = true);
	// 窗口属性
	virtual IPropertyWindow* GetWindowProp();
	// 取得窗口控件指针
	virtual IControlBase* GetControl(char *pszCtrlName);

protected:
	// 设置窗体的透明特性、设置窗口是否支持分层
	void SetLayeredWindow(bool bIsLayered);

protected:
	// 本窗口的消息处理函数，bPassOn参数为true是，消息会继续传递处理；false时，处理完毕，不再下传
	virtual LRESULT WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn);

	virtual void OnCreate();
	virtual void OnTimer(UINT nTimerId);
	virtual void OnKeyDown(int nVirtKey, int nFlag);
	// 系统消息，返回TRUE说明不需要返回给调用继续调用
	virtual bool OnSysCommand(int nSysCommand, int xPos, int yPos);
	virtual void OnKillFocus(WPARAM wParam, LPARAM lParam);
	virtual void OnSetFocus(WPARAM wParam, LPARAM lParam);
	virtual void OnDestroy();
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual void OnSizing(UINT nSide, LPRECT lpRect);
	// WM_ENTERSIZEMOVE：进入移动、拉伸窗口操作
	virtual void OnEnterSizeMove();
	// WM_EXITSIZEMOVE：退出移动、拉伸窗口操作
	virtual void OnExitSizeMove();
	virtual void OnPaint(HDC hWndDc);
	// 对话框主菜单：任务栏右键菜单，左上角菜单的截获
	virtual void OnPopupSystemMenu(POINT pt);

	virtual void OnMouseMove(int nVirtKey, POINT pt);
	virtual void OnLButtonDown(int nVirtKey, POINT pt);
	virtual void OnLButtonUp(int nVirtKey, POINT pt);
	virtual void OnLButtonDbClick(int nVirtKey, POINT pt);
	virtual void OnRButtonDown(int nVirtKey, POINT pt);

private:
	// 内部接受到初始化消息，开始初始化窗口，加载皮肤
	void OnInitWindowBase();

private:
	// 循环遍历每个控件的绘制
	void DrawControl();
	void RedrawWindow(RECT* pDrawRct = NULL);
	// 初始化是否完成
	bool IsInit();
	// 当窗口的属性发生变化时需要通知窗口进行刷新时调用
	void RefreshWindowStyle();
	// 取得当前鼠标坐标落在了哪个控件上
	bool CheckMouseInControl(CHILD_CTRLS_VEC *pCtrlVec, POINT pt, IControlBase **ppControl);
	// 设置窗口中所有控件的位置和大小
	void SetControlPostion(CHILD_CTRLS_VEC *pCtrlVec, SIZE NewSize);
	// 根据控件布局信息得到控件的位置
	void SetControlWindowPostion(IControlBase* pCtrl, RECT ParentRctInWnd);
	// 设置当前得到焦点的控件，如果参数为NULL，说明当前没有控件得到焦点，所有控件都失去焦点
	void SetFocusCtrl(IControlBase *pControl);
	// 通过递归查找指定名称的控件
	bool GetControlByName(CHILD_CTRLS_VEC *pCtrlVec, char *pszCtrlName, IControlBase **ppCtrl);

protected:
	BLENDFUNCTION m_Blend;
	// Window属性
	IPropertyWindow *m_pWndProp;
	// 父窗口句柄
	HWND m_hParent;
	// 窗口句柄
	HWND m_hWnd;
	// 整个对话框的内存DC
	CMemoryDC m_WndMemDc;
	// 子控件列表
	CHILD_CTRLS_VEC m_ChildCtrlsVec;
	// 是否为layered窗口
	bool m_bIsLayeredWnd;
	// 鼠标左键是否按下
	bool m_bIsLButtonDown;
	// 鼠标Hover的控件
	IControlBase* m_pMouseHoverCtrl;
	// 鼠标左键按下的控件
	IControlBase* m_pLButtonDownCtrl;
	// 取得焦点的控件
	IControlBase* m_pFocusCtrl;
	// 皮肤路径
	string m_strSkinPath;
	// 对话框名称
	string m_strWindowName;
};

