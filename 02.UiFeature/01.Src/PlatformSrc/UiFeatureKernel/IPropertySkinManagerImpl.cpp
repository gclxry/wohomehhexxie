
#include "StdAfx.h"
#include <assert.h>
#include "IPropertySkinManagerImpl.h"
#include "IUiFeatureKernelImpl.h"
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
#include "IWindowBaseImpl.h"
#include "CriSec.h"

// 系统默认字体
#define SYS_DEFAULT_FONT_NAME								"SystemDefaultFont"

IPropertySkinManager *GetSkinManagerInterface()
{
	return IPropertySkinManagerImpl::GetInstance();
}

IPropertySkinManager* IPropertySkinManagerImpl::GetInstance()
{
	static IPropertySkinManagerImpl _PropertySkinManagerInstance;
	return &_PropertySkinManagerInstance;
}

IPropertySkinManagerImpl::IPropertySkinManagerImpl()
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

	m_AreaType = AT_CN;
	// 取得整个程序默认的字体信息
	m_pDefaultFontBase = NULL;

	m_pKernelZipFile = ((IUiFeatureKernelImpl*)IUiFeatureKernelImpl::GetInstance())->GetZipFile();
}

IPropertySkinManagerImpl::~IPropertySkinManagerImpl()
{
	ReleaseSkinManagerPropetry();
}

// 清空属性队列
void IPropertySkinManagerImpl::ReleaseSkinManagerPropetry()
{
	ReleaseLayoutMap();
	ReleasePropMap(m_AllCtrlPropMap, false);
	ReleasePropMap(m_AllPropMap, true);
	m_AllWindowPropMap.clear();
}

void IPropertySkinManagerImpl::ReleasePropMap(RESOURCE_PROP_MAP &PropMap, bool bReleaseChild)
{
	for (RESOURCE_PROP_MAP::iterator pGroupItem = PropMap.begin(); pGroupItem != PropMap.end(); pGroupItem++)
	{
		ONE_RESOURCE_PROP_MAP* pGroup = pGroupItem->second;
		if (pGroup != NULL && bReleaseChild)
			ReleasePropMapItem(pGroup);
		SAFE_DELETE(pGroup);
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

void IPropertySkinManagerImpl::ReleaseLayoutMap()
{
	for (ONE_RESOURCE_PROP_MAP::iterator pWndItem = m_LayoutWindowMap.begin(); pWndItem != m_LayoutWindowMap.end(); pWndItem++)
	{
		IPropertyWindow* pWnd = dynamic_cast<IPropertyWindow*>(pWndItem->second);
		if (pWnd != NULL)
		{
			ReleaseLayoutMapPropControlVec(pWnd->GetChildPropControlVec());
			SAFE_DELETE(pWnd);
		}
	}
	m_LayoutWindowMap.clear();
}

void IPropertySkinManagerImpl::ReleaseLayoutMapPropControlVec(PROP_CONTROL_VEC* pCtrlVec)
{
	if (pCtrlVec == NULL)
		return;

	for (PROP_CONTROL_VEC::iterator pVecItem = pCtrlVec->begin(); pVecItem != pCtrlVec->end(); pVecItem++)
	{
		IPropertyControl* pCtrl = *pVecItem;
		if (pCtrl != NULL)
			ReleaseLayoutMapPropControlVec(pCtrl->GetChildPropControlVec());
		SAFE_DELETE(pCtrl);
	}
	pCtrlVec->clear();
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

	case OTID_CURSOR_BASE:
		{
			IPropertyCursorBase* pProp = dynamic_cast<IPropertyCursorBase*>(pCtrlProp);
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

	case OTID_FONT_BASE:
		{
			IPropertyFontBase* pProp = dynamic_cast<IPropertyFontBase*>(pCtrlProp);
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

	case OTID_CURSOR_BASE:
		{
			IPropertyCursorBase* pProp = new IPropertyCursorBase;
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

	case OTID_FONT_BASE:
		{
			IPropertyFontBase* pProp = new IPropertyFontBase;
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

	case OTID_CONTROL:
		{
			IPropertyControl* pProp = new IPropertyControl;
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
		pBaseProp->SetUiKernel(IUiFeatureKernelImpl::GetInstance());

		if (pszObjectId != NULL)
			pBaseProp->SetObjectId((const char*)pszObjectId);

		if (propType == OTID_WINDOW)
		{
			// 创建窗口属性
			IPropertyWindow* pWndProp = dynamic_cast<IPropertyWindow*>(pBaseProp);
			if (pWndProp == NULL)
			{
				ReleaseBaseProp(pBaseProp);
				return NULL;
			}

			m_LayoutWindowMap.insert(pair<string, IPropertyWindow*>(pBaseProp->GetObjectId(), pWndProp));
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
				pOnePropMap->insert(pair<string, IPropertyBase*>(pBaseProp->GetObjectId(), pBaseProp));
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
	if (pszSkinPath == NULL || strlen(pszSkinPath) <= 0 || m_pKernelZipFile == NULL)
		return false;

	// 初始化
	if (m_AllWindowPropMap.size() > 0)
		return true;

	// 从皮肤文件中初始化皮肤队列
	m_strSkinPath = pszSkinPath;
	if (!m_pKernelZipFile->ReadZipFile(pszSkinPath))
		return false;

	ZIP_FILE * pResurceXml = m_pKernelZipFile->FindUnZipFile(RESOURCE_XML_NAME);
	ZIP_FILE * pControlsXml = m_pKernelZipFile->FindUnZipFile(CONTROLS_XML_NAME);
	ZIP_FILE * pWindowsXml = m_pKernelZipFile->FindUnZipFile(WINDOWS_XML_NAME);
	ZIP_FILE * pLayoutXml = m_pKernelZipFile->FindUnZipFile(LAYOUT_XML_NAME);
	if (pWindowsXml == NULL || pResurceXml == NULL)
		return false;

	// 解读 Resource.xml
	if (!TranslateResourceXml(pResurceXml))
		return false;
	m_pKernelZipFile->RemoveFile(pResurceXml);

	// 解读 Controls.xml
	if (!TranslateControlsXml(pControlsXml))
		return false;
	m_pKernelZipFile->RemoveFile(pControlsXml);

	// 解读 Windows.xml
	if (!TranslateWindowsXml(pWindowsXml))
		return false;
	m_pKernelZipFile->RemoveFile(pWindowsXml);

	// 解析 Layout.xml
	if (!TranslateLayoutXml(pLayoutXml))
		return false;
	m_pKernelZipFile->RemoveFile(pLayoutXml);

	return true;
}

// 初始化皮肤
IPropertyWindow* IPropertySkinManagerImpl::PG_InitWindowSkin(const char *pszSkinPath, const char *pszWndName)
{
	if (pszSkinPath == NULL || strlen(pszSkinPath) <= 0 || pszWndName == NULL || strlen(pszWndName) <= 0)
		return NULL;

	if (!InitSkinPackage(pszSkinPath))
		return NULL;

	IPropertyWindow *pFindPropWnd = NULL;
	string strWndName = pszWndName;
	for (ONE_RESOURCE_PROP_MAP::iterator pWndPropItem = m_LayoutWindowMap.begin(); pWndPropItem != m_LayoutWindowMap.end(); pWndPropItem++)
	{
		IPropertyWindow *pPropWnd = dynamic_cast<IPropertyWindow*>(pWndPropItem->second);
		if (pPropWnd == NULL)
			continue;

		if (lstrcmpiA(pszWndName, pPropWnd->GetObjectName()) == 0)
		{
			pFindPropWnd = pPropWnd;
			break;
		}
	}

	return pFindPropWnd;
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
	ReleasePropMap(m_AllPropMap, true);
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

					if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_IMAGE_BASE_NAME) == 0)
					{
						m_pImageBasePropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_COLOR_BASE_NAME) == 0)
					{
						m_pColorBasePropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_CURSOR_BASE_NAME) == 0)
					{
						m_pCursorBasePropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_FONT_BASE_NAME) == 0)
					{
						m_pFontBasePropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_COLOR_NAME) == 0)
					{
						m_pColorPropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_CURSOR_NAME) == 0)
					{
						m_pCursorPropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_FONT_NAME) == 0)
					{
						m_pFontPropMap = pOnePropMap;
					}
					else if (lstrcmpiA(strTypeName.c_str(), PROP_TYPE_IMAGE_NAME) == 0)
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
	SetImageFileRelevancy();
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
	ReleasePropMap(m_AllCtrlPropMap, false);
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
	m_AllWindowPropMap.clear();
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
		if (psz_area == NULL)
			return false;

		AREA_TYPE areaType = (AREA_TYPE)atoi(psz_area);
		SetArea(areaType);

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
				if (!GeneralCreateWindowLayoutProp(pWindowNode, pOneWndLayoutProp->GetChildPropControlVec(), NULL))
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

bool IPropertySkinManagerImpl::GeneralCreateWindowLayoutProp(XmlNode* pXmlNode, PROP_CONTROL_VEC* pChildCtrlVec, IPropertyControl* pParentProp)
{
	if (pXmlNode == NULL || pChildCtrlVec == NULL)
		return false;

	int nItemCount = pXmlNode->numChild;
	for (int i = 0; i < nItemCount; i++)
	{
		XmlNode* pCtrlNode = JabberXmlGetNthChildWithoutTag(pXmlNode, i);
		if (pCtrlNode != NULL && pCtrlNode->name != NULL)
		{
			char* psz_id = JabberXmlGetAttrValue(pCtrlNode, SKIN_OBJECT_ID);
			if (psz_id == NULL)
				return false;

			string strCtrlType = "";
			IPropertyGroup* pCtrlPropGroup = FindControlPropGroup(psz_id, strCtrlType);
			if (pCtrlPropGroup == NULL)
				return false;

			IPropertyControl* pCtrlProp = dynamic_cast<IPropertyControl*>(CreateEmptyBaseProp(OTID_CONTROL, psz_id));
			if (pCtrlProp == NULL)
				return false;

			pCtrlProp->SetControlType((char*)strCtrlType.c_str());
			pCtrlProp->SetCtrlGroupProp(pCtrlPropGroup);
			pCtrlProp->SetParentCtrlProp(pParentProp);
			pChildCtrlVec->push_back(pCtrlProp);

			if (pCtrlNode->numChild > 0)
			{
				if (!GeneralCreateWindowLayoutProp(pCtrlNode, pCtrlProp->GetChildPropControlVec(), pCtrlProp))
					return false;
			}
		}
	}

	return true;
}

IPropertyGroup* IPropertySkinManagerImpl::FindControlPropGroup(char *pszObjectId, string &strCtrlType)
{
	strCtrlType = "";
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

			strCtrlType = pGroupItem->first;
			IPropertyGroup* pFindGroup = dynamic_cast<IPropertyGroup*>(pPropBase);
			return pFindGroup;
		}
	}

	return NULL;
}

