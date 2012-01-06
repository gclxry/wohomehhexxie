
// UiFeatureBuilderView.cpp : CUiFeatureBuilderView ���ʵ��
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"

#include "UiFeatureBuilderDoc.h"
#include "UiFeatureBuilderView.h"
#include "MainFrm.h"
#include "FeatureControlList.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ������ʾ����view�ı߿����
#define SHOW_WINDOW_SPACE						(50)


// CUiFeatureBuilderView

IMPLEMENT_DYNCREATE(CUiFeatureBuilderView, CFormView)

BEGIN_MESSAGE_MAP(CUiFeatureBuilderView, CFormView)
	// ��׼��ӡ����
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CUiFeatureBuilderView ����/����

CUiFeatureBuilderView::CUiFeatureBuilderView() : CFormView(CUiFeatureBuilderView::IDD)
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	m_hUiEngineDll = NULL;
	m_pUiEngine = NULL;
	m_pKernelWindow = NULL;
	m_pSkinManager = NULL;
	m_pControlList = NULL;
	m_bInitOk = false;
	m_pCurrentWnd = NULL;
	m_pSelectControl = NULL;
	m_bIsLButtonDown = false;
	m_bMoveInWndFangKuai8 = false;
	m_bMoveInCtrlFangKuai8 = false;
	m_bCreateNewCtrl = false;

	m_ScrollOffset.cx = m_ScrollOffset.cy = 0;
	m_LBtnDownPos.x = m_LBtnDownPos.y = 0;
	m_MouseMovePos.x = m_MouseMovePos.y = 0;

	GetUiEngine();
}

CUiFeatureBuilderView::~CUiFeatureBuilderView()
{
	SAFE_FREE_LIBRARY(m_hUiEngineDll);
	GdiplusShutdown(m_gdiplusToken);
}

void CUiFeatureBuilderView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

void CUiFeatureBuilderView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// û��,��������۾�,�������������д�����,�ɵ����Ǿ��ܴﵽ���Ŀ�ģ����Լ�¼�ر�Builder������
//	GetParentFrame()->RecalcLayout();
//	ResizeParentToFit();
}

BOOL CUiFeatureBuilderView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CUiFeatureBuilderView::ResetShowWindow(IWindowBase *pCurrentWnd)
{
	m_pCurrentWnd = pCurrentWnd;

	ResetViewShowSize();
	this->RedrawWindow();
}

BOOL CUiFeatureBuilderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

// CUiFeatureBuilderView ����

IUiEngine* CUiFeatureBuilderView::GetUiEngine()
{
	if (m_hUiEngineDll == NULL || m_pUiEngine == NULL)
	{
		SAFE_FREE_LIBRARY(m_hUiEngineDll);
		string strPath = PathHelper(NAME_ENGINE_DLL);
		if (strPath.size() > 0)
		{
			m_hUiEngineDll = ::LoadLibraryA(strPath.c_str());
			if (m_hUiEngineDll != NULL)
			{
				GETUIENGINEINTERFACE pUiEngine = (GETUIENGINEINTERFACE)::GetProcAddress(m_hUiEngineDll, "GetUiEngineInterface");
				if (pUiEngine != NULL)
					m_pUiEngine = pUiEngine();
			}
		}
	}

	return m_pUiEngine;
}


// CUiFeatureBuilderView ��ӡ

void CUiFeatureBuilderView::Init(IUiFeatureKernel* pKernelWindow, CFeatureControlList *pCtrlList)
{
	m_pKernelWindow = pKernelWindow;
	m_pControlList = pCtrlList;
	if (m_pKernelWindow != NULL)
		m_pSkinManager = m_pKernelWindow->GetSkinManager();
}

void CUiFeatureBuilderView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CUiFeatureBuilderView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CUiFeatureBuilderView ���

#ifdef _DEBUG
void CUiFeatureBuilderView::AssertValid() const
{
	CFormView::AssertValid();
}

void CUiFeatureBuilderView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CUiFeatureBuilderDoc* CUiFeatureBuilderView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUiFeatureBuilderDoc)));
	return (CUiFeatureBuilderDoc*)m_pDocument;
}
#endif //_DEBUG


// CUiFeatureBuilderView ��Ϣ�������

void CUiFeatureBuilderView::SetProjectInitState(bool bInitOk)
{
	m_bInitOk = bInitOk;
}

void CUiFeatureBuilderView::SetNewControl(bool bIsNew)
{
	m_bCreateNewCtrl = bIsNew;
}

