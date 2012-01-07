
#pragma once
#include "CDrawingBoard.h"
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

class IWindowBase;
class IWindowBaseImpl;
class IUiFeatureKernelImpl;
class IPropertyControl;
class IControlBase;

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
struct CONTROL_REG
{
	// 所处的DLL名称
	string	strDllName;
	// 控件所在的控件组名称
	string	strCtrlGroupName;
	// 控件名称
	string	strCtrlName;
	// 控件在Builder显示的图片或者icon文件，这些文件存放在ControlsRes目录下，为空则使用Builder中的默认的图标
	string	strControlImg;
	// 控件说明
	string strControlInfo;
};
// 索引：【CONTROL_REG::strCtrlName】
typedef map<string, CONTROL_REG>	CONTROL_REG_MAP;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 控件能够收到的消息
enum CONTROL_MSG
{
	// 初始化控件
	CM_Create	= 1,
	// 控件初始化完毕
	CM_FinalCreate,
	// Builder刷新属性
	CM_BuilderRefreshProp,
	// 鼠标进入
	CM_MouseEnter,
	// 鼠标移出
	CM_MouseLeave,
	// 鼠标移动
	CM_MouseMove,
	// 鼠标左键点击
	CM_LButtonDown,
	// 鼠标左键抬起
	CM_LButtonUp,
	// 鼠标左键双击
	CM_LButtonDbClick,
	// 鼠标右键点击
	CM_RButtonDown,
	// 移动、设置控件位置
	CM_Size,
	// 绘制控件
	CM_Paint,
	// 移动窗口开始
	CM_EnterSizeMove,
	// 移动窗口结束
	CM_ExitSizeMove,
	// 销毁控件
	CM_Destroy,
	// 控件取得焦点，通过Tab键跳转，激活控件
	CM_SetFocus,
	// 控件失去焦点
	CM_KillFocus,
	// 控件取得键盘输入消息
	CM_Char,
	// 接受到默认回车键信息
	CM_DefaultEnterCtrl
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 子控件列表
typedef vector<IControlBase*>			CHILD_CTRLS_VEC;

class IControlBase : public IFeatureObject
{
	friend class IWindowBaseImpl;
	friend class IUiFeatureKernelImpl;

public:
	IControlBase();
	virtual ~IControlBase();

	// 得到在Builder中显示的四周8个方块的位置
	virtual FANGKUAI_8* BD_GetFangKuai8Rect();

	// 取得父控件的指针，如果为NULL，说明父控件是对话框
	IControlBase* GetParentControl();
	IWindowBase* GetOwnerWindow();

	// 取得子控件列表
	CHILD_CTRLS_VEC* GetChildControlsVec();
	// 取得子控件的属性列表：Layout.xml 中的布局
	PROP_CONTROL_VEC* GetChildPropControlVec();

	// 重绘控件
	void RedrawControl(bool bDrawImmediately = true);
	// 重绘控件，这个重绘动画定时器中调用
	void RedrawControlInAnimationTimer();


	// 控件显示位置和大小，这个位置是相对于附着的窗口的
	void SetCtrlInWindowRect(RECT CtrlWndRct);
	RECT GetCtrlInWindowRect();
	// 控件显示位置和大小，这个位置是相对于父控件的
	RECT GetCtrlInControlRect();
	// 取得控件的大小
	RECT GetCtrlRect();

	const char * PP_GetControlObjectName();

	// 是否接受鼠标消息
	void SetReceiveMouseMessage(bool bIsReceive);
	bool GetReceiveMouseMessage();

	// 可见属性
	void SetVisible(bool bVisible, bool bSetChild = true);
	bool IsVisible();

	// 拖动控件属性
	void SetDragInControl(bool bDrag);
	bool GetDragInControl();

	// 可用属性
	void SetEnable(bool bEnable, bool bSetChild = true);
	bool IsEnable();

	// 相对于父控件的布局信息
	void SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo);
	CONTROL_LAYOUT_INFO GetLayout();

	// 鼠标是否Hover
	bool IsMousehover();

