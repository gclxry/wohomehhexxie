
#include "stdafx.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\UiFeatureKernel.h"

#define FEATURE_CLASS_NAME						"UiFeatureWindow"

// ��ǰ��ʾ�Ĵ���map
typedef map<HWND, CUiFeatureWindow*> FW_MAP;
// ��Ϣ�������໯
FW_MAP g_FeatureWndMap;
LRESULT CALLBACK Win32WndProc(HWND hWnd, UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	switch (nMsgId)
	{
		// ����������Ϣ
	case WM_NCCREATE:
		{
			CUiFeatureWindow *pDlg = (CUiFeatureWindow *)(((LPCREATESTRUCT)lParam)->lpCreateParams);
			if (pDlg != NULL)
			{
				g_FeatureWndMap.insert(pair<HWND, CUiFeatureWindow*>(hWnd, pDlg));
				pDlg->SetSafeHandle(hWnd);
				return pDlg->WndProc(nMsgId, wParam, lParam);
			}
		}
		break;

		// ������Ϣ
	default:
		{
			FW_MAP::iterator pDuiWnd = g_FeatureWndMap.find(hWnd);
			if (pDuiWnd != g_FeatureWndMap.end())
			{
				CUiFeatureWindow *pDlg = pDuiWnd->second;
				if (nMsgId == WM_NCDESTROY)
					g_FeatureWndMap.erase(pDuiWnd);

				if (pDlg != NULL)
				{
					LRESULT lRst = pDlg->WndProc(nMsgId, wParam, lParam);
					//if (nMsgId == WM_NCDESTROY)
					//	pDlg->_PostEndThread();
					return lRst;
				}
			}
		}
		break;
	}

	return ::DefWindowProc(hWnd, nMsgId, wParam, lParam);
}

// �����߳�
UINT WindowUiThread(LPVOID lpVoid)
{
	if (lpVoid == NULL)
		return -1;

	CUiFeatureWindow *pWindow = (CUiFeatureWindow*)lpVoid;
	pWindow->_BeginWindowThread();
	return 0;
}

void CUiFeatureWindow::_BeginWindowThread()
{
	// �����Ի���
	RegisterClass();
	InitInstance();
	::SetEvent(m_hCreateWaitEvent);

	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_QUIT)
			break;

		if (PreTranslateMessage(msg))
			continue;

		if (!::TranslateAccelerator(msg.hwnd, NULL, &msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}

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

// �ؼ�������Ϣ�ӿ�
LRESULT CUiFeatureWindow::OnCtrlMessage(IControlBase* pCtrl, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

// ȡ�ô��ھ��
HWND CUiFeatureWindow::GetSafeHandle()
{
	return m_hWnd;
}

// �õ�������Ļ����
RECT CUiFeatureWindow::GetWindowRect()
{
	RECT RetRect;
	INIT_RECT(RetRect);

	if (IS_SAFE_HANDLE(m_hWnd))
		::GetWindowRect(m_hWnd, &RetRect);

	return RetRect;
}

// �õ��ͻ�������
RECT CUiFeatureWindow::GetClientRect()
{
	RECT RetRect;
	INIT_RECT(RetRect);

	if (IS_SAFE_HANDLE(m_hWnd))
	{
		::GetWindowRect(m_hWnd, &RetRect);
		int nW = RetRect.right - RetRect.left;
		int nH = RetRect.bottom - RetRect.top;

		INIT_RECT(RetRect);
		RetRect.right = nW;
		RetRect.bottom = nH;
	}

	return RetRect;
}

IWindowBase* CUiFeatureWindow::GetUiFeatureWindow()
{
	return m_pWindowBase;
}

// ���ô��ھ��
void CUiFeatureWindow::SetSafeHandle(HWND hWnd)
{
	if (!IS_SAFE_HANDLE(m_hWnd))
		m_hWnd = hWnd;
}

// ȡ�ô��ڱ�������
const char* CUiFeatureWindow::GetWindowText()
{
	return m_strWndText.c_str();
}

// ���ô��ڱ�������
void CUiFeatureWindow::SetWindowText(char* pstrWndText)
{
	if (pstrWndText == NULL)
		return;

	if (IS_SAFE_HANDLE(m_hWnd))
	{
		m_strWndText = pstrWndText;
		::SetWindowTextA(m_hWnd, pstrWndText);
	}
}

// ͬWindowsAPI��IsWindow
bool CUiFeatureWindow::IsWindow()
{
	return (::IsWindow(m_hWnd) == TRUE);
}

// �������Ƶ���Ļ����
void CUiFeatureWindow::CenterWindow()
{
	RECT WndRect = GetClientRect();
	int cx = RECT_WIDTH(WndRect);
	int cy = RECT_HEIGHT(WndRect);

	if (IS_SAFE_HANDLE(m_hWnd) && cx > 0 && cy > 0)
	{
		// ����Ĭ�ϴ�С
		RECT WorkArea, CenterRect;
		INIT_RECT(WorkArea);
		INIT_RECT(CenterRect);
		::SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);

		CenterRect.left = WorkArea.left + (RECT_WIDTH(WorkArea) - cx) / 2;
		CenterRect.right = CenterRect.left + cx;
		CenterRect.top = WorkArea.top + (RECT_HEIGHT(WorkArea) - cy) / 2;
		CenterRect.bottom = CenterRect.top + cy;

		this->MoveWindow(CenterRect, TRUE);
	}
}

// ���ö�ʱ��
void CUiFeatureWindow::SetTimer(int nId, UINT uElapse)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::SetTimer(m_hWnd, nId, uElapse, NULL);
}

