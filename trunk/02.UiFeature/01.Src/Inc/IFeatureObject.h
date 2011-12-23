
#pragma once

class IFeatureObject
{
public:
	IFeatureObject();
	virtual ~IFeatureObject();

	const char* GetObjectId();
	void SetObjectId(const char* pszObjId);

	const char* GetObjectType();
	void SetObjectType(const char* pszObjType);

private:
	// ID ×Ö·û´®
	string m_strObjId;
	string m_strObjType;
};