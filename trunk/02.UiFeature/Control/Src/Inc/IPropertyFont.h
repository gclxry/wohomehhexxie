//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"
#include "IPropertyFontBase.h"

class IPropertyFont : public IPropertyBase
{
public:
	IPropertyFont();
	virtual ~IPropertyFont();

	// 是否为合法数据
	virtual bool IsRightData();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// 写入xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

	const char * GetFontBaseName();

	// 设置字体信息
	void SetFontBaseProp(IPropertyFontBase *pFontProp);
	IPropertyFontBase* GetFontBaseProp();

	// 绘制文字
	bool DrawFontText(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct);

private:
	void SetNeedRedraw();
};
