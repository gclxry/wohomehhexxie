//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

// 文字显示样式
enum FONT_SHOW_MODE
{
	// 单行显示，超过显示范围末尾不显示...
	FSM_ONE_ROW_NO_POINT	= 0,
	// 单行显示，超过显示范围显示...
	FSM_ONE_ROW_POINT		= 1,
	// 折行显示
	FSM_MULTI_ROW			= 2
};

// 对齐模式
enum FONT_ALIGNING
{
	// 水平靠左/垂直靠上
	FAL_LEFT_TOP		= 0,
	// 水平靠右/垂直靠下
	FAL_RIGHT_BOTTOM	= 1,
	// 水平居中/垂直居中
	FAL_MIDDLE		= 2
};

// 文字特效
enum FONT_EFFECT
{
	FE_NONE			= 0x00000000,
	// 阴影文字
	FE_SHADOW		= 0x00000001,
	// 模糊文字
	FE_OBSCURE		= 0x00000002
};

// 字体属性
struct FONT_PROP
{
	// 字体信息
	LOGFONTA Font;
	// 字体颜色
	COLORREF FontColor;
	// 垂直停靠信息
	FONT_ALIGNING VAligning;
	// 水平停靠信息
	FONT_ALIGNING HAligning;
	// 显示方式
	FONT_SHOW_MODE ShowMode;
	// 文字特效
	UINT FontEffect;
};

class IPropertyFontBase : public IPropertyBase
{
public:
	IPropertyFontBase();
	virtual ~IPropertyFontBase();

	// 是否为合法数据
	virtual bool IsRightData();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// 写入xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

	// 设置字体信息
	void SetFontProp(FONT_PROP *pFontProp);
	FONT_PROP* GetFontProp();

private:
	FONT_PROP m_FontProp;
};
