//////////////////////////////////////////////////////////////////////////
// 当前皮肤所有窗口中所有控件的属性管理类

#pragma once
#include "IPropertyWindowManager.h"
#include "IPropertyBase.h"
#include "IPropertyWindow.h"

class IPropertySkinManager
{
public:
	// 解析Resource.xml
	virtual bool BuilderTranslateResourceXml(char *pszXmlPath) = 0;
	// 解析Controls.xml
	virtual bool BuilderTranslateControlsXml(char *pszXmlPath) = 0;
	// 解析Windows.xml
	virtual bool BuilderTranslateWindowsXml(char *pszXmlPath) = 0;
	// 解析Layout.xml
	virtual bool BuilderTranslateLayoutXml(char *pszXmlPath) = 0;

	virtual PROP_BASE_ITEM* BuilderGetWindowPropMap() = 0;

	// 清空属性队列
	virtual void ReleaseSkinManagerPropetry() = 0;

//////////////////////////////////////////////////////////////////////////
	// 初始化Window皮肤
	virtual IPropertyGroup* InitWindowSkin(const char *pszSkinPath, const char *pszWndName) = 0;
//	// 查找指定的属性
//	virtual IPropertyBase* FindBaseProperty(OBJECT_TYPE_ID propType, const char* pszPropId) = 0;
//	virtual IPropertyBase* FindBaseProperty(const char* pszPropType, const char* pszPropId) = 0;
	// 设置显示的语言种类
	virtual void SetArea(AREA_TYPE areaType) = 0;
	// 创建一个属性，并将次属性放入队列
	virtual IPropertyBase* CreateEmptyBaseProp(OBJECT_TYPE_ID propType, char *pszObjectId = NULL) = 0;
	// 取得ID号
	virtual int GetNewId() = 0;
};
