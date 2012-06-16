
#include "StdAfx.h"
#include "ICtrl_XXXX_Impl.h"

ICtrl_XXXX_Impl::ICtrl_XXXX_Impl()
{
	// 添加控件，步骤3：向内核系统注册控件
	SetObjectType(CTRL_NAME_BASE_PANEL);

}

ICtrl_XXXX_Impl::~ICtrl_XXXX_Impl()
{
}

// 派生控件用于创建属于自己的控件属性
bool ICtrl_XXXX_Impl::CreateControlPropetry(bool bIsNewCtrl)
{
	return true;
}

// 初始化控件
void ICtrl_XXXX_Impl::OnCreate()
{
}

// 控件初始化完毕
void ICtrl_XXXX_Impl::OnFinalCreate()
{
}

// 销毁控件
void ICtrl_XXXX_Impl::OnDestroy()
{
}

// 绘制控件
void ICtrl_XXXX_Impl::OnPaint(CDrawingBoard &DrawBoard)
{
}
