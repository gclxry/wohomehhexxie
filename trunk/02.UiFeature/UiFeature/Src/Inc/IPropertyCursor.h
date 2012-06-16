//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"
#include "IPropertyCursorBase.h"

class IWindowBase;
class IPropertyCursor : public IPropertyBase
{
public:
	// 是否为合法数据
	virtual bool IsRightData() = 0;
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// 写入xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	virtual const char * GetCursorBaseName() = 0;

	// 设置鼠标信息
	virtual void SetCursorBaseProp(IPropertyCursorBase *pCursorProp) = 0;
	virtual IPropertyCursorBase* GetCursorBaseProp() = 0;
};
