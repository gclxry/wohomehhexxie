
// UiFeatureBuilderView.h : CUiFeatureBuilderView ��Ľӿ�
//


#pragma once
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IWindowBase.h"

class CFeatureControlList;
class CUiFeatureBuilderView : public CView
{
protected: // �������л�����
	CUiFeatureBuilderView();
	DECLARE_DYNCREATE(CUiFeatureBuilderView)

// ����
public:
	CUiFeatureBuilderDoc* GetDocument() const;
	void SetNewControl(bool bIsNew);
	void SetProjectInitState(bool bInitOk);

	void ResetShowWindow(IWindowBase *pCurrentWnd);
	void Init(IUiFeatureKernel* pKernelWindow, CFeatureControlList *pCtrlList);

private:
	void DrawWindowView();
	IUiEngine* GetUiEngine();

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

private:
	void ResetViewSize();

// ʵ��
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

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // UiFeatureBuilderView.cpp �еĵ��԰汾
inline CUiFeatureBuilderDoc* CUiFeatureBuilderView::GetDocument() const
   { return reinterpret_cast<CUiFeatureBuilderDoc*>(m_pDocument); }
#endif

