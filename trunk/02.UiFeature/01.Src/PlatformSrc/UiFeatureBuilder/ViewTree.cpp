
#include "stdafx.h"
#include "ViewTree.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
	m_pSkinMgr = NULL;
	m_pKernelWindow = NULL;
	m_pPropCtrl = NULL;
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CViewTree::OnNMRClick)
	ON_COMMAND(ID_CREATE_WINDOW_PANEL, &CViewTree::OnCreateWindowPanel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree ��Ϣ�������

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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

void CViewTree::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hRootItem = this->GetRootItem();
	HTREEITEM hItem = this->GetSelectedItem();

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

void CViewTree::Init(IKernelWindow* pKernelWindow, CPropertyCtrl *pPropCtrl)
{
	if (pKernelWindow == NULL || pPropCtrl == NULL)
		return;

	m_pKernelWindow = pKernelWindow;
	m_pSkinMgr = m_pKernelWindow->GetSkinManager();
	m_pPropCtrl = pPropCtrl;
}

void CViewTree::OnCreateWindowPanel()
{
	if (m_pSkinMgr == NULL || m_pKernelWindow == NULL)
	{
		AfxMessageBox(_T("�б�û�б���ʼ��"), MB_OK | MB_ICONERROR);
		return;
	}

	HTREEITEM hRootItem = this->GetRootItem();
	HTREEITEM hWindow = this->InsertItem(_T("�½�����/���"), 1, 1, hRootItem);
	this->Expand(hRootItem, TVE_EXPAND);
	if (hWindow == NULL)
	{
		AfxMessageBox(_T("�½�����/������"), MB_OK | MB_ICONERROR);
		return;
	}
	
	IWindowBase *pWndBase = m_pKernelWindow->BuilderCreateWindow();
	if (pWndBase == NULL)
	{
		AfxMessageBox(_T("�½�����/���ʱ���������ƴ������"), MB_OK | MB_ICONERROR);
		return;
	}

	this->SetItemData(hWindow, (DWORD_PTR)pWndBase);
}
