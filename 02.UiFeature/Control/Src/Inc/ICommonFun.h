
#pragma once
#include "IFeatureObject.h"
#include "IPropertySkinManager.h"
#include "IWindowBase.h"
#include "CUiXmlWrite.h"

string PathHelper(char *pszFileName);

OBJECT_TYPE_ID PropStringToType(string strPropType);
string PropTypeToString(OBJECT_TYPE_ID propType);
void ResetObjectId(IFeatureObject *pSetObj, IPropertySkinManager* pSkinPropMgr, char *pszBase);
// ����һ�����ԣ������������� group ���Ѿ����ˣ��ͷ���������ԣ����û��
IPropertyBase* CreateResourcePropetry(IFeatureObject *pOwnerObj, IPropertySkinManager* pSkinPropMgr, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
bool FileExists(const char *pszFilePath);

// ����IWindowBase�� objectname ��objectId
void ResetWindowBaseInfo(IWindowBase *pWndBase);
// ��һ��xml�ڵ����һ��int����
void AddIntAttrToNode(CUiXmlWriteNode* pNode, const char* pszAttrName, int nInt);
void DebugInfoOutput(char *pszFormat, ...);
// ��һ���������в�����Ϊ "@Object_Name" ������
IPropertyString* FindObjectNameProperty(IPropertyGroup *pGroupProp);

#ifndef _DEBUG
#define DEBUG_INFO
#else
#define DEBUG_INFO				DebugInfoOutput
#endif
