
#pragma once

#include "WindowsViewTree.h"
#include "WindowTreeToolBar.h"

class CWindowsView : public CDockablePane
{
public:
	CWindowsView();
	virtual ~CWindowsView();

	void AdjustLayout();
	void OnChangeVisualStyle();

	CWindowsViewTree *GetViewTreeCtrl();
	void Init(IUiFeatureKernel* pKernelWindow, CPropertyViewCtrl *pPropCtrl);
	void InitShowNewProject();
	void SetProjectInitState(bool bInitOk);

protected:
	CWindowTreeToolBar m_TreeToolBar;
	CWindowsViewTree m_wndWindowTree;
	CImageList m_WindowViewImages;

private:
	HTREEITEM m_hRoot;

// ÖØÐ´
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUpdateControyToDown(CCmdUI *pCmdUI);
	afx_msg void OnControyToDown();
	afx_msg void OnControyToUp();
	afx_msg void OnUpdateControyToUp(CCmdUI *pCmdUI);
};

