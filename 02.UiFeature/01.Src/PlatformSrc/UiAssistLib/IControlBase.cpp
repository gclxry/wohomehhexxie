
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

// �����δ����һ���ؼ�
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

// ���ø��ؼ�
void IControlBase::SetParentControl(IControlBase* pParentCtrl)
{
	m_pParentCtrl = pParentCtrl;
}

// ���ø��ؼ�
IControlBase* IControlBase::GetParentControl()
{
	return m_pParentCtrl;
}

// ���ÿؼ����´λ��Ƶ�ʱ���Ƿ���Ҫ�����ػ�
void IControlBase::SetNeedRedraw(bool bNeedRedraw)
{	
	if (!IsVisible())
	{
		m_bNeedRedraw = false;
		return;
	}

	m_bNeedRedraw = bNeedRedraw;
}

// �ػ�ؼ�������ػ涯����ʱ���е���
void IControlBase::RedrawControlInAnimationTimer()
{

}

// �ػ�ؼ�
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

// �����ӿؼ��������Ի�
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

// ȡ���ӿؼ��б�
CHILD_CTRLS_VEC* IControlBase::GetChildCtrlsVec()
{
	return &m_ChildCtrlsVec;
}

// ����Ƿ�Hover
void IControlBase::SetMouseHover(bool bHover)
{
	m_bMouseHover = bHover;
}

bool IControlBase::IsMousehover()
{
	return m_bMouseHover;
}
