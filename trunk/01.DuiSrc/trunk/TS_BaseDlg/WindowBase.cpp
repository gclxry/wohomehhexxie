
#include "WindowBase.h"

HINSTANCE CWindowBase::ms_hInstance = NULL;

CWindowBase::CWindowBase(void)
{
	m_hParent = NULL;
	m_hWnd = NULL;
	m_strWindowClass = _T("BfBaseDlg");
	m_PuppetWndType = PWT_WND;
	m_dwWndStyle = 0;
	m_strWindowText = _T("");
	m_nTimerId = 5000;
}

CWindowBase::~CWindowBase(void)
{

}

void CWindowBase::SetSafeHandle(HWND hWnd)
{
	m_hWnd = hWnd;
}

HWND CWindowBase::GetSafeHandle()
{
	return m_hWnd;
}

// 得到窗口屏幕坐标
CRect CWindowBase::GetWindowRect()
{
	CRect RetRrect(0, 0, 0, 0);

	if (IS_SAVE_HANDLE(m_hWnd))
		::GetWindowRect(m_hWnd, &RetRrect);

	return RetRrect;
}

// 得到客户端坐标
CRect CWindowBase::GetClientRect()
{
	CRect RetRrect(0, 0, 0, 0);

	if (IS_SAVE_HANDLE(m_hWnd))
	{
		::GetWindowRect(m_hWnd, &RetRrect);
		int nW = RetRrect.Width();
		int nH = RetRrect.Height();

		RetRrect.SetRectEmpty();
		RetRrect.right = nW;
		RetRrect.bottom = nH;
	}

	return RetRrect;
}

void CWindowBase::CenterWindow(int cx, int cy)
{
	if (cx == 0 || cy == 0)
	{
		CRect WndRect = GetClientRect();
		cx = WndRect.Width();
		cy = WndRect.Height();
	}

	if (IS_SAVE_HANDLE(m_hWnd) && cx > 0 && cy > 0)
	{
		// 设置默认大小
		CRect WorkArea(0, 0, 0, 0), CenterRect(0, 0, 0, 0);
		::SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);

		CenterRect.left = (WorkArea.Width() - cx) / 2;
		CenterRect.right = CenterRect.left + cx;
		CenterRect.top = (WorkArea.Height() - cy) / 2;
		CenterRect.bottom = CenterRect.top + cy;

		::MoveWindow(m_hWnd, CenterRect.left, CenterRect.top, CenterRect.Width(), CenterRect.Height(), TRUE);
	}
}

void CWindowBase::SetWindowText(CString strText)
{
	m_strWindowText = strText;
}

// 设置定时器
int CWindowBase::SetTimer(UINT uElapse)
{
	int nId = -1;

	if (IS_SAVE_HANDLE(m_hWnd))
	{
		nId = m_nTimerId++;
		::SetTimer(m_hWnd, nId, uElapse, NULL);
	}

	return nId;
}

// 取消定时器
void CWindowBase::KillTimer(int nId)
{
	if (IS_SAVE_HANDLE(m_hWnd))
		::KillTimer(m_hWnd, nId);
}
