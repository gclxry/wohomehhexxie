
#pragma once
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\CDrawingBoard.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\IPropertySkinManager.h"

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

//////////////////////////////////////////////////////////////////////////
	// 导入皮肤包使用的函数初始化
	virtual void PG_InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName);

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

//////////////////////////////////////////////////////////////////////////
	// 取得窗口控件指针
	virtual IControlBase* GetControl(char *pszCtrlName);
	// 向队列未插入一个控件
	virtual void AppendChildContrl(IControlBase *pCtrl);
	// 取得子控件列表
	virtual CHILD_CTRLS_VEC* GetChildControlsVec();
	// 取得子控件的属性列表：Layout.xml 中的布局
	virtual PROP_CONTROL_VEC* GetChildPropControlVec();

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
	// 001.内部接受到初始化消息，开始初始化窗口，加载皮肤
	void OnInitWindowBase();
	bool IsInit();

	// 在Builder中绘制用的边框色块
	void BD_NewFrameImage();
	void BD_NewFrameImageBase(IPropertyImageBase *pImgBase, string strImgPath);

private:
	// 循环遍历每个控件的绘制
	void DrawControl();
	void RedrawWindow(RECT* pDrawRct = NULL);
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
	// 皮肤路径
	string m_strSkinPath;
	// 皮肤的object名称
	string m_strWindowObjectName;
	// Builder 专用，显示控件的边框的8个方块
	FANGKUAI_8 m_BD_FangKuai8;

	// 在Builder中绘制用的边框色块
	IPropertyImage m_BuilderWndFrameImage;
	IPropertyImageBase m_BuilderWndFrameImageBase;
	IPropertyImage m_BuilderCtrlFrameImage;
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
	IPropertyBase* CreateCtrlOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
	// 释放子控件列表
	void ReleaseChildVec(CHILD_CTRLS_VEC *pChildCtrlsVec);
	// 绘制窗口和被选中的控件的边框的8个方块
	void BD_DrawSelectRect(CDrawingBoard &MemDc, RECT DrawRct, bool bIsWndFrame);

private:
	IUiEngine *m_pUiEngine;
	IPropertySkinManager* m_pSkinPropMgr;

	bool m_bIsFullScreen;

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
	// base-sysbase-最小尺寸
	// base-sysbase-最大尺寸
	// Group-size
	IPropertyGroup* m_pPropGroupSize;
	// size-width
	IPropertyInt *m_pPropSize_Width;
	// size-height
	IPropertyInt *m_pPropSize_Height;
	// Group-drag(拖拽窗口)
	IPropertyGroup* m_pPropGroupDrag;
	// drag-enable
	IPropertyBool *m_pPropDrag_Enable;
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