// 解析Resource.xml
bool IPropertySkinManagerImpl::BD_TranslateResourceXml(char *pszXmlPath)
{
	if (m_pKernelZipFile == NULL || pszXmlPath == NULL || strlen(pszXmlPath) <= 0)
		return false;

	ZIP_FILE *pFileItem = m_pKernelZipFile->FindUnZipFile(pszXmlPath);
	if (pFileItem == NULL)
		return false;

	if (!TranslateResourceXml(pFileItem))
		return false;

	ZIP_FILE_MAP* pFromZipMap = m_pKernelZipFile->GetUnZipFileMap();
	ZIP_FILE_MAP* pToZipMap = m_BD_SkinUnZipImageFile.GetUnZipFileMap();
	if (pFromZipMap == NULL || pToZipMap == NULL)
		return false;

	m_BD_SkinUnZipImageFile.Clear();
	for (ZIP_FILE_MAP::iterator pZipItem = pFromZipMap->begin(); pZipItem != pFromZipMap->end(); )
	{
		ZIP_FILE* pZip = pZipItem->second;
		if (pZip == NULL || ((ZIP_FILE_TYPE)(pZip->byFileType)) != ZFT_IMAGE)
		{
			pZipItem++;
			continue;
		}

		pToZipMap->insert(pair<string, ZIP_FILE*>(pZip->strFileName, pZip));
		pZipItem = pFromZipMap->erase(pZipItem);
	}

	return true;
}

bool IPropertySkinManagerImpl::SetImageFileRelevancy()
{
	if (m_pImageBasePropMap == NULL || m_pKernelZipFile == NULL)
		return false;

	for (ONE_RESOURCE_PROP_MAP::iterator pImage = m_pImageBasePropMap->begin(); pImage != m_pImageBasePropMap->end(); pImage++)
	{
		IPropertyBase* pPropBase = pImage->second;
		IPropertyImageBase* pImageBaseProp = dynamic_cast<IPropertyImageBase*>(pPropBase);
		if (pImageBaseProp == NULL || pImageBaseProp->GetImageProp() == NULL)
			continue;

		string strFileName = pImageBaseProp->GetImageProp()->strFileName;
		if (strFileName.size() <= 0)
			continue;

		ZIP_FILE *pZipFile = m_pKernelZipFile->FindUnZipFile((char*)strFileName.c_str());
		if (pZipFile == NULL)
			return false;

		pImageBaseProp->SetZipFile(pZipFile, false);
	}

	return true;
}

