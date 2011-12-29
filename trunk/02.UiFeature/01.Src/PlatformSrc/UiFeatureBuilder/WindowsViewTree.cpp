
#include "stdafx.h"
#include "WindowsViewTree.h"
#include "resource.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IFeatureObject.h"
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\ICommonFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWindowsViewTree

CWindowsViewTree::CWindowsViewTree()
{
	m_pSkinMgr = NULL;
	m_pKernelWindow = NULL;
	m_pPropCtrl = NULL;
}

CWindowsViewTree::~CWindowsViewTree()
{
}

BEGIN_MESSAGE_MAP(CWindowsViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CWindowsViewTree::OnNMRClick)
	ON_COMMAND(ID_CREATE_WINDOW_PANEL, &CWindowsViewTree::OnCreateWindowPanel)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CWindowsViewTree::OnTvnSelchanged)
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
	HTREEITEM hItem = this->GetSelectedItem();
	if (!IS_SAFE_HANDLE(hItem))
		return;

	HTREEITEM hRootItem = this->GetRootItem();
	if (hRootItem == hItem)
	{
		POINT pt;
		::GetCursorPos(&pt);

		CMenu CreateMenu;
		CreateMenu.LoadMenu(IDM_CREATE_WINDOW);
		CreateMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}

	*pResult = 0;
}

void CWindowsViewTree::Init(IKernelWindow* pKernelWindow, CPropertyViewCtrl *pPropCtrl)
{
	if (pKernelWindow == NULL || pPropCtrl == NULL)
		return;

	m_pKernelWindow = pKernelWindow;
	m_pSkinMgr = m_pKernelWindow->GetSkinManager();
	m_pPropCtrl = pPropCtrl;

	this->DeleteAllItems();
	HTREEITEM hRootItem = this->InsertItem(_T("【窗口/面板】"), 1, 1);
	this->SetItemState(hRootItem, TVIS_BOLD, TVIS_BOLD);
	this->SelectItem(hRootItem);
}

void CWindowsViewTree::OnCreateWindowPanel()
{
	if (m_pSkinMgr == NULL || m_pKernelWindow == NULL || m_pPropCtrl == NULL)
	{
		AfxMessageBox(_T("列表没有被初始化"), MB_OK | MB_ICONERROR);
		return;
	}

	HTREEITEM hRootItem = this->GetRootItem();
	HTREEITEM hWindow = this->InsertItem(_T("新建窗口/面板"), 0, 0, hRootItem);
	this->Expand(hRootItem, TVE_EXPAND);
	if (hWindow == NULL)
	{
		AfxMessageBox(_T("新建窗口/面板错误！"), MB_OK | MB_ICONERROR);
		return;
	}
	
	IWindowBase *pWndBase = m_pKernelWindow->BuilderCreateEmptyWindow();
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
		return;
	}

	*pResult = 0;
}

void CWindowsViewTree::OnTvnSelchanged_SelectRoot()
{
	if (m_pPropCtrl == NULL)
		return;

	m_pPropCtrl->ClearAll();
}

void CWindowsViewTree::OnTvnSelchanged_SelectWindow(IWindowBase *pWndBase)
{
	OnTvnSelchanged_SelectRoot();

	if (m_pPropCtrl == NULL || pWndBase == NULL)
		return;

	IPropertyWindowManager* pPropWndMgr = pWndBase->GetWindowProp();
	if (pPropWndMgr == NULL)
		return;

	IPropertyGroup* pPropGroup = pPropWndMgr->GetWindowPropetryBaseGroup();
	if (pPropGroup == NULL)
		return;

	m_pPropCtrl->SetShowPropGroup(pPropGroup);
}

void CWindowsViewTree::Refresh(IPropertyGroup *pRefreshGroup)
{
	if (pRefreshGroup == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pRefreshGroup);
	if (pPropBase == NULL)
		return;

	HTREEITEM hRootItem = this->GetRootItem();
	HTREEITEM hRefreshItem = FindRefreshTreeItem(hRootItem, pPropBase);
	if (hRefreshItem == NULL)
		return;
	
	RefreshTreeItem(hRefreshItem);
}

