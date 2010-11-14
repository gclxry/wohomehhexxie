
#pragma once
#include "Win32BaseDlg.h"
#include "DirectUi.h"
#include "DirectUiWndMsgCtrl.h"

class CHighEfficiency : public CWin32BaseDlg, public CDirectUiWndMsgCtrl
{
public:
	CHighEfficiency(HINSTANCE hInstance, HWND hParentWnd, int nIconId);
	~CHighEfficiency(void);

	bool OnDirectUiWndMsgProc(int nMsgId, DWM_INFO &MsgInfo);
	static void SetNeetLButtonUpMsg() { m_bIsNeedLButtonUpMsg = true; };

protected:
	// 实体窗口消息
	virtual void OnPaint(HDC hPaintDc);
	virtual void OnDestroy();
	virtual void OnCreate();
	virtual LRESULT OnNcActive(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnEraseBkgnd(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcPaint(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnEnterSizeMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnTimer(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnActivateApp(WPARAM wParam, LPARAM lParam);

	virtual LRESULT OnMeasureItem(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnDrawItem(WPARAM wParam, LPARAM lParam);

	virtual LRESULT OnSizeProc(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam);

	virtual void RedrawDlg();

	// 窗口是否初始化
	virtual bool IsReady();
	void MaxOrResWnd();

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

	// 是否有标准的标题栏
	void HaveNormalCaptionBar(bool bIsHave) { m_bIsHaveCaption = bIsHave; };

private:
	void SetWndRgn(int cx, int cy);
	static bool m_bIsNeedLButtonUpMsg;

protected:
	CDirectUiManager m_UiManager;
	bool m_bIsHaveCaption;
};
