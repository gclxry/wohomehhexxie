
#include "stdafx.h"
#include "WindowsViewTree.h"
#include "resource.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IFeatureObject.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\ICommonFun.h"
#include "UiFeatureBuilderDoc.h"
#include "UiFeatureBuilderView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DRAG_DELAY								(60)
/////////////////////////////////////////////////////////////////////////////
// CWindowsViewTree

CWindowsViewTree::CWindowsViewTree()
{
	m_pSkinMgr = NULL;
	m_pUiKernel = NULL;
	m_pPropCtrl = NULL;
	m_pWindowView = NULL;
	m_bProjectInitOk = false;
	m_hRBtnSelItem = NULL;
	m_bFromViewSel = false;

	m_TimerTicks = 0;
	m_nScrollTimerID = 0;
	m_HoverPoint.x = m_HoverPoint.y = 0;
	m_nHoverTimerID = 0;
	m_dwDragStart = 0;
	m_hItemDragS = NULL;
	m_hItemDragD = NULL;
	m_pDragImage = NULL;
	m_bDragging = false;
}

CWindowsViewTree::~CWindowsViewTree()
{
	SAFE_DELETE(m_pDragImage);
}

BEGIN_MESSAGE_MAP(CWindowsViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CWindowsViewTree::OnNMRClick)
	ON_COMMAND(ID_CREATE_WINDOW_PANEL, &CWindowsViewTree::OnCreateWindowPanel)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CWindowsViewTree::OnTvnSelchanged)
	ON_COMMAND(IDM_DELETE_WNDCTRL, &CWindowsViewTree::OnDeleteWndctrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &CWindowsViewTree::OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowsViewTree 消息处理程序

BOOL CWindowsViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

void CWindowsViewTree::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_hRBtnSelItem = NULL;
	if (!m_bProjectInitOk)
		return;

	m_hRBtnSelItem = this->GetSelectedItem();
	if (!IS_SAFE_HANDLE(m_hRBtnSelItem))
		return;

	POINT pt;
	::GetCursorPos(&pt);
	CMenu CreateMenu;

	HTREEITEM hRootItem = this->GetRootItem();
	if (hRootItem == m_hRBtnSelItem)
	{
		CreateMenu.LoadMenu(IDM_CREATE_WINDOW);
		CreateMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}
	else
	{
		CreateMenu.LoadMenu(IDR_DELETE_WND_OR_CTRL);
		CreateMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}

	*pResult = 0;
}

void CWindowsViewTree::SetProjectInitState(bool bInitOk)
{
	m_bProjectInitOk = bInitOk;

	this->DeleteAllItems();
	if (m_bProjectInitOk)
	{
		HTREEITEM hRootItem = this->InsertItem(_T("【窗口/面板】"), 1, 1);
		this->SetItemState(hRootItem, TVIS_BOLD, TVIS_BOLD);
		this->RedrawWindow();
	}
}

void CWindowsViewTree::SetBuilderView(CUiFeatureBuilderView* pWndView)
{
	if (pWndView == NULL)
		return;

	m_pWindowView = pWndView;
}

void CWindowsViewTree::Init(IUiFeatureKernel* pKernelWindow, CPropertyViewCtrl *pPropCtrl)
{
	if (pKernelWindow == NULL || pPropCtrl == NULL)
		return;

	m_pUiKernel = pKernelWindow;
	m_pSkinMgr = m_pUiKernel->GetSkinManager();
	m_pPropCtrl = pPropCtrl;

	this->DeleteAllItems();
}

void CWindowsViewTree::OnCreateWindowPanel()
{
	if (!m_bProjectInitOk || m_pSkinMgr == NULL || m_pUiKernel == NULL || m_pPropCtrl == NULL)
	{
		AfxMessageBox(_T("列表没有被初始化"), MB_OK | MB_ICONERROR);
		return;
	}

	SetNeedSave();
	HTREEITEM hRootItem = this->GetRootItem();
	HTREEITEM hWindow = this->InsertItem(_T("新建窗口/面板"), 0, 0, hRootItem, TVI_LAST);
	this->Expand(hRootItem, TVE_EXPAND);
	if (hWindow == NULL)
	{
		AfxMessageBox(_T("新建窗口/面板错误！"), MB_OK | MB_ICONERROR);
		return;
	}
	
	IWindowBase *pWndBase = m_pUiKernel->BD_CreateWindowEmptyPropetry();
	if (pWndBase == NULL)
	{
		AfxMessageBox(_T("新建窗口/面板时，创建绘制窗体错误！"), MB_OK | MB_ICONERROR);
		return;
	}

	this->SetItemData(hWindow, (DWORD_PTR)pWndBase);
	this->SelectItem(hWindow);
}

void CWindowsViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
	{
		if (this->GetSelectedItem() == NULL)
			pMain->SetRunTestToolbarState(false);
		else
			pMain->SetRunTestToolbarState(this->GetRootItem() != this->GetSelectedItem());
	}

	*pResult = 0;
	if (!m_bProjectInitOk)
		return;

	if (m_bFromViewSel)
	{
		m_bFromViewSel = false;
		return;
	}

	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hItem = this->GetSelectedItem();
	if (!IS_SAFE_HANDLE(hItem))
		return;

	HTREEITEM hRootItem = this->GetRootItem();
	if (hRootItem == hItem)
	{
		// 选择了根
		OnTvnSelchanged_SelectRoot();
		return;
	}

	IFeatureObject *pObj = (IFeatureObject*)this->GetItemData(hItem);
	if (pObj == NULL)
		return;

	if (lstrcmpA(pObj->GetObjectType(), PROP_TYPE_WINDOW_NAME) == 0)
	{
		IWindowBase *pWndBase = dynamic_cast<IWindowBase*>(pObj);
		OnTvnSelchanged_SelectWindow(pWndBase);
	}
	else
	{
		// 选择了控件
		IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(pObj);
		OnTvnSelchanged_SelectControl(pCtrlBase);
	}
}

void CWindowsViewTree::OnTvnSelchanged_SelectRoot()
{
	if (m_pPropCtrl != NULL)
		m_pPropCtrl->ClearAll();

	if (m_pWindowView != NULL)
		m_pWindowView->ResetShowWindow(NULL, NULL);
}

void CWindowsViewTree::OnTvnSelchanged_SelectWindow(IWindowBase *pWndBase)
{
	if (m_pWindowView == NULL || m_pPropCtrl == NULL || pWndBase == NULL)
	{
		OnTvnSelchanged_SelectRoot();
		return;
	}

	IPropertyGroup* pPropGroup = pWndBase->PP_GetWindowPropetryGroup();
	if (pPropGroup == NULL)
	{
		OnTvnSelchanged_SelectRoot();
		return;
	}

	m_pPropCtrl->SetShowPropGroup(pPropGroup);
	m_pWindowView->ResetShowWindow(pWndBase, NULL);
}

void CWindowsViewTree::OnTvnSelchanged_SelectControl(IControlBase *pCtrlBase)
{
	if (m_pWindowView == NULL || m_pPropCtrl == NULL || pCtrlBase == NULL)
	{
		OnTvnSelchanged_SelectRoot();
		return;
	}

	IPropertyGroup* pPropGroup = pCtrlBase->PP_GetControlPropetryGroup();
	if (pPropGroup == NULL)
	{
		OnTvnSelchanged_SelectRoot();
		return;
	}

	m_pPropCtrl->SetShowPropGroup(pPropGroup);
	m_pWindowView->ResetShowWindow(pCtrlBase->GetOwnerWindow(), pCtrlBase);
}

void CWindowsViewTree::RefreshObjectName()
{
	HTREEITEM hRootItem = this->GetRootItem();
	RefreshItemObjectName(hRootItem);
}

