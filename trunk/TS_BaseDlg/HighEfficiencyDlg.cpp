
#include "HighEfficiencyDlg.h"

#define __base_super					CDirectUiDlg

bool CHighEfficiencyDlg::m_bIsNeedLButtonUpMsg = false;

CHighEfficiencyDlg::CHighEfficiencyDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId)
: CDirectUiDlg(hInstance, hParentWnd, nIconId)
{
	m_pUiManager = NULL;
	m_bIsMistDlg = false;
}

CHighEfficiencyDlg::~CHighEfficiencyDlg(void)
{
}

LRESULT CHighEfficiencyDlg::OnEnterSizeMove(WPARAM wParam, LPARAM lParam)
{
	::SetFocus(m_hWnd);
	return ::DefWindowProc(m_hWnd, WM_ENTERSIZEMOVE, wParam, lParam);
}

LRESULT CHighEfficiencyDlg::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	// �Ƕ���״̬�²���Ӧ�����Ϣ
	if (!m_bIsFreeze && IsReady())
	{
		AddBfStyle(BFS_FIRST_IN_WND);
		CPoint point(-1, -1);
		m_pUiManager->OnMouseMove(0, point);
	}
	return 1;
}

LRESULT CHighEfficiencyDlg::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	// �Ƕ���״̬�²���Ӧ�����Ϣ
	if (!m_bIsFreeze && IsReady())
	{
		// ����ȡ������뿪���ڵ���Ϣ
		if (IsSetBfStyle(BFS_FIRST_IN_WND))
		{
			DeleteBfStyle(BFS_FIRST_IN_WND);
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = m_hWnd;
			tme.dwFlags = TME_LEAVE;
			::TrackMouseEvent(&tme);
		}

		int nFlags = (int)wParam;
		CPoint point(LOWORD(lParam), HIWORD(lParam));
		m_pUiManager->OnMouseMove(nFlags, point);
	}

	return 1;
}

LRESULT CHighEfficiencyDlg::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	::SetFocus(m_hWnd);

	SetFreezeDlg(false);

	//��ֹ��ʾ�ƶ����δ����
	::SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);

	if (IsReady())
	{
		int nFlags = (int)wParam;
		CPoint point(LOWORD(lParam), HIWORD(lParam));
		m_pUiManager->OnLButtonDown(nFlags, point);

		if (CDirectUiWindow::IsWndLButtonDown())
		{
			SetCapture(m_hWnd);

			if (CHighEfficiencyDlg::m_bIsNeedLButtonUpMsg)
			{
				CHighEfficiencyDlg::m_bIsNeedLButtonUpMsg = false;
				OnLButtonUp(wParam, lParam);
			}
		}
		else
		{
			if (!IsSetBfStyle(BFS_MAX_WND))
			{
				if (m_bIsMistDlg)
					MistDown();

				::PostMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, lParam);
			}
		}
	}

	return 1;
}

LRESULT CHighEfficiencyDlg::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	ReleaseCapture();
	
	if (IsReady())
	{
		int nFlags = (int)wParam;
		CPoint point(LOWORD(lParam), HIWORD(lParam));
		m_pUiManager->OnLButtonUp(nFlags, point);
	}

	if (m_bIsMistDlg)
		MistUp();

	return 1;
}

LRESULT CHighEfficiencyDlg::OnExitSizeMove(WPARAM wParam, LPARAM lParam)
{
	if (m_bIsMistDlg)
		MistUp();

	return __base_super::OnExitSizeMove(wParam, lParam);
}

LRESULT CHighEfficiencyDlg::OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	if (IsReady())
	{
		int nFlags = (int)wParam;
		CPoint point(LOWORD(lParam), HIWORD(lParam));
		m_pUiManager->OnLButtonDblClk(nFlags, point);
	}

	if (m_bIsMistDlg)
		MistUp();

	return 1;
}

