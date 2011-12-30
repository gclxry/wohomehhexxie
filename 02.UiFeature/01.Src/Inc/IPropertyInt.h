//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

class IPropertyInt : public IPropertyBase
{
public:
	IPropertyInt();
	virtual ~IPropertyInt();

	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

	void SetValue(int nValue);
	int GetValue();
private:
	int m_nIntData;
};
