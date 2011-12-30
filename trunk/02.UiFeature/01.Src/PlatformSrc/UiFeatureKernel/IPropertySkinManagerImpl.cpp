
#include "StdAfx.h"
#include <assert.h>
#include "IPropertySkinManagerImpl.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IPropertyFont.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyColor.h"
#include "..\..\Inc\IPropertyComboBox.h"
#include "..\..\Inc\IPropertyCursor.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\IPropertyImageBase.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "IPropertyWindowManagerImpl.h"

IPropertySkinManager *GetSkinManagerInterface()
{
	return IPropertySkinManagerImpl::GetInstance();
}

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
	m_AllWindowPropMap.clear();
	m_LayoutWindowMap.clear();

	m_pImageBasePropMap = NULL;
	m_pFontBasePropMap = NULL;
	m_pCursorBasePropMap = NULL;
	m_pColorBasePropMap = NULL;
	m_pImagePropMap = NULL;
	m_pFontPropMap = NULL;
	m_pCursorPropMap = NULL;
	m_pColorPropMap = NULL;

	m_nObjectIdInRes = 1;
	m_nEmptyObjectId = 1;
	m_AreaType = AT_CN;

	m_pZipFile = CZipFileList::GetInstance();
}

IPropertySkinManagerImpl::~IPropertySkinManagerImpl(void)
{
	ReleaseSkinManagerPropetry();
}

// 清空属性队列
void IPropertySkinManagerImpl::ReleaseSkinManagerPropetry()
{
	ReleaseLayoutMap();
	// 以下两个队列不需要释放，两个队列中所有内容均在 m_AllPropMap 被自动释放
//	ReleasePropMapItem(&m_AllWindowPropMap);
//	ReleasePropMap(m_AllCtrlPropMap);
	ReleasePropMap(m_AllPropMap);
}

void IPropertySkinManagerImpl::ReleaseLayoutMap()
{
	for (ONE_RESOURCE_PROP_MAP::iterator pWndItem = m_LayoutWindowMap.begin(); pWndItem != m_LayoutWindowMap.end(); pWndItem++)
	{
		IPropertyWindow* pWnd = dynamic_cast<IPropertyWindow*>(pWndItem->second);
		if (pWnd != NULL)
		{
			ReleaseLayoutMapChildCtrlVec(pWnd->GetChildControlVec());
			SAFE_DELETE(pWnd);
		}
	}
	m_LayoutWindowMap.clear();
}

void IPropertySkinManagerImpl::ReleaseLayoutMapChildCtrlVec(CHILD_CTRL_PROP_VEC* pCtrlVec)
{
	if (pCtrlVec == NULL)
		return;

	for (CHILD_CTRL_PROP_VEC::iterator pVecItem = pCtrlVec->begin(); pVecItem != pCtrlVec->end(); pVecItem++)
	{
		IPropertyControl* pCtrl = *pVecItem;
		if (pCtrl != NULL)
			ReleaseLayoutMapChildCtrlVec(pCtrl->GetChildControlVec());
		SAFE_DELETE(pCtrl);
	}
	pCtrlVec->clear();
}

void IPropertySkinManagerImpl::ReleasePropMap(RESOURCE_PROP_MAP &PropMap)
{
	for (RESOURCE_PROP_MAP::iterator pGroupItem = PropMap.begin(); pGroupItem != PropMap.end(); pGroupItem++)
	{
		ONE_RESOURCE_PROP_MAP* pGroup = pGroupItem->second;
		if (pGroup != NULL)
		{
			ReleasePropMapItem(pGroup);
			SAFE_DELETE(pGroup);
		}
	}
	PropMap.clear();
}

void IPropertySkinManagerImpl::ReleasePropMapItem(ONE_RESOURCE_PROP_MAP* pPropMapItem)
{
	if (pPropMapItem == NULL)
		return;

	for (ONE_RESOURCE_PROP_MAP::iterator pPropItem = pPropMapItem->begin(); pPropItem != pPropMapItem->end(); pPropItem++)
	{
		IPropertyBase* pProp = pPropItem->second;
		ReleaseBaseProp(pProp);
	}
	pPropMapItem->clear();
}

