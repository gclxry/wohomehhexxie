
// UiFeatureBuilderView.cpp : CUiFeatureBuilderView ���ʵ��
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"

#include "UiFeatureBuilderDoc.h"
#include "UiFeatureBuilderView.h"
#include "MainFrm.h"
#include "FeatureControlList.h"
#include "WindowsViewTree.h"
#include "PropertyViewCtrl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"

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
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CUiFeatureBuilderView ����/����

CUiFeatureBuilderView::CUiFeatureBuilderView() : CFormView(CUiFeatureBuilderView::IDD)
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	m_nMoveFangKuai8Type = SCT_NONE;
	m_pUiEngine = NULL;
	m_pUiKernel = NULL;
	m_pSkinManager = NULL;
	m_pControlList = NULL;
	m_pWindowViewTree = NULL;
	m_pPropViewCtrl = NULL;
	m_bInitOk = false;
	m_pCurrentWnd = NULL;
	m_pDrawParentCtrl = NULL;
	m_pMouseMoveCtrl = NULL;
	m_bIsLButtonDown = false;
	m_bMoveInWndFangKuai8 = false;
	m_bMoveInCtrlFangKuai8 = false;
	m_bCreateNewCtrl = false;;
	m_bSizeMoveCtrl = false;

	m_ScrollOffset.cx = m_ScrollOffset.cy = 0;
	m_LBtnDownPos.x = m_LBtnDownPos.y = 0;
	m_MouseMovePos.x = m_MouseMovePos.y = 0;
	m_LBtnUpPos.x = m_LBtnUpPos.y = 0;
}

CUiFeatureBuilderView::~CUiFeatureBuilderView()
{
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

void CUiFeatureBuilderView::ResetShowWindow(IWindowBase *pCurrentWnd, IControlBase *pCtrlBase)
{
	m_pCurrentWnd = pCurrentWnd;
	if (m_pCurrentWnd != NULL)
		m_pCurrentWnd->BD_SetFocusControl(pCtrlBase);

	ResetViewShowSize();
	this->RedrawWindow();
}

BOOL CUiFeatureBuilderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CUiFeatureBuilderView::Init(IUiFeatureKernel* pKernelWindow, CFeatureControlList *pCtrlList, CWindowsViewTree *pWndTree, CPropertyViewCtrl* pPropViewCtrl)
{
	m_pUiKernel = pKernelWindow;
	m_pControlList = pCtrlList;
	m_pPropViewCtrl = pPropViewCtrl;
	m_pWindowViewTree = pWndTree;
	if (m_pUiKernel != NULL)
	{
		m_pSkinManager = m_pUiKernel->GetSkinManager();
		m_pUiEngine = m_pUiKernel->GetUiEngine();
	}
}

void CUiFeatureBuilderView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (!m_bInitOk)
		return;

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

	this->RedrawWindow();
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

	this->SetTimer(UM_DFT_ANIMATION_TIMER, UM_DFT_ANIMATION_TIMER_100S, NULL);
}

void CUiFeatureBuilderView::OnDraw(CDC* pDC)
{
	if (pDC == NULL || !IS_SAFE_HANDLE(pDC->GetSafeHdc()) || m_pUiEngine == NULL)
		return;

	CSize ViewSize, sizePage, sizeLine;
	int nMode = 0;
	this->GetDeviceScrollSizes(nMode, ViewSize, sizePage, sizeLine);

	CRect ViewRct(0, 0, 0, 0);
	this->GetClientRect(&ViewRct);

	if (ViewSize.cx < ViewRct.Width())
		ViewSize.cx = ViewRct.Width();
	if (ViewSize.cy < ViewRct.Height())
		ViewSize.cy = ViewRct.Height();

	m_MemDc.Create(ViewSize.cx, ViewSize.cy, RGB(255,255,255), false, true);
	if (!IS_SAFE_HANDLE(m_MemDc.GetSafeHdc()))
		return;

	// ���ƴ����Լ����пؼ�
	DrawWindowView();

	// ���ƴ����¿ؼ�ʱ�ľ���
	DrawMark();

	::BitBlt(pDC->GetSafeHdc(), 0, 0, ViewSize.cx, ViewSize.cy, m_MemDc.GetSafeHdc(), 0, 0, SRCCOPY);
}

