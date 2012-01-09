
// UiFeatureBuilderView.h : CUiFeatureBuilderView 类的接口
//


#pragma once
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\IControlBase.h"

class CFeatureControlList;
class CWindowsViewTree;

#define UF_IDC_ARROW           (32512)
#define UF_IDC_CROSS           (32515)
#define UF_IDC_SIZENWSE        (32642)
#define UF_IDC_SIZENESW        (32643)
#define UF_IDC_SIZEWE          (32644)
#define UF_IDC_SIZENS          (32645)
#define UF_IDC_SIZEALL         (32646)

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
	void Init(IUiFeatureKernel* pKernelWindow, CFeatureControlList *pCtrlList, CWindowsViewTree *pWndTree);

	// 判断鼠标坐标是否落在了窗口内部
	bool PtInWindow(CPoint point);

private:
	void DrawWindowView();
	// 设置光标
	void SetViewCursor(int nCursor);

	void ResetViewShowSize();
	// 是否在窗口的8个方块内移动
	bool OnMouseMove_FangKuai8(CPoint point, bool bIsWnd);
	void OnMouseMove_LButtonDown(CPoint point);
	// 绘制创建新控件时的矩形
	void DrawCreateCtrlRect();
	// 取得新控件的大小
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

	bool m_bInitOk;
	CDrawingBoard m_MemDc;

	bool m_bIsLButtonDown;
	CPoint m_LBtnDownPos;
	CPoint m_LBtnUpPos;
	CPoint m_MouseMovePos;

	bool m_bCreateNewCtrl;

	IWindowBase *m_pCurrentWnd;
	bool m_bMoveInWndFangKuai8;
	bool m_bMoveInCtrlFangKuai8;

	// 创建新控件时的父控件
	IControlBase *m_pCreateCtrlParentCtrl;

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
};

#ifndef _DEBUG  // UiFeatureBuilderView.cpp 中的调试版本
inline CUiFeatureBuilderDoc* CUiFeatureBuilderView::GetDocument() const
   { return reinterpret_cast<CUiFeatureBuilderDoc*>(m_pDocument); }
#endif
