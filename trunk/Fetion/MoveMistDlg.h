
#pragma once
#include "Fetion.h"


class CMoveMistDlg : public CHighEfficiencyDlg
{
public:
	CMoveMistDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId);
	~CMoveMistDlg(void);

	void SetBmpDc(CBitmapDC *pBmpDc) { m_pBmpDc = pBmpDc; };

protected:
	virtual void OnCreate();
	virtual LRESULT OnTimer(WPARAM wParam, LPARAM lParam);

	BLENDFUNCTION m_Blend;//�ṹ��BLENDFUNCTION����ָ������DC(��ͼ�豸)���ںϷ�ʽ��

	virtual void OnPaint(HDC hPaintDc);
	virtual LRESULT OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam);

protected:
	CBaseCtrlManager m_UiManager;
	CBitmapDC *m_pBmpDc;
};
