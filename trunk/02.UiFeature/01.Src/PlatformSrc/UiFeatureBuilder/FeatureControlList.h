
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
	// true:����Ϊ���������ʽ��false:����Ϊ�϶��ؼ������ʽ
	void SetCtrlListCursor(bool bIsNormal);


private:
	bool m_bInitOk;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};
