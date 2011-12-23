//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

// Group 中的属性列表
typedef vector<IPropertyBase*>		GROUP_PROP_VEC;

struct GROUP_PROP
{
	// 属性名称
	int nPropId;
	string strName;
};

class IPropertyGroup : public IPropertyBase
{
public:
	IPropertyGroup();
	~IPropertyGroup();

	// 是否为合法数据
	virtual bool IsRightData();
	// 取得属性类型
	virtual PROP_TYPE GetPropType();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

	// 取得Group下的属性列表
	GROUP_PROP_VEC* GetPropVec();

private:
	GROUP_PROP m_GroupProp;
	GROUP_PROP_VEC m_PropVec;
};