// 解析Controls.xml
bool IPropertySkinManagerImpl::BD_TranslateControlsXml(char *pszXmlPath)
{
	if (m_pKernelZipFile == NULL || pszXmlPath == NULL || strlen(pszXmlPath) <= 0)
		return false;

	ZIP_FILE *pFileItem = m_pKernelZipFile->FindUnZipFile(pszXmlPath);
	if (pFileItem == NULL)
		return false;

	return TranslateControlsXml(pFileItem);
}

// 解析Windows.xml
bool IPropertySkinManagerImpl::BD_TranslateWindowsXml(char *pszXmlPath)
{
	if (m_pKernelZipFile == NULL || pszXmlPath == NULL || strlen(pszXmlPath) <= 0)
		return false;

	ZIP_FILE *pFileItem = m_pKernelZipFile->FindUnZipFile(pszXmlPath);
	if (pFileItem == NULL)
		return false;

	return TranslateWindowsXml(pFileItem);
}

// 解析Layout.xml
bool IPropertySkinManagerImpl::BD_TranslateLayoutXml(char *pszXmlPath)
{
	if (m_pKernelZipFile == NULL || pszXmlPath == NULL || strlen(pszXmlPath) <= 0)
		return false;

	ZIP_FILE *pFileItem = m_pKernelZipFile->FindUnZipFile(pszXmlPath);
	if (pFileItem == NULL)
		return false;

	bool bRet = TranslateLayoutXml(pFileItem);
	m_pKernelZipFile->Clear();
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
	while (nReadCtns < (int)FileAttr.nFileSizeLow)
	{
		BYTE *pRead = FileItem.pFileData + nReadCtns;
		int nNeedRead = FileAttr.nFileSizeLow - nReadCtns;

		int nRead = fread_s(pRead, nNeedRead, 1, nNeedRead, pFile);
		nReadCtns += nRead;
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

ONE_RESOURCE_PROP_MAP* IPropertySkinManagerImpl::BD_GetWindowPropMap()
{
	return &m_LayoutWindowMap;
}

// 保存皮肤包
bool IPropertySkinManagerImpl::BD_SaveProject(char *pszSkinDir, char *pszSkinName)
{
	if (pszSkinDir == NULL || pszSkinName == NULL || m_pKernelZipFile == NULL)
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
	if (!m_pKernelZipFile->WriteZipInit(pszSkinDir, (char*)strZipFile.c_str()))
		return false;

	if (!m_pKernelZipFile->WriteZipAppendBuffer(RESOURCE_XML_NAME, (BYTE*)strResourceXmlData.c_str(), strResourceXmlData.size(), ZFT_NORMAL))
		return false;
	if (!m_pKernelZipFile->WriteZipAppendBuffer(CONTROLS_XML_NAME, (BYTE*)strControlsXmlData.c_str(), strControlsXmlData.size(), ZFT_NORMAL))
		return false;
	if (!m_pKernelZipFile->WriteZipAppendBuffer(WINDOWS_XML_NAME, (BYTE*)strWindowsXmlData.c_str(), strWindowsXmlData.size(), ZFT_NORMAL))
		return false;
	if (!m_pKernelZipFile->WriteZipAppendBuffer(LAYOUT_XML_NAME, (BYTE*)strLayoutXmlData.c_str(), strLayoutXmlData.size(), ZFT_NORMAL))
		return false;

	// 写入图片文件
	for (ZIP_FILE_MAP::iterator pZipItem = m_BD_SkinUnZipImageFile.GetUnZipFileMap()->begin();
		pZipItem != m_BD_SkinUnZipImageFile.GetUnZipFileMap()->end(); pZipItem++)
	{
		ZIP_FILE* pZip = pZipItem->second;
		if (pZip == NULL)
			continue;

		if (!m_pKernelZipFile->WriteZipAppendStruct(pZip))
			return false;
	}

	m_pKernelZipFile->TestWriteUnZipFile("E:\\01.Work\\01.GoogleSvn\\wohomehhexxie\\02.UiFeature\\01.Src\\Bin\\TestSkin\\ok\\");
	return m_pKernelZipFile->WriteZipEnd(true);
}

bool IPropertySkinManagerImpl::SaveLayoutXml(const char *pszSavePath, string &strXmlData)
{
	CUiXmlWrite XmlStrObj;

	CUiXmlWriteNode* pRootNode = XmlStrObj.CreateNode("layout");
	if (pRootNode == NULL)
		return false;

	AddIntAttrToNode(pRootNode, "area", m_AreaType);

	for (ONE_RESOURCE_PROP_MAP::iterator pWndPropItem = m_LayoutWindowMap.begin(); pWndPropItem != m_LayoutWindowMap.end(); pWndPropItem++)
	{
		IPropertyWindow *pPropWnd = dynamic_cast<IPropertyWindow*>(pWndPropItem->second);
		if (pPropWnd == NULL)
			continue;

		if (!pPropWnd->GetActivePropetry())
			continue;

		CUiXmlWriteNode* pWndNode = XmlStrObj.CreateNode(pRootNode, "window");
		if (pWndNode == NULL)
			return false;

		pWndNode->AddAttribute(SKIN_OBJECT_ID, pPropWnd->GetObjectId());

		PROP_CONTROL_VEC* pWndChildVec = pPropWnd->GetChildPropControlVec();
		if (!SaveLayoutXml_ChildCtrl(XmlStrObj, pWndNode, pWndChildVec))
			return false;
	}
	strXmlData = XmlStrObj.ToXmlString();

	SaveXmlConfigFile((char*)pszSavePath, (BYTE*)strXmlData.c_str(), strXmlData.size());
	return true;
}

bool IPropertySkinManagerImpl::SaveLayoutXml_ChildCtrl(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pNode, PROP_CONTROL_VEC* pWndChildVec)
{
	if (pWndChildVec == NULL)
		return false;

	for (int i = 0; i < (int)pWndChildVec->size(); i++)
	{
		IPropertyControl* pPropCtrl = (*pWndChildVec)[i];
		if (pPropCtrl == NULL)
			continue;

		if (!pPropCtrl->GetActivePropetry())
			continue;

		CUiXmlWriteNode* pCtrlNode = XmlStrObj.CreateNode(pNode, "ctrl");
		if (pCtrlNode == NULL)
			return false;

		pCtrlNode->AddAttribute(SKIN_OBJECT_ID, pPropCtrl->GetObjectId());

		PROP_CONTROL_VEC* pCtrlChildVec = pPropCtrl->GetChildPropControlVec();
		if (!SaveLayoutXml_ChildCtrl(XmlStrObj, pCtrlNode, pCtrlChildVec))
			return false;
	}
	return true;
}

void IPropertySkinManagerImpl::SaveXmlConfigFile(char *pszFilePath, BYTE *pData, int nDataLen)
{
	// TBD 不再输出xml文件
	return;
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

			if (!pPropBase->GetActivePropetry())
				continue;

			if (!pPropBase->AppendToXmlNode(XmlStrObj, pPropTypeNode))
				return false;
		}
	}
	strXmlData = XmlStrObj.ToXmlString();

	SaveXmlConfigFile((char*)pszSavePath, (BYTE*)strXmlData.c_str(), strXmlData.size());
	return true;
}

