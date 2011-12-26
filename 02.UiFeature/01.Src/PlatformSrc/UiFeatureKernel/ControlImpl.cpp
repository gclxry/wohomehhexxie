
#include "StdAfx.h"
#include "ControlImpl.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"

CControlImpl::CControlImpl(void)
{
	m_hControlDll = NULL;
}

CControlImpl::~CControlImpl(void)
{
	SAFE_FREE_LIBRARY(m_hControlDll);
}

CControlImpl* CControlImpl::GetInstance()
{
	static CControlImpl _ControlImplInstance;
	return &_ControlImplInstance;
}

bool CControlImpl::LoadDll()
{
	if (m_hControlDll != NULL)
		return true;

	string strPath = GetDllPath(NAME_CONTROL_DLL);
	if (strPath.size() <= 0)
		return false;

	m_hControlDll = ::LoadLibraryA(strPath.c_str());
	return (m_hControlDll != NULL);
}

IControlManager* CControlImpl::GetControlManager()
{
	if (!LoadDll())
		return NULL;

	GETCONTROLMANAGER GetControl = (GETCONTROLMANAGER)::GetProcAddress(m_hControlDll, "GetControlManager");
	if (GetControl == NULL)
		return NULL;

	IControlManager * pMgr = GetControl();
	return pMgr;
}

void CControlImpl::SetRegControlMap(CONTROL_REG_MAP *pCtrlMap)
{
	IControlManager * pMgr = CControlImpl::GetInstance()->GetControlManager();
	if (pMgr != NULL)
		pMgr->SetRegControlMap(pCtrlMap);
}
