
#include "stdafx.h"
#include "..\..\Inc\IPropertyBase.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyBase::IPropertyBase()
{
	m_strPropId = "";
}

IPropertyBase::~IPropertyBase()
{

}

// ÊôÐÔ ID ×Ö·û´®
const char* IPropertyBase::GetPropId()
{
	return (m_strPropId.c_str());
}

void IPropertyBase::SetPropId(const char* pszPropId)
{
	if (pszPropId != NULL)
	{
		m_strPropId = pszPropId;
	}
}
