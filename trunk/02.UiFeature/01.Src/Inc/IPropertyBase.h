//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "CUiXmlParser.h"

// 属性类型
enum PROP_TYPE 
{
	PT_NONE	= 0,
	PT_BOOL	= 1,
	PT_COLOR,
	PT_COMBOBOX,
	PT_CURSOR,
	PT_FONT,
	PT_IMAGE,
	PT_INT,
	PT_STRING,
	PT_GROUP
};

#define PROP_TYPE_BOOL_NAME						"bool"
#define PROP_TYPE_COLOR_NAME					"color"
#define PROP_TYPE_COMBOBOX_NAME					"combobox"
#define PROP_TYPE_CURSOR_NAME					"cursor"
#define PROP_TYPE_FONT_NAME						"font"
#define PROP_TYPE_IMAGE_NAME					"image"
#define PROP_TYPE_INT_NAME						"int"
#define PROP_TYPE_STRING_NAME					"string"
#define PROP_TYPE_GROUP_NAME					"group"

// 语言种类
enum AREA_TYPE
{
	AT_NONE	= 0,
	// 中文简体
	AT_CN		= 1,
	// 中文繁体
	AT_CN_TW	= 2,
	// 英文
	AT_EN		= 3,
	// 日文
	AT_JP		= 4,
	// 德文
	AT_GE		= 5,
	AT_LAST		= 6
};

// string 队列
typedef vector<string>							STRING_VEC;

class IPropertyBase
{
public:
	// 是否为合法数据
	virtual bool IsRightData() = 0;
	// 取得属性类型
	virtual PROP_TYPE GetPropType() = 0;
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode) = 0;

};
