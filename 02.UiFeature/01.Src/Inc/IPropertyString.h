//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

typedef map<AREA_TYPE, string>		STRING_MAP;
// String����
struct STRING_PROP
{
	// ��������
	int nPropId;
	string strName;
	string strPropInfo;
	string strDefaultString;
	AREA_TYPE nDefaultArea;
	STRING_MAP StringMap;
};

class IPropertyString : public IPropertyBase
{
public:
	IPropertyString();
	~IPropertyString();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ȡ����������
	virtual PROP_TYPE GetPropType();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

	// Ĭ����ʾ����
	const char* GetString();
	void SetString(char* pszString);
	void SetArea(AREA_TYPE areaType);

private:
	void Clear();
	void ResetDefaultString();

private:
	STRING_PROP m_StringProp;
};
