
#pragma once
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\CDrawingBoard.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\CHighAccuracyTimer.h"
#include "WindowResize.h"

// 控件注册需要取得的消息
typedef vector<IControlBase*>	REG_CTRL_VEC;
typedef map<int, REG_CTRL_VEC>	REG_MSG_MAP;

class IWindowBaseImpl : public IWindowBase
{
public:
	IWindowBaseImpl();
	virtual ~IWindowBaseImpl();

//////////////////////////////////////////////////////////////////////////
	// Builder 使用的函数
	virtual void BD_InitWindowBase(IPropertyWindow *pWindowProp, bool bSetDftProp);
	virtual void BD_DrawWindowView(CDrawingBoard &ViewMemDc);
	// 得到在Builder中显示的四周8个方块的位置
	virtual FANGKUAI_8* BD_GetFangKuai8Rect();
	// 取得当前输入位置的控件
	virtual IControlBase *BD_GetMouseInControl(POINT pt);
	// 取得当前激活的控件
	virtual IControlBase *BD_GetFocusControl();
	// 设置当前激活的控件
	virtual void BD_SetFocusControl(IControlBase* pControl);
	// 设置控件在编辑模式下的位置和大小
	virtual void BD_SetControlRect(IControlBase* pControl, RECT RctInView);
	// 初始化所有控件在Builder中的显示位置
	virtual void BD_SetAllCtrlRectInView();
	// 设置指定控件在Builder中的显示位置
	virtual void BD_SetControlRectInView(CHILD_CTRLS_VEC *pChildCtrlsVec);
	// Builder有属性修改，重新刷新界面
	virtual void BD_RefreshWindowPropetry();
	// 重新计算子控件的位置和大小，参数：bMemToProp 是否记录到属性中，Builder时为true
	virtual void ResetChildCtrlPostion(CHILD_CTRLS_VEC* pChildVec, bool bMemToProp = false);
	// 是否为设计模式
	virtual bool IsDesignMode();

//////////////////////////////////////////////////////////////////////////
	// 导入皮肤包使用的函数初始化
	virtual void PG_InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName);
	virtual IUiFeatureKernel* GetUiKernel();

	// 窗口居中显示
	virtual void CenterWindow();
	// 取得窗口句柄
	virtual HWND GetSafeHandle();
	// 得到窗口屏幕坐标
	virtual RECT GetWindowRect();
	// 得到客户端坐标，[0,0]坐标系
	virtual RECT GetClientRect();

	// 根据控件布局信息设置控件的位置
	void SetControlWindowPostion(IControlBase* pCtrl, RECT ParentRctInWnd);
//////////////////////////////////////////////////////////////////////////
	// 取得窗口控件指针
	virtual IControlBase* GetControl(char *pszCtrlName);
	// 向队列未插入一个控件
	virtual void AppendChildContrl(IControlBase *pCtrl);
	// 取得子控件列表
	virtual CHILD_CTRLS_VEC* GetChildControlsVec();
	// 取得子控件的属性列表：Layout.xml 中的布局
	virtual PROP_CONTROL_VEC* GetChildPropControlVec();

	// 设置轻量级通用动画定时器
	virtual void SetAnimationTimer();
	// 设置普通定时器
	virtual int SetTimer(DWORD uElapse);
	virtual void KillTimer(int nId);
	// 设置高精度定时器
	virtual int SetHighAccuracyTimer(DWORD uElapse);
	virtual void KillHighAccuracyTimer(int nId);

	void InvalidateRect(RECT *lpRect);
	void UpdateWindow();
	// 立即重绘窗口
	virtual void RedrawWindow(RECT *pDrawRect = NULL);
	// 强迫立刻重绘窗口，强迫所有控件均重绘
	virtual void CompelRedrawWindow(RECT *pDrawRect = NULL);

	// 显示自定义光标
	void SetWindowCursor(int nCursor);

	// 取得整个程序默认的字体信息
	virtual IPropertyFontBase* GetDefaultFontBase();

	// 设置控件回调函数
	virtual void SetCtrlMsgCallBack(IControlMessage* pCtrlMsg);
	// 控件消息回调函数
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);

	// 向内核注册一个想要取到的消息
	virtual void RegisterControlMessage(IControlBase* pCtrl, int nMsgId);
	virtual void UnRegisterControlMessage(IControlBase* pCtrl, int nMsgId);

	// 发送消息:Send方式
	virtual LRESULT SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// 发送消息:Post方式
	virtual bool PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);

	// 显示光标，返回的是原有的鼠标手势
	virtual IPropertyCursorBase* ShowCursor(IPropertyCursorBase *pCursorBase);