void CWindowsViewTree::RefreshItemObjectName(HTREEITEM hParentItem)
{
	USES_CONVERSION;
	if (hParentItem == NULL)
		return;

	HTREEITEM hChild = this->GetChildItem(hParentItem);
	while (hChild != NULL)
	{
		IFeatureObject *pPropBase = (IFeatureObject*)this->GetItemData(hChild);
		if (pPropBase != NULL)
		{
			// 刷新操作，目前只有刷新名字
			if (pPropBase->GetObjectTypeId() == OTID_WINDOW)
			{
				// 窗口
				IWindowBase* pWnd = dynamic_cast<IWindowBase*>(pPropBase);
				if (pWnd != NULL && pWnd->PP_GetWindowObjectName() != NULL)
				{
					this->SetItemText(hChild, A2W(pWnd->PP_GetWindowObjectName()));
					pWnd->SetObjectName(pWnd->PP_GetWindowObjectName());
					if (pWnd->PP_GetWindowPropetry() != NULL)
						pWnd->PP_GetWindowPropetry()->SetObjectName(pWnd->PP_GetWindowObjectName());
				}
			}
			else
			{
				// 控件
				IControlBase* pCtrl = dynamic_cast<IControlBase*>(pPropBase);
				if (pCtrl != NULL && pCtrl->PP_GetControlObjectName() != NULL)
				{
					CString strName(_T(""));
					strName.Format(_T("%s[%s]"), A2W(pCtrl->PP_GetControlObjectName()), A2W(pCtrl->GetObjectType()));
					this->SetItemText(hChild, strName);
					pCtrl->SetObjectName(pCtrl->PP_GetControlObjectName());
					if (pCtrl->PP_GetControlPropetry() != NULL)
						pCtrl->PP_GetControlPropetry()->SetObjectName(pCtrl->PP_GetControlObjectName());
				}
			}
		}

		// 更新子控件的名称
		RefreshItemObjectName(hChild);

		hChild = this->GetNextItem(hChild, TVGN_NEXT);
	}
}

void CWindowsViewTree::InitShowNewProject()
{
	USES_CONVERSION;
	this->DeleteAllItems();
	HTREEITEM hRootItem = this->InsertItem(_T("【窗口/面板】"), 1, 1);
	this->SetItemState(hRootItem, TVIS_BOLD, TVIS_BOLD);

	if (m_pSkinMgr == NULL || m_pUiKernel == NULL)
		return;

	ONE_RESOURCE_PROP_MAP* pWndPropMap = m_pSkinMgr->BD_GetWindowPropMap();
	if (pWndPropMap == NULL)
		return;

	for (ONE_RESOURCE_PROP_MAP::iterator pWndItem = pWndPropMap->begin(); pWndItem != pWndPropMap->end(); pWndItem++)
	{
		IPropertyWindow* pPropWnd = dynamic_cast<IPropertyWindow*>(pWndItem->second);
		if (pPropWnd == NULL)
			continue;

		IWindowBase* pWndBase = m_pUiKernel->BD_CreateWindowByPropetry(pPropWnd);
		if (pWndBase == NULL)
			continue;

		HTREEITEM hWindowItem = this->InsertItem(A2W(pWndBase->GetObjectName()), 0, 0, hRootItem, TVI_LAST);
		if (hWindowItem == NULL)
			continue;

		this->SetItemData(hWindowItem, (DWORD_PTR)pWndBase);

		// 子控件显示
		InsertCtrlVecByPropCtrlVec(hWindowItem, pWndBase, NULL, pWndBase->GetChildPropControlVec(), pWndBase->GetChildControlsVec());
	}

	// 选中并打开根节点
	this->SelectItem(hRootItem);
	this->Expand(hRootItem, TVE_EXPAND);
}

// 向树中插入一个新节点
void CWindowsViewTree::InsertCtrlVecByPropCtrlVec(HTREEITEM hParentItem, IWindowBase *pParentWnd, IControlBase *pParentCtrl, PROP_CONTROL_VEC* pPropCtrlVec, CHILD_CTRLS_VEC* pCtrlVec)
{
	if (hParentItem == NULL || pCtrlVec == NULL || m_pUiKernel == NULL)
		return;

	for (PROP_CONTROL_VEC::iterator pCtrlItem = pPropCtrlVec->begin(); pCtrlItem != pPropCtrlVec->end(); pCtrlItem++)
	{
		IPropertyControl* pPropCtrl = *pCtrlItem;
		if (pPropCtrl == NULL)
			continue;

		IControlBase *pNewCtrl = m_pUiKernel->CreateControlByPropetry(pParentWnd, pParentCtrl, pPropCtrl);
		if (pNewCtrl == NULL)
			return;

		HTREEITEM hItem = InsertControlNodeToEnd(hParentItem, pNewCtrl);
		if (hItem == NULL)
			continue;

		InsertCtrlVecByPropCtrlVec(hItem, pParentWnd, pNewCtrl, pPropCtrl->GetChildPropControlVec(), pNewCtrl->GetChildControlsVec());
	}
}

