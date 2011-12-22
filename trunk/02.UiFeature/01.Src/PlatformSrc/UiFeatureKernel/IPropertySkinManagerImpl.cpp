
#include "StdAfx.h"
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

IPropertySkinManagerImpl::IPropertySkinManagerImpl(void)
{
	m_strSkinPath = "";
	m_WndPropMap.clear();
	m_AllPropMap.clear();
	m_AreaType = AT_CN;

	LoadZipDll();
}

IPropertySkinManagerImpl::~IPropertySkinManagerImpl(void)
{
	SAFE_FREE_LIBRARY(m_hZipModule);
	ReleaseResourceXml();
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
				ReleaseResourceXmlProp(pProp);
			}
			SAFE_DELETE(pGroup);
		}
	}
	m_AllPropMap.clear();
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

void IPropertySkinManagerImpl::ReleaseResourceXmlProp(IPropertyBase *pCtrlProp)
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

// 创建属性过程
// 1. 创建属性的记录参数
// 2. 设置属性的默认值
// 3. 创建用于显示的属性值
// 4. 设置显示用的属性


IPropertySkinManager* IPropertySkinManagerImpl::GetInstance()
{
	static IPropertySkinManagerImpl _PropertySkinManagerInstance;
	return &_PropertySkinManagerInstance;
}

// 查找指定的属性
IPropertyBase* IPropertySkinManagerImpl::FindProperty(char* pszPropType, char* pszPropName)
{
	if (pszPropType == NULL || pszPropName == NULL || m_AllPropMap.size() <= 0)
		return NULL;

	string strType(pszPropType);
	ALL_PROP_MAP::iterator pPropTypeItem = m_AllPropMap.find(strType);
	if (pPropTypeItem == m_AllPropMap.end())
		return NULL;

	PROP_MAP* pPropMap = pPropTypeItem->second;
	if (pPropMap == NULL)
		return NULL;

	string strPropName(pszPropName);
	PROP_MAP::iterator pPropItem = pPropMap->find(strPropName);
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
	m_pZipFile->WriteToZip("Layout.xml");
	m_pZipFile->WriteToZip("Resource.xml");
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
	FILE_ITEM * pWindowsXml = m_pZipFile->FindUnZipFile(WINDOWS_XML_NAME);
	if (pWindowsXml == NULL || pResurceXml == NULL)
		return false;

	// 解读属性
	if (!TranslateResourceXml(pResurceXml))
		return false;

	// 解析所有Windows
	if (!TranslateWindowsXml(pWindowsXml))
		return false;

	return true;
}

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

				//if (!GeneralCreateProp((char*)strTypeName.c_str(), pPropType, pOnePropMap))
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
			XmlNode* pPropType = JabberXmlGetNthChildWithoutTag(pResurceRoot, i);
			if (pPropType != NULL && pPropType->name != NULL)
			{
				PROP_MAP* pOnePropMap = NULL;
				string strTypeName = pPropType->name;
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
					m_AllPropMap.insert(pair<string, PROP_MAP*>(strTypeName, pOnePropMap));
				}

				if (pOnePropMap == NULL)
					return false;

				if (!GeneralCreateProp((char*)strTypeName.c_str(), pPropType, pOnePropMap))
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

// 判断属性是否已经存在
bool IPropertySkinManagerImpl::IsPropExist(XmlNode* pXmlNode, PROP_MAP* pPropMap, string &strPropName)
{
	strPropName = "";
	if (pXmlNode == NULL || pPropMap == NULL)
		return false;

	char* psz_name = JabberXmlGetAttrValue(pXmlNode, SKIN_PROP_NAME);
	if (psz_name == NULL)
		return false;

	strPropName = psz_name;
	PROP_MAP::iterator pPropItem = pPropMap->find(strPropName);
	if (pPropItem == pPropMap->end())
		return false;

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

bool IPropertySkinManagerImpl::GeneralCreateProp(char *pPropType, XmlNode* pXmlNode, PROP_MAP* pPropMap)
{
	if (pPropType == NULL || pXmlNode == NULL || pPropMap == NULL)
		return false;

	int nItemCount = pXmlNode->numChild;
	for (int i = 0; i < nItemCount; i++)
	{
		XmlNode* pItem = JabberXmlGetNthChildWithoutTag(pXmlNode, i);
		if (pItem != NULL)
		{
			string strPropName = "";
			if (IsPropExist(pItem, pPropMap, strPropName))
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
			else
			{
				return false;
			}

			if (pBaseProp == NULL)
				return false;

			if (!pBaseProp->ReadResourceXmlProperty(pItem))
			{
				ReleaseProp(pBaseProp);
				return false;
			}

			pPropMap->insert(pair<string, IPropertyBase*>(strPropName, pBaseProp));
		}
	}

	return true;
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
