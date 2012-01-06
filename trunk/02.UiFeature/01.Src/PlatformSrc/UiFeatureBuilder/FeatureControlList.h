
#pragma once
#include "afxlistctrl.h"

// 显示控件名称的列
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
	// true:设置为正常鼠标样式，false:设置为拖动控件鼠标样式
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
