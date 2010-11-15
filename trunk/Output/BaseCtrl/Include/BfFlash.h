
#pragma once
#include "BaseCtrlDefs.h"


class CBfFlash : public CDirectUiWindow
{
public:
	CBfFlash(void);
	virtual ~CBfFlash(void);

	// ´´½¨´°¿Ú
	virtual bool CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
		CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);

	void PlayFlash(CString strFlashPath);
	virtual void OnDestroy();

	virtual void MoveWindow(CRect ToRect, HDWP hWinPoslnfo);
	virtual void OnPaint();
	virtual void OnTimer(int nTimerId);
	virtual void OnActivateApp(WPARAM wParam, LPARAM lParam);

protected:
	virtual bool IsReady();

private:
	CString m_strFlashPath;
	bool m_bIsInit;
	HINSTANCE m_hDllHandle;

	//
	pInitPlayWnd m_fpInitPlayWnd;
	pUnInit m_fpUnInit;
	pPlayFlash m_fpPlayFlash;
	pMovePlayWindow m_fpMovePlayWindow;
	pOnTimerPlay m_fpOnTimerPlay;
	pOnPaint m_fpOnPaint;
	pOnActivateApp m_fpOnActivateApp;
};