// 查找指定的控件
HTREEITEM CWindowsViewTree::FindControlTreeNode(HTREEITEM hParentNode, IControlBase* pCtrl)
{
	if (hParentNode == NULL || pCtrl == NULL)
		return NULL;

	HTREEITEM hChildNode = this->GetChildItem(hParentNode);
	while (hChildNode != NULL)
	{
		IControlBase *pCtrlBase = (IControlBase*)this->GetItemData(hChildNode);
		if (pCtrlBase == pCtrl)
			return hChildNode;

		HTREEITEM hFind = FindControlTreeNode(hChildNode, pCtrl);
		if (hFind != NULL)
			return hFind;

		hChildNode = this->GetNextItem(hChildNode, TVGN_NEXT);
	}

	return NULL;
}

// 向树中插入一个新节点
void CWindowsViewTree::AddNewControlToWindowTreeNode(IWindowBase *pWindow, IControlBase* pParentCtrl, IControlBase *pControl)
{
	if (pWindow == NULL || pControl == NULL)
		return;

	HTREEITEM hRootItem = this->GetRootItem();
	if (hRootItem == NULL)
		return;

	HTREEITEM hWindowNode = this->GetChildItem(hRootItem);
	while (hWindowNode != NULL)
	{
		IWindowBase *pWndBase = (IWindowBase*)this->GetItemData(hWindowNode);
		if (pWndBase == pWindow)
		{
			HTREEITEM hNewItem = NULL;
			if (pParentCtrl == NULL)
			{
				hNewItem = InsertControlNodeToEnd(hWindowNode, pControl);
				this->Expand(hWindowNode, TVE_EXPAND);
			}
			else
			{
				HTREEITEM hFind = FindControlTreeNode(hWindowNode, pParentCtrl);
				if (hFind == NULL)
					return;

				hNewItem  = InsertControlNodeToEnd(hFind, pControl);
				this->Expand(hFind, TVE_EXPAND);
			}

			// 选中并打开根节点
			this->SelectItem(hNewItem);
			this->RedrawWindow();
			break;
		}

		hWindowNode = this->GetNextItem(hWindowNode, TVGN_NEXT);
	}
}

// 在指定节点的子节点末尾插入新节点
HTREEITEM CWindowsViewTree::InsertControlNodeToEnd(HTREEITEM hParentNode, IControlBase *pControl)
{
	USES_CONVERSION;
	if (hParentNode == NULL || pControl == NULL)
		return NULL;

	CString strName(_T(""));
	strName.Format(_T("%s[%s]"), A2W(pControl->GetObjectName()), A2W(pControl->GetObjectType()));
	HTREEITEM hItem = this->InsertItem(strName, 3, 3, hParentNode, TVI_LAST);
	if (hItem != NULL)
		this->SetItemData(hItem, (DWORD_PTR)pControl);

	return hItem;
}

// 设置可以保存的有效属性
void CWindowsViewTree::SetSaveWindowActivePropetry()
{
	HTREEITEM hRootItem = this->GetRootItem();
	if (hRootItem == NULL)
		return;

	HTREEITEM hWindowNode = this->GetChildItem(hRootItem);
	while (hWindowNode != NULL)
	{
		IWindowBase *pWndBase = (IWindowBase*)this->GetItemData(hWindowNode);
		if (pWndBase == NULL)
			continue;

		m_pUiKernel->BD_SetWindowPropetryActiveProp(pWndBase, true);

		hWindowNode = this->GetNextItem(hWindowNode, TVGN_NEXT);
	}
}

