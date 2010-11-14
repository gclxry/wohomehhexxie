
#include "HighEfficiencyDlg.h"
#include "BfMenuHook.h"

#define __base_super					CWin32BaseDlg

bool CHighEfficiency::m_bIsNeedLButtonUpMsg = false;

CHighEfficiency::CHighEfficiency(HINSTANCE hInstance, HWND hParentWnd, int nIconId)
: CWin32BaseDlg(hInstance, hParentWnd, nIconId)
{
	m_bIsHaveCaption = true;
	m_pCaptionBar = NULL;
	CBfMenuHook::InitMenuHook(m_hInstance);
}

CHighEfficiency::~CHighEfficiency(void)
{
	CBfMenuHook::UninitMenuHook();
}

LRESULT CHighEfficiency::OnEnterSizeMove(WPARAM wParam, LPARAM lParam)
{
	::SetFocus(m_hWnd);
	return DefWindowProc(m_hWnd, WM_ENTERSIZEMOVE, wParam, lParam);
}

LRESULT CHighEfficiency::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	// 非冻结状态下才响应鼠标消息
	if (!m_bIsFreeze)
	{
		AddBfStyle(BFS_FIRST_IN_WND);
		CPoint point(-1, -1);
		m_UiManager.OnMouseMove(0, point);
	}
	return 1;
}

LRESULT CHighEfficiency::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	// 非冻结状态下才响应鼠标消息
	if (!m_bIsFreeze)
	{
		// 请求取得鼠标离开窗口的消息
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
		m_UiManager.OnMouseMove(nFlags, point);
	}

	return 1;
}

LRESULT CHighEfficiency::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	::SetFocus(m_hWnd);

	SetFreezeDlg(false);

	//禁止显示移动矩形窗体框
	::SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);

	int nFlags = (int)wParam;
	CPoint point(LOWORD(lParam), HIWORD(lParam));
	m_UiManager.OnLButtonDown(nFlags, point);

	if (CDirectUiWnd::IsWndLButtonDown())
	{
		SetCapture(m_hWnd);

		if (CHighEfficiency::m_bIsNeedLButtonUpMsg)
		{
			CHighEfficiency::m_bIsNeedLButtonUpMsg = false;
			OnLButtonUp(wParam, lParam);
		}
	}
	else
	{
		if (!IsSetBfStyle(BFS_MAX_WND))
		{
			::PostMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, lParam);
		}
	}

	return 1;
}

LRESULT CHighEfficiency::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	ReleaseCapture();

	int nFlags = (int)wParam;
	CPoint point(LOWORD(lParam), HIWORD(lParam));
	m_UiManager.OnLButtonUp(nFlags, point);
	return 1;
}

LRESULT CHighEfficiency::OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	int nFlags = (int)wParam;
	CPoint point(LOWORD(lParam), HIWORD(lParam));
	m_UiManager.OnLButtonDblClk(nFlags, point);
	return 1;
}

LRESULT CHighEfficiency::OnNcHitTest(WPARAM wParam, LPARAM lParam)
{
	if (IsSetBfStyle(BFS_CAN_DRAW))
	{
		CPoint point(LOWORD(lParam), HIWORD(lParam));

		int nCheckPos = 5;
		int nRDPos = nCheckPos * 2;
		CRect WndRect(0, 0, 0, 0);
		::GetWindowRect(m_hWnd, &WndRect);

		if(point.x >= WndRect.right - nRDPos && point.y >= WndRect.bottom - nRDPos)
		{
			// 右下角
			return HTBOTTOMRIGHT;
		}
		else if(point.x >= WndRect.right - nRDPos && point.y <= WndRect.top + nRDPos)
		{
			// 右上角
			return HTTOPRIGHT;
		}
		else if(point.x <= WndRect.left + nRDPos && point.y <= WndRect.top + nRDPos)
		{
			// 左上角
			return HTTOPLEFT;
		}
		else if(point.x <= WndRect.left + nRDPos && point.y >= WndRect.bottom - nRDPos)
		{
			// 左下角
			return HTBOTTOMLEFT;
		}
		else if(point.x >= WndRect.right - nCheckPos)
		{
			// 右边线
			return HTRIGHT;
		}
		else if(point.x <= WndRect.left + nCheckPos)
		{
			// 左边线
			return HTLEFT;
		}
		else if(point.y <= WndRect.top + nCheckPos)
		{
			// 上边线
			return HTTOP;
		}
		else if(point.y >= WndRect.bottom - nCheckPos)
		{
			// 下边线
			return HTBOTTOM;
		}

		return __base_super::OnNcHitTest(wParam, lParam);
	}
	else
	{
		return DefWindowProc(m_hWnd, WM_NCHITTEST, wParam, lParam);
	}
}

