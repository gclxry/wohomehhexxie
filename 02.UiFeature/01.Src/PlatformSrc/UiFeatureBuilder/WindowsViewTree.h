
#pragma once
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IControlBase.h"
#include "PropertyViewCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CWindowsViewTree 窗口

class CUiFeatureBuilderView;
class CWindowsViewTree : public CTreeCtrl
{
// 构造
public:
	CWindowsViewTree();
	virtual ~CWindowsViewTree();

	// 设置可以保存的有效属性
	void SetSaveWindowActivePropetry();

	void SetBuilderView(CUiFeatureBuilderView* pWndView);
	void Init(IUiFeatureKernel* pKernelWindow, CPropertyViewCtrl *pPropCtrl);
	void RefreshObjectName();
	void InitShowNewProject();
	void SetProjectInitState(bool bInitOk);
	// 向树中插入一个新节点
	void AddNewControlToWindowTreeNode(IWindowBase *pWindow, IControlBase* pParentCtrl, IControlBase *pControl);

	void SetViewEditControl(IControlBase *pCtrl);

// 重写
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	void SetNeedSave();
private:
	void OnTvnSelchanged_SelectRoot();
	void OnTvnSelchanged_SelectWindow(IWindowBase *pWndBase);
	void OnTvnSelchanged_SelectControl(IControlBase *pCtrlBase);

	void RefreshItemObjectName(HTREEITEM hParentItem);
	// 查找指定的控件
	HTREEITEM FindControlTreeNode(HTREEITEM hParentNode, IControlBase* pCtrl);
	// 在指定节点的子节点末尾插入新节点
	HTREEITEM InsertControlNodeToEnd(HTREEITEM hParentNode, IControlBase *pControl);
	// 向树中插入一个新节点
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
	// 拖拽
	UINT          m_TimerTicks;      //处理滚动的定时器所经过的时间
	UINT          m_nScrollTimerID;  //处理滚动的定时器
	CPoint        m_HoverPoint;      //鼠标位置
	UINT          m_nHoverTimerID;   //鼠标敏感定时器
	DWORD         m_dwDragStart;     //按下鼠标左键那一刻的时间
	bool          m_bDragging;       //标识是否正在拖动过程中
	CImageList*   m_pDragImage;      //拖动时显示的图象列表
	HTREEITEM     m_hItemDragS;      //被拖动的标签
	HTREEITEM     m_hItemDragD;      //接受拖动的标签
	

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
