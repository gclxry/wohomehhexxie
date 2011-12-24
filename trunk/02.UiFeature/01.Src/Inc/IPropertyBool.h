//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

struct BOOL_PROP
{
	// 属性名称
	string strName;
	string strPropInfo;
	bool bBoolData;
};

class IPropertyBool : public IPropertyBase
{
public:
	IPropertyBool();
	virtual ~IPropertyBool();

	// 是否为合法数据
	virtual bool IsRightData();
	// 取得属性类型
	virtual PROP_TYPE GetPropType();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

private:
	BOOL_PROP m_BoolProp;
};
