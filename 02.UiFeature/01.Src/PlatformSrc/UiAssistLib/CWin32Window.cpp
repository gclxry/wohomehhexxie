
#include "stdafx.h"
#include <assert.h>
#include <shobjidl.h>
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\CWin32Window.h"

// ��ǰ��ʾ�Ĵ���map
typedef map<HWND, CWin32Window*> W32_Wnd_MAP;
// ��Ϣ�������໯
W32_Wnd_MAP g_Win32WndMap;
LRESULT CALLBACK Win32WndProc(HWND hWnd, UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	switch (nMsgId)
	{
		// ����������Ϣ
	case WM_NCCREATE:
		{
			CWin32Window *pDlg = (CWin32Window *)(((LPCREATESTRUCT)lParam)->lpCreateParams);
			if (pDlg != NULL)
			{
				g_Win32WndMap.insert(pair<HWND, CWin32Window*>(hWnd, pDlg));
				pDlg->SetSafeHandle(hWnd);
				return pDlg->WndProc(nMsgId, wParam, lParam);
			}
		}
		break;

		// ������Ϣ
	default:
		{
			W32_Wnd_MAP::iterator pDuiWnd = g_Win32WndMap.find(hWnd);
			if (pDuiWnd != g_Win32WndMap.end())
			{
				CWin32Window *pDlg = pDuiWnd->second;
				if (nMsgId == WM_NCDESTROY)
					g_Win32WndMap.erase(pDuiWnd);

				if (pDlg != NULL)
				{
					LRESULT lRst = pDlg->WndProc(nMsgId, wParam, lParam);
					if (nMsgId == WM_NCDESTROY)
						pDlg->_PostEndThread();
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

	CWin32Window *pWindow = (CWin32Window*)lpVoid;
	pWindow->_BeginWindowThread();
	return 0;
}

void CWin32Window::_BeginWindowThread()
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

CWin32Window::CWin32Window()
{
	::CoInitialize(NULL);

	m_hWnd = NULL;
	m_strWndText = "Welcome UiFeature";
	m_hParentWnd = NULL;
	m_lParam = NULL;

	INIT_RECT(m_rctCreate);
	m_nCreateShow = SW_SHOW;
	m_hCreateWaitEvent = NULL;
	m_hUiThread = NULL;
	m_dwUiThreadId = 0;
	m_bIsCreateWithThread = false;
}

CWin32Window::~CWin32Window()
{
	CloseWindow();
	SAFE_CLOSE_HANDLE(m_hUiThread);
	m_dwUiThreadId = 0;
}

// ��������
bool CWin32Window::CreateWindowWithoutThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, LPARAM lParam)
{
	m_bIsCreateWithThread = false;
	m_hParentWnd = hParent;
	m_rctCreate = WndRect;
	m_nCreateShow = nShow;
	m_lParam = lParam;

	if (pszWndText != NULL)
		m_strWndText = pszWndText;

	RegisterClass();
	return InitInstance();
}

// ��������
bool CWin32Window::CreateWindowWithNewThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, LPARAM lParam)
{
	m_bIsCreateWithThread = true;
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

LRESULT CWin32Window::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
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

	case WM_SIZE:
		OnSize((UINT)wParam, LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_NCCALCSIZE:
		return 0;

	case WM_ERASEBKGND:
	case WM_NCPAINT:
	case WM_NCACTIVATE:
	case 0x00AE:	// WM_NCUAHDRAWCAPTION
	case 0x00AF:	// WM_NCUAHDRAWFRAME
		return WM_PAINT;

	default:
		break;
	}

	return ::DefWindowProc(m_hWnd, nMsgId, wParam, lParam);
}

void CWin32Window::OnSize(UINT nType, int cx, int cy)
{
}

// ȡ�ô��ھ��
HWND CWin32Window::GetSafeHandle()
{
	return m_hWnd;
}

// �õ�������Ļ����
RECT CWin32Window::GetWindowRect()
{
	RECT RetRect;
	INIT_RECT(RetRect);

	if (IS_SAFE_HANDLE(m_hWnd))
		::GetWindowRect(m_hWnd, &RetRect);

	return RetRect;
}

// �õ��ͻ�������
RECT CWin32Window::GetClientRect()
{
	RECT RetRect;
	INIT_RECT(RetRect);

	if (IS_SAFE_HANDLE(m_hWnd))
	{
		::GetWindowRect(m_hWnd, &RetRect);
		int nW = RECT_WIDTH(RetRect);
		int nH = RECT_HEIGHT(RetRect);

		INIT_RECT(RetRect);
		RetRect.right = nW;
		RetRect.bottom = nH;
	}

	return RetRect;
}

// ͬWindowsAPI��IsWindow
bool CWin32Window::IsWindow()
{
	return (::IsWindow(m_hWnd) == TRUE);
}

// �������Ƶ���Ļ����
void CWin32Window::CenterWindow()
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

// ȡ�ô��ڱ�������
const char* CWin32Window::GetWindowText()
{
	return m_strWndText.c_str();
}

// ���ö�ʱ��
void CWin32Window::SetTimer(int nId, UINT uElapse)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::SetTimer(m_hWnd, nId, uElapse, NULL);
}

// ȡ����ʱ��
void CWin32Window::KillTimer(int nId)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::KillTimer(m_hWnd, nId);
}

