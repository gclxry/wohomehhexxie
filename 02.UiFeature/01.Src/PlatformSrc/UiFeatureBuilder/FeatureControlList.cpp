#include "StdAfx.h"
#include "FeatureControlList.h"
#include "MainFrm.h"
#include "UiFeatureBuilderView.h"

CFeatureControlList::CFeatureControlList(void)
{
	m_bInitOk = false;
	m_pView = NULL;
	m_pSelectItem = NULL;
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
		SetCtrlListCursor(true);
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
	if (!m_bInitOk)
		return;

	m_pSelectItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if (m_pSelectItem == NULL)
		return;

	// 
	if (m_pSelectItem->iItem < 0)
	{
		// û��ѡ����Ӧ�Ŀؼ�
		SetCtrlListCursor(true);
		return;
	}

	SetCtrlListCursor(false);
}

// ����Ϊ���������ʽ������Ϊ�϶��ؼ������ʽ
void CFeatureControlList::SetCtrlListCursor(bool bIsNormal)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
	{
		::ShowCursor(FALSE);
		pMain->SetCrossCursor(!bIsNormal);
		::ShowCursor(TRUE);
	}

	if (m_pView != NULL)
	{
		// �Ƿ���Ҫ����һ���¿ؼ�
		m_pView->SetNewControl(!bIsNormal);
	}
}

void CFeatureControlList::SetBuilderView(CUiFeatureBuilderView *pView)
{
	m_pView = pView;
}

CString CFeatureControlList::GetSelectCtrlTypeName()
{
	CString strName(_T(""));
	if (m_pSelectItem != NULL && m_pSelectItem->iItem >= 0)
		strName = this->GetItemText(m_pSelectItem->iItem, CONTROL_NAME_COLUMN);

	return strName;
}