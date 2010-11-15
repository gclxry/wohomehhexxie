
#include "DirectUiWindow.h"
#include "DirectUiManager.h"

bool CDirectUiWindow::ms_bIsWndLButtonDown = false;
CDirectUiWindow* CDirectUiWindow::ms_pLButtonDownWnd = NULL;
CDirectUiWindow* CDirectUiWindow::ms_pFocusWnd = NULL;
int CDirectUiWindow::ms_nDefaultWndId = 4;

CDirectUiWindow::CDirectUiWindow(void)
{
	m_pParentDlg = NULL;
	m_hParent = NULL;
	m_pDoGrap = NULL;
	m_hMemoryDC = NULL;
	m_pUiManager = NULL;
	m_pMsgCtrl = NULL;
	m_WndRect.SetRectEmpty();
	m_nWndId = 0;
	m_WndType = (WND_TYPE)0;
	m_BkColor = Color(255, 255, 255, 255);
	m_MsgInfo.lParam = m_MsgInfo.wParam = NULL;

	m_dwWndAttr = DWP_VISABLE | DWP_ENABLE | DWP_MSG_PAINT;

	SetDefaultFont();
}

CDirectUiWindow::~CDirectUiWindow(void)
{
}

bool CDirectUiWindow::IsReady()
{
	return (IS_SAVE_HANDLE(m_hParent) && m_pMsgCtrl != NULL && m_pUiManager != NULL);
}

void CDirectUiWindow::MoveWindow(CRect ToRect, HDWP hWinPoslnfo)
{
	if (IsReady())
	{
		m_WndRect = ToRect;
		SetTextRect(ToRect);
	}
}

void CDirectUiWindow::SetVisable(bool bIsVisable, bool bRedraw)
{
	if (bIsVisable)
		m_dwWndAttr |= DWP_VISABLE;
	else
		m_dwWndAttr &= ~DWP_VISABLE;

	if (bIsVisable && bRedraw)
		this->RedrawWindow();
}

bool CDirectUiWindow::OnMouseMoveProc(UINT nFlags, CPoint point)
{
	if (IsVisable() && IsEnable() && IsReady() && AllowMouseMoveMsg())
	{
		if (IsMouseHover())
		{
			if (!PtInRect(&m_WndRect, point))
			{
				// 鼠标离开本窗口
				m_dwWndAttr &= ~DWP_MOUSEHOVER;
				OnMouseLeave(point);
			}
		}
		else
		{
			if (PtInRect(&m_WndRect, point))
			{
				// 鼠标进入本窗口
				m_dwWndAttr |= DWP_MOUSEHOVER;
				OnMouseHover(point);
			}
		}

		if (IsMouseHover())
			OnMouseMove(point);
	}

	return IsMouseHover();
}

void CDirectUiWindow::OnLoseFocusProc()
{
	m_dwWndAttr &= ~DWP_FOCUS;
	OnLoseFocus();
}

void CDirectUiWindow::OnSetFocusProc()
{
	m_dwWndAttr |= DWP_FOCUS;
	OnSetFocus();
}

bool CDirectUiWindow::OnLButtonDownProc(UINT nFlags, CPoint point)
{
	bool bRet = false;
	if (IsVisable() && IsEnable() && IsReady() && AllowMouseDownMsg() && !CDirectUiWindow::IsWndLButtonDown() && PtInRect(&m_WndRect, point))
	{
		// 鼠标在本窗口按下
		m_dwWndAttr |= DWP_MOUSEDOWN;
		CDirectUiWindow::SetLButtonDown(this);
		OnLButtonDown(point);

		// 发送消息
		if (m_MsgInfo.wParam > 0 && PtInRect(&m_WndRect, point))
			m_pMsgCtrl->OnDirectUiWindowMsgProc(DWM_LBUTTONDOWN, m_MsgInfo);

		bRet = true;
	}
	return bRet;
}

bool CDirectUiWindow::OnLButtonUpProc(UINT nFlags, CPoint point)
{
	bool bRet = false;
	if (IsVisable() && IsEnable() && IsReady() && AllowMouseDownMsg() && IsThisWndDown(this))
	{
		// 鼠标在本窗口抬起
		m_dwWndAttr &= ~DWP_MOUSEDOWN;
		CDirectUiWindow::SetLButtonUp();
		OnLButtonUp(point);

		// 发送消息
		if (m_MsgInfo.wParam > 0 && PtInRect(&m_WndRect, point))
			m_pMsgCtrl->OnDirectUiWindowMsgProc(DWM_LBUTTONUP, m_MsgInfo);

		bRet = true;
	}
	return bRet;
}

bool CDirectUiWindow::OnLButtonDblClkProc(UINT nFlags, CPoint point)
{
	bool bRet = false;
	if (IsVisable() && IsEnable() && IsReady() && AllowMouseDClickMsg() && PtInRect(&m_WndRect, point))
	{
		OnLButtonDblClk(point);

		// 鼠标在本窗口双击
		if (m_MsgInfo.wParam > 0)
			m_pMsgCtrl->OnDirectUiWindowMsgProc(DWM_LBUTTONDBLCLK, m_MsgInfo);

		bRet = true;
	}
	return bRet;
}

