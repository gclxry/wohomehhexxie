
// UiFeatureBuilderView.cpp : CUiFeatureBuilderView 类的实现
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"

#include "UiFeatureBuilderDoc.h"
#include "UiFeatureBuilderView.h"

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
END_MESSAGE_MAP()

// CUiFeatureBuilderView 构造/析构

CUiFeatureBuilderView::CUiFeatureBuilderView()
{
	// TODO: 在此处添加构造代码

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
