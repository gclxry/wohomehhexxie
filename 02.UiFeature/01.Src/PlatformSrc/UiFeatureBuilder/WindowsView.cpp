
#include "stdafx.h"
#include "MainFrm.h"
#include "WindowsView.h"
#include "Resource.h"
#include "UiFeatureBuilder.h"

//////////////////////////////////////////////////////////////////////
// 构造/析构
//////////////////////////////////////////////////////////////////////

CWindowsView::CWindowsView()
{
	m_hRoot = NULL;
}

CWindowsView::~CWindowsView()
{
}

BEGIN_MESSAGE_MAP(CWindowsView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_UPDATE_COMMAND_UI(IDM_CONTROY_TO_DOWN, &CWindowsView::OnUpdateControyToDown)
	ON_COMMAND(IDM_CONTROY_TO_DOWN, &CWindowsView::OnControyToDown)
	ON_COMMAND(IDM_CONTROY_TO_UP, &CWindowsView::OnControyToUp)
	ON_UPDATE_COMMAND_UI(IDM_CONTROY_TO_UP, &CWindowsView::OnUpdateControyToUp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowsView 消息处理程序

int CWindowsView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if (!m_wndWindowTree.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("未能创建Dui窗口视图\n");
		return -1;      // 未能创建
	}

	OnChangeVisualStyle();

	m_wndWindowTree.ModifyStyle(0, TVS_SHOWSELALWAYS);

//////////////////////////////////////////////////////////////////////////
	// Load images:
	m_TreeToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDT_WINDOW_VIEW_UP_DOWN);
	m_TreeToolBar.LoadToolBar(IDT_WINDOW_VIEW_UP_DOWN, 0, 0, TRUE /* Is locked */);

	m_TreeToolBar.SetPaneStyle(m_TreeToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_TreeToolBar.SetPaneStyle(m_TreeToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_TreeToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_TreeToolBar.SetRouteCommandsViaFrame(FALSE);

	return 0;
}

void CWindowsView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CWindowsView::SetProjectInitState(bool bInitOk)
{
	m_wndWindowTree.SetProjectInitState(bInitOk);
}

void CWindowsView::Init(IUiFeatureKernel* pKernelWindow, CPropertyViewCtrl *pPropCtrl)
{
	m_wndWindowTree.Init(pKernelWindow, pPropCtrl);
}

CWindowsViewTree* CWindowsView::GetViewTreeCtrl()
{
	return &m_wndWindowTree;
}

void CWindowsView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndWindowTree;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CWindowsView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
		return;

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_TreeToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_TreeToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndWindowTree.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CWindowsView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CWindowsView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndWindowTree.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CWindowsView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndWindowTree.SetFocus();
}

void CWindowsView::OnChangeVisualStyle()
{
	m_WindowViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_WindowViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_WindowViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndWindowTree.SetImageList(&m_WindowViewImages, TVSIL_NORMAL);

	m_TreeToolBar.CleanUpLockedImages();
	m_TreeToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDT_WINDOW_VIEW_UP_DOWN, 0, 0, TRUE /* Locked */);
}

void CWindowsView::InitShowNewProject()
{
	m_wndWindowTree.InitShowNewProject();
}

void CWindowsView::OnUpdateControyToDown(CCmdUI *pCmdUI)
{
	m_wndWindowTree.OnUpdateControyToDown(pCmdUI);
}

void CWindowsView::OnUpdateControyToUp(CCmdUI *pCmdUI)
{
	m_wndWindowTree.OnUpdateControyToUp(pCmdUI);
}

void CWindowsView::OnControyToDown()
{
	m_wndWindowTree.OnControyToDown();
}

void CWindowsView::OnControyToUp()
{
	m_wndWindowTree.OnControyToUp();
}
