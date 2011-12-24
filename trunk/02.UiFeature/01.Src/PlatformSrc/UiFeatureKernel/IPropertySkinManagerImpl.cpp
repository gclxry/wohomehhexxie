
#include "StdAfx.h"
#include <assert.h>
#include "IPropertySkinManagerImpl.h"
#include "CommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IPropertyFont.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyColor.h"
#include "..\..\Inc\IPropertyComboBox.h"
#include "..\..\Inc\IPropertyCursor.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "IPropertyWindowImpl.h"

IPropertySkinManager* IPropertySkinManagerImpl::GetInstance()
{
	static IPropertySkinManagerImpl _PropertySkinManagerInstance;
	return &_PropertySkinManagerInstance;
}

IPropertySkinManagerImpl::IPropertySkinManagerImpl(void)
{
	m_strSkinPath = "";
	m_AllPropMap.clear();
	m_AllCtrlPropMap.clear();
	m_nObjectIdInRes = 1;
	m_nEmptyObjectId = 1;

	m_WndPropMap.clear();
	m_AreaType = AT_CN;

	LoadZipDll();
}

IPropertySkinManagerImpl::~IPropertySkinManagerImpl(void)
{
	SAFE_FREE_LIBRARY(m_hZipModule);
	ReleaseControlsXml();
	ReleaseResourceXml();
}

void IPropertySkinManagerImpl::ReleaseControlsXml()
{
	for (ALL_CONTROL_PROP_MAP::iterator pGroupItem = m_AllCtrlPropMap.begin(); pGroupItem != m_AllCtrlPropMap.end(); pGroupItem++)
	{
		CONTROL_PROP_MAP* pGroup = pGroupItem->second;
		SAFE_DELETE(pGroup);
	}
	m_AllCtrlPropMap.clear();
}

void IPropertySkinManagerImpl::ReleaseResourceXml()
{
	for (ALL_PROP_MAP::iterator pGroupItem = m_AllPropMap.begin(); pGroupItem != m_AllPropMap.end(); pGroupItem++)
	{
		PROP_MAP* pGroup = pGroupItem->second;
		if (pGroup != NULL)
		{
			for (PROP_MAP::iterator pPropItem = pGroup->begin(); pPropItem != pGroup->end(); pPropItem++)
			{
				IPropertyBase* pProp = pPropItem->second;
				ReleaseBaseProp(pProp);
			}
			SAFE_DELETE(pGroup);
		}
	}
	m_AllPropMap.clear();
}