// ���öԻ���λ��
void CWin32Window::MoveWindow(RECT MoveRect, BOOL bRepaint)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::MoveWindow(m_hWnd, MoveRect.left, MoveRect.top, RECT_WIDTH(MoveRect), RECT_HEIGHT(MoveRect), bRepaint);
}

// ��ʾ/���ش��ڣ�����ΪSW_SHOW֮��
void CWin32Window::ShowWindow(int nShow)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::ShowWindow(m_hWnd, nShow);
}

// �����ػ�����
void CWin32Window::InvalidateRect(RECT *pInvRect)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::InvalidateRect(m_hWnd, pInvRect, FALSE);
}

// ���´��ڣ��������л���
void CWin32Window::UpdateWindow()
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::UpdateWindow(m_hWnd);
}

// �����ػ洰��
void CWin32Window::RedrawWindow(RECT *pDrawRect)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::RedrawWindow(m_hWnd, pDrawRect, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// ������Ϣ:Send��ʽ
LRESULT CWin32Window::SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	LRESULT lpRes = -1;
	if (IS_SAFE_HANDLE(m_hWnd))
		lpRes = ::SendMessage(m_hWnd, nMsgId, wParam, lParam);

	return lpRes;
}

// ������Ϣ:Post��ʽ
bool CWin32Window::PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	bool bRet = false;
	if (IS_SAFE_HANDLE(m_hWnd))
		bRet = (::PostMessage(m_hWnd, nMsgId, wParam, lParam) == TRUE);

	return bRet;
}

// ���ô����͸������
void CWin32Window::SetWindowTransparence(bool bIsTrans)
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

void CWin32Window::SetCreateWindowParam(LPARAM lParam)
{
	if (IS_SAFE_HANDLE(m_hWnd))
		::SetPropA(m_hWnd, "featurewindowparam", (HANDLE)lParam);
}

LPARAM CWin32Window::GetCreateWindowParam()
{
	if (IS_SAFE_HANDLE(m_hWnd))
		return (LPARAM)::GetPropA(m_hWnd, "featurewindowparam");

	return NULL;
}

// �����Ƿ�����
bool CWin32Window::IsWindowEnd()
{
	return (!IS_SAFE_HANDLE(m_hWnd) || !::IsWindow(m_hWnd));
}

// �����߳��Ƿ�����
bool CWin32Window::IsWindowThreadEnd()
{
	return (m_hUiThread == NULL);
}

ATOM CWin32Window::RegisterClass()
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

