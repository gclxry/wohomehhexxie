// 一个控件必须实现的所有接口，纯虚接口是派生控件必须实现的，
// 非纯虚接口按照各个控件需求各自继承实现

#pragma once
#include "IControlBase.h"

class ICtrlInterface : public IControlBase
{
public:
	ICtrlInterface();
	virtual ~ICtrlInterface();

protected:
	// 派生控件用于创建属于自己的控件属性
	virtual bool CreateControlPropetry() = 0;
	// 初始化控件
	virtual void OnCreate() = 0;
	// 整个皮肤包初始化完毕
	virtual void OnFinalCreate() = 0;
	// 销毁控件
	virtual void OnDestroy() = 0;
	// 绘制控件
	virtual void OnPaint() = 0;
	// 派生控件其他处理的消息
	virtual void OnCtrlMessage(int nMsgId, WPARAM wParam, LPARAM lParam);
	// Builder刷新属性，此函数中只要重新加载控件属性即可
	virtual void OnBuilderRefreshProp();
	// 鼠标进入
	virtual void OnMouseEnter(POINT pt);
	// 鼠标移出
	virtual void OnMouseLeave();
	// 鼠标移动
	virtual void OnMouseMove(POINT pt);
	// 鼠标左键点击
	virtual void OnLButtonDown(POINT pt);
	// 鼠标左键抬起
	virtual void OnLButtonUp(POINT pt);
	// 鼠标左键双击
	virtual void OnLButtonDbClick(POINT pt);
	// 鼠标在控件内部点击按下并移动鼠标
	virtual void OnMouseDragInCtrl(POINT pt);
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
	// 接受到默认回车键，执行控件操作
	virtual void OnDefaultEnterCtrl();
	// 控件取得键盘输入消息
	virtual void OnChar(WPARAM wParam, LPARAM lParam);
	// 按键按下
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam);
};
