
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IKernelWindow.h"
#include "PropertyViewCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CWindowsViewTree 窗口

class CWindowsViewTree : public CTreeCtrl
{
// 构造
public:
	CWindowsViewTree();
	virtual ~CWindowsViewTree();
	void Init(IKernelWindow* pKernelWindow, CPropertyViewCtrl *pPropCtrl);

// 重写
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

private:
	void OnTvnSelchanged_SelectRoot();
	void OnTvnSelchanged_SelectWindow();

private:
	IPropertySkinManager *m_pSkinMgr;
	IKernelWindow* m_pKernelWindow;
	CPropertyViewCtrl *m_pPropCtrl;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCreateWindowPanel();
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};
