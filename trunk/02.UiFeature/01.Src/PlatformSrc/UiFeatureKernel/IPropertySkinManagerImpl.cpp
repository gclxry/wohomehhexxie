
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

IPropertySkinManagerImpl::IPropertySkinManagerImpl(void)
{
	m_bPropId = 1;
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
		PROP_VEC* pGroup = pGroupItem->second;
		if (pGroup != NULL)
		{
			for (PROP_VEC::iterator pPropItem = pGroup->begin(); pPropItem != pGroup->end(); pPropItem++)
			{
				IPropertyBase* pProp = *pPropItem;
				ReleaseProperty(pProp);
			}
			SAFE_DELETE(pGroup);
		}
	}
	m_AllPropMap.clear();
}

// ����zip�ļ�
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

void IPropertySkinManagerImpl::ReleaseProperty(IPropertyBase *pCtrlProp)
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

// �������Թ���
// 1. �������Եļ�¼����
// 2. �������Ե�Ĭ��ֵ
// 3. ����������ʾ������ֵ
// 4. ������ʾ�õ�����


IPropertySkinManager* IPropertySkinManagerImpl::GetInstance()
{
	static IPropertySkinManagerImpl _PropertySkinManagerInstance;
	return &_PropertySkinManagerInstance;
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

// ����һ�����ԣ����������Է������
IPropertyBase* IPropertySkinManagerImpl::CreateEmptyProperty(PROP_TYPE propType)
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
		PROP_VEC* pOnePropVec = NULL;
		string strTypeName = PropTypeToString(propType);
		ALL_PROP_MAP::iterator pTypeItem = m_AllPropMap.find(strTypeName);
		if (pTypeItem != m_AllPropMap.end())
		{
			// �ҵ�������
			pOnePropVec = pTypeItem->second;
		}
		else
		{
			// ����������
			pOnePropVec = new PROP_VEC;
			if (pOnePropVec == NULL)
			{
				ReleaseProperty(pBaseProp);
				return NULL;
			}

			pOnePropVec->clear();
			m_AllPropMap.insert(pair<string, PROP_VEC*>(strTypeName, pOnePropVec));
		}

		if (pOnePropVec != NULL)
			pOnePropVec->push_back(pBaseProp);
	}

	return pBaseProp;
}

// ����ָ��������
IPropertyBase* IPropertySkinManagerImpl::FindProperty(PROP_TYPE propType, const char* pszPropId)
{
	string strType = PropTypeToString(propType);
	return FindProperty(strType.c_str(), pszPropId);
}

IPropertyBase* IPropertySkinManagerImpl::FindProperty(const char* pszPropType, const char* pszPropId)
{
	if (pszPropType == NULL || strlen(pszPropType) <= 0 || pszPropId == NULL || strlen(pszPropId) <= 0 || m_AllPropMap.size() <= 0)
		return NULL;

	string strType = pszPropType;
	ALL_PROP_MAP::iterator pPropTypeItem = m_AllPropMap.find(strType);
	if (pPropTypeItem == m_AllPropMap.end())
		return NULL;

	PROP_VEC* pPropVec = pPropTypeItem->second;
	if (pPropVec == NULL)
		return NULL;

	string strPropId = pszPropId;
	for (int i = 0; i < (int)pPropVec->size(); i++)
	{
		IPropertyBase* pProp = (*pPropVec)[i];
		if (pProp != NULL)
		{
			if (lstrcmpiA(pProp->GetObjectId(), pszPropId) == 0)
				return pProp;
		}
	}

	return NULL;
}

// ��ʼ��Ƥ����
bool IPropertySkinManagerImpl::InitSkinPackage(const char *pszSkinPath)
{
	// TBD����Builder����Ƥ���ļ����ǲ�һ����
	if (pszSkinPath == NULL || strlen(pszSkinPath) <= 0 || m_pZipFile == NULL)
		return false;

	// ��ʼ��
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
	m_pZipFile->WriteToZip("����2��ע.png");
	m_pZipFile->WriteToZip("�����˵�Ч��ͼ_MarkMan.png");
	m_pZipFile->WriteToZip("��ͼ����.png");
	m_pZipFile->WriteToZip("�����޸�.png");
	m_pZipFile->EndWriteZip();
//////////////////////////////////////////////////////////////////////////

	// ��Ƥ���ļ��г�ʼ��Ƥ������ TBD
	m_strSkinPath = pszSkinPath;
	if (!m_pZipFile->ReadZipFile(pszSkinPath))
		return false;

	FILE_ITEM * pResurceXml = m_pZipFile->FindUnZipFile(RESOURCE_XML_NAME);
	FILE_ITEM * pWindowsXml = m_pZipFile->FindUnZipFile(WINDOWS_XML_NAME);
	if (pWindowsXml == NULL || pResurceXml == NULL)
		return false;

	// �������
	if (!TranslateResourceXml(pResurceXml))
		return false;

	// ��������Windows
	if (!TranslateWindowsXml(pWindowsXml))
		return false;

	return true;
}

