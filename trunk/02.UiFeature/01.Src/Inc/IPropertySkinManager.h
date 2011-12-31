//////////////////////////////////////////////////////////////////////////
// 当前皮肤所有窗口中所有控件的属性管理类

#pragma once
#include "IPropertyBase.h"
#include "IPropertyWindow.h"

class IPropertySkinManager
{
public:
	// 解析Resource.xml
	virtual bool BD_TranslateResourceXml(char *pszXmlPath) = 0;
	// 解析Controls.xml
	virtual bool BD_TranslateControlsXml(char *pszXmlPath) = 0;
	// 解析Windows.xml
	virtual bool BD_TranslateWindowsXml(char *pszXmlPath) = 0;
	// 解析Layout.xml
	virtual bool BD_TranslateLayoutXml(char *pszXmlPath) = 0;
	// 得到Layout.xml队列
	virtual ONE_RESOURCE_PROP_MAP* BD_GetWindowPropMap() = 0;

	// 清空4个xml文件的属性队列
	virtual void ReleaseSkinManagerPropetry() = 0;

//////////////////////////////////////////////////////////////////////////
	// 初始化Window皮肤
	virtual IPropertyWindow* PG_InitWindowSkin(const char *pszSkinPath, const char *pszWndName) = 0;
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
