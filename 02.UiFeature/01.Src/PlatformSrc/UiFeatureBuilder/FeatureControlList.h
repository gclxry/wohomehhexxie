
#pragma once
#include "afxlistctrl.h"

class CFeatureControlList :	public CMFCListCtrl
{
public:
	CFeatureControlList(void);
	~CFeatureControlList(void);

public:
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);

	void SetProjectInitState(bool bInitOk);

private:
	// true:设置为正常鼠标样式，false:设置为拖动控件鼠标样式
	void SetCtrlListCursor(bool bIsNormal);


private:
	bool m_bInitOk;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};
