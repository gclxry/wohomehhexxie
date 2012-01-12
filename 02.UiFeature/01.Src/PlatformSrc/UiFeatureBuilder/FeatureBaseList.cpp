
#include "StdAfx.h"
#include "FeatureBaseList.h"

CFeatureBaseList::CFeatureBaseList(void)
{
	m_nSelectItem = -1;
}

CFeatureBaseList::~CFeatureBaseList(void)
{
}

void CFeatureBaseList::Sort(int iColumn, BOOL bAscending, BOOL bAdd)
{

}

COLORREF CFeatureBaseList::OnGetCellBkColor(int nRow, int nColum)
{
//	return(nRow % 2) == 0 ? RGB(253, 241, 249) : RGB(196, 238, 254);
	return(nRow % 2) == 0 ? RGB(255, 235, 93) : RGB(129, 202, 227);
}

BEGIN_MESSAGE_MAP(CFeatureBaseList, CMFCListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CFeatureBaseList::OnNMClick)
END_MESSAGE_MAP()

void CFeatureBaseList::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pSelectItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	m_nSelectItem = -1;

	if (pSelectItem != NULL)
		m_nSelectItem = pSelectItem->iItem;

	OnSelectItem();
}

void CFeatureBaseList::OnSelectItem()
{

}
