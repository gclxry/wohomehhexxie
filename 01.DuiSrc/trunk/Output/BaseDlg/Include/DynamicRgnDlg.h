
#pragma once
#include "HighEfficiencyDlg.h"

class CDynamicRgnDlg : public CHighEfficiencyDlg
{
public:
	CDynamicRgnDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId);
	~CDynamicRgnDlg(void);

protected:
	// 实体窗口消息
	virtual LRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam);
	virtual void OnPaint(HDC hPaintDc);
	virtual void OnCreate();

	// DirectUi窗口消息
	// 鼠标左键按下消息
	virtual void DUI_OnLButtonDown(WPARAM wParam, LPARAM lParam);
	// 鼠标左键抬起消息
	virtual void DUI_OnLButtonUp(WPARAM wParam, LPARAM lParam);
	// 鼠标左键双击消息
	virtual void DUI_OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
	// 鼠标进入窗口
	virtual void DUI_OnMouseHover(WPARAM wParam, LPARAM lParam);
	// 鼠标离开窗口
	virtual void DUI_OnMouseLeave(WPARAM wParam, LPARAM lParam);
};
