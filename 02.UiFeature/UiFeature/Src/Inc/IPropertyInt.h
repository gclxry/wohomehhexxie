//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// int ��Builder�е�ֵ��Χ��-(0x7FFFFFFF), 0x7FFFFFFF
class IPropertyInt : public IPropertyBase
{
public:
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	virtual void SetValue(int nValue) = 0;
	virtual int GetValue() = 0;
};
