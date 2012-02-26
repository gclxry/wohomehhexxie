
#include "StdAfx.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\ICommonFun.h"

IPropertyWindow::IPropertyWindow(void)
{
	SetObjectType(PROP_TYPE_WINDOW_NAME);
	m_ChildCtrlPropVec.clear();
	m_pWindowProp = NULL;
}

IPropertyWindow::~IPropertyWindow(void)
{
}

void IPropertyWindow::AppendChildCtrlProp(IPropertyControl *pPropCtrl)
{
	if (pPropCtrl == NULL)
		return;

	m_ChildCtrlPropVec.push_back(pPropCtrl);
}

PROP_CONTROL_VEC* IPropertyWindow::GetChildPropControlVec()
{
	return &m_ChildCtrlPropVec;
}

void IPropertyWindow::SetWindowPropGroup(IPropertyGroup *pWindowProp)
{
	if (pWindowProp == NULL)
		return;

	SetObjectId(pWindowProp->GetObjectId());

	m_pWindowProp = pWindowProp;
	IPropertyString* pNameProp = FindObjectNameProperty(m_pWindowProp);
	if (pNameProp == NULL)
		return;

	SetObjectName(pNameProp->GetString());
}

IPropertyGroup* IPropertyWindow::GetWindowPropGroup()
{
	return m_pWindowProp;
}
