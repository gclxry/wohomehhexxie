//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

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

};
