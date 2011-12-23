//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// Group �е������б�
typedef vector<IPropertyBase*>		GROUP_PROP_VEC;

struct GROUP_PROP
{
	// ��������
	int nPropId;
	string strName;
};

class IPropertyGroup : public IPropertyBase
{
public:
	IPropertyGroup();
	~IPropertyGroup();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ȡ����������
	virtual PROP_TYPE GetPropType();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

	// ȡ��Group�µ������б�
	GROUP_PROP_VEC* GetPropVec();

private:
	GROUP_PROP m_GroupProp;
	GROUP_PROP_VEC m_PropVec;
};
