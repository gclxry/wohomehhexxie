
#include "StdAfx.h"
#include "ICtrlCheckBoxImpl.h"
#include "..\..\Inc\IControlManager.h"

ICtrlCheckBoxImpl::ICtrlCheckBoxImpl(void)
{
	// 添加控件，步骤3：向内核系统注册控件
	SetObjectType(CTRL_NAME_CHECK_BOX);

}

ICtrlCheckBoxImpl::~ICtrlCheckBoxImpl(void)
{
}

// 派生控件用于创建属于自己的控件属性
bool ICtrlCheckBoxImpl::CreateControlPropetry(bool bNeedSetDftProp)
{
	return true;
}

// 初始化控件
void ICtrlCheckBoxImpl::OnCreate()
{
}

// 控件初始化完毕
void ICtrlCheckBoxImpl::OnFinalCreate()
{
}

// 销毁控件
void ICtrlCheckBoxImpl::OnDestroy()
{
}

// 绘制控件
void ICtrlCheckBoxImpl::OnPaint(CDrawingBoard &DrawBoard)
{
}
