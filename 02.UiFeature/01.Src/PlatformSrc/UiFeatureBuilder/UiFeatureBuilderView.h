
// UiFeatureBuilderView.h : CUiFeatureBuilderView ��Ľӿ�
//


#pragma once


class CUiFeatureBuilderView : public CView
{
protected: // �������л�����
	CUiFeatureBuilderView();
	DECLARE_DYNCREATE(CUiFeatureBuilderView)

// ����
public:
	CUiFeatureBuilderDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CUiFeatureBuilderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // UiFeatureBuilderView.cpp �еĵ��԰汾
inline CUiFeatureBuilderDoc* CUiFeatureBuilderView::GetDocument() const
   { return reinterpret_cast<CUiFeatureBuilderDoc*>(m_pDocument); }
#endif

