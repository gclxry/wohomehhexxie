//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

class IPropertyBool : public IPropertyBase
{
public:
	IPropertyBool();
	virtual ~IPropertyBool();

	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);

public:
	void SetValue(bool bBoolData);
	bool GetValue();

private:
	bool m_bBoolData;
};
