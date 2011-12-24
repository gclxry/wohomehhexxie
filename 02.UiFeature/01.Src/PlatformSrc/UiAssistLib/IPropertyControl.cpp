
#include "StdAfx.h"
#include "..\..\Inc\IPropertyControl.h"

IPropertyControl::IPropertyControl(void)
{
	SetObjectType("PropertyControl");
	m_ChildCtrlPropVec.clear();
	m_pPrentCtrlProp = NULL;
	m_pCtrlPropGroup = NULL;
}

IPropertyControl::~IPropertyControl(void)
{
}

IPropertyControl* IPropertyControl::GetParentProp()
{
	return m_pPrentCtrlProp;
}

void IPropertyControl::SetParentProp(IPropertyControl* pCtrlProp)
{
	if (pCtrlProp != NULL)
		m_pPrentCtrlProp = pCtrlProp;
}

void IPropertyControl::AppendControlProp(IPropertyControl* pCtrlProp)
{
	if (pCtrlProp != NULL)
		m_ChildCtrlPropVec.push_back(pCtrlProp);
}

void IPropertyControl::SetControlBaseProp(IPropertyGroup *pBasePropGroup)
{
	if (pBasePropGroup != NULL)
		m_pCtrlPropGroup = pBasePropGroup;
}

IPropertyGroup* IPropertyControl::GetControlBaseProp()
{
	return m_pCtrlPropGroup;
}

CHILD_CTRL_PROP_VEC* IPropertyControl::GetChildControlVec()
{
	return &m_ChildCtrlPropVec;
}