void CHighEfficiency::OnDestroy()
{
	m_UiManager.OnDestroy();
}

LRESULT CHighEfficiency::OnNcActive(UINT message, WPARAM wParam, LPARAM lParam)
{
	return WM_PAINT;
}

LRESULT CHighEfficiency::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CHighEfficiency::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

void CHighEfficiency::OnCreate()
{
	// 初始化引擎
	m_UiManager.InitManager(this);

	// 设置默认大小
	CRect CenterRect = CenterWnd(260, 480);
	::MoveWindow(m_hWnd, CenterRect.left, CenterRect.top, CenterRect.Width(), CenterRect.Height(), FALSE);

	// 设置标题栏
	if (m_bIsHaveCaption)
	{
		m_pCaptionBar = m_UiManager.CreateBfCaptionBar(this, CRect(0, 0, 0, 0), IsSetBfStyle(BFS_HAVE_MIN_BTN), IsSetBfStyle(BFS_HAVE_MAX_BTN));
		if (m_pCaptionBar != NULL)
		{
			CString strSkinDir = GetAppPath();
			CString strPicPath = _T("");

			strPicPath = strSkinDir + _T("FetionData\\UseFace\\LogoS.bmp");
			m_pCaptionBar->SetLogoImage(0, strPicPath, IT_BMP);

			strPicPath = strSkinDir + _T("FetionData\\UseFace\\tbmin.png");
			m_pCaptionBar->SetMinBtnImage(0, strPicPath, IT_PNG);

			strPicPath = strSkinDir + _T("FetionData\\UseFace\\tbmax.png");
			m_pCaptionBar->SetMaxBtnImage(0, strPicPath, IT_PNG);

			strPicPath = strSkinDir + _T("FetionData\\UseFace\\tbnormal.png");
			m_pCaptionBar->SetResBtnImage(0, strPicPath, IT_PNG);

			strPicPath = strSkinDir + _T("FetionData\\UseFace\\tbclose.png");
			m_pCaptionBar->SetClsBtnImage(0, strPicPath, IT_PNG);
		}
	}

	// 设置背景参数
	m_UiManager.SetOutRingColor(Color(81, 154, 222));
	m_UiManager.SetInRingColor(Color(100, 229, 245, 254));
	m_UiManager.SetBkgndColor(Color(218, 241, 255));
}

LRESULT CHighEfficiency::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CHighEfficiency::OnSizeProc(WPARAM wParam, LPARAM lParam)
{
	int nCtns = m_UiManager.GetTrueWndCtns();

	HDWP hWinPoslnfo = NULL;
	hWinPoslnfo = BeginDeferWindowPos(nCtns);

	LRESULT lRes = OnSize(hWinPoslnfo, wParam, lParam);

	EndDeferWindowPos(hWinPoslnfo);

	return lRes;
}

LRESULT CHighEfficiency::OnTimer(WPARAM wParam, LPARAM lParam)
{
	int nTimerId = (int)wParam;
	m_UiManager.OnTimer(nTimerId);
	return 0;
}

LRESULT CHighEfficiency::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
//	m_UiManager.OnActivateApp(wParam, lParam);
	return CWin32BaseDlg::OnActivateApp(wParam, lParam);
}

LRESULT CHighEfficiency::OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam)
{
	int nType = (int)wParam;
	int cx = LOWORD(lParam); 
	int cy = HIWORD(lParam);

	SetWndRgn(cx, cy);

	if (m_pCaptionBar != NULL)
		m_pCaptionBar->MoveWindow(CRect(0, 0, cx, CAPTION_BAR_WND_H), hWinPoslnfo);

	return 1;
}

