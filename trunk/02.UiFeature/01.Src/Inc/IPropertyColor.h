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
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);

};
