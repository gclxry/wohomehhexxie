//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

class IPropertyBool : public IPropertyBase
{
public:
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// 写入xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	virtual void SetValue(bool bBoolData) = 0;
	virtual bool GetValue() = 0;
};