protected:
	// 本窗口的消息处理函数，bPassOn参数为true是，消息会继续传递处理；false时，处理完毕，不再下传
	virtual LRESULT WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn);

	virtual void OnCreate();
	virtual void BD_OnTimer(UINT nTimerId, HWND hView);
	virtual void OnTimer(UINT nTimerId);
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam);
	virtual void OnChar(WPARAM wParam, LPARAM lParam);
	// 系统消息，返回true说明不需要返回给调用继续调用
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
	virtual void OnPaint(HDC hWndDc, RECT *pLayeredRect = NULL);
	// 对话框主菜单：任务栏右键菜单，左上角菜单的截获
	virtual void OnPopupSystemMenu(POINT pt);
	// 设置鼠标样式，返回true表示设置了自定义的鼠标手势，false为需要使用系统默认的手势
	virtual bool OnSetCursor(HWND hWnd, int nHitTest, int nMsgId);
	virtual LRESULT OnNcHitTest(int nX, int nY);
	// 窗口尺寸最大值最小值设置
	virtual bool OnGetMinMaxInfo(MINMAXINFO *pMinMaxInfo);

	virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam);
	virtual void OnMouseMove(int nVirtKey, POINT pt);
	virtual void OnLButtonDown(int nVirtKey, POINT pt);
	virtual void OnLButtonUp(int nVirtKey, POINT pt);
	virtual void OnLButtonDbClick(int nVirtKey, POINT pt);
	virtual void OnRButtonDown(int nVirtKey, POINT pt);

private:
	// 内部接受到初始化消息，开始初始化窗口，加载皮肤
	void OnInitWindowBase();
	// 初始化对话框、加载窗口皮肤完成，在分层窗口模式下，初始化窗口后，显示窗口
	void OnInitWindowBaseEnd();
	bool IsInit();
	// 创建控件
	bool CreateChildCtrlVec(IControlBase *pParentCtrl, PROP_CONTROL_VEC* pPropCtrlVec, CHILD_CTRLS_VEC* pCtrlVec);

	// 在Builder中绘制用的边框色块
	void BD_NewFrameImage();
	void BD_NewFrameImageBase(IPropertyImageBase *pImgBase, string strImgPath);
	bool BD_CheckMouseInControl(CHILD_CTRLS_VEC *pCtrlVec, POINT pt, IControlBase** ppControl);

	// 从相对窗口的鼠标相对坐标得到相对控件的鼠标坐标
	POINT GetCtrlMouseOffset(POINT WndPt, IControlBase* pCtrl);
	// 取得桌面工作区域大小
	RECT GetWorkAreaRect();
	// 强迫子控件重绘
	void CompelRedrawControl(CHILD_CTRLS_VEC *pCtrlVec);