bool IPropertySkinManagerImpl::SaveControlsXml(const char *pszSavePath, string &strXmlData)
{
	CUiXmlWrite XmlStrObj;

	CUiXmlWriteNode* pRootNode = XmlStrObj.CreateNode("controls");
	if (pRootNode == NULL)
		return false;

	for (RESOURCE_PROP_MAP::iterator pCtrlTypeItem = m_AllCtrlPropMap.begin(); pCtrlTypeItem != m_AllCtrlPropMap.end(); pCtrlTypeItem++)
	{
		ONE_RESOURCE_PROP_MAP *pCtrlType = pCtrlTypeItem->second;
		if (pCtrlType == NULL)
			continue;

		for (ONE_RESOURCE_PROP_MAP::iterator pCtrlItem = pCtrlType->begin(); pCtrlItem != pCtrlType->end(); pCtrlItem++)
		{
			IPropertyGroup* pCtrlPropGroup = dynamic_cast<IPropertyGroup*>(pCtrlItem->second);
			if (pCtrlPropGroup == NULL)
				continue;

			if (!pCtrlPropGroup->GetActivePropetry())
				continue;

			string strCtrlType = pCtrlTypeItem->first;
			CUiXmlWriteNode* pCtrlTypeNode = XmlStrObj.CreateNode(pRootNode, strCtrlType.c_str());
			if (pCtrlTypeNode == NULL)
				return false;
			pCtrlTypeNode->AddAttribute(SKIN_OBJECT_ID, pCtrlPropGroup->GetObjectId());

			// 写入group中的数据
			if (!SaveXml_GroupProp(XmlStrObj, pCtrlTypeNode, pCtrlPropGroup))
				return false;
		}
	}
	strXmlData = XmlStrObj.ToXmlString();

	SaveXmlConfigFile((char*)pszSavePath, (BYTE*)strXmlData.c_str(), strXmlData.size());
	return true;
}

bool IPropertySkinManagerImpl::SaveXml_GroupProp(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentNode, IPropertyGroup *pPropGroup)
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

		if (!pProp->GetActivePropetry())
			continue;

		CUiXmlWriteNode* pPropNode = XmlStrObj.CreateNode(pParentNode, pProp->GetObjectType());
		if (pPropNode == NULL)
			return false;
		pPropNode->AddAttribute(SKIN_OBJECT_ID, pProp->GetObjectId());
		// 写上属性名称，便于查看
		pPropNode->AddAttribute("name", pProp->GetObjectName());

		if (pProp->GetObjectTypeId() == OTID_GROUP)
		{
			IPropertyGroup *pNextPropGroup = dynamic_cast<IPropertyGroup*>(pProp);
			if (pNextPropGroup == NULL)
				continue;

			if (!SaveXml_GroupProp(XmlStrObj, pPropNode, pNextPropGroup))
				return false;
		}
	}

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
		IPropertyGroup *pWndPropGroup = dynamic_cast<IPropertyGroup*>(pWndItem->second);
		if (pWndPropGroup == NULL)
			continue;

		if (!pWndPropGroup->GetActivePropetry())
			continue;

		CUiXmlWriteNode* pWindowNode = XmlStrObj.CreateNode(pRootNode, PROP_TYPE_WINDOW_NAME);
		if (pWindowNode == NULL)
			return false;
		pWindowNode->AddAttribute(SKIN_OBJECT_ID, pWndPropGroup->GetObjectId());

		SaveXml_GroupProp(XmlStrObj, pWindowNode, pWndPropGroup);
	}
	strXmlData = XmlStrObj.ToXmlString();

	SaveXmlConfigFile((char*)pszSavePath, (BYTE*)strXmlData.c_str(), strXmlData.size());
	return true;
}

ONE_RESOURCE_PROP_MAP* IPropertySkinManagerImpl::GetAllWindowPropMap()
{
	return &m_AllWindowPropMap;
}

// 向控件队列添加一个控件
bool IPropertySkinManagerImpl::BD_AppendControlToVec(char *pszCtrlType, IPropertyGroup* pCtrlPropGroup)
{
	if (pszCtrlType == NULL || pCtrlPropGroup == NULL)
		return false;

	string strObjId = pCtrlPropGroup->GetObjectId();
	if (strObjId.size() <= 0)
		return false;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pCtrlPropGroup);
	if (pPropBase == NULL)
		return false;

	ONE_RESOURCE_PROP_MAP* pCtrlType = NULL;
	string strCtrlType = pszCtrlType;
	RESOURCE_PROP_MAP::iterator pCtrlTypeItem = m_AllCtrlPropMap.find(strCtrlType);
	if (pCtrlTypeItem == m_AllCtrlPropMap.end())
	{
		pCtrlType = new ONE_RESOURCE_PROP_MAP;
		if (pCtrlType == NULL)
			return false;

		m_AllCtrlPropMap.insert(pair<string, ONE_RESOURCE_PROP_MAP*>(strCtrlType, pCtrlType));
	}
	else
	{
		pCtrlType = pCtrlTypeItem->second;
	}

	if (pCtrlType == NULL)
		return false;

	pCtrlType->insert(pair<string, IPropertyBase*>(strObjId, pPropBase));
	return true;
}