// ���ƴ����¿ؼ�ʱ�ľ���
void CUiFeatureBuilderView::DrawMark()
{
	if (m_pCurrentWnd == NULL || !m_bInitOk)
		return;

	Graphics DoGrap(m_MemDc.GetSafeHdc());

	Pen LinePen(Color(30, 0, 0, 255));
	SolidBrush PinkBrs(Color(15, 255, 0, 255));
	Pen FrameLinePen(Color(255, 255, 0, 0), 1.5f);
	REAL dashVals[2] = {0.8f, 2.0f};
	FrameLinePen.SetDashPattern(dashVals, 2);
	FrameLinePen.SetDashOffset(30);

	FANGKUAI_8* pFk8 = NULL;
	if (m_pMouseMoveCtrl != NULL && !m_bIsLButtonDown)
	{
		// ���Ƶ�ǰ����ƶ����Ŀؼ��ϣ����ƿؼ��߿�
		pFk8 = m_pMouseMoveCtrl->BD_GetFangKuai8Rect();
		DoGrap.DrawLine(&LinePen, pFk8->EntityRct.left, pFk8->EntityRct.top, pFk8->EntityRct.right, pFk8->EntityRct.top);
		DoGrap.DrawLine(&LinePen, pFk8->EntityRct.right, pFk8->EntityRct.top, pFk8->EntityRct.right, pFk8->EntityRct.bottom);
		DoGrap.DrawLine(&LinePen, pFk8->EntityRct.right, pFk8->EntityRct.bottom, pFk8->EntityRct.left, pFk8->EntityRct.bottom);
		DoGrap.DrawLine(&LinePen, pFk8->EntityRct.left, pFk8->EntityRct.bottom, pFk8->EntityRct.left, pFk8->EntityRct.top);
	}

	// ���ƴ����¿ؼ�ʱ�ľ���
	pFk8 = NULL;
	// �Ȼ��Ʊ�ѡ�еĸ��ؼ�������
	if (m_pDrawParentCtrl != NULL)
		pFk8 = m_pDrawParentCtrl->BD_GetFangKuai8Rect();
	else
		pFk8 = m_pCurrentWnd->BD_GetFangKuai8Rect();

	if ((m_bSizeMoveCtrl || m_bCreateNewCtrl) && m_bIsLButtonDown && m_pCurrentWnd != NULL)
	{
		DoGrap.FillRectangle(&PinkBrs, pFk8->EntityRct.left, pFk8->EntityRct.top, RECT_WIDTH(pFk8->EntityRct), RECT_HEIGHT(pFk8->EntityRct));

		if (m_bCreateNewCtrl)
		{
			DoGrap.DrawLine(&FrameLinePen, m_LBtnDownPos.x, m_LBtnDownPos.y, m_MouseMovePos.x, m_LBtnDownPos.y);
			DoGrap.DrawLine(&FrameLinePen, m_MouseMovePos.x, m_LBtnDownPos.y, m_MouseMovePos.x, m_MouseMovePos.y);
			DoGrap.DrawLine(&FrameLinePen, m_MouseMovePos.x, m_MouseMovePos.y, m_LBtnDownPos.x, m_MouseMovePos.y);
			DoGrap.DrawLine(&FrameLinePen, m_LBtnDownPos.x, m_MouseMovePos.y, m_LBtnDownPos.x, m_LBtnDownPos.y);
		}
	}

	if (m_bMoveInCtrlFangKuai8 && m_pDrawParentCtrl != NULL)
	{
		DoGrap.FillRectangle(&PinkBrs, pFk8->EntityRct.left, pFk8->EntityRct.top, RECT_WIDTH(pFk8->EntityRct), RECT_HEIGHT(pFk8->EntityRct));
	}
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
	if (m_pCurrentWnd != NULL && m_bInitOk)
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

	if (!m_bInitOk)
		return;

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

		FANGKUAI_8* pFk8 = m_pCurrentWnd->BD_GetFangKuai8Rect();
		if (pFk8 != NULL)
		{
			// ���õ�ǰ���������ӿؼ���λ��
			pFk8->EntityRct.left = (ViewRct.Width() - WndSize.cx) / 2;
			pFk8->EntityRct.right = pFk8->EntityRct.left + WndSize.cx;
			pFk8->EntityRct.top = (ViewRct.Height() - WndSize.cy) / 2;
			pFk8->EntityRct.bottom = pFk8->EntityRct.top + WndSize.cy;
			m_pCurrentWnd->BD_SetAllCtrlRectInView();
		}
	}
	else
	{
		CRect ViewRct;
		::GetClientRect(m_hWnd, ViewRct);
		nWidth = ViewRct.Width();
		nHeight = ViewRct.Height();
	}

	m_ScrollOffset.cx = m_ScrollOffset.cy = 0;
	this->SetScrollSizes(MM_TEXT, CSize(nWidth, nHeight));
}

