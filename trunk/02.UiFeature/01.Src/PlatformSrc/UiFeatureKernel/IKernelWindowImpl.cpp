
#include "StdAfx.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IFeatureObject.h"
#include "..\..\Inc\ICommonFun.h"
#include "IKernelWindowImpl.h"
#include "IWindowBaseImpl.h"
#include "WindowSubclass.h"
#include "ControlImpl.h"
#include "IPropertySkinManagerImpl.h"
#include "..\..\Inc\ICtrlInterface.h"
#include "..\..\Inc\IPropertyControl.h"

// �ں˶ԡ��Ի��򡿵Ľӿ�
IKernelWindow *GetKernelWindowInterface()
{
	return IKernelWindowImpl::GetInstance();
}

IKernelWindowImpl::IKernelWindowImpl(void)
{
	m_nBuilderHwnd = 1;
	m_CtrlRegMap.clear();
	m_pSkinMgr = (IPropertySkinManagerImpl *)GetSkinManager();

	m_pControlMgr = NULL;
	m_hControlDll = NULL;
	string strPath = PathHelper(NAME_CONTROL_DLL);
	if (strPath.size() > 0)
	{
		m_hControlDll = ::LoadLibraryA(strPath.c_str());
		if (m_hControlDll != NULL)
		{
			GETCONTROLMANAGER GetControl = (GETCONTROLMANAGER)::GetProcAddress(m_hControlDll, "GetControlManager");
			if (GetControl != NULL)
				m_pControlMgr = GetControl();
		}
	}
}

IKernelWindowImpl::~IKernelWindowImpl(void)
{
	SAFE_FREE_LIBRARY(m_hControlDll);
	ReleaseKernelWindow();
}

void IKernelWindowImpl::ReleaseKernelWindow()
{
	for (WINDOW_IMPL_MAP::iterator pWndItem = m_WndImplMap.begin(); pWndItem != m_WndImplMap.end(); pWndItem++)
	{
		IWindowBaseImpl* pDelWnd = pWndItem->second;
		SAFE_DELETE(pDelWnd);
	}
	m_WndImplMap.clear();
	m_CtrlRegMap.clear();
}

IKernelWindow* IKernelWindowImpl::GetInstance()
{
	static IKernelWindowImpl _KernelWindowInstance;
	return &_KernelWindowInstance;
}

// ȡ������֧�ֵĿؼ�
CONTROL_REG_MAP* IKernelWindowImpl::BD_GetRegisterControl()
{
	CControlImpl::GetInstance()->SetRegControlMap(&m_CtrlRegMap);
	return &m_CtrlRegMap;
}

IPropertySkinManager* IKernelWindowImpl::GetSkinManager()
{
	return IPropertySkinManagerImpl::GetInstance();
}

// һ���Ի����ͷ�Ƥ����Դ
void IKernelWindowImpl::PG_ReleaseFeatureSkin(HWND hWnd)
{
	WINDOW_IMPL_MAP::iterator pWndImplItem = m_WndImplMap.find(hWnd);
	if (pWndImplItem != m_WndImplMap.end())
	{
		IWindowBaseImpl* pWndImpl = pWndImplItem->second;
		SAFE_DELETE(pWndImpl);
		m_WndImplMap.erase(pWndImplItem);
	}
}

// �ر�һ������
bool IKernelWindowImpl::BD_CloseProject()
{
	ReleaseKernelWindow();
	if (m_pSkinMgr != NULL)
		m_pSkinMgr->ReleaseSkinManagerPropetry();

	return true;
}

// һ���Ի����һ��Ƥ������ʹ��ָ���ĶԻ���Ƥ����Դ��ʼ���Լ�
IWindowBase* IKernelWindowImpl::PG_InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName)
{
	if (!::IsWindow(hWnd) || pszSkinPath == NULL || pszWndName == NULL || strlen(pszSkinPath) <= 0 || strlen(pszWndName) <= 0)
		return NULL;

	// ��ʼ���໯
	if (CWindowSubclass::GetInstance()->FindSubWindow(hWnd) != NULL)
		return NULL;

	IWindowBaseImpl *pWndBaseImpl = new IWindowBaseImpl;
	if (pWndBaseImpl == NULL)
		return NULL;

	IWindowBase* pWndBase = (dynamic_cast<IWindowBase*>(pWndBaseImpl));
	if (!CWindowSubclass::GetInstance()->SubWindow(hWnd, pWndBase))
	{
		SAFE_DELETE(pWndBaseImpl);
		return NULL;
	}

	// ��ʼ������
	pWndBase->PG_InitWindowBase(hWnd, pszSkinPath, pszWndName);

	// ��¼�����ڶ�����
	m_WndImplMap.insert(pair<HWND, IWindowBaseImpl*>(hWnd, pWndBaseImpl));
	return pWndBase;
}

