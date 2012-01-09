
// UiFeatureBuilderView.h : CUiFeatureBuilderView ��Ľӿ�
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
	void Init(IUiFeatureKernel* pKernelWindow, CFeatureControlList *pCtrlList, CWindowsViewTree *pWndTree);

	// �ж���������Ƿ������˴����ڲ�
	bool PtInWindow(CPoint point);

private:
	void DrawWindowView();
	// ���ù��
	void SetViewCursor(int nCursor);

	void ResetViewShowSize();
	// �Ƿ��ڴ��ڵ�8���������ƶ�
	bool OnMouseMove_FangKuai8(CPoint point, bool bIsWnd);
	void OnMouseMove_LButtonDown(CPoint point);
	// ���ƴ����¿ؼ�ʱ�ľ���
	void DrawCreateCtrlRect();
	// ȡ���¿ؼ��Ĵ�С
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

	// �����¿ؼ�ʱ�ĸ��ؼ�
	IControlBase *m_pCreateCtrlParentCtrl;

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
};

#ifndef _DEBUG  // UiFeatureBuilderView.cpp �еĵ��԰汾
inline CUiFeatureBuilderDoc* CUiFeatureBuilderView::GetDocument() const
   { return reinterpret_cast<CUiFeatureBuilderDoc*>(m_pDocument); }
#endif
