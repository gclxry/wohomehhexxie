
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
}

CWindowsViewTree::~CWindowsViewTree()
{
}

BEGIN_MESSAGE_MAP(CWindowsViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CWindowsViewTree::OnNMRClick)
	ON_COMMAND(ID_CREATE_WINDOW_PANEL, &CWindowsViewTree::OnCreateWindowPanel)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CWindowsViewTree::OnTvnSelchanged)
	ON_COMMAND(IDM_DELETE_WNDCTRL, &CWindowsViewTree::OnDeleteWndctrl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowsViewTree ��Ϣ�������

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
		HTREEITEM hRootItem = this->InsertItem(_T("������/��塿"), 1, 1);
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
		AfxMessageBox(_T("�б�û�б���ʼ��"), MB_OK | MB_ICONERROR);
		return;
	}

	HTREEITEM hRootItem = this->GetRootItem();
	HTREEITEM hWindow = this->InsertItem(_T("�½�����/���"), 0, 0, hRootItem, TVI_LAST);
	this->Expand(hRootItem, TVE_EXPAND);
	if (hWindow == NULL)
	{
		AfxMessageBox(_T("�½�����/������"), MB_OK | MB_ICONERROR);
		return;
	}
	
	IWindowBase *pWndBase = m_pUiKernel->BD_CreateWindowEmptyPropetry();
	if (pWndBase == NULL)
	{
		AfxMessageBox(_T("�½�����/���ʱ���������ƴ������"), MB_OK | MB_ICONERROR);
		return;
	}

	this->SetItemData(hWindow, (DWORD_PTR)pWndBase);
	this->SelectItem(hWindow);
}

void CWindowsViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	if (!m_bProjectInitOk)
		return;

	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hItem = this->GetSelectedItem();
	if (!IS_SAFE_HANDLE(hItem))
		return;

	HTREEITEM hRootItem = this->GetRootItem();
	if (hRootItem == hItem)
	{
		// ѡ���˸�
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
		// ѡ���˿ؼ�
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
	OnTvnSelchanged_SelectRoot();

	if (m_pWindowView == NULL || m_pPropCtrl == NULL || pWndBase == NULL)
		return;

	IPropertyGroup* pPropGroup = pWndBase->PP_GetWindowPropetryGroup();
	if (pPropGroup == NULL)
		return;

	m_pPropCtrl->SetShowPropGroup(pPropGroup);
	m_pWindowView->ResetShowWindow(pWndBase, NULL);
}

void CWindowsViewTree::OnTvnSelchanged_SelectControl(IControlBase *pCtrlBase)
{
	OnTvnSelchanged_SelectRoot();

	if (m_pWindowView == NULL || m_pPropCtrl == NULL || pCtrlBase == NULL)
		return;

	IPropertyGroup* pPropGroup = pCtrlBase->PP_GetControlPropetryGroup();
	if (pPropGroup == NULL)
		return;

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
			// ˢ�²�����Ŀǰֻ��ˢ������
			if (pPropBase->GetObjectTypeId() == OTID_WINDOW)
			{
				// ����
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
				// �ؼ�
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

		// �����ӿؼ�������
		RefreshItemObjectName(hChild);

		hChild = this->GetNextItem(hChild, TVGN_NEXT);
	}
}

void CWindowsViewTree::InitShowNewProject()
{
	USES_CONVERSION;
	this->DeleteAllItems();
	HTREEITEM hRootItem = this->InsertItem(_T("������/��塿"), 1, 1);
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

		// �ӿؼ���ʾ
		InsertCtrlVecByPropCtrlVec(hWindowItem, pWndBase, NULL, pWndBase->GetChildPropControlVec(), pWndBase->GetChildControlsVec());
	}

	// ѡ�в��򿪸��ڵ�
	this->SelectItem(hRootItem);
	this->Expand(hRootItem, TVE_EXPAND);
}

