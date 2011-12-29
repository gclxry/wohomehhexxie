//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

// Group 中的属性列表
typedef vector<IPropertyBase*>		GROUP_PROP_VEC;

class IPropertyGroup : public IPropertyBase
{
public:
	IPropertyGroup();
	virtual ~IPropertyGroup();

	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);


public:
	// 取得Group下的属性列表
	GROUP_PROP_VEC* GetPropVec();
	// 追加一个属性
	void AppendProperty(IPropertyBase* pProperty);

private:
	GROUP_PROP_VEC m_PropVec;
};
