
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

IMPLEMENT_DYNCREATE(CUiFeatureBuilderView, CView)

BEGIN_MESSAGE_MAP(CUiFeatureBuilderView, CView)
	// ��׼��ӡ����
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
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
	m_bNewCtrl = false;
	m_bInitOk = false;
	m_pCurrentWnd = NULL;

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

	return CView::PreCreateWindow(cs);
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
	CView::AssertValid();
}

void CUiFeatureBuilderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUiFeatureBuilderDoc* CUiFeatureBuilderView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUiFeatureBuilderDoc)));
	return (CUiFeatureBuilderDoc*)m_pDocument;
}
#endif //_DEBUG


// CUiFeatureBuilderView ��Ϣ�������

void CUiFeatureBuilderView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);

	if (!m_bInitOk)
		return;

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
	{
		// ���ù��
		::ShowCursor(FALSE);
		pMain->SetCrossCursor(false);
		::ShowCursor(TRUE);
	}

	::PostMessage(pMain->m_hWnd, WM_SETCURSOR, NULL, NULL);

	// �����¿ؼ�
	if (m_pControlList != NULL)
	{
		CString strCtrlTypeName = m_pControlList->GetSelectCtrlTypeName();
	}
}

void CUiFeatureBuilderView::SetProjectInitState(bool bInitOk)
{
	m_bInitOk = bInitOk;
}

void CUiFeatureBuilderView::SetNewControl(bool bIsNew)
{
	m_bNewCtrl = bIsNew;
}

void CUiFeatureBuilderView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
		pMain->SetView(this);
}

void CUiFeatureBuilderView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
	if (m_pSkinManager == NULL || m_pKernelWindow == NULL)
		return;

	// �ж��������������ĸ��ؼ���
}

void CUiFeatureBuilderView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);
	if (m_pSkinManager == NULL || m_pKernelWindow == NULL)
		return;

}

void CUiFeatureBuilderView::OnDraw(CDC* pDC)
{
	if (pDC == NULL || !IS_SAFE_HANDLE(pDC->GetSafeHdc()) || m_pUiEngine == NULL)
		return;

	CRect ViewRct(0, 0, 0, 0);
	this->GetClientRect(&ViewRct);
	m_MemDc.Create(ViewRct.Width(), ViewRct.Height(), RGB(255,255,255), false, true);
	if (!IS_SAFE_HANDLE(m_MemDc.GetSafeHdc()))
		return;

	DrawWindowView();

	::BitBlt(pDC->GetSafeHdc(), 0, 0, ViewRct.Width(), ViewRct.Height(), m_MemDc.GetSafeHdc(), 0, 0, SRCCOPY);
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
		m_pCurrentWnd->BD_DrawWindowView(m_hWnd, m_MemDc);
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
	this->SetScrollSizes(MM_TEXT, CSize(nWidth, nHeight));
}
