// ImageBaseView.cpp : implementation file
//


#include "stdafx.h"
#include "ImageBaseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageBaseView dialog


CImageBaseView::CImageBaseView(CWnd* pParent /*=NULL*/)
	: CDialog(CImageBaseView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageBaseView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bDragging=FALSE;

	// modeless dialog - don't forget to force the
	// WS_CHILD style in the resource template and remove
	// caption and system menu
	Create(CImageBaseView::IDD,pParent);
}


void CImageBaseView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageBaseView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageBaseView, CDialog)
	//{{AFX_MSG_MAP(CImageBaseView)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageBaseView message handlers

BOOL CImageBaseView::OnInitDialog() 
{
	CDialog::OnInitDialog();

//	m_hCursor1=AfxGetApp()->LoadCursor(IDC_CURSOR1);
//	m_hCursor2=AfxGetApp()->LoadCursor(IDC_CURSOR2);

	//SetClassLong(m_hWnd,GCL_HCURSOR,(long)m_hCursor1);
	
	// save the original size
	GetWindowRect(m_rcOriginalRect);

	// initial scroll position
	m_nScrollPos = 0; 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImageBaseView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int nDelta;
	int nMaxPos = m_rcOriginalRect.Height() - m_nCurHeight;

	switch (nSBCode)
	{
	case SB_LINEDOWN:
		if (m_nScrollPos >= nMaxPos)
			return;

		nDelta = min(max(nMaxPos/20,5),nMaxPos-m_nScrollPos);
		break;

	case SB_LINEUP:
		if (m_nScrollPos <= 0)
			return;
		nDelta = -min(max(nMaxPos/20,5),m_nScrollPos);
		break;
	case SB_PAGEDOWN:
		if (m_nScrollPos >= nMaxPos)
			return;
		nDelta = min(max(nMaxPos/10,5),nMaxPos-m_nScrollPos);
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		nDelta = (int)nPos - m_nScrollPos;
		break;

	case SB_PAGEUP:
		if (m_nScrollPos <= 0)
			return;
		nDelta = -min(max(nMaxPos/10,5),m_nScrollPos);
		break;
	
         default:
		return;
	}
	m_nScrollPos += nDelta;
	SetScrollPos(SB_VERT,m_nScrollPos,TRUE);
	ScrollWindow(0,-nDelta);
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CImageBaseView::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	m_nCurHeight = cy;

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL; 
	si.nMin = 0;
	si.nMax = m_rcOriginalRect.Height();
	si.nPage = cy;
	si.nPos = 0;
    SetScrollInfo(SB_VERT, &si, TRUE); 	

}

BOOL CImageBaseView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	int nMaxPos = m_rcOriginalRect.Height() - m_nCurHeight;

	if (zDelta<0)
	{
		if (m_nScrollPos < nMaxPos)
		{
			zDelta = min(max(nMaxPos/20,5),nMaxPos-m_nScrollPos);

			m_nScrollPos += zDelta;
			SetScrollPos(SB_VERT,m_nScrollPos,TRUE);
			ScrollWindow(0,-zDelta);
		}
	}
	else
	{
		if (m_nScrollPos > 0)
		{
			zDelta = -min(max(nMaxPos/20,5),m_nScrollPos);

			m_nScrollPos += zDelta;
			SetScrollPos(SB_VERT,m_nScrollPos,TRUE);
			ScrollWindow(0,-zDelta);
		}
	}
	
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CImageBaseView::OnCancel() 
{
}

void CImageBaseView::OnOK() 
{
}

void CImageBaseView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bDragging=TRUE;
	SetCapture();

	m_ptDragPoint=point;

	SetCursor(m_hCursor2);
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CImageBaseView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	EndDrag();
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CImageBaseView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bDragging)
	{
		int nDelta=m_ptDragPoint.y-point.y;
		m_ptDragPoint=point;

		int nNewPos=m_nScrollPos+nDelta;

		if (nNewPos<0)
			nNewPos=0;
		else if (nNewPos>m_rcOriginalRect.Height() - m_nCurHeight)
			nNewPos=m_rcOriginalRect.Height() - m_nCurHeight;

		nDelta=nNewPos-m_nScrollPos;
		m_nScrollPos=nNewPos;

		SetScrollPos(SB_VERT,m_nScrollPos,TRUE);
		ScrollWindow(0,-nDelta);
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

void CImageBaseView::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);

	EndDrag();
}

void CImageBaseView::EndDrag()
{
	m_bDragging=FALSE;
	ReleaseCapture();
	SetCursor(m_hCursor1);
}

BOOL CImageBaseView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	BOOL bRet=TRUE;

	if (nHitTest==HTCLIENT)
	{
		SetCursor(m_hCursor1);
		bRet=FALSE;
	}
	else
		bRet=CDialog::OnSetCursor(pWnd,nHitTest,message);

	return bRet;
}
