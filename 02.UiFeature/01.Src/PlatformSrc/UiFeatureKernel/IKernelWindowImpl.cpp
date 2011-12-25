
#include "StdAfx.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "IKernelWindowImpl.h"
#include "IWindowBaseImpl.h"
#include "WindowSubclass.h"

// �ں˶ԡ��Ի��򡿵Ľӿ�
IKernelWindow *GetKernelWindowInterface()
{
	return IKernelWindowImpl::GetInstance();
}

IKernelWindowImpl::IKernelWindowImpl(void)
{
	for (WINDOW_IMPL_MAP::iterator pWndItem = m_WndImplMap.begin(); pWndItem != m_WndImplMap.end(); pWndItem++)
	{
		IWindowBaseImpl* pDelWnd = pWndItem->second;
		SAFE_DELETE(pDelWnd);
	}
	m_WndImplMap.clear();
}

IKernelWindowImpl::~IKernelWindowImpl(void)
{
}

IKernelWindow* IKernelWindowImpl::GetInstance()
{
	static IKernelWindowImpl _KernelWindowInstance;
	return &_KernelWindowInstance;
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