LRESULT CHighEfficiencyDlg::OnNcHitTest(WPARAM wParam, LPARAM lParam)
{
	if (IsSetBfStyle(BFS_CAN_DRAW) && IsReady())
	{
		CPoint point(LOWORD(lParam), HIWORD(lParam));

		int nCheckPos = 5;
		int nRDPos = nCheckPos * 2;
		CRect WndRect(0, 0, 0, 0);
		::GetWindowRect(m_hWnd, &WndRect);

		if(point.x >= WndRect.right - nRDPos && point.y >= WndRect.bottom - nRDPos)
		{
			// ���½�
			return HTBOTTOMRIGHT;
		}
		else if(point.x >= WndRect.right - nRDPos && point.y <= WndRect.top + nRDPos)
		{
			// ���Ͻ�
			return HTTOPRIGHT;
		}
		else if(point.x <= WndRect.left + nRDPos && point.y <= WndRect.top + nRDPos)
		{
			// ���Ͻ�
			return HTTOPLEFT;
		}
		else if(point.x <= WndRect.left + nRDPos && point.y >= WndRect.bottom - nRDPos)
		{
			// ���½�
			return HTBOTTOMLEFT;
		}
		else if(point.x >= WndRect.right - nCheckPos)
		{
			// �ұ���
			return HTRIGHT;
		}
		else if(point.x <= WndRect.left + nCheckPos)
		{
			// �����
			return HTLEFT;
		}
		else if(point.y <= WndRect.top + nCheckPos)
		{
			// �ϱ���
			return HTTOP;
		}
		else if(point.y >= WndRect.bottom - nCheckPos)
		{
			// �±���
			return HTBOTTOM;
		}

		return __base_super::OnNcHitTest(wParam, lParam);
	}
	else
	{
		return ::DefWindowProc(m_hWnd, WM_NCHITTEST, wParam, lParam);
	}
}

void CHighEfficiencyDlg::OnDestroy()
{
	if (IsReady())
		m_pUiManager->OnDestroy();
}

LRESULT CHighEfficiencyDlg::OnNcActive(UINT message, WPARAM wParam, LPARAM lParam)
{
	return WM_PAINT;
}

LRESULT CHighEfficiencyDlg::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CHighEfficiencyDlg::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

void CHighEfficiencyDlg::OnCreate()
{
	if (IsReady())
	{
		// ��ʼ������
		m_pUiManager->InitManager(this);
	}
}

LRESULT CHighEfficiencyDlg::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CHighEfficiencyDlg::OnSizeProc(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	if (IsReady())
	{
		int nCtns = m_pUiManager->GetTrueWndCtns();

		HDWP hWinPoslnfo = NULL;
		hWinPoslnfo = BeginDeferWindowPos(nCtns);

		lRes = OnSize(hWinPoslnfo, wParam, lParam);

		EndDeferWindowPos(hWinPoslnfo);
	}

	return lRes;
}

LRESULT CHighEfficiencyDlg::OnTimer(WPARAM wParam, LPARAM lParam)
{
	if (IsReady())
	{
		int nTimerId = (int)wParam;
		m_pUiManager->OnTimer(nTimerId);
	}
	return 0;
}

LRESULT CHighEfficiencyDlg::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
	if (IsReady())
	{
		//m_pUiManager->OnActivateApp(wParam, lParam);
	}

	return CDirectUiDlg::OnActivateApp(wParam, lParam);
}

LRESULT CHighEfficiencyDlg::OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam)
{
	if (IsReady())
	{
		int nType = (int)wParam;
		int cx = LOWORD(lParam); 
		int cy = HIWORD(lParam);

		SetWndRgn(cx, cy);
	}

	return 1;
}

void CHighEfficiencyDlg::SetWndRgn(int cx, int cy)
{
	if (IS_SAVE_HANDLE(m_hWnd))
	{
		int nCut = 2;
		CRect WndRect(0, 0, cx, cy);
		CPoint aPointList[8];

		aPointList[0].x = WndRect.left;
		aPointList[0].y = WndRect.top + nCut;

		aPointList[1].x = WndRect.left + nCut;
		aPointList[1].y = WndRect.top;

		aPointList[2].x = WndRect.right - nCut;
		aPointList[2].y = WndRect.top;

		aPointList[3].x = WndRect.right;
		aPointList[3].y = WndRect.top + nCut;

		aPointList[4].x = WndRect.right;
		aPointList[4].y = WndRect.bottom - nCut - 1;

		aPointList[5].x = WndRect.right - nCut - 1;
		aPointList[5].y = WndRect.bottom;

		aPointList[6].x = WndRect.left + nCut + 1;
		aPointList[6].y = WndRect.bottom;

		aPointList[7].x = WndRect.left;
		aPointList[7].y = WndRect.bottom - nCut - 1;

		HRGN hRgn = ::CreatePolygonRgn(aPointList, 8, ALTERNATE);
		::SetWindowRgn(m_hWnd, hRgn, TRUE);
		::DeleteObject(hRgn);
	}
}

