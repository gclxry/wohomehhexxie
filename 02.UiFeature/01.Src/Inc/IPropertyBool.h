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
	// ȡ����������
	virtual PROP_TYPE GetPropType();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

private:
	BOOL_PROP m_BoolProp;
};
