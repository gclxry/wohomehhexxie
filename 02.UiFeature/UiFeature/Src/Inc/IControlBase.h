
#pragma once
#include "CDrawingImage.h"
#include "IFeatureObject.h"
#include "IUiEngine.h"
#include "IPropertySkinManager.h"
#include "IPropertyString.h"
#include "IPropertyGroup.h"
#include "IPropertyBool.h"
#include "IPropertyInt.h"
#include "IPropertyColor.h"
#include "IPropertyComboBox.h"
#include "IPropertyCursor.h"
#include "IPropertyFont.h"
#include "IPropertyImage.h"
#include "CTList.h"


class IWindowBase;
class IWindowBaseImpl;
class IUiFeatureKernelImpl;
class IPropertyControl;
class IControlBase;
class IControlManager;


// 控件基础消息，这个消息会发给窗口或者创建它的父控件。
enum CTRL_MSG_BASE
{
	CMB_BASE = 0x000F0000,
	// 控件动画开始
	CMB_ANIMATION_BEGIN,
	// 控件动画结束
	CMB_ANIMATION_END,
	// 动画有异常
	CMB_ANIMATION_ERROR
};


// 控件发送消息接口
class IControlMessage
{
public:
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam) = 0;
};

// Builder 专用，显示控件的边框的8个方块
struct FANGKUAI_8
{
	// 所有坐标都是基于View的绝对坐标
	RECT EntityRct;
	RECT LeftTop;
	RECT LeftMid;
	RECT LeftBottom;
	RECT MidTop;
	RECT MidBottom;
	RECT RightTop;
	RECT RightMid;
	RECT RightBottom;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 当前控件相对于父控件的布局类型

// 固定大小：左上角定位
#define TN_CL_G_LEFT_TOP				"左上角定位"
// 固定大小：左下角定位
#define TN_CL_G_LEFT_BOTTOM				"左下角定位"
// 固定大小：右上角定位
#define TN_CL_G_RIGHT_TOP				"右上角定位"
// 固定大小：右下角定位
#define TN_CL_G_RIGHT_BOTTOM			"右下角定位"
// 拉伸变动大小：撑满左侧
#define TN_CL_L_LEFT					"撑满左侧"
// 拉伸变动大小：撑满右侧
#define TN_CL_L_RIGHT					"撑满右侧"
// 拉伸变动大小：撑满上方
#define TN_CL_L_TOP						"撑满上方"
// 拉伸变动大小：撑满下方
#define TN_CL_L_BOTTOM					"撑满下方"
// 拉伸变动大小：撑满全部
#define TN_CL_L_ALL						"撑满全部"
// 拉伸变动大小：居中
#define TN_CL_L_MIDDLE					"居中"
// 拉伸变动大小：用户自定义位置
#define TN_CL_L_USER_DEF				"用户自定义位置"
// 固定大小：靠上居中
#define TN_CL_G_TOP_MIDDLE				"固定大小：靠上居中"
// 固定大小：靠下居中
#define TN_CL_G_BOTTOM_MIDDLE			"固定大小：靠下居中"
// 固定大小：靠左居中
#define TN_CL_G_LEFT_MIDDLE				"固定大小：靠左居中"
// 固定大小：靠右居中
#define TN_CL_G_RIGHT_MIDDLE			"固定大小：靠右居中"
// 固定大小：居中
#define TN_CL_G_MID_MIDDLE				"固定大小：居中"

enum CONTROL_LAYOUT
{
	// 固定大小：左上角定位
	CL_G_LEFT_TOP		= 0,
	// 固定大小：左下角定位
	CL_G_LEFT_BOTTOM	= 1,
	// 固定大小：右上角定位
	CL_G_RIGHT_TOP		= 2,
	// 固定大小：右下角定位
	CL_G_RIGHT_BOTTOM	= 3,
	// 拉伸变动大小：撑满左侧
	CL_L_LEFT			= 4,
	// 拉伸变动大小：撑满右侧
	CL_L_RIGHT			= 5,
	// 拉伸变动大小：撑满上方
	CL_L_TOP			= 6,
	// 拉伸变动大小：撑满下方
	CL_L_BOTTOM			= 7,
	// 拉伸变动大小：撑满全部
	CL_L_ALL			= 8,
	// 拉伸变动大小：居中
	CL_L_MIDDLE			= 9,
	// 拉伸变动大小：用户自定义位置
	CL_L_USER_DEF		= 10,
	// 固定大小：靠上居中
	CL_G_TOP_MIDDLE		= 11,
	// 固定大小：靠下居中
	CL_G_BOTTOM_MIDDLE	= 12,
	// 固定大小：靠左居中
	CL_G_LEFT_MIDDLE	= 13,
	// 固定大小：靠右居中
	CL_G_RIGHT_MIDDLE	= 14,
	// 固定大小：居中
	CL_G_MID_MIDDLE		= 15,
};
// 当前控件相对于父控件的布局信息
struct CONTROL_LAYOUT_INFO
{
	// 布局类型
	CONTROL_LAYOUT clType;
	// 控件宽
	int nWidth;
	// 控件高
	int nHeight;
	// 距离父控件左侧距离
	int nLeftSpace;
	// 距离父控件右侧距离
	int nRightSpace;
	// 距离父控件上方距离
	int nTopSpace;
	// 距离父控件下方距离
	int nBottomSpace;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 一个控件对外提供的注册信息，这个信息会注册到UiFeatureBuilder提供Builder显示，
// 也会提供给UiFeatureKernel进行查询
class CONTROL_REG : public ListObj
{
public:
	CONTROL_REG();
	~CONTROL_REG();

