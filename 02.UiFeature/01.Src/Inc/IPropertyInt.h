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
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

	void SetValue(int nValue);
	int GetValue();
private:
	int m_nIntData;
};
