//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"
#include "IPropertyFontBase.h"

class IPropertyFont : public IPropertyBase
{
public:
	// 是否为合法数据
	virtual bool IsRightData() = 0;
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// 写入xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	virtual const char * GetFontBaseName() = 0;

	// 设置字体信息
	virtual void SetFontBaseProp(IPropertyFontBase *pFontProp) = 0;
	virtual IPropertyFontBase* GetFontBaseProp() = 0;

	// 绘制文字
	virtual bool DrawFontText(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct) = 0;

	// 设置图片文字重绘标志，设置完成后，将在下次绘制的时候重新创建图片文字
	virtual void SetPictureTextRedrawSign() = 0;

	// 取得绘制文字的矩形大小
	virtual bool GetTextDrawSize(const char* pszDrawText, SIZE &OutSize) = 0;
};
