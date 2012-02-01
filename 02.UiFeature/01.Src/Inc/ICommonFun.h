
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
IPropertyBase* CreateResourcePropetry(IFeatureObject *pOwnerObj, IPropertySkinManager* pSkinPropMgr, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
bool FileExists(const char *pszFilePath);

// 设置IWindowBase的 objectname ，objectId
void ResetWindowBaseInfo(IWindowBase *pWndBase);
// 向一个xml节点插入一个int属性
void AddIntAttrToNode(CUiXmlWriteNode* pNode, const char* pszAttrName, int nInt);
void DebugInfoOutput(char *pszFormat, ...);
// 从一个属性组中查找名为 "@Object_Name" 的属性
IPropertyString* FindObjectNameProperty(IPropertyGroup *pGroupProp);

#ifndef _DEBUG
#define DEBUG_INFO
#else
#define DEBUG_INFO				DebugInfoOutput
#endif