void CUiFeatureBuilderView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);

	if (!m_bInitOk)
		return;

}

void CUiFeatureBuilderView::OnMouseMove(UINT nFlags, CPoint point)
{
	CFormView::OnMouseMove(nFlags, point);

	if (!m_bInitOk)
		return;

	m_MouseMovePos = point;
	m_pMouseMoveCtrl = NULL;

	if (!m_bInitOk || m_pSkinManager == NULL || m_pUiKernel == NULL)
		return;

	if (m_bIsLButtonDown)
	{
		SetNeedSave();
		OnMouseMove_LButtonDown(point);
		this->RedrawWindow();
		return;
	}

	m_pMouseMoveCtrl = GetSelectControl(point);
	// �����Ҫ����һ���¿ؼ�
	if (m_bCreateNewCtrl)
	{
		this->RedrawWindow();
		return;
	}

	m_nMoveFangKuai8Type = OnMouseMove_FangKuai8(point, false);
	m_bMoveInCtrlFangKuai8 = (m_nMoveFangKuai8Type != SCT_NONE);
	if (m_bMoveInCtrlFangKuai8)
	{
		this->RedrawWindow();
		return;
	}

	m_nMoveFangKuai8Type = OnMouseMove_FangKuai8(point, true);
	m_bMoveInWndFangKuai8 = (m_nMoveFangKuai8Type != SCT_NONE);
	if (m_bMoveInWndFangKuai8)
	{
		this->RedrawWindow();
		return;
	}

	this->RedrawWindow();
	SetViewCursor(UF_IDC_ARROW);
}

void CUiFeatureBuilderView::OnMouseMove_LButtonDown(CPoint point)
{
	// �����Ҫ����һ���¿ؼ�
	if (m_bCreateNewCtrl)
	{
		// ���ƴ����¿ؼ�ʱ�ľ���
	}
	else if (m_bMoveInWndFangKuai8 && m_nMoveFangKuai8Type != SCT_NONE)
	{
		// �϶�����
	}
	else if (m_bMoveInCtrlFangKuai8 && m_nMoveFangKuai8Type != SCT_NONE)
	{
		// �϶��ؼ����ı�ؼ���С
		IControlBase* pLBtnDownCtrl = m_pCurrentWnd->BD_GetFocusControl();
		if (pLBtnDownCtrl == NULL)
			return;

		// �ؼ��Ƿ�����
		if (pLBtnDownCtrl->GetLockControl())
			return;

		// ����ȫ���Ĳ������޸Ĵ�С
		CONTROL_LAYOUT_INFO Layout = pLBtnDownCtrl->GetLayout();
		if (Layout.clType == CL_L_ALL)
			return;

		OnMouseMove_LButtonDown_SizeCtrl(m_nMoveFangKuai8Type, point, pLBtnDownCtrl);
	}
	else if (m_pCurrentWnd != NULL && m_pCurrentWnd->BD_GetFocusControl() != NULL)
	{
		// �ƶ��ؼ�
		m_bSizeMoveCtrl = true;
		SetViewCursor(UF_IDC_SIZEALL);

		// �϶��ؼ����ı�ؼ���С
		IControlBase* pLBtnDownCtrl = m_pCurrentWnd->BD_GetFocusControl();
		if (pLBtnDownCtrl == NULL)
			return;

		// �ؼ��Ƿ�����
		if (pLBtnDownCtrl->GetLockControl())
			return;

		// ����ȫ���Ĳ������޸Ĵ�С
		CONTROL_LAYOUT_INFO Layout = pLBtnDownCtrl->GetLayout();
		if (Layout.clType == CL_L_ALL)
			return;

		m_pDrawParentCtrl = pLBtnDownCtrl->GetParentControl();
		OnMouseMove_LButtonDown_MoveCtrl(point, pLBtnDownCtrl);
	}
	else
	{
		SetViewCursor(UF_IDC_ARROW);
	}
}

