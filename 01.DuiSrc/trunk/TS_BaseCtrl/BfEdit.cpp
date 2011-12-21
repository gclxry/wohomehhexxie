
#include "BfEdit.h"


CBfEdit::CBfEdit(HINSTANCE hInstance):
CBfWindowsWnd(hInstance)
{
	m_bIsDrawFrame = true;
}

CBfEdit::~CBfEdit(void)
{
}

LPCTSTR CBfEdit::GetSuperClassName() const
{
	return WC_EDIT;
}

LPCTSTR CBfEdit::GetWindowClassName() const
{
	return _T("BfEdit");
}

void CBfEdit::OnPaint()
{
	if (m_bIsDrawFrame)
	{
		// 绘制背景图
		if (m_BkgndImage.IsReady())
			CGdiPlusDraw::DrawCenterImage(m_pDoGrap, m_BkgndImage.GetImage(), m_WndRect);
		else
			CGdiPlusDraw::DrawColor(m_pDoGrap, Color(255, 255, 255), m_WndRect);
	}

	// 绘制文字信息
	if (!m_WndTextInfo.strText.IsEmpty())
	{
		if (m_WndTextInfo.IsEmpty())
			SetDefaultFont();

		FontFamily DefaultFamily(m_WndTextInfo.strFontName);
		Font DefaultFont(&DefaultFamily, (REAL)m_WndTextInfo.nFontHeight, m_WndTextInfo.FStyle, UnitPixel);
		SolidBrush DefaultBrush(m_WndTextInfo.TextColor);

		CGdiPlusDraw::DrawWndText(m_pDoGrap, m_WndTextInfo);
	}

	if (m_bIsDrawFrame)
		CGdiPlusDraw::DrawRectLine(m_pDoGrap, Color(192, 192, 192), m_WndRect);
}

void CBfEdit::MoveWindow(CRect ToRect, HDWP hWinPoslnfo)
{
	CDirectUiWindow::MoveWindow(ToRect, hWinPoslnfo);

	int nCut = 1;
	m_WndTextInfo.TextRectF.X += nCut;
	m_WndTextInfo.TextRectF.Y += nCut;
	m_WndTextInfo.TextRectF.Width -= (nCut * 2);
	m_WndTextInfo.TextRectF.Height -= (nCut * 2);
}

void CBfEdit::OnMouseHover(CPoint point)
{
	DWM_INFO MsgInfo;
	MsgInfo.wParam = m_nWndId;
	MsgInfo.lParam = NULL;
	m_pMsgCtrl->OnDirectUiWindowMsgProc(DWM_MOUSEHOVER, MsgInfo);
}

void CBfEdit::OnLoseFocus()
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

void CBfEdit::OnSetFocus()
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

LRESULT CBfEdit::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KILLFOCUS)
		OnLoseFocus();

	return ::CallWindowProc(m_OldWndProc, m_hWindowsWnd, uMsg, wParam, lParam);
}