void IPropertySkinManagerImpl::ReleaseBaseProp(IPropertyBase *pCtrlProp)
{
	if (pCtrlProp == NULL)
		return;

	switch (pCtrlProp->GetObjectTypeId())
	{
	case OTID_BOOL:
		{
			IPropertyBool* pProp = dynamic_cast<IPropertyBool*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case OTID_COLOR:
		{
			IPropertyColor* pProp = dynamic_cast<IPropertyColor*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case OTID_COMBOBOX:
		{
			IPropertyComboBox* pProp = dynamic_cast<IPropertyComboBox*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case OTID_CURSOR:
		{
			IPropertyCursor* pProp = dynamic_cast<IPropertyCursor*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case OTID_FONT:
		{
			IPropertyFont* pProp = dynamic_cast<IPropertyFont*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case OTID_GROUP:
		{
			IPropertyGroup* pProp = dynamic_cast<IPropertyGroup*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case OTID_IMAGE:
		{
			IPropertyImage* pProp = dynamic_cast<IPropertyImage*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case OTID_IMAGE_BASE:
		{
			IPropertyImageBase* pProp = dynamic_cast<IPropertyImageBase*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case OTID_INT:
		{
			IPropertyInt* pProp = dynamic_cast<IPropertyInt*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case OTID_STRING:
		{
			IPropertyString* pProp = dynamic_cast<IPropertyString*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case OTID_WINDOW:
		{
			IPropertyWindow* pProp = dynamic_cast<IPropertyWindow*>(pCtrlProp);
			if (pProp != NULL)
			{
				SAFE_DELETE(pProp);
				return;
			}
		}
		break;

	case OTID_CONTROL:
		{
			IPropertyControl* pProp = dynamic_cast<IPropertyControl*>(pCtrlProp);
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

// 创建一个属性，并将此属性放入队列
IPropertyBase* IPropertySkinManagerImpl::CreateEmptyBaseProp(OBJECT_TYPE_ID propType, char *pszObjectId)
{
	IPropertyBase* pBaseProp = NULL;
	switch (propType)
	{
	case OTID_BOOL:
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

	case OTID_COLOR:
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

	case OTID_COMBOBOX:
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

	case OTID_CURSOR:
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

	case OTID_FONT:
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

	case OTID_GROUP:
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

	case OTID_IMAGE:
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

	case OTID_IMAGE_BASE:
		{
			IPropertyImageBase* pProp = new IPropertyImageBase;
			if (pProp != NULL)
			{
				pBaseProp = dynamic_cast<IPropertyBase*>(pProp);
				if (pBaseProp == NULL)
					SAFE_DELETE(pProp);
			}
		}
		break;

	case OTID_INT:
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

	case OTID_STRING:
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

	case OTID_WINDOW:
		{
			IPropertyWindow* pProp = new IPropertyWindow;
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
		char szObjId[MAX_PATH + 1];
		memset(szObjId, 0, MAX_PATH + 1);
		if (pszObjectId == NULL)
			sprintf_s(szObjId, MAX_PATH, "NO_OBJ_ID_%d", m_nEmptyObjectId++);
		else
			strcpy_s(szObjId, MAX_PATH, pszObjectId);
		pBaseProp->SetObjectId((const char*)szObjId);

		if (propType == OTID_WINDOW)
		{
			// 创建窗口属性
			IPropertyWindow* pWndProp = dynamic_cast<IPropertyWindow*>(pBaseProp);
			if (pWndProp == NULL)
				ReleaseBaseProp(pBaseProp);

			m_LayoutWindowMap.insert(pair<string, IPropertyWindow*>(szObjId, pWndProp));
		}
		else if (propType == OTID_CONTROL)
		{
			// 创建控件属性
		}
		else
		{
			// 创建普通属性
			ONE_RESOURCE_PROP_MAP* pOnePropMap = NULL;
			string strTypeName = PropTypeToString(propType);
			RESOURCE_PROP_MAP::iterator pTypeItem = m_AllPropMap.find(strTypeName);
			if (pTypeItem != m_AllPropMap.end())
			{
				// 找到属性组
				pOnePropMap = pTypeItem->second;
			}
			else
			{
				// 创建属性组
				pOnePropMap = new ONE_RESOURCE_PROP_MAP;
				if (pOnePropMap == NULL)
				{
					ReleaseBaseProp(pBaseProp);
					return NULL;
				}

				pOnePropMap->clear();
				m_AllPropMap.insert(pair<string, ONE_RESOURCE_PROP_MAP*>(strTypeName, pOnePropMap));
			}

			if (pOnePropMap != NULL)
				pOnePropMap->insert(pair<string, IPropertyBase*>(szObjId, pBaseProp));
		}
	}

	return pBaseProp;
}

// 查找指定的属性
IPropertyBase* IPropertySkinManagerImpl::FindBaseProperty(OBJECT_TYPE_ID propType, const char* pszPropId)
{
	string strType = PropTypeToString(propType);
	return FindBaseProperty(strType.c_str(), pszPropId);
}

IPropertyBase* IPropertySkinManagerImpl::FindBaseProperty(const char* pszPropType, const char* pszPropId)
{
	if (pszPropType == NULL || strlen(pszPropType) <= 0 || pszPropId == NULL || strlen(pszPropId) <= 0 || m_AllPropMap.size() <= 0)
		return NULL;

	string strType = pszPropType;
	RESOURCE_PROP_MAP::iterator pPropTypeItem = m_AllPropMap.find(strType);
	if (pPropTypeItem == m_AllPropMap.end())
		return NULL;

	ONE_RESOURCE_PROP_MAP* pPropMap = pPropTypeItem->second;
	if (pPropMap == NULL)
		return NULL;

	string strPropId = pszPropId;
	ONE_RESOURCE_PROP_MAP::iterator pPropItem = pPropMap->find(strPropId);
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
	if (m_AllWindowPropMap.size() > 0)
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

	m_pZipFile->WriteZipInit((char*)strDir.c_str(), (char*)strUfd.c_str());
	m_pZipFile->WriteZipAppendFile(WINDOWS_XML_NAME);
	m_pZipFile->WriteZipAppendFile(RESOURCE_XML_NAME);
	m_pZipFile->WriteZipAppendFile(LAYOUT_XML_NAME);
	m_pZipFile->WriteZipAppendFile(CONTROLS_XML_NAME);
	m_pZipFile->WriteZipAppendFile("bk.PNG");
	m_pZipFile->WriteZipAppendFile("V5.Dlg.Close.png");
	m_pZipFile->WriteZipAppendFile("V5.Dlg.Mini.png");
	m_pZipFile->WriteZipAppendFile("V5.Logon.ACDC.png");
	m_pZipFile->WriteZipAppendFile("V5.Logon.Set.png");
	m_pZipFile->WriteZipAppendFile("V5.LogonBiz.01.jpg");
	m_pZipFile->WriteZipAppendFile("V5.LogonBiz.02.png");
	m_pZipFile->WriteZipAppendFile("下拉2标注.png");
	m_pZipFile->WriteZipAppendFile("下拉菜单效果图_MarkMan.png");
	m_pZipFile->WriteZipAppendFile("切图副本.png");
	m_pZipFile->WriteZipAppendFile("最新修改.png");
	m_pZipFile->WriteZipEnd();
//////////////////////////////////////////////////////////////////////////

	// 从皮肤文件中初始化皮肤队列 TBD
	m_strSkinPath = pszSkinPath;
	if (!m_pZipFile->ReadZipFile(pszSkinPath))
		return false;

	ZIP_FILE * pResurceXml = m_pZipFile->FindUnZipFile(RESOURCE_XML_NAME);
	ZIP_FILE * pControlsXml = m_pZipFile->FindUnZipFile(CONTROLS_XML_NAME);
	ZIP_FILE * pWindowsXml = m_pZipFile->FindUnZipFile(WINDOWS_XML_NAME);
	ZIP_FILE * pLayoutXml = m_pZipFile->FindUnZipFile(LAYOUT_XML_NAME);
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
	if (!TranslateLayoutXml(pLayoutXml))
		return false;
	m_pZipFile->RemoveFile(pLayoutXml);

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
	ONE_RESOURCE_PROP_MAP::iterator pWndPropItem = m_AllWindowPropMap.find(strWndName);
	if (pWndPropItem == m_AllWindowPropMap.end())
		return NULL;

	IPropertyWindow* pWndProp = dynamic_cast<IPropertyWindow*>(pWndPropItem->second);
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
	RESOURCE_PROP_MAP::iterator pStringItem = m_AllPropMap.find(PROP_TYPE_STRING_NAME);
	if (pStringItem == m_AllPropMap.end())
		return;

	ONE_RESOURCE_PROP_MAP* pPropMap = pStringItem->second;
	if (pPropMap == NULL)
		return;

	for (ONE_RESOURCE_PROP_MAP::iterator pPropItem = pPropMap->begin(); pPropItem != pPropMap->end(); pPropItem++)
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
bool IPropertySkinManagerImpl::TranslateResourceXml(ZIP_FILE *pResurceXml)
{
	ReleasePropMap(m_AllPropMap);
	if (pResurceXml == NULL || pResurceXml->pFileData == NULL)
		return false;

	XmlState xmlState = { 0 };
	JabberXmlInitState(&xmlState);
	int bytesParsed = JabberXmlParse(&xmlState, (char *)pResurceXml->pFileData, pResurceXml->dwSrcFileLen);
	XmlNode *pResurceRoot = JabberXmlGetChild(&xmlState.root, "resource");
	if (pResurceRoot != NULL)
	{
		int nItemCount = pResurceRoot->numChild;
		for (int i = 0; i < nItemCount; i++)
		{
			XmlNode* pPropTypeXml = JabberXmlGetNthChildWithoutTag(pResurceRoot, i);
			if (pPropTypeXml != NULL && pPropTypeXml->name != NULL)
			{
				ONE_RESOURCE_PROP_MAP* pOnePropMap = NULL;
				string strTypeName = pPropTypeXml->name;
				RESOURCE_PROP_MAP::iterator pTypeItem = m_AllPropMap.find(strTypeName);
				if (pTypeItem != m_AllPropMap.end())
				{
					// 找到属性组
					pOnePropMap = pTypeItem->second;
				}
				else
				{
					// 创建属性组
					pOnePropMap = new ONE_RESOURCE_PROP_MAP;
					if (pOnePropMap == NULL)
						return false;

					pOnePropMap->clear();
					m_AllPropMap.insert(pair<string, ONE_RESOURCE_PROP_MAP*>(strTypeName, pOnePropMap));

					if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_IMAGE_BASE_NAME))
					{
						m_pImageBasePropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_COLOR_BASE_NAME))
					{
						m_pColorBasePropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_CURSOR_BASE_NAME))
					{
						m_pCursorBasePropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_FONT_BASE_NAME))
					{
						m_pFontBasePropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_COLOR_NAME))
					{
						m_pColorPropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_CURSOR_NAME))
					{
						m_pCursorPropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_FONT_NAME))
					{
						m_pFontPropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_IMAGE_NAME))
					{
						m_pImagePropMap = pOnePropMap;
					}
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
	SetPropetryBaseRelevancy();
	return true;
}

// 设置属性与base属性的关联
void IPropertySkinManagerImpl::SetPropetryBaseRelevancy()
{
	SetPropRelevancy(m_pImageBasePropMap, m_pImagePropMap);
	SetPropRelevancy(m_pFontBasePropMap, m_pFontPropMap);
	SetPropRelevancy(m_pCursorBasePropMap, m_pCursorPropMap);
	SetPropRelevancy(m_pColorBasePropMap, m_pColorPropMap);
}

void IPropertySkinManagerImpl::SetPropRelevancy(ONE_RESOURCE_PROP_MAP* pFromMap, ONE_RESOURCE_PROP_MAP* pToMap)
{
	if (pFromMap == NULL || pToMap == NULL)
		return;

	for (ONE_RESOURCE_PROP_MAP::iterator pToItem = pToMap->begin(); pToItem != pToMap->end(); pToItem++)
	{
		IPropertyBase* pToProp = pToItem->second;
		if (pToProp == NULL)
			continue;

		if (pToProp->GetRelevancyPropName() == NULL || strlen(pToProp->GetRelevancyPropName()) <= 0)
			continue;

		for (ONE_RESOURCE_PROP_MAP::iterator pFromItem = pFromMap->begin(); pFromItem != pFromMap->end(); pFromItem++)
		{
			IPropertyBase* pFromProp = pFromItem->second;
			if (pFromProp == NULL)
				continue;

			if (pFromProp->GetObjectName() == NULL || strlen(pFromProp->GetObjectName()) <= 0)
				continue;

			if (lstrcmpiA(pToProp->GetRelevancyPropName(), pFromProp->GetObjectName()) == 0)
			{
				pToProp->SetRelevancyProp(pFromProp);
				break;
			}
		}
	}
}

bool IPropertySkinManagerImpl::GeneralCreateBaseProp(char *pPropType, XmlNode* pXmlNode, ONE_RESOURCE_PROP_MAP* pPropMap)
{
	if (pPropType == NULL || pXmlNode == NULL || pPropMap == NULL)
		return false;

	int nItemCount = pXmlNode->numChild;
	for (int i = 0; i < nItemCount; i++)
	{
		XmlNode* pItem = JabberXmlGetNthChildWithoutTag(pXmlNode, i);
		if (pItem != NULL)
		{
			char* psz_id = JabberXmlGetAttrValue(pItem, SKIN_OBJECT_ID);
			if (psz_id == NULL)
				return false;

			string strObjId = psz_id;
			ONE_RESOURCE_PROP_MAP::iterator pPropItem = pPropMap->find(strObjId);
			if (pPropItem != pPropMap->end())
				return false;

			string strProp = pPropType;
			OBJECT_TYPE_ID ObjTypeId = PropStringToType(strProp);
			IPropertyBase* pBaseProp = CreateEmptyBaseProp(ObjTypeId, psz_id);
			if (pBaseProp == NULL)
				return false;

			if (!pBaseProp->ReadPropertyFromXmlNode(pItem))
			{
				ReleaseBaseProp(pBaseProp);
				return false;
			}
		}
	}

	return true;
}

bool IPropertySkinManagerImpl::TranslateControlsXml(ZIP_FILE *pControlsXml)
{
	ReleasePropMap(m_AllCtrlPropMap);
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
				ONE_RESOURCE_PROP_MAP* pOneCtrlMap = NULL;
				string strTypeName = pCtrlTypeXml->name;
				RESOURCE_PROP_MAP::iterator pTypeItem = m_AllCtrlPropMap.find(strTypeName);
				if (pTypeItem != m_AllCtrlPropMap.end())
				{
					// 找到属性组
					pOneCtrlMap = pTypeItem->second;
				}
				else
				{
					// 创建属性组
					pOneCtrlMap = new ONE_RESOURCE_PROP_MAP;
					if (pOneCtrlMap == NULL)
						return false;

					pOneCtrlMap->clear();
					m_AllCtrlPropMap.insert(pair<string, ONE_RESOURCE_PROP_MAP*>(strTypeName, pOneCtrlMap));
				}

				if (pOneCtrlMap == NULL)
					return false;

				if (!GeneralCreateSubProp(pCtrlTypeXml, pOneCtrlMap))
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

bool IPropertySkinManagerImpl::GeneralCreateSubProp(XmlNode* pXmlNode, ONE_RESOURCE_PROP_MAP* pCtrlPropMap)
{
	if (pXmlNode == NULL || pCtrlPropMap == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	if (psz_id == NULL)
		return false;

	string strObjId = psz_id;
	ONE_RESOURCE_PROP_MAP::iterator pFindGroupItem = pCtrlPropMap->find(strObjId);
	if (pFindGroupItem != pCtrlPropMap->end())
		return false;

	// 创建一个窗口或者一个控件的所有属性节点的根节点：属性组
	IPropertyGroup* pCtrlProp = dynamic_cast<IPropertyGroup*>(CreateEmptyBaseProp(OTID_GROUP));
	if (pCtrlProp == NULL)
		return false;
	pCtrlProp->SetObjectId(psz_id);
	pCtrlProp->SetObjectType(PROP_ROOT_TYPE_NAME);

	IPropertyBase* pBaseProp = dynamic_cast<IPropertyBase*>(pCtrlProp);
	if (pBaseProp == NULL)
	{
		SAFE_DELETE(pCtrlProp);
		return false;
	}
	pCtrlPropMap->insert(pair<string, IPropertyBase*>(strObjId, pBaseProp));

	int nPropCount = pXmlNode->numChild;
	for (int nPropNo = 0; nPropNo < nPropCount; nPropNo++)
	{
		XmlNode* pPropNode = JabberXmlGetNthChildWithoutTag(pXmlNode, nPropNo);
		if (pPropNode != NULL && pPropNode->name != NULL)
		{
			psz_id = JabberXmlGetAttrValue(pPropNode, SKIN_OBJECT_ID);
			if (psz_id == NULL)
				return false;

			IPropertyBase* pFindBaseProp = FindBaseProperty(pPropNode->name, psz_id);
			if (pFindBaseProp == NULL)
				return false;

			pCtrlProp->AppendProperty(pFindBaseProp);
			if (pFindBaseProp->GetObjectTypeId() == OTID_GROUP)
			{
				IPropertyGroup *pNewGroup = dynamic_cast<IPropertyGroup*>(pFindBaseProp);
				if (pNewGroup == NULL)
					return false;

				if (!AppendBasePropToGroup(pNewGroup, pPropNode))
					return false;
			}
		}
	}

	return true;
}

bool IPropertySkinManagerImpl::AppendBasePropToGroup(IPropertyGroup *pGroup, XmlNode* pXmlNode)
{
	if (pGroup == NULL || pXmlNode == NULL)
		return false;

	int nItemCount = pXmlNode->numChild;
	for (int i = 0; i < nItemCount; i++)
	{
		XmlNode* pPropNode = JabberXmlGetNthChildWithoutTag(pXmlNode, i);
		if (pPropNode != NULL && pPropNode->name != NULL)
		{
			char* psz_id = JabberXmlGetAttrValue(pPropNode, SKIN_OBJECT_ID);
			if (psz_id == NULL)
				return false;

			IPropertyBase* pFindBaseProp = FindBaseProperty(pPropNode->name, psz_id);
			if (pFindBaseProp == NULL)
				return false;

			pGroup->AppendProperty(pFindBaseProp);
			if (pFindBaseProp->GetObjectTypeId() == OTID_GROUP)
			{
				IPropertyGroup *pNewGroup = dynamic_cast<IPropertyGroup*>(pFindBaseProp);
				if (pNewGroup == NULL)
					return false;

				if (!AppendBasePropToGroup(pNewGroup, pPropNode))
					return false;
			}
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 解析Windows.xml
bool IPropertySkinManagerImpl::TranslateWindowsXml(ZIP_FILE *pWindowsXml)
{
	ReleasePropMapItem(&m_AllWindowPropMap);
	if (pWindowsXml == NULL || pWindowsXml->pFileData == NULL)
		return false;

	XmlState xmlState = { 0 };
	JabberXmlInitState(&xmlState);
	int bytesParsed = JabberXmlParse(&xmlState, (char *)pWindowsXml->pFileData, pWindowsXml->dwSrcFileLen);
	XmlNode *pWindowsRoot = JabberXmlGetChild(&xmlState.root, "windows");
	if (pWindowsRoot != NULL)
	{
		int nItemCount = pWindowsRoot->numChild;
		for (int i = 0; i < nItemCount; i++)
		{
			XmlNode* pWindowNode = JabberXmlGetNthChildWithoutTag(pWindowsRoot, i);
			if (!GeneralCreateSubProp(pWindowNode, &m_AllWindowPropMap))
				return false;
		}
	}
	else
	{
		return false;
	}

	JabberXmlDestroyState(&xmlState);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 解析Windows.xml
bool IPropertySkinManagerImpl::TranslateLayoutXml(ZIP_FILE *pLayoutXml)
{
	ReleaseLayoutMap();
	if (pLayoutXml == NULL || pLayoutXml->pFileData == NULL)
		return false;

	XmlState xmlState = { 0 };
	JabberXmlInitState(&xmlState);
	int bytesParsed = JabberXmlParse(&xmlState, (char *)pLayoutXml->pFileData, pLayoutXml->dwSrcFileLen);
	XmlNode *pLayoutRoot = JabberXmlGetChild(&xmlState.root, "layout");
	if (pLayoutRoot != NULL)
	{
		char* psz_area = JabberXmlGetAttrValue(pLayoutRoot, "area");
		char* psz_lastid = JabberXmlGetAttrValue(pLayoutRoot, "lastid");
		if (psz_area == NULL || psz_lastid == NULL)
			return false;

		AREA_TYPE areaType = (AREA_TYPE)atoi(psz_area);
		SetArea(areaType);
		m_nObjectIdInRes = atoi(psz_lastid);

		int nItemCount = pLayoutRoot->numChild;
		for (int i = 0; i < nItemCount; i++)
		{
			XmlNode* pWindowNode = JabberXmlGetNthChildWithoutTag(pLayoutRoot, i);
			if (pWindowNode != NULL)
			{
				char* psz_id = JabberXmlGetAttrValue(pWindowNode, SKIN_OBJECT_ID);
				if (psz_id == NULL)
					return false;

				string strObjId = psz_id;
				ONE_RESOURCE_PROP_MAP::iterator pWndPropGroupItem = m_AllWindowPropMap.find(strObjId);
				if (pWndPropGroupItem == m_AllWindowPropMap.end())
					return false;

				IPropertyGroup *pWndPropGroup = dynamic_cast<IPropertyGroup*>(pWndPropGroupItem->second);
				if (pWndPropGroup == NULL)
					return false;

				ONE_RESOURCE_PROP_MAP::iterator pWndItem = m_LayoutWindowMap.find(strObjId);
				if (pWndItem != m_LayoutWindowMap.end())
					return false;

				IPropertyWindow* pOneWndLayoutProp = dynamic_cast<IPropertyWindow*>(CreateEmptyBaseProp(OTID_WINDOW, psz_id));
				if (pOneWndLayoutProp == NULL)
					return false;

				pOneWndLayoutProp->SetWindowPropGroup(pWndPropGroup);
				if (!GeneralCreateWindowLayoutProp(pWindowNode, pOneWndLayoutProp->GetChildControlVec(), NULL))
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

bool IPropertySkinManagerImpl::GeneralCreateWindowLayoutProp(XmlNode* pXmlNode, CHILD_CTRL_PROP_VEC* pChildCtrlVec, IPropertyControl* pParentProp)
{
	if (pXmlNode == NULL || pChildCtrlVec == NULL)
		return false;

	int nItemCount = pXmlNode->numChild;
	for (int i = 0; i < nItemCount; i++)
	{
		XmlNode* pCtrlNode = JabberXmlGetNthChildWithoutTag(pXmlNode, i);
		if (pCtrlNode != NULL)
		{
			char* psz_id = JabberXmlGetAttrValue(pCtrlNode, SKIN_OBJECT_ID);
			if (psz_id == NULL)
				return false;

			IPropertyGroup* pCtrlPropGroup = FindControlPropGroup(psz_id);
			if (pCtrlPropGroup == NULL)
				return false;

			IPropertyControl* pCtrlProp = dynamic_cast<IPropertyControl*>(CreateEmptyBaseProp(OTID_CONTROL, psz_id));
			if (pCtrlProp == NULL)
				return false;

			pCtrlProp->SetControlBaseProp(pCtrlPropGroup);
			pCtrlProp->SetParentProp(pParentProp);
			pChildCtrlVec->push_back(pCtrlProp);

			if (pCtrlNode->numChild > 0)
			{
				if (!GeneralCreateWindowLayoutProp(pCtrlNode, pCtrlProp->GetChildControlVec(), pCtrlProp))
					return false;
			}
		}
	}

	return true;
}

IPropertyGroup* IPropertySkinManagerImpl::FindControlPropGroup(char *pszObjectId)
{
	if (pszObjectId == NULL)
		return NULL;

	for (RESOURCE_PROP_MAP::iterator pGroupItem = m_AllCtrlPropMap.begin(); pGroupItem != m_AllCtrlPropMap.end(); pGroupItem++)
	{
		ONE_RESOURCE_PROP_MAP* pGroup = pGroupItem->second;
		if (pGroup != NULL)
		{
			string strObjId = pszObjectId;
			ONE_RESOURCE_PROP_MAP::iterator pPropItem = pGroup->find(strObjId);
			if (pPropItem == pGroup->end())
				continue;
			
			IPropertyBase* pPropBase = pPropItem->second;
			if (pPropBase == NULL)
				continue;

			IPropertyGroup* pFindGroup = dynamic_cast<IPropertyGroup*>(pPropBase);
			return pFindGroup;
		}
	}

	return NULL;
}

// 解析Resource.xml
bool IPropertySkinManagerImpl::BuilderTranslateResourceXml(char *pszXmlPath)
{
	ZIP_FILE FileItem;
	if (!BuilderCreateFileItem(pszXmlPath, FileItem))
		return false;

	bool bRet = TranslateResourceXml(&FileItem);

	BuilderFreeFileItem(FileItem);
	return bRet;
}

// 解析Controls.xml
bool IPropertySkinManagerImpl::BuilderTranslateControlsXml(char *pszXmlPath)
{
	ZIP_FILE FileItem;
	if (!BuilderCreateFileItem(pszXmlPath, FileItem))
		return false;

	bool bRet = TranslateControlsXml(&FileItem);

	BuilderFreeFileItem(FileItem);
	return bRet;
}

// 解析Windows.xml
bool IPropertySkinManagerImpl::BuilderTranslateWindowsXml(char *pszXmlPath)
{
	ZIP_FILE FileItem;
	if (!BuilderCreateFileItem(pszXmlPath, FileItem))
		return false;

	bool bRet = TranslateWindowsXml(&FileItem);

	BuilderFreeFileItem(FileItem);
	return bRet;
}

// 解析Layout.xml
bool IPropertySkinManagerImpl::BuilderTranslateLayoutXml(char *pszXmlPath)
{
	ZIP_FILE FileItem;
	if (!BuilderCreateFileItem(pszXmlPath, FileItem))
		return false;

	bool bRet = TranslateLayoutXml(&FileItem);

	BuilderFreeFileItem(FileItem);
	return bRet;
}

bool IPropertySkinManagerImpl::BuilderCreateFileItem(char *pFilePath, ZIP_FILE &FileItem)
{
	FileItem.strFileName = "";
	FileItem.dwSrcFileLen = 0;
	FileItem.dwZipDatalen = 0;
	FileItem.pFileData = NULL;

	if (pFilePath == NULL)
		return false;

	WIN32_FILE_ATTRIBUTE_DATA FileAttr;
	if (!::GetFileAttributesExA(pFilePath, GetFileExInfoStandard, &FileAttr))
		return false;

	FILE *pFile = NULL;
	fopen_s(&pFile, pFilePath, "rb");
	if (pFile == NULL)
		return false;

	FileItem.pFileData = new BYTE[FileAttr.nFileSizeLow];
	if (FileItem.pFileData == NULL)
	{
		fclose(pFile);
		return false;
	}

	int nReadCtns = 0;
	while(nReadCtns < (int)FileAttr.nFileSizeLow)
	{
		BYTE *pRead = FileItem.pFileData + nReadCtns;
		int nNeedRead = FileAttr.nFileSizeLow - nReadCtns;

		int nRead = fread_s(pRead, nNeedRead, 1, nNeedRead, pFile);
		nReadCtns += nRead;

		if (errno != 0)
		{
			SAFE_DELETE_LIST(FileItem.pFileData);
			fclose(pFile);
			return false;
		}
	}

	if (nReadCtns != (int)FileAttr.nFileSizeLow)
	{
		SAFE_DELETE_LIST(FileItem.pFileData);
		fclose(pFile);
		return false;
	}

	FileItem.dwSrcFileLen = FileAttr.nFileSizeLow;
	return true;
}

void IPropertySkinManagerImpl::BuilderFreeFileItem(ZIP_FILE &FileItem)
{
	if (FileItem.pFileData != NULL)
		SAFE_DELETE_LIST(FileItem.pFileData);

	FileItem.strFileName = "";
	FileItem.dwSrcFileLen = 0;
	FileItem.dwZipDatalen = 0;
	FileItem.pFileData = NULL;
}

ONE_RESOURCE_PROP_MAP* IPropertySkinManagerImpl::BuilderGetWindowPropMap()
{
	return &m_LayoutWindowMap;
}

// 保存皮肤包
bool IPropertySkinManagerImpl::BuilderSaveSkin(char *pszSkinDir, char *pszSkinName)
{
	if (pszSkinDir == NULL || pszSkinName == NULL || m_pZipFile == NULL)
		return false;

	string strDir = pszSkinDir;
	if (pszSkinDir[strlen(pszSkinDir) - 1] != '\\')
		strDir += "\\";

	// 保存 Resource.xml
	string strResourceXmlPath = strDir;
	strResourceXmlPath += RESOURCE_XML_NAME;
	string strResourceXmlData("");
	if (!SaveResourceXml(strResourceXmlPath.c_str(), strResourceXmlData))
		return false;

	// 保存 Controls.xml
	string strControlsXmlPath = strDir;
	strControlsXmlPath += CONTROLS_XML_NAME;
	string strControlsXmlData("");
	if (!SaveControlsXml(strControlsXmlPath.c_str(), strControlsXmlData))
		return false;

	// 保存 Windows.xml
	string strWindowsXmlPath = strDir;
	strWindowsXmlPath += WINDOWS_XML_NAME;
	string strWindowsXmlData("");
	if (!SaveWindowsXml(strWindowsXmlPath.c_str(), strWindowsXmlData))
		return false;

	// 保存 Layout.xml
	string strLayoutXmlPath = strDir;
	strLayoutXmlPath += LAYOUT_XML_NAME;
	string strLayoutXmlData("");
	if (!SaveLayoutXml(strLayoutXmlPath.c_str(), strLayoutXmlData))
		return false;

	string strZipFile(strDir);
	strZipFile += pszSkinName;
	strZipFile += NAME_SKIN_FILE_EX_NAME;
	
	// 写入zip文件
	if (!m_pZipFile->WriteZipInit(pszSkinDir, (char*)strZipFile.c_str()))
		return false;

	if (!m_pZipFile->WriteZipAppendBuffer(RESOURCE_XML_NAME, (BYTE*)strResourceXmlData.c_str(), strResourceXmlData.size()))
		return false;
	if (!m_pZipFile->WriteZipAppendBuffer(CONTROLS_XML_NAME, (BYTE*)strControlsXmlData.c_str(), strControlsXmlData.size()))
		return false;
	if (!m_pZipFile->WriteZipAppendBuffer(WINDOWS_XML_NAME, (BYTE*)strWindowsXmlData.c_str(), strWindowsXmlData.size()))
		return false;
	if (!m_pZipFile->WriteZipAppendBuffer(LAYOUT_XML_NAME, (BYTE*)strLayoutXmlData.c_str(), strLayoutXmlData.size()))
		return false;

	return m_pZipFile->WriteZipEnd();
}

bool IPropertySkinManagerImpl::SaveLayoutXml(const char *pszSavePath, string &strXmlData)
{
	CUiXmlWrite XmlStrObj;

	CUiXmlWriteNode* pRootNode = XmlStrObj.CreateNode("layout");
	if (pRootNode == NULL)
		return false;

	AddIntAttrToNode(pRootNode, "area", m_AreaType);
	AddIntAttrToNode(pRootNode, "lastid", m_nObjectIdInRes+1);

	for (ONE_RESOURCE_PROP_MAP::iterator pWndPropItem = m_LayoutWindowMap.begin(); pWndPropItem != m_LayoutWindowMap.end(); pWndPropItem++)
	{
		IPropertyWindow *pPropWnd = dynamic_cast<IPropertyWindow*>(pWndPropItem->second);
		if (pPropWnd == NULL)
			continue;

		CUiXmlWriteNode* pWndNode = XmlStrObj.CreateNode(pRootNode, "window");
		if (pWndNode == NULL)
			return false;

		pWndNode->AddAttribute(SKIN_OBJECT_ID, pPropWnd->GetObjectId());

		CHILD_CTRL_PROP_VEC* pWndChildVec = pPropWnd->GetChildControlVec();
		if (!SaveLayoutXml_ChildCtrl(XmlStrObj, pWndNode, pWndChildVec))
			return false;
	}
	strXmlData = XmlStrObj.ToXmlString();

	SaveToFile((char*)pszSavePath, (BYTE*)strXmlData.c_str(), strXmlData.size());
	return true;
}

bool IPropertySkinManagerImpl::SaveLayoutXml_ChildCtrl(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pNode, CHILD_CTRL_PROP_VEC* pWndChildVec)
{
	if (pWndChildVec == NULL)
		return false;

	for (int i = 0; i < (int)pWndChildVec->size(); i++)
	{
		IPropertyControl* pPropCtrl = (*pWndChildVec)[i];
		if (pPropCtrl == NULL)
			continue;

		CUiXmlWriteNode* pCtrlNode = XmlStrObj.CreateNode(pNode, "ctrl");
		if (pCtrlNode == NULL)
			return false;

		pCtrlNode->AddAttribute(SKIN_OBJECT_ID, pPropCtrl->GetObjectId());

		CHILD_CTRL_PROP_VEC* pCtrlChildVec = pPropCtrl->GetChildControlVec();
		if (!SaveLayoutXml_ChildCtrl(XmlStrObj, pCtrlNode, pCtrlChildVec))
			return false;
	}
	return true;
}

void IPropertySkinManagerImpl::SaveToFile(char *pszFilePath, BYTE *pData, int nDataLen)
{
	if (pszFilePath == NULL || pData == NULL || nDataLen <= 0)
		return;

	FILE* fp = NULL;
	fopen_s(&fp, pszFilePath, "wb");
	if (fp)
	{
		fwrite(pData, nDataLen, 1, fp);
		fclose(fp);
	}
}

bool IPropertySkinManagerImpl::SaveResourceXml(const char *pszSavePath, string &strXmlData)
{
	CUiXmlWrite XmlStrObj;

	CUiXmlWriteNode* pRootNode = XmlStrObj.CreateNode("resource");
	if (pRootNode == NULL)
		return false;

	for (RESOURCE_PROP_MAP::iterator pPropTypeItem = m_AllPropMap.begin(); pPropTypeItem != m_AllPropMap.end(); pPropTypeItem++)
	{
		ONE_RESOURCE_PROP_MAP *pPropType = pPropTypeItem->second;
		if (pPropType == NULL)
			continue;

		string strPropType = pPropTypeItem->first;
		CUiXmlWriteNode* pPropTypeNode = XmlStrObj.CreateNode(pRootNode, strPropType.c_str());
		if (pPropTypeNode == NULL)
			return false;

		for (ONE_RESOURCE_PROP_MAP::iterator pPropItem = pPropType->begin(); pPropItem != pPropType->end(); pPropItem++)
		{
			IPropertyBase* pPropBase = dynamic_cast<IPropertyBase*>(pPropItem->second);
			if (pPropBase == NULL)
				continue;

			if (!pPropBase->AppendToXmlNode(XmlStrObj, pPropTypeNode))
				return false;
		}
	}
	strXmlData = XmlStrObj.ToXmlString();

	SaveToFile((char*)pszSavePath, (BYTE*)strXmlData.c_str(), strXmlData.size());
	return true;
}

bool IPropertySkinManagerImpl::SaveControlsXml(const char *pszSavePath, string &strXmlData)
{
	return true;
}

bool IPropertySkinManagerImpl::SaveWindowsXml(const char *pszSavePath, string &strXmlData)
{
	CUiXmlWrite XmlStrObj;

	CUiXmlWriteNode* pRootNode = XmlStrObj.CreateNode("windows");
	if (pRootNode == NULL)
		return false;

	for (ONE_RESOURCE_PROP_MAP::iterator pWndItem = m_AllWindowPropMap.begin(); pWndItem != m_AllWindowPropMap.end(); pWndItem++)
	{
		string strObjId = pWndItem->first;
		IWindowBase* pPropBase = dynamic_cast<IWindowBase*>(pWndItem->second);
		if (pPropBase == NULL)
			continue;

		IPropertyGroup *pWndPropGroup = pPropBase->GetWindowProp()->GetWindowPropetryBaseGroup();
		if (pWndPropGroup == NULL)
			return false;

		CUiXmlWriteNode* pWindowNode = XmlStrObj.CreateNode(pRootNode, pPropBase->GetObjectType());
		if (pWindowNode == NULL)
			return false;
		pWindowNode->AddAttribute(SKIN_OBJECT_ID, pWndPropGroup->GetObjectId());

		SaveWindowsXml_GroupProp(XmlStrObj, pWindowNode, pWndPropGroup);
	}
	strXmlData = XmlStrObj.ToXmlString();

	SaveToFile((char*)pszSavePath, (BYTE*)strXmlData.c_str(), strXmlData.size());
	return true;
}

bool IPropertySkinManagerImpl::SaveWindowsXml_GroupProp(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentNode, IPropertyGroup *pPropGroup)
{
	if (pParentNode == NULL || pPropGroup == NULL)
		return false;

	GROUP_PROP_VEC* pPropVec = pPropGroup->GetPropVec();
	if (pPropVec == NULL)
		return false;

	for (GROUP_PROP_VEC::iterator pPropItem = pPropVec->begin(); pPropItem != pPropVec->end(); pPropItem++)
	{
		IPropertyBase* pProp = *pPropItem;
		if (pProp == NULL)
			continue;

		CUiXmlWriteNode* pPropNode = XmlStrObj.CreateNode(pParentNode, pProp->GetObjectType());
		if (pPropNode == NULL)
			return false;
		pPropNode->AddAttribute(SKIN_OBJECT_ID, pProp->GetObjectId());

		if (pProp->GetObjectTypeId() == OTID_GROUP)
		{
			IPropertyGroup *pNextPropGroup = dynamic_cast<IPropertyGroup*>(pProp);
			if (pNextPropGroup == NULL)
				continue;

			if (!SaveWindowsXml_GroupProp(XmlStrObj, pPropNode, pNextPropGroup))
				return false;
		}
	}

	return true;
}

ONE_RESOURCE_PROP_MAP* IPropertySkinManagerImpl::GetAllWindowPropMap()
{
	return &m_AllWindowPropMap;
}