// �����в���һ���½ڵ�
void CWindowsViewTree::InsertCtrlVecByPropCtrlVec(HTREEITEM hParentItem, IWindowBase *pParentWnd, IControlBase *pParentCtrl, PROP_CONTROL_VEC* pPropCtrlVec, CHILD_CTRLS_VEC* pCtrlVec)
{
	if (hParentItem == NULL || pCtrlVec == NULL || m_pUiKernel == NULL)
		return;

	for (PROP_CONTROL_VEC::iterator pCtrlItem = pPropCtrlVec->begin(); pCtrlItem != pPropCtrlVec->end(); pCtrlItem++)
	{
		IPropertyControl* pPropCtrl = *pCtrlItem;
		if (pPropCtrl == NULL)
			continue;

		IControlBase *pNewCtrl = m_pUiKernel->BD_CreateControlByPropetry(pParentWnd, pParentCtrl, pPropCtrl);
		if (pNewCtrl == NULL)
			return;

		HTREEITEM hItem = InsertControlNodeToEnd(hParentItem, pNewCtrl);
		if (hItem == NULL)
			continue;

		InsertCtrlVecByPropCtrlVec(hItem, pParentWnd, pNewCtrl, pPropCtrl->GetChildPropControlVec(), pNewCtrl->GetChildControlsVec());
	}
}

// ����ָ���Ŀؼ�
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

// �����в���һ���½ڵ�
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

			// ѡ�в��򿪸��ڵ�
			this->SelectItem(hNewItem);
			this->RedrawWindow();
			break;
		}

		hWindowNode = this->GetNextItem(hWindowNode, TVGN_NEXT);
	}
}

// ��ָ���ڵ���ӽڵ�ĩβ�����½ڵ�
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

// ���ÿ��Ա������Ч����
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
		AfxMessageBox(_T("�б�û�б���ʼ��"), MB_OK | MB_ICONERROR);
		return;
	}

	if (m_hRBtnSelItem == NULL)
	{
		AfxMessageBox(_T("û��ѡ����Ҫɾ���Ľڵ㣡"), MB_OK | MB_ICONERROR);
		return;
	}
	this->SelectItem(m_hRBtnSelItem);

	IFeatureObject* pObj = (IFeatureObject*)this->GetItemData(m_hRBtnSelItem);
	if (pObj->GetObjectTypeId() == OTID_WINDOW)
	{
		IWindowBase *pWndBase = dynamic_cast<IWindowBase*>(pObj);
		if (pWndBase == NULL)
		{
			AfxMessageBox(_T("����ġ�Window���ڵ㣡"), MB_OK | MB_ICONERROR);
			return;
		}

		CString strInfo(_T(""));
		strInfo.Format(_T("ȷ��ɾ������/��塾%s����"), A2W(pWndBase->GetObjectName()));
		if (AfxMessageBox(strInfo, MB_OKCANCEL | MB_ICONWARNING) != IDOK)
			return;

		m_pUiKernel->BD_DeleteWindow(pWndBase);
	}
	else
	{
		IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(pObj);
		if (pCtrlBase == NULL)
		{
			AfxMessageBox(_T("����ġ�Control���ڵ㣡"), MB_OK | MB_ICONERROR);
			return;
		}

		CString strInfo(_T(""));
		strInfo.Format(_T("ȷ��ɾ���ؼ���%s[%s]����"), A2W(pCtrlBase->GetObjectName()), A2W(pCtrlBase->GetObjectType()));
		if (AfxMessageBox(strInfo, MB_OKCANCEL | MB_ICONWARNING) != IDOK)
			return;

		m_pUiKernel->BD_DeleteControl(pCtrlBase);
	}

	HTREEITEM hItem = this->GetParentItem(m_hRBtnSelItem);
	this->DeleteItem(m_hRBtnSelItem);

	if (hItem == NULL)
		hItem = this->GetRootItem();

	if (hItem != NULL)
	{
		// ѡ�в��򿪸��ڵ�
		this->SelectItem(hItem);
		this->Expand(hItem, TVE_EXPAND);
	}
}
