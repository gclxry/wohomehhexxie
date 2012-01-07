
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IControlBase.h"
#include "PropertyViewCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CWindowsViewTree ����

class CUiFeatureBuilderView;
class CWindowsViewTree : public CTreeCtrl
{
// ����
public:
	CWindowsViewTree();
	virtual ~CWindowsViewTree();

	void SetBuilderView(CUiFeatureBuilderView* pWndView);
	void Init(IUiFeatureKernel* pKernelWindow, CPropertyViewCtrl *pPropCtrl);
	void RefreshObjectName();
	void InitShowNewProject();
	void SetProjectInitState(bool bInitOk);
	// �����в���һ���½ڵ�
	void AddNewControlToWindowTreeNode(IWindowBase *pWindow, IControlBase* pParentCtrl, IControlBase *pControl);

// ��д
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

private:
	void OnTvnSelchanged_SelectRoot();
	void OnTvnSelchanged_SelectWindow(IWindowBase *pWndBase);
	void OnTvnSelchanged_SelectControl(IControlBase *pCtrlBase);

	void RefreshItemObjectName(HTREEITEM hParentItem);
	// ����ָ���Ŀؼ�
	HTREEITEM FindControlTreeNode(HTREEITEM hParentNode, IControlBase* pCtrl);
	// ��ָ���ڵ���ӽڵ�ĩβ�����½ڵ�
	HTREEITEM InsertControlNodeToEnd(HTREEITEM hParentNode, IControlBase *pControl);
	// �����в���һ���½ڵ�
	void InsertControlVec(HTREEITEM hParentItem, CHILD_CTRLS_VEC* pCtrlVec);

private:
	bool m_bProjectInitOk;
	IPropertySkinManager *m_pSkinMgr;
	IUiFeatureKernel* m_pUiKernel;
	CPropertyViewCtrl *m_pPropCtrl;
	CUiFeatureBuilderView *m_pWindowView;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCreateWindowPanel();
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};
