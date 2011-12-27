//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

class IPropertyInt : public IPropertyBase
{
public:
	IPropertyInt();
	virtual ~IPropertyInt();

	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

private:
	int m_nIntData;
};
