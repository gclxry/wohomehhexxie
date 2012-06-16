//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

class IWindowBase;
class IPropertyCursorBase : public IPropertyBase
{
public:
	// 是否为合法数据
	virtual bool IsRightData() = 0;
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// 写入xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	// 设置系统光标
	virtual void SetSystemCursor(bool bIsSysCursor) = 0;
	// 是否为系统光标
	virtual bool IsSystemCursor() = 0;

	// 设置光标ID
	virtual void SetCursorId(int nId) = 0;
	// 得到光标id
	virtual int GetCursorId() = 0;
};
