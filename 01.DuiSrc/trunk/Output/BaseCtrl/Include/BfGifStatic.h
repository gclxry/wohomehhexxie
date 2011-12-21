
#pragma once
#include "BfLinkStatic.h"

class CBfGifStatic : public CBfLinkStatic
{
public:
	CBfGifStatic(void);
	virtual ~CBfGifStatic(void);

	virtual void OnPaint();
	virtual bool CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
		CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);

	CRect GetGifRect();
	
private:
	static UINT WINAPI DrawGifThread(LPVOID lpParameter);
	void DrawGif();

private:
	CGifImage *m_pGifImg;
	HANDLE m_hThread;
};
