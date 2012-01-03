// 一个控件必须实现的所有接口

#include "stdafx.h"
#include "..\..\Inc\ICtrlInterface.h"

ICtrlInterface::ICtrlInterface()
{
}

ICtrlInterface::~ICtrlInterface()
{
}

// 派生控件处理的消息
void ICtrlInterface::OnCtrlMessage(int nMsgId, WPARAM wParam, LPARAM lParam)
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