void CUiFeatureBuilderView::OnMouseMove_LButtonDown_SizeCtrl(SIZE_CTRL_TYPE nFangKuai8Type, CPoint point, IControlBase* pLBtnDownCtrl)
{
	if (nFangKuai8Type == SCT_NONE || pLBtnDownCtrl == NULL || m_pCurrentWnd == NULL)
		return;

	point.x += m_ScrollOffset.cx;
	point.y += m_ScrollOffset.cy;

//////////////////////////////////////////////////////////////////////////
	// ������builder�е�������
	FANGKUAI_8* pParentFk8 = m_pCurrentWnd->BD_GetFangKuai8Rect();
	if (pLBtnDownCtrl->GetParentControl() != NULL)
		pParentFk8 = pLBtnDownCtrl->GetParentControl()->BD_GetFangKuai8Rect();

	FANGKUAI_8* pFk8 = pLBtnDownCtrl->BD_GetFangKuai8Rect();
	if (pParentFk8 == NULL || pFk8 == NULL)
		return;

	if (nFangKuai8Type == SCT_LEFT_TOP)
	{
		pFk8->EntityRct.left = point.x;
		pFk8->EntityRct.top = point.y;

		// Խ���ж�
		if (pFk8->EntityRct.left > pFk8->EntityRct.right)
			pFk8->EntityRct.left = pFk8->EntityRct.right;
		if (pFk8->EntityRct.top > pFk8->EntityRct.bottom)
			pFk8->EntityRct.top = pFk8->EntityRct.bottom;
	}
	else if (nFangKuai8Type == SCT_LEFT_MID)
	{
		pFk8->EntityRct.left = point.x;

		// Խ���ж�
		if (pFk8->EntityRct.left > pFk8->EntityRct.right)
			pFk8->EntityRct.left = pFk8->EntityRct.right;
	}
	else if (nFangKuai8Type == SCT_LEFT_BOTTOM)
	{
		pFk8->EntityRct.left = point.x;
		pFk8->EntityRct.bottom = point.y;

		// Խ���ж�
		if (pFk8->EntityRct.left > pFk8->EntityRct.right)
			pFk8->EntityRct.left = pFk8->EntityRct.right;
		if (pFk8->EntityRct.bottom < pFk8->EntityRct.top)
			pFk8->EntityRct.bottom = pFk8->EntityRct.top;
	}
	else if (nFangKuai8Type == SCT_MID_TOP)
	{
		pFk8->EntityRct.top = point.y;

		// Խ���ж�
		if (pFk8->EntityRct.top > pFk8->EntityRct.bottom)
			pFk8->EntityRct.top = pFk8->EntityRct.bottom;
	}
	else if (nFangKuai8Type == SCT_MID_BOTTOM)
	{
		pFk8->EntityRct.bottom = point.y;

		// Խ���ж�
		if (pFk8->EntityRct.bottom < pFk8->EntityRct.top)
			pFk8->EntityRct.bottom = pFk8->EntityRct.top;
	}
	else if (nFangKuai8Type == SCT_RIGHT_TOP)
	{
		pFk8->EntityRct.right = point.x;
		pFk8->EntityRct.top = point.y;

		// Խ���ж�
		if (pFk8->EntityRct.right < pFk8->EntityRct.left)
			pFk8->EntityRct.right = pFk8->EntityRct.left;
		if (pFk8->EntityRct.top > pFk8->EntityRct.bottom)
			pFk8->EntityRct.top = pFk8->EntityRct.bottom;
	}
	else if (nFangKuai8Type == SCT_RIGHT_MID)
	{
		pFk8->EntityRct.right = point.x;

		// Խ���ж�
		if (pFk8->EntityRct.right < pFk8->EntityRct.left)
			pFk8->EntityRct.right = pFk8->EntityRct.left;
	}
	else if (nFangKuai8Type == SCT_RIGHT_BOTTOM)
	{
		pFk8->EntityRct.right = point.x;
		pFk8->EntityRct.bottom = point.y;

		// Խ���ж�
		if (pFk8->EntityRct.right < pFk8->EntityRct.left)
			pFk8->EntityRct.right = pFk8->EntityRct.left;
		if (pFk8->EntityRct.bottom < pFk8->EntityRct.top)
			pFk8->EntityRct.bottom = pFk8->EntityRct.top;
	}

	if (pFk8->EntityRct.left < pParentFk8->EntityRct.left)
		pFk8->EntityRct.left = pParentFk8->EntityRct.left;
	if (pFk8->EntityRct.right > pParentFk8->EntityRct.right)
		pFk8->EntityRct.right = pParentFk8->EntityRct.right;
	if (pFk8->EntityRct.top < pParentFk8->EntityRct.top)
		pFk8->EntityRct.top = pParentFk8->EntityRct.top;
	if (pFk8->EntityRct.bottom > pParentFk8->EntityRct.bottom)
		pFk8->EntityRct.bottom = pParentFk8->EntityRct.bottom;

//////////////////////////////////////////////////////////////////////////
	// ������Window�е�������
	RECT CtrlInWndRct;
	INIT_RECT(CtrlInWndRct);
	FANGKUAI_8* pWndFk8 = m_pCurrentWnd->BD_GetFangKuai8Rect();
	CtrlInWndRct.left = pFk8->EntityRct.left - pWndFk8->EntityRct.left;
	CtrlInWndRct.right = CtrlInWndRct.left + RECT_WIDTH(pFk8->EntityRct);
	CtrlInWndRct.top = pFk8->EntityRct.top - pWndFk8->EntityRct.top;
	CtrlInWndRct.bottom = CtrlInWndRct.top + RECT_HEIGHT(pFk8->EntityRct);
	pLBtnDownCtrl->MoveWindowRect(CtrlInWndRct);

	// ���¼����ӿؼ���λ�úʹ�С
	m_pCurrentWnd->ResetChildCtrlPostion(pLBtnDownCtrl->GetChildControlsVec(), true);
	m_pCurrentWnd->BD_SetControlRectInView(pLBtnDownCtrl->GetChildControlsVec());

	// ˢ����������
	m_pPropViewCtrl->RefreshLayoutData();
}

