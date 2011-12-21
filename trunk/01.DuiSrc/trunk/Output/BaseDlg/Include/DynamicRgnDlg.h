
#pragma once
#include "HighEfficiencyDlg.h"

class CDynamicRgnDlg : public CHighEfficiencyDlg
{
public:
	CDynamicRgnDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId);
	~CDynamicRgnDlg(void);

protected:
	// ʵ�崰����Ϣ
	virtual LRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam);
	virtual void OnPaint(HDC hPaintDc);
	virtual void OnCreate();

	// DirectUi������Ϣ
	// ������������Ϣ
	virtual void DUI_OnLButtonDown(WPARAM wParam, LPARAM lParam);
	// ������̧����Ϣ
	virtual void DUI_OnLButtonUp(WPARAM wParam, LPARAM lParam);
	// ������˫����Ϣ
	virtual void DUI_OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
	// �����봰��
	virtual void DUI_OnMouseHover(WPARAM wParam, LPARAM lParam);
	// ����뿪����
	virtual void DUI_OnMouseLeave(WPARAM wParam, LPARAM lParam);
};