	IControlManager* pCtrlMgr;
	// 所处的DLL名称
	char strDllName[MAX_PATH + 1];
	// 控件所在的控件组名称
	char strCtrlGroupName[MAX_PATH + 1];
	// 控件名称
	char strCtrlName[MAX_PATH + 1];
	// 控件说明
	char strControlInfo[MAX_PATH + 1];
};
// 内部存放 CONTROL_REG*
typedef CTList CONTROL_REG_TLIST;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 子控件列表
// typedef vector<IControlBase*>			CHILD_CTRLS_VEC;
// IControlBase* 列表
typedef CTList			CHILD_CTRLS_VEC;

class IControlBase : public IFeatureObject, public ListObj
{
	friend class IWindowBaseImpl;
	friend class IUiFeatureKernelImpl;

public:
	IControlBase();
	virtual ~IControlBase();

	// 得到在Builder中显示的四周8个方块的位置
	virtual FANGKUAI_8* BD_GetFangKuai8Rect();

	// 是否锁定在Builder中鼠标改变控件大小和位置
	void SetLockControl(bool bLock);
	bool GetLockControl();

	// 取得父控件的指针，如果为NULL，说明父控件是对话框
	IControlBase* GetParentControl();
	IWindowBase* GetOwnerWindow();

	// 取得子控件列表
	CHILD_CTRLS_VEC* GetChildControlsVec();
	// 取得子控件的属性列表：Layout.xml 中的布局
	PROP_CONTROL_VEC* GetChildPropControlVec();

	// 重绘控件
	virtual void RedrawControl(bool bDrawImmediately = false);

	// 控件显示位置和大小，这个位置是相对于附着的窗口的
	// bRememberToProp:false 不会改变布局信息
	// bRememberToProp:true 会改变布局信息
	virtual void SetWindowRect(RECT CtrlInWndRct, bool bRememberToProp = false);
	virtual RECT GetWindowRect();
	virtual RECT GetClientRect();
	// 移动控件，会将最终的位置信息存为布局信息
	// 参数：CtrlInWndRct控件位于窗口的位置
	// bSetChild：是否递归设置子控件
	void SetWindowRectLayoutWithChild(RECT CtrlInWndRct, bool bSetChild = true);

	// 可见属性
	virtual void SetVisible(bool bVisible, bool bSetChild = false);
	virtual bool IsVisible();

	// 可用属性
	virtual void SetEnable(bool bEnable, bool bSetChild = false);
	virtual bool IsEnable();

	// 绘制控件到指定的DC上
	void PrintTo(CDrawingBoard &DstBoard, RECT ToRct);
	// 将当前控件，包括子控件，都打印到一个内存DC上
	// bPrintWhenInvisible：如果控件visiable属性为false是否也打印
	bool PrintToCoverChild(CDrawingBoard &DstBoard, bool bPrintWhenInvisible);

	// 判断参数中的控件是否就是自己
	bool CompareControl(IControlBase* pCtrl);

	// 取得父窗口的句柄
	HWND GetOwnerWindowHwnd();

