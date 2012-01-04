
#pragma once
#include "IControlBase.h"
#include "IFeatureObject.h"
#include "IPropertyWindow.h"

class IWindowBase : public IFeatureObject
{
public:
//////////////////////////////////////////////////////////////////////////
// Builder 使用的函数
	virtual void BD_InitWindowBase(IPropertyWindow *pWindowProp, bool bSetDftProp) = 0;

//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
	// 取得窗口控件指针
	virtual IControlBase* GetControl(char *pszCtrlName) = 0;
	// 向队列未插入一个控件
	virtual void AppendChildContrl(IControlBase *pCtrl) = 0;

public:
////// 以下函数非外部窗口调用 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 非外部窗口调用：初始化子类化窗口
	virtual void PG_InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName) = 0;
	// 非外部窗口调用：本窗口的消息处理函数，bPassOn参数为true是，消息会继续传递处理；false时，处理完毕，不再下传
	virtual LRESULT WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn) = 0;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 窗口属性相关
	// 是否支持全窗口点击移动
	virtual void PP_SetDragWindow(bool bDrag) = 0;
	virtual bool PP_GetDragWindow() = 0;

	// 是否最大化
	virtual void PP_SetCanFullScreen(bool bCanFull) = 0;
	virtual bool PP_IsCanFullScreen() = 0;
	virtual void PP_SetFullScreen(bool bFull) = 0;
	virtual bool PP_IsFullScreen() = 0;

	// 窗口Object名称
	virtual void PP_SetWindowObjectName(char *pszWndName) = 0;
	virtual const char * PP_GetWindowObjectName() = 0;

	// 窗口名称
	virtual void PP_SetWindowText(char *pszWndName) = 0;
	virtual const char * PP_GetWindowText() = 0;

	virtual IPropertyGroup *PP_GetWindowPropetryGroup() = 0;

};
