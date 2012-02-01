
// UiFeatureBuilderView.h : CUiFeatureBuilderView 类的接口
//


#pragma once
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"

class CFeatureControlList;
class CWindowsViewTree;
class CPropertyViewCtrl;

class CUiFeatureBuilderView : public CFormView
{
protected: // 仅从序列化创建
	CUiFeatureBuilderView();
	DECLARE_DYNCREATE(CUiFeatureBuilderView)

public:
	virtual ~CUiFeatureBuilderView();
	enum{ IDD = IDD_UIFEATUREBUILDER_FORM };
	CUiFeatureBuilderDoc* GetDocument() const;

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图

public:
	void SetNewControl(bool bIsNew);
	void SetProjectInitState(bool bInitOk);

	void ResetShowWindow(IWindowBase *pCurrentWnd, IControlBase *pCtrlBase);
	void Init(IUiFeatureKernel* pKernelWindow, CFeatureControlList *pCtrlList, CWindowsViewTree *pWndTree, CPropertyViewCtrl* pPropViewCtrl);

	// 判断鼠标坐标是否落在了窗口内部
	bool PtInWindow(CPoint point);

	IWindowBase* GetCurrentWindow() { return m_pCurrentWnd; };

private:
	void SetNeedSave();
	void DrawWindowView();
	// 设置光标
	void SetViewCursor(int nCursor);

	void ResetViewShowSize();
	// 是否在窗口的8个方块内移动
	SIZE_CTRL_TYPE OnMouseMove_FangKuai8(CPoint point, bool bIsWnd);
	void OnMouseMove_LButtonDown(CPoint point);
	void OnMouseMove_LButtonDown_MoveCtrl(CPoint point, IControlBase* pLBtnDownCtrl);
	void OnMouseMove_LButtonDown_SizeCtrl(SIZE_CTRL_TYPE nFangKuai8Type, CPoint point, IControlBase* pLBtnDownCtrl);
	// 绘制创建新控件时的矩形
	void DrawMark();
	// 设置新控件的大小
	void CreateNewControlf_SetNewCtrlRect();
	// 取得选择的控件
	IControlBase* GetSelectControl(CPoint point);
	// 通过鼠标拖拽，创建一个新控件
	void CreateNewControl();

protected:
	IUiFeatureKernel* m_pUiKernel;
	IPropertySkinManager *m_pSkinManager;
	IUiEngine *m_pUiEngine;

	CFeatureControlList *m_pControlList;
	CWindowsViewTree *m_pWindowViewTree;
	CPropertyViewCtrl *m_pPropViewCtrl;

	bool m_bInitOk;
	CDrawingBoard m_MemDc;

	bool m_bIsLButtonDown;
	CPoint m_LBtnDownPos;
	CPoint m_LBtnUpPos;
	CPoint m_MouseMovePos;

	bool m_bSizeMoveCtrl;
	bool m_bCreateNewCtrl;

	IWindowBase *m_pCurrentWnd;
	bool m_bMoveInWndFangKuai8;
	bool m_bMoveInCtrlFangKuai8;
	SIZE_CTRL_TYPE m_nMoveFangKuai8Type;

	// 创建新控件时的父控件
	IControlBase *m_pDrawParentCtrl;

	// 鼠标移动时经过的控件
	IControlBase *m_pMouseMoveCtrl;

	// 滚动条滚动后视图的偏移量
	CSize m_ScrollOffset;

private:
	ULONG_PTR m_gdiplusToken;


// 生成的消息映射函数
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // UiFeatureBuilderView.cpp 中的调试版本
inline CUiFeatureBuilderDoc* CUiFeatureBuilderView::GetDocument() const
   { return reinterpret_cast<CUiFeatureBuilderDoc*>(m_pDocument); }
#endif