void CHighEfficiency::SetWndRgn(int cx, int cy)
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

void CHighEfficiency::OnPaint(HDC hPaintDc)
{
	CRect WndRect = GetWndRect(m_hWnd);

	HDC hMemoryDC = ::CreateCompatibleDC(hPaintDc);
	if (hMemoryDC != NULL)
	{
		HBITMAP hMemoryBitmap = ::CreateCompatibleBitmap(hPaintDc, WndRect.Width(), WndRect.Height());
		if (hMemoryBitmap != NULL)
		{
			::SelectObject(hMemoryDC, hMemoryBitmap);

			// 开始画图
			m_UiManager.OnPaint(hMemoryDC, WndRect);

			::BitBlt(hPaintDc, 0, 0, WndRect.Width(), WndRect.Height(),
				hMemoryDC, 0, 0, SRCCOPY);

			::DeleteObject(hMemoryBitmap);
		}
		::DeleteDC(hMemoryDC);
	}
}

// 窗口是否初始化
bool CHighEfficiency::IsReady()
{
	return ((m_pCaptionBar != NULL || !m_bIsHaveCaption) && m_hWnd != NULL && ::IsWindow(m_hWnd));
}

bool CHighEfficiency::OnDirectUiWndMsgProc(int nMsgId, DWM_INFO &MsgInfo)
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

// 鼠标左键按下消息
void CHighEfficiency::DUI_OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
}

// 鼠标左键抬起消息
void CHighEfficiency::DUI_OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	if (wParam == DWM_SYS_CMD_MIN && IsSetBfStyle(BFS_HAVE_MIN_BTN))
	{
		// 最小化
		::ShowWindow(m_hWnd, SW_MINIMIZE);
	}
	else if (wParam == DWM_SYS_CMD_MAX_RES)
	{
		// 最大化/恢复
		MaxOrResWnd();
	}
	else if (wParam == DWM_SYS_CMD_CLOSE)
	{
		// 关闭
		EndThisDialog();
		::PostQuitMessage(0);
	}
}

// 鼠标左键双击消息
void CHighEfficiency::DUI_OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	if (wParam == DWM_SYS_CMD_MAX_RES)
	{
		// 最大化/恢复
		MaxOrResWnd();
	}
}

// 鼠标进入窗口
void CHighEfficiency::DUI_OnMouseHover(WPARAM wParam, LPARAM lParam)
{

}

// 鼠标离开窗口
void CHighEfficiency::DUI_OnMouseLeave(WPARAM wParam, LPARAM lParam)
{

}

void CHighEfficiency::MaxOrResWnd()
{
	if (IsSetBfStyle(BFS_HAVE_MAX_BTN))
	{
		bool bIsMaxWnd = IsSetBfStyle(BFS_MAX_WND);
		bIsMaxWnd = !bIsMaxWnd;

		m_UiManager.SetWndMaxState(bIsMaxWnd);
		if (bIsMaxWnd)
		{
			// 最大化
			AddBfStyle(BFS_MAX_WND);
			::ShowWindow(m_hWnd, SW_MAXIMIZE);
		}
		else
		{
			// 恢复
			DeleteBfStyle(BFS_MAX_WND);
			::ShowWindow(m_hWnd, SW_RESTORE);
		}
	}
}

LRESULT CHighEfficiency::OnMeasureItem(WPARAM wParam, LPARAM lParam)
{
	int nIdCtl = (UINT)wParam;

	// 此参数为0代表消息来源于菜单
	if (nIdCtl == 0)
		CBfPopupMenu::OnMeasureItem((LPMEASUREITEMSTRUCT)lParam);

	return 0;
}

LRESULT CHighEfficiency::OnDrawItem(WPARAM wParam, LPARAM lParam)
{
	int nIdCtl = (UINT)wParam;

	// 此参数为0代表消息来源于菜单
	if (nIdCtl == 0)
		CBfPopupMenu::OnDrawItem((LPDRAWITEMSTRUCT)lParam);

	return 0;
}

void CHighEfficiency::RedrawDlg()
{
	RedrawWindow(m_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}
