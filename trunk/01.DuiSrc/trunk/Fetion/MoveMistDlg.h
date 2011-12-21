
#pragma once
#include "Fetion.h"


class CMoveMistDlg : public CHighEfficiencyDlg
{
public:
	CMoveMistDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId);
	~CMoveMistDlg(void);

	void SetBmpDc(CBitmapDC *pBmpDc) { m_pBmpDc = pBmpDc; };

	void CloseWindowImd() { EndThisDialog(); };
	virtual void CloseWindow();
protected:
	virtual void OnCreate();
	virtual LRESULT OnTimer(WPARAM wParam, LPARAM lParam);

	BLENDFUNCTION m_Blend;//结构体BLENDFUNCTION用于指定两个DC(画图设备)的融合方式。

	virtual void OnPaint(HDC hPaintDc);
	virtual LRESULT OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam);

	void HidenTaskbar();
protected:
	CBaseCtrlManager m_UiManager;
	CBitmapDC *m_pBmpDc;
	int m_nCloseTimer;
	int m_nCloseAlpha;
};
