
#include "StdAfx.h"
#include "..\..\Inc\ICommonFun.h"

string GetDllPath(char *pszDllName)
{
	string strPath = "";
	if (pszDllName != NULL)
	{
		char szPath[MAX_PATH + 1];
		memset(szPath, 0, MAX_PATH + 1);
		::GetModuleFileNameA(NULL, szPath, MAX_PATH);
		while (strlen(szPath) > 0 && szPath[strlen(szPath) - 1] != '\\')
			szPath[strlen(szPath) - 1] = '\0';

		strPath = szPath;
		strPath += pszDllName;
	}

	return strPath;
}

OBJECT_TYPE_ID PropStringToType(string strPropType)
{
	if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_FONT_NAME) == 0)
	{
		return PT_FONT;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_STRING_NAME) == 0)
	{
		return PT_STRING;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_COMBOBOX_NAME) == 0)
	{
		return PT_COMBOBOX;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_IMAGE_NAME) == 0)
	{
		return PT_IMAGE;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_CURSOR_NAME) == 0)
	{
		return PT_CURSOR;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_COLOR_NAME) == 0)
	{
		return PT_COLOR;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_BOOL_NAME) == 0)
	{
		return PT_BOOL;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_INT_NAME) == 0)
	{
		return PT_INT;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_GROUP_NAME) == 0)
	{
		return PT_GROUP;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_CONTROL_NAME) == 0)
	{
		return PT_CONTROL;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_WINDOW_NAME) == 0)
	{
		return PT_WINDOW;
	}

	return PT_NONE;
}

string PropTypeToString(OBJECT_TYPE_ID propType)
{
	string strType("");
	switch (propType)
	{
	case PT_BOOL:
		strType = PROP_TYPE_BOOL_NAME;
		break;

	case PT_COLOR:
		strType = PROP_TYPE_COLOR_NAME;
		break;

	case PT_COMBOBOX:
		strType = PROP_TYPE_COMBOBOX_NAME;
		break;

	case PT_CURSOR:
		strType = PROP_TYPE_CURSOR_NAME;
		break;

	case PT_FONT:
		strType = PROP_TYPE_FONT_NAME;
		break;

	case PT_IMAGE:
		strType = PROP_TYPE_IMAGE_NAME;
		break;

	case PT_INT:
		strType = PROP_TYPE_INT_NAME;
		break;

	case PT_STRING:
		strType = PROP_TYPE_STRING_NAME;
		break;

	case PT_GROUP:
		strType = PROP_TYPE_GROUP_NAME;
		break;

	case PT_CONTROL:
		strType = PROP_TYPE_CONTROL_NAME;
		break;

	case PT_WINDOW:
		strType = PROP_TYPE_WINDOW_NAME;
		break;

	default:
		break;
	}

	return strType;
}

void ResetObjectId(IFeatureObject *pSetObj, IPropertySkinManager* pSkinPropMgr, char *pszBase)
{
	if (pSetObj == NULL || pSkinPropMgr == NULL || pszBase == NULL)
		return;

	char szId[1024];
	memset(szId, 0, 1024);
	sprintf_s(szId, 1023, "%s.%s%d", pszBase, pSetObj->GetObjectType(), pSkinPropMgr->GetNewId());
	pSetObj->SetObjectId(szId);
}

IPropertyBase* CreateResourcePropetry(IPropertySkinManager* pSkinPropMgr, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo)
{
	if (pSkinPropMgr == NULL || pGroup == NULL || pszPropName == NULL || propType <= PT_NONE || propType >= PT_LAST || strlen(pszPropName) <= 0)
		return NULL;

	GROUP_PROP_VEC *pChildGroup = pGroup->GetPropVec();
	if (pChildGroup == NULL)
		return NULL;

	IPropertyBase* pPropBase = NULL;
	for (GROUP_PROP_VEC::iterator pPropItem = pChildGroup->begin(); pPropItem != pChildGroup->end(); pPropItem++)
	{
		pPropBase = *pPropItem;
		if (pPropBase == NULL || pPropBase->GetObjectName() == NULL)
			continue;

		if (lstrcmpiA(pPropBase->GetObjectName(), pszPropName) == 0)
		{
			if (propType == pPropBase->GetObjectTypeId())
			{
				// 找到了已经设置的属性
				pPropBase->SetObjectInfo(pszPropInfo);
				return pPropBase;
			}
			else
			{
				// 属性名字一样，但属性类型不一样，非法
				pChildGroup->erase(pPropItem);
			}
			break;
		}
	}

	pPropBase = pSkinPropMgr->CreateEmptyBaseProp(propType);
	if (pPropBase == NULL)
		return NULL;

	pPropBase->SetObjectName(pszPropName);
	pPropBase->SetObjectInfo(pszPropInfo);
	// 设置ObjectID
	ResetObjectId((IFeatureObject*)pPropBase, pSkinPropMgr, (char*)pGroup->GetObjectId());
	return pPropBase;
}
