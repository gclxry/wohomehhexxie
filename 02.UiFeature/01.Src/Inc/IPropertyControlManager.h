//////////////////////////////////////////////////////////////////////////
// 一个控件的属性管理类

#pragma once

class IPropertyControlManager
{
public:
	virtual void CreatePropertyGroup() = 0;
//	virtual IPropertyBase* CreateProperyt(GROUP* pGroup, CONTROL_PROPERTY_TYPE cptType, char *pPropName, char *pPropInfo, WPARAM wPropParam, LPARAM lPropParam) = 0;
};
