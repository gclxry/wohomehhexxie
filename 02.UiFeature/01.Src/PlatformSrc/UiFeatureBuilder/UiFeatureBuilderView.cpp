
// UiFeatureBuilderView.cpp : CUiFeatureBuilderView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CUiFeatureBuilderView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CUiFeatureBuilderView ����/����

CUiFeatureBuilderView::CUiFeatureBuilderView()
{
	m_pKernelWindow = NULL;
	m_pSkinManager = NULL;
	m_pControlList = NULL;
	m_bNewCtrl = false;
	m_bInitOk = false;
}

CUiFeatureBuilderView::~CUiFeatureBuilderView()
{
}

BOOL CUiFeatureBuilderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CUiFeatureBuilderView ����

void CUiFeatureBuilderView::OnDraw(CDC* /*pDC*/)
{
	CUiFeatureBuilderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CUiFeatureBuilderView ��ӡ

void CUiFeatureBuilderView::Init(IKernelWindow* pKernelWindow, CFeatureControlList *pCtrlList)
{
	m_pKernelWindow = pKernelWindow;
	m_pControlList = pCtrlList;
	if (m_pKernelWindow != NULL)
		m_pSkinManager = m_pKernelWindow->GetSkinManager();
}

void CUiFeatureBuilderView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CUiFeatureBuilderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CUiFeatureBuilderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CUiFeatureBuilderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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
