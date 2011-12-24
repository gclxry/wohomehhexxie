
#include "stdafx.h"
#include "..\..\Inc\IFeatureObject.h"


IFeatureObject::IFeatureObject()
{
	m_strObjId = "";
	m_strObjType = "";
}

IFeatureObject::~IFeatureObject()
{

}

const char* IFeatureObject::GetObjectId()
{
	return (m_strObjId.c_str());
}

void IFeatureObject::SetObjectId(const char* pszObjId)
{
	if (pszObjId != NULL && m_strObjId.size() <= 0)
		m_strObjId = pszObjId;
}

const char* IFeatureObject::GetObjectType()
{
	return (m_strObjType.c_str());
}

void IFeatureObject::SetObjectType(const char* pszObjType)
{
	if (pszObjType != NULL && m_strObjType.size() <= 0)
		m_strObjType = pszObjType;
}
