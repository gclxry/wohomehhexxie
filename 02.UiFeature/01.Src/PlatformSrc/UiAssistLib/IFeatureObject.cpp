
#include "stdafx.h"
#include "..\..\Inc\IFeatureObject.h"
#include "..\..\Inc\ICommonFun.h"


IFeatureObject::IFeatureObject()
{
	m_strObjId = "NO_OBJECT_ID";
	m_strObjType = "NO_OBJECT_TYPE_NAME";
	m_strObjName = "";
	m_strObjInfo = "NO_OBJECT_INFO";
	m_bIsActiveProp = false;
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
	else
		m_strObjId = "";
}

const char* IFeatureObject::GetObjectType()
{
	return (m_strObjType.c_str());
}

void IFeatureObject::SetObjectType(const char* pszObjType)
{
	if (pszObjType != NULL)
		m_strObjType = pszObjType;
	else
		m_strObjType = "";
}

const char* IFeatureObject::GetObjectName()
{
	return (m_strObjName.c_str());
}

void IFeatureObject::SetObjectName(const char* pszObjName)
{
	if (pszObjName != NULL)
		m_strObjName = pszObjName;
	else
		m_strObjName = "";
}

const char* IFeatureObject::GetObjectInfo()
{
	return (m_strObjInfo.c_str());
}

void IFeatureObject::SetObjectInfo(const char* pszObjInfo)
{
	if (pszObjInfo != NULL)
		m_strObjInfo = pszObjInfo;
	else
		m_strObjInfo = "";
}

OBJECT_TYPE_ID IFeatureObject::GetObjectTypeId()
{
	return PropStringToType(m_strObjType);
}

void IFeatureObject::SetActivePropetry(bool bIsActive)
{
	m_bIsActiveProp = bIsActive;
}

bool IFeatureObject::GetActivePropetry()
{
	return m_bIsActiveProp;
}
