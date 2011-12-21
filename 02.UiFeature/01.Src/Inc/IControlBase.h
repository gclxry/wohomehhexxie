
#pragma once
#include "IPropertyControl.h"
#include "..\..\Inc\CMemoryDC.h"

class IWindowBase;

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
};
// 索引：【CONTROL_REG::strCtrlName】
typedef map<string, CONTROL_REG*>	CONTROL_REG_MAP;


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
	CM_EnterRun
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 子控件列表
class IControlBase;
typedef vector<IControlBase*>			CHILD_CTRLS_VEC;

class IControlBase
{
public:
	// 绘制当前控件，参数为父窗口/父控件的内存DC
	virtual void OnPaintControl(CMemoryDC &WndMemDc) = 0;

	// 重绘控件
	virtual void RedrawControl(bool bDrawImmediately = true) = 0;
	// 重绘控件，这个重绘动画定时器中调用
	virtual void RedrawControlInAnimationTimer() = 0;
	// 设置子控件都必须自绘
	virtual void SetChildCtrlToRedraw() = 0;
	// 设置控件在下次绘制的时候是否需要进行重绘
	virtual void SetNeedRedraw(bool bNeedRedraw) = 0;
	// 取得子控件列表
	virtual CHILD_CTRLS_VEC* GetChildCtrlsVec() = 0;
	// 取得控件的基本属性，不包括各自控件扩展的私有属性
	virtual IPropertyControl* GetControlBaseProp() = 0;

	// 鼠标是否Hover
	virtual void SetMouseHover(bool bHover) = 0;
	virtual bool IsMousehover() = 0;

//////////////////////////////////////////////////////////////////////////
// 编码用的控制属性
	// 设置父控件
	virtual void SetParentControl(IControlBase* pParentCtrl) = 0;
	// 取得父控件的指针，如果为NULL，说明父控件是对话框
	virtual IControlBase* GetParentControl() = 0;

//////////////////////////////////////////////////////////////////////////
// 对话框相关
	// 附着对话框
	virtual void SetOwnerWindow(IWindowBase* pWindowsBase) = 0;
	virtual IWindowBase* GetOwnerWindow() = 0;

//////////////////////////////////////////////////////////////////////////
// 控件消息处理
	virtual void OnControlMessage(CONTROL_MSG nMsgId, WPARAM wParam, LPARAM lParam) = 0;
	// 初始化控件
	virtual void OnCreate() = 0;
	// 控件初始化完毕
	virtual void OnFinalCreate() = 0;
	// Builder刷新属性
	virtual void OnRefreshProp() = 0;
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
	virtual void OnMouseDrag(POINT pt) = 0;
	// 鼠标右键点击
	virtual void OnRButtonDown(POINT pt) = 0;
	// 移动、设置控件位置
	virtual void OnSize() = 0;
	// 绘制控件
	virtual void OnPaint() = 0;
	// 移动窗口开始
	virtual void OnEnterSizeMove() = 0;
	// 移动窗口结束
	virtual void OnExitSizeMove() = 0;
	// 销毁控件
	virtual void OnDestroy() = 0;
	// 控件取得焦点，通过Tab键跳转，激活控件
	virtual void OnSetFocus() = 0;
	// 控件失去焦点
	virtual void OnKillFocus() = 0;
	// 控件取得键盘输入消息
	virtual void OnChar(WPARAM wParam, LPARAM lParam) = 0;
	// 接受到默认回车键，执行控件操作
	virtual void OnEnterRun() = 0;
};