	const char * PP_GetControlObjectName();

	// 是否接受鼠标消息
	void SetReceiveMouseMessage(bool bIsReceive);
	bool GetReceiveMouseMessage();

	CONTROL_LAYOUT_INFO GetLayout();

	// 鼠标是否Hover
	bool IsMousehover();

	IPropertyGroup* PP_GetControlPropetryGroup();
	IPropertyControl *PP_GetControlPropetry();

	// 整个控件绘制完成后，再绘制到父控件上的alpha值
	void PP_SetControlDrawAlpha(int nCtrlAlpha);
	int PP_GetControlDrawAlpha();

	// 是否使用 AlphaBlend 函数直接将控件绘制到窗口上
	void PP_SetControlAlphaBlendDraw(bool bIsAlphaBlendDraw);
	bool PP_GetControlAlphaBlendDraw();

	// 是否为无绘制控件
	void PP_SetNoDrawControl(bool bIsNoDrawCtrl);
	bool PP_GetNoDrawControl();

	// 设置动画类型
	void PP_SetCtrlAnimationType(DWORD animEffect);
	DWORD PP_GetCtrlAnimationType();

	// 设置/取得发送控件消息的目标
	void SetControlMessage(IControlMessage* pCtrlMsg);
	IControlMessage* GetControlMessage();

	// 取得绘制控件的内存DC
	CDrawingBoard* GetMemoryDc();
	// 从属性更新数据到成员变量
	void PropetyValueToMemberValue(bool bCallRefresh, IPropertyBase* pPropBase);

//////////////////////////////////////////////////////////////////////////
	// 滚动条消息
	virtual void OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar) = 0;
	virtual void OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar) = 0;
	// 鼠标滚轮消息
	virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam) = 0;

	// 控件需要处理的一些自定义的消息，消息基本上会由对话框或者其他控件传入
	virtual void OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam) = 0;

	// 派生控件用于创建一个属性
	IPropertyBase* CreatePropetry(IPropertyGroup* pPropGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

	// 当一个控件包含了其他子控件的时候，系统会发送创建或加载子控件的消息
	void CreateSubControl(bool bIsCreate);
	// 设置父控件
	void SetParentControl(IControlBase* pParentCtrl);
	// 设置控件的布局方式
	void SetControlLayoutType(CONTROL_LAYOUT CtrlLayout);
	// 设置隶属于的dll
	void SetControlDllManager(IControlManager* pOwnerCtrlDllMgr);
	IControlManager* GetControlDllManager();

	// 是否使用临时内存绘制
	bool PP_IsUseTempDrawMem();

protected:
	// 设置子控件都必须自绘
	void SetChildCtrlToRedraw();

	// 派生控件用于创建属于自己的控件属性
	// bIsNewCtrl：true时说明是Builder调用，新创建一个控件，需要初始化属性的各个默认值
	// false：说明整个皮肤包已经初始化完毕，属性创建完毕的时候，从xml中读取的属性值已经赋值完毕了，不能再初始化，否则xml中的值会被冲掉
	virtual bool CreateControlPropetry(bool bIsNewCtrl) = 0;
	// 绘制控件的动画，如果需要重新刷新界面，返回true，否则返回false
	// 此函数由定时器触发，每100毫秒触发一次
	virtual bool OnDrawAnimation() = 0;
	// 定时器
	virtual void OnTimer(UINT nTimerId) = 0;
	// 初始化控件
	virtual void OnCreate() = 0;
	// 控件初始化完毕
	virtual void OnFinalCreate() = 0;
	// 当一个控件包含了其他子控件的时候，系统会发送创建或加载子控件的消息
	virtual void OnCreateSubControl(bool bIsCreate) = 0;
	// 整个对话框包括对话框上的控件都初始化完毕
	virtual void OnWindowFinalCreate() = 0;
	// 附属对话框即将关闭
	virtual void OnWindowClose() = 0;
	// Builder刷新属性，此函数中只要重新加载控件属性即可
	virtual void OnBuilderRefreshProp(IPropertyBase* pPropBase) = 0;
	// 销毁控件
	virtual void OnDestroy() = 0;
	// 绘制控件
	virtual void OnPaint(CDrawingBoard &DrawBoard) = 0;
	// 鼠标进入
	virtual void OnMouseEnter(POINT pt) = 0;
	// 鼠标移出
	virtual void OnMouseLeave(POINT pt) = 0;
	// 鼠标移动
	virtual void OnMouseMove(POINT pt) = 0;
	// 鼠标左键点击
	virtual void OnLButtonDown(POINT pt) = 0;
	// 鼠标左键抬起
	virtual void OnLButtonUp(POINT pt) = 0;
	// 鼠标左键双击
	virtual void OnLButtonDbClick(POINT pt) = 0;
	// 鼠标在控件内部拖动
	virtual void OnMouseDragging(POINT pt) = 0;
	// 鼠标拖动操作结束，抬起鼠标。pDragCtrl：拖拽来源控件
	virtual void OnDragStop(IControlBase* pDragCtrl, POINT pt, WPARAM wParam, LPARAM lParam) = 0;
	// 取得控件之间拖拽的数据参数，在触发了 OnDragStop 消息后会被调用
	virtual void OnGetDragParam(WPARAM& wParam, LPARAM& lParam) = 0;
	// 鼠标右键点击
	virtual void OnRButtonDown(POINT pt) = 0;
	// 移动、设置控件位置
	virtual void OnSize() = 0;
	// 移动窗口开始
	virtual void OnEnterSizeMove() = 0;
	// 移动窗口结束
	virtual void OnExitSizeMove() = 0;
	// 控件取得焦点，通过Tab键跳转，激活控件
	virtual void OnSetFocus() = 0;
	// 控件失去焦点
	virtual void OnKillFocus() = 0;
	// 接受到默认回车键，执行控件操作
	virtual void OnDefaultEnterCtrl() = 0;
	// 控件取得键盘输入消息
	virtual void OnChar(WPARAM wParam, LPARAM lParam) = 0;
	// 按键按下
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam) = 0;
	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam) = 0;
	// 鼠标是否落在了控件指定的RGN区域，默认返回true，整个控件就是RGN区域
	virtual bool OnCheckMouseInRgn(POINT pt) = 0;
	// 设置控件光标
	virtual IPropertyCursor* OnSetCursor(POINT pt) = 0;
	// 收到需要清空绘制缓存的消息
	virtual void OnClearDrawMemoryDc() = 0;

