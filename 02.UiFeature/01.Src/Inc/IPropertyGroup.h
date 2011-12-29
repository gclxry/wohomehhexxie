//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// Group �е������б�
typedef vector<IPropertyBase*>		GROUP_PROP_VEC;

class IPropertyGroup : public IPropertyBase
{
public:
	IPropertyGroup();
	virtual ~IPropertyGroup();

	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);


public:
	// ȡ��Group�µ������б�
	GROUP_PROP_VEC* GetPropVec();
	// ׷��һ������
	void AppendProperty(IPropertyBase* pProperty);

private:
	GROUP_PROP_VEC m_PropVec;
};
