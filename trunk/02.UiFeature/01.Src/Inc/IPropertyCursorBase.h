//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

class IPropertyCursorBase : public IPropertyBase
{
public:
	IPropertyCursorBase();
	virtual ~IPropertyCursorBase();

	// 是否为合法数据
	virtual bool IsRightData();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// 写入xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

	// 是否为系统光标
	bool IsSystemCursor();
	// 设置系统光标
	void SetSystemCursor(bool bIsSysCursor);
	// 设置光标ID
	void SetCursorId(int nId);

private:
	// 是否是系统默认光标
	bool m_bIsSysCursor;
	// 光标ID
	int m_nCursorId;
};
