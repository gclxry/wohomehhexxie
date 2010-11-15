//////////////////////////////////////////////////////////////////////////
// 类似MFC CStatic，静态文本窗口

#pragma once
#include "DirectUiWnd.h"
#include "FlashShow.h"

//typedef CSvodSvrPluginObject* (__stdcall *GET_PLUGIN_OBJECT_PROC)() 


class CBfFlash : public CDirectUiWindow
{
public:
	CBfFlash(void);
	virtual ~CBfFlash(void);

	// 创建窗口
	virtual bool CreateWnd(CWin32BaseDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWndMsgCtrl *pMsgCtrl,
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
