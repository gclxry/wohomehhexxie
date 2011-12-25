
#pragma once
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IPropertyWindowManager.h"

class IWindowBase
{
public:
	// 窗口居中显示
	virtual void CenterWindow() = 0;
	// 取得窗口句柄
	virtual HWND GetSafeHandle() = 0;
	// 得到窗口屏幕坐标
	virtual RECT GetWindowRect() = 0;
	// 得到客户端坐标，[0,0]坐标系
	virtual RECT GetClientRect() = 0;
	// 重绘控件
	virtual void RedrawControl(IControlBase* pCtrl, bool bDrawImmediately = true) = 0;
	// 窗口属性
	virtual IPropertyWindowManager* GetWindowProp() = 0;
	// 取得窗口控件指针
	virtual IControlBase* GetControl(char *pszCtrlName) = 0;


public:
////// 以下函数非外部窗口调用 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 非外部窗口调用：初始化子类化窗口
	virtual void InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName) = 0;
	// 非外部窗口调用：本窗口的消息处理函数，bPassOn参数为true是，消息会继续传递处理；false时，处理完毕，不再下传
	virtual LRESULT WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn) = 0;
};
