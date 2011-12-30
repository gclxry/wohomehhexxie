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
	// д��xml
	virtual bool AppendToXmlNode(CXmlStreamWrite &XmlStrObj, CNode* pParentXmlNode);

public:
	void SetValue(bool bBoolData);
	bool GetValue();

private:
	bool m_bBoolData;
};