void CWindowsViewTree::OnDeleteWndctrl()
{
	USES_CONVERSION;
	if (!m_bProjectInitOk || m_pSkinMgr == NULL || m_pUiKernel == NULL || m_pPropCtrl == NULL)
	{
		AfxMessageBox(_T("列表没有被初始化"), MB_OK | MB_ICONERROR);
		return;
	}

	if (m_hRBtnSelItem == NULL)
	{
		AfxMessageBox(_T("没有选择需要删除的节点！"), MB_OK | MB_ICONERROR);
		return;
	}
	this->SelectItem(m_hRBtnSelItem);

	SetNeedSave();

	IFeatureObject* pObj = (IFeatureObject*)this->GetItemData(m_hRBtnSelItem);
	if (pObj->GetObjectTypeId() == OTID_WINDOW)
	{
		IWindowBase *pWndBase = dynamic_cast<IWindowBase*>(pObj);
		if (pWndBase == NULL)
		{
			AfxMessageBox(_T("错误的【Window】节点！"), MB_OK | MB_ICONERROR);
			return;
		}

		CString strInfo(_T(""));
		strInfo.Format(_T("确定删除窗口/面板【%s】吗？"), A2W(pWndBase->GetObjectName()));
		if (AfxMessageBox(strInfo, MB_OKCANCEL | MB_ICONWARNING) != IDOK)
			return;

		m_pUiKernel->BD_DeleteWindow(pWndBase);
	}
	else
	{
		IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(pObj);
		if (pCtrlBase == NULL)
		{
			AfxMessageBox(_T("错误的【Control】节点！"), MB_OK | MB_ICONERROR);
			return;
		}

		CString strInfo(_T(""));
		strInfo.Format(_T("确定删除控件【%s[%s]】吗？"), A2W(pCtrlBase->GetObjectName()), A2W(pCtrlBase->GetObjectType()));
		if (AfxMessageBox(strInfo, MB_OKCANCEL | MB_ICONWARNING) != IDOK)
			return;

		IWindowBase *pWnd = pCtrlBase->GetOwnerWindow();
		if (pWnd != NULL)
			pWnd->BD_SetFocusControl(NULL);

		m_pUiKernel->BD_DeleteControl(pCtrlBase);
	}

	HTREEITEM hItem = this->GetParentItem(m_hRBtnSelItem);
	this->DeleteItem(m_hRBtnSelItem);

	if (hItem == NULL)
		hItem = this->GetRootItem();

	if (hItem != NULL)
	{
		// 选中并打开根节点
		this->SelectItem(hItem);
		this->Expand(hItem, TVE_EXPAND);
	}
}

void CWindowsViewTree::SetNeedSave()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
		pMain->SetPropetryChange();
}

void CWindowsViewTree::SetViewEditControl(IControlBase *pCtrl)
{
	m_bFromViewSel = true;
	HTREEITEM hRootItem = this->GetRootItem();
	SetViewEditControl_Child(hRootItem, pCtrl);
}

void CWindowsViewTree::SetViewEditControl_Child(HTREEITEM hParentItem, IControlBase *pCtrl)
{
	USES_CONVERSION;
	if (hParentItem == NULL)
		return;

	HTREEITEM hChild = this->GetChildItem(hParentItem);
	while (hChild != NULL)
	{
		IFeatureObject *pPropBase = (IFeatureObject*)this->GetItemData(hChild);
		if (pPropBase != NULL && pPropBase->GetObjectTypeId() != OTID_WINDOW)
		{
			IControlBase* pComCtrl = dynamic_cast<IControlBase*>(pPropBase);
			if (pComCtrl == pCtrl)
			{
				// 选中并打开根节点
				this->SelectItem(hChild);
				this->Expand(hChild, TVE_EXPAND);
				return;
			}
		}

		// 更新子控件的名称
		SetViewEditControl_Child(hChild, pCtrl);
		hChild = this->GetNextItem(hChild, TVGN_NEXT);
	}
}

//////////////////////////////////////////////////////////////////////////
void CWindowsViewTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 处理无意拖曳
	m_dwDragStart = GetTickCount();
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CWindowsViewTree::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if (pNMTreeView == NULL)
		return;

	//如果是无意拖曳，则放弃操作
	if((GetTickCount() - m_dwDragStart) < DRAG_DELAY)
		return;

	m_hItemDragS = pNMTreeView->itemNew.hItem;
	m_hItemDragD = NULL;

	if (m_hItemDragS == NULL)
		return;

	//得到用于拖动时显示的图象列表
	m_pDragImage = CreateDragImage( m_hItemDragS );
	if (m_pDragImage == NULL)
		return;

	m_bDragging = true;

	m_pDragImage->BeginDrag(0, CPoint(8, 8));

	CPoint pt = pNMTreeView->ptDrag;
	this->ClientToScreen(&pt);
	// "this"将拖曳动作限制在该窗口
	m_pDragImage->DragEnter(this,pt);

	this->SetCapture();

	m_nScrollTimerID = this->SetTimer(2, 40, NULL);
}