HTREEITEM CWindowsViewTree::FindRefreshTreeItem(HTREEITEM hItem, IPropertyBase *pPropBase)
{
	if (hItem == NULL || pPropBase == NULL)
		return NULL;

	IFeatureObject *pComPropBase = (IFeatureObject*)this->GetItemData(hItem);
	if (pComPropBase != NULL && pComPropBase->GetObjectId() != NULL && pPropBase->GetObjectId() != NULL
		&& lstrcmpA(pComPropBase->GetObjectId(), pPropBase->GetObjectId()) == 0)
		return hItem;

	if (!this->ItemHasChildren(hItem))
		return NULL;

	HTREEITEM hChild = this->GetChildItem(hItem);
	while(hChild != NULL)
	{
		HTREEITEM hFind = FindRefreshTreeItem(hChild, pPropBase);
		if (hFind != NULL)
			return hFind;

		hChild = this->GetNextItem(hChild, TVGN_NEXT);
	}

	return NULL;
}

void CWindowsViewTree::RefreshTreeItem(HTREEITEM hItem)
{
	USES_CONVERSION;
	if (hItem == NULL)
		return;

	IFeatureObject *pPropBase = (IFeatureObject*)this->GetItemData(hItem);
	if (pPropBase != NULL)
	{
		// 刷新操作，目前只有刷新名字
		if (pPropBase->GetObjectTypeId() == OTID_WINDOW)
		{
			// 窗口
			IWindowBase* pWnd = dynamic_cast<IWindowBase*>(pPropBase);
			if (pWnd != NULL)
			{
				IPropertyGroup *pWnpPropGroup = pWnd->GetWindowProp()->GetWindowPropetryBaseGroup();
				if (pWnpPropGroup != NULL)
				{
					pWnd->SetObjectName(pWnpPropGroup->GetObjectName());
					this->SetItemText(hItem, A2W(pWnd->GetObjectName()));
				}
			}
		}
		else if (pPropBase->GetObjectTypeId() == OTID_CONTROL)
		{
			// 控件
			this->SetItemText(hItem, A2W(pPropBase->GetObjectName()));
		}
	}

	if (!this->ItemHasChildren(hItem))
		return;

	HTREEITEM hChild = this->GetChildItem(hItem);
	while(hChild != NULL)
	{
		RefreshTreeItem(hChild);
		hChild = this->GetNextItem(hChild, TVGN_NEXT);
	}
}

void CWindowsViewTree::InitShowNewProject()
{
	USES_CONVERSION;
	this->DeleteAllItems();
	HTREEITEM hRootItem = this->InsertItem(_T("【窗口/面板】"), 1, 1);
	this->SetItemState(hRootItem, TVIS_BOLD, TVIS_BOLD);

	if (m_pSkinMgr == NULL || m_pKernelWindow == NULL)
		return;

	ONE_RESOURCE_PROP_MAP* pWndPropMap = m_pSkinMgr->BuilderGetWindowPropMap();
	if (pWndPropMap == NULL)
		return;

	for (ONE_RESOURCE_PROP_MAP::iterator pWndItem = pWndPropMap->begin(); pWndItem != pWndPropMap->end(); pWndItem++)
	{
		IPropertyWindow* pPropWnd = dynamic_cast<IPropertyWindow*>(pWndItem->second);
		if (pPropWnd == NULL)
			continue;

		IWindowBase* pWndBase = m_pKernelWindow->BuilderCreatePropetryWindow(pPropWnd);
		if (pWndBase == NULL)
			continue;

		HTREEITEM hWindowItem = this->InsertItem(A2W(pWndBase->GetObjectName()), 0, 0, hRootItem);
		if (hWindowItem == NULL)
			continue;


	}

	// 选中并打开根节点
	this->SelectItem(hRootItem);
	this->Expand(hRootItem, TVE_EXPAND);
}
