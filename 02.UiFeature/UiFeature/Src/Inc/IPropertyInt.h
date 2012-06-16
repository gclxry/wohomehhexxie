//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

// int 在Builder中的值范围：-(0x7FFFFFFF), 0x7FFFFFFF
class IPropertyInt : public IPropertyBase
{
public:
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// 写入xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	virtual void SetValue(int nValue) = 0;
	virtual int GetValue() = 0;
};
