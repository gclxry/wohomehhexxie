// DialogViewBase.cpp : implementation file
//


#include "stdafx.h"
#include "DialogViewBase.h"
#include "..\..\Inc\UiFeatureDefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogViewBase dialog


CDialogViewBase::CDialogViewBase(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogViewBase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogViewBase)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bIsLBtnDown = false;
	m_rcViewSize.SetRectEmpty();
	m_rcDlgSize.SetRectEmpty();
	m_ptLBtnDown.x = m_ptLBtnDown.y = 0;
	m_nVScrollPos = 0;
	m_nHScrollPos = 0;

	// modeless dialog - don't forget to force the
	// WS_CHILD style in the resource template and remove
	// caption and system menu
	Create(CDialogViewBase::IDD, pParent);
}


void CDialogViewBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogViewBase)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogViewBase, CDialog)
	//{{AFX_MSG_MAP(CDialogViewBase)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
	ON_WM_SETCURSOR()
	ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogViewBase message handlers

BOOL CDialogViewBase::OnInitDialog() 
{
	CDialog::OnInitDialog();
	this->GetClientRect(m_rcViewSize);
	return TRUE;
}

void CDialogViewBase::OnSize_SetViewSize(int cx, int cy)
{
	m_rcViewSize = m_rcDlgSize;
}

void CDialogViewBase::OnDraw()
{

}

void CDialogViewBase::OnCancel() 
{
}

void CDialogViewBase::OnOK() 
{
}

void CDialogViewBase::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nDelta = 0;
	int nMaxPos = m_rcViewSize.Width();

	switch (nSBCode)
	{
	case SB_LINERIGHT:
		if (m_nHScrollPos < nMaxPos)
			nDelta = min(max(nMaxPos/20,5),nMaxPos-m_nHScrollPos);
		break;

	case SB_LINELEFT:
		if (m_nHScrollPos > 0)
			nDelta = -min(max(nMaxPos/20,5),m_nHScrollPos);
		break;

	case SB_PAGERIGHT:
		if (m_nHScrollPos < nMaxPos)
			nDelta = min(max(nMaxPos/10,5),nMaxPos-m_nHScrollPos);
		break;

	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		nDelta = (int)nPos - m_nHScrollPos;
		break;

	case SB_PAGELEFT:
		if (m_nHScrollPos > 0)
			nDelta = -min(max(nMaxPos/10,5),m_nHScrollPos);
		break;

	default:
		return;
	}
	m_nHScrollPos += nDelta;
	if (m_nHScrollPos > nMaxPos)
		m_nHScrollPos = nMaxPos;
	if (m_nHScrollPos < 0)
		m_nHScrollPos = 0;

	SetScrollPos(SB_HORZ, m_nHScrollPos, TRUE);
//	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	this->RedrawWindow();
}

void CDialogViewBase::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (pScrollBar != NULL)
	{
		SCROLLBARINFO ScrollInfo;
		pScrollBar->GetScrollBarInfo(&ScrollInfo);
	}

	int nDelta = 0;
	int nMaxPos = m_rcViewSize.Height();

	switch (nSBCode)
	{
	case SB_LINEDOWN:
		if (m_nVScrollPos < nMaxPos)
			nDelta = min(max(nMaxPos/20,5),nMaxPos-m_nVScrollPos);
		break;

	case SB_LINEUP:
		if (m_nVScrollPos > 0)
			nDelta = -min(max(nMaxPos/20,5),m_nVScrollPos);
		break;

	case SB_PAGEDOWN:
		if (m_nVScrollPos < nMaxPos)
			nDelta = min(max(nMaxPos/10,5),nMaxPos-m_nVScrollPos);
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		nDelta = (int)nPos - m_nVScrollPos;
		break;

	case SB_PAGEUP:
		if (m_nVScrollPos > 0)
			nDelta = -min(max(nMaxPos/10,5),m_nVScrollPos);
		break;
	
	default:
		return;
	}
	m_nVScrollPos += nDelta;
	if (m_nVScrollPos > nMaxPos)
		m_nVScrollPos = nMaxPos;
	if (m_nVScrollPos < 0)
		m_nVScrollPos = 0;

	SetScrollPos(SB_VERT, m_nVScrollPos, TRUE);
//	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	this->RedrawWindow();
}

void CDialogViewBase::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	SetScrollBarSize(cx, cy);
}

void CDialogViewBase::SetScrollBarSize(int cx, int cy) 
{
	m_rcDlgSize.SetRectEmpty();
	m_rcDlgSize.right = cx;
	m_rcDlgSize.bottom = cy;

	OnSize_SetViewSize(cx, cy);

	m_nVScrollPos = m_nHScrollPos = 0;

	SCROLLINFO si;
	memset(&si, 0, sizeof(SCROLLINFO));
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = m_rcViewSize.Width();
	si.nPage = cx;
	si.nPos = 0;
	SetScrollInfo(SB_HORZ, &si, TRUE);

	memset(&si, 0, sizeof(SCROLLINFO));
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = m_rcViewSize.Height();
	si.nPage = cy;
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, TRUE);
}

void CDialogViewBase::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bIsLBtnDown=TRUE;
	SetCapture();
	m_ptLBtnDown=point;
	CDialog::OnLButtonDown(nFlags, point);
}

void CDialogViewBase::OnLButtonUp(UINT nFlags, CPoint point) 
{
	EndDrag();
	CDialog::OnLButtonUp(nFlags, point);
}

void CDialogViewBase::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bIsLBtnDown)
	{
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

void CDialogViewBase::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	EndDrag();
}

void CDialogViewBase::EndDrag()
{
	m_bIsLBtnDown = false;
	ReleaseCapture();
}

BOOL CDialogViewBase::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	BOOL bRet=TRUE;

	if (nHitTest == HTCLIENT)
	{
		bRet=FALSE;
	}
	else
	{
		bRet=CDialog::OnSetCursor(pWnd,nHitTest,message);
	}

	return bRet;
}

BOOL CDialogViewBase::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CDialogViewBase::OnPaint()
{
	CPaintDC dc(this);

	m_MemDc.Create(m_rcViewSize.Width(), m_rcViewSize.Height(), RGB(255,255,255), false, true);
	if (!IS_SAFE_HANDLE(m_MemDc.GetSafeHdc()))
		return;

	// ±³¾°
	Graphics DoGrap(m_MemDc.GetSafeHdc());
	SolidBrush sBrush(Color(MAX_ALPHA, 255, 255, 255));
	DoGrap.FillRectangle(&sBrush, 0, 0, m_rcViewSize.Width(), m_rcViewSize.Height());

	OnDraw();

	CRect CltRct;
	CltRct.SetRectEmpty();
	this->GetClientRect(&CltRct);
	::BitBlt(dc.GetSafeHdc(), 0, 0, CltRct.Width(), CltRct.Height(),
		m_MemDc.GetSafeHdc(), m_nHScrollPos, m_nVScrollPos, SRCCOPY);
}
