//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "CUiXmlParser.h"
#include "IFeatureObject.h"
#include "CUiXmlWrite.h"

class IPropertyBase;

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
typedef vector<string>									STRING_VEC;

// 一种属性的队列，如：font、string、image等，KEY：ObjectId
// 一种控件的属性队列，如：Button、CheckBox等，KEY：ObjectId
// 一种窗口的属性队列，KEY：ObjectId
typedef map<string, IPropertyBase*>						ONE_RESOURCE_PROP_MAP;

// 所有种类的属性的队列，KEY：属性类型名称，如：font
// 所有控件种类的属性的队列，KEY：控件类型名称，如：Button
// KEY:ObjectId，所有窗口的管理器map
typedef map<string, ONE_RESOURCE_PROP_MAP*>				RESOURCE_PROP_MAP;

class IPropertyBase : public IFeatureObject
{
public:
	IPropertyBase();
	virtual ~IPropertyBase();

	// 是否为合法数据
	virtual bool IsRightData();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// 写入xml
	virtual bool AppendToXmlNode(CXmlStreamWrite &XmlStrObj, CNode* pParentXmlNode);

	// 关联属性名称
	virtual const char* GetRelevancyPropName();
	virtual void SetRelevancyPropName(char *pszPropName);

	// 关联属性
	virtual IPropertyBase* GetRelevancyProp();
	virtual void SetRelevancyProp(IPropertyBase *pszProp);

private:
	// 关联属性名称
	string m_strRelevancyPropName;
	// 关联属性
	IPropertyBase *m_pRelevancyProp;
};
