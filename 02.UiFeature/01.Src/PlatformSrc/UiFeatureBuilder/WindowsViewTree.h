
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

	// ���ÿ��Ա������Ч����
	void SetSaveWindowActivePropetry();

	void SetBuilderView(CUiFeatureBuilderView* pWndView);
	void Init(IUiFeatureKernel* pKernelWindow, CPropertyViewCtrl *pPropCtrl);
	void RefreshObjectName();
	void InitShowNewProject();
	void SetProjectInitState(bool bInitOk);
	// �����в���һ���½ڵ�
	void AddNewControlToWindowTreeNode(IWindowBase *pWindow, IControlBase* pParentCtrl, IControlBase *pControl);

	void SetViewEditControl(IControlBase *pCtrl);

// ��д
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	void SetNeedSave();
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
	void InsertCtrlVecByPropCtrlVec(HTREEITEM hParentItem, IWindowBase *pParentWnd, IControlBase *pParentCtrl, PROP_CONTROL_VEC* pPropCtrlVec, CHILD_CTRLS_VEC* pCtrlVec);
	
	void SetViewEditControl_Child(HTREEITEM hParentItem, IControlBase *pCtrl);

private:
	bool m_bProjectInitOk;
	IPropertySkinManager *m_pSkinMgr;
	IUiFeatureKernel* m_pUiKernel;
	CPropertyViewCtrl *m_pPropCtrl;
	CUiFeatureBuilderView *m_pWindowView;

	HTREEITEM m_hRBtnSelItem;

	bool m_bFromViewSel;

//////////////////////////////////////////////////////////////////////////
	// ��ק
	UINT          m_TimerTicks;      //��������Ķ�ʱ����������ʱ��
	UINT          m_nScrollTimerID;  //��������Ķ�ʱ��
	CPoint        m_HoverPoint;      //���λ��
	UINT          m_nHoverTimerID;   //������ж�ʱ��
	DWORD         m_dwDragStart;     //������������һ�̵�ʱ��
	bool          m_bDragging;       //��ʶ�Ƿ������϶�������
	CImageList*   m_pDragImage;      //�϶�ʱ��ʾ��ͼ���б�
	HTREEITEM     m_hItemDragS;      //���϶��ı�ǩ
	HTREEITEM     m_hItemDragD;      //�����϶��ı�ǩ
	

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCreateWindowPanel();
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeleteWndctrl();
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
