//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

class IPropertyColor : public IPropertyBase
{
public:
	IPropertyColor();
	virtual ~IPropertyColor();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ȡ����������
	virtual PROP_TYPE GetPropType();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

};