void CHighEfficiencyDlg::OnPaint(HDC hPaintDc)
{
	if (IsReady())
	{
		CRect WndRect = this->GetClientRect();

		HDC hMemoryDC = ::CreateCompatibleDC(hPaintDc);
		if (hMemoryDC != NULL)
		{
			HBITMAP hMemoryBitmap = ::CreateCompatibleBitmap(hPaintDc, WndRect.Width(), WndRect.Height());
			if (hMemoryBitmap != NULL)
			{
				::SelectObject(hMemoryDC, hMemoryBitmap);

				Graphics DoGrap(hMemoryDC);

				SolidBrush brush(Color(255, 0, 0, 255));
				DoGrap.FillRectangle(&brush, 0, 0, WndRect.Width(), WndRect.Height());

				// ��ʼ��ͼ
				m_pUiManager->OnPaint(hMemoryDC, WndRect);

				::BitBlt(hPaintDc, 0, 0, WndRect.Width(), WndRect.Height(),
					hMemoryDC, 0, 0, SRCCOPY);

				::DeleteObject(hMemoryBitmap);
			}
			::DeleteDC(hMemoryDC);
		}
	}
}

// �����Ƿ��ʼ��
bool CHighEfficiencyDlg::IsReady()
{
	return (m_pUiManager != NULL && m_hWnd != NULL && ::IsWindow(m_hWnd));
}

bool CHighEfficiencyDlg::OnDirectUiWindowMsgProc(int nMsgId, DWM_INFO &MsgInfo)
{
	bool bRet = false;
	if (IsReady())
	{
		bRet = true;
		if (nMsgId == DWM_LBUTTONDOWN)
		{
			DUI_OnLButtonDown(MsgInfo.wParam, MsgInfo.lParam);
		}
		else if (nMsgId == DWM_LBUTTONUP)
		{
			DUI_OnLButtonUp(MsgInfo.wParam, MsgInfo.lParam);
		}
		else if (nMsgId == DWM_LBUTTONDBLCLK)
		{
			DUI_OnLButtonDblClk(MsgInfo.wParam, MsgInfo.lParam);
		}
		else if (nMsgId == DWM_MOUSEHOVER)
		{
			DUI_OnMouseHover(MsgInfo.wParam, MsgInfo.lParam);
		}
		else if (nMsgId == DWM_MOUSELEAVE)
		{
			DUI_OnMouseLeave(MsgInfo.wParam, MsgInfo.lParam);
		}
	}
	return bRet;
}

// ������������Ϣ
void CHighEfficiencyDlg::DUI_OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
}

// ������̧����Ϣ
void CHighEfficiencyDlg::DUI_OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	if (wParam == DWM_SYS_CMD_MIN && IsSetBfStyle(BFS_HAVE_MIN_BTN))
	{
		// ��С��
		::ShowWindow(m_hWnd, SW_MINIMIZE);
	}
	else if (wParam == DWM_SYS_CMD_MAX_RES)
	{
		// ���/�ָ�
		MaxOrResWnd();
	}
	else if (wParam == DWM_SYS_CMD_CLOSE)
	{
		// �ر�
		EndThisDialog();
		::PostQuitMessage(0);
	}
}

// ������˫����Ϣ
void CHighEfficiencyDlg::DUI_OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	if (wParam == DWM_SYS_CMD_MAX_RES)
	{
		// ���/�ָ�
		MaxOrResWnd();
	}
}

// �����봰��
void CHighEfficiencyDlg::DUI_OnMouseHover(WPARAM wParam, LPARAM lParam)
{

}

// ����뿪����
void CHighEfficiencyDlg::DUI_OnMouseLeave(WPARAM wParam, LPARAM lParam)
{

}

void CHighEfficiencyDlg::MaxOrResWnd()
{
	if (IsSetBfStyle(BFS_HAVE_MAX_BTN))
	{
		bool bIsMaxWnd = IsSetBfStyle(BFS_MAX_WND);
		bIsMaxWnd = !bIsMaxWnd;

		if (bIsMaxWnd)
		{
			// ���
			AddBfStyle(BFS_MAX_WND);
			::ShowWindow(m_hWnd, SW_MAXIMIZE);
		}
		else
		{
			// �ָ�
			DeleteBfStyle(BFS_MAX_WND);
			::ShowWindow(m_hWnd, SW_RESTORE);
		}
	}
}
