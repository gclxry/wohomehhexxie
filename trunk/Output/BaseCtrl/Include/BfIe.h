
#pragma once
#include "BaseCtrlDefs.h"
#include "BfWindowsWnd.h"
#include "WebBrowser.h"

class CBfIe : public CDirectUiWindow, public CBfWindowsWnd
{
public:
	CBfIe(HINSTANCE hInstance);
	virtual ~CBfIe(void);

	// 创建窗口
	virtual bool CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
		CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);

	// 移动窗口
	virtual void MoveWindow(CRect ToRect, HDWP hWinPoslnfo);

protected:
	virtual void OnPaint();
	virtual void OnMouseHover(CPoint point);
	virtual void OnLoseFocus();
	virtual void OnSetFocus();

	virtual LPCTSTR GetSuperClassName() const;
	virtual LPCTSTR GetWindowClassName() const;

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	CWebBrowser m_WebId;
};
