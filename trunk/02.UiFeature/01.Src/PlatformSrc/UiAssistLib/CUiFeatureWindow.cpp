
#include "stdafx.h"
#include <assert.h>
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\UiFeatureKernel.h"

CUiFeatureWindow::CUiFeatureWindow()
{
	m_hWnd = NULL;
	m_pWindowBase = NULL;
	m_strWndText = "Welcome UiFeature";
	m_hParentWnd = NULL;
	m_lParam = NULL;

	INIT_RECT(m_rctCreate);
	m_nCreateShow = SW_SHOW;
	m_hCreateWaitEvent = NULL;
	m_hUiThread = NULL;
	m_dwUiThreadId = 0;

	m_hKernelDll = NULL;
	m_pUiFeatureKernel = NULL;
	m_strKernelDllPath = "";
	m_strSkinPath = "";
	m_strSkinWndName = "";
}

CUiFeatureWindow::~CUiFeatureWindow()
{
	SAFE_FREE_LIBRARY(m_hKernelDll);
	CloseWindow();
	SAFE_CLOSE_HANDLE(m_hUiThread);
	m_dwUiThreadId = 0;
}

bool CUiFeatureWindow::CreateWindowWithNewThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, LPARAM lParam)
{
	return false;
}

// �ؼ�������Ϣ�ӿ�
LRESULT CUiFeatureWindow::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

IWindowBase* CUiFeatureWindow::GetUiFeatureWindow()
{
	return m_pWindowBase;
}

bool CUiFeatureWindow::InitInstance()
{
	m_hWnd = ::CreateWindowExA(0, FEATURE_CLASS_NAME, m_strWndText.c_str(), WS_OVERLAPPED | WS_THICKFRAME,
		m_rctCreate.left, m_rctCreate.top, RECT_WIDTH(m_rctCreate), RECT_HEIGHT(m_rctCreate), m_hParentWnd, NULL, ::GetModuleHandle(NULL), this);

	// ���ô����Ի������
	SetCreateWindowParam(m_lParam);

	// �Ի����ʼ��
	if (IS_SAFE_HANDLE(m_hWnd))
	{
		IControlMessage *pCtrlMsg = dynamic_cast<IControlMessage*>(this);
		if (pCtrlMsg == NULL)
		{
			assert(false);
			return false;
		}

		m_pWindowBase = m_pUiFeatureKernel->PG_InitFeatureSkin(m_hWnd, (char*)m_strSkinPath.c_str(), (char*)m_strSkinWndName.c_str());
		if (m_pWindowBase == NULL)
		{
			assert(false);
			return false;
		}

		// ���ÿؼ��ص�
		m_pWindowBase->SetCtrlMsgCallBack(pCtrlMsg);
		if (IS_RECT_EMPTY(m_rctCreate))
		{
			SIZE WndSize = m_pWindowBase->PP_GetWindowPropSize();
			INIT_RECT(m_rctCreate);
			m_rctCreate.right = WndSize.cx;
			m_rctCreate.bottom = WndSize.cy;
			this->MoveWindow(m_rctCreate);
			this->CenterWindow();
		}

		OnCreate();
		this->ShowWindow(SW_HIDE);
	}

	return IS_SAFE_HANDLE(m_hWnd);
}

LRESULT CUiFeatureWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	switch (nMsgId)
	{
		// ��ʼ���Ի������
	case UM_INIT_WINDOW_ERROR:
		OnInitWindowEnd((int)wParam);
		break;

		// ��ʼ���Ի���ɹ�
	case UM_INIT_WINDOW_SUCCESS:
		OnInitWindowEnd(0);
		break;

	default:
		break;
	}

	return CWin32Window::WndProc(nMsgId, wParam, lParam);
}

// ��ʼ���Ի������
void CUiFeatureWindow::OnInitWindowEnd(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		// �ɹ�
		this->ShowWindow(m_nCreateShow);
	}
	else
	{
		// ʧ��
		char szError[MAX_PATH];
		memset(szError, 0, MAX_PATH);
		sprintf_s(szError, MAX_PATH, "����Feature���ڴ��󣬴����룺%d", nErrorCode);
		MessageBoxA(NULL, szError, "�ں˴���", MB_OK | MB_ICONERROR);
	}
}

// ����һ�����ڣ�������
// char* pszDllDir��UiFeatureKernel.dll��ȫ·��
// char* pszSkinPath��*.ufdƤ���ļ���ȫ·��
// char *pszWndName��*.ufdƤ���ļ��жԻ��������
// HWND hParent��������
// RECT WndRect��������ʾλ�ã�����Ϊ��Ļλ��
// int nShow����ʾģʽ���磺SW_SHOW��SW_HIDE
// LPARAM lParam����������ʱ����Ĳ���������ͨ�� GetCreateWindowParam ����ȡ��
bool CUiFeatureWindow::CreateFeatureWindow(char* pszKernelDllPath, char* pszSkinPath, char *pszSkinWndName, HWND hParent, RECT WndRect, int nShow, LPARAM lParam)
{
	if (pszKernelDllPath == NULL || pszSkinPath == NULL || pszSkinWndName == NULL)
		return false;

	m_strKernelDllPath = pszKernelDllPath;
	m_strSkinPath = pszSkinPath;
	m_strSkinWndName = pszSkinWndName;

	HMODULE m_hKernelDll = ::LoadLibraryA(m_strKernelDllPath.c_str());
	if (m_hKernelDll == NULL)
		return false;

	GETKERNELWINDOWINTERFACE GetKernel = (GETKERNELWINDOWINTERFACE)::GetProcAddress(m_hKernelDll, "GetKernelWindowInterface");
	if (GetKernel == NULL)
	{
		SAFE_FREE_LIBRARY(m_hKernelDll);
		return false;
	}

	m_pUiFeatureKernel = GetKernel();
	if (m_pUiFeatureKernel == NULL)
	{
		SAFE_FREE_LIBRARY(m_hKernelDll);
		return false;
	}

	return CWin32Window::CreateWindowWithNewThread(hParent, WndRect, "Welcome UiFeature", nShow, lParam);
}
