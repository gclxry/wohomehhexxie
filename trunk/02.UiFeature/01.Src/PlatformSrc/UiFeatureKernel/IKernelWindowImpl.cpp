
#include "StdAfx.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IFeatureObject.h"
#include "IKernelWindowImpl.h"
#include "IWindowBaseImpl.h"
#include "WindowSubclass.h"
#include "ControlImpl.h"
#include "IPropertySkinManagerImpl.h"

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
}

IKernelWindowImpl::~IKernelWindowImpl(void)
{
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
CONTROL_REG_MAP* IKernelWindowImpl::BuilderRegisterControl()
{
	CControlImpl::GetInstance()->SetRegControlMap(&m_CtrlRegMap);
	return &m_CtrlRegMap;
}

IPropertySkinManager* IKernelWindowImpl::GetSkinManager()
{
	return IPropertySkinManagerImpl::GetInstance();
}

// һ���Ի����ͷ�Ƥ����Դ
void IKernelWindowImpl::ReleaseFeatureSkin(HWND hWnd)
{
	WINDOW_IMPL_MAP::iterator pWndImplItem = m_WndImplMap.find(hWnd);
	if (pWndImplItem != m_WndImplMap.end())
	{
		IWindowBaseImpl* pWndImpl = pWndImplItem->second;
		SAFE_DELETE(pWndImpl);
		m_WndImplMap.erase(pWndImplItem);
	}
}

// һ���Ի����һ��Ƥ������ʹ��ָ���ĶԻ���Ƥ����Դ��ʼ���Լ�
IWindowBase* IKernelWindowImpl::InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName)
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
	pWndBase->InitWindowBase(hWnd, pszSkinPath, pszWndName);

	// ��¼�����ڶ�����
	m_WndImplMap.insert(pair<HWND, IWindowBaseImpl*>(hWnd, pWndBaseImpl));
	return pWndBase;
}

// ����һ��Builderʹ�õĴ���
IWindowBase* IKernelWindowImpl::BuilderCreateWindow()
{
	IPropertyGroup *pWindowProp = (IPropertyGroup*)m_pSkinMgr->CreateEmptyBaseProp(PT_GROUP);
	if (pWindowProp == NULL)
		return NULL;

	// ����objecid
	char szId[MAX_PATH];
	memset(szId, 0, MAX_PATH);
	sprintf_s(szId, MAX_PATH-1, "%s%d", PROP_TYPE_WINDOW_NAME, m_pSkinMgr->GetNewId());
	pWindowProp->SetObjectId(szId);

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
	pWndBase->BuilderInitWindowBase(pWindowProp);

	// ��¼�����ڶ�����
	m_WndImplMap.insert(pair<HWND, IWindowBaseImpl*>((HWND)m_nBuilderHwnd++, pWndBaseImpl));
	return pWndBase;
}
