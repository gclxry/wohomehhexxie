// 一个控件必须实现的所有接口，纯虚接口是派生控件必须实现的，
// 非纯虚接口按照各个控件需求各自继承实现

#pragma once
#include "IControlBase.h"
#include "IWindowBase.h"

class ICtrlInterface : public IControlBase
{
public:
	ICtrlInterface();
	virtual ~ICtrlInterface();

protected:
	// 派生控件用于创建属于自己的控件属性
	// bIsNewCtrl：true时说明是Builder调用，新创建一个控件，需要初始化属性的各个默认值
	// false：说明整个皮肤包已经初始化完毕，属性创建完毕的时候，从xml中读取的属性值已经赋值完毕了，不能再初始化，否则xml中的值会被冲掉
	virtual bool CreateControlPropetry(bool bIsNewCtrl) = 0;
	// 控件初始化过程中
	virtual void OnCreate() = 0;
	// 控件初始化完毕
	virtual void OnFinalCreate() = 0;
	// 销毁控件
	virtual void OnDestroy() = 0;
	// 绘制控件
	virtual void OnPaint(CDrawingBoard &DrawBoard) = 0;
	// 当一个控件包含了其他子控件的时候，系统会发送创建或加载子控件的消息
	virtual void OnCreateSubControl(bool bIsCreate);
	// 控件需要处理的一些自定义的消息，消息基本上会由对话框或者其他控件传入
	virtual void OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam);
	// Builder刷新属性，此函数中只要重新加载控件属性即可
	virtual void OnBuilderRefreshProp(IPropertyBase* pPropBase);
	// 绘制控件的动画，如果需要重新刷新界面，返回true，否则返回false
	// 此函数由定时器触发，每100毫秒触发一次
	virtual bool OnDrawAnimation();
	// 定时器
	virtual void OnTimer(UINT nTimerId);
	// 鼠标进入
	virtual void OnMouseEnter(POINT pt);
	// 鼠标移出
	virtual void OnMouseLeave(POINT pt);
	// 鼠标移动
	virtual void OnMouseMove(POINT pt);
	// 鼠标左键点击
	virtual void OnLButtonDown(POINT pt);
	// 鼠标左键抬起
	virtual void OnLButtonUp(POINT pt);
	// 鼠标左键双击
	virtual void OnLButtonDbClick(POINT pt);
	// 鼠标在控件内部拖动控件，这个消息即可以处理控件内部拖拽的动作，也可以处理不同控件之间拖拽实现数据传输
	virtual void OnMouseDragging(POINT pt);
	// 鼠标右键点击
	virtual void OnRButtonDown(POINT pt);
	// 移动、设置控件位置
	virtual void OnSize();
	// 移动窗口开始
	virtual void OnEnterSizeMove();
	// 移动窗口结束
	virtual void OnExitSizeMove();
	// 控件取得焦点，通过Tab键跳转，激活控件
	virtual void OnSetFocus();
	// 控件失去焦点
	virtual void OnKillFocus();
	// 鼠标滚轮消息
	virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam);
	// 接受到默认回车键，执行控件操作
	virtual void OnDefaultEnterCtrl();
	// 控件取得键盘输入消息
	virtual void OnChar(WPARAM wParam, LPARAM lParam);
	// 按键按下
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam);
	// 滚动条消息
	virtual void OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar);
	// 鼠标是否落在了控件指定的RGN区域，默认返回true，整个控件就是RGN区域
	virtual bool OnCheckMouseInRgn(POINT pt);
	// 这个接口会在整个对话框初始化完成的时候调用
	// 控件通过派生这个接口，可以在这个接口函数里通过其他控件的名称取得当前对话框里的其他控件。
	virtual void OnWindowFinalCreate();
	// 附属对话框即将关闭
	virtual void OnWindowClose();
	// 设置控件光标
	virtual IPropertyCursor* OnSetCursor(POINT pt);
	// 收到需要清空绘制缓存的消息
	virtual void OnClearDrawMemoryDc();

//////////////////////////////////////////////////////////////////////////
	// 用户自定义强动画开始
	virtual void OnUserDefHighAnimationBegin();
	// 用户自定义强动画绘制接口，hWndDc：控件所在的窗口DC
	virtual void OnUserDefHighAnimationDraw(HDC hWndDc);
	// 用户自定义强动画结束
	virtual void OnUserDefHighAnimationEnd();
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
	// 控件之间拖拽，实现数据传输，一个控件 OnMouseDragging 结束后，会向鼠标抬起时所处的控件发送 OnDragStop 消息。
	// 而发起 OnMouseDragging 的控件又会收到 OnGetDragParam 消息，要求取得拖拽的参数。

	// 鼠标拖动操作结束，抬起鼠标。
	// pDragCtrl：拖拽来源控件。拖拽源控件本身无法收到此消息，只能通过 OnLButtonUp 消息来处理
	virtual void OnDragStop(IControlBase* pDragCtrl, POINT pt, WPARAM wParam, LPARAM lParam);
	// 取得控件之间拖拽的数据参数，在触发了 OnDragStop 消息前会被调用
	// WPARAM& wParam, LPARAM& lParam 是两个返回参数
	virtual void OnGetDragParam(WPARAM& wParam, LPARAM& lParam);
//////////////////////////////////////////////////////////////////////////
};
