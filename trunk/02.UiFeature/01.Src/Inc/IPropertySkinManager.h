//////////////////////////////////////////////////////////////////////////
// 当前皮肤所有窗口中所有控件的属性管理类

#pragma once
#include "IPropertyWindowManager.h"
#include "IPropertyBase.h"

class IPropertySkinManager
{
public:

	// 初始化Window皮肤
	virtual IPropertyGroup* InitWindowSkin(const char *pszSkinPath, const char *pszWndName) = 0;
//	// 查找指定的属性
//	virtual IPropertyBase* FindBaseProperty(OBJECT_TYPE_ID propType, const char* pszPropId) = 0;
//	virtual IPropertyBase* FindBaseProperty(const char* pszPropType, const char* pszPropId) = 0;
	// 设置显示的语言种类
	virtual void SetArea(AREA_TYPE areaType) = 0;
	// 创建一个属性，并将次属性放入队列
	virtual IPropertyBase* CreateEmptyBaseProp(OBJECT_TYPE_ID propType) = 0;
	// 取得ID号
	virtual int GetNewId() = 0;
};