// 设置可以保存的有效属性
void IPropertySkinManagerImpl::BD_SetWindowPropetryActiveProp(IWindowBase *pWndBase, bool bActive)
{
	if (pWndBase == NULL)
		return;

	pWndBase->SetActivePropetry(bActive);
	IPropertyWindow* pPropWnd = pWndBase->PP_GetWindowPropetry();
	if (pPropWnd != NULL)
		pPropWnd->SetActivePropetry(bActive);

	if (pWndBase->PP_GetWindowPropetryGroup() != NULL)
		pWndBase->PP_GetWindowPropetryGroup()->SetActivePropetry(bActive);

	// 不再需要设置自身的子属性的Active标志，在创建并加载属性的时候已经设置了此标志。
//	// 设置窗口自身的属性
//	BD_SetGroupPropActiveMark(pWndBase->PP_GetWindowPropetryGroup(), bActive);

	// 设置子窗口
	BD_SetChildVecActiveMark(pWndBase->GetChildControlsVec(), bActive);
}

void IPropertySkinManagerImpl::BD_SetChildVecActiveMark(CHILD_CTRLS_VEC* pChildCtrlVec, bool bActive)
{
	if (pChildCtrlVec == NULL)
		return;

	for (CHILD_CTRLS_VEC::iterator pCtrlItem = pChildCtrlVec->begin(); pCtrlItem != pChildCtrlVec->end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl == NULL)
			continue;

		if (pCtrl->PP_GetControlPropetry() != NULL)
			pCtrl->PP_GetControlPropetry()->SetActivePropetry(bActive);

		if (pCtrl->PP_GetControlPropetryGroup() != NULL)
			pCtrl->PP_GetControlPropetryGroup()->SetActivePropetry(bActive);

		pCtrl->SetActivePropetry(bActive);
		// 不再需要设置自身的子属性的Active标志，在创建并加载属性的时候已经设置了此标志。
//		BD_SetGroupPropActiveMark(pCtrl->PP_GetControlPropetryGroup(), bActive);
		BD_SetChildVecActiveMark(pCtrl->GetChildControlsVec(), bActive);
	}
}

void IPropertySkinManagerImpl::BD_SetGroupPropActiveMark(IPropertyGroup *pPropGroup, bool bActive)
{
	if (pPropGroup == NULL || pPropGroup->GetPropVec() == NULL)
		return;

	for (GROUP_PROP_VEC::iterator pPropItem = pPropGroup->GetPropVec()->begin(); pPropItem != pPropGroup->GetPropVec()->end(); pPropItem++)
	{
		IPropertyBase* pProp = *pPropItem;
		if (pProp == NULL)
			continue;

		pProp->SetActivePropetry(bActive);
		if (pProp->GetObjectTypeId() == OTID_GROUP)
		{
			IPropertyGroup *pNextPropGroup = dynamic_cast<IPropertyGroup*>(pProp);
			BD_SetGroupPropActiveMark(pNextPropGroup, bActive);
		}
	}
}

// 删除图片
bool IPropertySkinManagerImpl::DeleteImageBase(IPropertyImageBase *pPropImgBase)
{
	if (pPropImgBase == NULL)
		return false;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pPropImgBase);
	if (pPropBase == NULL)
		return false;

	return DeletePropetryBaseProp(pPropBase);
}

// 删除属性
bool IPropertySkinManagerImpl::DeletePropetryBaseProp(IPropertyBase *pPropBase)
{
	KERNEL_CRI_SEC;
	if (pPropBase == NULL)
		return false;

	if (pPropBase->GetObjectTypeId() == OTID_IMAGE_BASE)
	{
		IPropertyImageBase *pImgBaseProp = dynamic_cast<IPropertyImageBase*>(pPropBase);
		if (pImgBaseProp == NULL)
			return false;

		return DeleteImageBaseProp(pImgBaseProp);
	}

	if (pPropBase->GetObjectTypeId() == OTID_FONT_BASE)
	{
		IPropertyFontBase *pFontBaseProp = dynamic_cast<IPropertyFontBase*>(pPropBase);
		if (pFontBaseProp == NULL)
			return false;

		// 不允许删除默认字体
		if (pFontBaseProp == m_pDefaultFontBase || lstrcmpA(pFontBaseProp->GetObjectName(), SYS_DEFAULT_FONT_NAME) == 0)
			return false;

		return DeleteFontBaseProp(pFontBaseProp);
	}

	return false;
}

bool IPropertySkinManagerImpl::DeleteFontBaseProp(IPropertyFontBase *pFontBaseProp)
{
	if (pFontBaseProp == false)
		return false;

	if (m_pFontPropMap != NULL)
	{
		for (ONE_RESOURCE_PROP_MAP::iterator pFont = m_pFontPropMap->begin(); pFont != m_pFontPropMap->end(); pFont++)
		{
			IPropertyBase* pPropBase = pFont->second;
			IPropertyFont* pFontProp = dynamic_cast<IPropertyFont*>(pPropBase);
			if (pFontProp == NULL)
				continue;

			IPropertyFontBase *pComFontBase = dynamic_cast<IPropertyFontBase*>(pFontProp->GetRelevancyProp());
			if (lstrcmpiA(pFontProp->GetRelevancyPropName(), pFontBaseProp->GetObjectName()) == 0 || pComFontBase == pFontBaseProp)
			{
				pFontProp->SetRelevancyProp(NULL);
				pFontProp->SetRelevancyPropName(NULL);
			}
		}
	}

	if (m_pFontBasePropMap != NULL)
	{
		string strObjId(pFontBaseProp->GetObjectId());
		ONE_RESOURCE_PROP_MAP::iterator pFindFontBase = m_pFontBasePropMap->find(strObjId);
		if (pFindFontBase != m_pFontBasePropMap->end())
			m_pFontBasePropMap->erase(pFindFontBase);
	}

	ReleaseBaseProp(dynamic_cast<IPropertyBase*>(pFontBaseProp));
	return true;
}

bool IPropertySkinManagerImpl::DeleteImageBaseProp(IPropertyImageBase *pImgBaseProp)
{
	if (pImgBaseProp == false)
		return false;

	if (m_pImagePropMap != NULL)
	{
		for (ONE_RESOURCE_PROP_MAP::iterator pImage = m_pImagePropMap->begin(); pImage != m_pImagePropMap->end(); pImage++)
		{
			IPropertyBase* pPropBase = pImage->second;
			IPropertyImage* pImageProp = dynamic_cast<IPropertyImage*>(pPropBase);
			if (pImageProp == NULL)
				continue;

			IPropertyImageBase *pComImgBase = dynamic_cast<IPropertyImageBase*>(pImageProp->GetRelevancyProp());
			if (lstrcmpiA(pImageProp->GetRelevancyPropName(), pImgBaseProp->GetObjectName()) == 0 || pComImgBase == pImgBaseProp)
			{
				pImageProp->SetRelevancyProp(NULL);
				pImageProp->SetRelevancyPropName(NULL);
			}
		}
	}

	if (m_pImageBasePropMap != NULL)
	{
		string strObjId(pImgBaseProp->GetObjectId());
		ONE_RESOURCE_PROP_MAP::iterator pFindImageBase = m_pImageBasePropMap->find(strObjId);
		if (pFindImageBase != m_pImageBasePropMap->end())
			m_pImageBasePropMap->erase(pFindImageBase);
	}

	ReleaseBaseProp(dynamic_cast<IPropertyBase*>(pImgBaseProp));
	return true;
}

