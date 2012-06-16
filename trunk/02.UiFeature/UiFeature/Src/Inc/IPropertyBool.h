//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

class IPropertyBool : public IPropertyBase
{
public:
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	virtual void SetValue(bool bBoolData) = 0;
	virtual bool GetValue() = 0;
};
