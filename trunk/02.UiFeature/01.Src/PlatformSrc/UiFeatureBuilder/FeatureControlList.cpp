#include "StdAfx.h"
#include "FeatureControlList.h"
#include "MainFrm.h"
#include "UiFeatureBuilderView.h"

CFeatureControlList::CFeatureControlList(void)
{
	m_bInitOk = false;
	m_pView = NULL;
	memset(&m_SelectItem, 0, sizeof(NMITEMACTIVATE));
	m_SelectItem.iItem = -1;
}

CFeatureControlList::~CFeatureControlList(void)
{
}

void CFeatureControlList::Sort(int iColumn, BOOL bAscending, BOOL bAdd)
{

}

void CFeatureControlList::SetProjectInitState(bool bInitOk)
{
	m_bInitOk = bInitOk;

	if (!m_bInitOk)
		SelectCtrlToCreate(false);
}

COLORREF CFeatureControlList::OnGetCellBkColor(int nRow, int nColum)
{
	return(nRow % 2) == 0 ? RGB(253, 241, 249) : RGB(196, 238, 254);
}
BEGIN_MESSAGE_MAP(CFeatureControlList, CMFCListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CFeatureControlList::OnNMClick)
END_MESSAGE_MAP()

void CFeatureControlList::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pSelectItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	if (!m_bInitOk)
		return;

	memset(&m_SelectItem, 0, sizeof(NMITEMACTIVATE));
	m_SelectItem.iItem = -1;

	if (pSelectItem == NULL)
	{
		SelectCtrlToCreate(false);
		return;
	}

	m_SelectItem = *pSelectItem;

	if (m_SelectItem.iItem < 0)
	{
		// 没有选择相应的控件
		SelectCtrlToCreate(false);
		return;
	}

	SelectCtrlToCreate(true);
}

// 设置为正常鼠标样式，设置为拖动控件鼠标样式
void CFeatureControlList::SelectCtrlToCreate(bool bCreate)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain == NULL || m_pView == NULL)
		return;

	if (bCreate)
		pMain->SetViewCursor(UF_IDC_CROSS);
	else
		pMain->SetViewCursor(UF_IDC_ARROW);

	m_pView->SetNewControl(bCreate);
}

void CFeatureControlList::SetBuilderView(CUiFeatureBuilderView *pView)
{
	m_pView = pView;
}

CString CFeatureControlList::GetSelectCtrlTypeName()
{
	CString strName(_T(""));
	if (m_SelectItem.iItem >= 0)
		strName = this->GetItemText(m_SelectItem.iItem, CONTROL_NAME_COLUMN);

	return strName;
}