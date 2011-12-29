
#include "stdafx.h"
#include "..\..\Inc\IPropertyBase.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyBase::IPropertyBase()
{
	SetObjectType("PropertyBase");

	// ������������
	m_strRelevancyPropName = "";
	// ��������
	m_pRelevancyProp = NULL;
}

IPropertyBase::~IPropertyBase()
{

}

bool IPropertyBase::IsRightData()
{
	return (strlen(this->GetObjectName()) > 0);
}

// ��XML�ڵ��ȡ����ֵ�����������Զ���
bool IPropertyBase::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	return false;
}

const char* IPropertyBase::GetRelevancyPropName()
{
	return m_strRelevancyPropName.c_str();
}

void IPropertyBase::SetRelevancyPropName(char *pszPropName)
{
	if (pszPropName == NULL)
		return;

	m_strRelevancyPropName = pszPropName;
}

IPropertyBase* IPropertyBase::GetRelevancyProp()
{
	return m_pRelevancyProp;
}

void IPropertyBase::SetRelevancyProp(IPropertyBase *pszProp)
{
	if (pszProp == NULL)
		return;

	m_pRelevancyProp = pszProp;
}
