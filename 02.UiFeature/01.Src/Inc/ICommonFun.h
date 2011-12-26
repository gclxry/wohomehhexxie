
#pragma once
#include "IFeatureObject.h"
#include "IPropertySkinManager.h"

string GetDllPath(char *pszDllName);

OBJECT_TYPE_ID PropStringToType(string strPropType);
string PropTypeToString(OBJECT_TYPE_ID propType);
void ResetObjectId(IFeatureObject *pSetObj, IPropertySkinManager* pSkinPropMgr, char *pszBase);
// ����һ�����ԣ������������� group ���Ѿ����ˣ��ͷ���������ԣ����û��
IPropertyBase* CreateResourcePropetry(IPropertySkinManager* pSkinPropMgr, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);