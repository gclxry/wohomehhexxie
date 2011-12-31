
#include "StdAfx.h"
#include "..\..\Inc\IPropertyControl.h"

IPropertyControl::IPropertyControl(void)
{
	SetObjectType(PROP_TYPE_CONTROL_NAME);
	m_ChildCtrlPropVec.clear();
	m_pPrentCtrlProp = NULL;
	m_pCtrlPropGroup = NULL;
}

IPropertyControl::~IPropertyControl(void)
{
}

IPropertyControl* IPropertyControl::GetParentCtrlProp()
{
	return m_pPrentCtrlProp;
}

void IPropertyControl::SetParentCtrlProp(IPropertyControl* pCtrlProp)
{
	if (pCtrlProp != NULL)
		m_pPrentCtrlProp = pCtrlProp;
}

void IPropertyControl::AppendChildCtrlProp(IPropertyControl* pCtrlProp)
{
	if (pCtrlProp != NULL)
		m_ChildCtrlPropVec.push_back(pCtrlProp);
}

void IPropertyControl::SetCtrlGroupProp(IPropertyGroup *pBasePropGroup)
{
	if (pBasePropGroup != NULL)
		m_pCtrlPropGroup = pBasePropGroup;
}

IPropertyGroup* IPropertyControl::GetCtrlGroupProp()
{
	return m_pCtrlPropGroup;
}

CHILD_CTRL_PROP_VEC* IPropertyControl::GetChildCtrlVec()
{
	return &m_ChildCtrlPropVec;
}