	IPropertyGroup* PP_GetControlPropetryGroup();
	IPropertyControl *PP_GetControlPropetry();

protected:
	// 设置子控件都必须自绘
	void SetChildCtrlToRedraw();
	// 设置控件在下次绘制的时候是否需要进行重绘
	void SetNeedRedraw(bool bNeedRedraw);

protected:
	// 派生控件用于创建一个属性
	IPropertyBase* CreatePropetry(OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
	// 派生控件用于创建属于自己的控件属性
	// bNeedSetDftProp：true时说明是Builder调用，新创建一个控件，需要初始化属性的各个默认值
	// false：说明整个皮肤包已经初始化完毕，属性创建完毕的时候，从xml中读取的属性值已经赋值完毕了，不能再初始化，否则xml中的值会被冲掉
	virtual bool CreateControlPropetry(bool bNeedSetDftProp) = 0;
	// 初始化控件
	virtual void OnCreate() = 0;
	// 控件初始化完毕
	virtual void OnFinalCreate() = 0;
	// 销毁控件
	virtual void OnDestroy() = 0;
	// 绘制控件
	virtual void OnPaint() = 0;
	// 派生控件处理的消息
	virtual void OnCtrlMessage(int nMsgId, WPARAM wParam, LPARAM lParam) = 0;
	// Builder刷新属性
	virtual void OnBuilderRefreshProp() = 0;
	// 鼠标进入
	virtual void OnMouseEnter(POINT pt) = 0;
	// 鼠标移出
	virtual void OnMouseLeave() = 0;
	// 鼠标移动
	virtual void OnMouseMove(POINT pt) = 0;
	// 鼠标左键点击
	virtual void OnLButtonDown(POINT pt) = 0;
	// 鼠标左键抬起
	virtual void OnLButtonUp(POINT pt) = 0;
	// 鼠标左键双击
	virtual void OnLButtonDbClick(POINT pt) = 0;
	// 鼠标拖动控件
	virtual void OnMouseDragInCtrl(POINT pt) = 0;
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


private:
	// 创建控件属性
	void CreateCtrlAllPropetry(bool bNeedSetDftProp);
	IPropertyBase* CreateCtrlOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

	// 初始化在builder中的属性
	bool BD_InitControlBase(IPropertyControl *pCtrlProp, bool bNeedSetDftProp);
	void SetPropertySkinManager(IPropertySkinManager *pMgr);
	// 向队列未插入一个控件
	void AppendChildContrl(IControlBase *pCtrl);

	void SetUiEngine(IUiEngine *pUiEngine);
	// 设置父控件
	void SetParentControl(IControlBase* pParentCtrl);
	// 附着对话框
	void SetOwnerWindow(IWindowBase* pWindowsBase);

	// 鼠标是否Hover
	void SetMouseHover(bool bHover);

	// 此函数由窗口调用，绘制当前控件，参数为父窗口/父控件的内存DC
	virtual void OnPaintControl(CDrawingBoard &WndMemDc);

protected:
	// 整个控件的内存DC
	CDrawingBoard m_CtrlMemDc;
	// 附着的窗口
	IWindowBase* m_pOwnerWindowBase;
	// 父控件
	IControlBase* m_pParentCtrl;
	// 绘图引擎
	IUiEngine *m_pUiEngine;
	// 子控件列表
	CHILD_CTRLS_VEC m_ChildCtrlsVec;

	// 是否需重绘控件
	bool m_bNeedRedraw;
	// 鼠标Hover状态
	bool m_bMouseHover;
	// 控件位置，这个位置是相对于窗口的位置
	RECT m_RectInWindow;
	// 控件位置，这个位置是相对于父控件的位置
	RECT m_RectInParentCtrl;
	// 控件布局信息
	CONTROL_LAYOUT_INFO m_LayoutInfo;

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
	// base-visible
	IPropertyBool *m_pPropBase_Visible;
	// base-ReceiveMouseMessage
	IPropertyBool *m_pPropBase_RcvMouseMsg;
	// base-enable
	IPropertyBool *m_pPropBase_Enable;
	// base-dragInCtrl
	IPropertyBool *m_pPropBase_DragInCtrl;
	// base-taborder
	IPropertyInt *m_pPropBase_TabOrder;
	// base-defaultenterctrl
	IPropertyBool *m_pPropBase_DefaultEnterCtrl;
	// base-layout
	IPropertyGroup *m_pPropBase_LayoutGroup;
	// layout-width
	IPropertyInt *m_pPropBase_Layout_Width;
	// layout-height
	IPropertyInt *m_pPropBase_Layout_Height;

	// layout-leftspace
	IPropertyComboBox *m_pPropBase_Layout_Layout;
	// layout-leftspace
	IPropertyInt *m_pPropBase_Layout_LeftSpace;
	// layout-rightspace
	IPropertyInt *m_pPropBase_Layout_RightSpace;
	// layout-topspace
	IPropertyInt *m_pPropBase_Layout_TopSpace;
	// layout-bottomspace
	IPropertyInt *m_pPropBase_Layout_BottomSpace;

	// Group:CtrlDefs
	IPropertyGroup* m_pPropGroupCtrlDefs;
	
private:
	// Builder 专用，显示控件的边框的8个方块
	FANGKUAI_8 m_BD_FangKuai8;

protected:

	//////////////////////////////////////////////////////////////////////////
	// 以下3个函数创建、显示属性用，执行顺序由上到下
	// 1. 创建空的属性列表
	// 2. 从xml文件中读取控件属性时，不需要初始化属性的PropId，PropId来源于xml文件
	virtual bool ReadPropFromControlsXml(const char* pszControlId);
	// 2.从Builder中新创建一个控件，需要初始化属性的PropId
	virtual bool InitObjectIdByBuilder(const char* pszBaseId);
	// 3. 创建Builder显示用的属性
	virtual bool CreateBuilderShowPropList();

protected:

	// 2.从Builder中新创建一个控件，需要初始化属性的PropId
	void InitControlPropObjectId(GROUP_PROP_VEC *pPropList);

};
