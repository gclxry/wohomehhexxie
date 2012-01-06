
// UiFeatureBuilderView.h : CUiFeatureBuilderView ��Ľӿ�
//


#pragma once
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\IControlBase.h"


#define UF_IDC_ARROW           (32512)
#define UF_IDC_CROSS           (32515)
#define UF_IDC_SIZENWSE        (32642)
#define UF_IDC_SIZENESW        (32643)
#define UF_IDC_SIZEWE          (32644)
#define UF_IDC_SIZENS          (32645)
#define UF_IDC_SIZEALL         (32646)

class CFeatureControlList;
class CUiFeatureBuilderView : public CFormView
{
protected: // �������л�����
	CUiFeatureBuilderView();
	DECLARE_DYNCREATE(CUiFeatureBuilderView)

public:
	enum{ IDD = IDD_UIFEATUREBUILDER_FORM };

// ����
public:
	CUiFeatureBuilderDoc* GetDocument() const;
	void SetNewControl(bool bIsNew);
	void SetProjectInitState(bool bInitOk);

	void ResetShowWindow(IWindowBase *pCurrentWnd);
	void Init(IUiFeatureKernel* pKernelWindow, CFeatureControlList *pCtrlList);

	// �ж���������Ƿ������˴����ڲ�
	bool PtInWindow(CPoint point);
private:
	void DrawWindowView();
	IUiEngine* GetUiEngine();
	// ���ù��
	void SetViewCursor(int nCursor);

	void ResetViewShowSize();
	// �Ƿ��ڴ��ڵ�8���������ƶ�
	bool OnMouseMove_FangKuai8(CPoint point, bool bIsWnd);
	void OnMouseMove_LButtonDown(CPoint point);
	// ���ƴ����¿ؼ�ʱ�ľ���
	void DrawCreateCtrlRect();
	// ȡ��ѡ��Ŀؼ�
	IControlBase* GetSelectControl(CPoint point);
	// ͨ�������ק������һ���¿ؼ�
	void CreateNewControl();

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

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
	IUiFeatureKernel* m_pUiKernel;
	IPropertySkinManager *m_pSkinManager;
	bool m_bInitOk;
	CDrawingBoard m_MemDc;

	bool m_bIsLButtonDown;
	CPoint m_LBtnDownPos;
	CPoint m_LBtnUpPos;
	CPoint m_MouseMovePos;

	bool m_bCreateNewCtrl;

	IWindowBase *m_pCurrentWnd;
	bool m_bMoveInWndFangKuai8;

	IControlBase *m_pSelectControl;
	bool m_bMoveInCtrlFangKuai8;

	// ��������������ͼ��ƫ����
	CSize m_ScrollOffset;

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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // UiFeatureBuilderView.cpp �еĵ��԰汾
inline CUiFeatureBuilderDoc* CUiFeatureBuilderView::GetDocument() const
   { return reinterpret_cast<CUiFeatureBuilderDoc*>(m_pDocument); }
#endif