void CUiFeatureBuilderView::OnMouseMove_LButtonDown_MoveCtrl(CPoint point, IControlBase* pLBtnDownCtrl)
{
	if (pLBtnDownCtrl == NULL || m_pCurrentWnd == NULL)
		return;

//////////////////////////////////////////////////////////////////////////
	// ������builder�е�������
	FANGKUAI_8* pParentFk8 = m_pCurrentWnd->BD_GetFangKuai8Rect();
	if (pLBtnDownCtrl->GetParentControl() != NULL)
		pParentFk8 = pLBtnDownCtrl->GetParentControl()->BD_GetFangKuai8Rect();

	FANGKUAI_8* pFk8 = pLBtnDownCtrl->BD_GetFangKuai8Rect();
	if (pParentFk8 == NULL || pFk8 == NULL)
		return;

	RECT NewRect;
	INIT_RECT(NewRect);
	NewRect.left = point.x - RECT_WIDTH(pFk8->EntityRct) / 2 + m_ScrollOffset.cx;
	if (NewRect.left < pParentFk8->EntityRct.left)
		NewRect.left = pParentFk8->EntityRct.left;
	if ((NewRect.left + RECT_WIDTH(pFk8->EntityRct)) > pParentFk8->EntityRct.right)
		NewRect.left = pParentFk8->EntityRct.right - RECT_WIDTH(pFk8->EntityRct);

	NewRect.right = NewRect.left + RECT_WIDTH(pFk8->EntityRct);

	NewRect.top = point.y - RECT_HEIGHT(pFk8->EntityRct) / 2 + m_ScrollOffset.cy;
	if (NewRect.top < pParentFk8->EntityRct.top)
		NewRect.top = pParentFk8->EntityRct.top;
	if ((NewRect.top + RECT_HEIGHT(pFk8->EntityRct)) > pParentFk8->EntityRct.bottom)
		NewRect.top = pParentFk8->EntityRct.bottom - RECT_HEIGHT(pFk8->EntityRct);
	
	NewRect.bottom = NewRect.top + RECT_HEIGHT(pFk8->EntityRct);

	pFk8->EntityRct = NewRect;

//////////////////////////////////////////////////////////////////////////
	// ������Window�е�������
	RECT CtrlInWndRct;
	INIT_RECT(CtrlInWndRct);
	FANGKUAI_8* pWndFk8 = m_pCurrentWnd->BD_GetFangKuai8Rect();
	CtrlInWndRct.left = pFk8->EntityRct.left - pWndFk8->EntityRct.left;
	CtrlInWndRct.right = CtrlInWndRct.left + RECT_WIDTH(pFk8->EntityRct);
	CtrlInWndRct.top = pFk8->EntityRct.top - pWndFk8->EntityRct.top;
	CtrlInWndRct.bottom = CtrlInWndRct.top + RECT_HEIGHT(pFk8->EntityRct);
	pLBtnDownCtrl->MoveWindowRect(CtrlInWndRct);

	// ���¼����ӿؼ���λ�úʹ�С
	m_pCurrentWnd->ResetChildCtrlPostion(pLBtnDownCtrl->GetChildControlsVec(), true);
	m_pCurrentWnd->BD_SetControlRectInView(pLBtnDownCtrl->GetChildControlsVec());

	// ˢ����������
	m_pPropViewCtrl->RefreshLayoutData();
}

