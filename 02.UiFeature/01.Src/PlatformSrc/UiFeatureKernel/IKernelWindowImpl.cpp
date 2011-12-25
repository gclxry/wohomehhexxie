
#include "StdAfx.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "IKernelWindowImpl.h"
#include "IWindowBaseImpl.h"
#include "WindowSubclass.h"

// 内核对【对话框】的接口
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

// 一个对话框释放皮肤资源
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

// 一个对话框从一个皮肤包里使用指定的对话框皮肤资源初始化自己
IWindowBase* IKernelWindowImpl::InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName)
{
	if (!::IsWindow(hWnd) || pszSkinPath == NULL || pszWndName == NULL || strlen(pszSkinPath) <= 0 || strlen(pszWndName) <= 0)
		return NULL;

	// 开始子类化
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

	// 初始化窗口
	pWndBase->InitWindowBase(hWnd, pszSkinPath, pszWndName);

	// 记录到窗口队列中
	m_WndImplMap.insert(pair<HWND, IWindowBaseImpl*>(hWnd, pWndBaseImpl));
	return pWndBase;
}
