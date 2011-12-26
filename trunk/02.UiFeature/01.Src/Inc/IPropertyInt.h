//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

struct INT_PROP
{
	// ��������
	string strName;
	string strPropInfo;
	int nIntData;
};

class IPropertyInt : public IPropertyBase
{
public:
	IPropertyInt();
	virtual ~IPropertyInt();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

private:
	INT_PROP m_IntProp;
};