// ȡ����ʱ��
void CUiFeatureWindow::KillTimer(int nId)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::KillTimer(m_hWnd, nId);
}

// ���öԻ���λ��
void CUiFeatureWindow::MoveWindow(RECT MoveRect, BOOL bRepaint)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::MoveWindow(m_hWnd, MoveRect.left, MoveRect.top, RECT_WIDTH(MoveRect), RECT_HEIGHT(MoveRect), bRepaint);
}

// ��ʾ/���ش��ڣ�����ΪSW_SHOW֮��
void CUiFeatureWindow::ShowWindow(int nShow)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::ShowWindow(m_hWnd, nShow);
}

// �����ػ�����
void CUiFeatureWindow::InvalidateRect(RECT *pInvRect)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::InvalidateRect(m_hWnd, pInvRect, FALSE);
}

// ���´��ڣ��������л���
void CUiFeatureWindow::UpdateWindow()
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::UpdateWindow(m_hWnd);
}

// �����ػ洰��
void CUiFeatureWindow::RedrawWindow(RECT *pDrawRect)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::RedrawWindow(m_hWnd, pDrawRect, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// ������Ϣ:Send��ʽ
LRESULT CUiFeatureWindow::SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	LRESULT lpRes = -1;
	if (IS_SAFE_HANDLE(m_hWnd))
		lpRes = ::SendMessage(m_hWnd, nMsgId, wParam, lParam);

	return lpRes;
}

// ������Ϣ:Post��ʽ
bool CUiFeatureWindow::PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	bool bRet = false;
	if (IS_SAFE_HANDLE(m_hWnd))
		bRet = (::PostMessage(m_hWnd, nMsgId, wParam, lParam) == TRUE);

	return bRet;
}

// ���ô����͸������
void CUiFeatureWindow::SetWindowTransparence(bool bIsTrans)
{
	DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if (bIsTrans)
	{
		// ͸��
		if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
		{
			dwExStyle |= WS_EX_LAYERED;
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
		}
	}
	else
	{
		// ��͸��
		if ((dwExStyle & WS_EX_LAYERED) == WS_EX_LAYERED)
		{
			dwExStyle &= (~WS_EX_LAYERED);
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
		}
	}
}

void CUiFeatureWindow::SetCreateWindowParam(LPARAM lParam)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::SetPropA(m_hWnd, "featurewindowparam", (HANDLE)lParam);
}

LPARAM CUiFeatureWindow::GetCreateWindowParam()
{
	if (IS_SAFE_HANDLE(m_hWnd))
		return (LPARAM)::GetPropA(m_hWnd, "featurewindowparam");

	return NULL;
}

ATOM CUiFeatureWindow::RegisterClass()
{
	WNDCLASSEX wcex;
	if (!::GetClassInfoExA(::GetModuleHandle(NULL), FEATURE_CLASS_NAME, &wcex)) 
	{
		wcex.cbSize			= sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wcex.lpfnWndProc	= Win32WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= ::GetModuleHandle(NULL);
		wcex.hIcon			= NULL;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= FEATURE_CLASS_NAME;
		wcex.hIconSm		= NULL;

		return ::RegisterClassEx(&wcex);
	}

	return TRUE;
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
		m_pWindowBase = m_pUiFeatureKernel->PG_InitFeatureSkin(m_hWnd, (char*)m_strSkinPath.c_str(), (char*)m_strSkinWndName.c_str());
		if (m_pWindowBase == NULL)
		{
			assert(false);
			return false;
		}

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
		OnCreateEnd();
		this->ShowWindow(SW_HIDE);
	}

	return IS_SAFE_HANDLE(m_hWnd);
}

// ��������
bool CUiFeatureWindow::CreateWin32Window(HWND hParent, RECT WndRect, char *pszWndText, int nShow, LPARAM lParam)
{
	m_hParentWnd = hParent;
	m_rctCreate = WndRect;
	m_nCreateShow = nShow;
	m_lParam = lParam;

	if (pszWndText != NULL)
		m_strWndText = pszWndText;

	GUID guid;
	if (::CoCreateGuid(&guid) != S_OK)
		return false;

	char szEventName[MAX_PATH];
	memset(szEventName, 0, sizeof(szEventName));
	sprintf_s(szEventName, sizeof(szEventName), "UI_FEATURE_%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	m_hCreateWaitEvent = ::CreateEventA(NULL, FALSE, FALSE, szEventName);
	if (m_hCreateWaitEvent == NULL)
		return false;

	// ����UI�߳�
	m_hUiThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WindowUiThread, this, 0, &m_dwUiThreadId);
	if (m_hUiThread == NULL || m_dwUiThreadId == 0)
	{
		SAFE_CLOSE_HANDLE(m_hCreateWaitEvent);
		return false;
	}

	// �ȴ�
	if (::WaitForSingleObject(m_hCreateWaitEvent, 30 * 1000) != WAIT_OBJECT_0)
	{
		SAFE_CLOSE_HANDLE(m_hCreateWaitEvent);
		return false;
	}

	SAFE_CLOSE_HANDLE(m_hCreateWaitEvent);
	return true;
}