// 取得指定组的属性
ONE_RESOURCE_PROP_MAP* IPropertySkinManagerImpl::GetOneResourcePropMap(char *pPropGroupName, bool bIsCreate)
{
	if (pPropGroupName == NULL)
		return NULL;

	ONE_RESOURCE_PROP_MAP* pPropGroupItem = NULL;
	string strPropGroup(pPropGroupName);
	RESOURCE_PROP_MAP::iterator pPropGroup = m_AllPropMap.find(strPropGroup);
	if (pPropGroup != m_AllPropMap.end())
		pPropGroupItem = pPropGroup->second;

	if (pPropGroupItem == NULL && bIsCreate)
	{
		pPropGroupItem = new ONE_RESOURCE_PROP_MAP;
		if (pPropGroupItem != NULL)
		{
			if (lstrcmpiA(strPropGroup.c_str(), PROP_TYPE_IMAGE_BASE_NAME) == 0)
			{
				m_pImageBasePropMap = pPropGroupItem;
			}
			else if (lstrcmpiA(strPropGroup.c_str(), PROP_TYPE_COLOR_BASE_NAME) == 0)
			{
				m_pColorBasePropMap = pPropGroupItem;
			}
			else if (lstrcmpiA(strPropGroup.c_str(), PROP_TYPE_CURSOR_BASE_NAME) == 0)
			{
				m_pCursorBasePropMap = pPropGroupItem;
			}
			else if (lstrcmpiA(strPropGroup.c_str(), PROP_TYPE_FONT_BASE_NAME) == 0)
			{
				m_pFontBasePropMap = pPropGroupItem;
			}
			else if (lstrcmpiA(strPropGroup.c_str(), PROP_TYPE_COLOR_NAME) == 0)
			{
				m_pColorPropMap = pPropGroupItem;
			}
			else if (lstrcmpiA(strPropGroup.c_str(), PROP_TYPE_CURSOR_NAME) == 0)
			{
				m_pCursorPropMap = pPropGroupItem;
			}
			else if (lstrcmpiA(strPropGroup.c_str(), PROP_TYPE_FONT_NAME) == 0)
			{
				m_pFontPropMap = pPropGroupItem;
			}
			else if (lstrcmpiA(strPropGroup.c_str(), PROP_TYPE_IMAGE_NAME) == 0)
			{
				m_pImagePropMap = pPropGroupItem;
			}

			m_AllPropMap.insert(pair<string, ONE_RESOURCE_PROP_MAP*>(strPropGroup, pPropGroupItem));
		}
	}

	return pPropGroupItem;
}

// 修改属性名称
bool IPropertySkinManagerImpl::BD_ModifyPropetryName(IPropertyBase *pPropBase, char *pszNewPropName)
{
	KERNEL_CRI_SEC;
	if (pPropBase == NULL || pszNewPropName == NULL)
		return false;

	if (pPropBase->GetObjectTypeId() == OTID_IMAGE_BASE)
	{
		IPropertyImageBase *pImgBaseProp = dynamic_cast<IPropertyImageBase*>(pPropBase);
		if (pImgBaseProp == NULL)
			return false;

		return ModifyImageBaseProp(pImgBaseProp, pszNewPropName);
	}

	if (pPropBase->GetObjectTypeId() == OTID_FONT_BASE)
	{
		IPropertyFontBase *pFontBaseProp = dynamic_cast<IPropertyFontBase*>(pPropBase);
		if (pFontBaseProp == NULL)
			return false;

		// 不允许修改默认字体名称
		if (pFontBaseProp == m_pDefaultFontBase || lstrcmpA(pFontBaseProp->GetObjectName(), SYS_DEFAULT_FONT_NAME) == 0)
			return false;

		return ModifyFontBaseProp(pFontBaseProp, pszNewPropName);
	}

	return false;
}

bool IPropertySkinManagerImpl::ModifyFontBaseProp(IPropertyFontBase *pFontBaseProp, char *pszNewPropName)
{
	if (pFontBaseProp == NULL || pszNewPropName == NULL)
		return false;

	string strOldName = "";
	if (m_pFontBasePropMap != NULL)
	{
		string strObjId(pFontBaseProp->GetObjectId());
		ONE_RESOURCE_PROP_MAP::iterator pFindFontBase = m_pFontBasePropMap->find(strObjId);
		if (pFindFontBase != m_pFontBasePropMap->end())
		{
			IPropertyBase* pFind = pFindFontBase->second;
			if (pFind == NULL)
				return false;

			IPropertyFontBase *pFindFontBaseProp = dynamic_cast<IPropertyFontBase*>(pFind);
			if (pFindFontBaseProp == NULL)
				return false;

			strOldName = pFindFontBaseProp->GetObjectName();
			pFindFontBaseProp->SetObjectName(pszNewPropName);
		}
	}

	if (m_pFontPropMap != NULL)
	{
		for (ONE_RESOURCE_PROP_MAP::iterator pFont = m_pFontPropMap->begin(); pFont != m_pFontPropMap->end(); pFont++)
		{
			IPropertyBase* pPropBase = pFont->second;
			IPropertyFont* pFontProp = dynamic_cast<IPropertyFont*>(pPropBase);
			if (pFontProp == NULL)
				continue;

			IPropertyFontBase *pComFontBase = dynamic_cast<IPropertyFontBase*>(pFontProp->GetRelevancyProp());
			if (lstrcmpiA(pFontProp->GetRelevancyPropName(), strOldName.c_str()) == 0 || pComFontBase == pFontBaseProp)
			{
				pFontProp->SetRelevancyPropName(pszNewPropName);
				pFontProp->SetRelevancyProp(pFontBaseProp);
			}
		}
	}

	return true;
}

