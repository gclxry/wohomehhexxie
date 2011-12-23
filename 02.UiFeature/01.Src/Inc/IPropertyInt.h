//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

struct INT_PROP
{
	// 属性名称
	int nPropId;
	string strName;
	int nIntData;
};

class IPropertyInt : public IPropertyBase
{
public:
	IPropertyInt();
	~IPropertyInt();

	// 是否为合法数据
	virtual bool IsRightData();
	// 取得属性类型
	virtual PROP_TYPE GetPropType();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

private:
	INT_PROP m_IntProp;
};