private:
	// 循环遍历每个控件的绘制
	void DrawControl();
	// 当窗口的属性发生变化时需要通知窗口进行刷新时调用
	void RefreshWindowStyle();
	// 取得当前鼠标坐标落在了哪个控件上
	bool CheckMouseInControl(CHILD_CTRLS_VEC *pCtrlVec, POINT pt, IControlBase **ppControl);
	// 设置窗口中所有控件的位置和大小
	void SetControlPostion(CHILD_CTRLS_VEC *pCtrlVec, SIZE NewSize);
	// 设置当前得到焦点的控件，如果参数为NULL，说明当前没有控件得到焦点，所有控件都失去焦点
	void SetFocusCtrl(IControlBase *pControl);
	// 通过递归查找指定名称的控件
	bool GetControlByName(CHILD_CTRLS_VEC *pCtrlVec, char *pszCtrlName, IControlBase **ppCtrl);
	// 在分层窗口模式下拉伸窗口大小
	void ResizeInLayeredWindow(RECT NewWndRect);
	// 根据窗口基本属性，设置窗口基本样式
	void SetWindowStyleByProp();
	// 设置窗口支持透明模式
	void SetWindowTransparence(bool bIsTrans);
	// 在任务栏上隐藏主窗口按钮
	void HideInTaskbar();
	// 向内核注册一个想要取到的消息
	void DoRegisterControlMessage(IControlBase* pCtrl, int nMsgId);
	void DoUnRegisterControlMessage(IControlBase* pCtrl, int nMsgId);
	// 派发控件注册的消息
	void DispatchRegisterMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);

	bool OnTimerToChild(CHILD_CTRLS_VEC &ChildCtrlsVec, UINT nTimerId);

protected:
	// 控件注册需要取得的消息
	REG_MSG_MAP m_CtrlRegMsgMap;
	// 控件的消息回调接口
	IControlMessage* m_pCtrlMsgCallBack;
	// 高进度定时器
	CHighAccuracyTimer m_HighTimer;
	// 是否为设计模式
	bool m_bIsDesignMode;
	// 皮肤路径
	string m_strSkinPath;
	// 皮肤的object名称
	string m_strWindowObjectName;
	// Builder 专用，显示控件的边框的8个方块
	FANGKUAI_8 m_BD_FangKuai8;

	// 在Builder中绘制用的边框色块
	IPropertyImageBase m_BuilderWndFrameImageBase;
	IPropertyImageBase m_BuilderCtrlFrameImageBase;

	BLENDFUNCTION m_Blend;
	// 父窗口句柄
	HWND m_hParent;
	// 窗口句柄
	HWND m_hWnd;
	// 整个对话框的内存DC
	CDrawingBoard m_WndMemDc;
	// 鼠标左键是否按下
	bool m_bIsLButtonDown;
	// 鼠标Hover的控件
	IControlBase* m_pMouseHoverCtrl;
	// 鼠标左键按下的控件
	IControlBase* m_pLButtonDownCtrl;
	// 取得焦点的控件
	IControlBase* m_pFocusCtrl;
	// 子控件列表
	CHILD_CTRLS_VEC m_ChildCtrlsVec;
	// Builder中View窗口的句柄
	HWND m_hBuilderView;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 窗口属性
public:
	// 将xml中的属性设置到manager中
	virtual IPropertyGroup *PP_GetWindowPropetryGroup();
	virtual IPropertyWindow *PP_GetWindowPropetry();

	virtual void PP_SetWindowPropetry(IPropertyWindow *pWndPropInXml, bool bSetDftProp);

	// 是否支持全窗口点击移动
	virtual void PP_SetDragWindow(bool bDrag);
	virtual bool PP_GetDragWindow();

	// 是否最大化
	virtual void PP_SetCanFullScreen(bool bCanFull);
	virtual bool PP_IsCanFullScreen();
	virtual void PP_SetFullScreen(bool bFull);
	virtual bool PP_IsFullScreen();

	// 设置窗体的透明特性、设置窗口是否支持分层
	virtual void PP_SetLayeredWindow(bool bIsLayered);
	virtual bool PP_GetLayeredWindow();

	// 窗口Object名称
	virtual void PP_SetWindowObjectName(char *pszWndName);
	virtual const char * PP_GetWindowObjectName();

	// 窗口名称
	virtual void PP_SetWindowText(char *pszWndName);
	virtual const char * PP_GetWindowText();

	// 取得窗口中设置属性的窗口大小
	virtual SIZE PP_GetWindowPropSize();

