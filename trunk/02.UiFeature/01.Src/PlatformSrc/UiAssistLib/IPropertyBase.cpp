
#include "stdafx.h"
#include "..\..\Inc\IPropertyBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IUiFeatureKernel.h"

IPropertyBase::IPropertyBase()
{
	SetObjectType("PropertyBase");
	m_pUiKernel = NULL;

	// ������������
	m_strRelevancyPropName = "";
	// ��������
	m_pRelevancyProp = NULL;
	m_pBuilderCtrl = NULL;
}

IPropertyBase::~IPropertyBase()
{

}

void IPropertyBase::SetUiKernel(IUiFeatureKernel *pUiKernel)
{
	if (pUiKernel != NULL)
		m_pUiKernel = pUiKernel;
}

IUiFeatureKernel* IPropertyBase::GetUiKernel()
{
	return m_pUiKernel;
}

bool IPropertyBase::IsRightData()
{
	return (strlen(this->GetObjectName()) > 0);
}

// ��XML�ڵ��ȡ����ֵ�����������Զ���
bool IPropertyBase::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	return true;
}

const char* IPropertyBase::GetRelevancyPropName()
{
	return m_strRelevancyPropName.c_str();
}

void IPropertyBase::SetRelevancyPropName(char *pszPropName)
{
	if (pszPropName == NULL)
	{
		m_strRelevancyPropName = "";
		m_pRelevancyProp = NULL;
		return;
	}

	m_strRelevancyPropName = pszPropName;
}

IPropertyBase* IPropertyBase::GetRelevancyProp()
{
	return m_pRelevancyProp;
}

void IPropertyBase::SetRelevancyProp(IPropertyBase *pszProp)
{
	m_pRelevancyProp = pszProp;

	if (m_pRelevancyProp == NULL)
		m_strRelevancyPropName = "";
	else
		m_strRelevancyPropName = pszProp->GetObjectName();
}

bool IPropertyBase::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
{
	// �������Ч���ԣ���д��XML
	if (!GetActivePropetry())
		return true;

	return true;
}

// ��Builder�н���
void IPropertyBase::EnableInBuilder(bool bEnable)
{
	if (m_pBuilderCtrl != NULL)
		m_pBuilderCtrl->EnableBuilderCtrl(bEnable);
}

void IPropertyBase::SetPropBuilderCtrl(IPropertyBuilderCtrl* pBuilderCtrl)
{
	m_pBuilderCtrl = pBuilderCtrl;
}
