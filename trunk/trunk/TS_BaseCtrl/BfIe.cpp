
#include "BfIe.h"


CBfIe::CBfIe(HINSTANCE hInstance)
{
}

CBfIe::~CBfIe(void)
{
}

void CBfIe::OnPaint()
{
	// 从当前裁减区中去除本窗口
	NotDrawWindow();
}

void CBfIe::MoveWindow(CRect ToRect, HDWP hWinPoslnfo)
{
	CDirectUiWindow::MoveWindow(ToRect, hWinPoslnfo);
	m_WebId.MoveWindow(ToRect);
}

bool CBfIe::CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
								CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	bool bRet = CDirectUiWindow::CreateWnd(pParentDlg, pUiManager, pMsgCtrl, WndRect, nWndId, WndType, nImageId, strImagePath, nImageType);
	if (bRet)
	{
		m_WebId.LaunchIE(pParentDlg->GetSafeHandle(), CRect(0, 0, 100, 100), _T("www.baidu.com"));
	}

	return bRet;
}
