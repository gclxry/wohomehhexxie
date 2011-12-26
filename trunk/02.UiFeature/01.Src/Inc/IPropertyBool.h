//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

struct BOOL_PROP
{
	// ��������
	string strName;
	string strPropInfo;
	bool bBoolData;
};

class IPropertyBool : public IPropertyBase
{
public:
	IPropertyBool();
	virtual ~IPropertyBool();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

public:
	void SetValue(bool bBoolData);
	bool GetValue();

private:
	BOOL_PROP m_BoolProp;
};
