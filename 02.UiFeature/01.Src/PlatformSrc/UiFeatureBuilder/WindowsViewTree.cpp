
#include "stdafx.h"
#include "WindowsViewTree.h"
#include "resource.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IFeatureObject.h"

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
	HTREEITEM hRootItem = this->InsertItem(_T("【窗体-面板】"), 0, 0);
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
	HTREEITEM hWindow = this->InsertItem(_T("新建窗体/面板"), 1, 1, hRootItem);
	this->Expand(hRootItem, TVE_EXPAND);
	if (hWindow == NULL)
	{
		AfxMessageBox(_T("新建窗体/面板错误！"), MB_OK | MB_ICONERROR);
		return;
	}
	
	IWindowBase *pWndBase = m_pKernelWindow->BuilderCreateWindow();
	if (pWndBase == NULL)
	{
		AfxMessageBox(_T("新建窗体/面板时，创建绘制窗体错误！"), MB_OK | MB_ICONERROR);
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
