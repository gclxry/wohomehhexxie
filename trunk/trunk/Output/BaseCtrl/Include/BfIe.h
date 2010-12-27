
#pragma once
#include "BaseCtrlDefs.h"
#include "BfWindowsWnd.h"
#include "WebBrowser.h"

class CBfIe : public CDirectUiWindow
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

private:
	CWebBrowser m_WebId;
};
