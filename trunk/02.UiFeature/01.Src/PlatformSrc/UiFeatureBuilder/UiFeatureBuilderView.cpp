
// UiFeatureBuilderView.cpp : CUiFeatureBuilderView 类的实现
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"

#include "UiFeatureBuilderDoc.h"
#include "UiFeatureBuilderView.h"
#include "MainFrm.h"
#include "FeatureControlList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUiFeatureBuilderView

IMPLEMENT_DYNCREATE(CUiFeatureBuilderView, CView)

BEGIN_MESSAGE_MAP(CUiFeatureBuilderView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CUiFeatureBuilderView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CUiFeatureBuilderView 构造/析构

CUiFeatureBuilderView::CUiFeatureBuilderView()
{
	m_pKernelWindow = NULL;
	m_pControlList = NULL;
	m_bNewCtrl = false;
	m_bInitOk = false;
}

CUiFeatureBuilderView::~CUiFeatureBuilderView()
{
}

BOOL CUiFeatureBuilderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CUiFeatureBuilderView 绘制

void CUiFeatureBuilderView::OnDraw(CDC* /*pDC*/)
{
	CUiFeatureBuilderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CUiFeatureBuilderView 打印

void CUiFeatureBuilderView::Init(IKernelWindow* pKernelWindow, CFeatureControlList *pCtrlList)
{
	m_pKernelWindow = pKernelWindow;
	m_pControlList = pCtrlList;
}

void CUiFeatureBuilderView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CUiFeatureBuilderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CUiFeatureBuilderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CUiFeatureBuilderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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
		NMITEMACTIVATE *pSelItem = m_pControlList->GetSelectControlItem();
		if (pSelItem != NULL && pSelItem->iItem >= 0)
		{
			CString strCtrlTypeName = m_pControlList->GetItemText(pSelItem->iItem, CONTROL_NAME_COLUMN);
			int i = 0;
		}
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
	// TODO: Add your specialized code here and/or call the base class

	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
		pMain->SetView(this);
}