// ����һ��Builderʹ�õĿյĴ���
IWindowBase* IKernelWindowImpl::BD_CreateWindowEmptyPropetry()
{
	if (m_pSkinMgr == NULL)
		return NULL;

	IPropertyGroup *pWindowPropGroup = dynamic_cast<IPropertyGroup*>(m_pSkinMgr->CreateEmptyBaseProp(OTID_GROUP));
	if (pWindowPropGroup == NULL)
		return NULL;

	IPropertyWindow *pPropWindow = dynamic_cast<IPropertyWindow*>(m_pSkinMgr->CreateEmptyBaseProp(OTID_WINDOW));
	if (pPropWindow == NULL)
		return NULL;

	pPropWindow->SetWindowPropGroup(pWindowPropGroup);

	// ����objecid
	char szId[MAX_PATH];
	memset(szId, 0, MAX_PATH);
	sprintf_s(szId, MAX_PATH-1, "%s%d", PROP_TYPE_WINDOW_NAME, m_pSkinMgr->GetNewId());
	pWindowPropGroup->SetObjectId(szId);
	pPropWindow->SetObjectId(szId);

	IWindowBaseImpl *pWndBaseImpl = new IWindowBaseImpl;
	if (pWndBaseImpl == NULL)
		return NULL;

	IWindowBase* pWndBase = (dynamic_cast<IWindowBase*>(pWndBaseImpl));
	if (pWndBase == NULL)
	{
		SAFE_DELETE(pWndBaseImpl);
		return NULL;
	}
	// ��ʼ����builder�е�����
	pWndBase->BD_InitWindowBase(pPropWindow);

	// ��¼�����ڶ�����
	m_WndImplMap.insert(pair<HWND, IWindowBaseImpl*>((HWND)m_nBuilderHwnd++, pWndBaseImpl));
	m_pSkinMgr->GetAllWindowPropMap()->insert(pair<string, IPropertyBase*>(pWndBase->GetObjectId(), pWindowPropGroup));
	return pWndBase;
}

// ����һ��Builderʹ�õĿյĴ���
IWindowBase* IKernelWindowImpl::BD_CreateWindowByPropetry(IPropertyWindow *pPropWnd)
{
	if (pPropWnd == NULL)
		return NULL;

	IWindowBaseImpl *pWndBaseImpl = new IWindowBaseImpl;
	if (pWndBaseImpl == NULL)
		return NULL;

	IWindowBase* pWndBase = (dynamic_cast<IWindowBase*>(pWndBaseImpl));
	if (pWndBase == NULL)
	{
		SAFE_DELETE(pWndBaseImpl);
		return NULL;
	}
	// ��ʼ����builder�е�����
	pWndBase->BD_InitWindowBase(pPropWnd);

	// ��¼�����ڶ�����
	m_WndImplMap.insert(pair<HWND, IWindowBaseImpl*>((HWND)m_nBuilderHwnd++, pWndBaseImpl));
	m_pSkinMgr->GetAllWindowPropMap()->insert(pair<string, IPropertyBase*>(pWndBase->GetObjectId(), pWndBase->PP_GetWindowPropetryGroup()));
	return pWndBase;
}

// ����Ƥ����
bool IKernelWindowImpl::BD_SaveProject(char *pszSkinDir, char *pszSkinName)
{
	if (m_pSkinMgr == NULL)
		return false;
	
	return m_pSkinMgr->BD_SaveProject(pszSkinDir, pszSkinName);
}

// ����/��һ���µ�Ƥ������
bool IKernelWindowImpl::BD_OpenProject(char *pszSkinDir, char *pszSkinName)
{
	if (pszSkinDir == NULL || pszSkinName == NULL || m_pSkinMgr == NULL)
		return false;

	m_pSkinMgr->ReleaseSkinManagerPropetry();

	// ����zip�ļ�
	string strZipPath = pszSkinDir;
	if (pszSkinDir[strlen(pszSkinDir) - 1] != '\\')
		strZipPath += "\\";
	strZipPath += pszSkinName;
	strZipPath += NAME_SKIN_FILE_EX_NAME;

	if (!CZipFileList::GetInstance()->ReadZipFile(strZipPath.c_str()))
		return false;

	return true;
}

// ����һ��Builderʹ�õĿյĿؼ�
IControlBase* IKernelWindowImpl::BD_CreateControlEmptyPropetry(IWindowBase *pParentWnd, IControlBase *pParentCtrl, char *pszNewCtrlTypeName)
{
	if (m_pControlMgr == NULL || m_pSkinMgr == NULL || pParentWnd == NULL || pszNewCtrlTypeName == NULL || strlen(pszNewCtrlTypeName) <= 0)
		return NULL;

	// �����¿ؼ���ObjectID
	string strObjId(pParentWnd->GetObjectId());
	if (pParentCtrl != NULL)
	{
		strObjId = pParentCtrl->GetObjectId();
	}

	char szId[1024];
	memset(szId, 0, 1024);
	sprintf_s(szId, 1023, "%s.%s%d", strObjId.c_str(), pszNewCtrlTypeName, m_pSkinMgr->GetNewId());

	// �����¿ؼ�
	ICtrlInterface* pCtrlIfc = m_pControlMgr->CreateCtrl(pszNewCtrlTypeName, szId);
	if (pCtrlIfc == NULL)
		return NULL;

	IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(pCtrlIfc);
	if (pCtrlBase == NULL)
	{
		m_pControlMgr->ReleaseCtrl(&pCtrlIfc);
		return NULL;
	}
	pCtrlBase->SetPropertySkinManager(m_pSkinMgr);

	// ����ؼ�����
	if (pParentCtrl != NULL)
		pParentCtrl->AppendChildContrl(pCtrlBase);
	else
		pParentWnd->AppendChildContrl(pCtrlBase);

	// �����¿ؼ�������
	IPropertyGroup *pCtrlPropGroup = dynamic_cast<IPropertyGroup*>(m_pSkinMgr->CreateEmptyBaseProp(OTID_GROUP));
	if (pCtrlPropGroup == NULL)
	{
		m_pControlMgr->ReleaseCtrl(&pCtrlIfc);
		return NULL;
	}

	IPropertyControl *pPropCtrl = dynamic_cast<IPropertyControl*>(m_pSkinMgr->CreateEmptyBaseProp(OTID_CONTROL));
	if (pPropCtrl == NULL)
	{
		m_pControlMgr->ReleaseCtrl(&pCtrlIfc);
		return NULL;
	}
	pPropCtrl->SetCtrlGroupProp(pCtrlPropGroup);
	pCtrlBase->BD_InitControlBase(pPropCtrl);
	pCtrlBase->OnFinalCreate();
	return pCtrlBase;
}