void CWindowsViewTree::OnMouseMove(UINT nFlags, CPoint point)
{
	HTREEITEM  hItem = NULL;
	UINT       flags;

	//检测鼠标敏感定时器是否存在,如果存在则删除,删除后再定时
	if (m_nHoverTimerID != 0)
	{
		this->KillTimer(m_nHoverTimerID);
		m_nHoverTimerID = 0;
	}

	// 定时为 0.8 秒则自动展开
	m_nHoverTimerID = this->SetTimer(1, 800, NULL);
	m_HoverPoint = point;

	if (m_bDragging)
	{
		CPoint pt = point;
		CImageList::DragMove(pt);

		// 鼠标经过时高亮显示

		// 避免鼠标经过时留下难看的痕迹
		CImageList::DragShowNolock(false);
		if ((hItem = HitTest(point,&flags)) != NULL)
		{
			this->SelectDropTarget(hItem);
			m_hItemDragD = hItem;
		}
		CImageList::DragShowNolock(true);

		// 当条目被拖曳到左边缘时，将条目放在根下
		CRect rect;
		this->GetClientRect(&rect);
		if (point.x < rect.left + 20)
			m_hItemDragD = NULL;
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}

void CWindowsViewTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonUp(nFlags, point);

	if (m_bDragging)
	{
		m_bDragging = false;
		CImageList::DragLeave(this);
		CImageList::EndDrag();
		::ReleaseCapture();
		SAFE_DELETE(m_pDragImage);

		this->SelectDropTarget(NULL);

		if (m_hItemDragS == m_hItemDragD)
		{
			this->KillTimer(m_nScrollTimerID);
			return;
		}

		this->Expand(m_hItemDragD, TVE_EXPAND);

		HTREEITEM htiParent = m_hItemDragD;
		//while( (htiParent = GetParentItem(htiParent)) != NULL )
		//{
		//	if( htiParent == m_hItemDragS )
		//	{
		//		HTREEITEM  htiNewTemp = CopyBranch( m_hItemDragS,NULL,TVI_LAST );
		//		HTREEITEM  htiNew = CopyBranch( htiNewTemp,m_hItemDragD,TVI_LAST );
		//		DeleteItem( htiNewTemp );
		//		SelectItem( htiNew );
		//		KillTimer( m_nScrollTimerID );
		//		return;
		//	}
		//}

		//HTREEITEM  htiNew = CopyBranch( m_hItemDragS,m_hItemDragD,TVI_LAST );
		//DeleteItem( m_hItemDragS );
		//SelectItem( htiNew );
		this->KillTimer(m_nScrollTimerID);
	}
}

void CWindowsViewTree::OnTimer(UINT_PTR nIDEvent)
{
	// 鼠标敏感节点
	if (nIDEvent == m_nHoverTimerID)
	{
		this->KillTimer(m_nHoverTimerID);
		m_nHoverTimerID = 0;

		HTREEITEM trItem = 0;
		UINT uFlag = 0;
		trItem = this->HitTest(m_HoverPoint, &uFlag);
		if (trItem && m_bDragging)
		{
			this->SelectItem(trItem);
			this->Expand(trItem, TVE_EXPAND);
		}
	}
	//处理拖曳过程中的滚动问题
	else if (nIDEvent == m_nScrollTimerID)
	{
		m_TimerTicks++;
		CPoint pt;
		::GetCursorPos(&pt);
		CRect rect;
		this->GetClientRect(&rect);
		this->ClientToScreen(&rect);

		HTREEITEM hItem = GetFirstVisibleItem();

		if (pt.y < rect.top + 10)
		{
			// 向上滚动
			int slowscroll = 6 - (rect.top + 10 - pt.y )/20;
			if (0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)))
			{
				CImageList::DragShowNolock(false);
				this->SendMessage(WM_VSCROLL, SB_LINEUP);
				this->SelectDropTarget(hItem);
				m_hItemDragD = hItem;
				CImageList::DragShowNolock(true);
			}
		}
		else if (pt.y > rect.bottom - 10)
		{
			// 向下滚动
			int slowscroll = 6 - (pt.y - rect.bottom + 10)/20;
			if (0 == (m_TimerTicks % ((slowscroll > 0) ? slowscroll : 1)))
			{
				CImageList::DragShowNolock(false);
				this->SendMessage(WM_VSCROLL,SB_LINEDOWN);
				int nCount = this->GetVisibleCount();
				for (int i=0 ; i<nCount-1 ; i++)
					hItem = this->GetNextVisibleItem(hItem);
				if (hItem)
					this->SelectDropTarget(hItem);
				m_hItemDragD = hItem;
				CImageList::DragShowNolock(true);
			}
		}
	}
	else
	{
		CTreeCtrl::OnTimer(nIDEvent);
	}
}

