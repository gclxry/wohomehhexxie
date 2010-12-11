
#include "DirectUiDlg.h"


#pragma warning(disable:4312)
#pragma warning(disable:4244)


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

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

CDirectUiDlg::CDirectUiDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId)
{
	m_bCoerceEnd = false;
	m_bIsFreeze = false;
	m_PuppetWndType = PWT_WND;
	m_hParent = hParentWnd;
	ms_hInstance = hInstance;
	m_nIconId = nIconId;
	m_strWindowText = _T("飞信");
	m_bIsMoveMistDlg = false;
	m_WndRect.SetRectEmpty();

	AddBfStyle(BFS_HAVE_MIN_BTN | BFS_HAVE_MAX_BTN | BFS_FIRST_IN_WND | BFS_CAN_DRAW);
}

CDirectUiDlg::~CDirectUiDlg(void)
{
}

int CDirectUiDlg::DoModal()
{
	MSG msg;
	HACCEL hAccelTable;

	AddBfStyle(BFS_MODAL_DLG);
	memset(&msg, 0, sizeof(MSG));
	if (CreateDlg())
	{
		hAccelTable = LoadAccelerators(ms_hInstance, MAKEINTRESOURCE(m_nIconId));

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

void CDirectUiDlg::ShowWindow()
{
	DeleteBfStyle(BFS_MODAL_DLG);
	CreateDlg();
}

void CDirectUiDlg::RedrawWindow()
{
	if (IS_SAVE_HANDLE(m_hWnd))
		::RedrawWindow(m_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}

void CDirectUiDlg::EndThisDialog()
{
	if (IS_SAVE_HANDLE(m_hWnd))
	{
		::DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}

	m_bCoerceEnd = true;
	m_WndRect.SetRectEmpty();
}

bool CDirectUiDlg::CreateDlg()
{
	// 初始化全局字符串
	RegisterBfoClass();

	// 执行应用程序初始化:
	return InitInstance();
}

void CDirectUiDlg::MoveWindow(CRect WndRect)
{
	if (IS_SAVE_HANDLE(m_hWnd))
	{
		::MoveWindow(m_hWnd, WndRect.left, WndRect.top, WndRect.Width(), WndRect.Height(), TRUE);
		::UpdateWindow(m_hWnd);
	}
}

ATOM CDirectUiDlg::RegisterBfoClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= PuppetWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= ms_hInstance;
	wcex.hIcon			= LoadIcon(ms_hInstance, MAKEINTRESOURCE(m_nIconId));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(m_nIconId);
	wcex.lpszClassName	= m_strWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(m_nIconId));

	return RegisterClassEx(&wcex);
}

bool CDirectUiDlg::InitInstance()
{
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	if (m_bIsMoveMistDlg)
		dwStyle = WS_EX_TOOLWINDOW;

	m_hWnd = ::CreateWindowEx(0, m_strWindowClass, m_strWindowText, dwStyle,
		m_WndRect.left, m_WndRect.top, m_WndRect.Width(), m_WndRect.Height(), m_hParent, NULL, ms_hInstance, this);

	if (!m_hWnd)
		return false;

	OnCreate();

	::ShowWindow(m_hWnd, SW_SHOW);
	::UpdateWindow(m_hWnd);

	return true;
}

LRESULT CDirectUiDlg::OnNcActive(UINT message, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, message, wParam, lParam);
}

LRESULT CDirectUiDlg::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_NCCALCSIZE, wParam, lParam);
}

LRESULT CDirectUiDlg::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_ERASEBKGND, wParam, lParam);
}

LRESULT CDirectUiDlg::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_NCPAINT, wParam, lParam);
}

LRESULT CDirectUiDlg::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_MOUSELEAVE, wParam, lParam);
}

LRESULT CDirectUiDlg::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_MOUSEMOVE, wParam, lParam);
}

LRESULT CDirectUiDlg::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_LBUTTONDOWN, wParam, lParam);
}

LRESULT CDirectUiDlg::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_LBUTTONUP, wParam, lParam);
}

LRESULT CDirectUiDlg::OnNcLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_NCLBUTTONUP, wParam, lParam);
}

LRESULT CDirectUiDlg::OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_LBUTTONDBLCLK, wParam, lParam);
}

LRESULT CDirectUiDlg::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_GETMINMAXINFO, wParam, lParam);
}

LRESULT CDirectUiDlg::OnNcHitTest(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_NCHITTEST, wParam, lParam);
}

LRESULT CDirectUiDlg::OnSizeProc(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_SIZE, wParam, lParam);
}

LRESULT CDirectUiDlg::OnEnterSizeMove(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_ENTERSIZEMOVE, wParam, lParam);
}

LRESULT CDirectUiDlg::OnExitSizeMove(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_EXITSIZEMOVE, wParam, lParam);
}

LRESULT CDirectUiDlg::OnMove(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_MOVE, wParam, lParam);
}

LRESULT CDirectUiDlg::OnTimer(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_TIMER, wParam, lParam);
}

LRESULT CDirectUiDlg::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_ACTIVATEAPP, wParam, lParam);
}

LRESULT CDirectUiDlg::OnKillFocus(WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_hWnd, WM_KILLFOCUS, wParam, lParam);
}

LRESULT CDirectUiDlg::WndProc(UINT message, WPARAM wParam, LPARAM lParam)
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

	case WM_NCLBUTTONUP:
		return OnNcLButtonUp(wParam, lParam);

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
		nRet = ::DefWindowProc(m_hWnd, message, wParam, lParam);
	}

	return nRet;
}
