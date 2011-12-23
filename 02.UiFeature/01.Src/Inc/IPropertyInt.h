//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

struct INT_PROP
{
	// ��������
	int nPropId;
	string strName;
	int nIntData;
};

class IPropertyInt : public IPropertyBase
{
public:
	IPropertyInt();
	~IPropertyInt();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ȡ����������
	virtual PROP_TYPE GetPropType();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

private:
	INT_PROP m_IntProp;
};
