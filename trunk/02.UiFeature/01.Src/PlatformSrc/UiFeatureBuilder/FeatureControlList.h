
#pragma once
#include "afxlistctrl.h"

// ��ʾ�ؼ����Ƶ���
#define CONTROL_NAME_COLUMN					(1)

class CUiFeatureBuilderView;
class CFeatureControlList :	public CMFCListCtrl
{
public:
	CFeatureControlList(void);
	~CFeatureControlList(void);

public:
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);

	void SetProjectInitState(bool bInitOk);
	void SetBuilderView(CUiFeatureBuilderView *pView);
	CString GetSelectCtrlTypeName();

private:
	// true:����Ϊ���������ʽ��false:����Ϊ�϶��ؼ������ʽ
	void SelectCtrlToCreate(bool bCreate);

protected:
	virtual void Sort(int iColumn, BOOL bAscending = TRUE, BOOL bAdd = FALSE);

private:
	bool m_bInitOk;
	CUiFeatureBuilderView *m_pView;
	NMITEMACTIVATE m_SelectItem;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};
