
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
/////////////////////////////////////////////////////////////////////////////
// CViewTree 窗口

class CViewTree : public CTreeCtrl
{
// 构造
public:
	CViewTree();

// 重写
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// 实现
public:
	virtual ~CViewTree();

	void SetSkinManager(IPropertySkinManager *pSkinMgr);

private:
	IPropertySkinManager *m_pSkinMgr;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCreateWindowPanel();
};
