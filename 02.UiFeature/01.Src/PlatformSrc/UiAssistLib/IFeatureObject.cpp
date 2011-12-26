
#include "stdafx.h"
#include "..\..\Inc\IFeatureObject.h"
#include "..\..\Inc\ICommonFun.h"


IFeatureObject::IFeatureObject()
{
	m_strObjId = "NO_OBJECT_ID";
	m_strObjType = "NO_OBJECT_TYPE_NAME";
	m_strObjName = "NO_OBJECT_NAME";
	m_strObjInfo = "NO_OBJECT_INFO";
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
	if (pszObjId != NULL)
		m_strObjId = pszObjId;
}

const char* IFeatureObject::GetObjectType()
{
	return (m_strObjType.c_str());
}

void IFeatureObject::SetObjectType(const char* pszObjType)
{
	if (pszObjType != NULL)
		m_strObjType = pszObjType;
}

const char* IFeatureObject::GetObjectName()
{
	return (m_strObjName.c_str());
}

void IFeatureObject::SetObjectName(const char* pszObjName)
{
	if (pszObjName != NULL)
		m_strObjName = pszObjName;
}

const char* IFeatureObject::GetObjectInfo()
{
	return (m_strObjInfo.c_str());
}

void IFeatureObject::SetObjectInfo(const char* pszObjInfo)
{
	if (pszObjInfo != NULL)
		m_strObjInfo = pszObjInfo;
}

OBJECT_TYPE_ID IFeatureObject::GetObjectTypeId()
{
	return PropStringToType(m_strObjType);
}