bool IPropertySkinManagerImpl::ModifyImageBaseProp(IPropertyImageBase *pImgBaseProp, char *pszNewPropName)
{
	if (pImgBaseProp == NULL || pszNewPropName == NULL)
		return false;

	string strOldName = "";
	if (m_pImageBasePropMap != NULL)
	{
		string strObjId(pImgBaseProp->GetObjectId());
		ONE_RESOURCE_PROP_MAP::iterator pFindImageBase = m_pImageBasePropMap->find(strObjId);
		if (pFindImageBase != m_pImageBasePropMap->end())
		{
			IPropertyBase* pFind = pFindImageBase->second;
			if (pFind == NULL)
				return false;

			IPropertyImageBase *pFindImgBaseProp = dynamic_cast<IPropertyImageBase*>(pFind);
			if (pFindImgBaseProp == NULL)
				return false;

			strOldName = pFindImgBaseProp->GetObjectName();
			pFindImgBaseProp->SetObjectName(pszNewPropName);
		}
	}

	if (m_pImagePropMap != NULL)
	{
		for (ONE_RESOURCE_PROP_MAP::iterator pImage = m_pImagePropMap->begin(); pImage != m_pImagePropMap->end(); pImage++)
		{
			IPropertyBase* pPropBase = pImage->second;
			IPropertyImage* pImageProp = dynamic_cast<IPropertyImage*>(pPropBase);
			if (pImageProp == NULL)
				continue;

			IPropertyImageBase *pComImgBase = dynamic_cast<IPropertyImageBase*>(pImageProp->GetRelevancyProp());
			if (lstrcmpiA(pImageProp->GetRelevancyPropName(), strOldName.c_str()) == 0 || pComImgBase == pImgBaseProp)
			{
				pImageProp->SetRelevancyPropName(pszNewPropName);
				pImageProp->SetRelevancyProp(pImgBaseProp);
			}
		}
	}

	return true;
}

ZIP_FILE_MAP* IPropertySkinManagerImpl::BD_GetUnZipFileMap()
{
	return m_BD_SkinUnZipImageFile.GetUnZipFileMap();
}

// 初始化鼠标手势属性
bool IPropertySkinManagerImpl::InitCursorBasePropetry()
{
	if (m_pCursorBasePropMap == NULL)
		m_pCursorBasePropMap = GetOneResourcePropMap(PROP_TYPE_CURSOR_BASE_NAME);

	if (m_pCursorBasePropMap == NULL)
	{
		// 创建属性组
		m_pCursorBasePropMap = new ONE_RESOURCE_PROP_MAP;
		if (m_pCursorBasePropMap == NULL)
			return false;

		m_pCursorBasePropMap->clear();
		m_AllPropMap.insert(pair<string, ONE_RESOURCE_PROP_MAP*>(PROP_TYPE_CURSOR_BASE_NAME, m_pCursorBasePropMap));
	}

	if (m_pCursorBasePropMap == NULL)
		return false;

	// 正常光标 标准的箭头
	if (FindCursorBasePropetry(UF_IDC_ARROW) == NULL)
		AddCursorBasePropetry(true, UF_IDC_ARROW);

	// 十字架光标
	if (FindCursorBasePropetry(UF_IDC_CROSS) == NULL)
		AddCursorBasePropetry(true, UF_IDC_CROSS);

	// 双箭头指向西北和东南
	if (FindCursorBasePropetry(UF_IDC_SIZENWSE) == NULL)
		AddCursorBasePropetry(true, UF_IDC_SIZENWSE);

	// 双箭头指向东北和西南
	if (FindCursorBasePropetry(UF_IDC_SIZENESW) == NULL)
		AddCursorBasePropetry(true, UF_IDC_SIZENESW);

	// 双箭头指向东西
	if (FindCursorBasePropetry(UF_IDC_SIZEWE) == NULL)
		AddCursorBasePropetry(true, UF_IDC_SIZEWE);

	// 双箭头指向南北
	if (FindCursorBasePropetry(UF_IDC_SIZENS) == NULL)
		AddCursorBasePropetry(true, UF_IDC_SIZENS);

	// 四向箭头指向东、西、南、北
	if (FindCursorBasePropetry(UF_IDC_SIZEALL) == NULL)
		AddCursorBasePropetry(true, UF_IDC_SIZEALL);

	// 标准的箭头和小沙漏
	if (FindCursorBasePropetry(UF_IDC_APPSTARTING) == NULL)
		AddCursorBasePropetry(true, UF_IDC_APPSTARTING);

	// 标准的箭头和问号
	if (FindCursorBasePropetry(UF_IDC_HELP) == NULL)
		AddCursorBasePropetry(true, UF_IDC_HELP);

	// 工字光标
	if (FindCursorBasePropetry(UF_IDC_IBEAM) == NULL)
		AddCursorBasePropetry(true, UF_IDC_IBEAM);

	// 禁止圈
	if (FindCursorBasePropetry(UF_IDC_NO) == NULL)
		AddCursorBasePropetry(true, UF_IDC_NO);

	// 垂直箭头
	if (FindCursorBasePropetry(UF_IDC_UPARROW) == NULL)
		AddCursorBasePropetry(true, UF_IDC_UPARROW);

	// 沙漏
	if (FindCursorBasePropetry(UF_IDC_WAIT) == NULL)
		AddCursorBasePropetry(true, UF_IDC_WAIT);

	// 手势点击
	if (FindCursorBasePropetry(UF_IDC_HAND) == NULL)
		AddCursorBasePropetry(true, UF_IDC_HAND);

	return true;
}

IPropertyCursorBase* IPropertySkinManagerImpl::FindCursorBasePropetry(int nCursorId)
{
	if (m_pCursorBasePropMap == NULL)
		return NULL;

	IPropertyCursorBase* pFind = NULL;
	for (ONE_RESOURCE_PROP_MAP::iterator pCurItem = m_pCursorBasePropMap->begin(); pCurItem != m_pCursorBasePropMap->end(); pCurItem++)
	{
		IPropertyBase* pPropBase = pCurItem->second;
		if (pPropBase == NULL)
			continue;

		IPropertyCursorBase* pFindCom = dynamic_cast<IPropertyCursorBase*>(pPropBase);
		if (pFindCom == NULL)
			continue;

		SetCursorObjectName(pFindCom);
		if (pFindCom->GetCursorId() == nCursorId)
		{
			pFind = pFindCom;
			break;
		}
	}

	return pFind;
}

