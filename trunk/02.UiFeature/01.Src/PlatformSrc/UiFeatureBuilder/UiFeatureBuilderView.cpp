
// UiFeatureBuilderView.cpp : CUiFeatureBuilderView 类的实现
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

// 窗口显示距离view的边框距离
#define SHOW_WINDOW_SPACE						(50)


// CUiFeatureBuilderView

IMPLEMENT_DYNCREATE(CUiFeatureBuilderView, CView)

BEGIN_MESSAGE_MAP(CUiFeatureBuilderView, CView)
	// 标准打印命令
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CUiFeatureBuilderView 构造/析构

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
	// 没错,相信你的眼睛,就是下面这两行代码了,干掉他们就能达到你的目的！可以记录关闭Builder布局了
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CUiFeatureBuilderView 绘制

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


// CUiFeatureBuilderView 打印

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


// CUiFeatureBuilderView 诊断

#ifdef _DEBUG
void CUiFeatureBuilderView::AssertValid() const
{
	CView::AssertValid();
}

void CUiFeatureBuilderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUiFeatureBuilderDoc* CUiFeatureBuilderView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUiFeatureBuilderDoc)));
	return (CUiFeatureBuilderDoc*)m_pDocument;
}
#endif //_DEBUG


// CUiFeatureBuilderView 消息处理程序

void CUiFeatureBuilderView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);

	if (!m_bInitOk)
		return;

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
	{
		// 设置光标
		::ShowCursor(FALSE);
		pMain->SetCrossCursor(false);
		::ShowCursor(TRUE);
	}

	::PostMessage(pMain->m_hWnd, WM_SETCURSOR, NULL, NULL);

	// 创建新控件
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

	// 判断数遍左键点击在哪个控件上
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

	// 背景
	Graphics DoGrap(m_MemDc.GetSafeHdc());
	SolidBrush sBrush(Color(MAX_ALPHA, 255, 255, 255));
	DoGrap.FillRectangle(&sBrush, 0, 0, ViewRct.Width(), ViewRct.Height());

	// 窗口绘制
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

		// 设置View的大小
		nWidth = ViewRct.Width();
		if (nWidth < WndSize.cx + SHOW_WINDOW_SPACE)
			nWidth = WndSize.cx + SHOW_WINDOW_SPACE;

		 nHeight = ViewRct.Height();
		if (nHeight < WndSize.cy + SHOW_WINDOW_SPACE)
			nHeight = WndSize.cy + SHOW_WINDOW_SPACE;
	}
	this->SetScrollSizes(MM_TEXT, CSize(nWidth, nHeight));
}
