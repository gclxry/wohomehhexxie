
#pragma once
#include "IControlBase.h"
#include "IFeatureObject.h"
#include "IPropertyWindow.h"


class IUiFeatureKernel;
class IWindowBase : public IFeatureObject
{
public:
//////////////////////////////////////////////////////////////////////////
// Builder 使用的函数
	virtual void BD_InitWindowBase(IPropertyWindow *pWindowProp, bool bSetDftProp) = 0;
	virtual void BD_DrawWindowView(CDrawingBoard &ViewMemDc) = 0;
	// 得到在Builder中显示的四周8个方块的位置
	virtual FANGKUAI_8* BD_GetFangKuai8Rect() = 0;
	// 取得当前输入位置的控件
	virtual IControlBase *BD_GetMouseInControl(POINT pt) = 0;
	// 取得当前激活的控件
	virtual IControlBase *BD_GetFocusControl() = 0;
	// 设置当前激活的控件
	virtual void BD_SetFocusControl(IControlBase* pControl) = 0;
	// 设置控件在编辑模式下的位置和大小
	virtual void BD_SetControlRect(IControlBase* pControl, RECT RctInView) = 0;
	// 初始化所有控件在Builder中的显示位置
	virtual void BD_SetAllCtrlRectInView() = 0;
	// 设置指定控件在Builder中的显示位置
	virtual void BD_SetControlRectInView(CHILD_CTRLS_VEC *pChildCtrlsVec) = 0;
	virtual void BD_OnTimer(UINT nTimerId, HWND hView) = 0;
	// Builder有属性修改，重新刷新界面
	virtual void BD_RefreshWindowPropetry() = 0;
	// 重新计算子控件的位置和大小
	virtual void ResetChildCtrlPostion(CHILD_CTRLS_VEC* pChildVec, bool bMemToProp = false) = 0;
	// 是否为设计模式
	virtual bool IsDesignMode() = 0;
//////////////////////////////////////////////////////////////////////////
	// 窗口居中显示
	virtual void CenterWindow() = 0;
	// 取得窗口句柄
	virtual HWND GetSafeHandle() = 0;
	// 得到窗口屏幕坐标
	virtual RECT GetWindowRect() = 0;
	// 得到客户端坐标，[0,0]坐标系
	virtual RECT GetClientRect() = 0;

	// 根据控件布局信息设置控件的位置
	virtual void SetControlWindowPostion(IControlBase* pCtrl, RECT ParentRctInWnd) = 0;
//////////////////////////////////////////////////////////////////////////
	// 取得窗口控件指针
	virtual IControlBase* GetControl(char *pszCtrlName) = 0;
	// 向队列未插入一个控件
	virtual void AppendChildContrl(IControlBase *pCtrl) = 0;
	// 取得子控件列表
	virtual CHILD_CTRLS_VEC* GetChildControlsVec() = 0;
	// 取得子控件的属性列表：Layout.xml 中的布局
	virtual PROP_CONTROL_VEC* GetChildPropControlVec() = 0;

	virtual void InvalidateRect(RECT *lpRect) = 0;
	virtual void UpdateWindow() = 0;
	// 立即重绘窗口，只有需要重绘的控件才重绘
	virtual void RedrawWindow(RECT *pDrawRect = NULL) = 0;
	// 强迫立刻重绘窗口，强迫所有控件均重绘
	virtual void CompelRedrawWindow(RECT *pDrawRect = NULL) = 0;
	// 设置轻量级通用动画定时器
	virtual void SetAnimationTimer() = 0;
	// 设置普通定时器
	virtual int SetTimer(DWORD uElapse) = 0;
	virtual void KillTimer(int nId) = 0;
	// 设置高精度定时器
	virtual int SetHighAccuracyTimer(DWORD uElapse) = 0;
	virtual void KillHighAccuracyTimer(int nId) = 0;

	// 取得整个程序默认的字体信息
	virtual IPropertyFontBase* GetDefaultFontBase() = 0;
	// 设置控件回调函数
	virtual void SetCtrlMsgCallBack(IControlMessage* pCtrlMsg) = 0;
	// 控件消息回调函数
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam) = 0;

	// 向内核注册一个想要取到的消息
	virtual void RegisterControlMessage(IControlBase* pCtrl, int nMsgId) = 0;
	virtual void UnRegisterControlMessage(IControlBase* pCtrl, int nMsgId) = 0;

	// 发送消息:Send方式
	virtual LRESULT SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam) = 0;
	// 发送消息:Post方式
	virtual bool PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam) = 0;

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
	virtual IPropertyGroup *PP_GetWindowPropetryGroup() = 0;
	virtual IPropertyWindow *PP_GetWindowPropetry() = 0;

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

	// 取得窗口中设置属性的窗口大小
	virtual SIZE PP_GetWindowPropSize() = 0;

	virtual IUiFeatureKernel* GetUiKernel() = 0;
};