LRESULT CUiFeatureWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (!::IsWindow(m_hWnd))
		return 0;

	switch (nMsgId)
	{
	case WM_KEYDOWN:
		OnKeyDown((int)wParam, (int)lParam);
		break;

	case WM_SYSCOMMAND:
		if (OnSysCommand(wParam, lParam))
			return TRUE;
		break;

		// WM_TIMER����ʱ��	
	case WM_TIMER:
		OnTimer((UINT)wParam);
		break;

	case WM_KILLFOCUS:
		OnKillFocus();
		break;

	case WM_SETFOCUS:
		OnSetFocus();
		break;

		// WM_DESTROY�����ٴ���
	case WM_DESTROY:
		OnDestroy();
		break;

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

	return ::DefWindowProc(m_hWnd, nMsgId, wParam, lParam);
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

// WM_TIMER����ʱ��	
void CUiFeatureWindow::OnTimer(UINT nTimerId)
{
}

// WM_CREATE���Ի����ʼ��	
void CUiFeatureWindow::OnCreate()
{
}

// �Ի����ʼ����ϵ���
void CUiFeatureWindow::OnCreateEnd()
{
}

// WM_DESTROY�����ٴ���
void CUiFeatureWindow::OnDestroy()
{
	m_lParam = NULL;
	m_pWindowBase = NULL;
	m_hWnd = m_hParentWnd = NULL;
}

void CUiFeatureWindow::OnKillFocus()
{
}

void CUiFeatureWindow::OnSetFocus()
{
}

bool CUiFeatureWindow::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
	return false;
}

void CUiFeatureWindow::OnKeyDown(int nVirtKey, int nFlag)
{
}

// ����MFC��PreTranslateMessage��������ص���true�����ټ��������ɷ���Ϣ
bool CUiFeatureWindow::PreTranslateMessage(MSG msg)
{
	return false;
}

// �����Ƿ�����
bool CUiFeatureWindow::IsWindowEnd()
{
	return (!IS_SAFE_HANDLE(m_hWnd));
}

// �����߳��Ƿ�����
bool CUiFeatureWindow::IsWindowThreadEnd()
{
	return (m_hUiThread == NULL);
}

void CUiFeatureWindow::_PostEndThread()
{
	if (m_hUiThread != NULL && m_dwUiThreadId != 0)
	{
		::PostThreadMessage(m_dwUiThreadId, WM_QUIT, 0, 0);
		SAFE_CLOSE_HANDLE(m_hUiThread);
		m_dwUiThreadId = 0;
	}
}

// �����ڲ���Ҫ�رմ��ڣ����ô˺���
void CUiFeatureWindow::CloseSelf()
{
	this->PostMessage(WM_CLOSE, NULL, NULL);
	if (m_hUiThread != NULL)
		::PostThreadMessage(m_dwUiThreadId, WM_QUIT, 0, 0);

	SAFE_CLOSE_HANDLE(m_hUiThread);
	m_dwUiThreadId = 0;
}

void CUiFeatureWindow::CloseWindow()
{
	this->PostMessage(WM_CLOSE, NULL, NULL);
	if (m_hUiThread != NULL)
	{
		BOOL bSuccess = ::PostThreadMessage(m_dwUiThreadId, WM_QUIT, 0, 0);
		if (m_hUiThread != NULL)
		{
			if (::WaitForSingleObject(m_hUiThread, 5 * 1000) == WAIT_TIMEOUT)
				::TerminateThread(m_hUiThread, -1);
		}
	}

	SAFE_CLOSE_HANDLE(m_hUiThread);
	m_dwUiThreadId = 0;
}

void CUiFeatureWindow::WaitWindowThreadEnd()
{
	if (m_hUiThread != NULL)
	{
		if (::WaitForSingleObject(m_hUiThread, 5 * 1000) == WAIT_TIMEOUT)
		{
			::TerminateThread(m_hUiThread, -1);
			SAFE_CLOSE_HANDLE(m_hUiThread);
			m_dwUiThreadId = 0;
		}
	}
}

// ȡ�ô�����ָ�����ƵĿؼ�
IControlBase* CUiFeatureWindow::GetCtrlObject(char* pstrCtrlName)
{
	return NULL;
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

	return CreateWin32Window(hParent, WndRect, "Welcome UiFeature", nShow, lParam);
}