SIZE_CTRL_TYPE CUiFeatureBuilderView::OnMouseMove_FangKuai8(CPoint point, bool bIsWnd)
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
		if (m_pCurrentWnd != NULL && m_pCurrentWnd->BD_GetFocusControl() != NULL)
		{
			pFk8 = m_pCurrentWnd->BD_GetFocusControl()->BD_GetFangKuai8Rect();
		}
	}

	if (pFk8 == NULL)
		return SCT_NONE;

	if (PtInRect(&pFk8->LeftTop, point))
	{
		SetViewCursor(UF_IDC_SIZENWSE);
		return SCT_LEFT_TOP;
	}
	else if (PtInRect(&pFk8->LeftMid, point))
	{
		SetViewCursor(UF_IDC_SIZEWE);
		return SCT_LEFT_MID;
	}
	else if (PtInRect(&pFk8->LeftBottom, point))
	{
		SetViewCursor(UF_IDC_SIZENESW);
		return SCT_LEFT_BOTTOM;
	}
	else if (PtInRect(&pFk8->MidTop, point))
	{
		SetViewCursor(UF_IDC_SIZENS);
		return SCT_MID_TOP;
	}
	else if (PtInRect(&pFk8->MidBottom, point))
	{
		SetViewCursor(UF_IDC_SIZENS);
		return SCT_MID_BOTTOM;
	}
	else if (PtInRect(&pFk8->RightTop, point))
	{
		SetViewCursor(UF_IDC_SIZENESW);
		return SCT_RIGHT_TOP;
	}
	else if (PtInRect(&pFk8->RightMid, point))
	{
		SetViewCursor(UF_IDC_SIZEWE);
		return SCT_RIGHT_MID;
	}
	else if (PtInRect(&pFk8->RightBottom, point))
	{
		SetViewCursor(UF_IDC_SIZENWSE);
		return SCT_RIGHT_BOTTOM;
	}

	return SCT_NONE;
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

	::ReleaseCapture();

	SetViewCursor(UF_IDC_ARROW);
	m_LBtnUpPos = point;
	m_bIsLButtonDown = false;
	m_pDrawParentCtrl = NULL;
	m_bSizeMoveCtrl = false;

	if (!m_bInitOk)
		return;

	// �����Ҫ����һ���¿ؼ�
	if (m_bCreateNewCtrl)
	{
		CreateNewControl();
		m_pDrawParentCtrl = NULL;
		m_bCreateNewCtrl = false;
		//this->RedrawWindow();
		return;
	}
}