void CUiFeatureBuilderView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
		pMain->SetView(this);
}

void CUiFeatureBuilderView::OnDraw(CDC* pDC)
{
	if (pDC == NULL || !IS_SAFE_HANDLE(pDC->GetSafeHdc()) || m_pUiEngine == NULL)
		return;

	CSize ViewSize, sizePage, sizeLine;
	int nMode = 0;
	this->GetDeviceScrollSizes(nMode, ViewSize, sizePage, sizeLine);
	m_MemDc.Create(ViewSize.cx, ViewSize.cy, RGB(255,255,255), false, true);
	if (!IS_SAFE_HANDLE(m_MemDc.GetSafeHdc()))
		return;

	DrawWindowView();

	// ���ƴ����¿ؼ�ʱ�ľ���
	DrawCreateCtrlRect();

	::BitBlt(pDC->GetSafeHdc(), 0, 0, ViewSize.cx, ViewSize.cy, m_MemDc.GetSafeHdc(), 0, 0, SRCCOPY);
}

// ���ƴ����¿ؼ�ʱ�ľ���
void CUiFeatureBuilderView::DrawCreateCtrlRect()
{
	if (!m_bCreateNewCtrl)
		return;

	Graphics DoGrap(m_MemDc.GetSafeHdc());

	Pen LinePen(Color(255, 255, 0, 0), 1.5f);
	REAL dashVals[2] = {0.8f, 2.0f};
	LinePen.SetDashPattern(dashVals, 2);
	LinePen.SetDashOffset(30);

	DoGrap.DrawLine(&LinePen, m_LBtnDownPos.x, m_LBtnDownPos.y, m_MouseMovePos.x, m_LBtnDownPos.y);
	DoGrap.DrawLine(&LinePen, m_MouseMovePos.x, m_LBtnDownPos.y, m_MouseMovePos.x, m_MouseMovePos.y);
	DoGrap.DrawLine(&LinePen, m_MouseMovePos.x, m_MouseMovePos.y, m_LBtnDownPos.x, m_MouseMovePos.y);
	DoGrap.DrawLine(&LinePen, m_LBtnDownPos.x, m_MouseMovePos.y, m_LBtnDownPos.x, m_LBtnDownPos.y);

//	DoGrap.DrawRectangle(&LinePen, m_LBtnDownPos.x, m_LBtnDownPos.y, m_MouseMovePos.x - m_LBtnDownPos.x, m_MouseMovePos.y - m_LBtnDownPos.y);
}

void CUiFeatureBuilderView::DrawWindowView()
{
	CRect ViewRct(0, 0, 0, 0);
	this->GetClientRect(&ViewRct);

	// ����
	Graphics DoGrap(m_MemDc.GetSafeHdc());
	SolidBrush sBrush(Color(MAX_ALPHA, 255, 255, 255));
	DoGrap.FillRectangle(&sBrush, 0, 0, ViewRct.Width(), ViewRct.Height());

	// ���ڻ���
	if (m_pCurrentWnd != NULL)
		m_pCurrentWnd->BD_DrawWindowView(m_MemDc);
}

void CUiFeatureBuilderView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
	m_ScrollOffset.cx = this->GetScrollPos(SB_HORZ);
}

void CUiFeatureBuilderView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
	m_ScrollOffset.cy = this->GetScrollPos(SB_VERT);
}

void CUiFeatureBuilderView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	ResetViewShowSize();
	this->RedrawWindow();
}

void CUiFeatureBuilderView::ResetViewShowSize()
{
	int nWidth = 500, nHeight = 500;
	if (m_pCurrentWnd != NULL)
	{
		CRect ViewRct(0, 0, 0, 0);
		::GetClientRect(m_hWnd, &ViewRct);
		CSize WndSize = m_pCurrentWnd->PP_GetWindowPropSize();

		// ����View�Ĵ�С
		nWidth = ViewRct.Width();
		if (nWidth < WndSize.cx + SHOW_WINDOW_SPACE)
			nWidth = WndSize.cx + SHOW_WINDOW_SPACE;

		 nHeight = ViewRct.Height();
		if (nHeight < WndSize.cy + SHOW_WINDOW_SPACE)
			nHeight = WndSize.cy + SHOW_WINDOW_SPACE;
	}
	else
	{
		CRect ViewRct;
		::GetClientRect(m_hWnd, ViewRct);
		nWidth = ViewRct.Width();
		nHeight = ViewRct.Height();
	}

	this->SetScrollSizes(MM_TEXT, CSize(nWidth, nHeight));
}