//////////////////////////////////////////////////////////////////////////
	// 用户自定义强动画开始
	virtual void OnUserDefHighAnimationBegin() = 0;
	// 用户自定义强动画绘制接口，hWndDc：控件所在的窗口DC
	virtual void OnUserDefHighAnimationDraw(HDC hWndDc) = 0;
	// 用户自定义强动画结束
	virtual void OnUserDefHighAnimationEnd() = 0;
//////////////////////////////////////////////////////////////////////////

	// 向内核注册一个想要取到的消息
	void RegisterControlMessage(int nMsgId);
	void UnRegisterControlMessage(int nMsgId);
	// 发送消息:Send方式
	LRESULT SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// 发送消息:Post方式
	bool PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// 播放动画消息
	void OnCtrlAnimation(WPARAM wParam, LPARAM lParam);
	// 准备控件动画
	bool ControlAnimationReady();

private:
	// 创建控件属性
	void CreateCtrlAllPropetry(bool bIsNewCtrl);
	IPropertyBase* CreateCtrlOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

	// 初始化在builder中的属性
	bool InitControlPropetry(IPropertyControl *pCtrlProp, bool bIsNewCtrl);
	void SetPropertySkinManager(IPropertySkinManager *pMgr);
	// 向队列未插入一个控件
	void AppendChildContrl(IControlBase *pCtrl);

	void SetUiEngine(IUiEngine *pUiEngine);
	// 附着对话框
	void SetOwnerWindow(IWindowBase* pWindowsBase);

	// 鼠标是否Hover
	void SetMouseHover(bool bHover);

	// 此函数由窗口调用，绘制当前控件，参数为父窗口/父控件的内存DC
	virtual void OnPaintControl(CDrawingBoard &WndMemDc, RECT ActiveDrawRct);

	// 从成员变量更新数据到属性
	void MemberValueToPropetyValue();
	// 重新计算子控件的位置和大小
	void ResetChildPropetyValueToMemberValue(IControlBase* pParentCtrl, bool bCallRefresh, IPropertyBase* pPropBase);
	// 控件显示位置和大小，会根据布局信息连带修改子控件的位置
	void SetChildControlLayoutPostion(CHILD_CTRLS_VEC* pVec);
	// 递归打印子控件到一个内存DC上
	bool ChildPrint(CHILD_CTRLS_VEC *pChildCtrlsVec, CDrawingBoard& DstBoard, POINT offsetPt, bool bPrintWhenInvisible);

	// 清空属性的隶属于哪个控件的信息
	void ClearPropertyOwner();
	// 清空绘制缓存
	void ClearDrawMemoryDc();

