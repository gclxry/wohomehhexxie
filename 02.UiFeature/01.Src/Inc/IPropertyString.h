//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

typedef map<AREA_TYPE, string>		STRING_MAP;
// String属性
struct STRING_PROP
{
	// 属性名称
	string strName;
	string strPropInfo;
	string strDefaultString;
	AREA_TYPE nDefaultArea;
	STRING_MAP StringMap;
};

class IPropertyString : public IPropertyBase
{
public:
	IPropertyString();
	virtual ~IPropertyString();

	// 是否为合法数据
	virtual bool IsRightData();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

	// 默认显示文字
	const char* GetString();
	void SetString(char* pszString);
	void SetArea(AREA_TYPE areaType);

private:
	void Clear();
	void ResetDefaultString();

private:
	STRING_PROP m_StringProp;
};
