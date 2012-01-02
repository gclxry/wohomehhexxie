#include "StdAfx.h"
#include "FeatureControlList.h"
#include "MainFrm.h"

CFeatureControlList::CFeatureControlList(void)
{
	m_bInitOk = false;
}

CFeatureControlList::~CFeatureControlList(void)
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
//	if (!m_bInitOk)
//		return;

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if (pNMItemActivate == NULL)
		return;

	// 
	if (pNMItemActivate->iItem < 0)
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
////	HINSTANCE hInstance = ::GetModuleHandle(NULL);
//	HCURSOR hCursor = NULL;
//	if (bIsNormal)
//		hCursor = ::LoadCursor(NULL, IDC_ARROW);
//	else
//		hCursor = ::LoadCursor(NULL, IDC_CROSS);
//
////	DWORD dwErr = GetLastError();
//
//	::ShowCursor(FALSE) ;//����ԭ���Ĺ��
//	HCURSOR hSetCur = ::SetCursor(hCursor);
//	::ShowCursor(TRUE) ;//��ʾ�µĹ�� 
//	DWORD dwErr = GetLastError();
////	int i = 0;

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
	{
		::ShowCursor(FALSE);
		if (bIsNormal)
			pMain->SetCrossCursor(false);
		else
			pMain->SetCrossCursor(true);
		::ShowCursor(TRUE);
	}
}