void CUiFeatureBuilderView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CUiFeatureBuilderView::OnMouseMove(UINT nFlags, CPoint point)
{
	CFormView::OnMouseMove(nFlags, point);
	if (m_pSkinManager == NULL || m_pKernelWindow == NULL)
		return;

	if (m_bIsLButtonDown)
	{
		OnMouseMove_LButtonDown(point);
		return;
	}

	// �����Ҫ����һ���¿ؼ�
	if (m_bCreateNewCtrl)
		return;

	m_bMoveInWndFangKuai8 = OnMouseMove_FangKuai8(point, true);
	if (m_bMoveInWndFangKuai8)
		return;

	m_bMoveInCtrlFangKuai8 = OnMouseMove_FangKuai8(point, false);
	if (m_bMoveInCtrlFangKuai8)
		return;

	SetViewCursor(UF_IDC_ARROW);
}

void CUiFeatureBuilderView::OnMouseMove_LButtonDown(CPoint point)
{
	// �����Ҫ����һ���¿ؼ�
	if (m_bCreateNewCtrl)
	{
		// ���ƴ����¿ؼ�ʱ�ľ���
		m_MouseMovePos = point;
		this->RedrawWindow();
	}
	else if (m_bMoveInWndFangKuai8)
	{
		// �϶�����
	}
	else if (m_bMoveInCtrlFangKuai8)
	{
		// �϶��ؼ����ı�ؼ���С
	}
}

bool CUiFeatureBuilderView::OnMouseMove_FangKuai8(CPoint point, bool bIsWnd)
{
	point.x += m_ScrollOffset.cx;
	point.y += m_ScrollOffset.cy;

	FANGKUAI_8* pFk8 = NULL;
	if (bIsWnd)
	{
		if (m_pCurrentWnd != NULL)
			pFk8 = m_pCurrentWnd->BD_GetFangKuai8Rect();
	}
	else
	{
		if (m_pSelectControl != NULL)
			pFk8 = m_pCurrentWnd->BD_GetFangKuai8Rect();
	}

	if (pFk8 == NULL)
		return false;

	if (PtInRect(&pFk8->LeftTop, point))
	{
		SetViewCursor(UF_IDC_SIZENWSE);
		return true;
	}
	else if (PtInRect(&pFk8->LeftMid, point))
	{
		SetViewCursor(UF_IDC_SIZEWE);
		return true;
	}
	else if (PtInRect(&pFk8->LeftBottom, point))
	{
		SetViewCursor(UF_IDC_SIZENESW);
		return true;
	}
	else if (PtInRect(&pFk8->MidTop, point))
	{
		SetViewCursor(UF_IDC_SIZENS);
		return true;
	}
	else if (PtInRect(&pFk8->MidBottom, point))
	{
		SetViewCursor(UF_IDC_SIZENS);
		return true;
	}
	else if (PtInRect(&pFk8->RightTop, point))
	{
		SetViewCursor(UF_IDC_SIZENESW);
		return true;
	}
	else if (PtInRect(&pFk8->RightMid, point))
	{
		SetViewCursor(UF_IDC_SIZEWE);
		return true;
	}
	else if (PtInRect(&pFk8->RightBottom, point))
	{
		SetViewCursor(UF_IDC_SIZENWSE);
		return true;
	}

	return false;
}

// ���ù��
void CUiFeatureBuilderView::SetViewCursor(int nCursor)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
		pMain->SetViewCursor(nCursor);
}

void CUiFeatureBuilderView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CFormView::OnLButtonUp(nFlags, point);

	if (!m_bInitOk)
		return;

	m_bIsLButtonDown = false;

	// �����Ҫ����һ���¿ؼ�
	if (m_bCreateNewCtrl)
	{
		m_bCreateNewCtrl = false;
		this->RedrawWindow();
		return;
	}
}

//void CUiFeatureBuilderView::CreateNewControl(CPoint point)
//{
//
//	// �����¿ؼ�
//	if (m_pControlList != NULL)
//	{
//		CString strCtrlTypeName = m_pControlList->GetSelectCtrlTypeName();
//	}
//}

void CUiFeatureBuilderView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CFormView::OnLButtonDown(nFlags, point);
	m_LBtnDownPos = point;

	if (m_pSkinManager == NULL || m_pKernelWindow == NULL)
		return;

	m_bIsLButtonDown = true;

	// �����Ҫ����һ���¿ؼ�
	if (m_bCreateNewCtrl)
		return;


	// �ж��������������ĸ��ؼ���
}
