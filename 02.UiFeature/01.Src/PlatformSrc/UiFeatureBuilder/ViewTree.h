
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IKernelWindow.h"
#include "PropertyCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CWindowsViewTree ����

class CWindowsViewTree : public CTreeCtrl
{
// ����
public:
	CWindowsViewTree();

// ��д
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// ʵ��
public:
	virtual ~CWindowsViewTree();

	void Init(IKernelWindow* pKernelWindow, CPropertyCtrl *pPropCtrl);

private:
	IPropertySkinManager *m_pSkinMgr;
	IKernelWindow* m_pKernelWindow;
	CPropertyCtrl *m_pPropCtrl;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCreateWindowPanel();
};
