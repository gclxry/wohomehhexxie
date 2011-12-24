//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// Group �е������б�
typedef vector<IPropertyBase*>		GROUP_PROP_VEC;

struct GROUP_PROP
{
	// ��������
	string strName;
	string strPropInfo;
};

class IPropertyGroup : public IPropertyBase
{
public:
	IPropertyGroup();
	virtual ~IPropertyGroup();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ȡ����������
	virtual PROP_TYPE GetPropType();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);


public:
	// ȡ��Group�µ������б�
	GROUP_PROP_VEC* GetPropVec();
	// ׷��һ������
	void AppendProperty(IPropertyBase* pProperty);

private:
	GROUP_PROP m_GroupProp;
	GROUP_PROP_VEC m_PropVec;
};