protected:
	// 发送消息的目标
	IControlMessage* m_pSendMsgCtrl;

	// 子控件列表
	CHILD_CTRLS_VEC m_ChildCtrlsVec;

	// 是否需重绘控件
	bool m_bNeedRedraw;
	// 鼠标Hover状态
	bool m_bMouseHover;
	// 控件位置，这个位置是相对于窗口的位置
	RECT m_RectInWindow;

	// 整个控件的内存DC
	CDrawingImage m_CtrlMemDc;
	// 动画内存DC
	CDrawingImage m_CtrlAnimationMemDc;
	// 动画是否开始
	bool m_bIsCtrlAnimationBegin;

	// 附着的窗口
	IWindowBase* m_pWindowBase;
	// 父控件
	IControlBase* m_pParentCtrl;
	// 绘图引擎
	IUiEngine *m_pUiEngine;

	// 皮肤包管理类
	IPropertySkinManager *m_pSkinPropMgr;
	// 记录到xml中的属性
	IPropertyControl *m_pXmlPropCtrl;

	// Group:base
	IPropertyGroup* m_pPropGroupBase;
	// base-类型名称
	IPropertyString *m_pPropBase_TypeName;
	// base-objectid
	IPropertyString *m_pPropBase_ObjectId;
	// base-name
	IPropertyString *m_pPropBase_Name;
	// base-lock
	IPropertyBool *m_pPropBase_Lock;
	// base-visible
	IPropertyBool *m_pPropBase_Visible;
	// base-ReceiveMouseMessage
	IPropertyBool *m_pPropBase_RcvMouseMsg;
	// base-enable
	IPropertyBool *m_pPropBase_Enable;
	// base-taborder
	IPropertyInt *m_pPropBase_TabOrder;
	// base-defaultenterctrl
	IPropertyBool *m_pPropBase_DefaultEnterCtrl;

	// base-Draw
	IPropertyGroup *m_pPropBase_DrawGroup;
	// base-Draw-NoDrawControl
	IPropertyBool *m_pPropBase_NoDrawCtrl;
	// base-Draw-AlphaBlendDraw
	IPropertyBool *m_pPropBase_Draw_AlphaBlendDraw;
	// base-Draw-DrawAlpha
	IPropertyInt *m_pPropBase_Draw_DrawAlpha;
	// base-Draw-TempDrawMem
	IPropertyBool *m_pPropBase_Draw_TempDrawMem;

	// base-layout
	IPropertyGroup *m_pPropBase_LayoutGroup;
	// layout-width
	IPropertyInt *m_pPropBase_Layout_Width;
	// layout-height
	IPropertyInt *m_pPropBase_Layout_Height;

	// layout-
	IPropertyComboBox *m_pPropBase_Layout_Layout;
	// layout-leftspace
	IPropertyInt *m_pPropBase_Layout_LeftSpace;
	// layout-rightspace
	IPropertyInt *m_pPropBase_Layout_RightSpace;
	// layout-topspace
	IPropertyInt *m_pPropBase_Layout_TopSpace;
	// layout-bottomspace
	IPropertyInt *m_pPropBase_Layout_BottomSpace;

	// base-Animation
	IPropertyGroup *m_pPropBase_AnimationGroup;
	// Animation-AnimationType
	IPropertyComboBox *m_pPropBase_AnimationType;
	// Animation-FrameTimeSpin
	IPropertyInt *m_pPropBase_Animation_FrameTime;
	// Animation-Front
	IPropertyComboBox *m_pPropBase_Animation_Direction;

	// Group:CtrlDefs
	IPropertyGroup* m_pPropGroupCtrlDefs;

private:
	// Builder 专用，显示控件的边框的8个方块
	FANGKUAI_8 m_BD_FangKuai8;
	IControlManager* m_pOwnerCtrlDllMgr;
};