bool CWin32Window::InitInstance()
{
	m_hWnd = ::CreateWindowExA(0, FEATURE_CLASS_NAME, m_strWndText.c_str(), WS_OVERLAPPED | WS_THICKFRAME,
		m_rctCreate.left, m_rctCreate.top, RECT_WIDTH(m_rctCreate), RECT_HEIGHT(m_rctCreate), m_hParentWnd, NULL, ::GetModuleHandle(NULL), this);

	// ���ô����Ի������
	SetCreateWindowParam(m_lParam);

	// �Ի����ʼ��
	if (IS_SAFE_HANDLE(m_hWnd))
	{
		this->CenterWindow();
		OnCreate();
		this->ShowWindow(m_nCreateShow);
	}

	return IS_SAFE_HANDLE(m_hWnd);
}

// WM_TIMER����ʱ��	
void CWin32Window::OnTimer(UINT nTimerId)
{
}

// WM_CREATE���Ի����ʼ��	
void CWin32Window::OnCreate()
{
}

// WM_DESTROY�����ٴ���
void CWin32Window::OnDestroy()
{
	m_lParam = NULL;
	m_hWnd = m_hParentWnd = NULL;
}

void CWin32Window::OnKillFocus()
{
}

void CWin32Window::OnSetFocus()
{
}

bool CWin32Window::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
	return false;
}

void CWin32Window::OnKeyDown(int nVirtKey, int nFlag)
{
}

// ����MFC��PreTranslateMessage��������ص���true�����ټ��������ɷ���Ϣ
bool CWin32Window::PreTranslateMessage(MSG msg)
{
	return false;
}

// ���ô��ھ��
void CWin32Window::SetSafeHandle(HWND hWnd)
{
	if (!IS_SAFE_HANDLE(m_hWnd))
		m_hWnd = hWnd;
}

// ���ô��ڱ�������
void CWin32Window::SetWindowText(char* pstrWndText)
{
	if (pstrWndText == NULL)
		return;

	if (IS_SAFE_HANDLE(m_hWnd))
	{
		m_strWndText = pstrWndText;
		::SetWindowTextA(m_hWnd, pstrWndText);
	}
}

void CWin32Window::CloseWindow(bool bIsWaitEnd)
{
	this->PostMessage(WM_CLOSE, NULL, NULL);
	if (m_bIsCreateWithThread && bIsWaitEnd)
		WaitWindowThreadEnd();
}

void CWin32Window::WaitWindowThreadEnd()
{
	if (m_hUiThread != NULL)
	{
		if (::WaitForSingleObject(m_hUiThread, 5 * 1000) == WAIT_TIMEOUT)
			::TerminateThread(m_hUiThread, -1);
	}
	SAFE_CLOSE_HANDLE(m_hUiThread);
	m_dwUiThreadId = 0;
}

void CWin32Window::_PostEndThread()
{
	if (m_bIsCreateWithThread && m_hUiThread != NULL && m_dwUiThreadId != 0)
		::PostThreadMessage(m_dwUiThreadId, WM_QUIT, 0, 0);
}

// �������������������ڰ�ť
void CWin32Window::HideInTaskbar()
{
	HRESULT hr = NULL;
	ITaskbarList* pTaskbarList = NULL;

	hr = ::CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void**)&pTaskbarList);
	if (hr == S_OK && pTaskbarList != NULL)
	{
		pTaskbarList->HrInit();

		::SetWindowTextA(this->GetSafeHandle(), "");

		DWORD dwLong = ::GetWindowLong(this->GetSafeHandle(), GWL_STYLE);
		dwLong &= (~WS_CAPTION);
		::SetWindowLong(this->GetSafeHandle(), GWL_STYLE, dwLong);

		dwLong = ::GetWindowLong(this->GetSafeHandle(), GWL_EXSTYLE);
		dwLong &= (~WS_EX_APPWINDOW);
		dwLong |= WS_EX_TOOLWINDOW;
		::SetWindowLong(this->GetSafeHandle(), GWL_EXSTYLE, dwLong);

		pTaskbarList->DeleteTab(this->GetSafeHandle());
		pTaskbarList->Release();
	}
}