void CWindowsViewTree::OnUpdateControyToDown(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CWindowsViewTree::OnUpdateControyToUp(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CWindowsViewTree::OnControyToDown()
{
	HTREEITEM hItem = this->GetSelectedItem();
	if (!IS_SAFE_HANDLE(hItem))
		return;

	// 选择了根
	HTREEITEM hRootItem = this->GetRootItem();
	if (hRootItem == hItem)
	{
		AfxMessageBox(_T("调整控件的层次关系前，请先选择控件节点！"), MB_OK | MB_ICONWARNING);
		return;
	}

	IFeatureObject *pObj = (IFeatureObject*)this->GetItemData(hItem);
	if (pObj == NULL)
	{
		AfxMessageBox(_T("居然有无效节点！"), MB_OK | MB_ICONWARNING);
		return;
	}

	if (lstrcmpA(pObj->GetObjectType(), PROP_TYPE_WINDOW_NAME) == 0)
	{
		AfxMessageBox(_T("调整控件的层次关系前，请先选择控件节点！"), MB_OK | MB_ICONWARNING);
		return;
	}

	ControyToDown(hItem);
}

void CWindowsViewTree::OnControyToUp()
{
	HTREEITEM hItem = this->GetSelectedItem();
	if (!IS_SAFE_HANDLE(hItem))
		return;

	// 选择了根
	HTREEITEM hRootItem = this->GetRootItem();
	if (hRootItem == hItem)
	{
		AfxMessageBox(_T("调整控件的层次关系前，请先选择控件节点！"), MB_OK | MB_ICONWARNING);
		return;
	}

	IFeatureObject *pObj = (IFeatureObject*)this->GetItemData(hItem);
	if (pObj == NULL)
	{
		AfxMessageBox(_T("居然有无效节点！"), MB_OK | MB_ICONWARNING);
		return;
	}

	if (lstrcmpA(pObj->GetObjectType(), PROP_TYPE_WINDOW_NAME) == 0)
	{
		AfxMessageBox(_T("调整控件的层次关系前，请先选择控件节点！"), MB_OK | MB_ICONWARNING);
		return;
	}

	ControyToUp(hItem);
}

HTREEITEM CWindowsViewTree::GetLastChildItem(HTREEITEM hItem)
{
	if (hItem == NULL)
		return NULL;

	HTREEITEM hLastChild = NULL;
	HTREEITEM hChild = this->GetChildItem(hItem);
	while (hChild != NULL)
	{
		hLastChild = hChild;
		hChild = this->GetNextItem(hChild, TVGN_NEXT);
	}

	return hLastChild;
}

HTREEITEM CWindowsViewTree::GetFirstChildItem(HTREEITEM hItem)
{
	if (hItem == NULL)
		return NULL;

	return this->GetChildItem(hItem);
}

void CWindowsViewTree::ControyToDown(HTREEITEM hItem)
{
	if (hItem == NULL)
		return;

	HTREEITEM hParentItem = this->GetParentItem(hItem);
	if (hParentItem == NULL)
		return;

	HTREEITEM hLast = GetLastChildItem(hParentItem);
	if (hLast == hItem)
	{
		AfxMessageBox(_T("已经将控件设置到最顶层了！"), MB_OK | MB_ICONWARNING);
		return;
	}


}

void CWindowsViewTree::ControyToUp(HTREEITEM hItem)
{
	if (hItem == NULL)
		return;

}
