
#pragma once
#include "afxlistctrl.h"

class CFeatureBaseList : public CMFCListCtrl
{
public:
	CFeatureBaseList(void);
	~CFeatureBaseList(void);

protected:
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);
	virtual void Sort(int iColumn, BOOL bAscending = TRUE, BOOL bAdd = FALSE);

	virtual void OnSelectItem();

protected:
	NMITEMACTIVATE m_SelectItem;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};
