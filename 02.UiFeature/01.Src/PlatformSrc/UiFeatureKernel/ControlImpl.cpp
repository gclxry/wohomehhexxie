
#include "StdAfx.h"
#include "ControlImpl.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"

CControlImpl::CControlImpl(void)
{
	m_CtrlDllVec.clear();
	LoadControlDll();
}

CControlImpl::~CControlImpl(void)
{
	for (CONTROL_DLL_VEC::iterator pCtrlItem = m_CtrlDllVec.begin(); pCtrlItem != m_CtrlDllVec.end(); pCtrlItem++)
	{
		CONTRL_DLL_INFO &CtrlDllInfo = *pCtrlItem;
		SAFE_FREE_LIBRARY(CtrlDllInfo.hDll);
	}
	m_CtrlDllVec.clear();
}

CControlImpl* CControlImpl::GetInstance()
{
	static CControlImpl _ControlImplInstance;
	return &_ControlImplInstance;
}

bool CControlImpl::LoadControlDll()
{
	if (m_CtrlDllVec.size() > 0)
		return true;

	string strPath = PathHelper(NAME_UIFEATURE_XML);
	if (strPath.size() <= 0)
		return false;

	HANDLE hFile = ::CreateFileA(strPath.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	DWORD dwSize = ::GetFileSize(hFile, NULL);
	if (dwSize == INVALID_FILE_SIZE)
	{
		::CloseHandle(hFile);
		return false;
	}

	char *pszData = (char*)malloc(dwSize + 32);
	if (pszData == NULL)
	{
		::CloseHandle(hFile);
		return false;
	}
	memset(pszData, 0, dwSize + 32);

	DWORD dwRead = 0;
	if (!::ReadFile(hFile, pszData, dwSize, &dwRead, NULL))
	{
		::CloseHandle(hFile);
		SAFE_FREE(pszData);
		return false;
	}

	bool bRet = true;
	XmlState xmlState = { 0 };
	JabberXmlInitState(&xmlState);
	int bytesParsed = JabberXmlParse(&xmlState, pszData, strlen(pszData));
	XmlNode *pPData  = JabberXmlGetChild(&xmlState.root, "uifeature");
	if (pPData != NULL)
	{
		XmlNode *p_controldll  = JabberXmlGetChild(pPData, "controldll");
		if (p_controldll != NULL)
		{
			int nItemCount = p_controldll->numChild;
			for (int i = 0; i < nItemCount; i++)
			{
				XmlNode* pItem = JabberXmlGetNthChildWithoutTag(p_controldll, i);
				if (pItem)
				{
					char* psz_path = JabberXmlGetAttrValue(pItem, "path");
					if (psz_path != NULL)
					{
						CONTRL_DLL_INFO DllInfo;
						DllInfo.strPath = PathHelper(psz_path);
						DllInfo.hDll = ::LoadLibraryA(DllInfo.strPath.c_str());
						if (DllInfo.hDll == NULL)
							continue;

						GETCONTROLMANAGER GetControl = (GETCONTROLMANAGER)::GetProcAddress(DllInfo.hDll, "GetControlManager");
						if (GetControl == NULL)
							continue;

						DllInfo.pCtrlMgr = GetControl();
						if (DllInfo.pCtrlMgr == NULL)
							continue;

						m_CtrlDllVec.push_back(DllInfo);
					}
				}
			}
		}
		else
		{
			bRet = false;
		}
	}
	else
	{
		bRet = false;
	}

	JabberXmlDestroyState(&xmlState);
	::CloseHandle(hFile);
	SAFE_FREE(pszData);
	return bRet;
}

void CControlImpl::SetRegControlMap(CONTROL_REG_MAP *pCtrlMap)
{
	if (pCtrlMap == NULL)
		return;
	pCtrlMap->clear();

	for (CONTROL_DLL_VEC::iterator pCtrlItem = m_CtrlDllVec.begin(); pCtrlItem != m_CtrlDllVec.end(); pCtrlItem++)
	{
		CONTRL_DLL_INFO &CtrlDllInfo = *pCtrlItem;
		if (CtrlDllInfo.pCtrlMgr != NULL)
			CtrlDllInfo.pCtrlMgr->SetRegControlMap(pCtrlMap);
	}
}

// 创建一个控件，参数为步骤1的宏
ICtrlInterface* CControlImpl::CreateCtrl(char *pCtrlType)
{
	ICtrlInterface* pNewCtrl = NULL;
	for (CONTROL_DLL_VEC::iterator pCtrlItem = m_CtrlDllVec.begin(); pCtrlItem != m_CtrlDllVec.end(); pCtrlItem++)
	{
		CONTRL_DLL_INFO &CtrlDllInfo = *pCtrlItem;
		if (CtrlDllInfo.pCtrlMgr != NULL)
		{
			pNewCtrl = CtrlDllInfo.pCtrlMgr->CreateCtrl(pCtrlType);
			if (pNewCtrl != NULL)
				return pNewCtrl;
		}
	}
	return pNewCtrl;
}

// 销毁一个控件
bool CControlImpl::ReleaseCtrl(ICtrlInterface **ppCtrl)
{
	if (ppCtrl == NULL || *ppCtrl == NULL)
		return false;

	for (CONTROL_DLL_VEC::iterator pCtrlItem = m_CtrlDllVec.begin(); pCtrlItem != m_CtrlDllVec.end(); pCtrlItem++)
	{
		CONTRL_DLL_INFO &CtrlDllInfo = *pCtrlItem;
		if (CtrlDllInfo.pCtrlMgr != NULL && CtrlDllInfo.pCtrlMgr->ReleaseCtrl(ppCtrl))
			return true;
	}

	SAFE_DELETE(*ppCtrl);
	return true;
}
