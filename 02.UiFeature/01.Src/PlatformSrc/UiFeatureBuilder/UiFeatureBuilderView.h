
// UiFeatureBuilderView.h : CUiFeatureBuilderView 类的接口
//


#pragma once
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IWindowBase.h"

class CFeatureControlList;
class CUiFeatureBuilderView : public CFormView
{
protected: // 仅从序列化创建
	CUiFeatureBuilderView();
	DECLARE_DYNCREATE(CUiFeatureBuilderView)

public:
	enum{ IDD = IDD_UIFEATUREBUILDER_FORM };

// 属性
public:
	CUiFeatureBuilderDoc* GetDocument() const;
	void SetNewControl(bool bIsNew);
	void SetProjectInitState(bool bInitOk);

	void ResetShowWindow(IWindowBase *pCurrentWnd);
	void Init(IUiFeatureKernel* pKernelWindow, CFeatureControlList *pCtrlList);

private:
	void DrawWindowView();
	IUiEngine* GetUiEngine();

	void ResetViewShowSize();

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CUiFeatureBuilderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HMODULE m_hUiEngineDll;
	IUiEngine *m_pUiEngine;

	CFeatureControlList *m_pControlList;
	IUiFeatureKernel* m_pKernelWindow;
	IPropertySkinManager *m_pSkinManager;
	bool m_bNewCtrl;
	bool m_bInitOk;
	CDrawingBoard m_MemDc;

	IWindowBase *m_pCurrentWnd;

private:
	ULONG_PTR m_gdiplusToken;

protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

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
};

#ifndef _DEBUG  // UiFeatureBuilderView.cpp 中的调试版本
inline CUiFeatureBuilderDoc* CUiFeatureBuilderView::GetDocument() const
   { return reinterpret_cast<CUiFeatureBuilderDoc*>(m_pDocument); }
#endif
