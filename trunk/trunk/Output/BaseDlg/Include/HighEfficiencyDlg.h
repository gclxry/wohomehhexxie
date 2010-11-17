
#pragma once
#include "DirectUiDlg.h"
#include "DirectUiManager.h"

class CHighEfficiencyDlg : public CDirectUiDlg
{
public:
	CHighEfficiencyDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId);
	~CHighEfficiencyDlg(void);

	virtual bool OnDirectUiWindowMsgProc(int nMsgId, DWM_INFO &MsgInfo);
	static void SetNeetLButtonUpMsg() { m_bIsNeedLButtonUpMsg = true; };

protected:
	// ʵ�崰����Ϣ
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
	virtual LRESULT OnSizeProc(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam);

	// �����Ƿ��ʼ��
	virtual bool IsReady();
	void MaxOrResWnd();

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

private:
	void SetWndRgn(int cx, int cy);
	static bool m_bIsNeedLButtonUpMsg;

protected:
	CDirectUiManager *m_pUiManager;
};
