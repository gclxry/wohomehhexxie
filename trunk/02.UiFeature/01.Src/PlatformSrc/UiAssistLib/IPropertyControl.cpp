
#include "StdAfx.h"
#include "..\..\Inc\IPropertyControl.h"

IPropertyControl::IPropertyControl(void)
{
	SetObjectType(PROP_TYPE_CONTROL_NAME);
	m_ChildCtrlPropVec.clear();
	m_pPrentCtrlProp = NULL;
	m_pCtrlPropGroup = NULL;
	m_strControlType = "";
}

IPropertyControl::~IPropertyControl(void)
{
}

const char * IPropertyControl::GetControlType()
{
	return m_strControlType.c_str();
}

void IPropertyControl::SetControlType(char *pszCtrlType)
{
	if (pszCtrlType == NULL)
		return;

	m_strControlType = pszCtrlType;
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

IPropertyGroup* IPropertyControl::GetControlPropGroup()
{
	return m_pCtrlPropGroup;
}

PROP_CONTROL_VEC* IPropertyControl::GetChildPropControlVec()
{
	return &m_ChildCtrlPropVec;
}
