
#pragma once

#include "WindowsViewTree.h"

class CClassToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CWindowView : public CDockablePane
{
public:
	CWindowView();
	virtual ~CWindowView();

	void AdjustLayout();
	void OnChangeVisualStyle();

	CWindowsViewTree *GetViewTreeCtrl();
	void Init(IKernelWindow* pKernelWindow, CPropertyCtrl *pPropCtrl);

protected:
	CClassToolBar m_wndToolBar;
	CWindowsViewTree m_wndWindowTree;
	CImageList m_ClassViewImages;
	UINT m_nCurrSort;

	void FillClassView();

private:
	HTREEITEM m_hRoot;

// ÖØÐ´
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

