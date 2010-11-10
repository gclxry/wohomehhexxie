
#include "Win32BaseDlg.h"


#pragma warning(disable:4312)
#pragma warning(disable:4244)

HINSTANCE CWindowBase::m_hInstance = NULL;
CString CWin32BaseDlg::m_strWindowClass = _T("BfBaseDlg");

LRESULT CALLBACK PuppetWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CWindowBase *pDlg = NULL;
	switch (message)
	{
	case WM_NCCREATE :
		pDlg = (CWindowBase *)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		if (pDlg != NULL)
		{
			pDlg->SetSafeHandle(hWnd);
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pDlg);
		}
		break;

	case WM_NCDESTROY:
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, NULL);
		break;

	case WM_DESTROY:
		pDlg = (CWindowBase *)::GetWindowLongPtr(hWnd, GWL_USERDATA);
		if (pDlg != NULL)
			pDlg->WndProc(message, wParam, lParam);
		break;

	default :
		pDlg = (CWindowBase *)::GetWindowLongPtr(hWnd, GWL_USERDATA);
		if (pDlg != NULL)
			return pDlg->WndProc(message, wParam, lParam);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

CWin32BaseDlg::CWin32BaseDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId)
{
	m_bCoerceEnd = false;
	m_bIsFreeze = false;
	m_PuppetWndType = PWT_WND;
	m_hParent = hParentWnd;
	m_hInstance = hInstance;
	m_nIconId = nIconId;
	m_hWnd = NULL;
	m_dwBfStyle = 0;
	m_strWindowText = _T("飞信");

	AddBfStyle(BFS_HAVE_MIN_BTN | BFS_HAVE_MAX_BTN | BFS_FIRST_IN_WND | BFS_CAN_DRAW);
}

CWin32BaseDlg::~CWin32BaseDlg(void)
{
}

int CWin32BaseDlg::DoModal()
{
	MSG msg;
	HACCEL hAccelTable;

	AddBfStyle(BFS_MODAL_DLG);
	memset(&msg, 0, sizeof(MSG));
	if (CreateDlg())
	{
		hAccelTable = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(m_nIconId));

		m_bCoerceEnd = false;
		while (GetMessage(&msg, NULL, 0, 0) && !m_bCoerceEnd)
		{
			// 主消息循环
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	return (int)msg.wParam;
}

void CWin32BaseDlg::OpenDialog()
{
	DeleteBfStyle(BFS_MODAL_DLG);
	CreateDlg();
}

void CWin32BaseDlg::EndThisDialog()
{
	if (IS_SAVE_HANDLE(m_hWnd))
	{
		::DestroyWindow(m_hWnd);
	}

	m_bCoerceEnd = true;
}

bool CWin32BaseDlg::CreateDlg()
{
	// 初始化全局字符串
	RegisterBfoClass();

	// 执行应用程序初始化:
	return InitInstance();
}

ATOM CWin32BaseDlg::RegisterBfoClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= PuppetWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_hInstance;
	wcex.hIcon			= LoadIcon(m_hInstance, MAKEINTRESOURCE(m_nIconId));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(m_nIconId);
	wcex.lpszClassName	= m_strWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(m_nIconId));

	return RegisterClassEx(&wcex);
}

bool CWin32BaseDlg::InitInstance()
{
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	m_hWnd = ::CreateWindowEx(0, m_strWindowClass, m_strWindowText, dwStyle,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, m_hParent, NULL, m_hInstance, this);

	if (!m_hWnd)
		return false;

	OnCreate();

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}

LRESULT CWin32BaseDlg::OnNcActive(UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, message, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_NCCALCSIZE, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_ERASEBKGND, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_NCPAINT, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_MOUSELEAVE, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_MOUSEMOVE, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_LBUTTONDOWN, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_LBUTTONUP, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_LBUTTONDBLCLK, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_GETMINMAXINFO, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnNcHitTest(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_NCHITTEST, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnSizeProc(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_SIZE, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnEnterSizeMove(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_ENTERSIZEMOVE, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnExitSizeMove(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_EXITSIZEMOVE, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnMove(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_MOVE, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnTimer(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_TIMER, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_ACTIVATEAPP, wParam, lParam);
}

LRESULT CWin32BaseDlg::OnKillFocus(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hWnd, WM_KILLFOCUS, wParam, lParam);
}

LRESULT CWin32BaseDlg::WndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT nRet = 0;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_ENTERSIZEMOVE:
		return OnEnterSizeMove(wParam, lParam);

	case WM_EXITSIZEMOVE:
		return OnExitSizeMove(wParam, lParam);

	case WM_MOVE:
		return OnMove(wParam, lParam);

	case 0x00AE:	// WM_NCUAHDRAWCAPTION
	case 0x00AF:	// WM_NCUAHDRAWFRAME
	case WM_NCACTIVATE:
		return OnNcActive(message, wParam, lParam);

	case WM_NCCALCSIZE:
		return OnNcCalcSize(wParam, lParam);

	case WM_ERASEBKGND:
		return OnEraseBkgnd(wParam, lParam);

	case WM_NCPAINT:
		return OnNcPaint(wParam, lParam);

	case WM_PAINT:
		hdc = BeginPaint(m_hWnd, &ps);
		OnPaint(hdc);
		EndPaint(m_hWnd, &ps);
		break;

	case WM_DESTROY:
		OnDestroy();
		break;

	case WM_MOUSELEAVE:
		return OnMouseLeave(wParam, lParam);

	case WM_MOUSEMOVE:
		return OnMouseMove(wParam, lParam);

	case WM_LBUTTONDOWN:
		return OnLButtonDown(wParam, lParam);

	case WM_LBUTTONUP:
		return OnLButtonUp(wParam, lParam);

	case WM_LBUTTONDBLCLK:
		return OnLButtonDblClk(wParam, lParam);

	case WM_GETMINMAXINFO:
		return OnGetMinMaxInfo(wParam, lParam);

	case WM_NCHITTEST:
		return OnNcHitTest(wParam, lParam);

	case WM_SIZE:
		return OnSizeProc(wParam, lParam);

	case WM_TIMER:
		return OnTimer(wParam, lParam);

	case WM_ACTIVATEAPP:
		return OnActivateApp(wParam, lParam);

	case WM_KILLFOCUS:
		return OnKillFocus(wParam, lParam);

	default:
		nRet = DefWindowProc(m_hWnd, message, wParam, lParam);
	}

	return nRet;
}
