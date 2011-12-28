
#include "StdAfx.h"
#include "..\..\Inc\ICommonFun.h"

string PathHelper(char *pszDllName)
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
		return OTID_FONT;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_STRING_NAME) == 0)
	{
		return OTID_STRING;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_COMBOBOX_NAME) == 0)
	{
		return OTID_COMBOBOX;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_IMAGE_NAME) == 0)
	{
		return OTID_IMAGE;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_CURSOR_NAME) == 0)
	{
		return OTID_CURSOR;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_COLOR_NAME) == 0)
	{
		return OTID_COLOR;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_BOOL_NAME) == 0)
	{
		return OTID_BOOL;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_INT_NAME) == 0)
	{
		return OTID_INT;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_GROUP_NAME) == 0)
	{
		return OTID_GROUP;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_CONTROL_NAME) == 0)
	{
		return OTID_CONTROL;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_WINDOW_NAME) == 0)
	{
		return OTID_WINDOW;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_COLOR_BASE_NAME) == 0)
	{
		return OTID_COLOR_BASE;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_CURSOR_BASE_NAME) == 0)
	{
		return OTID_CURSOR_BASE;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_FONT_BASE_NAME) == 0)
	{
		return OTID_FONT_BASE;
	}
	else if (lstrcmpiA(strPropType.c_str(), PROP_TYPE_IMAGE_BASE_NAME) == 0)
	{
		return OTID_IMAGE_BASE;
	}

	return OTID_NONE;
}

string PropTypeToString(OBJECT_TYPE_ID propType)
{
	string strType("");
	switch (propType)
	{
	case OTID_BOOL:
		strType = PROP_TYPE_BOOL_NAME;
		break;

	case OTID_COLOR:
		strType = PROP_TYPE_COLOR_NAME;
		break;

	case OTID_COMBOBOX:
		strType = PROP_TYPE_COMBOBOX_NAME;
		break;

	case OTID_CURSOR:
		strType = PROP_TYPE_CURSOR_NAME;
		break;

	case OTID_FONT:
		strType = PROP_TYPE_FONT_NAME;
		break;

	case OTID_IMAGE:
		strType = PROP_TYPE_IMAGE_NAME;
		break;

	case OTID_INT:
		strType = PROP_TYPE_INT_NAME;
		break;

	case OTID_STRING:
		strType = PROP_TYPE_STRING_NAME;
		break;

	case OTID_GROUP:
		strType = PROP_TYPE_GROUP_NAME;
		break;

	case OTID_CONTROL:
		strType = PROP_TYPE_CONTROL_NAME;
		break;

	case OTID_WINDOW:
		strType = PROP_TYPE_WINDOW_NAME;
		break;

	case OTID_COLOR_BASE:
		strType = PROP_TYPE_COLOR_BASE_NAME;
		break;

	case OTID_CURSOR_BASE:
		strType = PROP_TYPE_CURSOR_BASE_NAME;
		break;

	case OTID_FONT_BASE:
		strType = PROP_TYPE_FONT_BASE_NAME;
		break;

	case OTID_IMAGE_BASE:
		strType = PROP_TYPE_IMAGE_BASE_NAME;
		break;

	default:
		break;
	}

	return strType;
}

void ResetObjectId(IFeatureObject *pSetObj, IPropertySkinManager* pSkinPropMgr, char *pszBase)
{
	if (pSetObj == NULL || pSkinPropMgr == NULL)
		return;

	char szId[1024];
	memset(szId, 0, 1024);

	if (pszBase != NULL)
		sprintf_s(szId, 1023, "%s.%s%d", pszBase, pSetObj->GetObjectType(), pSkinPropMgr->GetNewId());
	else
		sprintf_s(szId, 1023, "%s%d", pSetObj->GetObjectType(), pSkinPropMgr->GetNewId());

	pSetObj->SetObjectId(szId);
}

// 创建一个属性，如果这个属性在 group 中已经有了，就返回这个属性，如果没有
IPropertyBase* CreateResourcePropetry(IPropertySkinManager* pSkinPropMgr, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo)
{
	if (pSkinPropMgr == NULL || pGroup == NULL || pszPropName == NULL || propType <= OTID_NONE || propType >= OTID_LAST || strlen(pszPropName) <= 0)
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

	pGroup->AppendProperty(pPropBase);
	return pPropBase;
}
