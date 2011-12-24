
#include "StdAfx.h"
#include "..\..\Inc\IPropertyWindow.h"

IPropertyWindow::IPropertyWindow(void)
{
	SetObjectType("PropertyWindow");
	m_ChildCtrlPropVec.clear();
}

IPropertyWindow::~IPropertyWindow(void)
{
}

CHILD_CTRL_PROP_VEC* IPropertyWindow::GetChildControlVec()
{
	return &m_ChildCtrlPropVec;
}
