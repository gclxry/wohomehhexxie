
// UiFeatureBuilderView.h : CUiFeatureBuilderView ��Ľӿ�
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
protected: // �������л�����
	CUiFeatureBuilderView();
	DECLARE_DYNCREATE(CUiFeatureBuilderView)

public:
	virtual ~CUiFeatureBuilderView();
	enum{ IDD = IDD_UIFEATUREBUILDER_FORM };
	CUiFeatureBuilderDoc* GetDocument() const;

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ

public:
	void SetNewControl(bool bIsNew);
	void SetProjectInitState(bool bInitOk);

	void ResetShowWindow(IWindowBase *pCurrentWnd, IControlBase *pCtrlBase);
	void Init(IUiFeatureKernel* pKernelWindow, CFeatureControlList *pCtrlList, CWindowsViewTree *pWndTree, CPropertyViewCtrl* pPropViewCtrl);

	// �ж���������Ƿ������˴����ڲ�
	bool PtInWindow(CPoint point);

	IWindowBase* GetCurrentWindow() { return m_pCurrentWnd; };

private:
	void SetNeedSave();
	void DrawWindowView();
	// ���ù��
	void SetViewCursor(int nCursor);

	void ResetViewShowSize();
	// �Ƿ��ڴ��ڵ�8���������ƶ�
	SIZE_CTRL_TYPE OnMouseMove_FangKuai8(CPoint point, bool bIsWnd);
	void OnMouseMove_LButtonDown(CPoint point);
	void OnMouseMove_LButtonDown_MoveCtrl(CPoint point, IControlBase* pLBtnDownCtrl);
	void OnMouseMove_LButtonDown_SizeCtrl(SIZE_CTRL_TYPE nFangKuai8Type, CPoint point, IControlBase* pLBtnDownCtrl);
	// ���ƴ����¿ؼ�ʱ�ľ���
	void DrawMark();
	// �����¿ؼ��Ĵ�С
	void CreateNewControlf_SetNewCtrlRect();
	// ȡ��ѡ��Ŀؼ�
	IControlBase* GetSelectControl(CPoint point);
	// ͨ�������ק������һ���¿ؼ�
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

	// �����¿ؼ�ʱ�ĸ��ؼ�
	IControlBase *m_pDrawParentCtrl;

	// ����ƶ�ʱ�����Ŀؼ�
	IControlBase *m_pMouseMoveCtrl;

	// ��������������ͼ��ƫ����
	CSize m_ScrollOffset;

private:
	ULONG_PTR m_gdiplusToken;


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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // UiFeatureBuilderView.cpp �еĵ��԰汾
inline CUiFeatureBuilderDoc* CUiFeatureBuilderView::GetDocument() const
   { return reinterpret_cast<CUiFeatureBuilderDoc*>(m_pDocument); }
#endif