private:
	// 创建空的属性队列
	void CreateWindowPropetry(bool bSetDftProp);
	IPropertyBase* CreateWindowOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
	// 释放子控件列表
	void ReleaseChildVec(CHILD_CTRLS_VEC *pChildCtrlsVec);
	// 绘制窗口和被选中的控件的边框的8个方块
	void BD_DrawSelectRect(CDrawingBoard &MemDc, FANGKUAI_8 &FangKuai8, bool bIsWndFrame);
	// 向所有控件发送对话框初始化完成的消息
	void SendWindowInitOkMsgToCtrl(CHILD_CTRLS_VEC *pChildCtrlsVec);
	// 向所有控件发送进入/离开对话框移动/拉伸消息
	void SendEnterOrExitSizeMsgToCtrl(bool bIsEnter, CHILD_CTRLS_VEC *pChildCtrlsVec);

private:
	IUiFeatureKernel *m_pUiKernel;
	IUiEngine *m_pUiEngine;
	IPropertySkinManager* m_pSkinPropMgr;
	// 控制拉伸窗口操作的类
	CWindowResize m_WndResize;
	// 当前显示的鼠标手势
	IPropertyCursorBase *m_pCurrentCursorBase;

	bool m_bIsFullScreen;
	// 当前鼠标样式宏
	int m_nCurMouseStyle;

	// 从xml中读入并需要写入xml中的属性窗口属性列表
	IPropertyWindow *m_pXmlPropWindow;

	// Group:base
	IPropertyGroup* m_pPropGroupBase;
	// base-类型名称
	IPropertyString *m_pPropBase_TypeName;
	// base-objectid
	IPropertyString *m_pPropBase_ObjectId;
	// base-name
	IPropertyString *m_pPropBase_Name;
	// base-windowtitle
	IPropertyString *m_pPropBase_WindowText;
	// base-visible
	IPropertyBool *m_pPropBase_Visible;
	// base-在任务栏显示按钮
	IPropertyBool *m_pPropBase_ShowInTaskbar;
	// base-支持分层窗口
	IPropertyBool *m_pPropBase_Layered;
	// base-topmost
	IPropertyBool *m_pPropBase_TopMost;
	// base-sysbase
	IPropertyGroup* m_pPropGroupSysBase;
	// base-sysbase-最大化
	IPropertyBool *m_pPropSysBase_CanFullScreen;
	// base-sysbase-最小化
	IPropertyBool *m_pPropSysBase_CanMiniSize;

	// Group-size
	IPropertyGroup* m_pPropGroupWindowSize;
	// size-width
	IPropertyInt *m_pPropSize_WindowWidth;
	// size-height
	IPropertyInt *m_pPropSize_WindowHeight;

	// Group-drag(拖拽窗口)
	IPropertyGroup* m_pPropGroupDrag;
	// drag-enable
	IPropertyBool *m_pPropDrag_Enable;

	// Group-Size(窗口的大小)
	IPropertyGroup* m_pPropGroupSize;
	// Size-enable
	IPropertyBool *m_pPropSize_Enable;
	// Size-MaxWidth
	IPropertyInt *m_pPropSize_MaxWidth;
	// Size-MaxHeight
	IPropertyInt *m_pPropSize_MaxHeight;
	// Size-MinWidth
	IPropertyInt *m_pPropSize_MinWidth;
	// Size-MinHeight
	IPropertyInt *m_pPropSize_MinHeight;

	// Group-stretching(拉伸窗口)
	IPropertyGroup* m_pPropGroupStretching;
	// stretching-enable
	IPropertyBool *m_pPropStretching_Enable;
	// stretching-leftspace
	IPropertyInt *m_pPropStretching_LeftSpace;
	// stretching-rightspace
	IPropertyInt *m_pPropStretching_RightSpace;
	// stretching-topspace
	IPropertyInt *m_pPropStretching_TopSpace;
	// stretching-bottomspace
	IPropertyInt *m_pPropStretching_BottomSpace;
	// Group-WindowRgn
	IPropertyGroup* m_pPropGroupWindowRgn;
};
