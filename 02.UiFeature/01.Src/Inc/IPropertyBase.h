//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "CUiXmlParser.h"

// ��������
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

// ��������
enum AREA_TYPE
{
	AT_NONE	= 0,
	// ���ļ���
	AT_CN		= 1,
	// ���ķ���
	AT_CN_TW	= 2,
	// Ӣ��
	AT_EN		= 3,
	// ����
	AT_JP		= 4,
	// ����
	AT_GE		= 5,
	AT_LAST		= 6
};

// string ����
typedef vector<string>							STRING_VEC;

class IPropertyBase
{
public:
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ȡ����������
	virtual PROP_TYPE GetPropType() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode) = 0;

};
