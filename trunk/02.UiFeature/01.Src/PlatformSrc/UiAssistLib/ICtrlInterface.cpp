// 一个控件必须实现的所有接口

#include "stdafx.h"
#include "..\..\Inc\ICtrlInterface.h"

ICtrlInterface::ICtrlInterface()
{
}

ICtrlInterface::~ICtrlInterface()
{
}

// 控件需要处理的一些自定义的消息，消息基本上会由对话框或者其他控件传入
void ICtrlInterface::OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam)
{
}

// Builder刷新属性，此函数中只要重新加载控件属性即可
void ICtrlInterface::OnBuilderRefreshProp()
{
}

// 鼠标进入
void ICtrlInterface::OnMouseEnter(POINT pt)
{
}

// 鼠标移出
void ICtrlInterface::OnMouseLeave()
{
}

// 鼠标移动
void ICtrlInterface::OnMouseMove(POINT pt)
{
}

// 鼠标左键点击
void ICtrlInterface::OnLButtonDown(POINT pt)
{
}

// 鼠标左键抬起
void ICtrlInterface::OnLButtonUp(POINT pt)
{
}

// 鼠标左键双击
void ICtrlInterface::OnLButtonDbClick(POINT pt)
{
}

// 鼠标在控件内部点击按下并移动鼠标
void ICtrlInterface::OnMouseDragInCtrl(POINT pt)
{
}

// 鼠标右键点击
void ICtrlInterface::OnRButtonDown(POINT pt)
{
}

// 移动、设置控件位置
void ICtrlInterface::OnSize()
{
}

// 移动窗口开始
void ICtrlInterface::OnEnterSizeMove()
{
}

// 移动窗口结束
void ICtrlInterface::OnExitSizeMove()
{
}

// 控件取得焦点，通过Tab键跳转，激活控件
void ICtrlInterface::OnSetFocus()
{
}

// 控件失去焦点
void ICtrlInterface::OnKillFocus()
{
}

// 控件取得键盘输入消息
void ICtrlInterface::OnChar(WPARAM wParam, LPARAM lParam)
{
}

// 控件取得键盘输入消息
void ICtrlInterface::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
}

// 控件取得键盘输入消息
void ICtrlInterface::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
}

// 接受到默认回车键，执行控件操作
void ICtrlInterface::OnDefaultEnterCtrl()
{
}

// 绘制控件的动画，如果需要重新刷新界面，返回true，否则返回false
// 此函数由定时器触发，每100毫秒触发一次
bool ICtrlInterface::OnDrawAnimation()
{
	return false;
}
// 定时器
void ICtrlInterface::OnTimer(UINT nTimerId)
{
}