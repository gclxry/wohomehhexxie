
#include "stdafx.h"
#include "..\..\Inc\IFeatureObject.h"
#include "..\..\Inc\ICommonFun.h"


IFeatureObject::IFeatureObject()
{
	::CoInitialize(NULL);
	m_strObjId = "NO_OBJECT_ID";
	m_strObjType = "NO_OBJECT_TYPE_NAME";
	m_strObjName = "";
	m_strObjInfo = "NO_OBJECT_INFO";
	m_bIsActiveProp = false;

	GUID guid;
	if (::CoCreateGuid(&guid) == S_OK)
	{
		char szObjeId[MAX_PATH];
		memset(szObjeId, 0, sizeof(szObjeId));
		sprintf_s(szObjeId, sizeof(szObjeId), "%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4],
			guid.Data4[5], guid.Data4[6], guid.Data4[7]);

		m_strObjId = szObjeId;
	}
}

IFeatureObject::~IFeatureObject()
{

}

const char* IFeatureObject::GetObjectId()
{
	return (m_strObjId.c_str());
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
