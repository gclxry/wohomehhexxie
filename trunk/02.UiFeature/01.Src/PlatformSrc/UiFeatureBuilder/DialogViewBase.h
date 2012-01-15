#if !defined(AFX_DialogViewBase_H__3586FDB6_FC0D_4FF7_BA09_D86692F0006A__INCLUDED_)
#define AFX_DialogViewBase_H__3586FDB6_FC0D_4FF7_BA09_D86692F0006A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogViewBase.h : header file
//

#include "Resource.h"
#include "..\..\Inc\CDrawingBoard.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogViewBase dialog

class CDialogViewBase : public CDialog
{
// Construction
public:
	void EndDrag();
	CDialogViewBase(CWnd* pParent = NULL);   // standard constructor


protected:
	bool m_bIsLBtnDown;
	CPoint m_ptLBtnDown;

	// 真实的滚动条位置
	int m_nVScrollPos;
	int m_nHScrollPos;

	// dialog size as you see in the resource view (original size)
	// 在View中看到的尺寸，包括看不见的部分，最小不小于对话框的尺寸
	CRect m_rcViewSize;
	// 实际对话框的大小
	CRect m_rcDlgSize;

protected:
	CDrawingBoard m_MemDc;

protected:
	void SetScrollBarSize(int cx, int cy);
	virtual void OnSize_SetViewSize(int cx, int cy);
	virtual void OnDraw();

// Dialog Data
	//{{AFX_DATA(CDialogViewBase)
	enum { IDD = IDD_IMAGEBASE_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogViewBase)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogViewBase)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DialogViewBase_H__3586FDB6_FC0D_4FF7_BA09_D86692F0006A__INCLUDED_)