void CUiFeatureBuilderView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CFormView::OnLButtonDown(nFlags, point);

	if (!m_bInitOk)
		return;

	::SetCapture(m_hWnd);

	m_LBtnDownPos = point;
	m_bIsLButtonDown = true;
	m_pDrawParentCtrl = NULL;

	if (m_pSkinManager == NULL || m_pUiKernel == NULL || m_pCurrentWnd == NULL)
		return;

	FANGKUAI_8* pFk8 = m_pCurrentWnd->BD_GetFangKuai8Rect();
	if (pFk8 == NULL)
		return;

	// �����Ҫ����һ���¿ؼ�
	if (m_bCreateNewCtrl)
	{
		m_bCreateNewCtrl = PtInWindow(point);
		if (m_bCreateNewCtrl)
		{
			// ȡ��ѡ�еĸ��ؼ�
			m_pDrawParentCtrl = GetSelectControl(point);
			this->RedrawWindow();
		}
		else
		{
			SetViewCursor(UF_IDC_ARROW);
		}
		return;
	}

	if (m_bMoveInCtrlFangKuai8)
	{
		if (m_pCurrentWnd->BD_GetFocusControl() != NULL)
			m_pDrawParentCtrl = m_pCurrentWnd->BD_GetFocusControl()->GetParentControl();
	}
	else
	{
		IControlBase *pSelCtrl = GetSelectControl(point);
		if (m_pCurrentWnd->BD_GetFocusControl() != pSelCtrl)
		{
			m_pCurrentWnd->BD_SetFocusControl(pSelCtrl);

			if (m_pPropViewCtrl != NULL && m_pCurrentWnd->BD_GetFocusControl() != NULL)
			{
				m_pPropViewCtrl->SetShowPropGroup(m_pCurrentWnd->BD_GetFocusControl()->PP_GetControlPropetryGroup());
				m_pWindowViewTree->SetViewEditControl(m_pCurrentWnd->BD_GetFocusControl());
			}
		}
	}

	this->RedrawWindow();
}

bool CUiFeatureBuilderView::PtInWindow(CPoint point)
{
	if (m_pCurrentWnd == NULL)
		return false;

	FANGKUAI_8* pFk8 = m_pCurrentWnd->BD_GetFangKuai8Rect();
	if (pFk8 == NULL)
		return false;

	point.x += m_ScrollOffset.cx;
	point.y += m_ScrollOffset.cy;

	if (::PtInRect(&(pFk8->EntityRct), point))
		return true;

	return false;
}

// ȡ��ѡ��Ŀؼ�
IControlBase* CUiFeatureBuilderView::GetSelectControl(CPoint point)
{
	if (m_pCurrentWnd == NULL)
		return NULL;

	point.x += m_ScrollOffset.cx;
	point.y += m_ScrollOffset.cy;

	return m_pCurrentWnd->BD_GetMouseInControl(point);
}