// ����Windows.xml
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
		// ȡ����������
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
				//	// �ҵ�������
				//	pOnePropVec = pTypeItem->second;
				//}
				//else
				//{
				//	// ����������
				//	pOnePropVec = new PROP_VEC;
				//	if (pOnePropVec == NULL)
				//		return false;

				//	pOnePropVec->clear();
				//	m_AllPropMap.insert(pair<string, PROP_VEC*>(strTypeName, pOnePropVec));
				//}

				//if (pOnePropVec == NULL)
				//	return false;

				//if (!GeneralCreateProp((char*)strTypeName.c_str(), pPropType, pOnePropVec))
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

// ����Resource.xml
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
				PROP_VEC* pOnePropVec = NULL;
				string strTypeName = pPropType->name;
				ALL_PROP_MAP::iterator pTypeItem = m_AllPropMap.find(strTypeName);
				if (pTypeItem != m_AllPropMap.end())
				{
					// �ҵ�������
					pOnePropVec = pTypeItem->second;
				}
				else
				{
					// ����������
					pOnePropVec = new PROP_VEC;
					if (pOnePropVec == NULL)
						return false;

					pOnePropVec->clear();
					m_AllPropMap.insert(pair<string, PROP_VEC*>(strTypeName, pOnePropVec));
				}

				if (pOnePropVec == NULL)
					return false;

				if (!GeneralCreateProp((char*)strTypeName.c_str(), pPropType, pOnePropVec))
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

// �ж������Ƿ��Ѿ�����
bool IPropertySkinManagerImpl::IsPropExist(XmlNode* pXmlNode, PROP_VEC* pPropVec, string &strPropId)
{
	strPropId = "";
	if (pXmlNode == NULL || pPropVec == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_PROP_ID);
	if (psz_id == NULL)
		return false;

	//for (PROP_VEC::iterator pPropItem = pPropVec->begin(); pPropItem != pPropVec->end(); pPropItem++)
	//{
	//	IPropertyBase* pProp = *pPropItem;
	//	if (pProp != NULL && lstrcmpiA(pProp->GetPropId(), ) == 0)
	//		return true;
	//}

	return false;
}

// ��ʼ��Ƥ��
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

void IPropertySkinManagerImpl::ResetPropId(int nPropId)
{
	if (nPropId >= m_bPropId)
		m_bPropId = nPropId + 1;
}

// ȡ��ID��
int IPropertySkinManagerImpl::GetNewId()
{
	return m_bPropId++;
}

bool IPropertySkinManagerImpl::GeneralCreateProp(char *pPropType, XmlNode* pXmlNode, PROP_VEC* pPropVec)
{
	if (pPropType == NULL || pXmlNode == NULL || pPropVec == NULL)
		return false;

	int nItemCount = pXmlNode->numChild;
	for (int i = 0; i < nItemCount; i++)
	{
		XmlNode* pItem = JabberXmlGetNthChildWithoutTag(pXmlNode, i);
		if (pItem != NULL)
		{
			//int nPropId = 0;
			//if (IsPropExist(pItem, pPropMap, nPropId))
			//	return false;

			//// ��������PropId
			//ResetPropId(nPropId);

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
				ReleaseProperty(pBaseProp);
				return false;
			}

			pPropVec->push_back(pBaseProp);
		}
	}

	return true;
}

// ������ʾ����������
void IPropertySkinManagerImpl::SetArea(AREA_TYPE areaType)
{
	ALL_PROP_MAP::iterator pStringItem = m_AllPropMap.find(PROP_TYPE_STRING_NAME);
	if (pStringItem == m_AllPropMap.end())
		return;

	PROP_VEC* pPropMap = pStringItem->second;
	if (pPropMap == NULL)
		return;

	for (PROP_VEC::iterator pPropItem = pPropMap->begin(); pPropItem != pPropMap->end(); pPropItem++)
	{
		IPropertyBase* pProp = *pPropItem;
		if (pProp == NULL)
			continue;

		IPropertyString *pStringProp = dynamic_cast<IPropertyString*>(pProp);
		if (pStringProp == NULL)
			continue;

		pStringProp->SetArea(areaType);
	}
}

bool IPropertySkinManagerImpl::TranslateControlsXml(FILE_ITEM *pWindowsXml)
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
		// ȡ����������
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
				//	// �ҵ�������
				//	pOnePropVec = pTypeItem->second;
				//}
				//else
				//{
				//	// ����������
				//	pOnePropVec = new PROP_VEC;
				//	if (pOnePropVec == NULL)
				//		return false;

				//	pOnePropVec->clear();
				//	m_AllPropMap.insert(pair<string, PROP_VEC*>(strTypeName, pOnePropVec));
				//}

				//if (pOnePropVec == NULL)
				//	return false;

				//if (!GeneralCreateProp((char*)strTypeName.c_str(), pPropType, pOnePropVec))
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
