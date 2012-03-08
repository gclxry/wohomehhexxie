//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"
#include "IPropertyCursorBase.h"

class IWindowBase;
class IPropertyCursor : public IPropertyBase
{
public:
	IPropertyCursor();
	virtual ~IPropertyCursor();

	// 是否为合法数据
	virtual bool IsRightData();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// 写入xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

	const char * GetCursorBaseName();

	// 设置鼠标信息
	void SetCursorBaseProp(IPropertyCursorBase *pCursorProp);
	IPropertyCursorBase* GetCursorBaseProp();

	// 显示鼠标手势
	bool ShowCursor(IWindowBase *pWndBase);
	// 恢复鼠标手势
	bool RecoverCursor(IWindowBase *pWndBase);
};