void CUiFeatureBuilderView::CreateNewControl()
{
	USES_CONVERSION;
	// �����¿ؼ�
	if (m_pControlList == NULL || m_pUiKernel == NULL || m_pCurrentWnd == NULL)
		return;

	m_pDrawParentCtrl = GetSelectControl(m_LBtnDownPos);
	CString strCtrlTypeName = m_pControlList->GetSelectCtrlTypeName();
	IControlBase *pControl = m_pUiKernel->BD_CreateControlEmptyPropetry(m_pCurrentWnd, m_pDrawParentCtrl, W2A(strCtrlTypeName));
	if (pControl == NULL)
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("�����ؼ���%s��ʧ�ܣ�"), strCtrlTypeName);
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return;
	}
	m_pCurrentWnd->BD_SetFocusControl(pControl);

	// �����¿ؼ���λ�úʹ�С
	CreateNewControlf_SetNewCtrlRect();

	// ���»���WindowTree
	if (m_pWindowViewTree != NULL)
	{
		m_pWindowViewTree->AddNewControlToWindowTreeNode(m_pCurrentWnd, m_pDrawParentCtrl, m_pCurrentWnd->BD_GetFocusControl());
	}
	
	// ����������ͼ
}

// �����¿ؼ��Ĵ�С
void CUiFeatureBuilderView::CreateNewControlf_SetNewCtrlRect()
{
	if (m_pCurrentWnd->BD_GetFocusControl() == NULL)
		return;

	FANGKUAI_8* pFk8 = NULL;
	// �Ȼ��Ʊ�ѡ�еĸ��ؼ�������
	if (m_pDrawParentCtrl != NULL)
		pFk8 = m_pDrawParentCtrl->BD_GetFangKuai8Rect();
	else
		pFk8 = m_pCurrentWnd->BD_GetFangKuai8Rect();

	if (pFk8 == NULL)
		return;

	RECT EntityRct;
	INIT_RECT(EntityRct);
	EntityRct.left = ((m_LBtnDownPos.x  <= m_LBtnUpPos.x) ? m_LBtnDownPos.x : m_LBtnUpPos.x) + m_ScrollOffset.cx;
	EntityRct.right = ((m_LBtnUpPos.x  >= m_LBtnDownPos.x) ? m_LBtnUpPos.x : m_LBtnDownPos.x) + m_ScrollOffset.cx;
	EntityRct.top = ((m_LBtnDownPos.y  <= m_LBtnUpPos.y) ? m_LBtnDownPos.y : m_LBtnUpPos.y) + m_ScrollOffset.cy;
	EntityRct.bottom = ((m_LBtnUpPos.y  >= m_LBtnDownPos.y) ? m_LBtnUpPos.y : m_LBtnDownPos.y) + m_ScrollOffset.cy;

	if (EntityRct.left < pFk8->EntityRct.left)
		EntityRct.left = pFk8->EntityRct.left;

	if (EntityRct.right > pFk8->EntityRct.right)
		EntityRct.right = pFk8->EntityRct.right;

	if (EntityRct.top < pFk8->EntityRct.top)
		EntityRct.top = pFk8->EntityRct.top;

	if (EntityRct.bottom > pFk8->EntityRct.bottom)
		EntityRct.bottom = pFk8->EntityRct.bottom;
	
	m_pCurrentWnd->BD_SetControlRect(m_pCurrentWnd->BD_GetFocusControl(), EntityRct);
}

void CUiFeatureBuilderView::SetNeedSave()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
		pMain->SetPropetryChange();
}

void CUiFeatureBuilderView::OnTimer(UINT_PTR nIDEvent)
{
	CFormView::OnTimer(nIDEvent);

	if (!m_bInitOk || m_pCurrentWnd == NULL)
		return;

	m_pCurrentWnd->BD_OnTimer(nIDEvent, m_hWnd);
}