// 设置光标属性的名称
void IPropertySkinManagerImpl::SetCursorObjectName(IPropertyCursorBase *pCursorBase)
{
	if (pCursorBase == NULL || pCursorBase->GetObjectName() == NULL || strlen(pCursorBase->GetObjectName()) > 0)
		return;

	switch (pCursorBase->GetCursorId())
	{
		// 正常光标 标准的箭头
	case UF_IDC_ARROW:
		pCursorBase->SetObjectName("ARROW");
		break;

		// 双箭头指向东北和西南
	case UF_IDC_SIZENESW:
		pCursorBase->SetObjectName("SIZENESW");
		break;

		// 工字光标
	case UF_IDC_IBEAM:
		pCursorBase->SetObjectName("IBEAM");
		break;

		// 十字架光标
	case UF_IDC_CROSS:
		pCursorBase->SetObjectName("CROSS");
		break;

		// 四向箭头指向东、西、南、北
	case UF_IDC_SIZEALL:
		pCursorBase->SetObjectName("SIZEALL");
		break;

		// 垂直箭头
	case UF_IDC_UPARROW:
		pCursorBase->SetObjectName("UPARROW");
		break;

		// 双箭头指向东西
	case UF_IDC_SIZEWE:
		pCursorBase->SetObjectName("SIZEWE");
		break;

		// 双箭头指向南北
	case UF_IDC_SIZENS:
		pCursorBase->SetObjectName("SIZENS");
		break;

		// 双箭头指向西北和东南
	case UF_IDC_SIZENWSE:
		pCursorBase->SetObjectName("SIZENWSE");
		break;

		// 手势
	case UF_IDC_HAND:
		pCursorBase->SetObjectName("HAND");
		break;

		// 标准的箭头和小沙漏
	case UF_IDC_APPSTARTING:
		pCursorBase->SetObjectName("APPSTARTING");
		break;

		// 沙漏
	case UF_IDC_WAIT:
		pCursorBase->SetObjectName("WAIT");
		break;

		// 标准的箭头和问号
	case UF_IDC_HELP:
		pCursorBase->SetObjectName("HELP");
		break;

		// 禁止圈
	case UF_IDC_NO:
		pCursorBase->SetObjectName("NO");
		break;

	default:
		break;
	}
}

// 增加一个鼠标手势
bool IPropertySkinManagerImpl::AddCursorBasePropetry(bool bSysCursor, int nCursorId)
{
	if (m_pCursorBasePropMap == NULL || nCursorId <= 0)
		return false;

	IPropertyCursorBase *pCursorBase = dynamic_cast<IPropertyCursorBase*>(CreateEmptyBaseProp(OTID_CURSOR_BASE));
	if (pCursorBase == NULL)
		return false;

	pCursorBase->SetCursorId(nCursorId);
	pCursorBase->SetSystemCursor(bSysCursor);
	SetCursorObjectName(pCursorBase);

	m_pCursorBasePropMap->insert(pair<string, IPropertyBase*>(pCursorBase->GetObjectId(), pCursorBase));
	return true;
}

// 加载本地图片
IPropertyImageBase* IPropertySkinManagerImpl::LoadLocalImage(char *pszLocalImgPath)
{
	if (!FileExists(pszLocalImgPath))
		return NULL;

	IPropertyImageBase* pNewImgBase = (IPropertyImageBase*)this->CreateEmptyBaseProp(OTID_IMAGE_BASE);
	if (pNewImgBase == NULL)
		return NULL;
	pNewImgBase->SetObjectName(pNewImgBase->GetObjectId());

	CDrawingImage* pDrawingImg = pNewImgBase->GetDrawingImage();
	if (pDrawingImg == NULL)
	{
		this->DeleteImageBaseProp(pNewImgBase);
		return NULL;
	}

	pDrawingImg->CreateByFile((const char *)pszLocalImgPath);
	if (pDrawingImg->GetSafeHdc() == NULL)
	{
		this->DeleteImageBaseProp(pNewImgBase);
		return NULL;
	}

	IMAGE_BASE_PROP LocalImgProp;
	IPropertyImageBase::InitPropImageBase(&LocalImgProp);
	LocalImgProp.bIsZipFile = false;
	LocalImgProp.strFileName = pszLocalImgPath;
	LocalImgProp.ImgShowType = IST_ALL_LASHEN;
	LocalImgProp.RectInImage.left = LocalImgProp.RectInImage.top = 0;
	LocalImgProp.RectInImage.right = pDrawingImg->GetDcSize().cx;
	LocalImgProp.RectInImage.bottom = pDrawingImg->GetDcSize().cy;
	pNewImgBase->SetImageProp(&LocalImgProp);

	return pNewImgBase;
}

// 删除一张图片
bool IPropertySkinManagerImpl::BD_DeleteZipImage(ZIP_FILE* pZipImage)
{
	if (pZipImage == NULL)
		return false;

	ONE_RESOURCE_PROP_MAP* pImageBasePropMap = GetOneResourcePropMap(PROP_TYPE_IMAGE_BASE_NAME);
	if (pImageBasePropMap == NULL)
		return true;

	for (ONE_RESOURCE_PROP_MAP::iterator pImageBaseItem = pImageBasePropMap->begin(); pImageBaseItem != pImageBasePropMap->end(); pImageBaseItem++)
	{
		IPropertyBase* pPropBase = pImageBaseItem->second;
		IPropertyImageBase* pImageBaseProp = dynamic_cast<IPropertyImageBase*>(pPropBase);
		if (pImageBaseProp == NULL)
			continue;

		if (pImageBaseProp->GetZipFile() == pZipImage)
			pImageBaseProp->SetZipFile(NULL, false);
	}
	return true;
}

// 取得整个程序默认的字体信息
IPropertyFontBase* IPropertySkinManagerImpl::GetDefaultFontBase()
{
	if (m_pDefaultFontBase == NULL)
	{
		if (m_pFontBasePropMap == NULL)
			m_pFontBasePropMap = GetOneResourcePropMap(PROP_TYPE_FONT_BASE_NAME, false);

		if (m_pFontBasePropMap != NULL)
		{
			for (ONE_RESOURCE_PROP_MAP::iterator pFontBaseItem = m_pFontBasePropMap->begin(); pFontBaseItem != m_pFontBasePropMap->end(); pFontBaseItem++)
			{
				IPropertyFontBase* pFontBaseProp = dynamic_cast<IPropertyFontBase*>(pFontBaseItem->second);
				if (pFontBaseProp == NULL)
					continue;

				if (lstrcmpA(pFontBaseProp->GetObjectName(), SYS_DEFAULT_FONT_NAME) == 0)
				{
					m_pDefaultFontBase = pFontBaseProp;
					break;
				}
			}
		}
	}

	if (m_pDefaultFontBase == NULL)
	{
		m_pDefaultFontBase = dynamic_cast<IPropertyFontBase*>(CreateEmptyBaseProp(OTID_FONT_BASE));
		if (m_pDefaultFontBase != NULL)
			m_pDefaultFontBase->SetObjectName(SYS_DEFAULT_FONT_NAME);
	}

	return m_pDefaultFontBase;
}
