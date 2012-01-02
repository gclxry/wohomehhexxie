
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\UiFeatureDefs.h"

IControlBase::IControlBase()
{
	SetObjectType("ControlBase");
	m_pUiEngine = NULL;
	m_pOwnerWindowBase = NULL;
	m_ChildCtrlsVec.clear();
	m_bNeedRedraw = true;
	m_bMouseHover = false;

	m_pParentCtrl = NULL;

	InitControlPropetry();
}

IControlBase::~IControlBase()
{
}

// 向队列未插入一个控件
void IControlBase::AppendChildContrl(IControlBase *pCtrl)
{
	if (pCtrl != NULL)
		m_ChildCtrlsVec.push_back(pCtrl);
}

void IControlBase::OnControlMessage(CONTROL_MSG nMsgId, WPARAM wParam, LPARAM lParam)
{

}

void IControlBase::SetOwnerWindow(IWindowBase* pWindowsBase)
{
	m_pOwnerWindowBase = pWindowsBase;
}

IWindowBase* IControlBase::GetOwnerWindow()
{
	return m_pOwnerWindowBase;
}

// 设置父控件
void IControlBase::SetParentControl(IControlBase* pParentCtrl)
{
	m_pParentCtrl = pParentCtrl;
}

// 设置父控件
IControlBase* IControlBase::GetParentControl()
{
	return m_pParentCtrl;
}

// 设置控件在下次绘制的时候是否需要进行重绘
void IControlBase::SetNeedRedraw(bool bNeedRedraw)
{	
	if (!IsVisible())
	{
		m_bNeedRedraw = false;
		return;
	}

	m_bNeedRedraw = bNeedRedraw;
}

// 重绘控件，这个重绘动画定时器中调用
void IControlBase::RedrawControlInAnimationTimer()
{

}

// 重绘控件
void IControlBase::RedrawControl(bool bDrawImmediately)
{
	if (m_pOwnerWindowBase != NULL)
	{
		IControlBase *pCtrl = dynamic_cast<IControlBase*>(this);
		m_pOwnerWindowBase->RedrawControl(pCtrl);
	}

	m_bNeedRedraw = true;
	SetChildCtrlToRedraw();
}

// 设置子控件都必须自绘
void IControlBase::SetChildCtrlToRedraw()
{
	m_bNeedRedraw = true;
	for (CHILD_CTRLS_VEC::iterator pCtrlItem = m_ChildCtrlsVec.begin(); pCtrlItem != m_ChildCtrlsVec.end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl != NULL)
			pCtrl->SetChildCtrlToRedraw();
	}
}

// 取得子控件列表
CHILD_CTRLS_VEC* IControlBase::GetChildCtrlsVec()
{
	return &m_ChildCtrlsVec;
}

// 鼠标是否Hover
void IControlBase::SetMouseHover(bool bHover)
{
	m_bMouseHover = bHover;
}

bool IControlBase::IsMousehover()
{
	return m_bMouseHover;
}
