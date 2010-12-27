
#include "BfIe.h"


CBfIe::CBfIe(HINSTANCE hInstance) : CBfWindowsWnd(hInstance)
{
}

CBfIe::~CBfIe(void)
{
}

LPCTSTR CBfIe::GetSuperClassName() const
{
	return WC_EDIT;
}

LPCTSTR CBfIe::GetWindowClassName() const
{
	return _T("BfIe");
}

void CBfIe::OnPaint()
{
	HDC hPDc = CDirectUiWindow::GetParentPaintDc();
	if (IS_SAVE_HANDLE(hPDc))
	{
		// 从当前裁减区中去除客户区的某矩形部分
		::ExcludeClipRect(hPDc, m_WndRect.left, m_WndRect.top, m_WndRect.right, m_WndRect.bottom);
	}
}

void CBfIe::MoveWindow(CRect ToRect, HDWP hWinPoslnfo)
{
	CDirectUiWindow::MoveWindow(ToRect, hWinPoslnfo);

	m_WebId.MoveWindow(ToRect);
}

void CBfIe::OnMouseHover(CPoint point)
{
	DWM_INFO MsgInfo;
	MsgInfo.wParam = m_nWndId;
	MsgInfo.lParam = NULL;
	m_pMsgCtrl->OnDirectUiWindowMsgProc(DWM_MOUSEHOVER, MsgInfo);
}

void CBfIe::OnLoseFocus()
{
	if (IS_SAVE_HANDLE(m_hWindowsWnd))
	{
		int nLen = ::GetWindowTextLength(m_hWindowsWnd) + 1;
		LPTSTR pData = static_cast<LPTSTR>(_alloca(nLen * sizeof(TCHAR)));

		if (pData != NULL)
		{
			::GetWindowText(m_hWindowsWnd, pData, nLen);
			SetWindowText(CString(pData));
		}

		::DestroyWindow(m_hWindowsWnd);
		m_hWindowsWnd = NULL;

		this->RedrawWindow();
	}
}

void CBfIe::OnSetFocus()
{
	CreateWindowsWnd(m_hParent, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL);
	if (IS_SAVE_HANDLE(m_hWindowsWnd))
	{
		int nCut = 1;
		::MoveWindow(m_hWindowsWnd, m_WndRect.left + nCut, m_WndRect.top + nCut * 2, m_WndRect.Width() - nCut * 2, m_WndRect.Height() - nCut * 3, TRUE);

		LOGFONT lf = { 0 };
		::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFont = ::CreateFontIndirect(&lf);
		::SendMessage(m_hWindowsWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

		::SetWindowText(m_hWindowsWnd, m_WndTextInfo.strText.LockBuffer());
		m_WndTextInfo.strText.UnlockBuffer();

		::SendMessage(m_hWindowsWnd, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(2, 2));
		::SendMessage(m_hWindowsWnd, EM_SETSEL, 0, -1);
		::SetFocus(m_hWindowsWnd);
		::ShowWindow(m_hWindowsWnd, SW_SHOWNOACTIVATE);
	}
}

LRESULT CBfIe::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KILLFOCUS)
		OnLoseFocus();

	return ::CallWindowProc(m_OldWndProc, m_hWindowsWnd, uMsg, wParam, lParam);
}

bool CBfIe::CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
								CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	bool bRet = CDirectUiWindow::CreateWnd(pParentDlg, pUiManager, pMsgCtrl, WndRect, nWndId, WndType, nImageId, strImagePath, nImageType);
	if (bRet)
	{
		m_WebId.LaunchIE(pParentDlg->GetSafeHandle(), CRect(0, 0, 100, 100), _T("www.baidu.com"));
	}

	return bRet;
}