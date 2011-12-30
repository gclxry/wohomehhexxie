
#pragma once
#include "IFeatureObject.h"
#include "IPropertySkinManager.h"
#include "IWindowBase.h"
#include "CUiXmlWrite.h"

string PathHelper(char *pszFileName);

OBJECT_TYPE_ID PropStringToType(string strPropType);
string PropTypeToString(OBJECT_TYPE_ID propType);
void ResetObjectId(IFeatureObject *pSetObj, IPropertySkinManager* pSkinPropMgr, char *pszBase);
// 创建一个属性，如果这个属性在 group 中已经有了，就返回这个属性，如果没有
IPropertyBase* CreateResourcePropetry(IPropertySkinManager* pSkinPropMgr, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
bool FileExists(const char *pszFilePath);

// 设置IWindowBase的 objectname ，objectId
void ResetWindowBaseInfo(IWindowBase *pWndBase);

void AddIntAttrToNode(CNode* pNode, const char* pszAttrName, int nInt);