void IPropertySkinManagerImpl::ReleaseBaseProp(IPropertyBase *pCtrlProp)
{
	if (pCtrlProp == NULL)
		return;

	switch (pCtrlProp->GetPropType())
	{
	case PT_BOOL:
		{
			IPropertyBool* pProp = dynamic_cast<IPropertyBool*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case PT_COLOR:
		{
			IPropertyColor* pProp = dynamic_cast<IPropertyColor*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case PT_COMBOBOX:
		{
			IPropertyComboBox* pProp = dynamic_cast<IPropertyComboBox*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case PT_CURSOR:
		{
			IPropertyCursor* pProp = dynamic_cast<IPropertyCursor*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case PT_FONT:
		{
			IPropertyFont* pProp = dynamic_cast<IPropertyFont*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case PT_GROUP:
		{
			IPropertyGroup* pProp = dynamic_cast<IPropertyGroup*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case PT_IMAGE:
		{
			IPropertyImage* pProp = dynamic_cast<IPropertyImage*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case PT_INT:
		{
			IPropertyInt* pProp = dynamic_cast<IPropertyInt*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case PT_STRING:
		{
			IPropertyString* pProp = dynamic_cast<IPropertyString*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	default:
		break;
	}

	SAFE_DELETE(pCtrlProp);
}

// 加载zip文件
void IPropertySkinManagerImpl::LoadZipDll()
{
	m_pZipFile = NULL;
	m_hZipModule = NULL;

	string strPath = GetDllPath(NAME_ZIP_DLL);
	m_hZipModule = ::LoadLibraryA(strPath.c_str());
	if (m_hZipModule == NULL)
		return;

	GETZIPFILEINTERFACE GetZip = (GETZIPFILEINTERFACE)::GetProcAddress(m_hZipModule, "GetZipFileInterface");
	if (GetZip == NULL)
		return;

	m_pZipFile = GetZip();
}

PROP_TYPE IPropertySkinManagerImpl::PropStringToType(string strPropType)
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

	return PT_NONE;
}

string IPropertySkinManagerImpl::PropTypeToString(PROP_TYPE propType)
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

	default:
		break;
	}

	return strType;
}

// 创建一个属性，并将次属性放入队列
IPropertyBase* IPropertySkinManagerImpl::CreateEmptyBaseProp(PROP_TYPE propType)
{
	IPropertyBase* pBaseProp = NULL;
	switch (propType)
	{
	case PT_BOOL:
		{
			IPropertyBool* pProp = new IPropertyBool;
			if (pProp != NULL)
			{
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
					SAFE_DELETE(pProp);
			}
		}
		break;

	case PT_COLOR:
		{
			IPropertyColor* pProp = new IPropertyColor;
			if (pProp != NULL)
			{
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
					SAFE_DELETE(pProp);
			}
		}
		break;

	case PT_COMBOBOX:
		{
			IPropertyComboBox* pProp = new IPropertyComboBox;
			if (pProp != NULL)
			{
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
					SAFE_DELETE(pProp);
			}
		}
		break;

	case PT_CURSOR:
		{
			IPropertyCursor* pProp = new IPropertyCursor;
			if (pProp != NULL)
			{
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
					SAFE_DELETE(pProp);
			}
		}
		break;

	case PT_FONT:
		{
			IPropertyFont* pProp = new IPropertyFont;
			if (pProp != NULL)
			{
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
					SAFE_DELETE(pProp);
			}
		}
		break;

	case PT_GROUP:
		{
			IPropertyGroup* pProp = new IPropertyGroup;
			if (pProp != NULL)
			{
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
					SAFE_DELETE(pProp);
			}
		}
		break;

	case PT_IMAGE:
		{
			IPropertyImage* pProp = new IPropertyImage;
			if (pProp != NULL)
			{
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
					SAFE_DELETE(pProp);
			}
		}
		break;

	case PT_INT:
		{
			IPropertyInt* pProp = new IPropertyInt;
			if (pProp != NULL)
			{
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
					SAFE_DELETE(pProp);
			}
		}
		break;

	case PT_STRING:
		{
			IPropertyString* pProp = new IPropertyString;
			if (pProp != NULL)
			{
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
					SAFE_DELETE(pProp);
			}
		}
		break;

	default:
		break;
	}

	if (pBaseProp != NULL)
	{
		PROP_MAP* pOnePropMap = NULL;
		string strTypeName = PropTypeToString(propType);
		ALL_PROP_MAP::iterator pTypeItem = m_AllPropMap.find(strTypeName);
		if (pTypeItem != m_AllPropMap.end())
		{
			// 找到属性组
			pOnePropMap = pTypeItem->second;
		}
		else
		{
			// 创建属性组
			pOnePropMap = new PROP_MAP;
			if (pOnePropMap == NULL)
			{
				ReleaseBaseProp(pBaseProp);
				return NULL;
			}

			pOnePropMap->clear();
			m_AllPropMap.insert(pair<string, PROP_MAP*>(strTypeName, pOnePropMap));
		}

		if (pOnePropMap != NULL)
		{
			char szObjId[MAX_PATH + 1];
			memset(szObjId, 0, MAX_PATH + 1);
			sprintf_s(szObjId, MAX_PATH, "NO_OBJ_ID_%d", m_nEmptyObjectId++);
			pBaseProp->SetObjectId((const char*)szObjId);

			pOnePropMap->insert(pair<string, IPropertyBase*>(szObjId, pBaseProp));
		}
	}

	return pBaseProp;
}

// 查找指定的属性
IPropertyBase* IPropertySkinManagerImpl::FindBaseProperty(PROP_TYPE propType, const char* pszPropId)
{
	string strType = PropTypeToString(propType);
	return FindBaseProperty(strType.c_str(), pszPropId);
}

IPropertyBase* IPropertySkinManagerImpl::FindBaseProperty(const char* pszPropType, const char* pszPropId)
{
	if (pszPropType == NULL || strlen(pszPropType) <= 0 || pszPropId == NULL || strlen(pszPropId) <= 0 || m_AllPropMap.size() <= 0)
		return NULL;

	string strType = pszPropType;
	ALL_PROP_MAP::iterator pPropTypeItem = m_AllPropMap.find(strType);
	if (pPropTypeItem == m_AllPropMap.end())
		return NULL;

	PROP_MAP* pPropMap = pPropTypeItem->second;
	if (pPropMap == NULL)
		return NULL;

	string strPropId = pszPropId;
	PROP_MAP::iterator pPropItem = pPropMap->find(strPropId);
	if (pPropItem == pPropMap->end())
		return NULL;

	return (pPropItem->second);
}

// 初始化皮肤包
bool IPropertySkinManagerImpl::InitSkinPackage(const char *pszSkinPath)
{
	// TBD，从Builder来和皮肤文件来是不一样的
	if (pszSkinPath == NULL || strlen(pszSkinPath) <= 0 || m_pZipFile == NULL)
		return false;

	// 初始化
	if (m_WndPropMap.size() > 0)
		return true;

//////////////////////////////////////////////////////////////////////////
	// TBD
	char szPath[MAX_PATH + 1];
	memset(szPath, 0, MAX_PATH + 1);
	::GetModuleFileNameA(NULL, szPath, MAX_PATH);
	while (strlen(szPath) > 0 && szPath[strlen(szPath) - 1] != '\\')
		szPath[strlen(szPath) - 1] = '\0';

	string strDir = szPath;
	strDir += SKIN_DATA_DIR;

	string strUfd = szPath;
	strUfd += SKIN_DATA_DIR;
	strUfd += "skintest.ufd";

	m_pZipFile->InitWriteZip((char*)strDir.c_str(), (char*)strUfd.c_str());
	m_pZipFile->WriteToZip(WINDOWS_XML_NAME);
	m_pZipFile->WriteToZip(RESOURCE_XML_NAME);
	m_pZipFile->WriteToZip(LAYOUT_XML_NAME);
	m_pZipFile->WriteToZip(CONTROLS_XML_NAME);
	m_pZipFile->WriteToZip("bk.PNG");
	m_pZipFile->WriteToZip("V5.Dlg.Close.png");
	m_pZipFile->WriteToZip("V5.Dlg.Mini.png");
	m_pZipFile->WriteToZip("V5.Logon.ACDC.png");
	m_pZipFile->WriteToZip("V5.Logon.Set.png");
	m_pZipFile->WriteToZip("V5.LogonBiz.01.jpg");
	m_pZipFile->WriteToZip("V5.LogonBiz.02.png");
	m_pZipFile->WriteToZip("下拉2标注.png");
	m_pZipFile->WriteToZip("下拉菜单效果图_MarkMan.png");
	m_pZipFile->WriteToZip("切图副本.png");
	m_pZipFile->WriteToZip("最新修改.png");
	m_pZipFile->EndWriteZip();
//////////////////////////////////////////////////////////////////////////

	// 从皮肤文件中初始化皮肤队列 TBD
	m_strSkinPath = pszSkinPath;
	if (!m_pZipFile->ReadZipFile(pszSkinPath))
		return false;

	FILE_ITEM * pResurceXml = m_pZipFile->FindUnZipFile(RESOURCE_XML_NAME);
	FILE_ITEM * pControlsXml = m_pZipFile->FindUnZipFile(CONTROLS_XML_NAME);
	FILE_ITEM * pWindowsXml = m_pZipFile->FindUnZipFile(WINDOWS_XML_NAME);
	FILE_ITEM * pLayoutXml = m_pZipFile->FindUnZipFile(LAYOUT_XML_NAME);
	if (pWindowsXml == NULL || pResurceXml == NULL)
		return false;

	// 解读 Resource.xml
	if (!TranslateResourceXml(pResurceXml))
		return false;
	m_pZipFile->RemoveFile(pResurceXml);

	// 解读 Controls.xml
	if (!TranslateControlsXml(pControlsXml))
		return false;
	m_pZipFile->RemoveFile(pControlsXml);

	// 解读 Windows.xml
	if (!TranslateWindowsXml(pWindowsXml))
		return false;
	m_pZipFile->RemoveFile(pWindowsXml);

	// 解析 Layout.xml

	return true;
}

// 初始化皮肤
IPropertyWindow* IPropertySkinManagerImpl::InitWindowSkin(const char *pszSkinPath, const char *pszWndName)
{
	if (pszSkinPath == NULL || strlen(pszSkinPath) <= 0 || pszWndName == NULL || strlen(pszWndName) <= 0)
		return NULL;

	if (!InitSkinPackage(pszSkinPath))
		return NULL;

	string strWndName = pszWndName;
	WND_PROP_MAP::iterator pWndPropItem = m_WndPropMap.find(strWndName);
	if (pWndPropItem == m_WndPropMap.end())
		return NULL;

	IPropertyWindow* pWndProp = pWndPropItem->second;
	return pWndProp;
}

void IPropertySkinManagerImpl::ResetBaseObjectId(int nObjectId)
{
	if (nObjectId >= m_nObjectIdInRes)
		m_nObjectIdInRes = nObjectId + 1;
}

// 取得ID号
int IPropertySkinManagerImpl::GetNewId()
{
	return m_nObjectIdInRes++;
}

// 设置显示的语言种类
void IPropertySkinManagerImpl::SetArea(AREA_TYPE areaType)
{
	ALL_PROP_MAP::iterator pStringItem = m_AllPropMap.find(PROP_TYPE_STRING_NAME);
	if (pStringItem == m_AllPropMap.end())
		return;

	PROP_MAP* pPropMap = pStringItem->second;
	if (pPropMap == NULL)
		return;

	for (PROP_MAP::iterator pPropItem = pPropMap->begin(); pPropItem != pPropMap->end(); pPropItem++)
	{
		IPropertyBase* pProp = pPropItem->second;
		if (pProp == NULL)
			continue;

		IPropertyString *pStringProp = dynamic_cast<IPropertyString*>(pProp);
		if (pStringProp == NULL)
			continue;

		pStringProp->SetArea(areaType);
	}
}

// 解析Resource.xml
bool IPropertySkinManagerImpl::TranslateResourceXml(FILE_ITEM *pResurceXml)
{
	m_AllPropMap.clear();
	if (pResurceXml == NULL || pResurceXml->pFileData == NULL)
		return false;

	XmlState xmlState = { 0 };
	JabberXmlInitState(&xmlState);
	int bytesParsed = JabberXmlParse(&xmlState, (char *)pResurceXml->pFileData, pResurceXml->dwSrcFileLen);
	XmlNode *pResurceRoot  = JabberXmlGetChild(&xmlState.root, "resource");
	if (pResurceRoot != NULL)
	{
		int nItemCount = pResurceRoot->numChild;
		for (int i = 0; i < nItemCount; i++)
		{
			XmlNode* pPropTypeXml = JabberXmlGetNthChildWithoutTag(pResurceRoot, i);
			if (pPropTypeXml != NULL && pPropTypeXml->name != NULL)
			{
				PROP_MAP* pOnePropMap = NULL;
				string strTypeName = pPropTypeXml->name;
				ALL_PROP_MAP::iterator pTypeItem = m_AllPropMap.find(strTypeName);
				if (pTypeItem != m_AllPropMap.end())
				{
					// 找到属性组
					pOnePropMap = pTypeItem->second;
				}
				else
				{
					// 创建属性组
					pOnePropMap = new PROP_MAP;
					if (pOnePropMap == NULL)
						return false;

					pOnePropMap->clear();
					m_AllPropMap.insert(pair<string, CONTROL_PROP_MAP*>(strTypeName, pOnePropMap));
				}

				if (pOnePropMap == NULL)
					return false;

				if (!GeneralCreateBaseProp((char*)strTypeName.c_str(), pPropTypeXml, pOnePropMap))
					return false;
			}
		}
	}
	else
	{
		return false;
	}

	JabberXmlDestroyState(&xmlState);
	return true;
}

bool IPropertySkinManagerImpl::GeneralCreateBaseProp(char *pPropType, XmlNode* pXmlNode, PROP_MAP* pPropMap)
{
	if (pPropType == NULL || pXmlNode == NULL || pPropMap == NULL)
		return false;

	int nItemCount = pXmlNode->numChild;
	for (int i = 0; i < nItemCount; i++)
	{
		XmlNode* pItem = JabberXmlGetNthChildWithoutTag(pXmlNode, i);
		if (pItem != NULL)
		{
			char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
			if (psz_id == NULL)
				return false;

			string strObjId = psz_id;
			PROP_MAP::iterator pPropItem = pPropMap->find(strObjId);
			if (pPropItem != pPropMap->end())
				return false;

			IPropertyBase* pBaseProp = NULL;
			if (lstrcmpiA(pPropType, PROP_TYPE_FONT_NAME) == 0)
			{
				IPropertyFont* pProp = new IPropertyFont;
				if (pProp == NULL)
					return false;
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
				{
					SAFE_DELETE(pProp);
				}
			}
			else if (lstrcmpiA(pPropType, PROP_TYPE_STRING_NAME) == 0)
			{
				IPropertyString* pProp = new IPropertyString;
				if (pProp == NULL)
					return false;
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
				{
					SAFE_DELETE(pProp);
				}
			}
			else if (lstrcmpiA(pPropType, PROP_TYPE_COMBOBOX_NAME) == 0)
			{
				IPropertyComboBox* pProp = new IPropertyComboBox;
				if (pProp == NULL)
					return false;
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
				{
					SAFE_DELETE(pProp);
				}
			}
			else if (lstrcmpiA(pPropType, PROP_TYPE_IMAGE_NAME) == 0)
			{
				IPropertyImage* pProp = new IPropertyImage;
				if (pProp == NULL)
					return false;
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
				{
					SAFE_DELETE(pProp);
				}
			}
			else if (lstrcmpiA(pPropType, PROP_TYPE_CURSOR_NAME) == 0)
			{
				IPropertyCursor* pProp = new IPropertyCursor;
				if (pProp == NULL)
					return false;
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
				{
					SAFE_DELETE(pProp);
				}
			}
			else if (lstrcmpiA(pPropType, PROP_TYPE_COLOR_NAME) == 0)
			{
				IPropertyColor* pProp = new IPropertyColor;
				if (pProp == NULL)
					return false;
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
				{
					SAFE_DELETE(pProp);
				}
			}
			else if (lstrcmpiA(pPropType, PROP_TYPE_BOOL_NAME) == 0)
			{
				IPropertyBool* pProp = new IPropertyBool;
				if (pProp == NULL)
					return false;
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
				{
					SAFE_DELETE(pProp);
				}
			}
			else if (lstrcmpiA(pPropType, PROP_TYPE_INT_NAME) == 0)
			{
				IPropertyInt* pProp = new IPropertyInt;
				if (pProp == NULL)
					return false;
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
				{
					SAFE_DELETE(pProp);
				}
			}
			else if (lstrcmpiA(pPropType, PROP_TYPE_GROUP_NAME) == 0)
			{
				IPropertyGroup* pProp = new IPropertyGroup;
				if (pProp == NULL)
					return false;
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
				{
					SAFE_DELETE(pProp);
				}
			}
			else
			{
				return false;
			}

			if (pBaseProp == NULL)
				return false;

			if (!pBaseProp->ReadResourceXmlProperty(pItem))
			{
				ReleaseBaseProp(pBaseProp);
				return false;
			}

			pPropMap->insert(pair<string, IPropertyBase*>(strObjId, pBaseProp));
		}
	}

	return true;
}

bool IPropertySkinManagerImpl::TranslateControlsXml(FILE_ITEM *pControlsXml)
{
	m_AllCtrlPropMap.clear();
	if (pControlsXml == NULL || pControlsXml->pFileData == NULL)
		return false;

	XmlState xmlState = { 0 };
	JabberXmlInitState(&xmlState);
	int bytesParsed = JabberXmlParse(&xmlState, (char *)pControlsXml->pFileData, pControlsXml->dwSrcFileLen);
	XmlNode *pControlsRoot = JabberXmlGetChild(&xmlState.root, "controls");
	if (pControlsRoot != NULL)
	{
		int nItemCount = pControlsRoot->numChild;
		for (int i = 0; i < nItemCount; i++)
		{
			XmlNode* pCtrlTypeXml = JabberXmlGetNthChildWithoutTag(pControlsRoot, i);
			if (pCtrlTypeXml != NULL && pCtrlTypeXml->name != NULL)
			{
				CONTROL_PROP_MAP* pOneCtrlMap = NULL;
				string strTypeName = pCtrlTypeXml->name;
				ALL_CONTROL_PROP_MAP::iterator pTypeItem = m_AllCtrlPropMap.find(strTypeName);
				if (pTypeItem != m_AllCtrlPropMap.end())
				{
					// 找到属性组
					pOneCtrlMap = pTypeItem->second;
				}
				else
				{
					// 创建属性组
					pOneCtrlMap = new CONTROL_PROP_MAP;
					if (pOneCtrlMap == NULL)
						return false;

					pOneCtrlMap->clear();
					m_AllCtrlPropMap.insert(pair<string, CONTROL_PROP_MAP*>(strTypeName, pOneCtrlMap));
				}

				if (pOneCtrlMap == NULL)
					return false;

				if (!GeneralCreateCtrlProp((char*)strTypeName.c_str(), pCtrlTypeXml, pOneCtrlMap))
					return false;
			}
		}
	}
	else
	{
		return false;
	}

	JabberXmlDestroyState(&xmlState);
	return true;
}

bool IPropertySkinManagerImpl::GeneralCreateCtrlProp(char *pCtrlType, XmlNode* pXmlNode, CONTROL_PROP_MAP* pCtrlPropMap)
{
	if (pCtrlType == NULL || pXmlNode == NULL || pCtrlPropMap == NULL)
		return false;

	int nItemCount = pXmlNode->numChild;
	for (int i = 0; i < nItemCount; i++)
	{
		XmlNode* pItemNode = JabberXmlGetNthChildWithoutTag(pXmlNode, i);
		if (pItemNode != NULL)
		{
			int nPropCount = pItemNode->numChild;
			for (int nPropNo = 0; nPropNo < nPropCount; nPropNo++)
			{
				XmlNode* pPropNode = JabberXmlGetNthChildWithoutTag(pItemNode, i);
				if (pPropNode != NULL && pPropNode->name != NULL)
				{
					char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
					if (psz_id == NULL)
						return false;

					IPropertyBase* pFindBaseProp = FindBaseProperty(pPropNode->name, psz_id);
					if (pFindBaseProp == NULL)
						continue;

					string strObjId = psz_id;
					pCtrlPropMap->insert(pair<string, IPropertyBase*>(strObjId, pFindBaseProp));
					if (pFindBaseProp->GetPropType() == PT_GROUP)
					{
						IPropertyGroup *pGroup = dynamic_cast<IPropertyGroup*>(pFindBaseProp);
						if (pGroup != NULL)
							AppendBasePropToGroup(pGroup, pPropNode);
					}
				}
			}
		}
	}

	return true;
}

void IPropertySkinManagerImpl::AppendBasePropToGroup(IPropertyGroup *pGroup, XmlNode* pXmlNode)
{
	if (pGroup == NULL || pXmlNode == NULL)
		return;

	int nItemCount = pXmlNode->numChild;
	for (int i = 0; i < nItemCount; i++)
	{
		XmlNode* pItemNode = JabberXmlGetNthChildWithoutTag(pXmlNode, i);
		if (pItemNode != NULL)
		{
			int nPropCount = pItemNode->numChild;
			for (int nPropNo = 0; nPropNo < nPropCount; nPropNo++)
			{
				XmlNode* pPropNode = JabberXmlGetNthChildWithoutTag(pItemNode, i);
				if (pPropNode != NULL && pPropNode->name != NULL)
				{
					char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
					if (psz_id == NULL)
						return;

					IPropertyBase* pFindBaseProp = FindBaseProperty(pPropNode->name, psz_id);
					if (pFindBaseProp == NULL)
						continue;

					pGroup->AppendProperty(pFindBaseProp);
					if (pFindBaseProp->GetPropType() == PT_GROUP)
					{
						IPropertyGroup *pNewGroup = dynamic_cast<IPropertyGroup*>(pFindBaseProp);
						if (pNewGroup != NULL)
							AppendBasePropToGroup(pNewGroup, pPropNode);
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 解析Windows.xml
bool IPropertySkinManagerImpl::TranslateWindowsXml(FILE_ITEM *pWindowsXml)
{
	m_WndPropMap.clear();
	if (pWindowsXml == NULL || pWindowsXml->pFileData == NULL)
		return false;

	XmlState xmlState = { 0 };
	JabberXmlInitState(&xmlState);
	int bytesParsed = JabberXmlParse(&xmlState, (char *)pWindowsXml->pFileData, pWindowsXml->dwSrcFileLen);
	XmlNode *pWindowRoot  = JabberXmlGetChild(&xmlState.root, "layout");
	if (pWindowRoot != NULL)
	{
		// 取得语言种类
		char* psz_area = JabberXmlGetAttrValue(pWindowRoot, "area");
		if (psz_area == NULL)
			return false;
		m_AreaType = (AREA_TYPE)atoi(psz_area);

		int nItemCount = pWindowRoot->numChild;
		for (int i = 0; i < nItemCount; i++)
		{
			XmlNode* pPropType = JabberXmlGetNthChildWithoutTag(pWindowRoot, i);
			if (pPropType != NULL && pPropType->name != NULL)
			{
				if (lstrcmpiA(pPropType->name, "window") == 0)
				{
					string strWndName = pPropType->name;
					WND_PROP_MAP::iterator pWndItem = m_WndPropMap.find(strWndName);
					if (pWndItem != m_WndPropMap.end())
						return false;

					IPropertyWindowImpl *pWndProp = new IPropertyWindowImpl;

				}

				//{
				//	// 找到属性组
				//	pOnePropMap = pTypeItem->second;
				//}
				//else
				//{
				//	// 创建属性组
				//	pOnePropMap = new PROP_MAP;
				//	if (pOnePropMap == NULL)
				//		return false;

				//	pOnePropMap->clear();
				//	m_AllPropMap.insert(pair<string, PROP_MAP*>(strTypeName, pOnePropMap));
				//}

				//if (pOnePropMap == NULL)
				//	return false;

				//if (!GeneralCreateBaseProp((char*)strTypeName.c_str(), pPropType, pOnePropMap))
				//	return false;
			}
		}
	}
	else
	{
		return false;
	}

	JabberXmlDestroyState(&xmlState);
	return true;
}