bool CDirectUiWindow::CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
					   CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	bool bRet = false;

	if (!IsReady() && pParentDlg != NULL && pUiManager != NULL && pMsgCtrl != NULL && nWndId >= 0 && WndType > (WND_TYPE)0)
	{
		m_pParentDlg = pParentDlg;
		m_hParent = m_pParentDlg->GetSafeHandle();
		m_pUiManager = pUiManager;
		m_pMsgCtrl = pMsgCtrl;
		m_WndRect = WndRect;
		m_nWndId = nWndId;
		m_WndType = WndType;
		m_MsgInfo.wParam = m_nWndId;

		// 普通bar
		if (WndType & DWT_BAR_NORMAL)
		{
			// 不需进行绘图操作
			m_dwWndAttr &= ~DWP_MSG_PAINT;
		}

		// ComboBox的选择按钮Bar
		if (WndType == DWT_BAR_COMBO_SELECT_BUTTON)
		{
			// 需要鼠标单击消息和鼠标移动消息
			m_dwWndAttr |= DWP_MSG_MOUSEDOWN | DWP_MSG_MOUSEMOUSE;
		}

		// 标题栏
		if (WndType == DWT_BAR_CAPTION)
		{
			// 允许双击
			m_dwWndAttr |= DWP_MSG_MOUSEDCLICK;
			m_MsgInfo.wParam = DWM_SYS_CMD_MAX_RES;
		}

		// 按钮
		if (WndType & DWT_BUTTON)
		{
			m_dwWndAttr |= DWP_MSG_MOUSEDOWN | DWP_MSG_MOUSEMOUSE;
			this->SetCenterText();
		}

		if (WndType == DWT_LINK_STATIC || WndType == DWT_MOUSEMOVE_STATIC || WndType == DWT_GIF_STATIC)
		{
			m_dwWndAttr |= DWP_MSG_MOUSEDOWN | DWP_MSG_MOUSEMOUSE;
		}
		
		if (WndType & DWT_EDIT)
		{
			m_dwWndAttr |= DWP_MSG_MOUSEDOWN | DWP_MSG_MOUSEMOUSE;
		}

		if (WndType & DWT_CHECK_BOX)
		{
			m_dwWndAttr |= DWP_MSG_MOUSEDOWN | DWP_MSG_MOUSEMOUSE;
		}

		if (WndType & DWT_COMBO_BOX)
		{
			m_dwWndAttr |= DWP_MSG_MOUSEMOUSE;
		}

		// 导入窗口背景图片
		SetBkgndImage(nImageId, strImagePath, nImageType);

		bRet = true;
	}

	return bRet;
}

bool CDirectUiWindow::SetBkgndImage(int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	bool bRet = false;

	// 导入窗口背景图片
	if (nImageId > 0)
		bRet = m_BkgndImage.LoadImageFromRes(nImageId, nImageType);

	if (!strImagePath.IsEmpty())
		bRet = m_BkgndImage.LoadImageFromFile(strImagePath, nImageType);

	return bRet;
}

void CDirectUiWindow::SetTextFont(CString strFontName, int nFontHeight, FontStyle FStyle, Color nColor, StringFormat *pFormat)
{
	m_WndTextInfo.strFontName = strFontName;
	m_WndTextInfo.nFontHeight = nFontHeight;
	m_WndTextInfo.FStyle = FStyle;
	m_WndTextInfo.TextColor = nColor;

	if (pFormat != NULL)
	{

	}
}

// 设置文字现在在窗口正中央
void CDirectUiWindow::SetCenterText()
{
	m_WndTextInfo.OutFormat.SetAlignment(StringAlignmentCenter);
	m_WndTextInfo.OutFormat.SetLineAlignment(StringAlignmentCenter);
}

void CDirectUiWindow::OnPaintProc(Graphics *pDoGrap, HDC hMemoryDC)
{
	if (IsVisable() && IsReady() && AllowPaintMsg() && !m_WndRect.IsRectEmpty())
	{
		m_pDoGrap = pDoGrap;
		m_hMemoryDC = hMemoryDC;
		OnPaint();
	}
}

void CDirectUiWindow::SetTextRect(CRect TextRect)
{
	m_WndTextInfo.TextRectF = CRect2RectF(TextRect);
}

CRect CDirectUiWindow::GetWndTextRect()
{
	CRect TextRect(0, 0, 0, 0);
	if (IsReady())
	{
//		TextRect = m_pUiManager->GetTextRect(m_WndTextInfo.strText, m_WndTextInfo);
	}

	return TextRect;
}

void CDirectUiWindow::RedrawWindow(UINT flags)
{
	::RedrawWindow(m_hParent, &m_WndRect, NULL, flags);
}

void CDirectUiWindow::SetDefaultFont()
{
	SetTextFont(_T("宋体"), 12, FontStyleRegular, Color(0, 0, 0));
}

void CDirectUiWindow::OnDestroy()
{
	m_dwWndAttr &= ~DWP_VISABLE;
	m_dwWndAttr |= DWP_DESTROY;
}

void CDirectUiWindow::OnEnterSizeProc(WPARAM wParam, LPARAM lParam)
{
	m_dwWndAttr |= DWP_ENTERSIZEMOVE;
	OnEnterSize();
}

void CDirectUiWindow::OnExitSizeProc(WPARAM wParam, LPARAM lParam)
{
	m_dwWndAttr &= ~DWP_ENTERSIZEMOVE;
	OnExitSize();
}

void CDirectUiWindow::SetHotWnd(bool bIsHot)
{
	if (bIsHot)
		m_dwWndAttr |= DWP_HOT_WND;
	else
		m_dwWndAttr &= ~DWP_HOT_WND;
}

// 设置是否允许接收某一类消息
void CDirectUiWindow::SetAllowMsg(DWORD dwMsg, bool bIsAllow)
{
	if (bIsAllow)
		m_dwWndAttr |= dwMsg;
	else
		m_dwWndAttr &= ~dwMsg;
}

void CDirectUiWindow::DeleteBkgndImage()
{
	m_BkgndImage.FreeResImage();
}
