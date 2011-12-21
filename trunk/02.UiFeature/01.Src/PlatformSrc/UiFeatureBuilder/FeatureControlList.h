
#pragma once
#include "afxlistctrl.h"

class CFeatureControlList :	public CMFCListCtrl
{
public:
	CFeatureControlList(void);
	~CFeatureControlList(void);

	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);
};
