//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// Group �е������б�
typedef CTList				GROUP_PROP_VEC;

class IPropertyGroup : public IPropertyBase
{
public:
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	// ׷��һ������
	virtual void AppendProperty(IPropertyBase* pProperty) = 0;

	// ȡ��Group�µ������б�
	virtual GROUP_PROP_VEC* GetPropVec() = 0;
};
