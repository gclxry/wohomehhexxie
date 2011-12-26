
#pragma once
#include "IFeatureObject.h"
#include "IPropertySkinManager.h"

string GetDllPath(char *pszDllName);

OBJECT_TYPE_ID PropStringToType(string strPropType);
string PropTypeToString(OBJECT_TYPE_ID propType);
void ResetObjectId(IFeatureObject *pSetObj, IPropertySkinManager* pSkinPropMgr, char *pszBase);
// 创建一个属性，如果这个属性在 group 中已经有了，就返回这个属性，如果没有
IPropertyBase* CreateResourcePropetry(IPropertySkinManager* pSkinPropMgr, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);